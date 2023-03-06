// SPDX-License-Identifier: UNLICENSED
pragma solidity >=0.8.1;

contract B {
    uint256 num;

    function add(uint256 to_add) public returns (uint256) {
        num += to_add;

        return num;
    }
}

contract A {
    uint256 num;
    B b;

    constructor() {}

    event Add(uint256 to_add, uint256 num);
    event GetBalance(bool result);
    event Deploy();
    event CallB(uint256 to_add, uint256 num);

    function add(uint256 to_add) public returns (uint256) {
        num += to_add;

        emit Add(to_add, num);
        return num;
    }

    function get_balance() public payable returns (bool) {
        bool ret = msg.value > 1000;
        emit GetBalance(ret);
        return ret;
    }

    function deploy() public {
        b = new B();
        emit Deploy();
    }

    function callB(uint256 to_add) public returns (uint256) {
        uint256 ret = b.add(to_add);
        emit CallB(to_add, ret);
        return ret;
    }
}
