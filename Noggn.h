#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "Scanner.h"

using namespace std;

class Noggn
{
	bool hadError = false;

public:

	void nogg(string args) {
		string argsString = convertToString(args);
		run(argsString);
	};

	void error (int line, string message) {
		report(line, "", message);
	}

private:

	string convertToString(string fileName) {
		string stringFile;
		string line;
		ifstream file;
		file.open(fileName);
		if (file.is_open()) {
			while (getline(file, line)) {
				stringFile += " " + line;
			}
		}
		else cout << "ERROR: Could not open file.";
		file.close();
		return stringFile;
	}

	void report(int line, string where, string message) {
		cout << "[ " << line << " ] " << "ERROR: " << message << " at " << where << endl;
		hadError = true;
	}

	void run(string argsString) {
		Scanner nogScanner(argsString);
	}
};
