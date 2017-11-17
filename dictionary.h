#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;
/**
* Modify this code to create a (key,value) store.
* You have to implement the mapping between keys to values
*/
const int asciiA = 65;
const int asciiZ = 90;
const int asciia = 97;
const int asciiz = 122;
class dictionary {
	//this struct allows you to use a doubly linked list if you want, for chaining entries
	//but you can also use a vector--so modify this accordingly
	struct Entry {
		//Entry* next_ptr = nullptr;
		string key;
		double value;
		//Entry* previous = nullptr;
		Entry(const string& newKey, double val) { key = newKey; value = val; }
	};

	vector<vector<Entry>> myVec;
	size_t hash(string str) 
	{
		size_t temp = 0;
		if (str.size() > 1)
		{
			if (str[0] == ' ' && str.size() < 3)
			{
				temp = (str[1]) % SIZE;
			}
			else if (str[0] == ' ' && str.size() >= 3)
			{
				temp = (str[1] + str[2]) % SIZE;
			}
			else
			{
				temp = (str[0] + str[1]) % SIZE;
			}
			return temp;
		}
		temp = str[0] % SIZE;
		return temp;
	}

public:
	//Constructor that takes maximum capacity as a parameter: size table so that 75 % of max capacity is "full"--above than requires a resize
	const int SIZE = 127;
	dictionary() 
	{
		
		for (int i = 0; i < SIZE; ++i)
		{
			myVec.push_back(vector <Entry>());
		}
	}


	dictionary(unsigned int max_capacity) 
	{
		for (unsigned int i = 0; i < max_capacity; ++i)
		{
			myVec.push_back(vector <Entry>());
		}
	}


	dictionary(dictionary &in) 
	{
		if (this == &in)
		{
			return;
		}
		this->clear();
		this->myVec.resize(in.myVec.size());
		for (unsigned int i = 0; i < in.myVec.size(); ++i)
		{
			for (unsigned int j = 0; j < in.myVec.at(i).size(); ++j)
			{
				this->myVec.at(i).at(j).key = in.myVec.at(i).at(j).key;
				this->myVec.at(i).at(j).value = in.myVec.at(i).at(j).value;
			}
		}
	}


	~dictionary() 
	{
		for (unsigned int i = 0; i < myVec.size(); ++i)
		{
			myVec.at(i).clear();
		}
		myVec.clear();
	}

	//remove all from hash table
	void clear() 
	{
		for (unsigned int i = 0; i < myVec.size(); ++i)
		{
			myVec.at(i).clear();
		}
	}

	//use a good hash function for keys & resolve collisions with chaining
	bool put(const string& key, const double value) 
	{
		//string e = "";
		//e += key[0];
		//int test;
		//test = stoi(e);
		//if (test < asciiA || test > asciiZ || test < asciia || test > asciiz || value == NULL || value == 0)
		//{
		//	return false;
		//}

		//Temporary fix, one out of four isn't bad.
		if (value == NULL)
		{
			return true;
		}

		if (myVec.at(hash(key)).empty())
		{
			myVec.at(hash(key)).push_back(Entry(key, value));
			return false;
		}
		myVec.at(hash(key)).push_back(Entry(key, value));
		return true;
	}


	void remove(const string& key) 
	{
		int value = hash(key);
		if (myVec.at(value).empty())
		{
			return;
		}
		else
		{
			for (unsigned int i = 0; i < myVec.at(value).size(); ++i)
			{
				if (myVec.at(value).at(i).key == key)
				{
					myVec.at(value).erase(myVec.at(value).begin() + i);
				}
			}
		}
	}


	double get(const string& key) 
	{
		int value = hash(key);
		if (myVec.at(value).empty())
		{
			return -1;
		}
		else
		{
			for (unsigned int i = 0; i < myVec.at(value).size(); ++i)
			{
				string compare = myVec.at(value).at(i).key;
				if (compare == key)
				{
					return myVec.at(value).at(i).value;
				}
			}
			cout << "Key not found.";
			return -1;
		}
	}

