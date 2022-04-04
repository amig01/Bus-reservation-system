#include <iostream>
using namespace std;

int globalID;

class Bus
{
protected:
	char seatID[10][10];
	double cost;
	int busID;

public:
	Bus()
	{
		busID = ++globalID;
	}

	int getBusID()
	{
		return busID;
	}
};

class Passenger : protected Bus
{
private:
	int passengerID;

public:
	Passenger()
	{
		passengerID = ++globalID;
	}

	int getPassengerID()
	{
		return passengerID;
	}
};

int main()
{
	Bus buses[10];

	for (int i = 0; i < 10; i++)
	{
		cout << buses[i].getBusID() << endl;
	}

	globalID = 0;

	Passenger passenger[20];

	for (int i = 0; i < 10; i++)
	{
		cout << passenger[i].getPassengerID() << endl;
	}

	return 0;
}