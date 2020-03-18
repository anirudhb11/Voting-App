//contract abstraction specific to truffle
//represents our smart contract
//means to interact with this.
var Election = artifacts.require("./Election.sol");

module.exports = function(deployer) {
  deployer.deploy(Election);
};
