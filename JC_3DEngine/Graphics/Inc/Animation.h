#pragma once
#include <vector>
#include "KeyFrame.h"
#include "Math\Inc\EngineMath.h"
#include <algorithm>

namespace Graphics
{

	class Animation
	{

		std::vector<KeyFrame> mKeyFrames;
		float currentTime;
		float maxTime;


	public:
		Animation()
			: currentTime{ 0.0f }
		{

		}
		void AddKeyFrame(const KeyFrame& keyframe)
		{
			mKeyFrames.push_back(keyframe);

			if (mKeyFrames.size() > 1)
			{
				std::sort(mKeyFrames.begin(), mKeyFrames.end(), [](const KeyFrame& A, const KeyFrame& B) {return A.time < B.time; });
			}

			maxTime = mKeyFrames.back().time;

		}


		Matrix Update(float deltaTime)
		{

			Matrix ret;

			currentTime += deltaTime;


			if (currentTime >= maxTime)
			{
				currentTime -= maxTime;
			}

			if (mKeyFrames.size() == 0)
			{
				ret.Identity();
				return ret;
			}

			if (mKeyFrames.size() == 1)
			{
				return mKeyFrames[0].GetTransform();
			}

			int i = 0;
			float t = 0;
			for (size_t i; i < mKeyFrames.size() - 1; i++)
			{
				float firstTime = mKeyFrames[i].time;
				float secondTime = mKeyFrames[i + 1].time;

				if (currentTime == firstTime)
				{
					return mKeyFrames[i].GetTransform();
				}
				if (currentTime == secondTime)
				{
					return mKeyFrames[i + 1].GetTransform();
				}
				if (currentTime > firstTime && currentTime < secondTime)
				{
					t = (currentTime - firstTime) / (secondTime - firstTime);
					break;
				}
			}

			return KeyFrame::Lerp(mKeyFrames[i], mKeyFrames[i + 1], t).GetTransform();

		}



	};
}