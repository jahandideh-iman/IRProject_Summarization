#pragma once
#include "summarizer.h"
#include "SentenceGraphConstructor.h"
#include "SentenceScorer.h"
#include "SentenceExtractor.h"

namespace IRProject
{
	class GraphBasedSummarizer :
		public Summarizer
	{
	public:
		GraphBasedSummarizer(SentenceGraphConstructor *graphConstructor, SentenceScorer *scorer, SentenceExtractor *extractor);
		~GraphBasedSummarizer(void);

		std::vector<std::string> summarize() override;

	private:
		SentenceGraphConstructor *graphConstructor;
		SentenceScorer *scorer;
		SentenceExtractor *extractor;
	};
}
