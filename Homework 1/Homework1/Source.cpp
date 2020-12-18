#include <iostream>
#include <string>
#include "CitizensDB.h"
#include "District.h"
#include "DistrictsArr.h"
#include "CitizensArr.h"
#include "PartiesArr.h"
#include "UserActions.h"
#include <algorithm>

using namespace std;
using namespace elections;

// This function creates new district and adds it to districtsArr.
void addNewDistrict(DistrictsArr& districtsArr, PartiesArr& partiesArr);

// This function creates new citizen and adds it to citizensArr.
void addNewCitizen(CitizensArr& citizensArr, DistrictsArr& districtsArr);

// This function creates new party and adds it to districtsArr.
void addNewParty(PartiesArr& partiesArr, int districtsArrSize, CitizensArr& citizensArr);

// This function creates new rep and adds it to repsArr inside partiesArr.
void addNewRep(PartiesArr& partiesArr, CitizensArr& citizensArr, DistrictsArr& districtsArr);

// This function gets name and returns it's length.
int getStrLen(char* name);

// This function lets' the user vote by inputting citizen id and party, 
// and adds the vote to the party inside partiesArr.
void createNewVote(CitizensArr& citizensArr, PartiesArr& partiesArr);

// this function is the managing function of counting votes and displaying results
void countVotes(DistrictsArr& districtsArr, CitizensArr& citizensArr, PartiesArr& partiesArr);

// this function will actually calculate the result into "results" array and display results data regarding number of
// votes (and percentage) in each party and voting percentage in each district
void setElected(int districtsNum, PartiesArr& partiesArr, CitizensDB& electedByDist,
	CitizensArr& citizensArr, Results* results);

// this function calculate an display the final result - meaning which representatives and how many went to 
// which party leader (and their details) , after doing so, the function will print
// final result relating to parties - meanning what party has won and (by order) and how
// many representatives
void printRep_Election(DistrictsArr& districtArr, Results* results, PartiesArr& partiesArr,
	CitizensDB& electedByDist, CitizensArr& citizensArr);

void sortCitizensByDistricts(CitizensDB& citizensDB, CitizensArr& citizensArr);
Results getResults(int* votesInDists, int partiesNum);
Results* checkWinner(Results* results, int distNum, int partiesNum);
void printMenu();

int main() {
	UserActions userActions;
	int action = 0;

	DistrictsArr districtsArr;
	CitizensArr citizensArr;
	PartiesArr partiesArr;

	printMenu();

	while (action != 10) {
		cin >> action;
		userActions = (UserActions)action;

		switch (userActions) {
		case UserActions::ADD_DISTRICT:
			addNewDistrict(districtsArr, partiesArr);
			break;

		case UserActions::ADD_CITIZEN:
			addNewCitizen(citizensArr, districtsArr);
			break;

		case UserActions::ADD_PARTY:
			addNewParty(partiesArr, districtsArr.getLogSize(), citizensArr);
			break;

		case UserActions::ADD_REP:
			addNewRep(partiesArr, citizensArr, districtsArr);
			break;

		case UserActions::SHOW_ALL_DISTRICTS:
			districtsArr.printDistricts();
			break;
		case UserActions::SHOW_ALL_CITIZENS:
			citizensArr.printCitizens();
			break;

		case UserActions::SHOW_ALL_PARTIES:
			partiesArr.printParties();
			break;

		case UserActions::VOTE:
			createNewVote(citizensArr, partiesArr);
			break;

		case UserActions::SHOW_ELECTION_POLLS:
			countVotes(districtsArr, citizensArr, partiesArr);
			break;

		default:
			cout << "NO INPUT" << endl;
			break;
		}
	}
}

