# Ledger Plugin Swell

This is a plugin for the Ethereum application which helps parsing and displaying relevant information when signing a Swell smart contract.

## Prerequisite

Clone the plugin to a new folder.

```shell
git clone https://github.com/libertify/ledger-plugin-lens.git
```

Then in the same folder clone the app-ethereum.

```shell
git clone --recurse-submodules https://github.com/LedgerHQ/app-ethereum.git     #app-ethereum
```

## Documentation

Need more information about the interface, the architecture, or general stuff about ethereum plugins? You can find more about them in the [ethereum-app documentation](https://github.com/LedgerHQ/app-ethereum/blob/master/doc/ethapp_plugins.adoc).

## Smart Contracts

Smart contracts covered by this plugin are:

|  Network | Smart Contract                 | Smart Contract Address |
| -------- | ------------------------------ | ---------------------- |
| Ethereum| Deposit Manager & Node Operator Registry    | [0x46DdC39E780088B1B146Aba8cBBe15DC321A1A1d](https://etherscan.io/address/0x46ddc39e780088b1b146aba8cbbe15dc321a1a1d) |
...


## Functions implemented:


|    Function                   | Selector | Displayed Parameters   | 
| ---                           | ---      | ---                    |
|updateOperatorRewardAddress    |0xe8f28a6c|<table> <tbody> <tr><td><code>address operator</code></td></tr> <tr><td><code>address reward</code></td></tr>  </tbody> </table>  |
|updateOperatorName*            |0x9f5db69c| <table> <tbody> <tr><td><code>address operator</code></td></tr> <tr><td><code>string name</code></td></tr>  </tbody> </table> |
...

For strings and byte arrays bigger then 32, plugin is showing the first and last 16 bytes in "16...16" format, due to memory limitations.

## Build

To build the plugin, go to your folder with Ethereum app and plugin. Open a new terminal window and run:
```shell
sudo docker run --rm -ti -v "$(realpath .):/app" --user $(id -u $USER):$(id -g $USER) ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest
```

In the container, go to the plugin repository, then to the tests/ folder.
```shell
cd ledger-plugin-swell/tests
./build_local_test_elfs.sh. 
```

## Tests

To test the plugin go to the tests folder from the "ledger-plugin-swell" and run the script "test"
```shell
cd ledger-plugin-swell/tests         # go to the tests folder in ledger-plugin-swell
yarn test                       # run the script test
```
