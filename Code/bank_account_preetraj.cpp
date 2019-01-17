/*
NAME : preetraj 
DATE : 12/18/2017
PROJECT : ACCOUNT MANAGEMENT SYSTEM
FILE : DERIVED CLASS .CPP FILE
*/
#include<iostream>	// Standard I/O library
#include<iomanip>	// standard I/O manipulation library
#include<time.h>	// Library for time stamp
#include<fstream>	// File I/O library
#include<string>	// Standard string operations library
#include<stdlib.h>	// standard library

using namespace std;
// include other class files
#include "bank_account_preetraj.h"

//constructor
BankAccount::BankAccount()
{
	setbal();
	deposit = 0;
	withdraw = 0;
}

// destructor
BankAccount::~BankAccount()
{
	cout << "\nAccount Exited.";
}

// Get cash balance
double BankAccount::getbal()
{
	return cashbal;
}

// Set cash balance
void BankAccount::setbal()
{
	streampos len;
	ifstream file1;
	file1.open("balance_file.txt", ios::binary);     // open balance file
	if (file1.is_open())
	{
		file1.seekg(0, ios::end);              // put console at end of file
		len = file1.tellg();				   // find the position of the cursor
		file1.close();                         // close file
	}

	if (!len) // put default cash balance of 10000
	{
		double cash = 10000.00;
		ofstream file2;
		file2.open("balance_file.txt", ios_base::out);
		file2 << cash;
		file2.close();

		ifstream file3("balance_file.txt", ios_base::in);
		file3 >> cashbal;
		file3.close();
	}
	else
	{
		// else update balance from existing cash balance 
		ifstream file4("balance_file.txt", ios_base::in);
		file4 >> cashbal;
		file4.close();
	}
}

//Display cash balance
void BankAccount::display_balance()
{
	setbal();
	cout << "\nCurrent Cash Balance : " << getbal() << "$" << endl;
}

//Deposit cash
void BankAccount::cash_deposit(double amount)
{
	deposit = amount;
	cashbal = getbal();
	cashbal = cashbal + deposit;
	cout << "\nAmount $" << deposit << " is Deposited to the Account\n";

	// generate the current date and timestamp
	time_t R;
	struct tm T;
	char buffer[80];
	time(&R);
	localtime_s(&T, &R);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &T);
	std::string str(buffer);

	// write deposit transaction to bank_transaction_history.txt file
	file.open("bank_transaction_history.txt", ios::app);
	file << endl << left << setw(30) << "Deposit";
	file << left << setw(1) << "$";
	file << left << setw(15) << deposit;
	file << right << setw(15) << str;
	file << right << setw(5) << "$" << cashbal;
	file.close();

	// write to a balance file
	writebalance_file.open("balance_file.txt", std::ios_base::out);
	writebalance_file << cashbal;
	writebalance_file.close();
}

//withdraw cash
void BankAccount::cash_withdraw(double amount)
{
	withdraw = amount;
	setbal();
	cashbal = getbal();

	if (cashbal > 0)	//check if cash balance is greater than 0 
	{
		if (withdraw > cashbal)
		{
			cout << "\nBalance insufficient! Cannot Withdraw!\n";
			return;
		}

		else
		{
			cashbal = cashbal - withdraw; // update cash balance after withdrawl
			cout << "\nAmount $" << withdraw << " is withdrwan from the Account\n";

			//generate the current date and timestamp
			time_t R;
			struct tm T;
			char buffer[80];
			time(&R);
			localtime_s(&T, &R);
			strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &T);
			std::string str(buffer);

			// write withdrawal transaction to file
			file.open("bank_transaction_history.txt", ios::app);
			file << endl << left << setw(30) << "Withdrawal";
			file << left << setw(1) << "$";
			file << left << setw(15) << withdraw;
			file << right << setw(15) << str;
			file << right << setw(5) << "$" << cashbal;
			file.close();

			// write to a balance file
			writebalance_file.open("balance_file.txt", std::ios_base::out);
			writebalance_file << cashbal;
			writebalance_file.close();

			return;
		}
	}
	else
	{
		cout << "\nAccount Balance is 0, cannot withdraw!\n";
	}
}

//print history
void BankAccount::print_history()
{
	read_file.open("bank_transaction_history.txt", ios::app);
	cout << endl << left << setw(30) << "Transaction";
	cout << left << setw(16) << "Amount";
	cout << left << setw(23) << "Timestamp";
	cout << right << setw(5) << "Balance" << endl;
	if (read_file.is_open())
	{
		while (!read_file.eof())
		{
			while (getline(read_file, line))
				cout << line << "\n";
		}
	}
	read_file.close();
}
