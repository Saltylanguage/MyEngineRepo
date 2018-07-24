#pragma once
#include "BoneAnimation.h"


namespace Graphics
{
	struct Bone;

	class AnimationClip
	{
	public:

		AnimationClip();
		~AnimationClip();

		void GetTransform(float time, Bone* bone, Matrix& transform) const;
		std::vector<BoneAnimation*> boneAnimations;
		std::string mName;
		float duration;
		float ticksPerSecond;
		uint32_t keyFrameCount;

	};
}