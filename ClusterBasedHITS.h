#pragma once

#include "ClusterBasedSummarizer.h"

namespace IRProject
{
	class ClusterBasedHITS : public ClusterBasedSummarizer
	{
	public:
		ClusterBasedHITS(Index *index);
		~ClusterBasedHITS(void);

	protected:
		std::vector<double> computeSentencesScore(Matrix &m) override;
	private:
		void initialAdjacencyMatrix(Matrix &m,const std::vector<ClusterInfo> &clusters) override;
		
	};
}
