//
//  Lineed.h
//  A2
//
//  Created by Sadaf Najam on 2019-06-20.
//  Copyright © 2019 Sadaf Najam. All rights reserved.
//

#ifndef LineEd_h
#define LineEd_h
#include <list>
#include <vector>
#include <string>
#include <iostream>

#include "Command.h"

using std::list;
using std::vector;
using std::string;


class LineEd {
private:

	string filename; // filename of string type
	int currentAddress; // Storage for line address
	list<string> buffer; // Buffer list container of type string
	vector<string> clipboard; // Storage to cut and paste text
	bool isValidSymbol(char); // private boolean to check if symbol is valid
	bool isValidNumber(const string &str); // private boolean to check if number is valid
	bool isValidCmd { true }; // boolean set to 1 to check command validity
	string commandError; // Storage for command error
	void commandOperations(char, int, int); // master command operation

public:

	LineEd(string); //Ctor

	void run(); // Runner to exceute command mode
	 
	void inCommandMode(); // To take input command

	void runCommand(string); // Runner to validate and execute entered command

	void appends(); // Appends text into the buffer after last line

	void inserts(int); // Inserts text into the buffer at given line number

	void pastes(int); // Pastes text from the clipboard into the buffer at given line number

	void deletes(int, int); // Deletes the line range passed from the buffer

	void cuts(int, int); // Cuts the line range passed from the buffer into the clipboard

	void joins(int, int); // Joins the text from given line range in one line at passed line number

	void prints(int, int); // Prints the line range passed

	void changes(int, int); // prompts for and reads the text to be changed and replacement text

	void up(); // Moves the current line up by one line

	void down(); // Moves the current line down by one line

	void goes(int); // Goes to the specified line number

	void writes(); // Writes the file with buffer content
	 
	void quits(); // Quits editor

};
#endif