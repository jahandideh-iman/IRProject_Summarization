#pragma once
#include "clusterer.h"
#include "OfflineCluster.hpp"
#include "Types.h"

namespace IRProject
{
	class KMeansClusterer :
		public Clusterer
	{
	public:
		KMeansClusterer(const Index *index, unsigned k);
		~KMeansClusterer(void);

		virtual std::vector<Cluster *> *cluster() override;
	private:
		lemur::cluster::OfflineCluster *clusterer;

		const Index *index;
		unsigned k;
	};
}
