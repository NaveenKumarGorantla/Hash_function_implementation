#include <iostream>
#include <string>

#include <list>
#include <algorithm>    // used for remove

#include <time.h>       // clock_t, clock, CLOCKS_PER_SEC
#include <math.h>

using namespace std;

template <class DT>
class HashTableList
{
protected:
	list< list < DT > >* htable; // list of list hash table

public:
	HashTableList<DT>(); // default constructor
	~HashTableList(); // destructor

	void insert(string str); // insert a string into the right spot in the hash table
	int h(char a); // hash function - returns the key
	void displayTable(); // display the contents of htable
	void remove(string str); // removes a names from htable

};


int main()
{
	string tempName; // to store the name using cin

	HashTableList<string>* h2 = new HashTableList<string>(); // hash table object for vector

	char option; // to store the option from redirected input

	clock_t start_time;
	 //START CLOCK
	start_time = clock();
	
	while (cin >> option)
	{
		switch (option) {
		case 'D':
		{
			h2->displayTable();
			break;
		}
		case 'I':
		{
			cin >> tempName;
			cout << "adding " << tempName << endl;
			h2->insert(tempName);
			break;
		}
		case 'R':
		{
			cin >> tempName;
			cout << "removing " << tempName << endl;
			h2->remove(tempName);
			break;
		}
		} // switch case
	} // while

	 //END CLOCK
	start_time = clock() - start_time;
	cout << "\n";
	cout << "time taken: " << (float)start_time / CLOCKS_PER_SEC << " seconds" << endl;
	delete h2;
	return 0;
}

template<class DT>
HashTableList<DT>::HashTableList()
{
	htable = new list < list<DT>>(15);
}

template<class DT>
HashTableList<DT>::~HashTableList()
{
	if (htable != NULL)
	{
		delete htable;
		htable = NULL;
	}
}

template<class DT>
void HashTableList<DT>::insert(string str)
{
	int key = h(str[0]);
	if (key > htable->size())
	{
		htable->resize(key);
		list<list<string>>::iterator iter = htable->begin();
		advance(iter, key);
		list<string> list_strings;
		list_strings.push_back(str);
		htable->insert(iter, list_strings);
	}
	else
	{
		list<list<string>>::iterator iter = htable->begin();
		advance(iter, key);
		list<string> list_strings = *iter;

		if (find(list_strings.begin(), list_strings.end(), str) != list_strings.end())
		{
			cout << "element to be added already existent: " << str << endl;			
		}
		else
		{
			htable->erase(iter);
			iter = htable->begin();
			advance(iter, key);
			list_strings.push_back(str);
			htable->insert(iter, list_strings);
		}
	}
}	

template<class DT>
int HashTableList<DT>::h(char a)
{
	int key = a - 'A';
	return key;
}

template<class DT>
void HashTableList<DT>::displayTable()
{
	int j = 0;
	list <list<string>>::iterator iter = htable->begin();
	while (iter != htable->end())
	{
		cout << to_string(j) + ":";	
		if (iter->size() > 0)
		{
			cout << *iter->begin();
		}
		if (iter->size() > 1)
		{
			list<string>::iterator string_iter = next(iter->begin());
			while (string_iter != iter->end())
			{
				cout << " => " << *string_iter ;
				string_iter++ ;
			}
		}
		iter++;
		j = j + 1;
		cout << "\n";
			
	}

}

template<class DT>
void HashTableList<DT>::remove(string str)
{
	bool found = false;
	list<list<string>>::iterator iter = htable->begin();
	while (iter != htable->end())
	{
		
		auto it = find( iter->begin(), iter->end(), str);
		if (it != iter->end())
		{
			iter->remove(str);
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
