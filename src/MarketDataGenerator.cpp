//============================================================================
// Name        : MarketDataGenerator.cpp
// Author      : Gareth Mason
// Version     :
// Copyright   : 
// Description : Base class of marketDataGenerator project, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <list>
#include "symbol.h"
#include "generatorTemplate.h"
using namespace std;

string subStringConverter (string startField, string line)
{
	int start, end;
	start = line.find(startField, 0);
	end = line.find(' ', start);
    string returnString = line.substr(start+startField.length(), end);

	return returnString;
}

int LengthOfFile (string filename)
{
	string line;
    int numLines = 0;

    ifstream symFile (filename.c_str());
    ofstream processedFile;

    char buf[256];
    snprintf(buf, sizeof buf, "%s%s", filename.c_str(), "_processed");
    processedFile.open(buf);

    while ( getline (symFile, line) )
    {
  	  if (string::npos != line.find("wTradePrice"))
  	  {
  	   ++numLines;
  	  }
    }
    symFile.clear();
    symFile.seekg(0);
	symFile.close();

	return numLines;
}

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void FileParser (string filename, int arrLength, symbol *arr[ ]) {
  string line;
  int numLines = arrLength;

  ifstream symFile (filename.c_str());
  ofstream processedFile;

  char buf[256];
  snprintf(buf, sizeof buf, "%s%s", filename.c_str(), "_processed");
  processedFile.open(buf);

  string symFileLine [numLines];
  symbol *symbolsInFile [numLines];

  int n = 0;

  while ( getline (symFile, line) )
  {
	  if (string::npos != line.find("wTradePrice"))
	  {
		  double symPrice;
		  int symVolume, tradeCount;
		  symFileLine[n] = line;

		  // set the symbol
		  int i = line.find(".NSDQ", 0);
		  string symName = line.substr(0, i);

		  // set the trade price
		  stringstream convertPrice (subStringConverter("wTradePrice F64=", line));
		  if ( !(convertPrice >> symPrice) )
		      symPrice = 0;

		  // set the trade volume
		  stringstream convertVolume(subStringConverter("wTradeVolume U32=", line));
		  if ( !(convertVolume >> symVolume) )
			  symVolume = 0;

		  // set the trade count
		  stringstream convertCount(subStringConverter("wTradeCount U32=", line));
		  if ( !(convertCount >> tradeCount) )
			  tradeCount = 0;

		  symbolsInFile[n] = new symbol(symName, symPrice, symVolume, tradeCount);
		  processedFile << symFileLine[n] << endl;
		  n++;

	  }
  }

  for (int i = 0; i < numLines; i++)
	  arr[i] = symbolsInFile[i];

  symFile.close();
  processedFile.close();
}