// ( 1 )
void addNewDistrict(DistrictsArr& districtsArr, PartiesArr& partiesArr) {
	char name[20];
	int nameLen, numOfRep;

	cout << "Enter district name (max 20 chars): ";
	cin.ignore();
	cin.getline(name, 20);

	if (!districtsArr.isDistrictExistsByName((name))) {

		nameLen = getStrLen(name);

		cout << "Enter number of representatives: ";
		cin >> numOfRep;

		District newDist(name, nameLen, numOfRep, districtsArr.getLogSize());

		districtsArr.add(newDist);
		partiesArr.addDistrictToAllParties();
	}

	else {
		cout << "The district with name " << name << " already exists!!!" << endl;
	}

}
// ( 2 )
void addNewCitizen(CitizensArr& citizensArr, DistrictsArr& districtsArr)
{
	char name[20];
	int nameLen, districtNum, year;
	long int id;

	cout << "Enter citizen's name (max 20 chars): ";
	cin.ignore();
	cin.getline(name, 20);

	nameLen = getStrLen(name);

	cout << "Enter ID: ";
	cin >> id;

	Citizen* currCitizen = citizensArr.getCitizen(id);

	if (currCitizen == nullptr) {

		cout << "Enter year of birth: ";
		cin >> year;

		cout << "Enter district number: ";
		cin >> districtNum;

		District* currDistrict = districtsArr.getDistrictByNum(districtNum);

		if (currDistrict != nullptr) {
			Citizen newCitizen(name, nameLen, id, year, currDistrict);
			citizensArr.add(newCitizen);
		}

		else {
			cout << "The district with id " << districtNum << " does not exists!!!" << endl;
		}
	}

	else {
		cout << "The citizen with id " << id << " already exists!!" << endl;
	}
}
// ( 3 )
void addNewParty(PartiesArr& partiesArr, int districtsArrSize, CitizensArr& citizensArr)
{
	char name[20];
	int nameLen;
	long int id;

	cout << "Enter party's name (max 20 chars): ";
	cin.ignore();
	cin.getline(name, 20);

	nameLen = getStrLen(name);

	cout << "Enter ID of the party leader: ";
	cin >> id;

	Citizen* currCitizen = citizensArr.getCitizen(id);

	if (currCitizen != nullptr) {
		if (!partiesArr.isCitizenAlreadyLeader(id)) {
			Party newParty(name, nameLen, id, districtsArrSize);

			partiesArr.add(newParty);
		}
		else {
			cout << "The citizen with the id " << id << " is already a party leader!!" << endl;
		}
	}

	else {
		cout << "No citizen with id " << id << " found!!!" << endl;
	}
}
// ( 4 )
void addNewRep(PartiesArr& partiesArr, CitizensArr& citizensArr, DistrictsArr& districtsArr)
{
	int partyNum, districtNum;
	long int repId;

	cout << "Enter ID of rep: ";
	cin >> repId;

	Citizen* rep;
	rep = citizensArr.getCitizen(repId);

	if (rep != nullptr) {
		if (!partiesArr.isCitizenAlreadyRep(repId)) {
			cout << "Enter party number: ";
			cin >> partyNum;

			if ((partyNum < partiesArr.getLogSize()) && (partyNum >= 0)) {
				cout << "Enter district number: ";
				cin >> districtNum;

				if ((districtNum < districtsArr.getLogSize()) && (districtNum >= 0))
					partiesArr.addRep(rep, partyNum, districtNum);

				else
					cout << "The district with the number " << districtNum << " does not exists!!" << endl;
			}

			else
				cout << "The party with the number " << partyNum << " does not exists!!" << endl;
		}

		else
			cout << "The citizen with id " << repId << " is already representative!!" << endl;
	}

	else
		cout << "The citizen with id " << repId << " does not exists!" << endl;
}


