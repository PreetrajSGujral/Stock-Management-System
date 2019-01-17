/*
NAME : PREETRAJ 
DATE : 12/18/2017
PROJECT : ACCOUNT MANAGEMENT SYSTEM
FILE : DERIVED CLASS .CPP FILE
*/

// Library files for linking to MATLAB 
#pragma comment( lib, "libmx.lib" )	
#pragma comment( lib, "libmex.lib" )
#pragma comment( lib, "libeng.lib" )
#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
// end

#include<engine.h>			// library for MATLAB
#include<cmath>				// math operations library
#include<time.h>			// time stamp library
#include<iostream>			// standard console I/O library
#include<iomanip>			// standard I/O manipulation library
#include<map>				// container map library
#include<sstream>			// string stream library
#include<fstream>			// file streaming library
#include<string>			// string library
#include<stdlib.h>			// standard library

using namespace std;
// include other class files
#include "stock_account_preetraj.h"
#include "node_preetraj.h"

// constructor
StockAccount::StockAccount()	// Default constructor
{
	headptr = NULL;				// Assign NULL to head pointer of linked list
	tailptr = NULL;				// Assign NULL to tail pointer of linked list
	
								//Initialising all portfolio variables
	port_array[20] = { 0 };		
	count = 0;
	port_value = 0;
	
	setbal();					// Set value for cash balance

	srand((unsigned int)time(NULL));	// Generate random seeds for random function using time

	// Access the given two stock text files 
	file1.open("Result_1.txt");
	file2.open("Result_2.txt");

	if (file1.is_open() && file2.is_open())		// Check if files are opened
	{
		while (!file1.eof() && !file2.eof())	// Check if end of file reached
		{
			getline(file1, line);				// Read line from the file
			stream1 << line;					// store in the stream 
			stream1 >> symb1 >> price1;			// Store into different parts for Ticker and price
			result1.insert(pair<string, double>(symb1, price1));	// Store pair into container
			stream1.str("");					// allocate string object
			stream1.clear();					// clear stream

			getline(file2, line);				// Read line from the file
			stream1 << line;					// store in the stream 
			stream1 >> symb1 >> price1;			// Store into different parts for Ticker and price
			result2.insert(pair<string, double>(symb1, price1));	// Store pair into container
			stream1.str("");					// allocate string object
			stream1.clear();					// clear stream
		}
	}
	// close files after use
	file1.close();
	file2.close();

	// getting size of previously stored portfolio (doubly linked list)
	file1.open("list_size.txt", ios_base::in); // open file for reading
	file1 >> size;
	file1.close();
	if (size != 0)
		this->get_portfolio(); 	// retrieing the previously stored portfolio in a double linked list
	this->get_port_value(); // retrieve portflio value in double array for plotting
}

// destructor 
StockAccount::~StockAccount()
{
	cout << "\n Account System Exited. ";
}

// Get cash balance
double StockAccount::getbal()
{
	return cashbal;
}

// Set cash balance
void StockAccount::setbal()
{
	streampos len;
	ifstream file1;
	file1.open("balance_file.txt", ios::binary);    // open  file
	if (file1.is_open())
	{
		file1.seekg(0, ios::end);              // put the console at the end of the file
		len = file1.tellg();                   // find the position of the console
		file1.close();                         // close  file
	}

	if (!len) // if len is not found, create the file and put 10,000 cash balance into it.
	{
		double putcash = 10000.00;

		ofstream file2; // output file
		file2.open("balance_file.txt", ios_base::out);
		file2 << putcash;
		file2.close();

		//update cash balance as 10000
		ifstream file3("balance_file.txt", ios_base::in);
		file3 >> cashbal;
		file3.close();
	}
	else
	{
		// else update balance from existing cash balance file.
		ifstream file4("balance_file.txt", ios_base::in);
		file4 >> cashbal;
		file4.close();
	}
}

