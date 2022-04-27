#include <string>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

const int BUSES = 10;
const int SEATS = 20;
const int PASSENGERS = 200;
const int CITIES = 10;

const string cities[CITIES] = { "KHIVA", "BUKHARA", "SAMARKAND", "NUKUS", "JIZAKH", "KASHKADARYA", "SURKHANDARYA", "ALAT", "VOBKENT", "GULISTAN" };

void putEnters(int number = 1)
{
	for (int i = 0; i < number; i++)
		cout << endl;
}

int inputUpTo(int max_value)
{
	int input;
	cin >> input;
	while (cin.fail() || input > max_value || input < 0)
	{
		cout << "PLEASE ENTER VALID VALUE: ";
		cin.clear();
		cin.ignore(32767, '\n');
		cin >> input;
	}
	return input;
}

class Seat
{
private:
	const string m_seatID;			// String Seats ID
	bool m_business;				// Status of Being Ordered
	static int scounter;			// Variable to Initialize Seats IDs
public:
	Seat() : m_business(false), m_seatID('S' + (scounter < 9 ? to_string(0) : "") + to_string(++(scounter %= 20))) {  }
	const string& getSeatID() const { return m_seatID; }
	void setBusiness(bool business) { m_business = business; }
	const bool getBusiness() const { return m_business; }
};
int Seat::scounter;

class Bus
{
protected:
	const string m_busID;			// String Bus ID
	const string m_departure_city;	// String Departure City
	const string m_arrival_city;	// String Arrival City
	Seat* m_bus_seats;				// Array of Seats in Bus
	const int m_price;				// Integral Seat Price
	static int bcounter;			// Variable to Initialize Bus IDs
public:
	Bus() : m_busID('B' + (bcounter < 9 ? to_string(0) : "") + to_string(++bcounter)), m_departure_city("TASHKENT"), m_arrival_city(cities[rand() % CITIES]), m_bus_seats(new Seat[SEATS]), m_price(rand() % 51 + 50) {  }
	~Bus() { delete[] m_bus_seats; }
	const string& getDepartureCity() const { return m_departure_city; }
	const string& getArrivalCity() const { return m_arrival_city; }
	const string& getBusID() const { return m_busID; }
	Seat& getSeat(int index) { return m_bus_seats[index]; }
	int getPrice() const { return m_price; }
	void showSeatsTable();
	friend void showBusesTable(Bus buses[]);
};
int Bus::bcounter;

void Bus::showSeatsTable()
{
	cout << "BUS ID: " << m_busID << endl;
	for (int i = 0; i < SEATS; i++)
	{
		cout << m_bus_seats[i].getSeatID() << (m_bus_seats[i].getBusiness() ? "(busy)" : "(free)") << '\t';
		if (i % 2 && i)
			cout << endl;
	}
	putEnters();
}

void showBusesTable(Bus buses[])
{
	cout << "BUS ID\tDEPARTURE\tARRIVAL\t\tPRICE\tTIME\t" << endl;
	for (int i = 0; i < BUSES; i++)
	{
		cout << buses[i].m_busID << '\t' << buses[i].m_departure_city << '\t' << buses[i].m_arrival_city;
		buses[i].m_arrival_city.size() < 8 ? cout << "\t\t" : cout << '\t';
		cout << buses[i].m_price << "$\t" << buses[i].m_busID << endl;
	}
	putEnters();
}

class Passenger
{
private:
	const string m_passengerID;		// String Passenger ID
	string m_ticketID;				// String Passenger Ticket ID
	static int pcounter;			// Variable to Initialize Passenger IDs
public:
	Passenger() : m_passengerID('P' + (pcounter < 9 ? to_string(0) : "") + to_string(++pcounter)) { }
	const string& getPassengerID() const { return m_passengerID; }
	const string& getTicketID() const { return m_ticketID; }
	void makeOrder(Bus buses[]);
	void currentOrder(Bus buses[]);
	void modifyOrder(Bus buses[]);
	void cancelOrder(Bus buses[]);
	bool orderIsEmpty() { return m_ticketID.empty(); }
	//friend void searchOrder(Passenger passengers[], Bus buses[]);
	//friend void makePayment() {}
};
int Passenger::pcounter;

void Passenger::makeOrder(Bus buses[])
{
	showBusesTable(buses);
	cout << "ENTER BUS ID: ";
	int bus_index = inputUpTo(BUSES);
	buses[bus_index - 1].showSeatsTable();
	cout << "ENTER SEAT ID: ";
	int seat_index = inputUpTo(SEATS);
	if (buses[bus_index - 1].getSeat(seat_index - 1).getBusiness() == false)
	{
		m_ticketID = buses[bus_index - 1].getBusID() + buses[bus_index - 1].getSeat(seat_index - 1).getSeatID();
		buses[bus_index - 1].getSeat(seat_index - 1).setBusiness(true);
		cout << "THE ORDER WAS RECORDED SUCCESSFULLY" << endl;
	}
	else
		cout << "THE SEAT IS ALREADY OCCUPIED" << endl;
}

