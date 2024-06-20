# Ledger Plugin Swell
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
---

![zondax_light](docs/zondax_light.png#gh-light-mode-only)
![zondax_dark](docs/zondax_dark.png#gh-dark-mode-only)

_Please visit our website at [zondax.ch](https://www.zondax.ch)_

---

This is a plugin for the Ethereum application which helps parsing and displaying relevant information when signing a Swell smart contract.

- Ledger Nano S/S+/X/Stax Swell plugin
- Specs / Documentation
- Ragger tests

## ATTENTION

Please:

- **Do not use in production**
- **Do not use a Ledger device with funds for development purposes.**
- **Have a separate and marked device that is used ONLY for development and testing**

## Documentation

Need more information about the interface, the architecture, or general stuff about ethereum plugins? You can find more about them in the [ethereum-app documentation](https://github.com/LedgerHQ/app-ethereum/blob/master/doc/ethapp_plugins.adoc).

## Smart Contracts

Smart contracts covered by this plugin are:

|  Network | Smart Contract                 | Smart Contract Address |
| -------- | ------------------------------ | ---------------------- |
| Ethereum| Deposit Manager & Node Operator Registry    | [0x46DdC39E780088B1B146Aba8cBBe15DC321A1A1d](https://etherscan.io/address/0x46ddc39e780088b1b146aba8cbbe15dc321a1a1d) |
| Ethereum| rswETH    | [0xFAe103DC9cf190eD75350761e95403b7b8aFa6c0](https://etherscan.io/address/0xFAe103DC9cf190eD75350761e95403b7b8aFa6c0) |
| Ethereum| swETH    | [0xf951e335afb289353dc249e82926178eac7ded78](https://etherscan.io/address/0xf951e335afb289353dc249e82926178eac7ded78#code) |


## Functions implemented:


|    Function                   | Selector | Displayed Parameters   | 
| ---                           | ---      | ---                    |
|addNewValidatorDetails*    |0x60ec5216|<table> <tbody> <tr><td><code>bytes[] pubkeys</code></td></tr> </tbody> </table>  |
|addOperator*    |0x54741d6d|<table> <tbody> <tr><td><code>string name</code></td></tr> <tr><td><code>address operator</code></td></tr> <tr><td><code>address reward</code></td></tr>  </tbody> </table>  |
|deleteActiveValidators*    |0xeda74e71|<table> <tbody> <tr><td><code>bytes[] pubkeys</code></td></tr> </tbody> </table>  |
|deletePendingValidators*   |0x242eba0e|<table> <tbody> <tr><td><code>bytes[] pubkeys</code></td></tr> </tbody> </table>  |
|usePubKeysForValidatorSetup*   |0xc3953502|<table> <tbody> <tr><td><code>bytes[] pubkeys</code></td></tr> </tbody> </table>  |
|deposit     |0xd0e30db0|<table> <tbody> <tr><td><code>amount stake</code></td></tr>  </tbody> </table>  |
|disableOperator     |0xf56408ed|<table> <tbody> <tr><td><code>address operator</code></td></tr>  </tbody> </table>  |
|enableOperator   |0xdd307b99|<table> <tbody> <tr><td><code>address operator</code></td></tr>  </tbody> </table>  |
|initialize   |0xc4d66de8|<table> <tbody> <tr><td><code>address control_manager</code></td></tr>  </tbody> </table>  |
|updateOperatorControllingAddress    |0x32f73258|<table> <tbody> <tr><td><code>address operator</code></td></tr> <tr><td><code>address new_operator</code></td></tr>  </tbody> </table>  |
|updateOperatorRewardAddress    |0xe8f28a6c|<table> <tbody> <tr><td><code>address operator</code></td></tr> <tr><td><code>address reward</code></td></tr>  </tbody> </table>  |
|updateOperatorName*            |0x9f5db69c| <table> <tbody> <tr><td><code>address operator</code></td></tr> <tr><td><code>string name</code></td></tr>  </tbody> </table> |
|withdrawERC20   |0xf4f3b200|<table> <tbody> <tr><td><code>address token</code></td></tr>  </tbody> </table>  |

*For strings and byte arrays bigger then 32, plugin is showing the first and last 16 bytes in "16...16" format, due to memory limitations.
For addNewValidatorDetails, deleteActiveValidators, deletePendingValidators, usePubKeysForValidatorSetup, plugin can only verify transactions with 4 pubkeys maximum due to memory limitation.


## How to build

Ledger's recommended [plugin guide](https://developers.ledger.com/docs/dapp/embedded-plugin/code-overview/) is out-dated and doesn't work since they introduced a lot of new changes. Here's a simple way to get started with this repo:
1. Clone this repo (along with git submodules)
2. Install [Xquartz](https://www.xquartz.org/) and make sure you have enabled "Allow connections from network clients" enabled under "Security" settings.
3. Install and start Docker (Note: If Docker is already running, quit and start it after starting Xquartz, otherwise docker cannot connect to Xquartz).
4. Install the [Ledger Dev Tools VS Code plugin](https://marketplace.visualstudio.com/items?itemName=LedgerHQ.ledger-dev-tools#:~:text=ledger%2Dvscode%2Dextension,Plus%2C%20Nano%20X%2C%20Stax) and makes sure it's enabled
5. Once you have installed the plugin and open the repo, the plugin should by default try to create and start the containers. If it doesn't, you can simply click "Update Container" under "Ledger Dev Tools" in the Activity Side Bar on VS Code.
6. On the "Ledger Dev Tools" side bar, Select a target and then click on Build. 
7. Once build is complete, click on "Run tests" to run the tests

