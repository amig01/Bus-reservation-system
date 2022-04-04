#include <iostream>
using namespace std;

class Bus
{
protected:
	// char seatID[10][10]; // Number of Seats In One Bus
	// double cost;		 // Cost of Bus
	string strBusID;	 // String Bus ID
	static int bcounter; // Variable to Initialize IDs

public:
	Bus()
	{
		strBusID = to_string(++bcounter);
		strBusID = 'B' + strBusID;
	}

	string getBusID()
	{
		return strBusID;
	}
};

class Passenger
{
private:
	string strPassengerID; // String Passenger ID
	static int pcounter;   // Variable to Initialize IDs

public:
	Passenger()
	{
		strPassengerID = to_string(++pcounter);
		strPassengerID = 'P' + strPassengerID;
	}

	string getPassengerID()
	{
		return strPassengerID;
	}

	// void ConnectPassToBus(int client, int busn)
	// {
	// }
};

int Passenger::pcounter = 0;
int Bus::bcounter = 0;

int main()
{
	Bus buses[10];

	for (int i = 0; i < 10; i++)
	{
		cout << buses[i].getBusID() << " ";
	}

	cout << endl;

	Passenger passenger[10];

	for (int i = 0; i < 10; i++)
	{
		cout << passenger[i].getPassengerID() << " ";
	}

	return 0;
}