//display stock price 
void StockAccount::display_stock()
{
	bool flag = false;		// temporary indicator

	cout << "\nEnter Stock Symbol : ";
	cin >> stock_symbol;

	file_no = rand() % 2;    // generate random numbers for selecting between two text filesS

	if (file_no == 0)		// Access Result_1.txt
	{
		// iterating through map
		for (map<string, double>::iterator i = result1.begin(); i != result1.end(); i++)
		{
			// if symbol is found then display its stock price
			if (stock_symbol == (*i).first)		// compare the first stored value
			{	// print all the parameters
				cout << left << setw(10) << "Symbol";			
				cout << left << setw(10) << "Price/Share" << endl;
				cout << left << setw(10) << (*i).first;
				cout << left << setw(10) << (*i).second << endl;
				flag = true;
			}
		}
		if (flag == false)
			cout << "\nSymbol not found at database !\n";
		return;
	}
	
	else if (file_no == 1)	// Access Result_2.txt
	{
		// iterating through container
		for (map<string, double>::iterator i = result2.begin(); i != result2.end(); i++)
		{
			// if symbol is found then display its stock price
			if (stock_symbol == (*i).first)	// compare the first stored value
			{
				cout << left << setw(10) << "Symbol";
				cout << left << setw(10) << "Price/Share" << endl;
				cout << left << setw(10) << (*i).first;
				cout << left << setw(10) << (*i).second << endl;
				flag = true;
			}
		}
		
		if (flag == false)	// if symbol not found
			cout << "\nSymbol not found!\n";
		return;
	}
}

// display portfolio
void StockAccount::display_portfolio()
{
	Node *cur = headptr;	// new temporary pointer for accessing linked list
	setbal();				// set value for cash balance
	double stockval = 0, cashbal = getbal();	// initialise cash and stock values

	while (cur != NULL)
	{
		file_no = rand() % 2;
		// for file 1 assign temporary stock price to corresponding symbol in portfolio 
		if (file_no == 0)
		{
			for (map<string, double>::iterator i = result1.begin(); i != result1.end(); i++)
			{
				if (cur->symb == (*i).first)	// compare the symbol from the node
				{
					cur->temp_price = (*i).second;				 // assign price per share
					cur->cur_port_val = cur->share_num*cur->temp_price; // calculate temporary node value of portfolio
				}
			}
		}

		// Repeat above steps for file 2
		else if (file_no == 1)
		{
			for (map<string, double>::iterator i = result2.begin(); i != result2.end(); i++)
			{
				if (cur->symb == (*i).first)
				{
					cur->temp_price = (*i).second;                
					cur->cur_port_val = cur->share_num*cur->temp_price; 
				}
			}
		}
		cur = cur->nextptr; // access next node
	}
	
	this->sort_list(); // sort the stock values using the linked list nodes

	if (size > 0) 
	{
		cout << endl << left << setw(15) << "Symbol";
		cout << left << setw(15) << "Shares";
		cout << left << setw(15) << "Price/Share($)";
		cout << left << setw(15) << "Total Value($)" << endl;
		cur = headptr;  // temp pointer for iterations

		while (cur != NULL)
		{
			cout << left << setw(15) << cur->symb;			// print symbol
			cout << left << setw(15) << cur->share_num;		// number of shares
			cout << left << setw(15) << cur->temp_price;	// price per share
			cout << left << setw(15) << cur->cur_port_val << endl;		// stock value

			stockval = stockval + cur->cur_port_val;		// update the stock value
			cur = cur->nextptr;						// move to next node
		}
		port_value = cashbal + stockval;			// calculate the portfolio value
		cout << "\nCash Balance  : $" << cashbal;
		cout << "\nStock Balance : $" << stockval;
		cout << "\nTotal Portfolio value is : $" << port_value << endl; // print total portfolio value

		port_array[count] = port_value; // store portfolio value changes in double type array.
		count++;
	}
	
	else if (size == 0) // if no values present in shares
	{
		port_value = cashbal;
		cout << "\nNo shares available in portfolio! Buy some.\n";
	}
}

