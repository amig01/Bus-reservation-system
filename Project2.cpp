#include <iostream>
#include <string>
#include <ctime>

#define BUSES 10
#define SEATS 20
#define PASSENGERS 20

using namespace std;

string cities[] = { "KHIVA" };

class Seat
{
private:
	string m_seatID;	 // String Seats ID
	static int scounter; // Variable to Initialize Seats IDs
	bool m_business;
public:
	Seat() : m_business(false) { m_seatID = 'S' + (scounter < 9 ? to_string(0) : "") + to_string(scounter + 1); ++scounter; }
	const string &getSeatID() const { return m_seatID; }
	void setSeatBusiness(bool &business) { m_business = business; }
};
int Seat::scounter;

class Bus
{
private:
	string m_departure_city;
	string m_arrival_city;
	string m_busID;		 // String Bus ID
	Seat *m_bus_seats;	 // Array of seats in bus
	int m_price;
	static int bcounter; // Variable to Initialize Bus IDs
public:
	Bus() : m_bus_seats(new Seat[SEATS]), m_departure_city("TASHKENT"), m_arrival_city(cities[0]), m_price(50) { m_busID = 'B' + (bcounter < 9 ? to_string(0) : "") + to_string(bcounter + 1); ++bcounter; }
	~Bus() { delete[] m_bus_seats; }
	const string &getBusID() const { return m_busID; }
	const string &getSeatID(int index) const { return m_bus_seats[index].getSeatID(); }
	friend void makeOrder();
	friend void cancelOrder();
};
int Bus::bcounter;

class Passenger
{
private:
	string m_passengerID;	   // String Passenger ID
	static int pcounter;	   // Variable to Initialize Passenger IDs
	string m_passenger_seatID; // String Passenger Seat ID
public:
	Passenger() { m_passengerID = 'P' + (pcounter < 9 ? to_string(0) : "") + to_string(pcounter + 1); ++pcounter; }
	const string &getPassengerID() const { return m_passengerID; }
	void setPassengerSeatID(const string &ID) { m_passenger_seatID = ID; }
	const string &getPassengerSeatID() const { return m_passenger_seatID; }
	void makeOrder() {}
	void cancelOrder() {}
};
int Passenger::pcounter;


int main()
{
	Bus *buses = new Bus[BUSES];
	Passenger *passengers = new Passenger[PASSENGERS];

	delete[] passengers;
	delete[] buses;

	system("pause");
	return 0;
}

// Add try catch
// Add menu
// Add header
