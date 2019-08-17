//
//  Command.cpp
//  A2
//
//  Created by Sadaf Najam on 2019-06-20.
//  Copyright © 2019 Sadaf Najam. All rights reserved.
//

#include "Command.h"
#include <cctype>

using std::string;

//Ctor

Command::Command(string command_line) : command_line(command_line), address1(""), address2("") {}

/*
* Member command parse function
*/

void Command::parse(string command_line) {
	for (string::iterator it = command_line.begin(); it != command_line.end(); ++it) {
		if ((*it == ' ') || (*it == '\t') || (*it == '\r')) {
			command_line.erase(it);
		}
	}
	if (command_line.empty()) {
		symbol = "p";
		address1 = address2 = ".";

	}
	else {
		size_t pos = command_line.find(',');
		if (pos != string::npos) {
			string preComma = command_line.substr(0, pos);
			string postComma = command_line.substr((pos + 1), command_line.length());
			if (preComma.length()) {
				if (!isdigit(preComma.at(0)) && preComma.at(0) != '.' && preComma.at(0) != ',' && preComma.at(0) != '$') {
					if (preComma.length() == 1) {
						symbol = std::tolower(preComma.at(0));
						address1 = ".";
					}
					else {
						symbol = std::tolower(preComma.at(0));
						address1 = preComma.substr(1, preComma.length());
					}
				}
				else {
					symbol = "p";
					address1 = preComma;
				}
			}
			else {
				symbol = "p";
				address1 = ".";
			}
			address2 = postComma.length() ? postComma : address1;
			if (symbol == "-" && isdigit(address1.at(0)) && isdigit(address2.at(0))) {
				symbol = "p";
				address1 = "1";
				address2 = "$";
			}

		}
		else {
			if (!isdigit(command_line.at(0)) && command_line.at(0) != '.' && command_line.at(0) != ',' && command_line.at(0) != '$') {
				symbol = std::tolower(command_line.at(0));
				if (command_line.length() == 1) {
					address1 = address2 = ".";
				}
				else {
					address1 = address2 = command_line.substr(1, command_line.length());
				}
				if (symbol == "-" && isdigit(address1.at(0)) && isdigit(address2.at(0))) {
					symbol = "p";
					address1 = "1";
					address2 = "$";
				}
			}
			else {
				symbol = "p";
				address1 = address2 = command_line;
			}
		}
	}

}

/*
* getters and setters
*/

string Command::getSymbol() const {
	return symbol;
}

string Command::getAddress1() const {
	return address1;
}

string Command::getAddress2() const {
	return address2;
}

bool Command::getStatus() const {
	return status;
}

void Command::setStatus(bool sts) {
	status = sts;
}