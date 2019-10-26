#include "Vote.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Vote::Vote(){}

Vote::Vote(string phrase)
{
	size_t pos = 0;
	
	string token;
	vector<string> data_vector;
	while ((pos = phrase.find(' ')) != string::npos)
	{
		token = phrase.substr(0, pos);
		phrase.erase(0, pos + 1);
		data_vector.push_back(token);
	}
	data_vector.push_back(phrase); // last remaining item, day information
	
	if (data_vector.size() == 3)
	{
		// correct case
		this->name = data_vector.at(0);
		if (data_vector.at(1) == "pick")
		{
			this->type = PICK;
			this->state = NORMAL;
		}
		else if (data_vector.at(1) == "delegate")
		{
			this->type = DELEGATE;
			this->state = UNDEFINED;
		}
		else
		{
			this->type = UNKNOWN;
			this->state = INVALID;
		}
		this->target = data_vector.at(2);
		
	}
	this->link = nullptr;
}

bool Vote::isValid()
{
	if (this->type == UNKNOWN || this->state == INVALID)
	{
		return false;
	}
	return true;
}

string Vote::typeStr()
{
	switch(this->type)
	{
		case PICK:
			return "PICK";
		case DELEGATE:
			return "DELEGATE";
		default:
			return "UNKNOWN";
	}
}

string Vote::stateStr()
{
	switch(this->state)
	{
		case NORMAL:
			return "NORMAL";
		case INVALID:
			return "INVALID";
		default:
			return "UNDEFINED";
	}
}

string Vote::display()
{
	return "name " + this->name + ", type " + this->typeStr() + ", target " + this->target + ", state " + this->stateStr();
}

void Vote::print()
{
	cout <<"name " << this->name << ", type " << this->typeStr() << ", target " << this->target << ", state " << this->stateStr() << endl;
}

// get last element of link chain, if that chain is circular dependency, then return any element which marked it's state as INVALID 
Vote* Vote::end()
{
	Vote* curr = this;
	while (curr != nullptr)
	{
		if (curr->getLink() == nullptr)
			return curr;
		if (curr->getState() == INVALID)
			return curr;
		curr = curr->getLink();
	}
	return nullptr;
}