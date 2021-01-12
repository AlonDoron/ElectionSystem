#include <iostream>
#include <fstream>
#include "FilesHandler.h"
#include <string>
#include <vector>
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
void addNewCitizen(CitizensDB& citizensDB, DistrictsArr& districtsArr, Date& electionDate);

// ( 3)
// This function creates new party and adds it to districtsArr.
void addNewParty(PartiesArr& partiesArr, DistrictsArr& districtsArr, CitizensDB& citizensDB);

// ( 4 )
// This function creates new rep and adds it to repsArr inside partiesArr.
void addNewRep(PartiesArr& partiesArr, CitizensDB& citizensDB, DistrictsArr& districtsArr);

// ( 8 )
// This function lets' the user vote by inputting citizen id and party, 
void addNewVote(CitizensDB& citizensDB, DistrictsArr& districtsArr, PartiesArr& partiesArr);

// ( 9 )
// a function that creates "Election" object where all the results will be claculated
void showElectionPolls(Date& electionDate, DistrictsArr& districtsArr, PartiesArr& partiesArr, CitizensDB& citizensDB);

void addNewSingleState(DistrictsArr& districtsArr, CitizensDB& citizensDB);

void printMainMenu();

void handleElectionType(ElectionType& electionType, DistrictsArr& districtsArr, CitizensDB& citizensDB, Date& date);

bool loadingElectionChoice();

// This function gets districtsArr, citizensDB and partiesArr and electionType,
// and saves it's data to bin file.
void saveElectionRound(DistrictsArr& districtsArr, CitizensDB& citizensDB,
	PartiesArr& partiesArr, ElectionType& type);

// This function gets districtsArr, citizensDB and partiesArr and electionType,
// and loading data into them from bin file.
void loadElectionRound(DistrictsArr& districtsArr, CitizensDB& citizensDB,
	PartiesArr& partiesArr, ElectionType& type);


int main() {

	UserActions userActions; int action = 0;
	Date electionDate;
	DistrictsArr districtsArr; CitizensDB citizensDB;
	PartiesArr partiesArr; ElectionType electionType;

	try {
		if (loadingElectionChoice())
			loadElectionRound(districtsArr, citizensDB, partiesArr, electionType);

		else
			handleElectionType(electionType, districtsArr, citizensDB, electionDate);

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
				addNewCitizen(citizensDB, districtsArr, electionDate);
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
				showElectionPolls(electionDate, districtsArr, partiesArr, citizensDB);
				break;

			case UserActions::EXIT:
				cout << "Goodbye." << endl;
				break;

			case UserActions::SAVE_ELECTION_ROUND:
				saveElectionRound(districtsArr, citizensDB, partiesArr, electionType);
				break;

			case UserActions::LOAD_ELECTION_ROUND:
				loadElectionRound(districtsArr, citizensDB, partiesArr, electionType);
				break;

			default:
				cout << "NO INPUT" << endl;
				break;
			}
		}
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}

}

