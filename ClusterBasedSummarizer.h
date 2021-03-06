#pragma once

#include "Summarizer.h"
#include "Types.h"

namespace IRProject
{

	class ClusterBasedSummarizer : public Summarizer
	{
	public:
		ClusterBasedSummarizer(Index *index);
		~ClusterBasedSummarizer(void);

		virtual std::vector<int> summarize() final override;

	protected:
		virtual std::vector<double> computeSentencesScore(Matrix &m) = 0;
		virtual void initialAdjacencyMatrix(Matrix &m,const std::vector<ClusterInfo> &clusters) = 0;

		void normalize(Matrix &m);
		void normalize(std::vector<double> &vector, unsigned startIndex = 0);

		bool isUnderThreshold(std::vector<double> &v1, std::vector<double> &v2, unsigned startIndex, double threshold);

	private:
		std::vector<ClusterInfo> detectClusters();
		std::vector<int> selectMaximumDoc(const std::vector<double> &finalScore);
		std::vector<int> selectDocs(const std::vector<double> &finalScore);
		double computeClusterWeight(Cluster *cluster);

		int findMaxIndex(const std::vector<double> &vector, const std::vector<bool> &selectionFlag);
		void initialSimilarityMatrix(Matrix &similarityMatrix);
	protected:
		Index *index;
		ClusterRep *setCluster;
		CosSim *cosSim;
		int docsCount;
	};

}
