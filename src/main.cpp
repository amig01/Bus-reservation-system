#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#define next   \
	cin.get(); \
	cin.get();
#define cls system("clear");
using namespace std;

const int BUSES = 10;
const int SEATS = 20;
const int PASSENGERS = 200;
const int CITIES = 10;

const bool EMPTY = true;
const bool BUSY = true;
const bool FREE = false;

const string MYFILE = "/Users/user/Desktop/C/Project/extra/FILE.dat";

const string cities[CITIES] = {"KHIVA", "BUKHARA", "SAMARKAND", "NUKUS", "JIZAKH", "KASHKADARYA", "SURKHANDARYA", "ALAT", "VOBKENT", "GULISTAN"};

void proceed()
{
	cout << "\nPRESS ENTER TO CONTINUE ";
	next;
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

void putEnters(int number = 1)
{
	for (int i = 0; i < number; i++)
		cout << endl;
}

class Seat
{
private:
	const string m_seatID; // String Seats ID
	bool m_business;	   // Status of Being Ordered
	static int scounter;   // Variable to Initialize Seats IDs
public:
	Seat() : m_business(FREE), m_seatID('S' + (scounter < 9 ? to_string(0) : "") + to_string(++(scounter %= 20))) {}
	const string &getSeatID() const { return m_seatID; }
	void setBusiness(bool business) { m_business = business; }
	const bool getBusiness() const { return m_business; }
};
int Seat::scounter;

class Bus
{
protected:
	const string m_busID;		   // String Bus ID
	const string m_departure_city; // String Departure City
	const string m_arrival_city;   // String Arrival City
	Seat *m_bus_seats;			   // Array of Seats in Bus
	const int m_price;			   // Integral Seat Price
	static int bcounter;		   // Variable to Initialize Bus IDs
public:
	Bus() : m_busID('B' + (bcounter < 9 ? to_string(0) : "") + to_string(++bcounter)), m_departure_city("TASHKENT"), m_arrival_city(cities[rand() % CITIES]), m_bus_seats(new Seat[SEATS]), m_price(rand() % 51 + 50) {}
	~Bus() { delete[] m_bus_seats; }
	const string &getDepartureCity() const { return m_departure_city; }
	const string &getArrivalCity() const { return m_arrival_city; }
	const string &getBusID() const { return m_busID; }
	Seat &getSeat(int index) { return m_bus_seats[index]; }
	int getPrice() const { return m_price; }
	void showSeatsTable();
	friend void showBusesTable(Bus buses[]);
};
int Bus::bcounter;

int getDigit(int number)
{
	if (number < 9)
		return number;
	return number / 10 + number % 10;
}

int getSize(long d)
{
	string num = to_string(d);
	return num.length();
}

long getPrefix(long number, int k)
{
	if (getSize(number) > k)
	{
		string num = to_string(number);
		return stol(num.substr(0, k));
	}
	return number;
}

bool prefixMatched(long number, int d)
{
	return getPrefix(number, getSize(d)) == d;
}

int sumOfDoubleEvenPlace(long int number)
{
	int sum = 0;
	string num = to_string(number);
	for (int i = getSize(number) - 2; i >= 0; i -= 2)
		sum += getDigit(int(num[i] - '0') * 2);

	return sum;
}

int sumOfOddPlace(long number)
{
	int sum = 0;
	string num = to_string(number);
	for (int i = getSize(number) - 1; i >= 0; i -= 2)
		sum += num[i] - '0';
	return sum;
}

void Bus::showSeatsTable()
{
	cls;
	cout << "\nBUS ID: " << m_busID << "\n\n";
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

void showArrivalsTable()
{
	for (int i = 0; i < CITIES; i++)
		cout << setw(2) << i + 1 << ". " << cities[i] << endl;
	putEnters();
}

class Passenger
{
private:
	const string m_passengerID; // String Passenger ID
	string m_ticketID;			// String Passenger Ticket ID
	static int pcounter;		// Variable to Initialize Passenger IDs
public:
	Passenger() : m_passengerID('P' + (pcounter < 9 ? to_string(0) : "") + to_string(++pcounter)) {}
	const string &getPassengerID() const { return m_passengerID; }
	const string &getTicketID() const { return m_ticketID; }
	void makeOrder(Bus buses[]);
	void currentOrder(Bus buses[]);
	void modifyOrder(Bus buses[]);
	void cancelOrder(Bus buses[]);
	bool orderIsEmpty() { return m_ticketID.empty(); }
	friend void searchOrder(Passenger passengers[], Bus buses[]);
	friend void makePayment(Passenger passengers[], Bus buses[]);
};
int Passenger::pcounter;

void Passenger::makeOrder(Bus buses[])
{
	cls;
	ofstream FILEOUT(MYFILE, ios::beg | ios::binary | ios::trunc);
	showBusesTable(buses);
	cout << "ENTER BUS ID: B";
	int bus_index = inputUpTo(BUSES);
	buses[bus_index - 1].showSeatsTable();
	cout << "ENTER SEAT ID: S";
	int seat_index = inputUpTo(SEATS);
	if (buses[bus_index - 1].getSeat(seat_index - 1).getBusiness() == FREE)
	{
		m_ticketID = buses[bus_index - 1].getBusID() + buses[bus_index - 1].getSeat(seat_index - 1).getSeatID();
		buses[bus_index - 1].getSeat(seat_index - 1).setBusiness(BUSY);
		FILEOUT.write((char *)(&buses[bus_index - 1]), sizeof(buses[bus_index - 1]));
		cout << "\nTHE ORDER WAS RECORDED SUCCESSFULLY" << endl;
	}
	else
	{
		cout << "\nTHE SEAT IS ALREADY OCCUPIED" << endl;
	}
	FILEOUT.close();
	proceed();
}

void Passenger::currentOrder(Bus buses[])
{
	cls;
	cout << "CURRENT ORDER" << endl;
	cout << "PASSENGER ID: " << m_passengerID << endl;
	if (orderIsEmpty() != EMPTY)
	{
		cout << "TICKET ID: " << m_ticketID << endl;
		int bus_index = stoi(m_ticketID.substr(1, 2));
		cout << "DEPARTURE: " << buses[bus_index - 1].getDepartureCity() << endl;
		cout << "ARRIVAL: " << buses[bus_index - 1].getArrivalCity() << endl;
		cout << "PRICE: " << buses[bus_index - 1].getPrice() << '$' << endl;
	}
	proceed();
}

void Passenger::modifyOrder(Bus buses[])
{
	cout << "MODIFY CURRENT ORDER?" << endl;
	cout << "1. YES\n0. NO" << endl;
	cout << "SELECT THE OPTION: ";
	if (inputUpTo(1))
	{
		int bus_index = stoi(m_ticketID.substr(1, 2));
		int seat_index = stoi(m_ticketID.substr(4, 2));
		buses[bus_index - 1].getSeat(seat_index - 1).setBusiness(FREE);
		m_ticketID.clear();
		makeOrder(buses);
	}
	cout << "\nTHE ORDER WAS MODIFIED SUCCESSFULLY" << endl;
	proceed();
}

void Passenger::cancelOrder(Bus buses[])
{
	cls;
	cout << "CANCEL CURRENT ORDER?" << endl;
	cout << "1. YES\n0. NO" << endl;
	cout << "SELECT THE OPTION: ";
	if (inputUpTo(1))
	{
		int bus_index = stoi(m_ticketID.substr(1, 2));
		int seat_index = stoi(m_ticketID.substr(4, 2));
		buses[bus_index - 1].getSeat(seat_index - 1).setBusiness(FREE);
		m_ticketID.clear();
	}
	cout << "THE ORDER WAS CANCELLED SUCCESSFULLY" << endl;
	proceed();
}

void showOrders(Passenger passengers[], Bus buses[])
{
	cls;
	for (int i = 0; passengers[i].orderIsEmpty() != EMPTY; i++, putEnters(2))
		passengers[i].currentOrder(buses);
	proceed();
}

void searchOrder(Passenger passengers[], Bus buses[])
{
	showArrivalsTable();
	cout << "CHOOSE THE ARRIVAL CITY: ";
	int arrival_index = inputUpTo(CITIES);

	bool passengerIsFound = false;
	for (int i = 0; passengers[i].orderIsEmpty() != EMPTY; i++)
	{
		int bus_index = stoi(passengers[i].m_ticketID.substr(1, 2));
		if (buses[bus_index - 1].getArrivalCity() == cities[arrival_index - 1])
		{
			if (passengerIsFound == false)
			{
				cout << "FOUND PASSENGER(S) WITH THIS ARRIVAL" << endl;
				passengerIsFound = true;
			}
			putEnters();
			passengers[i].currentOrder(buses);
		}
	}
	if (passengerIsFound == false)
		cout << "THERE ARE NO PASSENGERS WITH THIS ARRIVAL" << endl;
}

bool isValid(long int &number)
{
	return (getSize(number) >= 13 &&
			getSize(number) <= 16) &&
		   (prefixMatched(number, 4) ||
			prefixMatched(number, 5) ||
			prefixMatched(number, 37) ||
			prefixMatched(number, 6)) &&
		   ((sumOfDoubleEvenPlace(number) +
			 sumOfOddPlace(number)) %
				10 ==
			0);
}

void makePayment(Passenger passengers[], Bus buses[])
{
	long int cardNumber;
	cls;
	for (int i = 0; passengers[i].orderIsEmpty() != EMPTY; i++)
	{
		cout << "ENTER VALID CREDIT CARD NUMBER: ";
		cin >> cardNumber;

		if (isValid(cardNumber) == true)
		{
			int bus_index = stoi(passengers[i].m_ticketID.substr(1, 2));
			cout << '\n'
				 << buses[bus_index - 1].getPrice() << '$' << " WAS WITHDRAWN\n\n";
			proceed();
			break;
		}

		else
		{
			cout << "\nCARD NUMBER'S NOT VALID\n\n";
			proceed();
			break;
		}
	}
}

void menu()
{
	cout << "**************************" << endl;
	cout << "1. MAKE NEW ORDER\n2. MODIFY ORDER\n3. CANCEL ORDER\n4. SHOW LIST OF ORDERS\n5. SEARCH FOR ORDER\n6. MAKE PAYMENT\n7. EXIT" << endl;
	cout << "**************************" << endl;
	cout << "SELECT THE OPTION: ";
}

int main()
{
	srand(time(0));
	enum OPTIONS
	{
		MAKE = 1,
		MODIFY,
		CANCEL,
		SHOW,
		SEARCH,
		PAY,
		EXIT
	};
	Bus *buses = new Bus[BUSES];
	Passenger *passengers = new Passenger[PASSENGERS];
	int current_passenger = 0;

	while (true)
	{
		cls;
		menu();
		switch (inputUpTo(7))
		{
		case MAKE:
			putEnters(2);
			if (passengers[current_passenger].orderIsEmpty() != EMPTY)
				current_passenger++;
			passengers[current_passenger].makeOrder(buses);
			putEnters(2);
			break;

		case MODIFY:
			putEnters(2);
			passengers[current_passenger].currentOrder(buses);
			putEnters();
			if (passengers[current_passenger].orderIsEmpty() != EMPTY)
				passengers[current_passenger].modifyOrder(buses);
			else
				cout << "CURRENT ORDER IS EMPTY" << endl;
			putEnters(2);
			break;

		case CANCEL:
			putEnters(2);
			passengers[current_passenger].currentOrder(buses);
			putEnters();
			if (passengers[current_passenger].orderIsEmpty() != EMPTY)
				passengers[current_passenger].cancelOrder(buses);
			else
				cout << "CURRENT ORDER IS EMPTY" << endl;
			putEnters(2);
			break;

		case SHOW:
			putEnters(2);
			if (passengers[0].orderIsEmpty() != EMPTY)
				showOrders(passengers, buses);
			else
				cout << "THERE ARE NO ORDERS" << endl;
			putEnters(2);
			break;

		case SEARCH:
			putEnters(2);
			if (passengers[0].orderIsEmpty() != EMPTY)
				searchOrder(passengers, buses);
			else
				cout << "THERE ARE NO ORDERS" << endl;
			putEnters(2);
			break;

		case PAY:
			putEnters(2);
			passengers[current_passenger].currentOrder(buses);
			makePayment(passengers, buses);
			putEnters(2);
			break;

		case EXIT:
			cout << "\nTHANK YOU\n";
			exit(0);
		}
	}
	// system("pause>null");
	return 0;
}
