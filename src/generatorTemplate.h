/*
 * generatorTemplate.h
 *
 *  Created on: Nov 13, 2012
 *      Author: gtgmason
 */

#ifndef GENERATORTEMPLATE_H_
#define GENERATORTEMPLATE_H_
#include <string>
using std::string;

class generatorTemplate {
	public: string wIssueSymbol;
	public: double wBaseTradePrice;
	public: double wTradePriceChange;
	public: int wTradeVolume;
	public: int wBaseTradeCount;
	public: int wTradeCountChange;
	public: int quotesToProduce;
	public: void print();
public:
	generatorTemplate(string, double, double, int, int, int, int);
	generatorTemplate();
	generatorTemplate(const generatorTemplate&);
	generatorTemplate& operator =(const generatorTemplate& a);
	virtual ~generatorTemplate();
};
#endif
