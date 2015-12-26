#pragma once

#include <vector>

namespace IRProject
{
	class Summarizer
	{
	public:
		Summarizer(void);
		virtual ~Summarizer(void);

		virtual std::vector<int> summarize() = 0;
	};
}
