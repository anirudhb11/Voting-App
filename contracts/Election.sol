//declaring the version of solidity that I am using
pragma solidity ^0.5.11;

//declaring contract

contract Election{
	//model a candidate
	struct Candidate{
		//unsigned integer
		uint id;
		string name;
		uint voteCount;
	}
	//store candidates
	//you are declaring a mapping from integer 
	//to struct candidate and this is used to 
	//fetch the value of the candidate.
	//since you have declared it public
	//Truffle gives you a free constructor
	//to access this.
	//chanding the state of conteact when we add 
	//candidate and writing to the blockchain
	//fetch candidates
	mapping(uint => Candidate) public candidates;
	
	//store voted accounts
	mapping(address=>bool)public voters;
	
	//store candidate count
	//increment as you add candidates
	uint public candidatesCount;
	constructor () public {
		 addCandidate("Candidate 1");
		 addCandidate("Candidate 2");
	}

	function addCandidate(string memory _name) private{
		candidatesCount++;
		candidates[candidatesCount] = Candidate(candidatesCount, _name, 0);
	}
	//declared as. public so that anything outside this contract can call this
	//would be triggered due to press of a buttion.
	function vote(uint _candidateId) public{
		//upd cand votes
		//recored that voter has voted..
		//only address of the voter is to be noted.

		//address has not voted before 
		//voting for a valid candidate

		//If false then any gas used in the computation of the
		//function will not be used.
		require(!voters[msg.sender]);
		require(_candidateId > 0 && _candidateId <= candidatesCount);


		voters[msg.sender] = true;

		candidates[_candidateId].voteCount++;

	}
}