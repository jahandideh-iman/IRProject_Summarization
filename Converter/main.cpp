#include <string>
#include <fstream>
#include <iostream>

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
	while (std::getline(in, line)) {
		//TODO: write your code here.
	}
}

int main(int argc, char* argv[]) 
{
	if(argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " Input file path, Output file path" << std::endl;
		return -1;
	}

	string inputPath = argv[1];
	string outputPath = argv[2];

	ifstream input(inputPath);
	ofstream output(outputPath);
	
	if(input.is_open()==false || output.is_open()==false)
	{
		std::cerr << "Could Not open file" << std::endl;
		return -1;
	}

	//convertToLemurFormat(input, output);
	removeTweetMetaData(input, output);

	output.close();

	return 0;
}