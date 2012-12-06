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
#include "symbol.h"
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

void FileParser (string filename, int arrLength, symbol arr[ ]) {
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
  {
	  arr[i].wIssueSymbol = symbolsInFile[i]->wIssueSymbol;
	  arr[i].wTradePrice = symbolsInFile[i]->wTradePrice;
	  arr[i].wTradeVolume = symbolsInFile[i]->wTradeVolume;
	  arr[i].wTradeCount = symbolsInFile[i]->wTradeCount;

	  /*
	  cout << symbolsInFile[i]->wIssueSymbol;
	  cout << "		";
	  cout << symbolsInFile[i]->wTradePrice;
	  cout << "		";
	  cout << symbolsInFile[i]->wTradeVolume;
	  cout << "		";
	  cout << symbolsInFile[i]->wTradeCount << endl;

*/
	  cout << arr[i].wIssueSymbol;
	  cout << "		";
	  cout << arr[i].wTradePrice;
	  cout << "		";
	  cout << arr[i].wTradeVolume;
	  cout << "		";
	  cout << arr[i].wTradeCount << endl;

  }
  symFile.close();
  processedFile.close();
}

int main () {
  string filePath = "/Users/gtgmason/Documents/workspace/no_control_chars.txt";
  int symCount = LengthOfFile(filePath.c_str());
  symbol *syms1[symCount];

  FileParser(filePath.c_str(), symCount, *syms1);

  for (int i = 0; i < symCount; i++)
  {
	  cout << syms1[i]->wIssueSymbol;
	  cout << "		";
	  cout << syms1[i]->wTradePrice;
	  cout << "		";
	  cout << syms1[i]->wTradeVolume;
	  cout << "		";
	  cout << syms1[i]->wTradeCount << endl;;
  }

  cout << "Symbol		Price		Volume		Count" << endl;

  return 0;
}
