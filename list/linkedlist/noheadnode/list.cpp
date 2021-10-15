#include <iomanip>
#include "list.h"

using namespace std;

struct PrivateData
{
	PrivateData() : first{nullptr} {}

	static PrivateData*	getPrivateData(const List& list)
	{
		return static_cast<PrivateData*>(list.privateData);
	}

	struct Node
	{
		Node(char ch, Node* next) : ch{ch}, next{next} { }

		char	ch;
		Node*	next;
	};

	Node*	first;
};

List::List(void) :
	privateData{new PrivateData()}
{
}

List::~List(void)
{
	empty();
	delete static_cast<PrivateData*>(privateData);
}

void List::addFirst(char ch)
{
	PrivateData*	pd{PrivateData::getPrivateData(*this)};

	pd->first = new PrivateData::Node{ch, pd->first};
}

static bool findPrev(const List& list, char ch, PrivateData::Node*& prevRet)
{
	PrivateData*		pd{PrivateData::getPrivateData(list)};

	PrivateData::Node*	node{pd->first};
	PrivateData::Node*	prev{nullptr};

	while (node) {
		if (node->ch == ch) {
			prevRet = prev;
			return true;
			}
		prev = node;
		node = node->next;
	}
	return false;
}

bool List::addBefore(char before, char ch)
{
	PrivateData*		pd{PrivateData::getPrivateData(*this)};

	PrivateData::Node*	prev;
	PrivateData::Node*	node;

	if (findPrev(*this, before, prev)) {
		node = new PrivateData::Node(ch, nullptr);
		if (prev == nullptr) {
			node->next = pd->first;
			pd->first = node;
			}
		else {
			node->next = prev->next;
			prev->next = node;
			}
		return true;
		}
	else
		return false;
}

void List::addLast(char ch)
{
	PrivateData*		pd{PrivateData::getPrivateData(*this)};

	PrivateData::Node*	node{pd->first};
	PrivateData::Node*	lastNode{nullptr};

	while (node) {
		lastNode = node;
		node = node->next;
		}
	lastNode->next = new PrivateData::Node(ch, nullptr);
}

bool List::find(char ch) const
{
	PrivateData::Node*	node;

	return findPrev(*this, ch, node);
}

bool List::remove(char ch)
{
	PrivateData*		pd{PrivateData::getPrivateData(*this)};

	PrivateData::Node*	prev;
	PrivateData::Node*	node;

	if (findPrev(*this, ch, prev)) {
		if (prev == nullptr) {
			node = pd->first;
			pd->first = node->next;
			}
		else {
			node = prev->next;
			prev->next = node->next;
			}
		delete node;
		return true;
		}		
	else
		return false;
}

void List::empty()
{
	PrivateData*		pd{PrivateData::getPrivateData(*this)};

	PrivateData::Node*	node{pd->first};
	PrivateData::Node*	nextNode;

	while (node) {
		nextNode = node->next;
		delete node;
		node = nextNode;
		}
	pd->first = nullptr;
}

int List::length(void) const
{
	PrivateData*		pd{PrivateData::getPrivateData(*this)};

	PrivateData::Node*	node{pd->first};
	int					lgth{0};

	while (node) {
		lgth++;
		node = node->next;
		}
	return lgth;
}

char& List::operator[](int index)
{
	PrivateData*	pd{PrivateData::getPrivateData(*this)};

	static char*	outOfRangeMsg{"index out of range"};

	PrivateData::Node*	node{pd->first};

	if (index < 0)
		throw outOfRangeMsg;
	for (int i = 0; i < index; i++) {
		if (node == nullptr)
			throw outOfRangeMsg;
		node = node->next;
		}
	return node->ch;
}

ostream& operator<<(ostream& out, const List& list)
{
	PrivateData*		pd{PrivateData::getPrivateData(list)};

	PrivateData::Node*	node{pd->first};
	bool				first{true};

	out << "List: (" << setw(2) << list.length() << " elements) [";
	while (node) {
		if (first)
			first = false;
		else
			out << ", ";
		out << node->ch;
		node = node->next;
		}
	out << "]" << endl;
	return out;
}
