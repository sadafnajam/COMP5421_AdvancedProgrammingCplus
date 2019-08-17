//
//  Command.h
//  A2
//
//  Created by Sadaf Najam on 2019-06-20.
//  Copyright © 2019 Sadaf Najam. All rights reserved.
//

#ifndef Command_h
#define Command_h
#include<string>
#include<list>
#include "Command.h"
using std::string;
class Command {
private:
	string command_line; // Stores supplied command line
	bool status; // Stores validity of this command
	string symbol; // Stores the command symbol
	string address1; // Stores address 1
	string address2; // Stores address 2
public:
	Command(string); // Ctor, sets and parses command line
	void parse(string); // Resets and parses command line 
	string getSymbol() const; // Returns the command symbol
	string getAddress1() const; // Returns address 1
	string getAddress2() const; // Returns address 2
	bool getStatus() const; // Returns whether command line syntax is valid
	void setStatus(bool sts); // Sets status of this command
};
#endif