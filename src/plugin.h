/*******************************************************************************
 *   Plugin Swell
 *   (c) 2023 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#pragma once

#include <string.h>
#include "eth_plugin_interface.h"

// All possible selectors of your plugin.
// EDIT THIS: Enter your selectors here, in the format X(NAME, value)
// A Xmacro below will create for you:
//     - an enum named selector_t with every NAME
//     - a map named SELECTORS associating each NAME with it's value
#define SELECTORS_LIST(X)                    \
    X(ADD_NEW_VALIDATOR, 0x60ec5216)         \
    X(ADD_OPERATOR, 0x54741d6d)              \
    X(DELETE_ACTIVE_VALIDATORS, 0xeda74e71)  \
    X(DELETE_PENDING_VALIDATORS, 0x242eba0e) \
    X(DEPOSIT, 0xd0e30db0)                   \
    X(DISABLE_OPERATOR, 0xf56408ed)          \
    X(ENABLE_OPERATOR, 0xdd307b99)           \
    X(INITIALIZE, 0xc4d66de8)                \
    X(UPDATE_OPERATOR_ADDRESS, 0x32f73258)   \
    X(UPDATE_OPERATOR_NAME, 0x9f5db69c)      \
    X(UPDATE_OPERATOR_REWARD, 0xe8f28a6c)    \
    X(USE_PUBKEYS_FOR_VALIDATOR, 0xc3953502) \
    X(WITHDRAWERC20, 0xf4f3b200)

// Xmacro helpers to define the enum and map
// Do not modify !
#define TO_ENUM(selector_name, selector_id)  selector_name,
#define TO_VALUE(selector_name, selector_id) selector_id,

// This enum will be automatically expanded to hold all selector names.
// The value SELECTOR_COUNT can be used to get the number of defined selectors
// Do not modify !
typedef enum selector_e {
    SELECTORS_LIST(TO_ENUM) SELECTOR_COUNT,
} selector_t;

// This array will be automatically expanded to map all selector_t names with the correct value.
// Do not modify !
extern const uint32_t SELECTORS[SELECTOR_COUNT];

#define HALF_PARAMETER_LENGTH 16

// Enumeration used to parse the smart contract data.
typedef enum {
    ADDRESS = 0,
    NAME,
    NAME_OFFSET,
    OFFSET,
    NAME_LEN,
    NAME_OFFSET_1,
    NAME_OFFSET_2,
    OPERATOR,
    REWARD,
    PUBKEY,
    PUBKEY_OFFSET,
    PUBKEY_LEN,
    PUBKEY_OFFSET_1,
    PUBKEY_OFFSET_2,
    N_PUBKEYS,
    TUPLE_OFFSET_1,
    OFFSETS,
    NONE
} parameter;

typedef struct {
    uint8_t value[ADDRESS_LENGTH];
} address_t;

typedef struct {
    uint16_t len;
    uint8_t text[PARAMETER_LENGTH + 1];
    bool ellipsis;
} name_t;

typedef struct {
    uint8_t value[INT256_LENGTH];
    bool ellipsis;
} bytes32_t;

typedef struct {
    union {
        struct {
            uint16_t n_pubkeys;
            uint16_t pubkeys_len[4];
            bytes32_t pubkey[4];
            uint8_t id;
            uint16_t tuple_offsets[4];
            uint16_t tuple_offsets_start;
        } add_new_validator;

        struct {
            uint16_t n_pubkeys;
            uint16_t pubkeys_len[4];
            bytes32_t pubkey[4];
            uint8_t id;
            uint16_t offsets[4];
            uint16_t offsets_start;
        } pubkey_methods;

        struct {
            name_t name;
            address_t operator;
            address_t reward;
            uint16_t name_offset;
        } add_operator;

        struct {
            address_t operator;
        } disable_enable_operator;

        struct {
            address_t control;
        } initialize;
        struct {
            address_t operator;
            address_t new_operator;
        } update_operator_address;
        struct {
            address_t operator;
            name_t name;
        } update_operator_name;

        struct {
            address_t operator;
            address_t reward;
        } update_operator_reward;

        struct {
            address_t token_addr;
        } withdrawerc20;

    } body;
} swell_tx_t;

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_s {
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

// Check if the context structure will fit in the RAM section ETH will prepare for us
// Do not remove!
#ifndef BUILDING_FUZZER
ASSERT_SIZEOF_PLUGIN_CONTEXT(context_t);
#endif
