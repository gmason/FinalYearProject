/*
 * symbol.h
 *
 *  Created on: Nov 5, 2012
 *      Author: gtgmason
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_
#include <string>
using std::string;

class symbol {
	public: string wIssueSymbol;
	public: double wTradePrice;
	public: int wTradeVolume;
	public: int wTradeCount;
	public: void print();
public:
	symbol(string, double, int, int);
	symbol();
	symbol(const symbol&);
	symbol& operator =(const symbol& a);
	virtual ~symbol();
};
#endif /* SYMBOL_H_ */

