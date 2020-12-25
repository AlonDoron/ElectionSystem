#include <iostream>
#include <fstream>
#include "FilesHandler.h"
#include <string>
#include "CitizensDB.h"
#include "District.h"
#include "DistrictsArr.h"
#include "CitizensArr.h"
#include "PartiesArr.h"
#include "UserActions.h"
#include "Election.h"
#include "ElectionType.h"
#include "DividedDistrict.h"

using namespace std;
using namespace elections;

// ( 1 )
// This function creates new district and adds it to districtsArr.
void addNewDistrict(DistrictsArr& districtsArr, PartiesArr& partiesArr, CitizensDB& citizensDB);

// ( 2 )
// This function creates new citizen and adds it to citizensArr.
void addNewCitizen(CitizensDB& citizensDB, DistrictsArr& districtsArr);
// ( 3)
// This function creates new party and adds it to districtsArr.
void addNewParty(PartiesArr& partiesArr, DistrictsArr& districtsArr, CitizensDB& citizensDB);

// ( 4 )
// This function creates new rep and adds it to repsArr inside partiesArr.
void addNewRep(PartiesArr& partiesArr, CitizensDB& citizensDB, DistrictsArr& districtsArr);

// This function gets name and returns it's length.
int getStrLen(char* name);

// This function lets' the user vote by inputting citizen id and party, 
// and adds the vote to the party inside partiesArr.
void addNewVote(CitizensDB& citizensDB, DistrictsArr& districtsArr, PartiesArr& partiesArr);

void addNewSingleState(DistrictsArr& districtsArr);

void printMainMenu();

void handleElectionType(ElectionType& electionType, DistrictsArr& districtsArr, Date& date);

bool loadingElectionChoice();

void saveElectionRound(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr);

void loadElectionRound(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr);

int main() {
	char fileName[20];
	UserActions userActions; int action = 0;
	Date electionDate;
	DistrictsArr districtsArr; CitizensDB citizensDB;
	PartiesArr partiesArr; Election* election; ElectionType electionType;

	if (loadingElectionChoice())
		loadElectionRound(districtsArr, citizensDB, partiesArr);

	else
		handleElectionType(electionType, districtsArr, electionDate);

	printMainMenu();

	while (action != 10) {
		cin >> action;
		userActions = (UserActions)action;

		switch (userActions) {
		case UserActions::ADD_DISTRICT:
			if (electionType == ElectionType::REGULAR_ELECTION)
				addNewDistrict(districtsArr, partiesArr, citizensDB);

			else
				cout << "You can't add district" << endl;

			break;

		case UserActions::ADD_CITIZEN:
			addNewCitizen(citizensDB, districtsArr);
			break;

		case UserActions::ADD_PARTY:
			addNewParty(partiesArr, districtsArr, citizensDB);
			break;

		case UserActions::ADD_REP:
			addNewRep(partiesArr, citizensDB, districtsArr);
			break;

		case UserActions::SHOW_ALL_DISTRICTS:
			cout << districtsArr;
			break;

		case UserActions::SHOW_ALL_CITIZENS:
			cout << citizensDB;
			break;

		case UserActions::SHOW_ALL_PARTIES:
			cout << partiesArr;
			break;

		case UserActions::VOTE:
			addNewVote(citizensDB, districtsArr, partiesArr);
			break;

		case UserActions::SHOW_ELECTION_POLLS:
			if (electionType == ElectionType::REGULAR_ELECTION)
				election = new RegularElection(electionDate, districtsArr, partiesArr, citizensDB);

			else if (electionType == ElectionType::SIMPLE_ELECTION)
				election = new SimpleElection(electionDate, districtsArr, partiesArr, citizensDB);

			election->displayResults();
			break;

		case UserActions::EXIT:
			cout << "Goodbye." << endl;
			break;

		case UserActions::SAVE_ELECTION_ROUND:
			saveElectionRound(districtsArr, citizensDB, partiesArr);
			break;

		case UserActions::LOAD_ELECTION_ROUND:
			loadElectionRound(districtsArr, citizensDB, partiesArr);
			break;

		default:
			cout << "NO INPUT" << endl;
			break;
		}
	}
}

