#include "GraphBasedSummarizer.h"


IRProject::GraphBasedSummarizer::GraphBasedSummarizer(SentenceGraphConstructor *graphConstructor, SentenceScorer *scorer, SentenceExtractor *extractor)
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
	return extractor->extractSentences();
}
