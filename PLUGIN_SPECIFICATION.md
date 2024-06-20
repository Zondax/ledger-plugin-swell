# Technical Specification

## About

This documentation describes the smart contracts and functions supported by the Swell plugin.

## Smart Contracts

Smart contracts covered by this plugin are:

|  Network | Smart Contract                 | Smart Contract Address |
| -------- | ------------------------------ | ---------------------- |
| Ethereum| Deposit Manager & Node Operator Registry    | [0x46DdC39E780088B1B146Aba8cBBe15DC321A1A1d](https://etherscan.io/address/0x46ddc39e780088b1b146aba8cbbe15dc321a1a1d) |
| Ethereum| rswETH    | [0xFAe103DC9cf190eD75350761e95403b7b8aFa6c0](https://etherscan.io/address/0xFAe103DC9cf190eD75350761e95403b7b8aFa6c0) |
| Ethereum| swETH    | [0xf951e335afb289353dc249e82926178eac7ded78](https://etherscan.io/address/0xf951e335afb289353dc249e82926178eac7ded78#code) |


## Functions implemented


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
