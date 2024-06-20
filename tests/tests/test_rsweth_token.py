from web3 import Web3
from tests.utils import run_test, load_contract

contract_rsweth_token = load_contract(
    "fae103dc9cf190ed75350761e95403b7b8afa6c0"
)

def test_rsweth_token_deposit(backend, firmware, navigator, test_name, wallet_addr):
    data = "0xd0e30db0"
    run_test(
        contract_rsweth_token, 
        data, 
        backend, 
        firmware, 
        navigator, 
        test_name, 
        wallet_addr
    )