// input files are standard wombat symbol files (with all fields)
// Before inputting please run the following in vi
// :%s/_^...._^/ /g
// :%s/_^...._^/ /g
// :%s/<tab>/ /g
int main () {
  srand(time(0));
  string firstDayfilePath = "/Users/gtgmason/Documents/workspace/symfiles/sorted/tvitch4mc.sym_20121101";
  string secondDayfilePath = "/Users/gtgmason/Documents/workspace/symfiles/sorted/tvitch4mc.sym_20121105";
  int linesFirstDay = LengthOfFile(firstDayfilePath.c_str());
  int linesSecondDay = LengthOfFile(secondDayfilePath.c_str());
  symbol* firstDay[linesFirstDay];
  symbol* secondDay[linesSecondDay];
  FileParser(firstDayfilePath.c_str(), linesFirstDay, firstDay);
  FileParser(secondDayfilePath.c_str(), linesSecondDay, secondDay);

 std::list<string> symbolsToCompare;

  int longerFile;
  if (linesSecondDay > linesFirstDay)
  {
	  longerFile = linesSecondDay;
	  for (int i = 0; i < linesSecondDay; i++)
	  {
		  for (int j = 0; j < linesFirstDay; j++)
		  {
			  if (secondDay[i]->wIssueSymbol.compare(firstDay[j]->wIssueSymbol) == 0)
			  {
				  symbolsToCompare.push_back(secondDay[i]->wIssueSymbol);
			  }
		  }
	  }
  }
  else
  {
	  longerFile = linesFirstDay;
	  for (int i = 0; i < linesFirstDay; i++)
	  {
		  for (int j = 0; j < linesSecondDay; j++)
		  {
			  if (firstDay[i]->wIssueSymbol.compare(secondDay[j]->wIssueSymbol) == 0)
			  {
				  symbolsToCompare.push_back(secondDay[j]->wIssueSymbol);
			  }
		  }
	  }
  }

  std::list<symbol> comparedSymbols;
  list<string>::iterator it = symbolsToCompare.begin();

  generatorTemplate* comparedSymbol;
  symbol* firstDaySymbol;
  if (symbolsToCompare.size() >= 0)
  {
	  for (int i = 0; i < symbolsToCompare.size(); i++)
	  {
		  string symLookingFor = (*it++).c_str();
		  firstDaySymbol = new symbol("0", 0, 0, 0);
		  symbol* secondDaySymbol = new symbol("0", 0, 0, 0);

		  for (int j = 0; j < linesFirstDay; j++)
		  {
			  if (firstDay[j]->wIssueSymbol == symLookingFor)
				  firstDaySymbol = firstDay[j];
		  }

		  for (int k = 0; k < linesSecondDay; k++)
		  {
			  if (secondDay[k]->wIssueSymbol == symLookingFor)
				  secondDaySymbol = secondDay[k];
		  }

		  double priceChange;
		  int countChange, volumeToAssign;

		  if (secondDaySymbol->wTradePrice == firstDaySymbol->wTradePrice)
			  priceChange = secondDaySymbol->wTradePrice;
		  else
			  priceChange = secondDaySymbol->wTradePrice - firstDaySymbol->wTradePrice;

		  if (secondDaySymbol->wTradeCount == firstDaySymbol->wTradeCount)
			  countChange = secondDaySymbol->wTradeCount;
		  else if ( (secondDaySymbol->wTradeCount - firstDaySymbol->wTradeCount) + secondDaySymbol->wTradeCount  < 0 )
			  countChange = firstDaySymbol->wTradeCount - secondDaySymbol->wTradeCount;
		  else
			  countChange = secondDaySymbol->wTradeCount - firstDaySymbol->wTradeCount;

		  volumeToAssign = firstDaySymbol->wTradeVolume;

		  do
		  {
			  if (!(priceChange <= 0.05 && priceChange >= 0.00) || !(priceChange >= -0.05 && priceChange <= 0.00))
			  {
				  if (priceChange != 0.00)
				  {
					  priceChange = randfrom(0.00, priceChange * (rand() % 5));
					  int count = 0;
					  while (priceChange == 0.00)
					  {
						  priceChange = randfrom(0.00, (priceChange + 0.05) * (rand() % 5));
						  count++;
						  if (count == 5 )
							  break;
					  }
				  }
			  }
		  }while (priceChange + secondDaySymbol->wTradePrice <= 0);

		  do
		  {
			  if ((countChange <= 20 && countChange >= 0) || (countChange >= -20 && countChange <= 0))
			  {
				  countChange = rand() % secondDaySymbol->wTradeCount;
				  int count = 0;
				  while (countChange == 0)
				  {
					  countChange = rand() % secondDaySymbol->wTradeCount;
					  count++;
					  if (count == 5 )
						  break;
				  }
			  }
		  }while (countChange + secondDaySymbol->wTradeCount < 0);

		  int quotes = ((rand() % 65)+1) * (secondDaySymbol->wTradeCount + countChange);

		  comparedSymbol = new generatorTemplate(secondDaySymbol->wIssueSymbol, secondDaySymbol->wTradePrice, priceChange, volumeToAssign, secondDaySymbol->wTradeCount, countChange, quotes);

		  cout << fixed << showpoint;
		  cout << setprecision(2);
		  comparedSymbol->print();
	  }
  }
  cout << endl << endl << "Symbol		Base Price	Price Change	Volume		Base Count	Count Change	QuoteCount" << endl;

  return 0;
}
