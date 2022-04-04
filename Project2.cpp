#include <iostream>
using namespace std;

int globalID;

class Bus
{
private:
	char seatID[10][10];
	double cost;
	int busID;

public:
	Bus()
	{
		busID = ++globalID;
	}
};

class Passenger
{
private:
	int passengerID;

public:
	Passenger()
	{
		passengerID = ++globalID;
	}
};

int main()
{
	Bus buses[10];

	return 0;
}