#include "Param.hpp"
#include "IndexManager.hpp"
#include <iostream>
#include "Summarizer.h"
#include "ClusterBasedConditionalMarkovRandomWalk.h"
#include "MinimumDominatingSetSummarizer.h"
#include "ClusterBasedHITS.h"
using namespace lemur::api;

IRProject::Summarizer *createSummarizer(string type, Index *index);

int main(int argc, char* argv[]) 
{
	if(argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " Summarization Type, Index Key Path, Output Path" << std::endl;
		return -1;
	}

	string summarizationType = argv[1];
	string indexKeyPath = argv[2];
	string outputPath = argv[3];

	lemur::api::Index * idx = IndexManager::openIndex(indexKeyPath);
	IRProject::Summarizer *summarizer = createSummarizer(summarizationType, idx);

	if(summarizer == nullptr)
	{
		std::cerr << "Invalid summarizer type " << summarizationType << std::endl;
		return -1;
	}

	std::vector<int> result = summarizer->summarize();

	printf("%s : %d \n", summarizationType.c_str() ,result[0]);

	delete idx;
	delete summarizer;
	return 0;
}


IRProject::Summarizer *createSummarizer(string type, Index *index)
{
	if(type == "MDS")
		return new IRProject::MinimumDominatingSetSummarizer(0.8,index);
	else if(type == "CHITS")
		return new IRProject::ClusterBasedHITS(index);
	else if(type == "CMRW")
		return new IRProject::ClusterBasedConditionalMarkovRandomWalk(index);

	return nullptr;
}