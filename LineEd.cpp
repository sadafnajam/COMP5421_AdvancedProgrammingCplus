//
//  LineEd.cpp
//  A2
//
//  Created by Sadaf Najam on 2019-06-20.
//  Copyright © 2019 Sadaf Najam. All rights reserved.
//

#include "LineEd.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::getline;
using std::cin;
using std::cout;
using std::endl;
using std::advance;
using std::size_t;

//Ctor implementation

LineEd::LineEd(string filename) : filename(filename) {
}

//Runner implementation for command mode

void LineEd::run() {
	if (!filename.empty()) {
		ifstream fin(filename.c_str());
		string line;
		while (getline(fin, line)) {
			buffer.push_back(line);
		}
		currentAddress = buffer.size();
		string msg = currentAddress > 1 ? " lines" : " line";
		cout << "\"" << filename << "\" " << currentAddress << msg << endl;
		cout << "Entering command mode." << endl;
	}
	else {
		currentAddress = 0;
		cout << "\"?\" " << "[New file]" << endl;
		cout << "Entering command mode." << endl;
		while (true) {
			inCommandMode();
		}
	}
}

// cout ? to input command

void LineEd::inCommandMode() {
	string command;
	cout << "? ";
	getline(cin, command);
	runCommand(command);
}

// Runner implementation of to validate and parse input command

void LineEd::runCommand(string str) {
	//cout<<currentAddress<<"-"<<buffer.size()<<endl;
	isValidCmd = true;
	commandError = "";
	Command cmd(str);
	cmd.parse(str);
	//cout<<cmd.getSymbol()<<" "<<cmd.getAddress1()<<" "<<cmd.getAddress2()<<endl;
	if (!isValidSymbol(cmd.getSymbol().at(0))) {
		commandError = "bad command: " + std::string(" ") + std::string(cmd.getSymbol());
		isValidCmd = false;
	}
	else if ((cmd.getAddress1() != "." && cmd.getAddress1() != "$" && (!isValidNumber(cmd.getAddress1())))) {
		commandError = "Bad address 1: " + std::string(" ") + std::string(cmd.getAddress1());
		isValidCmd = false;
	}
	else if ((cmd.getAddress2() != "." && cmd.getAddress2() != "$" && (!isValidNumber(cmd.getAddress2())))) {
		commandError = "Bad address 2: " + std::string(" ") + std::string(cmd.getAddress2());
		isValidCmd = false;
	}
	if (isValidCmd) {
		cmd.setStatus(true);
		int x = cmd.getAddress1() == "." ? currentAddress : (cmd.getAddress1() == "$" ? buffer.size() : stoi(cmd.getAddress1()));
		int y = cmd.getAddress2() == "." ? currentAddress : (cmd.getAddress2() == "$" ? buffer.size() : stoi(cmd.getAddress2()));
		if (x>y) {
			int temp = x;
			x = y;
			y = (temp > buffer.size()) ? buffer.size() : temp;
		}
		//cout<<x <<":"<<y<<endl;
		commandOperations(cmd.getSymbol().at(0), x, y);
	}
	else {
		cmd.setStatus(false);
		cout << commandError << endl;
	}
}

// boolean function to check validity of symbols

bool LineEd::isValidSymbol(char symbol) {
	char validCommands[13] = { 'a', 'i', 'v', 'd', 'x' ,'j', 'p', 'c', 'u', 'n', 'g', 'w', 'q' };
	int size = (sizeof(validCommands) / sizeof(char)), count = 0;
	while (count < size) {
		if (validCommands[count] == symbol)
			return true;
		count++;
	}
	return false;
}

// boolean function to check validity of numbers

bool LineEd::isValidNumber(const string &num) {
	for (auto itr = num.begin(); itr != num.end(); itr++)
		if (!isdigit(*itr))
			return false;
	return true;
}

// Master opeartor to run individual LineEd operations

