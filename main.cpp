#include "Param.hpp"
#include "IndexManager.hpp"
#include <iostream>
#include "Summarizer.h"
#include "ClusterBasedConditionalMarkovRandomWalk.h"
#include "MinimumDominatingSetSummarizer.h"
#include "ClusterBasedHITS.h"
#include <fstream>

using namespace lemur::api;


IRProject::Summarizer *createSummarizer(string type, Index *index, double lambda);

std::vector<string> extractLines(ifstream &originalText);

int main(int argc, char* argv[]) 
{
	if(argc != 6)
	{
		std::cerr << "Usage: " << argv[0] << " Summarization Type, Index Key Path, Output Path, Original Text path, Lambda" << std::endl;
		return -1;
	}

	string summarizationType = argv[1];
	string indexKeyPath = argv[2];
	string outputPath = argv[3];
	string originalTextPath = argv[4];
	double lambda = atof(argv[5]);

	ifstream originalText(originalTextPath);
	if(originalText.is_open() == false)
	{
		std::cerr << "Could not open original text file" << std::endl;
		return -1;
	}

	ofstream output;
	output.open(outputPath);

	std::vector<string> lines = extractLines(originalText);

	lemur::api::Index * idx = IndexManager::openIndex(indexKeyPath);
	IRProject::Summarizer *summarizer = createSummarizer(summarizationType, idx, lambda);

	if(summarizer == nullptr)
	{
		std::cerr << "Invalid summarizer type " << summarizationType << std::endl;
		return -1;
	}

	std::vector<int> result = summarizer->summarize();

	for(int i : result)
	{
		printf("%d \n", i);
		output << lines[i-1] << std::endl;
	}

	output.close();
	delete idx;
	delete summarizer;
	return 0;
}

IRProject::Summarizer *createSummarizer(string type, Index *index, double lambda)
{
	if(type == "MDS")
		return new IRProject::MinimumDominatingSetSummarizer(lambda,index);
	else if(type == "CHITS")
		return new IRProject::ClusterBasedHITS(index);
	else if(type == "CMRW")
		return new IRProject::ClusterBasedConditionalMarkovRandomWalk(lambda,index);

	return nullptr;
}

std::vector<string> extractLines(ifstream &originalText)
{
	string line;
	std::vector<string> res;
	while ( getline(originalText,line) )
	{
		res.push_back(line);
	}
	originalText.close();

	return res;
}