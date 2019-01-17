/*
NAME : PREETRAJ 
DATE : 12/18/2017
PROJECT : ACCOUNT MANAGEMENT SYSTEM
FILE : MAIN FUNCTION FILE
*/


#include <iostream>			// standard console I/O library
#include <string>			// string library
#include <fstream>			// file streaming library
#include <sstream>			// string stream library

// include other class files
#include "account_preetraj.h"
#include "bank_account_preetraj.h"
#include "stock_account_preetraj.h"
#include "node_preetraj.h"
using namespace std;

BankAccount BA;		// Object of class BankAccount, Global access, singleton design pattern--------------------------------------

int main()
{
	int choice1 = 0, choice2 = 0, choice3 = 0;  // Menu choice variables
	double deposit = 0, withdraw = 0;			// deposit and withdraw variables
	
	StockAccount *sap = new StockAccount();	// Pointer object to class StockAccount
								
	Node *node = NULL;						// New node created for linked list

	cout << "------ ACCOUNT MANAGEMENT SYSTEM ------ |\n";
	cout << "------         MAIN MENU         ------ |";

	bool fin = true;							// temporary flag
	
	while (choice1 != 3)
	{
		// MAIN MENU
		cout << "\n    1.  Stock Portfolio Account"
			 << "\n    2.  Bank Account"
			 << "\n    3.  Exit program";
		cout << "\n-------------------------------------------------------|";
		cout << "\n Your choice : ";
		cin >> choice1;

		switch (choice1)
		{
		case 1:
			// Stock Account Menu
			while (choice2 != 8)
			{
				cout << "\n-------------------------------------------------------|";
				cout << "\n	STOCK PORTFOLIO ACCOUNT";
				cout << "\n1. Display the price for Stock Symbol"
					<< "\n2. Display Current Portfolio"
					<< "\n3. Buy Shares"
					<< "\n4. Sell Shares"
					<< "\n5. View Graph for the Portfolio Value variation"
					<< "\n6. View Transaction History"
					<< "\n7. Sort the Stock List"
					<< "\n8. ...Back to Previous Menu";
				cout << "\n-------------------------------------------------------|";
				cout << "\nEnter Your Choice : ";
				cin >> choice2;
				switch (choice2)
				{
				case 1:
					sap->display_stock();	// display stock prices
					break;
				case 2:
					sap->display_portfolio();	// display portfolio
					break;
				case 3:
					node = new Node();
					sap->buy_shares(node);	// Buy shares
					break;
				case 4:
					sap->sell_shares();		// sell shares
					break;
				case 5:
					sap->plot_graph();		// Plot MATLAB graph
					break;
				case 6:
					sap->print_history();	// Print transaction history
					break;
				case 7:
					fin = sap->sort_list();	// Sort the linked list
					if (fin == false)
						cout << "\nEmpty list.\n";
					else
						cout << "\nStock list is now sorted!\n";
					break;
				case 8:
					break;
				default:
					cout << "\n";
				}
			}
			choice2 = 0;
			break;

		case 2:
			// Bank account Menu
			while (choice3 != 5)
			{
				cout << "\n-------------------------------------------------------|";
				cout << "\n			BANK ACCOUNT	";
				cout << "\n1. View Account Cash Balance"
					<< "\n2. Deposit Money"
					<< "\n3. Withdraw Money"
					<< "\n4. Print History"
					<< "\n5. ...Back to Previous Menu";
				cout << "\n-------------------------------------------------------|";
				cout << "\nEnter Your Choice : ";
				cin >> choice3;
				switch (choice3)
				{
				case 1:
					BA.display_balance();		// display bank balance
					break;
				case 2:
					cout << "\nEnter Amount in $ to Deposit : ";
					cin >> deposit;				// temporary amount variable
					BA.cash_deposit(deposit);	// call deposit function
					break;
				case 3:
					cout << "\nEnter Amount in $ to Withdraw : ";
					cin >> withdraw;			// temporary amount variable
					BA.cash_withdraw(withdraw); // call withdraw function
					break;
				case 4:
					BA.print_history();		// call function to print transaction history
					break;
				case 5:
					break;		// go back to previous menu
				default:
					cout << "\n Invalid choice!";
				}
			}
			choice3 = 0;
			break;
		case 3: // if user exits from main menu, save all data
			sap->save_portfolio();    // save portfolio.
			sap->saveport_value();    // save portfolio value and timestamp 
			cout << "\nSystem Exited.";
			break;
		default:
			cout << "\nInvalid choice!";
		}
	}
} // End of main function 