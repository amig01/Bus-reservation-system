#include <iostream>
#include <string>
using namespace std;

class Seat
{
protected:
	string m_seatID[20]; // String Seats ID
	static int scounter; // Variable to Initialize Seats IDs
public:
	Seat()
	{
		for (int i = 0; i < 20; i++)
			m_seatID[i] = 'S' + (scounter < 9 ? to_string(0) : "") + to_string(++scounter);
	}
	const string& operator [](int index) const { return m_seatID[index]; }
};
int Seat::scounter;

class Bus
{
protected:
	string m_busID;	 // String Bus ID
	Seat m_bus_seats; //Array of seats in bus
	static int bcounter; // Variable to Initialize Bus IDs
public:
	Bus() : m_busID('B' + (bcounter < 9 ? to_string(0) : "") + to_string(++bcounter)) {}
	string getBusID() const { return m_busID; }
	const string& getSeatID(int index) const { return m_bus_seats[index]; } 
};
int Bus::bcounter;

class Passenger
{
protected:
	string m_passengerID; // String Passenger ID
	static int pcounter;   // Variable to Initialize Passenger IDs
	string m_passenger_seatID; //String Passenger Seat ID
public:
	Passenger() : m_passengerID('P' + (pcounter < 9 ? to_string(0) : "") + to_string(++pcounter)) {}
	const string& getPassengerID() const { return m_passengerID; }
	void setPassengerSeatID(const string& ID) { m_passenger_seatID = ID; }
	const string& getPassengerSeatID() const { return m_passenger_seatID; }
};
int Passenger::pcounter;

int main()
{
	Bus* buses = new Bus[1];
	for (int i = 0; i < 1; i++)
	{
		cout << "\tBus " << buses[i].getBusID() << endl;
		for (int j = 0; j < 20; j++)
		{
			cout << "Seat " << buses[i].getSeatID(j);
			j % 2 == 0 ? cout << '\t' : cout << '\n';
		}
	}
	cout << endl;

	Passenger* passengers = new Passenger[1];
	for (int i = 0; i < 1; i++)
		cout << "Passenger " << passengers[i].getPassengerID() << endl;

	passengers[0].setPassengerSeatID(buses[0].getBusID() + buses[0].getSeatID(2));

	cout << "\n\nPassenger information:" << endl;
	cout << "Passenger's ID: " << passengers[0].getPassengerID() << endl;
	cout << "Passenger's seat ID: " << passengers[0].getPassengerSeatID() << endl;

	return 0;
}

//Add try catch
//Add menu
//Add header
