#pragma once
#include "Global.h"

class Seat
{
private:
	const string m_seatID; // String Seats ID
	bool m_business;	   // Status of Being Ordered
	static int scounter;   // Variable to Initialize Seats IDs
public:
	Seat() : m_business(FREE), m_seatID('S' + (scounter < 9 ? to_string(0) : "") + to_string(++(scounter %= 20))) {}
	const string& getSeatID() const { return m_seatID; }
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
	Seat* m_bus_seats;			   // Array of Seats in Bus
	const int m_price;			   // Integral Seat Price
	static int bcounter;		   // Variable to Initialize Bus IDs
public:
	Bus() : m_busID('B' + (bcounter < 9 ? to_string(0) : "") + to_string(++bcounter)), m_departure_city("TASHKENT"), m_arrival_city(cities[rand() % CITIES]), m_bus_seats(new Seat[SEATS]), m_price(rand() % 51 + 50) {}
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
	cout << '\n' << setw(15) << "BUS ID: " << m_busID << endl;
	cout << "-------------------------" << endl;
	for (int i = 0; i < SEATS; i++)
		cout << m_bus_seats[i].getSeatID() << (m_bus_seats[i].getBusiness() == BUSY ? "(busy)" : "(free)") << '\t' << (i % 2 != 0 && i != 0 ? "\n" : "");
	putEnters();
}

void showBusesTable(Bus buses[])
{
	cout << "\nBUS ID\tDEPARTURE\tARRIVAL\t\tPRICE\tTIME\t" << endl;
	cout << "----------------------------------------------------" << endl;
	for (int i = 0; i < BUSES; i++)
	{
		cout << setw(6)  << buses[i].m_busID << '\t' << buses[i].m_departure_city << '\t' << buses[i].m_arrival_city;
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

