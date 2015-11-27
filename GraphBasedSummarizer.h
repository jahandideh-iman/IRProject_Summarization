#pragma once
#include "summarizer.h"
#include "UnitGraphConstructor.h"
#include "UnitScorer.h"
#include "UnitExtractor.h"

namespace IRProject
{
	class GraphBasedSummarizer :
		public Summarizer
	{
	public:
		GraphBasedSummarizer(UnitGraphConstructor *graphConstructor, UnitScorer *scorer, UnitExtractor *extractor);
		~GraphBasedSummarizer(void);

		std::vector<std::string> summarize() override;

	private:
		UnitGraphConstructor *graphConstructor;
		UnitScorer *scorer;
		UnitExtractor *extractor;
	};
}
