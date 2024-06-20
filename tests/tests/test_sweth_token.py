from web3 import Web3
from tests.utils import run_test, load_contract

contract_rsweth_token = load_contract(
    "f951e335afb289353dc249e82926178eac7ded78"
)

def test_sweth_token_deposit(backend, firmware, navigator, test_name, wallet_addr):
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
