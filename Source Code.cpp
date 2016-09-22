#include<iostream>
#include<string>
#include<fstream>
#include <algorithm>

using namespace std;

class Header{  //creating class Header

private:
	string MessageCategory;
	string MessageType;
	string MessageNetwork;
	string MessageSequenceNumber;
	string ParticipantID;

public:					// declaring constructors for Header
	void variables_header(string);
	void printheader();
};

void Header::variables_header(string input) {	//constructor 1 variables take value from the input file
	MessageCategory = input.substr(0, 1);
	MessageType = input.substr(1, 1);
	MessageNetwork = input.substr(2, 1);
	MessageSequenceNumber = input.substr(8, 9);
	ParticipantID = input.substr(17, 1);
}

void Header::printheader() { //constructor II that writes to the file

	ofstream fout("C:\\Users\\Aisha\\Desktop\\equity_trades_mod.txt", ios::app);
	fout << MessageCategory << "," << MessageType << "," << MessageNetwork << "," << MessageSequenceNumber << "," << ParticipantID << ",";
	fout.close();
}

class Short{ //declaring another class Short

private:
	string SecuritySymbol;
	string TradePrice;
	string PriceDenominator;
	string TradeVolume;
	string SaleCondition;

public:								//Short constructors
	void variables_short(string);
	void printshort();
	
};

void Short::variables_short(string input) { //Constructor I for the input
	SecuritySymbol = input.substr(45, 3);
	TradePrice = input.substr(54, 8);
	PriceDenominator = input.substr(53, 1);
	TradeVolume = input.substr(49, 4);
	SaleCondition = input.substr(48, 1);
}

void Short::printshort() { //constructor II that writes to the file

	ofstream fout("C:\\Users\\Aisha\\Desktop\\equity_trades_mod.txt", ios::app); 
	
	fout << SecuritySymbol << ",";

	double price = atof(TradePrice.c_str()); //converting string variables into double (for price) and integer (for volume)
	int volume = atof(TradeVolume.c_str());

	if (PriceDenominator == "A")		{ fout << price / 10; }			//depending on pricedenominator, divide price by 10^k, print out price
	else if (PriceDenominator == "B")	{ fout << price / 100; }
	else if (PriceDenominator == "C")	{ fout << price / 1000; }
	else if (PriceDenominator == "D")	{ fout << price / 10000; }
	else if (PriceDenominator == "E")	{ fout << price / 100000; }
	else if (PriceDenominator == "F")	{ fout << price / 1000000; }
	else if (PriceDenominator == "G")	{ fout << price / 10000000; }
	else if (PriceDenominator == "H")	{ fout << price / 100000000; }
	else	{ fout << "ERROR"; }

	fout << "," << volume << "," << SaleCondition << endl;				//outputting volume and sale condition in the file
	fout.close();
}



class Long					//declaring class Long
{
private:
	string SecuritySymbol;
	string TradePrice;
	string PriceDenominator;
	string part9;
	string part10;
	string part11;

public:						//constructors
	void variables_long(string);
	void printlong();
};

void Long::variables_long(string input) {	//constructor 1 variables take value from the input file
	SecuritySymbol = input.substr(45, 11);
	TradePrice = input.substr(78, 12);
	PriceDenominator = input.substr(77, 1);
	part9 = input.substr(90, 9);
	part10 = input.substr(70, 4);
	part11 = input.substr(58, 1);
}

