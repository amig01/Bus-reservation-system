 #include <iostream>
#include <string>
#include <ctype.h>
#include <ctime>

#define BUSES 10
#define SEATS 20
#define PASSENGERS 20
#define CITIES 10

using namespace std;

string cities[] = { "KHIVA" , "BUKHARA", "SAMARKAND", "NUKUS", "JIZAKH", "KASHKADARYA", "SURKHANDARYA", "ALAT", "VOBKENT", "GULISTAN"};

class Seat
{
private:
	string m_seatID;			// String Seats ID
	bool m_business;			// Status of Being Ordered
	int m_price;				// Integral Seat Price
	static int scounter;		// Variable to Initialize Seats IDs
public:
	Seat() : m_business(false), m_price(rand() % 51 + 50) { m_seatID = 'S' + (scounter % 20 < 9 ? to_string(0) : "") + to_string(scounter % 20 + 1), ++scounter; }
	const string& getSeatID() const { return m_seatID; }
	void setSeatBusiness(const bool& business) { m_business = business; }
	const bool& getSeatBusiness() const { return m_business; }
};
int Seat::scounter;

class Bus
{
private:
	string m_departure_city;	// String Departure City
	string m_arrival_city;		// String Arrival City
	string m_busID;				// String Bus ID
	Seat* m_bus_seats;			// Array of Seats in Bus
	static int bcounter;		// Variable to Initialize Bus IDs
public:
	Bus() : m_bus_seats(new Seat[SEATS]), m_departure_city("TASHKENT"), m_arrival_city(cities[rand() % CITIES])
		{ m_busID = 'B' + (bcounter < 9 ? to_string(0) : "") + to_string(bcounter + 1), ++bcounter; }
	~Bus() { delete[] m_bus_seats; }
	const string& getBusID() const { return m_busID; }
	Seat& getSeat(int index) const { return m_bus_seats[index]; }
	const string& getDepartureCity() const { return m_departure_city; }
	const string& getArrivalCity() const { return m_arrival_city; }
	int getFreeSeats() const 
	{
		int counter = 0;
		for (int i = 0; i < SEATS; ++i)
			if (m_bus_seats[i].getSeatBusiness() == false)
				++counter;
		return counter;
	}
	void showSeats()
	{
		cout << "\n__BUS " << m_busID << "__" << endl;
		for (int i = 0; i < SEATS; i++)
			cout << (m_bus_seats[i].getSeatBusiness() ? "SNA" : m_bus_seats[i].getSeatID()) << (i % 2 ? '\n' : '\t');
		cout << endl;
	}
};
int Bus::bcounter;

class Passenger
{
private:
	string m_passengerID;		// String Passenger ID
	string m_passenger_seatID;	// String Passenger Seat ID
	static int pcounter;		// Variable to Initialize Passenger IDs
public:
	Passenger() { m_passengerID = 'P' + (pcounter < 9 ? to_string(0) : "") + to_string(pcounter + 1), ++pcounter; }
	const string& getPassengerID() const { return m_passengerID; }
	const string& getPassengerSeatID() const { return m_passenger_seatID; }
	void makeOrder(const Bus& bus, Seat& seat) { m_passenger_seatID.assign(bus.getBusID() + seat.getSeatID()), seat.setSeatBusiness(true); }
	void cancelOrder(const Bus& bus, Seat& seat) { m_passenger_seatID.clear(), seat.setSeatBusiness(false); }
};
int Passenger::pcounter;

void showBusesTable(Bus* buses);

int main()
{
	srand(time(0));
	Bus* buses = new Bus[BUSES];
	Passenger* passengers = new Passenger[PASSENGERS];
	string input1, input2;

	for (size_t i = 0; i < 2; i++)
	{
		int index1, index2;

		cout << "1. MAKE NEW ORDER\n2. MODIFY ORDER\n3. CANCEL ORDER\n";
		cout << "4. SHOW LIST OF ORDERS\n5.SEARCH FOR ORDER\n6.MAKE PAYMENT\n0.EXIT\n" << endl;
		cout << "CHOOSE THE OPTION: ";
		cin >> input1;

		switch (input1[0])
		{
		case '1':
		{
			showBusesTable(buses);
			cout << "Please enter the ID of the bus: ";

		INPUT1:	cin >> input1;
			if (input1.size() != 3 || (input1[0] != 'B' || input1[1] < '0' || input1[1] > '1') || !isdigit(input1[2]))
			{
				cout << "Please enter valid ID: ";
				goto INPUT1;
			}
			index1 = (input1[1] - '0') + (input1[2] - '0');
			buses[index1].showSeats();

			cout << "Please enter the ID of the seat: ";
		INPUT2:	cin >> input2;
			if (input2.size() != 3 || (input2[0] != 'S' || input2[1] < '0' || input2[1] > '2') || !isdigit(input2[2]))
			{
				cout << "Please enter valid ID: ";
				goto INPUT2;
			}
			index2 = (input2[1] - '0') + (input2[2] - '0');
			passengers[0].makeOrder(buses[index1], buses[index1].getSeat(index2));

			break;
		}
		default:
			cout << "Not available option." << endl;
			break;
		}
	}

	delete[] passengers;
	delete[] buses;

 	return 0;
}

void showBusesTable(Bus* buses)
{
	cout << "\nBUSID\tDEPARTURE\tARRIVAL\t\tFREE SEATS\tTIME\t" << endl;
	for (int i = 0; i < BUSES; i++)
	{
		cout << buses[i].getBusID() << '\t' << buses[i].getDepartureCity() << '\t' << buses[i].getArrivalCity();
		buses[i].getArrivalCity().size() < 8 ? cout << "\t\t" : cout << '\t';
		cout << buses[i].getFreeSeats() << "\t\t" << buses[i].getBusID() << '\t' << endl;
	}
	cout << endl;
}