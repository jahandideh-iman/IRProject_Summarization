#pragma once

#include <vector>

namespace IRProject
{
	class Summarizer
	{
	public:
		Summarizer(void);
		virtual ~Summarizer(void);

		virtual std::vector<std::string> summarize() = 0;
	};
}