void LineEd::commandOperations(char csymbol, int x, int y) {
	if (csymbol == 'a') {
		cout << "Entering input mode." << endl;
		appends();
	}
	else if (csymbol == 'i') {
		cout << "Entering input mode." << endl;
		inserts(x);
	}
	else if (csymbol == 'v') {
		if (clipboard.size() != 0) {
			pastes(x);
		}
	}
	else if (csymbol == 'd') {
		deletes(x, y);
	}
	else if (csymbol == 'x') {
		cuts(x, y);
	}
	else if (csymbol == 'j') {
		joins(x, y);
	}
	else if (csymbol == 'p') {
		y = (y > buffer.size()) ? buffer.size() : y;
		prints(x, y);
	}
	else if (csymbol == 'c') {
		changes(x, y);
	}
	else if (csymbol == 'u') {
		up();
	}
	else if (csymbol == 'n') {
		down();
	}
	else if (csymbol == 'g') {
		goes(x);
	}
	else if (csymbol == 'w') {
		writes();
	}
	else if (csymbol == 'q') {
		quits();
	}
}

/*
* Ignores line range if any. 
* Appends text into the buffer after last line. 
* The current line is set to the last line
*/

void LineEd::appends() {
	list<string>::iterator itr = buffer.begin();
	advance(itr, buffer.size());
	string str;
	while (getline(cin, str)) {
		if (str.compare(".") == 0) {
			currentAddress = buffer.size();
			cout << "Entering command mode." << endl;
			break;
		}
		buffer.insert(itr, str);
	}
	cin.clear();
}

/*
* Ignores line address 2, if any.
* Inserts text into the buffer at given line number.
* The current address is set to the last line entered.
*/

void LineEd::inserts(int x) {
	list<string>::iterator itr = buffer.begin();
	currentAddress = (x == 0) ? x : x - 1;
	advance(itr, currentAddress);
	string str;
	while (getline(cin, str)) {
		if (str.compare(".") == 0) {
			cout << "Entering command mode." << endl;
			break;
		}
		buffer.insert(itr, str);
		currentAddress++;
	}
	cin.clear();
}

/*
* Ignores line address 2, if any. 
* Pastes text from the clipboard into the buffer at given line number.
* The current address is set to the last line pasted.
*/

void LineEd::pastes(int x) {
	list<string>::iterator itr = buffer.begin();
	currentAddress = (x == 0) ? x : x - 1;
	advance(itr, currentAddress);
	string str;
	for (vector<string>::iterator itp = clipboard.begin(); itp != clipboard.end(); itp++) {
		str = *itp;
		buffer.insert(itr, str);
		currentAddress++;
	}
}

/*
* Deletes the line range x through y from the buffer. 
* If there is a line after the deleted line range, then the current address is set to that line. 
*/

void LineEd::deletes(int x, int y) {
	currentAddress = (buffer.size() > y) ? x : (x - 1);
	currentAddress = currentAddress >0 ? currentAddress : currentAddress + 1;
	list<string>::iterator itr = buffer.begin();
	advance(itr, x - 1);
	int index = x;
	while (index <= y) {
		buffer.erase((next(itr, y - index)));
		index++;
	}
}

/*
* Cuts the line range x through y from the buffer into the clipboard. 
* If there is a line after the cut line range, then the current address is set to that line; 
*/

void LineEd::cuts(int x, int y) {
	list<string>::iterator itr = buffer.begin();
	advance(itr, x - 1);
	clipboard.clear();
	int index = x;
	while (index <= y) {
		clipboard.push_back(*(itr));
		itr = next(itr);
		index++;
	}
	deletes(x, y);
}

/*
* Joins the text from the specified line range together on one line at address x, concatenating the characters in the lines. 
* Line x becomes the current line.
*/

void LineEd::joins(int x, int y) {
	list<string>::iterator itr = buffer.begin();
	currentAddress = x;
	advance(itr, x - 1);
	int index = x;
	while (index < y) {
		string accum = *(itr++);
		(*itr++) = accum + *(itr--);
		buffer.erase(itr++);
		index++;
	}
}

/*
* Prints the line range x through y without affecting the current line address.
*/

