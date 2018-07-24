#pragma once

#include "KeyFrame.h"
#include "Bone.h"


namespace Graphics
{

	struct Bone;

	class BoneAnimation
	{
	public:

		BoneAnimation() {};
		~BoneAnimation() {};

		Matrix GetTransform(float time) const { return bone->transform; }

		//float GetEndTime() const;
		//uint32_t FindKeyFrameIndex(float time) const;

		std::vector<KeyFrame> keyframes;
		Bone* bone;
		uint32_t boneIndex;


	};
}
