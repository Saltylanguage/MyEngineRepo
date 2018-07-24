#include "Precompiled.h"

#include "AnimationClip.h"
#include "Bone.h"
#include "BoneAnimation.h"

using namespace Graphics;

AnimationClip::AnimationClip() : duration(0.0f), ticksPerSecond(0.0f), keyFrameCount(0)
{
}

AnimationClip::~AnimationClip()
{
	for (auto animation : boneAnimations)
	{
		SafeDelete(animation);
	}

	boneAnimations.clear();
}

void AnimationClip::GetTransform(float time, Bone* bone, Matrix& transform) const
{
	BoneAnimation* boneAnim = boneAnimations[bone->index];

	if (boneAnim != nullptr)
	{
		if (boneAnim->bone)
		{

			transform = boneAnim->GetTransform(time);
		}
	}
	else
	{
		Matrix mat = mat.Identity();
		transform = mat;
	}
}


