#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;


void convertToLemurFormat(ifstream &in, ofstream &out) {

	string line;
	int count = 1;
	while (std::getline(in, line)) {
		out << "<DOC>\n<DOCNO> " << count
			<< " </DOCNO>\n<TEXT>\n" << line
			<< "\n</TEXT>\n</DOC>\n\n";
		count++;
	}

}

void removeTweetMetaData(ifstream &in, ofstream &out)
{
	string line;
	while ( std::getline(in, line) ) {
		stringstream ss(line);
		string tmp;
		ss >> tmp;
		ss >> tmp;
		ss >> tmp;
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		if(tmp != "rt" && tmp != "v") {
			out << tmp;
		}
		while(ss >> tmp)
			out << " "<< tmp;
		out<< endl;
	}
}

int main(int argc, char* argv[]) 
{
	if(argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << "Conversion Type, Input file path, Output file path" << std::endl;
		return -1;
	}

	string conversionType = argv[1];
	string inputPath = argv[2];
	string outputPath = argv[3];

	ifstream input(inputPath);
	ofstream output(outputPath);
	
	if(input.is_open()==false || output.is_open()==false)
	{
		std::cerr << "Could Not open file" << std::endl;
		return -1;
	}
	
	if(conversionType == "TRIM")
		removeTweetMetaData(input, output);
	else if(conversionType == "LEMUR")
		convertToLemurFormat(input, output);

	output.close();

	return 0;
}