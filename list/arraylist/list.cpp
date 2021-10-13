#include <iomanip>
#include "list.h"

using namespace std;

static const int	INITIAL_SIZE{4};

struct PrivateData
{
	PrivateData(int arraySize, int nItems) :
		listArray{new char[INITIAL_SIZE]},
		arraySize{arraySize},
		nItems{nItems}
	{
	}

	~PrivateData()
	{
		delete[] listArray;
	}

	static PrivateData*	getPrivateData(const List& list)
	{
		return static_cast<PrivateData*>(list.privateData);
	}

	char*	listArray;
	int		arraySize;
	int		nItems;
};

List::List(void) :
	privateData{new PrivateData{INITIAL_SIZE, 0}}
{
}

List::~List(void)
{
	delete static_cast<PrivateData*>(privateData);
}

static void expandIfNeeded(List& list)
{
	PrivateData*	pd{PrivateData::getPrivateData(list)};
	int				newArraySize;
	char*			newArray;

	if (pd->nItems >= pd->arraySize) {
		newArraySize = pd->arraySize + INITIAL_SIZE;
		newArray = new char[newArraySize];
		for (int i = 0; i < pd->arraySize; i++)
			newArray[i] = pd->listArray[i];
		delete[] pd->listArray;
		pd->listArray = newArray;
		pd->arraySize = newArraySize;
		}
}

void List::addFirst(char ch)
{
	PrivateData*	pd{PrivateData::getPrivateData(*this)};

	expandIfNeeded(*this);
	for (int i{pd->nItems}; i > 0; i--)
		pd->listArray[i] = pd->listArray[i - 1];
	pd->listArray[0] = ch;
	pd->nItems++;
}

static bool findIndex(const List& list, char ch, int& index)
{
	PrivateData*	pd{PrivateData::getPrivateData(list)};

	for (int i{0}; i < pd->nItems; i++)
		if (pd->listArray[i] == ch) {
			index = i;
			return true;
			}
	return false;
}

bool List::addBefore(char before, char ch)
{
	PrivateData*	pd{PrivateData::getPrivateData(*this)};
	int				index;
	
	if (findIndex(*this, before, index)) {
		expandIfNeeded(*this);
		for (int i{pd->nItems - 1}; i >= index; i--)
			pd->listArray[i + 1] = pd->listArray[i];
		pd->listArray[index] = ch;
		pd->nItems++;
		return true;
		}
	else
		return false;
}

void List::addLast(char ch)
{
	PrivateData*	pd{PrivateData::getPrivateData(*this)};

	expandIfNeeded(*this);
	pd->listArray[pd->nItems++] = ch;
}

bool List::find(char ch) const
{
	int		index;

	return findIndex(*this, ch, index);
}

bool List::remove(char ch)
{
	PrivateData*	pd{PrivateData::getPrivateData(*this)};
	int				index;

	if (findIndex(*this, ch, index)) {
		for (int i = index; i < pd->nItems - 1; i++)
			pd->listArray[i] = pd->listArray[i + 1];
		pd->nItems--;
		return true;
		}
	else
		return false;
}

int List::length(void) const
{
	PrivateData*	pd{PrivateData::getPrivateData(*this)};

	return pd->nItems;
}

char& List::operator[](int index)
{
	PrivateData*	pd{PrivateData::getPrivateData(*this)};

	if (index < 0 || index >= pd->nItems)
		throw "index out of bounds";

	return pd->listArray[index];
}

ostream& operator<<(ostream& out, const List& list)
{
	PrivateData*	pd{PrivateData::getPrivateData(list)};
	bool			first{true};

	out << "List: (" << setw(2) << list.length() << " elements) [";
	for (int i{0}; i < pd->nItems; i++) {
		if (first)
			first = false;
		else
			out << ", ";
		out << pd->listArray[i];
		}
	out << "]" << endl;
	return out;
}
