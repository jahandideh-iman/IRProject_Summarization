#include "GraphBasedSummarizer.h"


IRProject::GraphBasedSummarizer::GraphBasedSummarizer(UnitGraphConstructor *graphConstructor, UnitScorer *scorer, UnitExtractor *extractor)
{
	this->graphConstructor = graphConstructor;
	this->scorer = scorer;
	this->extractor = extractor;
}


IRProject::GraphBasedSummarizer::~GraphBasedSummarizer(void)
{
}

std::vector<std::string> IRProject::GraphBasedSummarizer::summarize()
{
	graphConstructor->constructGraph();
	scorer->computeScores();
	return extractor->extractUnits();
}
