#include "swell_plugin.h"

uint8_t bytes_missing = 0;

static void copy_text(uint8_t *dst, uint16_t dst_len, uint16_t max_len, const uint8_t *src) {
    size_t len = MIN(dst_len, max_len);
    memcpy(dst, src, len);
}

static void handle_operator_name(ethPluginProvideParameter_t *msg, context_t *context) {
    uint16_t containers = 0;  // group of 32 bytes needed to hold name

    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset) {
            return;
        }
        context->go_to_offset = false;
    }

    switch (context->next_param) {
        case OPERATOR:
            copy_address(context->tx.body.update_operator_name.operator.value,
                         msg->parameter,
                         sizeof(context->tx.body.update_operator_name.operator.value));
            context->next_param = NAME_OFFSET;
            break;
        case NAME_OFFSET:
            context->next_param = NAME_LEN;
            break;
        case NAME_LEN:
            if (!U2BE_from_parameter(msg->parameter,
                                     &context->tx.body.update_operator_name.name.len)) {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                return;
            }
            context->next_param = NAME;
            break;
        case NAME:
            // Name has less then 32
            if (context->tx.body.update_operator_name.name.len <= PARAMETER_LENGTH) {
                copy_text(context->tx.body.update_operator_name.name.text,
                          context->tx.body.update_operator_name.name.len,
                          PARAMETER_LENGTH,
                          msg->parameter);
                context->tx.body.update_operator_name.name.ellipsis = false;
                context->next_param = NONE;
            } else {  // Name has more then 32 bytes
                context->tx.body.update_operator_name.name.ellipsis = true;
                containers = context->tx.body.update_operator_name.name.len / PARAMETER_LENGTH;
                bytes_missing = context->tx.body.update_operator_name.name.len % PARAMETER_LENGTH;

                // copy first 16 bytes
                copy_text(context->tx.body.update_operator_name.name.text,
                          context->tx.body.update_operator_name.name.len,
                          HALF_PARAMETER_LENGTH,
                          msg->parameter);

                if (bytes_missing < HALF_PARAMETER_LENGTH) {
                    if (containers < 2) {  // only one container we still need bytes from this one
                                           // to complete the last 16. then go to last container
                        copy_text(
                            context->tx.body.update_operator_name.name.text + HALF_PARAMETER_LENGTH,
                            context->tx.body.update_operator_name.name.len - HALF_PARAMETER_LENGTH,
                            HALF_PARAMETER_LENGTH - bytes_missing,
                            msg->parameter + HALF_PARAMETER_LENGTH + bytes_missing);

                        context->offset = msg->parameterOffset + PARAMETER_LENGTH;
                        context->go_to_offset = true;
                        context->next_param = NAME_OFFSET_2;
                    } else {  // more then 1 container go to second-last and get missing bytes to
                              // complete the last 16
                        context->offset =
                            msg->parameterOffset + (containers - 1) * PARAMETER_LENGTH;
                        context->go_to_offset = true;
                        context->next_param = NAME_OFFSET_1;
                    }
                } else {  // last container has the last 16 bytes we need
                    context->offset = msg->parameterOffset + containers * PARAMETER_LENGTH;
                    context->go_to_offset = true;
                    context->next_param = NAME_OFFSET_2;
                }
            }
            break;
        case NAME_OFFSET_1:  // second last container
            copy_text(context->tx.body.update_operator_name.name.text + HALF_PARAMETER_LENGTH,
                      context->tx.body.update_operator_name.name.len - HALF_PARAMETER_LENGTH,
                      HALF_PARAMETER_LENGTH - bytes_missing,
                      msg->parameter + HALF_PARAMETER_LENGTH + bytes_missing);
            context->next_param = NAME_OFFSET_2;
            break;
        case NAME_OFFSET_2:                                // last container
            if (bytes_missing <= HALF_PARAMETER_LENGTH) {  // copy missing bytes
                copy_text(context->tx.body.update_operator_name.name.text + HALF_PARAMETER_LENGTH +
                              (HALF_PARAMETER_LENGTH - bytes_missing),
                          context->tx.body.update_operator_name.name.len - HALF_PARAMETER_LENGTH +
                              (HALF_PARAMETER_LENGTH - bytes_missing),
                          bytes_missing,
                          msg->parameter);
            } else {  // last container has 16 or more bytes, move the need offset to copy the last
                      // 16 bytes
                copy_text(context->tx.body.update_operator_name.name.text + HALF_PARAMETER_LENGTH,
                          context->tx.body.update_operator_name.name.len - HALF_PARAMETER_LENGTH,
                          HALF_PARAMETER_LENGTH,
                          msg->parameter + (bytes_missing - HALF_PARAMETER_LENGTH));
            }
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_operator_reward(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case OPERATOR:
            copy_address(context->tx.body.update_operator_reward.operator.value,
                         msg->parameter,
                         sizeof(context->tx.body.update_operator_reward.operator.value));
            context->next_param = REWARD;
            break;
        case REWARD:
            copy_address(context->tx.body.update_operator_reward.reward.value,
                         msg->parameter,
                         sizeof(context->tx.body.update_operator_reward.reward.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_operator_address(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case OPERATOR:
            copy_address(context->tx.body.update_operator_address.operator.value,
                         msg->parameter,
                         sizeof(context->tx.body.update_operator_address.operator.value));
            context->next_param = ADDRESS;
            break;
        case ADDRESS:
            copy_address(context->tx.body.update_operator_address.new_operator.value,
                         msg->parameter,
                         sizeof(context->tx.body.update_operator_address.new_operator.value));
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(ethPluginProvideParameter_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case UPDATE_OPERATOR_REWARD:
            handle_operator_reward(msg, context);
            break;
        case UPDATE_OPERATOR_NAME:
            handle_operator_name(msg, context);
            break;
        case UPDATE_OPERATOR_ADDRESS:
            handle_operator_address(msg, context);
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
