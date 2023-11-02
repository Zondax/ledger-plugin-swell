#include "swell_plugin.h"

// Define here the selectors
static const uint8_t WITHDRAWERC20_SELECTOR[SELECTOR_SIZE] = {0xf4,0xf3,0xb2,0x00};
static const uint8_t UPDATE_OPERATOR_REWARD_SELECTOR[SELECTOR_SIZE] = {0xe8,0xf2,0x8a,0x6c};

// Array of all the different ens selectors. Make sure this follows the same order as the
// enum defined in `opensea_plugin.h`
const uint8_t *const SWELL_SELECTORS[NUM_SELECTORS] = {
    WITHDRAWERC20_SELECTOR,
    UPDATE_OPERATOR_REWARD_SELECTOR
};
