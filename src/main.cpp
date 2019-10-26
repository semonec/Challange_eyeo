#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Vote.h"
#include <map>
#include <algorithm>

#define DEBUG true


using namespace std;

void initDataFromFile(map<string, Vote> *items)
{
	// for the test, read data from file
	string testInput = "test.txt";
	ifstream openFile(testInput.data());
	if( openFile.is_open() )
	{
		string line;
		while(getline(openFile, line))
		{
			Vote v = Vote(line);
			items->insert(make_pair(v.getName(), v));
		}
		openFile.close();
	} else
	{
		cout << "cannot read test file"; 
	}
}

void initDataFromCIN(map<string, Vote> *items)
{
	string line;
	while(getline(cin, line) && line.length())
	{
		Vote v = Vote(line);
		items->insert(make_pair(v.getName(), v));
	}
}

void assignPick(map<string, int>* picks, string target)
{

	map<string,int>::iterator it = picks->find(target);
	if (it != picks->end())
	{
		it->second++;
	}
	else
	{
		picks->insert(make_pair(target, 1));
	}
}

void assignDelegate(map<string, Vote>* votes, Vote* vote)
{
	//picks
	string target = vote->getTarget();
	map<string, Vote>::iterator it = votes->find(target);
	if (it != votes->end())
	{
		vote->setLink(&it->second);
	}
	else
	{
		cerr << "Cannot find deleate target: "<< target << endl;
		vote->setState(INVALID);
	}
}

// check circular dependency
void checkDelegate(Vote* vote)
{
	bool isCircular = false;
	Vote* curr = vote;
	Vote* next = curr->getLink();
	// if curr element will link to invalid element, then curr element will be marked as INVALID.
	if (next != nullptr && next->getState() == INVALID)
	{
		curr->setState(INVALID);
		return;
	}
	// check circular dependency
	while(curr != nullptr && next != nullptr)
	{
		curr = curr->getLink();
		next = (next->getLink() != nullptr) ? next->getLink()->getLink() : nullptr;
		if (curr == next && curr != nullptr)
		{
			isCircular = true;
			break;
		}
	}
	// In case of circular dependency, mark all the elements in the link's state as INVALID
	if (isCircular)
	{
		vote->setState(INVALID);
	}
}

int main(int argc, char* argv[])
{
	
	map<string, Vote> items;
	map<string, int> picks;
	int invalid_cnt = 0;

	if (DEBUG) // read initial data from file
	{
		initDataFromFile(&items);
	}
	else
	{
		initDataFromCIN(&items);
	}
    for (auto &item: items)
	{
		if (item.second.getType() == DELEGATE)
		{
			assignDelegate(&items, &item.second);
			checkDelegate(&item.second);
		}
	}

	for (auto &item: items)
	{
		Vote* end = item.second.end();
		if (end == nullptr)
		{
			continue;
		}
		switch (end->getType())
		{
			case PICK:
				assignPick(&picks, end->getTarget());
				item.second.setState(NORMAL);
				break;
			case DELEGATE:
				if (end->getState() == INVALID)
				{
					item.second.setState(INVALID);
					invalid_cnt++;
				}
				else // delegate that isn't exist voter, so will be treated as INVALID
				{
					item.second.setState(INVALID);
					invalid_cnt++;
				}
				break;
			default:
				// illegal vote type, not a pick and not a delegate, so will be treated as INVALID
				item.second.setState(INVALID);
		}
	}

	// sort picks, map is hard to sort, so convert it as vector, and then sort
	vector<std::pair<string, int>> pairs;
	for (auto itr = picks.begin(); itr != picks.end(); ++itr)
	{
		pairs.push_back(*itr);
	}

	sort(pairs.begin(), 
		 pairs.end(), 
		 [=](pair<string, int>& a, pair<string, int>& b) -> bool { return a.second > b.second; }
	);
	
	for (auto &pair: pairs)
	{
		cout << pair.second << " " << pair.first << endl;
	}
	cout << "invalid " << invalid_cnt << endl;
	return 0;
}