#pragma once

#include <vector>

namespace IRProject
{
	class SentenceExtractor
	{
	public:
		SentenceExtractor(void);
		virtual ~SentenceExtractor(void);

		virtual std::vector<std::string> extractSentences() = 0;
	};
}
