// LRU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>
using namespace std;


class LRUBuffer 
{
public:
	LRUBuffer(int ibufsize)
	{
		bufsize = ibufsize;
		capacity = ibufsize;
	}

	string getByKey(string key){
		for (auto i  = keylist.begin(); i != keylist.end(); i++) {
			//if found in cache

			//debug
			cout << "key = " << key << " *i = " <<  *i << endl;
			if (*i == key) {
				//return result
				auto keypair = keyvaluemap.find(key);
				string result = "GOT " + keypair->second;
				//erase from current location and insert at end
				keylist.erase(i);
				keylist.push_back(key);
				return result;
			}
		}
		//else return NOTFOUND
		return "NOTFOUND";
	}

	void setByKey(string key, string value){
		//if key not exist before
		for (auto i = keylist.begin(); i != keylist.end(); i++) {
			//if found, remove it from current location and insert at end

				if (*i == key){
					//debug
					//	cout << "set a key which exist before " << endl;
				keylist.erase(i);
				keylist.push_back(key);

				//update a keypair by erase existing one and insert a new one
				keyvaluemap.erase(key);
				keyvaluemap.insert(make_pair(key, value));
				return;
			}
		}
			//else not exist before, insert at end
				//debug
				//cout << "set a key not exist before" << endl;

				keylist.push_back(key);
				if (capacity > 0)
					capacity--;
				else {
					keylist.erase(keylist.begin());
				}

				//insert a new keypair
				keyvaluemap.insert(make_pair(key, value));
				return;
	}

	~LRUBuffer(){
	}

private:
//	string  *keys;
//	string  *values;
	int bufsize;
	int capacity; //current remaining capacity, if it is > 0, no need to remove existing item from oldest 
	map<string, string> keyvaluemap;
	list<string> keylist;

};

int _tmain(int argc, _TCHAR* argv[])
{
	string input;
	string output;
	string verb;
	string key;
	string value;
	int bufsize;
	LRUBuffer *lruBuffer = NULL;

	while (true) {
		getline(cin, input);
		istringstream iss(input);
		if (iss)
			iss >> verb;
		if (iss)
			iss >> key;
		value = "";
		if (iss)
			iss >> value;
		if (_stricmp(verb.c_str(), "size") == 0) {
			bufsize = stoi(key);
			if (bufsize <= 0) {
				output = "ERROR";
				cout << output << endl;
				continue;
			}

			//for any size >= 1, we clear the existing buffer and resize the buffer
			if (lruBuffer != NULL)
				delete lruBuffer;  // to avoid memory leak
			lruBuffer = new LRUBuffer(bufsize);
			output = "SIZE OK";
			cout << output << endl;
			continue;

		}
		else if (_stricmp(verb.c_str(), "set") == 0) {
			if (value == "") {
				output = "ERROR";
				cout << output << endl;
				continue;
			}

			lruBuffer->setByKey(key, value);
			output = "SET OK";
			cout << output << endl;
			continue;

		}
		else if (_stricmp(verb.c_str(), "get") == 0) {
			if (value != "") {
				output = "ERROR";
				cout << output << endl;
				continue;

			}
			output = lruBuffer->getByKey(key);
			cout << output << endl;
			continue;


		}
		else if (_stricmp(verb.c_str(), "exit") == 0) {
			delete lruBuffer;
			return 0;
		}
		else {
			output = "ERROR";
			cout << output << endl;
			continue;
		}

		cout << output << endl;

	}
	return 0;
}