// ( 1 )
void addNewDistrict(DistrictsArr& districtsArr, PartiesArr& partiesArr, CitizensDB& citizensDB) {
	char name[20];
	int nameLen, numOfRep, districtType;
	District* newDist;

	cout << "Enter district name (max 20 chars): ";
	cin.ignore();
	cin.getline(name, 20);

	if (!districtsArr.isDistrictExistsByName((name))) {

		nameLen = getStrLen(name);

		cout << "Enter number of representatives: ";
		cin >> numOfRep;

		cout << "Enter district type: (0 = united, 1 = divided)" << endl;
		cin >> districtType;

		if (districtType == 0)
			newDist = new District(name, nameLen, numOfRep, districtsArr.getLogSize());
		if (districtType == 1)
			newDist = new DividedDistrict(name, nameLen, numOfRep, districtsArr.getLogSize());

		districtsArr.add(newDist);
		citizensDB.addEmptyCitizensArr(); // adding new citizensArr in DB for new district
		partiesArr.addNewDistToRepArr(); //// adding new citizensArr to reps list of each party for new district 
	}
	else
		cout << "The district with name " << name << " already exists!!!" << endl;


}
// ( 2 )
void addNewCitizen(CitizensDB& citizensDB, DistrictsArr& districtsArr)
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

	if (!citizensDB.isCitizenExistsById(id)) {

		cout << "Enter year of birth: ";
		cin >> year;

		cout << "Enter district number: (for simple election - press only 0)";
		cin >> districtNum;

		if (districtsArr.isDistExist(districtNum)) {
			Citizen newCitizen(name, nameLen, id, year, &districtsArr[districtNum]);
			citizensDB[districtNum].add(newCitizen);
			districtsArr[districtNum].addOneCitizen();
		}
		else
			cout << "The district with id " << districtNum << " does not exists!!!" << endl;
	}
	else
		cout << "The citizen with id " << id << " already exists!!" << endl;
}
// ( 3 )
void addNewParty(PartiesArr& partiesArr, DistrictsArr& districtsArr, CitizensDB& citizensDB)
{
	char name[20]; int nameLen; long int id;

	cout << "Enter party's name (max 20 chars): ";
	cin.ignore();
	cin.getline(name, 20);

	nameLen = getStrLen(name);

	cout << "Enter ID of the party leader: ";
	cin >> id;

	if (citizensDB.isCitizenExistsById(id)) {
		if (!partiesArr.isCitizenAlreadyLeader(id)) {
			Party newParty(name, nameLen, id, districtsArr.getLogSize());

			districtsArr.addNewPartyToVotesCounters(); // adding counter to new party in each district
			partiesArr.add(newParty);

		}
		else
			cout << "The citizen with the id " << id << " is already a party leader!!" << endl;
	}
	else
		cout << "No citizen with id " << id << " found!!!" << endl;

}
// ( 4 )
void addNewRep(PartiesArr& partiesArr, CitizensDB& citizensDB, DistrictsArr& districtsArr)
{
	int partyNum, districtNum; long int repId;

	cout << "Enter ID of rep: ";
	cin >> repId;

	if (citizensDB.isCitizenExistsById(repId)) {
		Citizen rep = citizensDB[repId];
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
// ( 8 )
void addNewVote(CitizensDB& citizensDB, DistrictsArr& districtsArr, PartiesArr& partiesArr)
{
	long int ID;
	int partyID;
	int districtNum;

	cout << "Enter your ID: ";
	cin >> ID;

	if (citizensDB.isCitizenExistsById(ID))
	{
		Citizen& voter = citizensDB[ID];

		if (!(voter.getVoted())) {

			cout << "Enter party: ";
			cin >> partyID;

			if (partyID >= 0 && partyID < partiesArr.getLogSize())
			{
				voter.setVoted(true);
				districtNum = voter.getDistrictNum();
				districtsArr[districtNum].addVoteToVotesCountersInIdx(partyID);
			}
			else
				cout << "Party with ID " << partyID << " does not exist" << endl;
		}
		else
			cout << "Voter with id " << ID << " has already voted!!" << endl;
	}
	else
		cout << "Voter with id " << ID << " not found!!" << endl;
}
// ( 11 )
void saveElectionRound(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr)
{
	char fileName[20];

	cout << "Enter file name: " << endl;
	cin >> fileName;

	ofstream outfile(fileName, ios::binary);

	if (!outfile) {
		cout << "Error opening the file " << fileName << endl;
		exit(-1);
	}

	outfile.close();

	int fileNameLen = getStrLen(fileName);

	FilesHandler filesHandler(fileName, fileNameLen);

	filesHandler.saveToFile(districtsArr, citizensDB, partiesArr);

	cout << "Election round has been successfully saved to " << fileName << endl;
}
// ( 12 )
void loadElectionRound(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr)
{
	// TODO: ADD KILL ALL ARRAYS BEFORE READING FROM FILE!
	districtsArr = DistrictsArr();
	citizensDB = CitizensDB();
	partiesArr = PartiesArr();
	char fileName[20];

	cout << "Enter file name: " << endl;
	cin >> fileName;

	ifstream infile(fileName, ios::binary);

	if (!infile) {
		cout << "Error opening the file " << fileName << endl;
		exit(-1);
	}


	int fileNameLen = getStrLen(fileName);

	FilesHandler filesHandler(fileName, fileNameLen);

	filesHandler.loadFromFile(districtsArr, citizensDB, partiesArr);

	infile.close();

	cout << "Election round has been successfully loaded from " << fileName << endl;
}

void handleElectionType(ElectionType& electionType, DistrictsArr& districtsArr, Date& date)
{
	int type = 0;
	cout << "Welcome to elections. " << endl;
	cout << "Enter the date of the election: (Day, Month, Year)" << endl;
	cin >> date.day >> date.month >> date.year;

	cout << "Enter type of election: (1 = regular, 0 = simple)" << endl;
	cin >> type;

	electionType = (ElectionType)type;

	switch (electionType) {
	case ElectionType::SIMPLE_ELECTION:
		addNewSingleState(districtsArr);
		break;
	case ElectionType::REGULAR_ELECTION:
		break;

	default:
		cout << "There is no type of choice that matches the number you have selected " << endl;
		break;
	}
}

void addNewSingleState(DistrictsArr& districtsArr)
{
	int numOfReps, nameLen;
	char name[20];
	District* newDist;

	cout << "Enter state name (max 20 chars): ";
	cin.ignore();
	cin.getline(name, 20);

	cout << "Enter num of reps: " << endl;
	cin >> numOfReps;

	nameLen = getStrLen(name);

	newDist = new DividedDistrict(name, nameLen, numOfReps, 0);
	districtsArr.add(newDist);
}

bool loadingElectionChoice()
{
	int answer;

	cout << "Would you like load Election or create your own? ( 1 = load Election , 0 = create my own) " << endl;
	cin >> answer;

	return answer;
}

int getStrLen(char* name) {
	int i = 0;

	while (name[i] != '\0')
		i++;

	return i;
}

void printMainMenu()
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
	cout << "11 - Save lection round to file" << endl;
	cout << "12 - Load election round from file" << endl;
}