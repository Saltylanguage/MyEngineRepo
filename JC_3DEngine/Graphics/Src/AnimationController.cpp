#include "Precompiled.h"

#include "AnimationController.h"

#include "AnimationClip.h"
#include "Bone.h"
#include "Model.h"

#include "AnimationController.h"

using namespace Graphics;

AnimationController::AnimationController() :
	mModel(nullptr),
	mCurrentAnimationClip(nullptr),
	mCurrentTime(0.0f),
	mCurrentFrame(0),
	mIsPlaying(false),
	mIsLooping(false)
{}

AnimationController::~AnimationController()
{

}


void AnimationController::Initialize(Model& model)
{
	mModel = &model;
	mToRootTransforms.resize(model.mBones.size());
	mFinalTransforms.resize(model.mBones.size());
}

void AnimationController::StartClip(const char * animationClipName, bool loop)
{
	mCurrentAnimationClip = mModel->FindAnimationClip(animationClipName);

	mCurrentTime = 0;
	mCurrentFrame = 0;
	mIsPlaying = true;
	mIsLooping = loop;

	//Force root transform to identity
	//mModel->mRoot->transform = Matrix::Identity();
	
	for (size_t i = 0; i < mModel->mBones.size(); i++)
	{
		if (mModel->mBones[i]->parentIndex == -1)
		{
			mModel->mRoot = mModel->mBones[i];
		}
	}

	mInverseRootTransform = Matrix::Inverse(mModel->mRoot->transform);

	GetBindPose(mModel->mRoot);
}

void AnimationController::Update(float deltaTime)
{
	if (!mIsPlaying)
	{
		return;
	}
	mCurrentTime += deltaTime * mCurrentAnimationClip->ticksPerSecond;
	if (mCurrentTime >= mCurrentAnimationClip->duration)
	{
		if (mIsLooping)
		{
			mCurrentTime = 0.0f;
		}
		else
		{
			mIsPlaying = false;
		}
	}

	if (mIsPlaying)
	{
		GetPose(mCurrentTime, mModel->mRoot);
	}
}

void AnimationController::GetBindPose(Bone* bone)
{
	Matrix toParentTransform = bone->transform;
	Matrix toRootTransform = toParentTransform;
	if (bone->parent != nullptr)
	{
		toRootTransform = toParentTransform * mToRootTransforms[bone->parent->index];
	}
	mToRootTransforms[bone->index] = toRootTransform;
	mFinalTransforms[bone->index] = bone->offsetTransform * toRootTransform * mInverseRootTransform;

	for (Bone* child : bone->children) // not pointing to children and setting offset matrix
	{
		GetBindPose(child);
	}

}

void AnimationController::GetPose(float time, Bone* bone)
{
	Matrix toParentTransform;
	mCurrentAnimationClip->GetTransform(time, bone, toParentTransform);

	Matrix toRootTransform = toParentTransform;
	if (bone->parent != nullptr)
	{
		toRootTransform = toParentTransform * mToRootTransforms[bone->parent->index];
	}

	mToRootTransforms[bone->index] = toRootTransform;  
	mFinalTransforms[bone->index] = bone->offsetTransform * toRootTransform * mInverseRootTransform;

	for (Bone* child : bone->children)
	{
		GetPose(time,child);
	}
}