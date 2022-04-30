#pragma once
#include "Global.h"

class Passenger
{
private:
	const string m_passengerID; // String Passenger ID
	string m_ticketID;			// String Passenger Ticket ID
	static int pcounter;		// Variable to Initialize Passenger IDs
public:
	Passenger() : m_passengerID('P' + (pcounter < 9 ? to_string(0) : "") + to_string(++pcounter)) {}
	const string& getPassengerID() const { return m_passengerID; }
	const string& getTicketID() const { return m_ticketID; }
	bool orderIsEmpty() { return m_ticketID.empty(); }
	bool makeOrder(Bus buses[]); // Returns "true" as Success
	bool modifyOrder(Bus buses[]); // Returns "true" as Success
	bool cancelOrder(Bus buses[]); // Returns "true" as Success
	void currentOrder(Bus buses[]);
	friend void searchOrder(Passenger passengers[], Bus buses[]);
	friend void makePayment(Passenger passengers[], Bus buses[]);
};

int Passenger::pcounter;

bool Passenger::makeOrder(Bus buses[])
{
	showBusesTable(buses);

	cout << "ENTER BUS ID: B";
	int bus_index = inputInRange(1, BUSES);
	buses[bus_index - 1].showSeatsTable();

	cout << "ENTER SEAT ID: S";
	int seat_index = inputInRange(1, SEATS);
	if (buses[bus_index - 1].getSeat(seat_index - 1).getBusiness() == FREE)
	{
		m_ticketID = buses[bus_index - 1].getBusID() + buses[bus_index - 1].getSeat(seat_index - 1).getSeatID();
		buses[bus_index - 1].getSeat(seat_index - 1).setBusiness(BUSY);
		ofstream fout(file_name, ios::beg | ios::binary | ios::trunc);
		fout.write((char*)(&buses[bus_index - 1]), sizeof(buses[bus_index - 1]));
		fout.close();
		return SUCCESS;
	}
	else
		return FAIL;
}

bool Passenger::modifyOrder(Bus buses[])
{
	cout << "MODIFY CURRENT ORDER?" << endl;
	cout << "1. YES\n0. NO" << endl;
	cout << "SELECT THE OPTION: ";
	if (inputInRange(1))
	{
		int bus_index = stoi(m_ticketID.substr(1, 2));
		int seat_index = stoi(m_ticketID.substr(4, 2));
		buses[bus_index - 1].getSeat(seat_index - 1).setBusiness(FREE);
		m_ticketID.clear();
		makeOrder(buses);
		return SUCCESS;
	}
	else
		return FAIL;
}

bool Passenger::cancelOrder(Bus buses[])
{
	cout << "CANCEL CURRENT ORDER?" << endl;
	cout << "1. YES\n0. NO" << endl;
	cout << "SELECT THE OPTION: ";
	if (inputInRange(1))
	{
		int bus_index = stoi(m_ticketID.substr(1, 2));
		int seat_index = stoi(m_ticketID.substr(4, 2));
		buses[bus_index - 1].getSeat(seat_index - 1).setBusiness(FREE);
		m_ticketID.clear();
		return SUCCESS;
	}
	else
		return FAIL;
}

void Passenger::currentOrder(Bus buses[])
{
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
}

void showOrders(Passenger passengers[], Bus buses[])
{
	for (int i = 0; passengers[i].orderIsEmpty() != EMPTY; i++, putEnters(2))
		passengers[i].currentOrder(buses);
}

void searchOrder(Passenger passengers[], Bus buses[])
{
	showArrivalsTable();
	cout << "CHOOSE THE ARRIVAL CITY: ";
	int arrival_index = inputInRange(1, CITIES);

	bool passenger_is_found = false;
	for (int i = 0; passengers[i].orderIsEmpty() != EMPTY; i++)
	{
		int bus_index = stoi(passengers[i].m_ticketID.substr(1, 2));
		if (buses[bus_index - 1].getArrivalCity() == cities[arrival_index - 1])
		{
			if (passenger_is_found == false)
			{
				cout << "\nFOUND PASSENGER(S) WITH THIS ARRIVAL" << endl;
				passenger_is_found = true;
			}
			putEnters();
			passengers[i].currentOrder(buses);
		}
	}
	if (passenger_is_found == false)
		cout << "\nTHERE ARE NO PASSENGERS WITH THIS ARRIVAL" << endl;
}

void makePayment(Passenger passengers[], Bus buses[])
{
	long int card_number;
	for (int i = 0; passengers[i].orderIsEmpty() != EMPTY; i++)
	{
		cout << "ENTER VALID CREDIT CARD NUMBER: ";
		cin >> card_number;

		if (isValid(card_number) == true)
		{
			int bus_index = stoi(passengers[i].m_ticketID.substr(1, 2));
			cout << '\n' << buses[bus_index - 1].getPrice() << '$' << " WAS WITHDRAWN\n" << endl;
			break;
		}
		else
		{
			cout << "\nCARD NUMBER IS NOT VALID\n" << endl;
			break;
		}
	}
}
