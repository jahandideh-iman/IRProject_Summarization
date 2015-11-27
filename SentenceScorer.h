#pragma once

namespace IRProject
{
	class SentenceScorer
	{
	public:
		SentenceScorer(void);
		virtual ~SentenceScorer(void);

		virtual void computeScores() = 0;
	};
}