//sorting the linked list using nodes
bool StockAccount::sort_list()
{
	Node *c1 = headptr; // create a head pointer temporary
	int counter = 0;	// temporary counter

	while (c1 != NULL)	// check if head pointer is NULL
	{
		file_no = rand() % 2;	// choose a random file

		if (file_no == 0)		// for Result_1.txt
		{
			for (map<string, double>::iterator i = result1.begin(); i != result1.end(); i++) 
			{
				if (c1->symb == (*i).first)
				{
					c1->temp_price = (*i).second;
					c1->cur_port_val = c1->share_num*c1->temp_price; 
				}
			}
		}

		else if (file_no == 1)	// for Result_2.txt
		{
			for (map<string, double>::iterator i = result2.begin(); i != result2.end(); i++)
			{
				if (c1->symb == (*i).first)
				{
					c1->temp_price = (*i).second;
					c1->cur_port_val = c1->share_num*c1->temp_price; 
				}
			}
		}

		c1 = c1->nextptr; // go to next node
	}

	Node *c2 = headptr;	// create another temporary head pointer

	if (headptr != NULL) // check if list not empty.
	{
		Node *prev = 0;			// assign previous pointer as zero
		Node *temp_ptr = NULL;	// temporary pointer
		int swap = 0;			// flag to check if swapped

		// Implementing bubble sorting using the same nodes of doubly linked list
		for (int i = 0; i < size; i++)
		{
			while (c2->nextptr != 0) // checking if tail pointer
			{
				temp_ptr = c2->nextptr;	//assign next pointer to a temporary pointer
				if (c2->cur_port_val < temp_ptr->cur_port_val) // if the portfolio values are smaller than consequent,then swap.
				{
					temp_ptr->prevptr = c2->prevptr;
					c2->prevptr = temp_ptr;
					swap = 1;
					c2->nextptr = temp_ptr->nextptr;

					if (c2->nextptr != NULL) // checking for tail pointer to be NULL
						c2->nextptr->prevptr = c2;
					temp_ptr->nextptr = c2;   // after swapping temptr's next pointer should be current.
					if (prev != 0)				  // if previous pointer to the current is not NULL
						prev->nextptr = temp_ptr;  // then previous's next pointer should be temptr after swapping.
					prev = temp_ptr;               // and for next iteration previous should be temptr.
					if (headptr == c2)       // if headptr is current, then after swapping, headptr should be temptr.
						headptr = temp_ptr;
					if (c2->nextptr == 0)    // if current's next pointer is tailpointer then after swapping, tailpointer should be current.
						tailptr = c2;
				}
				else
				{
					prev = c2;               // if no swapping, then for next iteration, previous pointer should be c2.
					c2 = c2->nextptr;   // increment the node.
				}
			}
			if (swap == 0) // list already sorted, no swapping.
				break;
			else               // start again from head pointer.
			{
				prev = 0;
				c2 = headptr;
				swap = 0;
			}
		}
	}
	else // list is empty
	{
		cout << "\nList is Empty! Can't Sort!\n";
		return false;		
	}
	return true;
}

