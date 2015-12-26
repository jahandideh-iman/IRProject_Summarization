#include <string>
#include <fstream>
#include <iostream>

using namespace std;


void convertedDoc(string inFileName, string outFileName) {
	fstream fin(inFileName.c_str());
	fstream fout;
	fout.open(outFileName.c_str(), fstream::out);
	string line;
	int count = 1;
	while (std::getline(fin, line)) {
		fout << "<DOC>\n<DOCNO> " << count
			<< " </DOCNO>\n<TEXT>\n" << line
			<< "\n</TEXT>\n</DOC>\n\n";
		count++;
	}
	fout.flush();
	fout.close();
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

	convertedDoc(inputPath, outputPath);

	return 0;
}