void countVotes(DistrictsArr& districtsArr, CitizensArr& citizensArr, PartiesArr& partiesArr)
{
	int partiesNum = partiesArr.getLogSize();
	int districtsNum = districtsArr.getLogSize();

	// this CitizensDB will update with all the elected representatives 
	CitizensDB electedByDist(districtsNum);
	// this structre will update with the result of each district
	Results* results = new Results[districtsNum];

	cout << endl;
	cout << endl;
	cout << " ~ ~ ~ ~ ~ ~ ~ ~ Welcome to results screen of election day: 26/08/1993 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl;
	cout << endl;

	setElected(districtsNum, partiesArr, electedByDist, citizensArr, results);

	printRep_Election(districtsArr, results, partiesArr, electedByDist, citizensArr);


}


// Election day functions ------------------------------------------------------------------------------
void setElected(int districtsNum, PartiesArr& partiesArr,
	CitizensDB& electedByDist, CitizensArr& citizensArr, Results* results)
{
	CitizensDB citizensDB(districtsNum);
	sortCitizensByDistricts(citizensDB, citizensArr);
	int partiesNum = partiesArr.getLogSize();

	int* votesInDists = new int[partiesNum];
	int* generalVotes = new int[partiesNum];
	int* generalVotesInDist = new int[districtsNum];

	for (int i = 0; i < districtsNum; i++)
		generalVotesInDist[i] = 0;

	for (int i = 0; i < partiesNum; i++)
	{
		votesInDists[i] = 0;
		generalVotes[i] = 0;
	}

	for (int i = 0; i < districtsNum; i++)
	{
		int currDistSize = citizensDB.getCitizensArrByIndex(i).getLogSize();

		for (int j = 0; j < partiesNum; j++)
		{
			votesInDists[j] = ((float)(partiesArr.getPartyByIndex(j)).getVotesInDist(i) / currDistSize) * 100;
			generalVotesInDist[i] += (partiesArr.getPartyByIndex(j)).getVotesInDist(i);
			generalVotes[j] += (partiesArr.getPartyByIndex(j)).getVotesInDist(i);
		}
		CitizensArr currRepsToAdd;
		CitizensArr currAddedReps;

		for (int j = 0; j < partiesNum; j++)
		{
			Party currParty;
			currParty = partiesArr.getPartyByIndex(j);

			int numRepToAdd = ((float)votesInDists[j] / (float)100) * currDistSize;
			currRepsToAdd = *(currParty.getRepListByPercent(i, numRepToAdd));
			currAddedReps.add_citizenArr(currRepsToAdd);
		}
		electedByDist.add(currAddedReps, i);

		results[i] = getResults(votesInDists, partiesNum);
		results[i].numOfReps = currAddedReps.getLogSize();

		for (int z = 0; z < partiesNum; z++)
			votesInDists[z] = 0;
	}

	int generalVotesNum = 0;

	for (int i = 0; i < partiesNum; i++)
		generalVotesNum += generalVotes[i];


	for (int i = 0; i < partiesNum; i++)
		cout << "Number of votes in party " << partiesArr.getPartyByIndex(i).getPartyName() << " is " <<
		generalVotes[i] << " which is " << ((float)generalVotes[i] / (float)generalVotesNum) * 100 << "%" << endl;
	cout << endl;

	for (int i = 0; i < districtsNum; i++)
		cout << "Percentages of votes in district number " << i << " is " <<
		((float)generalVotesInDist[i] / (float)citizensDB.getCitizensArrByIndex(i).getLogSize()) * 100
		<< "%" << endl;
	cout << endl;
}