void Passenger::currentOrder(Bus buses[])
{
	cout << "CURRENT ORDER" << endl;
	cout << "PASSENGER ID: " << m_passengerID << endl;
	if (!orderIsEmpty())
	{
		cout << "TICKET ID: " << m_ticketID << endl;
		int bus_index = m_ticketID[1] - '0' + m_ticketID[2] - '0';
		cout << "DEPARTURE: " << buses[bus_index - 1].getDepartureCity() << endl;
		cout << "ARRIVAL: " << buses[bus_index - 1].getArrivalCity() << endl;
		cout << "PRICE: " << buses[bus_index - 1].getPrice() << '$' << endl;
	}
}

void Passenger::modifyOrder(Bus buses[])
{
	cout << "MODIFY CURRENT ORDER?" << endl;
	cout << "1. YES\n0. NO" << endl;
	cout << "SELECT THE OPTION: ";
	if (inputUpTo(1))
	{
		int bus_index = m_ticketID[1] - '0' + m_ticketID[2] - '0';
		int seat_index = m_ticketID[4] - '0' + m_ticketID[5] - '0';
		buses[bus_index - 1].getSeat(seat_index - 1).setBusiness(false);
		m_ticketID.clear();
		makeOrder(buses);
	}
	cout << "THE ORDER WAS MODIFIED" << endl;
}

void Passenger::cancelOrder(Bus buses[])
{
	cout << "CANCEL CURRENT ORDER?" << endl;
	cout << "1. YES\n0. NO" << endl;
	cout << "SELECT THE OPTION: ";
	if (inputUpTo(1))
	{
		int bus_index = m_ticketID[1] - '0' + m_ticketID[2] - '0';
		int seat_index = m_ticketID[4] - '0' + m_ticketID[5] - '0';
		buses[bus_index - 1].getSeat(seat_index - 1).setBusiness(false);
		m_ticketID.clear();
	}
	cout << "THE ORDER WAS CANCELLED" << endl;
}

void showOrders(Passenger passengers[], Bus buses[])
{
	for (int i = 0; !passengers[i].orderIsEmpty(); i++, putEnters(2))
		passengers[i].currentOrder(buses);
}

/*void searchOrder(Passenger passengers[], Bus buses[])
{
	cout << "WHAT TO SEARCH?" << endl;
	cout << "1. BUS\n2. SEAT\n3. PASSENGER" << endl;
	cout << "SELECT THE OPTION: ";
}*/

void menu()
{
	putEnters(3);
	cout << "**************************" << endl;
	cout << "1. MAKE NEW ORDER\n2. MODIFY ORDER\n3. CANCEL ORDER\n4. SHOW LIST OF ORDERS\n5. SEARCH FOR ORDER\n6. MAKE PAYMENT\n7. EXIT" << endl;
	cout << "**************************" << endl;
	cout << "SELECT THE OPTION: ";
}

int main()
{
	srand(time(0));
	enum OPTIONS { MAKE = 1, MODIFY, CANCEL, SHOW, SEARCH, PAY };
	Bus* buses = new Bus[BUSES];
	Passenger* passengers = new Passenger[PASSENGERS];
	int currentPassenger = 0;
	
start:
	menu();
	switch (inputUpTo(7))
	{
	case MAKE:
		putEnters();
		if (passengers[currentPassenger].getTicketID() != "")
			currentPassenger++;
		passengers[currentPassenger].makeOrder(buses);
		putEnters();
		break;

	case MODIFY:
		putEnters();
		passengers[currentPassenger].currentOrder(buses);
		putEnters();
		if (!passengers[currentPassenger].orderIsEmpty())
			passengers[currentPassenger].modifyOrder(buses);
		else
			cout << "THE ORDER IS EMPTY" << endl;
		putEnters();
		break;

	case CANCEL:
		putEnters();
		passengers[currentPassenger].currentOrder(buses);
		putEnters();
		if (!passengers[currentPassenger].orderIsEmpty())
			passengers[currentPassenger].cancelOrder(buses);
		else
			cout << "THE ORDER IS EMPTY" << endl;
		putEnters();
		break;

	case SHOW:
		putEnters(2);
		showOrders(passengers, buses);
		putEnters(2);
		break;

	case SEARCH:
		putEnters(2);
		//searchOrder(passengers, buses);
		putEnters(2);
		break;

	case PAY:
		break;

	default:
		break;
	}

	goto start;

	//system("pause>null");
	return 0;
}