void Long::printlong() {	//outputting variables into our file
	
	ofstream fout("C:\\Users\\Aisha\\Desktop\\equity_trades_mod.txt", ios::app);
	string m_SecuritySymbol = SecuritySymbol;
	string p = part10;
	m_SecuritySymbol.erase(m_SecuritySymbol.find_last_not_of(" \t\n\r\f\v") + 1);	//erasing whitespaces in Security SYmbol and Sale Condition variables
	p.erase(remove(p.begin(), p.end(), ' '), p.end());

	fout << m_SecuritySymbol << ",";

	double price = atof(TradePrice.c_str());			//changing string TradePrice into double, string TradeVolume into integer
	int volume = atof(part9.c_str());

	if (PriceDenominator == "A")		{ fout << price / 10; }	//depending on pricedenominator, divide price by 10^k, save price in the file
	else if (PriceDenominator == "B")	{ fout << price / 100; }
	else if (PriceDenominator == "C")	{ fout << price / 1000; }
	else if (PriceDenominator == "D")	{ fout << price / 10000; }
	else if (PriceDenominator == "E")	{ fout << price / 100000; }
	else if (PriceDenominator == "F")	{ fout << price / 1000000; }
	else if (PriceDenominator == "G")	{ fout << price / 10000000; }
	else if (PriceDenominator == "H")	{ fout << price / 100000000; }
	else	{ fout << "ERROR"; }

	fout << "," << volume << "," << p << "," << part11 << endl;  //outputting volume and sale condition in the file
	fout.close();												//closing file
}

void base95(string input) { //function to decode timestamps and transactionID

	long long n = 0;
	long long  m = 1;

	string CTStimestamp = input.substr(18, 6); //reading CTS timestamp
	int len = CTStimestamp.length();

	while (len > 0) {						//converting CTS timestamp into a decimal number (variable n)
		n += (CTStimestamp[--len] - 32) * m;
		m *= 95;
	}

	long Microseconds = n % 1000000;		//converting n milliseconds into hr:mm:ss:mmmmmm
	long Seconds = (n / 1000000) % 60;
	long Minutes = (n / 60000000) % 60;
	long Hours = (n / 3600000000) % 24;

	ofstream fout("C:\\Users\\Aisha\\Desktop\\equity_trades_mod.txt", ios::app);
	fout << Hours << ":" << Minutes << ":" << Seconds << "." << Microseconds << ","; //outputting time into the file

	n = 0, m = 1;							//nulling values for n,m

	string TimestampI = input.substr(24, 6); //extracting TimeStampI from file
	len = TimestampI.length();

	while (len > 0) {						//converting timestampI into a decimal number (n milliseconds)
		n += (TimestampI[--len] - 32) * m;
		m *= 95;
	}

	fout << n << ",";						//outputting n milliseconds (TimestampI) into the file

	n = 0, m = 1;							//nulling values fr n,m
	string TimestampII = input.substr(30, 6); //extracting TimeStampII from file
	len = TimestampII.length();

	while (len > 0) {						//converting timestampI into a decimal number (n milliseconds)
		n += (TimestampII[--len] - 32) * m;
		m *= 95;
	}

	fout << n << ",";						//outputting n milliseconds (TimestampII) into the file

	n = 0, m = 1;

	string TransactionID = input.substr(36, 9); //extracting TransactionID from file
	len = TransactionID.length();

	while (len > 0) {							//converting TransactionID into a decimal number n
		n += (TransactionID[--len] - 32) * m;
		m *= 95;
	}

	fout << n << ","; fout.close();			//outputting TransactionID into the file 

}

int main() {
	
	ifstream fin("C:\\Users\\Aisha\\Desktop\\equity_trades_small.txt");
	string input;
	while (getline(fin, input)) {			//reading file line by line
		if (input.length() <= 65) 
		{	
			base95(input);					//if the length of line is less or equal 65, then it's short trade
			
			Header c;						//calling Header class constructors
			c.variables_header(input);
			c.printheader();

			Short a;						//we use short class and call its constructors and a function base95
			a.variables_short(input);
			a.printshort();


		}
		else
		{
			base95(input);					// if the line is more than 65 characters, it will be treated as long trade

			Header c;						//calling Header class constructors
			c.variables_header(input);
			c.printheader();

			Long b;							//calling Long class constructors
			b.variables_long(input);
			b.printlong();


		}
	}


	char response;			//doesn't close until a character is entered
	std::cin >> response;

	return 0;
}




