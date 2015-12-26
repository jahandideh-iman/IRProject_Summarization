#include "Param.hpp"
#include "IndexManager.hpp"
#include <iostream>
#include "ClusterBasedConditionalMarkovRandomWalk.h"
#include "MinimumDominatingSetSummarizer.h"
#include "ClusterBasedHITS.h"
using namespace lemur::api;

int main(int argc, char* argv[]) {
	int a = 0;
	std::vector<int> result;
	//lemur::api::Index * idx = IndexManager::openIndex(LocalParameter::index);
	lemur::api::Index * idx = IndexManager::openIndex("Index/index2.key");

	//IRProject::MinimumDominatingSetSummarizer summerizer(0.8,idx);
	IRProject::ClusterBasedConditionalMarkovRandomWalk MRWSummerizer(idx);

	result = MRWSummerizer.summarize();
	printf("ClusterBasedConditionalMarkovRandomWalk : %d \n", result[0]);

	IRProject::ClusterBasedHITS HITSSummerizer(idx);
	result = HITSSummerizer.summarize();
	printf("ClusterBasedHITS : %d \n", result[0]);

	delete(idx);
	return 0;
}