// BUY shares
void StockAccount::buy_shares(Node *n)
{
	setbal();
	bool flag2 = true, flag3 = true, flag4 = true, flag5 = true;
	double sval1, sval2;
	cashbal = getbal();
	double total_amount;
	cout << "\nEnter the stock symbol : ";
	cin >> stock_symbol;
	
	for (map<string, double>::iterator i = result1.begin(); i != result1.end(); i++) // check in container if symbol present
	{
		if (stock_symbol == (*i).first)
		{
			flag4 = false;
		}
	}

	if (flag4 == true)	// if symbol absent
	{
		cout << "\nSymbol Not found in the database!\n";
		return;
	}

	// if symbol found, continue
	cout << "\nEnter Number of shares to buy : ";
	cin >> shares;
	cout << "\nEnter Maximum limit willing to pay per share : ";
	cin >> max;

	for (map<string, double>::iterator i = result1.begin(); i != result1.end(); i++)
	{
		if (stock_symbol == (*i).first)
		{
			sval1 = (*i).second;
		}
	}

	for (map<string, double>::iterator i = result2.begin(); i != result2.end(); i++)
	{
		if (stock_symbol == (*i).first)
		{
			sval2 = (*i).second;
		}
	}

	file_no = rand() % 2; // randomly select one of the two files

	if (file_no == 0)
	{
		if (max >= sval1) // check if value entered is more than expected
		{
			total_amount = shares * sval1;
			price1 = sval1;
		}
		else	// otherwise, print error
		{
			cout << "\nMaximum limit entered is less than current Share value! Can't buy stock. \n";
			return;
		}
	}

	// for the other file -
	else if (file_no == 1)
	{
		if (max >= sval2)
		{
			total_amount = shares * sval2;
			price1 = sval2;
		}
		else
		{
			cout << "\nMaximum limit entered is less than current Share value! Can't buy stock.\n";
			return;
		}
	}

	// compare amount with current cash balance.
	if (total_amount > cashbal)
	{
		cout << "\n Insufficient Cash Balance!\a\n";
		return;
	}

	// else update cash balance.
	else
	{
		cashbal = cashbal - total_amount;

		cout << "\nYou purchased " << shares << " shares of " << stock_symbol << " for a total of $" << total_amount;

		// write back to a balance file.
		writebalance_file.open("balance_file.txt", std::ios_base::out);
		writebalance_file << cashbal;
		writebalance_file.close();

		// generate the current timestamp using time.h
		time_t raw;
		struct tm space;
		char buffer[80];
		time(&raw);
		localtime_s(&space, &raw);
		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &space);
		std::string str(buffer);

		// write deposit transaction to bank_transaction_history.txt file
		write_bank_history.open("bank_transaction_history.txt", ios::app);
		write_bank_history << endl << left << setw(30) << "Debited to Stock Account.";
		write_bank_history << left << setw(1) << "$";
		write_bank_history << left << setw(15) << total_amount;
		write_bank_history << right << setw(15) << str;
		write_bank_history << right << setw(5) << "$" << cashbal;
		write_bank_history.close();

		// write transaction to stock_transaction_history.txt file
		write_bank_history.open("stock_transaction_history.txt", ios::app);
		write_bank_history << endl << left << setw(7) << "Buy";
		write_bank_history << left << setw(14) << stock_symbol;
		write_bank_history << left << setw(7) << shares;
		write_bank_history << left << setw(14) << price1;
		write_bank_history << left << setw(10) << total_amount;
		write_bank_history << left << setw(15) << str;
		write_bank_history.close();

	//-------updating doubly linked list--------

		
		if (tailptr == NULL&&headptr == NULL) // start from a new node
		{
			// point head and tail to same node
			tailptr = n;
			headptr = n;
			n->symb = stock_symbol;
			n->share_num = shares;
			n->price = price1;
		}

		// else update existing nodes
		else
		{
			Node *cur = headptr;
			while (cur != NULL)
			{
				// if already present, update share number 
				if (stock_symbol == cur->symb)
				{
					cur->share_num = cur->share_num + shares;
					return;
				}
				cur = cur->nextptr;
			}

			// add new node at the end with new values
			Node *copy = tailptr;
			tailptr->nextptr = n;
			tailptr = n;
			tailptr->prevptr = copy;
			n->symb = stock_symbol;
			n->share_num = shares;
			n->price = price1;
		}
		size++; // update size of list.
	}
}

