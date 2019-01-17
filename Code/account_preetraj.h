/* 
NAME : PREETRAJ 
DATE : 12/18/2017
PROJECT : ACCOUNT MANAGEMENT SYSTEM
FILE : BASE CLASS .H FILE 
*/

#pragma once
#ifndef ACCOUNT_PREETRAJ
#define ACCOUNT_PREETRAJ

class Account	// abstract base class - Account
{
protected:
	double cashbal;	// cashbal = cash balance, accessible to derived classes

public:
	virtual double getbal() = 0;	// get cash balance
	virtual void setbal() = 0;		// set cash balance
	virtual void print_history() = 0;	// Print history of transaction	
};

#endif