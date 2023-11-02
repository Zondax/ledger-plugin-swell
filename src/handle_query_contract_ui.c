#include <stdbool.h>
#include "swell_plugin.h"

// Set UI for any address screen.
static bool set_address_ui(ethQueryContractUI_t *msg, address_t *value) {
    // Prefix the address with `0x`.
    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
    // Setting it to `0` will make it work with every chainID :)
    uint64_t chainid = 0;

    // Get the string representation of the address stored in `context->beneficiary`. Put it in
    // `msg->msg`.
    return getEthAddressStringFromBinary(
        value->value,
        msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
        msg->pluginSharedRW->sha3,
        chainid);
}

static uint32_t array_to_hexstr(char *dst, size_t dstLen, const uint8_t *src, uint8_t count) {
    memset(dst, 0, dstLen);
    if (dstLen < (count * 2 + 1)) {
        return 0;
    }

    const char hexchars[] = "0123456789abcdef";
    for (uint8_t i = 0; i < count; i++, src++) {
        *dst++ = hexchars[*src >> 4u];
        *dst++ = hexchars[*src & 0x0Fu];
    }
    *dst = 0;  // terminate string

    return (uint32_t) (count * 2);
}

static bool set_addr_ui(ethQueryContractUI_t *msg, address_t *address, const char *title) {
    strlcpy(msg->title, title, msg->titleLength);
    return set_address_ui(msg, address);
}

static bool set_name_ui(ethQueryContractUI_t *msg, name_t *name, const char *title) {
    strlcpy(msg->title, title, msg->titleLength);
    if (name->ellipsis) {
        snprintf(msg->msg, msg->msgLength, "%.*s...%s", 16, name->text, name->text + 16);
        return true;
    } else {
        snprintf(msg->msg, msg->msgLength, "%s", name->text);
        return true;
    }
    return false;
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;
    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case INITIALIZE:
            if (msg->screenIndex == 0) {
                ret = set_addr_ui(msg, &context->tx.body.initialize.control, "Control Manager");
            } else {
                PRINTF("Received an invalid screenIndex\n");
                ret = false;
            }
            break;
        case UPDATE_OPERATOR_ADDRESS:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_addr_ui(msg,
                                      &context->tx.body.update_operator_address.operator,
                                      "Operator Addr");
                    break;
                case 1:
                    ret = set_addr_ui(msg,
                                      &context->tx.body.update_operator_address.new_operator,
                                      "New Operator Addr");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;
        case UPDATE_OPERATOR_NAME:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_addr_ui(msg,
                                      &context->tx.body.update_operator_name.operator,
                                      "Operator Addr");
                    break;
                case 1:
                    ret = set_name_ui(msg, &context->tx.body.update_operator_name.name, "Name");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;
        case UPDATE_OPERATOR_REWARD:
            switch (msg->screenIndex) {
                case 0:
                    ret = set_addr_ui(msg,
                                      &context->tx.body.update_operator_reward.operator,
                                      "Operator Addr");
                    break;
                case 1:
                    ret = set_addr_ui(msg,
                                      &context->tx.body.update_operator_reward.reward,
                                      "Reward Addr");
                    break;
                default:
                    PRINTF("Received an invalid screenIndex\n");
                    ret = false;
            }
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            ret = false;
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
