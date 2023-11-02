#include "swell_plugin.h"

// Define here the selectors
static const uint8_t WITHDRAWERC20_SELECTOR[SELECTOR_SIZE] = {0xf4, 0xf3, 0xb2, 0x00};
static const uint8_t UPDATE_OPERATOR_REWARD_SELECTOR[SELECTOR_SIZE] = {0xe8, 0xf2, 0x8a, 0x6c};
static const uint8_t UPDATE_OPERATOR_NAME_SELECTOR[SELECTOR_SIZE] = {0x9f, 0x5d, 0xb6, 0x9c};
static const uint8_t UPDATE_OPERATOR_ADDRESS_SELECTOR[SELECTOR_SIZE] = {0x32, 0xf7, 0x32, 0x58};

// Array of all the different ens selectors. Make sure this follows the same order as the
// enum defined in `opensea_plugin.h`
const uint8_t *const SWELL_SELECTORS[NUM_SELECTORS] = {WITHDRAWERC20_SELECTOR,
                                                       UPDATE_OPERATOR_REWARD_SELECTOR,
                                                       UPDATE_OPERATOR_NAME_SELECTOR,
                                                       UPDATE_OPERATOR_ADDRESS_SELECTOR};
