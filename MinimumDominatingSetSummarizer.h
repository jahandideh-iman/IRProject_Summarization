#pragma once

#include "Summarizer.h"
#include <vector>
#include <set>
#include "Types.h"

using std::set;
using std::vector;

namespace IRProject
{
	class MinimumDominatingSetSummarizer : public Summarizer
	{
	public:
		MinimumDominatingSetSummarizer(double lambda, Index *index);
		~MinimumDominatingSetSummarizer(void);

		virtual std::vector<int> summarize() override;

	private:
		vector<set<int>> getAdjacencyGraph();

	private:
		Index *index;
		double lambda;
	};
}
