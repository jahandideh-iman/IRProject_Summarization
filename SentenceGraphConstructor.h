#pragma once

namespace IRProject
{
	class SentenceGraphConstructor
	{
	public:
		SentenceGraphConstructor(void);
		virtual ~SentenceGraphConstructor(void);

		virtual void constructGraph() = 0;
	};
}
