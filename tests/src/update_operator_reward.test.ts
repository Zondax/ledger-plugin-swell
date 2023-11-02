import { processTest, populateTransaction } from "./test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "eth_update_operator_reward"; // <= Name of the test
const testDirSuffix = "eth_update_operator_reward"; // <= directory to compare device snapshots to
const testNetwork = "ethereum";
const signedPlugin = false;

const contractAddr = "0x46ddc39e780088b1b146aba8cbbe15dc321a1a1d"; // <= Address of the smart contract
const chainID = 1;

const inputData = "0xe8f28a6c00000000000000000000000071c7656ec7ab88b098defb751b7401b5f6d8976f000000000000000000000000b794f5ea0ba39494ce839613fffba74279579268";
// Create serializedTx and remove the "0x" prefix
const value = "3.1";
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);
const devices = [
   {
     name: "nanos",
     label: "Nano S",
     steps: 10, // <= Define the number of steps for this test case and this device
   },
  {
    name: "nanox",
    label: "Nano X",
    steps: 5, // <= Define the number of steps for this test case and this device
  },
  {
     name: "nanosp",
     label: "Nano S+",
     steps: 5, // <= Define the number of steps for this test case and this device
   },
];

devices.forEach((device) =>
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork)
);