// SELL shares
void StockAccount::sell_shares()
{
	bool flag3 = false, flag4 = true, flag6 = false;
	setbal();
	cashbal = getbal();

	cout << "\nEnter the Symbol of stock to sell : ";
	cin >> stock_symbol;

	Node *curtemp = headptr;

	// chec if symbol present in the portfolio
	while (curtemp != NULL)
	{
		if (stock_symbol == curtemp->symb)
		{
			flag6 = true;
		}
		curtemp = curtemp->nextptr;
	}

	// if not present
	if (flag6 == false)
	{
		cout << "\nSymbol not found in portfolio!\n";
		return;
	}

	// else continue
	cout << "\nEnter the no. of shares to sell : ";
	cin >> shares;

	cout << "\nEnter Minimum limit willing to pay per share : ";
	cin >> min;

	file_no = rand() % 2; // choose from random files 

	if (size > 0) 
	{
		Node *cur = headptr;  // temporary pointer for iteration

		while (cur != NULL)
		{
			if (stock_symbol == cur->symb && shares <= cur->share_num) // if entered limit is correct
			{
				flag3 = true;
				cur->share_num = cur->share_num - shares;

				// for file 1
				if (file_no == 0)
				{
					// get current price for the symbol 
					for (map<string, double>::iterator i = result1.begin(); i != result1.end(); i++)
					{
						if (stock_symbol == (*i).first)
						{
							// if min. limit entered is greater than current share value 
							if (min > ((*i).second))
							{
								cout << "\nMinimum limit entered is greater than current Share value! Can't sell shares.\n";
								return;
							}
							price1 = (*i).second; // update price
						}
					}
				}
				// repeat for file 2
				else if (file_no == 1)
				{
					for (map<string, double>::iterator i = result2.begin(); i != result2.end(); i++)
					{
						
						if (stock_symbol == (*i).first)
						{
							
							if (min > ((*i).second))
							{
								cout << "\nMinimum limit entered is greater than current Share value! Can't sell shares.\n";
								return;
							}
							price1 = (*i).second; 
						}
					}
				}

				//update balance after selling
				cashbal = cashbal + (shares*price1);

				// print the statement 
				cout << "\nYou sold " << shares << " shares of " << stock_symbol << " at rate of " << price1 << " per share\n";

				//generating the current date and timestamp
				time_t raw;
				struct tm space;
				char buffer[80];
				time(&raw);
				localtime_s(&space, &raw);
				strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &space);
				std::string str(buffer);

				// write deposit transaction to bank_transaction_history.txt file
				write_bank_history.open("bank_transaction_history.txt", ios::app);
				write_bank_history << endl << left << setw(30) << "Credited from Stock Account.";
				write_bank_history << left << setw(1) << "$";
				write_bank_history << left << setw(15) << shares*price1;
				write_bank_history << right << setw(15) << str;
				write_bank_history << right << setw(5) << "$" << cashbal;
				write_bank_history.close();

				// write transaction to stock_transaction_history.txt file
				write_bank_history.open("stock_transaction_history.txt", ios::app);
				write_bank_history << endl << left << setw(7) << "Sell";
				write_bank_history << left << setw(14) << stock_symbol;
				write_bank_history << left << setw(7) << shares;
				write_bank_history << left << setw(14) << price1;
				write_bank_history << left << setw(10) << shares*price1;
				write_bank_history << left << setw(15) << str;
				write_bank_history.close();

				//update current balance 
				writebalance_file.open("balance_file.txt", std::ios_base::out);
				writebalance_file << cashbal;
				writebalance_file.close();

				// delete node if shares zero
				if (cur->share_num == 0)
				{
					//if current node is head
					if (cur == headptr)
					{
						if (cur == tailptr)
						{
							headptr = NULL;
							tailptr = NULL;
							delete cur;
							size--;
							return;
						}
						Node *temp = cur->nextptr;
						headptr = cur->nextptr;
						temp->prevptr = NULL;
						delete cur; // delete the node.
						size--;     // update the size.
						return;
					}
					//if current node is tail
					else if (cur == tailptr)
					{
						if (cur == headptr)
						{
							headptr = NULL;
							tailptr = NULL;
							delete cur;
							size--;
							return;
						}
						Node *temp2 = cur->prevptr;
						tailptr = cur->prevptr;
						temp2->nextptr = NULL;
						delete cur;    // delete the node
						size--;        // reduce the size.
						return;
					}
					// if the node is on the middle
					else
					{
						Node *temp3 = cur->prevptr;
						Node *temp4 = cur->nextptr;
						temp3->nextptr = cur->nextptr;  
						temp4->prevptr = cur->prevptr;  
						delete cur;                     // delete current node.
						size--;                         // update the size.
						return;
					}
				}
				return;
			}
			cur = cur->nextptr; // move to next pointer
		}
	}
	if (flag3 == false)
		cout << "\n Number of shares out of range!\n"; 
}

// Save portfolio to a temporary text file
void StockAccount::save_portfolio()
{
	Node *tem = headptr; // temporary instance of linked list node
	write_portfolio.open("portfolio_file.txt", std::ios_base::out);
	while (tem != NULL)
	{
		write_portfolio << tem->symb << "\t" << tem->share_num << "\n";
		tem = tem->nextptr;
	}
	write_portfolio.close();
	// update size of the doubly llist_sizeinked list.
	write_portfolio.open(".txt");
	write_portfolio << size;
	write_portfolio.close();
}