void LineEd::prints(int x, int y) {
	//cout<<buffer.size()<<endl;
	if (buffer.size() != 0) {
		list<string>::iterator itr = buffer.begin();
		advance(itr, x - 1);
		int index = x;
		while (index <= y) {
			cout << index << ((currentAddress != index) ? ": " : "> ") << *itr << endl;
			itr++;
			index++;
		}
	}
	else {
		if (clipboard.size() == 0) {
			cout << "File empty. Must use one of I,A,Q commands" << endl;
		}
		else {
			cout << "File empty. Must use one of I,A,Q,V commands" << endl;
		}
	}
}

/*
* Prompts for and reads the text to be changed, and then prompts for and reads the replacement text. 
* Searches each line in the line range for an occurrence of the specified string and changes all matched strings to the replacement text.
*/

void LineEd::changes(int x, int y) {
	string from;
	string to;
	size_t match = 0;
	cout << "change? ";
	getline(cin, from);
	cout << "    to? ";
	getline(cin, to);
	list<string>::iterator itr = buffer.begin();
	advance(itr, x - 1);
	int index = x;
	int cl = x;
	while (index <= y) {
		match = 0;
		while (true) {
			match = (*itr).find(from, match);
			if (string::npos == match) break;
			(*itr).replace(match, from.length(), to);
			match = match + to.length();
			cl++;
		}
		itr++;
		index++;
	}
	currentAddress = cl;
}

/*
* Ignores line range, if any. 
* Moves the current line up by one line provided that there is a line above the current line.
*/

void LineEd::up() {
	currentAddress--;
	if (currentAddress < 1) {
		cout << "BOF reached" << endl;
		currentAddress = 1;
	}
	else {
		prints(currentAddress, currentAddress);
	}
}

/*
* Ignores line range, if any. 
* Moves the current line down by one line provided that there is a line after the current line. 
*/

void LineEd::down() {
	currentAddress++;
	if (currentAddress > buffer.size()) {
		cout << "EOF reached" << endl;
		currentAddress = buffer.size();
	}
	else {
		prints(currentAddress, currentAddress);
	}

}

/*
* Ignores line address 2, if any. 
* Goes to the specified line x, meaning that it sets the current line to x and prints it.
*/

void LineEd::goes(int x) {
	currentAddress = x;
	prints(currentAddress, currentAddress);
}

/*
* Ignores line range, if any. 
* If there is a file associated with the buffer, it prompts the user asking whether it is OK to replace that file with the buffer contents. 
* If the answer is negative, or there is no file associated with the buffer, it prompts the user for the name of a file to save the buffer to.
*/

void LineEd::writes() {
	string choice;
	if (!filename.empty()) {
		cout << "Save changes to the file: " << filename << " (y or n)?" << endl;
		while (cin >> choice) {
			if (choice == "y") {
				cin.ignore();
				break;
			}
			else {
				break;
			}
		}
	}
	if (choice == "n" || filename.empty()) {
		cout << "Enter the name of a file to write to: ";
		cin >> filename;
		cin.ignore();
	}
	ofstream output;
	output.open(filename.c_str());
	for (list<string>::iterator itr = buffer.begin(); itr != buffer.end(); itr++) {
		output << *itr << endl;
	}
	output.close();
	currentAddress = buffer.size();
	cout << buffer.size() << std::string((buffer.size() > 1) ? " lines" : " line") + " written to file \"" << filename << "\"" << endl;
}

/*
* Ignores line range, if any. Quits LineEd. 
* Before quitting, however, it gives the user a last chance to save the buffer. 
* If the user takes the chance, it simulates the w command, and then quits; otherwise, it quits, discarding buffer contents.
*/

void LineEd::quits() {
	cout << "There are unsaved changes. \nDo you wish to save the changes(y or n)?" << endl;
	string choice;
	while (cin >> choice) {
		if ("y" == choice) {
			writes();
			cout << "bye" << endl;
			break;
		}
		else if ("n" == choice) {
			cin.ignore();
			break;
		}
	}
}