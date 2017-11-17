#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "dictionary.h"
#include <iostream>
using namespace std;
int main()
{
	string output = "results.txt";
	ofstream out;
	out.open(output);
	if (out.fail())
	{
		cerr << "Could not open file.  Please make sure that the file is closed and in the correct directory." << endl;
		system("PAUSE");
		exit(0);
	}
	double DIV = 1.5;
	//create two vectors for the tables
	vector<double> dubVec;
	vector<string> stVec;
	bool passValue = true;
	int numPass = 0;
	int numFail = 0;

	unsigned int testNums = 100;
	dictionary table;

	stVec.push_back("A");
	stVec.push_back("AB");
	stVec.push_back("G");
	stVec.push_back("Za");
	stVec.push_back("ZA");
	stVec.push_back("z");
	//push doubles into the vector
	for (unsigned int i = 0; i < stVec.size(); ++i)
	{
		dubVec.push_back(testNums);
		testNums = testNums / DIV;
	}

	//push entrys into the table
	cout << "Testing put function: ";
	out << "Testing put function: ";
	passValue = true;
	for (unsigned int i = 0; i < stVec.size(); ++i)
	{
		bool val = table.put(stVec[i], dubVec[i]);
		if (val == true)
		{
			passValue = false;
			numFail++;
			cout << "Collision at index " << i << endl;
			out << "Collision at index " << i << endl;
		}
	}
	cout << "Pass? " << passValue << endl;
	out << "Pass? " << passValue << endl;
	if (passValue == true)
		numPass++;


	//get the table data
	cout << "Test get function: ";
	out << "Test get function: ";
	passValue = true;
	for (unsigned int i = 0; i < stVec.size(); ++i)
	{
		cout << "Value: " << table.get(stVec[i]) << " ,";
		out << "Value: " << table.get(stVec[i]) << " ,";
		if (table.get(stVec[i]) != dubVec[i])
		{
			passValue = false;
			numFail++;
			cout << "Error: " << table.get(stVec[i]) << " " << "Expected: " << dubVec[i] << endl;
			out << "Error: " << table.get(stVec[i]) << " " << "Expected: " << dubVec[i] << endl;
		}
	}
	cout << endl;
	cout << "Did get pass? " << passValue << endl;
	out << endl;
	out << "Did get pass? " << passValue << endl;
	if (passValue == true)
		numPass++;

	//test remove function
	cout << "Test remove function: ";
	out << "Test remove function: ";
	passValue = true;
	table.remove(stVec[0]);
	if (table.get(stVec[0]) != -1)
	{
		passValue = false;
		numFail++;
		cout << "Remove failed." << endl;
		out << "Remove failed." << endl;
	}
	else
	{
		stVec.erase(stVec.begin());
		dubVec.erase(dubVec.begin());
	}
	table.remove(stVec[3]);
	cout << "Pass? " << passValue << endl;
	out << "Pass? " << passValue << endl;
	if (passValue == true)
		numPass++;

	cout << "Test remove function at non zero index: ";
	out << "Test remove function at non zero index: ";
	passValue = true;
	//Test if the data was removed
	if (table.get(stVec[3]) != -1)
	{
		passValue = false;
		numFail++;
		cout << "Remove failed." << endl;
		out << "Remove failed." << endl;
	}
	else
	{
		stVec.erase(stVec.begin() + 3);
		dubVec.erase(dubVec.begin() + 3);
	}
	cout << "Pass? " << passValue << endl;
	out << "Pass? " << passValue << endl;
	if (passValue == true)
		numPass++;

	//Test copy constructor and = operator
	cout << "test copy constructor to empty table: ";
	out << "test copy constructor to empty table: ";
	passValue = true;
	dictionary copyTable;
	copyTable = table;

	//get the table data
	for (unsigned int i = 0; i < stVec.size(); ++i)
	{
		cout << "Value: " << copyTable.get(stVec[i]) << " ,";
		out << "Value: " << copyTable.get(stVec[i]) << " ,";
		if (copyTable.get(stVec[i]) != table.get(stVec[i]))
		{
			passValue = false;
			numFail++;
			cout << "Copy error: " << copyTable.get(stVec[i]) << " " << "Expected: " << table.get(stVec[i]) << endl;
			out << "Copy error: " << copyTable.get(stVec[i]) << " " << "Expected: " << table.get(stVec[i]) << endl;
		}
	}
	cout << endl;
	cout << "Copy constructor pass? " << passValue << endl;
	out << "Copy constructor pass? " << passValue << endl;
	if (passValue == true)
		numPass++;

	//More copy constructor testing
	cout << "Add one value and copy to an existing table that has values: ";
	out << "Add one value and copy to an existing table that has values: ";
	passValue = true;
	bool val = copyTable.put("Ce", .0035);
	if (val == true)
	{
		passValue = false;
		numFail++;
		cout << "Collision." << endl;
		out << "Collision." << endl;
	}

	//more copy constructor testing
	table = copyTable;
	cout << "Key: " << "Ce, " << "Value: " << copyTable.get("Ce") << endl;
	out << "Key: " << "Ce, " << "Value: " << copyTable.get("Ce") << endl;
	stVec.push_back("Ce");
	dubVec.push_back(.0035);
	cout << "Copying values: ";
	out << "Copying values: ";
	for (unsigned int i = 0; i < stVec.size(); ++i)
	{
		cout << table.get(stVec[i]) << " ,";
		if (copyTable.get("Ce") != table.get("Ce"))
		{
			passValue = false;
			numFail++;
			cout << "Copy error: " << table.get("Ce") << " " << "Expected: " << copyTable.get("Ce") << endl;
			out << "Copy error: " << table.get("Ce") << " " << "Expected: " << copyTable.get("Ce") << endl;
		}
	}
	cout << endl;
	cout << "Copy constructor pass? " << passValue << endl;
	out << endl;
	out << "Copy constructor pass? " << passValue << endl;
	if (passValue == true)
		numPass++;


	//Test clear function
	cout << "Testing clear function: ";
	out << "Testing clear function: ";
	passValue = true;
	table.clear();
	copyTable = table;
	for (unsigned int i = 0; i < stVec.size(); ++i)
	{
		if (table.get(stVec[i]) != -1)
		{
			passValue = false;
			numFail++;
			cout << "Remove failed at index " << i << endl;
			out << "Remove failed at index " << i << endl;
		}
	}
	cout << "Pass? " << passValue << endl;
	out << "Pass? " << passValue << endl;
	if (passValue == true)
		numPass++;

	//More copy constructor testing
	cout << "Testing copy constructor on an empty list: ";
	out << "Testing copy constructor on an empty list: ";
	passValue = true;
	for (unsigned int i = 0; i < stVec.size(); ++i)
	{
		if (copyTable.get(stVec[i]) != -1)
		{
			passValue = false;
			numFail++;
			cout << "Remove failed at index " << i << endl;
			out << "Remove failed at index " << i << endl;
		}
	}
	cout << "Pass? " << passValue << endl;
	out << "Pass? " << passValue << endl;
	if (passValue == true)
		numPass++;
	cout << endl << endl << "Number of passes = " << numPass << "." << endl << "Number of failures = " << numFail << "." << endl;
	out << endl << endl << "Number of passes = " << numPass << "." << endl << "Number of failures = " << numFail << "." << endl << endl;
	out << "Results from the eval function: " << endl;

	//Begin working on atomic masses
	vector<double> expectedValues;
	expectedValues.push_back(46.069);
	expectedValues.push_back(174.449);
	expectedValues.push_back(98.078);
	expectedValues.push_back(84.006);
	expectedValues.push_back(664.711);
	expectedValues.push_back(169.992);
	expectedValues.push_back(129.62);
	expectedValues.push_back(62.112);
	expectedValues.push_back(60.096);
	expectedValues.push_back(265.897);
	expectedValues.push_back(182.701);
	expectedValues.push_back(353.177);
	expectedValues.push_back(183.614);
	expectedValues.push_back(121.136);
	expectedValues.push_back(89.094);
	expectedValues.push_back(260.38);
	expectedValues.push_back(705.684);
	expectedValues.push_back(162.838);
	expectedValues.push_back(583.138);
	expectedValues.push_back(633.305);
	dictionary dictionary;
	string formulas = "formulas.txt";
	string mass = "atomic.csv";
	ifstream in;
	string name;
	string key;
	string number;
	string value;
	double weight;
	in.open(mass);
	bool test;
	int collisions = 0;
	if (in.fail())
	{
		cerr << "Could not open file.  Please make sure that the file is closed and in the correct directory." << endl;
		system("PAUSE");
		exit(0);
	}
	getline(in, name, ',');
	getline(in, key, ',');
	getline(in, number, ',');
	getline(in, value);
	while (!in.eof())
	{
		getline(in, name, ',');
		getline(in, key, ',');
		key.erase(remove(key.begin(), key.end(), ' '), key.end());
		getline(in, number, ',');
		getline(in, value);
		weight = stod(value);
		if (!key.empty())
		{
			test = dictionary.put(key, weight);
			if (test == true)
			{
				++collisions;
			}
		}
	}
	cout << "Number of collisions: " << collisions << endl;
	in.close();

	in.open(formulas);
	if (in.fail())
	{
		cerr << "Could not open file.  Please make sure that the file is closed and in the correct directory." << endl;
		system("PAUSE");
		exit(0);
	}
	int i = 0;
	while (i < expectedValues.size())
	{
		getline(in, name);
		weight = eval(name, dictionary);
		out << name << '\t' << " Eval function: " << weight << " Expected: " << expectedValues[i] << endl;
		++i;
	}
	out.close();
	in.close();
	system("PAUSE");
}