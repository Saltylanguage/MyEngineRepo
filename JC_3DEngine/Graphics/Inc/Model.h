#pragma once
#include "Vertex.h"
#include <vector>
#include "ConstantBuffer.h"
#include "Animation.h"
#include "AnimationController.h"


namespace Graphics
{
	class Mesh;
	class MeshBuffer;
	class Texture;
	class Camera;
	class AnimationClip;
	struct Bone;

	typedef std::vector<Mesh*> MeshList;
	typedef std::vector<std::string> TextureList;

	class Model 
	{
		friend class AnimationController;

	public:
		Model(): mTextures(nullptr)
		{};
		~Model() {};


		struct WorldInfo
		{
			Matrix world;
			Matrix wvp;

			Vector3 cameraPosition;
		};

		TypedConstantBuffer<WorldInfo> mWorldBuffer;

		Vector3 mPosition;
		Matrix mRotationMatrix;
		Vector3 mScale;

		NONCOPYABLE(Model);

		std::vector<Graphics::Mesh*> Meshes;
		std::vector<std::string> Textures;
		std::vector<Graphics::MeshBuffer*> MeshBuffers;

		Texture* mTextures;

		std::vector<Bone*> mBones;
		std::vector<AnimationClip*> mAnimationClips;

		Matrix mWorldTransform;

		Bone* mRoot;
		

	public:

		void Load(const char* filname);
		bool LoadModel(const char* filename, MeshList& meshes, TextureList& textures);
		void Unload();

		void AssignBonePointers(int count);

		void SetPosition(Vector3 pos);
		void SetRotation(Vector3 rot, float angle);
		void SetScale(Vector3 scale);

		//void SetAnimation(const Animation& anim) { mAnimation = anim; }

		void Draw(Camera& cam);

		void Update(float deltaTime);

		Bone* FindBone(const char* name);
		AnimationClip* FindAnimationClip(const char* name);

	};
}