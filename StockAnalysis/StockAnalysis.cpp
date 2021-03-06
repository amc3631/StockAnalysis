// Author: Michael Boisvert

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <iomanip>


using namespace std;

// input and output variables
ifstream inp;
ofstream outp;

// structure to hold data
struct dataSet {
	string date;
	float close;
	int volume;
	float open;
	float high;
	float low;
	float avg;
};

void LocalMax(int numLines, dataSet stockData[]) {
	// find and print local maximums

	bool maxExists = 0;

	for (int j = 1; j < numLines - 2; j++) {

		if ((stockData[j - 1].close < stockData[j].close) && (stockData[j].close > stockData[j + 1].close)) {

			if (maxExists == 0) {
				maxExists = 1;
				outp << "Local maximums: " << endl;
				outp << endl;
				outp << "date:	    close:	 volume:	  open:	 high:   low:" << endl;
			}

			// if date is formatted differently, add extra whitespace to improve readability
			outp << stockData[j].date;
			if (stockData[j].date.length() < 10) {
				outp << "	";
			}
			outp << "  " << stockData[j].close << "	 ";
			outp << setfill('0') << setw(6) << stockData[j].volume;
			outp << "		  " << stockData[j].open << "	  " << stockData[j].high << "  " << stockData[j].low << endl;

		}

	}

	if (maxExists == 0) {
		outp << "Error: no maximums found" << endl << endl;
	}

	outp << endl << endl;
}

void LocalMin(int numLines, dataSet stockData[]) {
	// find and print local minimums

	bool minExists = 0;

	for (int k = 1; k < numLines - 2; k++) {

		if ((stockData[k - 1].close < stockData[k].close) && (stockData[k].close > stockData[k + 1].close)) {
			if (minExists == 0) {
				minExists = 1;
				outp << "Local minimums: " << endl;
				outp << endl;
				outp << "date:	    close:	 volume:	  open:	 high:   low:" << endl;
			}

			// if date is formatted differently, add extra whitespace to improve readability
			outp << stockData[k].date;
			if (stockData[k].date.length() < 10) {
				outp << "	";
			}
			outp << "  " << stockData[k].close << "	 ";
			outp << setfill('0') << setw(6) << stockData[k].volume;
			outp << "		  " << stockData[k].open << "	  " << stockData[k].high << "  " << stockData[k].low << endl;

		}

	}

	if (minExists == 0) {
		outp << "Error: no minimums found" << endl << endl;
	}
}

void avgLocalMax(int numLines, dataSet stockData[]) {
	// find and print local maximums for moving average data

	bool maxExists = 0;

	for (int j = 1; j < numLines - 2; j++) {

		if ((stockData[j - 1].avg < stockData[j].avg) && (stockData[j].avg > stockData[j + 1].avg)) {

			if (maxExists == 0) {
				maxExists = 1;
				outp << "Moving average maximums: " << endl;
				outp << endl;
				outp << "date:	    close:	 volume:	  open:	 high:   low:" << endl;
			}

			// if date is formatted differently, add extra whitespace to improve readability
			outp << stockData[j].date;
			if (stockData[j].date.length() < 10) {
				outp << "	";
			}
			outp << "  " << stockData[j].close << "	 ";
			outp << setfill('0') << setw(6) << stockData[j].volume;
			outp << "		  " << stockData[j].open << "	  " << stockData[j].high << "  " << stockData[j].low << endl;

		}

	}

	if (maxExists == 0) {
		outp << "Error: no maximums found" << endl << endl;
	}

	outp << endl << endl;
}

void avgLocalMin(int numLines, dataSet stockData[]) {
	// find and print local minimums for moving average data

	bool minExists = 0;

	for (int k = 1; k < numLines - 2; k++) {

		if ((stockData[k - 1].avg < stockData[k].avg) && (stockData[k].avg > stockData[k + 1].avg)) {
			if (minExists == 0) {
				minExists = 1;
				outp << "Moving average minimums: " << endl;
				outp << endl;
				outp << "date:	    close:	 volume:	  open:	 high:   low:" << endl;
			}

			// if date is formatted differently, add extra whitespace to improve readability
			outp << stockData[k].date;
			if (stockData[k].date.length() < 10) {
				outp << "	";
			}
			outp << "  " << stockData[k].close << "	 ";
			outp << setfill('0') << setw(6) << stockData[k].volume;
			outp << "		  " << stockData[k].open << "	  " << stockData[k].high << "  " << stockData[k].low << endl;

		}

	}

	if (minExists == 0) {
		outp << "Error: no minimums found" << endl << endl;
	}
}

int main()
{
	// open files for reading and writing
	inp.open("data.txt");
	outp.open("LocalExtremes.txt");

	// round data to two decimal places
	outp << fixed << setprecision(2);

	// count number of lines in file in order to dynamically allocate memory
	int numLines = 0;
	while (!inp.eof()) {
		string buffer;
		getline(inp, buffer);
		numLines++;
	}

	if (numLines == 0) {
		outp << "Error: empty data file";
		return 0;
	}

	// allocate memory
	dataSet* stockData = new dataSet[numLines];

	// return to top of file
	inp.clear();
	inp.seekg(0, inp.beg);

	// skip first line containing column labels
	string skip;
	getline(inp, skip);

	// read data and calculate moving average
	int i = 0;
	float sum = 0;
	while (i < numLines - 1) {
		inp >> stockData[i].date >> stockData[i].close >> stockData[i].volume >> stockData[i].open >> stockData[i].high >> stockData[i].low;
		sum += stockData[i].close;
		if (19 < i) {
			sum -= stockData[i - 3].close;
		}
		if (19 > i) {
			stockData[i].avg = sum;
		}
		else {
			stockData[i].avg = sum / 20;
		}
		i++;

	}

	// print local maximums
	LocalMax(numLines, stockData);

	// print local minimums
	LocalMin(numLines, stockData);

	outp << endl << endl;
	outp << "Local extremes based on calculated moving average data: " << endl << endl;

	// print average local maximums
	avgLocalMax(numLines, stockData);

	// print average local minimums
	avgLocalMin(numLines, stockData);

	cout << "Local extreme analysis complete. See LocalExtremes file for results." << endl;

	inp.close();
	outp.close();
	return 0;
}


