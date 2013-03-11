/*
 * timetype.h
 *
 *  Created on: Mar 11, 2013
 *      Author: gtgmason
 */

#ifndef TIMETYPE_H_
#define TIMETYPE_H_
#include <string>
#include <vector>
#include "iostream.h"
#include <fstream>
#include <sstream>
using std::string;
using std::vector;

class timetype	{
	public: int hours;
	public: int minutes;
	public: int seconds;
	public: string print();
	public: void add();
public:
	timetype(int, int, int);
	timetype();
	virtual ~timetype();
};
#endif /* TIME_H_ */
