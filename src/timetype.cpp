/*
 * timetype.cpp
 *
 *  Created on: Mar 11, 2013
 *      Author: gtgmason
 */

#include "timetype.h"
#include "iostream.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

timetype::timetype(int _hours, int _minutes, int _seconds)	{
	hours = _hours;
	minutes = _minutes;
	seconds = _seconds;
}

timetype::~timetype() {
	// TODO Auto-generated destructor stub
}

timetype::timetype() {
	hours = 0;
	minutes = 0;
	seconds = 0;
}

void timetype::add()
{
	seconds++;

	if (seconds > 59)
	{
		minutes++;
		seconds = 0;
	}

	if (minutes > 59)
	{
		hours++;
		minutes = 0;
	}
}

string timetype::print()
{
	stringstream ss;
	if (hours < 10)
		ss << "0"<< hours << ":";
	else
		ss << hours << ":";

	if (minutes < 10)
		ss << "0"<< minutes << ":";
	else
		ss << minutes << ":";

	if (seconds < 10)
		ss << "0"<< seconds;
	else
		ss << seconds;

	string rtn_string = ss.str();
	return rtn_string;
}


