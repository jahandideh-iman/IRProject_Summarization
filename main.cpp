#include "Param.hpp"
#include "IndexManager.hpp"
#include <iostream>
#include "ClusterBasedConditionalMarkovRandomWalk.h"
#include "MinimumDominatingSetSummarizer.h"
using namespace lemur::api;

namespace LocalParameter {
	std::string index;   
	std::string docID;
	int summLength;   
	void get() {
		index  = ParamGetString("index");
		docID = ParamGetString("docID");
		summLength   = ParamGetInt("summLength", 5);

	}    
};

void GetAppParam() {
	LocalParameter::get();
}

int main(int argc, char* argv[]) {
	int a = 0;

	//lemur::api::Index * idx = IndexManager::openIndex(LocalParameter::index);
	lemur::api::Index * idx = IndexManager::openIndex("Index/index.key");

	IRProject::MinimumDominatingSetSummarizer summerizer(0.8,idx);
	std::vector<int> result = summerizer.summarize();


	auto d = idx->docManager(1);
	delete(idx);
	return 0;
}
