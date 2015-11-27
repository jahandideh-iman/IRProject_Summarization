#include "Param.hpp"
#include "BasicSumm.hpp"
#include "IndexManager.hpp"
#include <iostream>

using namespace lemur::api;
using namespace lemur::summarization;

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

int AppMain(int argc, char* argv[]) {
	lemur::api::Index * idx = IndexManager::openIndex(LocalParameter::index);


	// Create a basic summarizer
	lemur::summarization::BasicSumm* s = new lemur::summarization::BasicSumm(idx);
	// Generate a summary
	// NULL is not valid for an empty string
	//  s->summDocument(LocalParameter::docID, LocalParameter::summLength, NULL);
	s->summDocument(LocalParameter::docID, LocalParameter::summLength, "");
	// Print to stdout
	s->outputSumm();
	delete(idx);
	return 0;
}
