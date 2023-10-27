#include "template_plugin.h"

// Define here the selectors
static const uint8_t COMMIT_SELECTOR[SELECTOR_SIZE] = {0xf1, 0x4f, 0xcb, 0xc8};

// Array of all the different ens selectors. Make sure this follows the same order as the
// enum defined in `opensea_plugin.h`
const uint8_t *const TEMPLATE_SELECTORS[NUM_SELECTORS] = {
    COMMIT_SELECTOR,
};
