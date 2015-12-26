#pragma once

#include "ClusterBasedSummarizer.h"
#include "Types.h"

namespace IRProject
{
	class ClusterBasedConditionalMarkovRandomWalk : public ClusterBasedSummarizer
	{
	public:
		ClusterBasedConditionalMarkovRandomWalk(Index *index);
		~ClusterBasedConditionalMarkovRandomWalk(void);


	protected:
		std::vector<double> computeSentencesScore(Matrix &m) override;
		void initialAdjacencyMatrix(Matrix &m, const std::vector<ClusterInfo> &clusters) override;

	private:
		void initialDocsInfo(std::vector<DocInfo> &docs, const std::vector<ClusterInfo> &clusters);

	private:
		double lambda;
	};
}

