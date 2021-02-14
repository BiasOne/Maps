#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void readAndWrite();
void searchMapsandPrint(string findMe);
void RollDice(int numberOfRolls, int numberOfSides);
void printMaps();

map<int, string> censusState;
map<int, int> censusPerCapitaIncome;
map<int, int> censusPopulation;
map<int, int> censusHouseholdMedianIncome;
map<int, int> censusNumberOfHouseholds;

mt19937 random_mt;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);

		cout << "Number of times to roll the die: ";
		int rolls;
		cin >> rolls;

		cout << "Number of sides on this die: ";
		int sidesOnDice;
		cin >> sidesOnDice;

		RollDice(rolls, sidesOnDice);
	}
	else if (option == 2)
	{		
		option = 0;
		cout << "1. Print all states" << endl;
		cout << "2. Search for a state" << endl;
		cin >> option;

		if (option == 1)
		{
			readAndWrite();
			printMaps();
		}
		else if (option == 2)
		{
			readAndWrite();
			string stateSearch;
			cin >> stateSearch;
			searchMapsandPrint(stateSearch);
		}
	}
	return 0;
}


void readAndWrite()
{
	string state;
	string perCapitaIncome;
	string population;
	string medianHouseholdIncome;
	string numberOfHouseholds;

	ifstream file;
	file.open("states.csv");
	

	if (file.fail())
	{
		throw runtime_error("An error has occurred. File not loaded");
		exit(1);
	}
	else
	{
		if (file.is_open())
		{
			string dummyLine;
			getline(file, dummyLine);
			int count = 0;

			while (!file.eof())
			{
				getline(file, state, ',');
				censusState[count] = state;


				getline(file, perCapitaIncome, ',');				
				censusPerCapitaIncome[count] = stoi(perCapitaIncome);


				getline(file, population, ',');
				censusPopulation[count] = stoi(population);

				getline(file, medianHouseholdIncome, ',');
				censusHouseholdMedianIncome[count] = stoi(medianHouseholdIncome);

				getline(file, numberOfHouseholds);
				censusNumberOfHouseholds[count] = stoi(numberOfHouseholds);

				count = count + 1;
			}
		}
	}
	file.close();
}


void searchMapsandPrint(string findMe)
{
	int count = 0;

	for (int i = 0; i < 53; i++)
	{
		if (censusState[i] == findMe)
		{
			cout << censusState[i] << endl;
			cout << "Population: " << censusPopulation[i] << endl;
			cout << "Per Capita Income: " << censusPerCapitaIncome[i] << endl;
			cout << "Median Household Income: " << censusHouseholdMedianIncome[i] << endl;
			cout << "Number of Households: " << censusNumberOfHouseholds[i] << endl;
		}
		else
			count++;			
	}
	if (count == 53)
		cout << "No match found for " << findMe << endl;
	

}
//unordered
void printMaps()
{
	for (int i =0; i < 53; i++)
	{
		cout << censusState[i] << endl;
		cout << "Population: " << censusPopulation[i] << endl;
		cout << "Per Capita Income: " << censusPerCapitaIncome[i] << endl;
		cout << "Median Household Income: " << censusHouseholdMedianIncome[i] << endl;
		cout << "Number of Households: " << censusNumberOfHouseholds[i] << endl;
	}
}

void RollDice(int numberOfRolls, int numberOfSides)
{
	map<int, int> myDiceMap;

	for (int i = 1; i <= numberOfSides ;i++)
	{
		myDiceMap.insert(pair<int, int>(i, 0));	
	}

	for (int i = 0; i < numberOfRolls; i++)
	{
		int temp =  Random(1, numberOfSides);
		myDiceMap[temp]++;
	}
	
	auto iter = myDiceMap.begin();

	for (; iter != myDiceMap.end(); ++iter)
	{
		cout << iter->first << ": " << iter->second << endl;		
	}
}