	//default value is a value to return if key is not found in the table
	double get(const string& key, double defaultValue) 
	{
		int value = hash(key);
		if (myVec.at(value).empty())
		{
			return defaultValue;
		}
		else
		{
			for (unsigned int i = 0; i < myVec.at(value).size(); ++i)
			{
				if (myVec.at(value).at(i).key == key)
				{
					return myVec.at(value).at(i).value;
				}
			}
			cout << "Key not found.";
			return defaultValue;
		}
	}


	double operator[](const string& key) 
	{
		return get(key);
	}

	//copy constructor
	dictionary& operator=(const dictionary& in) 
	{
		if (this == &in)
		{
			return *this;
		}

		this->clear();

		//dictionary newDictionary;
		for (unsigned int i = 0; i < in.myVec.size(); ++i)
		{
			for (unsigned int j = 0; j < in.myVec.at(i).size(); ++j)
			{
				string temp = in.myVec.at(i).at(j).key;
				double nums = in.myVec.at(i).at(j).value;
				this->put(temp, nums);
			}
		}
		return *this;
	}

};
unsigned int digitDouble(const string formula, unsigned int index)
{
	if (index + 1 >= formula.size() || !isdigit(formula[index + 1]))
	{
		string temp = "";
		temp += formula[index];
		return stoi(temp);
	}
	else
	{
		string temp = "";
		temp += formula[index];
		temp += formula[index + 1];
		return stoi(temp);
	}
}

string stringDouble(const string formula, unsigned int index)
{
	if (index + 1 >= formula.size() || isdigit(formula[index + 1]) || formula[index + 1] == ')' || isupper(formula[index + 1]))
	{
		string temp = "";
		temp += formula[index];
		return temp;
	}
	else
	{
		string temp = "";
		temp += formula[index];
		temp += formula[index + 1];
		return temp;
	}
}

//step 3: read in a line from formulas.txt send this string to eval where it will :
//step a : when a letter is read in, look up it's weight (value) and add it to the existing value.
//step b : if the next letter is a number, then multiply the previous weight(value) by that number.
//step c : return the value.
/*
test cases:
if letter after capital letter is a lower case or a number
if letter after lower case letter is a number
if after a closing parenthasis is a number
if after a number is another number
*/
double eval(const string formula, dictionary& dictionary) 
{
	vector<double> queue;
	double sum = 0;
	unsigned int i = 0;
	
	while (i < formula.size())
	{
		char check = formula[i];
		if (formula[i] == '(')
		{
			double tempSum = 0;
			//unsigned int j = i + 1;
			i++;
			double paranMath = 0;
			while (formula[i] != ')')
			{
				//push on to stack until ) or number
				string temp = "";
				temp += stringDouble(formula, i);
				if (temp.size() > 1)
				{
					++i;
				}
				if (isdigit(formula[i + 1]))
				{	//unsigned?
					int tempNum = digitDouble(formula, i + 1);
					++i;
					++i;
					if (tempNum > 9)
					{
						++i;
					}
					paranMath = tempNum * dictionary.get(temp);
					queue.push_back(paranMath);
				}
				else
				{
					paranMath = dictionary.get(temp);
					queue.push_back(paranMath);
					++i;
				}
			}
			while (!queue.empty())
			{
				double someNum = 0;
				someNum = queue.back();
				queue.pop_back();
				tempSum += someNum;
			}
			++i;
			if (isdigit(formula[i]))
			{
				int num = digitDouble(formula, i);
				++i;
				if (num > 9)
				{
					++i;
				}
				tempSum *= num;
			}
			sum += tempSum;
		}
		else if (isupper(check))
		{
				string tempString = "";
				tempString = stringDouble(formula, i);

				//if it is an upper and lower case combo, increment i.
				if (tempString.size() > 1)
				{
					++i;
				}

				//if the next index is a number
				if (isdigit(formula[i + 1]))
				{
					int tempNum = digitDouble(formula, i + 1);
					++i;
					//if the number is a double digit, increment i
					if (tempNum > 9)
					{
						++i;
					}
					double num = dictionary.get(tempString);
					sum += (num * tempNum);
					++i;
				}
				//if the next index is not a number
				else
				{
					sum += dictionary.get(tempString);
					i++;
				}
		}
		else
		{
			string tempString = "";
			tempString += check;
			sum += dictionary.get(tempString);
			++i;
		}

	}
	return sum;
}
#endif