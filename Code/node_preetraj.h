/*
NAME : PREETRAJ
DATE : 12/18/2017
PROJECT : ACCOUNT MANAGEMENT SYSTEM
FILE : NODE CLASS .H FILE FOR LINKED LIST
*/
#pragma once

#include<iostream>	// Standard I/O library
#include<string>	// Standard string operations library

// include other class files
#include "account_preetraj.h"
#include "stock_account_preetraj.h"

using namespace std;

#ifndef NODE_PREETRAJ_H
#define NODE_PREETRAJ_H

class Node
{
	friend class StockAccount;
public:
	Node()
	{
		this->nextptr = NULL;
		this->prevptr = NULL;
	}
private:
	
	string symb;		// stock symbol
	int share_num;		// number of shares

	double price;      // price per share 
	double temp_price; // temporary price per share for sorting
	double cur_port_val;         //  current value of a portfolio node 

// doubly linked list parameters - 
	Node *nextptr;	// Next pointer of the node
	Node *prevptr;	// Previous pointer of the node
};

#endif

