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
