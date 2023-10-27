# Ledger Template Plugin

This is a plugin for the Ethereum application which helps parsing and displaying relevant information when signing a template smart contract.

## Prerequisite

Clone the plugin to a new folder.

```shell
git clone https://github.com/Zondax/ledger-plugin-template.git
```

Then in the same folder clone two more repositories, which is the plugin-tools and app-ethereum.

```shell
git clone https://github.com/LedgerHQ/plugin-tools.git                          #plugin-tools
git clone --recurse-submodules https://github.com/LedgerHQ/app-ethereum.git     #app-ethereum
```
## Documentation

Need more information about the interface, the architecture, or general stuff about ethereum plugins? You can find more about them in the [ethereum-app documentation](https://github.com/LedgerHQ/app-ethereum/blob/master/doc/ethapp_plugins.adoc).

## Smart Contracts

Smart contracts covered by this plugin are:

|  Network | Smart Contract                 | Smart Contract Address |
| -------- | ------------------------------ | ---------------------- |
| Ethereum | ETH Registrar Controller       | [0x253553366da8546fc250f225fe3d25d0c782303b](https://etherscan.io/address/0x253553366da8546fc250f225fe3d25d0c782303b) |
| Ethereum| ETH Registrar Controller Old    | [0x283af0b28c62c092c9727f1ee09c02ca627eb7f5](https://etherscan.io/address/0x283af0b28c62c092c9727f1ee09c02ca627eb7f5) |
...


## Functions implemented:


|    Function               | Selector | Displayed Parameters   | 
| ---                       | ---      | ---                    |
|commit                     |0xf14fcbc8|<code>bytes32 commitment</code> |
|register                   |0x85f6d155| <table> <tbody> <tr><td><code>string name</code></td></tr> <tr><td><code>address owner</code></td></tr> <tr><td><code>uint256 duration</code></td></tr> <tr><td><code>bytes32 secret</code></td></tr> </tbody> </table>                               |
...

## Build

Go to the plugin-tools folder and run the "./start" script.
```shell
cd plugin-tools  # go to plugin folder
./start.sh       # run the script start.sh
```
The script will build a docker image and attach a console.
When the docker image is running go to the "ledger-plugin-template" folder and build the ".elf" files.
```shell
cd ledger-plugin-template/tests       # go to the tests folder in ledger-plugin-template
./build_local_test_elfs.sh      # run the script build_local_test_elfs.sh
```

## Tests

To test the plugin go to the tests folder from the "ledger-plugin-template" and run the script "test"
```shell
cd ledger-plugin-template/tests         # go to the tests folder in ledger-plugin-template
yarn test                       # run the script test
```
