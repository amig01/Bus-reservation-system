#include "Bus.h"
#include "Passenger.h"

int main()
{
	srand(time(0));
	enum OPTIONS { MAKE = 1, MODIFY, CANCEL, SHOW, SEARCH, PAY, EXIT };
	Bus* buses = new Bus[BUSES];
	Passenger* passengers = new Passenger[PASSENGERS];
	int current_passenger = 0;

	while (true)
	{
		system("cls");

		cout << "1. MAKE NEW ORDER\n2. MODIFY ORDER\n3. CANCEL ORDER\n4. SHOW LIST OF ORDERS\n5. SEARCH FOR ORDER\n6. MAKE PAYMENT\n7. EXIT" << endl;
		cout << "SELECT THE OPTION: ";

		switch (inputInRange(1, 7))
		{
		case MAKE:
			putEnters(2);
			if (passengers[current_passenger].orderIsEmpty() != EMPTY)
				current_passenger++;
			if (passengers[current_passenger].makeOrder(buses) == SUCCESS)
				cout << "\nTHE ORDER WAS RECORDED SUCCESSFULLY" << endl;
			else
				cout << "\nTHE SEAT IS ALREADY OCCUPIED" << endl;
			putEnters(2);
			break;

		case MODIFY:
			putEnters(2);
			passengers[current_passenger].currentOrder(buses);
			putEnters();
			if (passengers[current_passenger].orderIsEmpty() != EMPTY)
			{
				if (passengers[current_passenger].modifyOrder(buses))
					cout << "\nTHE ORDER WAS MODIFIED SUCCESSFULLY" << endl;
			}
			else
				cout << "\nCURRENT ORDER IS EMPTY" << endl;
			putEnters(2);
			break;

		case CANCEL:
			putEnters(2);
			passengers[current_passenger].currentOrder(buses);
			putEnters();
			if (passengers[current_passenger].orderIsEmpty() != EMPTY)
			{
				if (passengers[current_passenger].cancelOrder(buses))
					cout << "\nTHE ORDER WAS CANCELLED SUCCESSFULLY" << endl;
			}
			else
				cout << "\nCURRENT ORDER IS EMPTY" << endl;
			putEnters(2);
			break;

		case SHOW:
			putEnters(2);
			if (passengers[0].orderIsEmpty() != EMPTY)
				showOrders(passengers, buses);
			else
				cout << "\nTHERE ARE NO ORDERS" << endl;
			putEnters(2);
			break;

		case SEARCH:
			putEnters(2);
			if (passengers[0].orderIsEmpty() != EMPTY)
				searchOrder(passengers, buses);
			else
				cout << "\nTHERE ARE NO ORDERS" << endl;
			putEnters(2);
			break;

		case PAY:
			putEnters(2);
			passengers[current_passenger].currentOrder(buses);
			makePayment(passengers, buses);
			putEnters(2);
			break;

		case EXIT:
			delete[] buses, passengers;
			cout << "\nTHANK YOU" << endl;
			exit(0);
		}
		cout << "\nPRESS ENTER TO CONTINUE";
		cin.ignore(); cin.get();
	}
	// system("pause>null");
	return 0;
}
