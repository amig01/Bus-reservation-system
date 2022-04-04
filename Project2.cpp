#include <iostream>
using namespace std;

class Bus
{
protected:
	string strBusID;	 // String Bus ID
	static int bcounter; // Variable to Initialize IDs

public:
	Bus()
	{
		strBusID = 'B' + to_string(++bcounter);
	}

	string getBusID() { return strBusID; }
};

class Passenger
{
protected:
	string strPassengerID; // String Passenger ID
	static int pcounter;   // Variable to Initialize IDs

public:
	Passenger()
	{
		strPassengerID = 'P' + to_string(++pcounter);
	}

	string getPassengerID() { return strPassengerID; }
};

class Seat
{
protected:
	string seatID[10][6];

public:
	Seat()
	{
		for (int r = 1; r < 10; r++)
		{
			for (int c = 1; c <= 5; c++)
			{
				seatID[r][c] = 'S' + to_string(r) + to_string(c);
			}
		}
	}
};

int Passenger::pcounter = 0;
int Bus::bcounter = 0;

int main()
{
	/*Bus buses[10];

	for (int i = 0; i < 10; i++)
	{
		cout << buses[i].getBusID() << " ";
	}

	cout << endl;

	Passenger passenger[10];

	for (int i = 0; i < 10; i++)
	{
		cout << passenger[i].getPassengerID() << " ";
	}*/

	Seat seats;

	return 0;
}