// Get values from portfolio in a doubly linked list 
void StockAccount::get_portfolio()
{
	
	port_file.open("portfolio_file.txt", ios_base::in);
	if (port_file.is_open())
	{
		while (!port_file.eof())
		{ // read from the text file line by line and store in separate parts
			getline(port_file, line);
			stream2 << line;             
			stream2 >> temp1 >> sharetemp1;  
			portfolio.insert(pair<string, int>(temp1, sharetemp1)); 
			stream2.clear();
		}
	}
	port_file.close();

	for (map<string, int>::iterator i = portfolio.begin(); i != portfolio.end(); ++i) // iterating through the container
	{
		Node *current = new Node();
		current->symb = (*i).first;
		current->share_num = (*i).second;

// first new node
		if (prev == NULL)
		{
			current->prevptr = NULL;
			current->nextptr = NULL;
			headptr = current;
			tailptr = current;
		}
//update list at the end
		else
		{
			current->prevptr = prev;
			prev->nextptr = current;
		}
		prev = current;
		tailptr = prev;
	}
	Node *cur = headptr;

	while (cur != NULL)
	{
		file_no = rand() % 2;
		// for file 1
		if (file_no == 0)
		{
			for (map<string, double>::iterator i = result1.begin(); i != result1.end(); i++)
			{
				if (cur->symb == (*i).first) // compare the symbol name 
				{
					cur->temp_price = (*i).second;                // update price per share
					cur->cur_port_val = cur->share_num*cur->temp_price; // calculate temp node portfolio value
				}
			}
		}
		// repeat these steps for file 2
		else if (file_no == 1)
		{
			for (map<string, double>::iterator i = result2.begin(); i != result2.end(); i++)
			{
				if (cur->symb == (*i).first)
				{
					cur->temp_price = (*i).second;               
					cur->cur_port_val = cur->share_num*cur->temp_price; 
				}
			}
		}
		port_value = port_value + cur->cur_port_val; // update potfolio value
		cur = cur->nextptr; // move to next node
	}
	port_value += cashbal; // update portfolio value

}

// Get portfolio value
void StockAccount::get_port_value()
{
	string line2, temp;
	//open port_value text file and get the historical data from it and save it in two arrays.
	portval_file.open("port_value.txt", ios_base::in);
	if (portval_file.is_open())
	{
		while (!portval_file.eof())
		{
			getline(portval_file, line2);
			stream3 << line2;
			stream3 >> port_array[count] >> time_stamp[count] >> temp; // storing porfolio values in port_array.
			if (time_stamp[count] == "") // retrieve corresponding date in time_stamp
				continue;
			else
			{
				time_stamp[count].append(" ");
				time_stamp[count].append(temp); // append time to it.
			}
			count++; // increment counter for both arrays.
			stream3.clear();
		}
	}
	portval_file.close();
}

// Update portfolio value and timestamp
void StockAccount::saveport_value()
{
	//generating the current date and timestamp
	time_t raw;
	struct tm space;
	char buffer[80];
	time(&raw);
	localtime_s(&space, &raw);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &space);
	std::string str(buffer);

	if (size == 0)
		port_value = cashbal; // update cash balance if portfolio empty.
	write_portfolio.open("port_value.txt.", ios::app);
	write_portfolio << port_value << "  " << str << endl;
	write_portfolio.close();
}

// Plot MATLAB graph for portfolio value variation
void StockAccount::plot_graph()
{
	// pointer to the engine
	Engine *N;
	N = engOpen(NULL);
	// if matlab engine is not opened.
	if (N == NULL)
	{
		cout << "Error." << endl;
		exit(1);
	}
	/*cout << "Potfolio Value" << setw(15) << "Date & Time" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << port_array[i] << setw(30) << time_stamp[i] << endl;
	}*/
	// create mxArray and copy your c++ double array of portfolio value into it.
	cout << "\n Plotting MATLAB graph. Please wait...";
	mxArray *M;
	M = mxCreateDoubleMatrix(1, count, mxREAL); // creat a matrix
	memcpy((void *)mxGetPr(M), (void *)port_array, count * sizeof(double)); // allocate memory space
	engPutVariable(N, "set", M);
	engEvalString(N, "plot(set);"); // plot the value
	engEvalString(N, "title('Change In Portfolio Value');");
	mxDestroyArray(M);// deallocate matrix M
}

// Print transaction history
void StockAccount::print_history()
{
	cout << endl << left << setw(7) << "Transaction";
	cout << left << setw(14) << "Symbol";
	cout << left << setw(7) << "Shares";
	cout << left << setw(14) << "Price per Share($)";
	cout << left << setw(10) << "Value($)";
	cout << left << setw(15) << "Timestamp" << endl;

	file1.open("stock_transaction_history.txt", ios::app); // open history file

	if (file1.is_open())
	{
		while (!file1.eof())
		{
			while (getline(file1, line2))
				cout << line2 << "\n";
		}
	}
	file1.close();  // close the file
}
