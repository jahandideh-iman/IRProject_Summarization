#include <string>
#include <fstream>

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

int main()
{
	convertedDoc("data/1.txt", "data/1_out.txt");

	return 0;
}