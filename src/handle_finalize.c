#include "swell_plugin.h"

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    // The total number of screen you will need.
    switch (context->selectorIndex) {
        case INITIALIZE:
            msg->numScreens = 1;
            break;
        case UPDATE_OPERATOR_ADDRESS:
        case UPDATE_OPERATOR_NAME:
        case UPDATE_OPERATOR_REWARD:
            msg->numScreens = 2;
            break;
        default:
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
