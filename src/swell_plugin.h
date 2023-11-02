#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SELECTORS 11

// Name of the plugin.
#define PLUGIN_NAME "Swell"

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    WITHDRAWERC20 = 0,
    UPDATE_OPERATOR_REWARD,
} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    ADDRESS = 0,
    OPERATOR,
    REWARD,
    NONE
} parameter;

extern const uint8_t *const SWELL_SELECTORS[NUM_SELECTORS];

typedef struct {
    uint8_t value[INT256_LENGTH];
} bytes32_t;

typedef struct {
    uint8_t value[ADDRESS_LENGTH];
} address_t;

typedef struct {
    union {
        struct {
            address_t token_addr;
        } withdrawerc20;

        struct {
            address_t operator;
            address_t reward;
        } update_operator_reward;
    } body;
} swell_tx_t;

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.
    uint16_t offset;     // Offset at which the array or struct starts.
    bool go_to_offset;   // If set, will force the parsing to iterate through parameters until
                         // `offset` is reached.

    // For both parsing and display.
    selector_t selectorIndex;

    // Tx related context
    swell_tx_t tx;
} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");
