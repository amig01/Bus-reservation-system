#include <iostream>
using namespace std;

class Bus
{
protected:
	char seatID[10][10]; // Number of Seats In One Bus
	double cost;		 // Cost of Bus
	string strBusID;	 // String Bus ID
	static int bcounter; // Variable to Initialize IDs

public:
	Bus()
	{
		strBusID = to_string(++bcounter);
		strBusID = 'B' + strBusID;
	}
};

class Passenger : protected Bus
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

	void ConnectPassToBus(int client, int busn)
	{
	}
};

int Passenger::pcounter = 0;
int Bus::bcounter = 0;

int main()
{
	Bus buses[10];

	Passenger passenger[5];

	return 0;
}