// ( 1 )
void addNewDistrict(DistrictsArr& districtsArr, PartiesArr& partiesArr, CitizensDB& citizensDB) {
	string name;
	int numOfRep, districtType;
	District* newDist;

	cout << "Enter district name (max 20 chars): ";
	cin.ignore();
	getline(cin, name);

	try {

		cout << "Enter number of representatives: ";
		cin >> numOfRep;

		cout << "Enter district type: (0 = united, 1 = divided)" << endl;
		cin >> districtType;

		if (districtType == 0)
			newDist = new District(name, numOfRep, districtsArr.getLogSize());
		if (districtType == 1)
			newDist = new DividedDistrict(name, numOfRep, districtsArr.getLogSize());

		districtsArr.add(newDist);
		citizensDB.addEmptyCitizensArr(); // adding new citizensArr in DB for new district
		partiesArr.addNewDistToRepArr(); //// adding new citizensArr to reps list of each party for new district 

	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	catch (std::bad_alloc)
	{
		throw "somthing went wrong ==> allocation issue !!!";
	}
}
// ( 2 )
void addNewCitizen(CitizensDB& citizensDB, DistrictsArr& districtsArr, Date& electionDate)
{
	string name;
	int districtNum, year;
	long int id;

	cout << "Enter citizen's name (max 20 chars): ";
	cin.ignore();
	getline(cin, name);

	cout << "Enter ID: ";
	cin >> id;
	try {
		if (!citizensDB.isCitizenExistsById(id)) {

			cout << "Enter year of birth: ";
			cin >> year;

			cout << "Enter district number (for simple election - press only 0): ";
			cin >> districtNum;

			if (districtsArr.isDistExist(districtNum)) {
				Citizen newCitizen(name, id, year, &districtsArr[districtNum], electionDate.year);
				citizensDB[districtNum].add(newCitizen);
				districtsArr[districtNum].addOneCitizen();
			}
			else
				cout << "The district with id " << districtNum << " does not exists!!!" << endl;
		}
		else
			cout << "The citizen with id " << id << " already exists!!" << endl;

	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}

}
// ( 3 )
void addNewParty(PartiesArr& partiesArr, DistrictsArr& districtsArr, CitizensDB& citizensDB)
{
	string name; long int id;

	cout << "Enter party's name (max 20 chars): ";
	cin.ignore();
	getline(cin, name);

	cout << "Enter ID of the party leader: ";
	cin >> id;
	try {
		if (citizensDB.isCitizenExistsById(id)) {
			if (!partiesArr.isCitizenAlreadyLeader(id)) {
				Party newParty(name, id, districtsArr.getLogSize());

				districtsArr.addNewPartyToVotesCounters();
				partiesArr.add(newParty);
			}
			else
				cout << "The citizen with the id " << id << " is already a party leader!!" << endl;
		}
		else
			cout << "No citizen with id " << id << " found!!!" << endl;
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}

}
// ( 4 )
void addNewRep(PartiesArr& partiesArr, CitizensDB& citizensDB, DistrictsArr& districtsArr)
{
	int partyNum, districtNum; long int repId;

	cout << "Enter ID of rep: ";
	cin >> repId;
	try {
		if (citizensDB.isCitizenExistsById(repId)) {
			Citizen rep = citizensDB[repId];
			if (!partiesArr.isCitizenAlreadyRep(repId)) {
				cout << "Enter party number: ";
				cin >> partyNum;

				cout << "Enter district number: ";
				cin >> districtNum;

				partiesArr.addRep(rep, partyNum, districtNum, districtsArr.getLogSize());
			}
			else
				cout << "The citizen with id " << repId << " is already representative!!" << endl;
		}
		else
			cout << "The citizen with id " << repId << " does not exists!" << endl;
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}
// ( 8 )
void addNewVote(CitizensDB& citizensDB, DistrictsArr& districtsArr, PartiesArr& partiesArr)
{
	long int ID;
	int partyID;
	int districtNum;

	cout << "Enter your ID: ";
	cin >> ID;
	try {
		if (citizensDB.isCitizenExistsById(ID))
		{
			Citizen& voter = const_cast<Citizen&>(citizensDB[ID]);
			cout << "Enter party: ";
			cin >> partyID;

			partiesArr.isPartyNumberExist(partyID);

			voter.setVoted(true);
			districtNum = voter.getDistrictNum();
			districtsArr[districtNum].addVoteToVotesCountersInIdx(partyID);

		}
		else
			cout << "Voter with id " << ID << " not found!!" << endl;
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}
// ( 9 )
void showElectionPolls(Date& electionDate, DistrictsArr& districtsArr, PartiesArr& partiesArr, CitizensDB& citizensDB)
{	// a new election object is created
	Election election(electionDate, districtsArr, partiesArr, citizensDB);
	election.displayResults();
}
// ( 11 )
void saveElectionRound(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr, ElectionType& type)
{
	string fileName;

	cout << "Enter file name: " << endl;
	cin.ignore();
	getline(cin, fileName);

	ofstream outfile(fileName, ios::binary);

	if (!outfile) {
		cout << "Error opening the file " << fileName << endl;
		exit(-1);
	}

	outfile.close();

	FilesHandler filesHandler(fileName);

	filesHandler.saveToFile(districtsArr, citizensDB, partiesArr, (int)type);

	cout << "Election round has been successfully saved to " << fileName << endl;
}
// ( 12 )
void loadElectionRound(DistrictsArr& districtsArr, CitizensDB& citizensDB, PartiesArr& partiesArr, ElectionType& type)
{
	string fileName;

	// If districts are not empty, we need to clear all arrays first before loading into them.
	if (districtsArr.getLogSize() != 0)
	{
		districtsArr = DistrictsArr();

		if (citizensDB.getLogSize() != 0) {

			citizensDB = CitizensDB();

			if (partiesArr.getLogSize() != 0)
				partiesArr = PartiesArr();
		}
	}

	cout << "Enter file name: " << endl;
	cin.ignore();
	getline(cin, fileName);

	ifstream infile(fileName, ios::binary);

	if (!infile) {
		cout << "Error opening the file " << fileName << endl;
		exit(-1);
	}

	infile.close();

	FilesHandler filesHandler(fileName);

	int typeNum;
	filesHandler.loadFromFile(districtsArr, citizensDB, partiesArr, typeNum);
	type = (ElectionType)typeNum;

	cout << "Election round has been successfully loaded from " << fileName << endl;
}

void handleElectionType(ElectionType& electionType, DistrictsArr& districtsArr, CitizensDB& citizensDB, Date& date)
{
	int day, month, year;
	int type = 0;
	cout << "Welcome to elections. " << endl;
	cout << "Enter the date of the election: (Day, Month, Year)" << endl;
	cin >> day >> month >> year;


	Date _date(day, month, year);
	date = _date;

	cout << "Enter type of election: (1 = regular, 0 = simple)" << endl;
	cin >> type;

	electionType = (ElectionType)type;

	switch (electionType) {
	case ElectionType::SIMPLE_ELECTION:
		addNewSingleState(districtsArr, citizensDB);
		break;

	case ElectionType::REGULAR_ELECTION:
		break;

	default:
		cout << "There is no type of choice that matches the number you have selected " << endl;
		break;


	}
}
void addNewSingleState(DistrictsArr& districtsArr, CitizensDB& citizensDB)
{
	int numOfReps;
	string name;
	District* newDist;

	cout << "Enter state name (max 20 chars): ";
	cin.ignore();
	getline(cin, name);

	cout << "Enter num of reps: " << endl;
	cin >> numOfReps;
	try {
		newDist = new DividedDistrict(name, numOfReps, 0);
		districtsArr.add(newDist);
		citizensDB.addEmptyCitizensArr();
	}
	catch (std::bad_alloc)
	{
		throw "somthing went wrong ==> allocation issue !!!";
	}

}

bool loadingElectionChoice()
{
	int answer;

	cout << "Would you like load Election or create your own? ( 1 = load Election , 0 = create my own) " << endl;
	cin >> answer;

	return answer;
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