void printRep_Election(DistrictsArr& districtArr, Results* results,
	PartiesArr& partiesArr, CitizensDB& electedByDist, CitizensArr& citizensArr)
{
	for (int i = 0; i < electedByDist.getLogSize(); i++)
	{
		int currWinnerPartyId = results[i].winnerPartyId;

		long int partyLeaderId = partiesArr.getPartyByIndex(i).getLeaderId();
		char* distName = (districtArr.getDistrictByNum(i))->getDistrictName();


		cout << "District name: " << distName << "| Number of representatives: "
			<< electedByDist.getCitizensArrByIndex(i).getLogSize()
			<< "| all representatives went to: " << (citizensArr.getCitizen(partyLeaderId))->getName() << endl;
		cout << endl;
		electedByDist.getCitizensArrByIndex(i).printCitizens();
		cout << endl;
	}

	Results* res = checkWinner(results, districtArr.getLogSize(), partiesArr.getLogSize());

	for (int i = 0; i < partiesArr.getLogSize(); i++)
	{
		Party currParty;
		currParty = partiesArr.getPartyByIndex(res[i].winnerPartyId);
		long int partyLeaderId = currParty.getLeaderId();
		char* partyLeaderName = (citizensArr.getCitizen(partyLeaderId))->getName();
		char* currPartyName = currParty.getPartyName();
		int numOfRepsInParty = res[i].numOfReps;

		cout << endl;
		cout << "Party: " << currPartyName << " with leader: " << partyLeaderName
			<< " won " << numOfRepsInParty << " representatives" << endl;
	}

	delete[] res;
}

void sortCitizensByDistricts(CitizensDB& citizensDB, CitizensArr& citizensArr)
{
	int districtsSize = citizensDB.getLogSize();
	int citizensSize = citizensArr.getLogSize();

	for (int i = 0; i < districtsSize; i++)
	{
		CitizensArr currCitizensArr;

		for (int j = 0; j < citizensSize; j++) {
			Citizen currCitizen;
			currCitizen = citizensArr.getCitizenByIndex(j);

			if (currCitizen.getDistrictNum() == i) {
				// add to temp citizensArr then all the citizensArr add to eligibleVotersInDistrict
				currCitizensArr.add(currCitizen);
			}
		}

		citizensDB.add(currCitizensArr, i);
	}
}

Results* checkWinner(Results* results, int distNum, int partiesNum)
{
	Results* res = new Results[partiesNum];
	for (int i = 0; i < partiesNum; i++)
	{
		res[i].numOfReps = 0;
		res[i].winnerPartyId = i;
	}

	for (int i = 0; i < distNum; i++)
		res[results[i].winnerPartyId].numOfReps += results[i].numOfReps;

	sort(res, res + partiesNum);

	return res;
}

void createNewVote(CitizensArr& citizensArr, PartiesArr& partiesArr)
{
	long int ID;
	int partyID;
	int districtNum;
	Citizen* voter;

	cout << "Enter your ID: ";
	cin >> ID;

	voter = citizensArr.getCitizen(ID);

	if (voter != nullptr) {
		if (!(voter->getVoted())) {
			voter->setVoted(true);

			cout << "Enter party: ";
			cin >> partyID;

			districtNum = voter->getDistrictNum();

			partiesArr.addVoteToDistrictInParty(partyID, districtNum);

		}

		else
			cout << "Voter with id " << ID << " has already voted!!" << endl;
	}

	else
		cout << "Voter with id " << ID << " not found!!" << endl;
}

Results getResults(int* votesInDists, int partiesNum)
{
	Results res = { 0,0 };

	res.winnerPartyId = 0;

	for (int i = 0; i < partiesNum; i++)
		if (votesInDists[i] > votesInDists[res.winnerPartyId])
			res.winnerPartyId = i;

	return res;
}

int getStrLen(char* name) {
	int i = 0;

	while (name[i] != '\0')
		i++;

	return i;
}

void printMenu()
{
	cout << "Enter Action: " << endl;
	cout << "1 - add district" << endl;
	cout << "2 - add citizen" << endl;
	cout << "3 - add party" << endl;
	cout << "4 - add representative" << endl;
	cout << "5 - Show all districts" << endl;
	cout << "6 - show all citizens" << endl;
	cout << "7 - show all parties" << endl;
	cout << "8 - vote" << endl;
	cout << "9 - show election polls" << endl;
	cout << "10 - Exit" << endl;


}

