#pragma once
#include "BoneAnimation.h"
#include <Math\Inc\Matrix.h>

namespace Graphics
{

	struct Bone;
	class AnimationClip;
	class Model;

	typedef std::vector<Matrix> BoneTransforms;

	class AnimationController
	{
	public :
		AnimationController();
		~AnimationController();

		void Initialize(Model& model);


		void StartClip(const char* animationClipName, bool loop);
		void Update(float deltaTime);

		const BoneTransforms& ToRootTransforms() const { return mToRootTransforms; }
		const BoneTransforms& ToLocalTransforms() const { return mFinalTransforms; }
		const Matrix& InverseRootTransform() const { return mInverseRootTransform; }


	private:
		 
		void GetBindPose(Bone* bone);
		void GetPose(float time, Bone* bone);

		AnimationClip* mCurrentAnimationClip;

		BoneTransforms mToRootTransforms;
		BoneTransforms mFinalTransforms;
		Matrix mInverseRootTransform;

		Model* mModel;

		float mCurrentTime;
		uint32_t mCurrentFrame;

		bool mIsPlaying;
		bool mIsLooping;

	};

}
