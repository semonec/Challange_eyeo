#include <string>
using namespace std;

enum VoteType
{
	PICK,
	DELEGATE,
	UNKNOWN
};


enum VoteState
{
	NORMAL,
	INVALID,
	UNDEFINED
};

class Vote
{
public:
	Vote();
	Vote(string phrase);
	bool isValid();
	string display();
	void print();
	string getName() { return this->name; }
	VoteType getType() { return this->type; }
	VoteState getState() { return this->state; }
	void setState(VoteState newState) { this->state = newState; }
	void setLink(Vote* vote) { this->link = vote; }
	Vote* getLink() { return this->link; }
	string getTarget() { return this->target; }
	string typeStr();
	string stateStr();
	Vote* end();
private:
	string name;
	VoteType type;
	string target;
	VoteState state;
	Vote* link;
};
