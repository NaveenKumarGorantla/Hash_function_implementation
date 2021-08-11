#include <iostream>
#include <string>

#include <vector>
#include <algorithm>    // used for remove

#include <time.h>       // clock_t, clock, CLOCKS_PER_SEC
#include <math.h>

using namespace std;

template <class DT>
class HashTableVector
{
protected:
	vector< vector < DT > >* htable; // vector of vector hash table

public:
	HashTableVector<DT>(); // default constructor
	~HashTableVector(); // destructor

	void insert(string str); // insert a string into the right spot in the hash table
	int h(char a); // hash function - returns the key
	void displayTable(); // display the contents of htable
	void remove(string str); // removes a names from htable

};

int main()
{
	string tempName; // to store the name using cin

	HashTableVector<string>* h1 = new HashTableVector<string>(); // hash table object for vector

	char option; // to store the option from redirected input

	// START CLOCK
	clock_t start_time;
	start_time = clock();

	while (cin >> option)
	{
		switch (option) {
		case 'D':
		{
			// call display method
			h1->displayTable();
			break;
		}
		case 'I':
		{
			cin >> tempName;
			cout << "adding " << tempName << endl;
			// call insert method
			h1->insert(tempName);
			break;
		}
		case 'R':
		{
			cin >> tempName;
			cout << "removing " << tempName << endl;
			// call remove method
			h1->remove(tempName);
			break;
		}

		}
	}
		
	start_time = clock() - start_time;
	cout << "\n";
	cout << "time taken: " << (float)start_time / CLOCKS_PER_SEC << " seconds" << endl;

	delete h1;
	return 0;
}

template<class DT>
HashTableVector<DT>::HashTableVector()
{
	htable = new vector<vector<DT>>();
}

template<class DT>
HashTableVector<DT>::~HashTableVector()
{
	if (htable != NULL)
	{
		delete htable;
		htable = NULL;
	}
}

template<class DT>
void HashTableVector<DT>::insert(string str)
{
	int key = h(str[0]);
		if (key > htable->size())
		{
			htable->resize(key);
			vector<vector<string>>::iterator iter = htable->begin();
			advance(iter, key);
			vector<string> vector_strings;
			vector_strings.push_back(str);
			htable->insert(iter, vector_strings);
		}
		else
		{
			vector<vector<string>>::iterator iter = htable->begin();
			advance(iter, key);
			vector<string> vector_strings = *iter;

			if (find(vector_strings.begin(), vector_strings.end(), str) != vector_strings.end())
			{
				cout << "element to be added already existent: " << str << endl;
			}
			else
			{
				htable->erase(iter);
				iter = htable->begin();
				advance(iter, key);
				vector_strings.push_back(str);
				htable->insert(iter, vector_strings);
			}
		}
}

template<class DT>
int HashTableVector<DT>::h(char a)
{
	int key = a - 'A';
	return key;
}

template<class DT>
void HashTableVector<DT>::displayTable()
{
	int j = 0;
	vector <vector<string>>::iterator iter = htable->begin();
	while (iter != htable->end())
	{
		cout << to_string(j) + ":";
		if (iter->size() > 0)
		{
			cout << *iter->begin();
		}
		if (iter->size() > 1)
		{
			vector<string>::iterator string_iter = next(iter->begin());
			while (string_iter != iter->end())
			{
				cout << " => " << *string_iter;
				string_iter++;
			}
		}
		iter++;
		j = j + 1;
		cout << "\n";

	}

}

template<class DT>
void HashTableVector<DT>::remove(string str)
{
	bool found = false;
	vector<vector<string>>::iterator iter = htable->begin();
	while (iter != htable->end())
	{
		auto it = find(iter->begin(), iter->end(), str);
		if (it != iter->end())
		{
			iter->erase(it);
			found = true;
			break;
		}
		iter++;
	}
	if (found == false)
	{
		cout << "element to be removed not found: " << str << endl;
	}
}
