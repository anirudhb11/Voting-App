var Election = artifacts.require("./Election.sol");

//inject all accounts for testing purpose.
contract("Election", function(accounts){
	var app, electionInstance;
	it("initializes with 2 candidates", function(){
		return Election.deployed().then(function(instance){
			return instance.candidatesCount();
		}).then(function(count){
			assert.equal(count, 2 );
		});
	});

	it("Checks initialazation of the 2 candidates.", function(){
		return Election.deployed().then(function(instance){
			app = instance;
			return app.candidates(1);
		}).then(function(cand){
			assert.equal(cand[0], 1, "Correct id of cand 1");
			assert.equal(cand[1], "Candidate 1", "coorect name of cand 1");
			assert.equal(cand[2], 0, "correct vote count of cand 1");
			return app.candidates(2);
		}).then(function(cand){
			assert.equal(cand[0], 2, "Correct id of cand 2");
			assert.equal(cand[1], "Candidate 2", "correct name of cand 2");
			assert.equal(cand[2], 0, "correct vote count of cand 2");
		});
	});

	//testing for whether the vote Count increases.
	it("allows voter to cast vote", function(){
		return Election.deployed().then(function(instance){
			electionInstance = instance;
			candidateId = 1;
			//return a transaction rcpt.
			return electionInstance.vote(candidateId, {from: accounts[0]});
		}).then(function(receipt){
			//checking if that voter voted..
			return electionInstance.voters(accounts[0]);
		}).then(function(voted){
			assert(voted, "Voter has voted");
			return electionInstance.candidates(candidateId);
		}).then(function(Candidate){
			var voteCount = Candidate[2];
			assert.equal(voteCount, 1, "increments Cand vote count by 1");
		});
	})

});

