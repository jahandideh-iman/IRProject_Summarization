#pragma once

#include "Index.hpp"
#include "Cluster.hpp"
#include "ClusterRep.hpp"
#include "CosSim.hpp"

namespace IRProject
{

	typedef lemur::api::Index Index;
	typedef lemur::cluster::Cluster Cluster;
	typedef lemur::cluster::ClusterRep ClusterRep;
	typedef lemur::cluster::CosSim CosSim;

	typedef  std::vector<std::vector<double>> Matrix;


	struct ClusterInfo{

		ClusterInfo(const ClusterInfo &other)
		{
			cluster = other.cluster;
			weight = other.weight;
		}

		ClusterInfo()
		{
			cluster = nullptr;
			weight  = 0;
		}

		ClusterInfo(Cluster *c, double w)
		{
			cluster = c;
			weight  = w;
		}
		Cluster *cluster;
		double weight;
	};

	struct DocInfo{

		DocInfo()
		{
			clusterInfo = nullptr;
			weight  = 0;
		}

		DocInfo(ClusterInfo *c, double w)
		{
			clusterInfo = c;
			weight  = w;
		}
		const ClusterInfo *clusterInfo;
		double weight;
	};
}