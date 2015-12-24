#pragma once

#include "Summarizer.h"
#include "Types.h"

namespace IRProject
{
	class ClusterBasedConditionalMarkovRandomWalk : public Summarizer
	{
	public:
		ClusterBasedConditionalMarkovRandomWalk(Index *index);
		~ClusterBasedConditionalMarkovRandomWalk(void);

		virtual std::vector<std::string> summarize();

	private:
		double computeClusterWeight(Cluster *cluster);

	private:
		Index *index;
		ClusterRep *docsSetCluster;
	};
}

