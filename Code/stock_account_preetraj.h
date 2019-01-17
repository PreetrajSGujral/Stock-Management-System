/*
NAME : PREETRAJ 
DATE : 12/18/2017
PROJECT : ACCOUNT MANAGEMENT SYSTEM
FILE : DERIVED CLASS .H FILE
*/

#pragma once
#include<iostream>				// Standard I/O library	
#include<fstream>				// File I/O library
#include<string>				// Standard string operations library
#include<time.h>				// Library for time stamp
#include<sstream>				// string stream library
#include<map>					// Standard template map for storing key and contents

// include base class and node class 
#include "account_preetraj.h"
#include "node_preetraj.h"

using namespace std;


#ifndef STOCK_ACCOUNT_PREETRAJ_H
#define STOCK_ACCOUNT_PREETRAJ_H

class Node;	// Class Node forwarded

class StockAccount : public Account
{
public:
	StockAccount();					  // constructor
	~StockAccount();				  // destructor 

	void display_stock();			  // display stock price
	void display_portfolio();         // display current portfolio

	void buy_shares(Node *);		  // BUY shares
	void sell_shares();				  // SELL shares


	bool sort_list();				 // sort linked list
	void save_portfolio();			 // save portfolio
	void get_portfolio();		     // get portfolio

	virtual double getbal();		 // get cash balance
	virtual void setbal();			 // setting cash balance

	void saveport_value();			 // save portfolio value and timestamp.
	void get_port_value();			 // get portfolio value.

	void plot_graph();				 // view portfolio value graph
	virtual void print_history();    // print stock history

private:
	string stock_symbol;	// Stock ticker at the text files

	int size;				// Size of the list
	int file_no;			// For random selection between two text files
	int count;				// size of portfolio value array

	// Linked list nodes 
	Node *prev = NULL;
	Node *headptr;
	Node *tailptr;

	double port_value, port_array[100];		// Portfolio value and array of portfolio values

	string time_stamp[100];					// Array for time values

	int shares;								// Number of shares
	double max, min;						// Maximum and minimum amount user willing to pay for share

	ifstream balance_file, port_file, portval_file;	// Instances to access portfolio text files
	ifstream file1, file2;							// Instances to access stock info files

	// Temporary variables to store different parts of the line read from files
	string temp1;				
	int sharetemp1;

	// Containers to hold values ----------------- Class: Template. Behavioural Design Pattern.--------------
	map<string, double> result1, result2;
	map<string, int> portfolio;

	// Variables to store streams of strings from file
	stringstream stream1;
	stringstream stream2;
	stringstream stream3;

	// string holders for different parameters from the line 
	string line, line2, symb1, date1;
	double price1;

	// output file instances 
	ofstream writebalance_file, write_bank_history, write_portfolio;
};	

#endif


