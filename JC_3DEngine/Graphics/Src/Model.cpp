#include "Precompiled.h"
#include "Model.h"
#include "MeshBuilder.h"
#include "Texture.h"
#include "MeshBuffer.h"
#include "Camera.h"
#include "AnimationClip.h"

using namespace Graphics;

void Model::Load(const char* filename)
{
	LoadModel(filename, Meshes, Textures);
	//MeshBuilder::LoadModel(filename, Meshes, Textures);
	MeshBuffers.resize(Meshes.size());

	for (uint32_t currentMesh = 0; currentMesh < Meshes.size(); ++currentMesh)
	{
		MeshBuffers[currentMesh] = new MeshBuffer();
		MeshBuffers[currentMesh]->Initialize(Meshes[currentMesh]->GetVertices(),
			Meshes[currentMesh]->GetVertexCount(),
			Meshes[currentMesh]->GetIndices(),
			Meshes[currentMesh]->GetIndexCount());
	}

	mTextures = new Texture[Textures.size()];
	for (uint32_t i = 0; i < Textures.size(); ++i)
	{
		wchar_t fileName[1024];
		mbstowcs_s(nullptr, fileName, Textures[i].c_str(), 1024);
		std::wstring finalFileName;

		finalFileName = L"../Textures/";
		finalFileName += fileName;
		mTextures[i].Initialize(finalFileName.data());
	}

	mWorldBuffer.Initialize();
}

bool Graphics::Model::LoadModel(const char * filename, MeshList & meshes, TextureList & textures)
{
	FILE* modelFile;
	fopen_s(&modelFile, filename, "r");

	uint32_t textureCount;
	uint32_t meshCount;
	uint32_t vertCount;
	uint32_t indexCount;
	uint32_t numBones;
	uint32_t numAnims;

	// so these are......

	fscanf(modelFile, "MeshCount = %d\n", &meshCount);
	fscanf(modelFile, "TextureCount = %d\n", &textureCount);
	fscanf(modelFile, "BoneCount: %d\n", &numBones);
	fscanf(modelFile, "AnimationCount: %d\n", &numAnims);

	meshes.resize(meshCount);
	textures.resize(textureCount);

	for (uint32_t meshIndex = 0; meshIndex < meshCount; meshIndex++)
	{
		fscanf(modelFile, "VertexCount = %d\n", &vertCount);
		fscanf(modelFile, "IndexCount = %d\n", &indexCount);

		Graphics::Vertex* vertArray = new Graphics::Vertex[vertCount];
		for (uint32_t vertIndex = 0; vertIndex < vertCount; ++vertIndex)
		{
			fscanf(modelFile, "Position: %f %f %f\n", &vertArray[vertIndex].POS.x, &vertArray[vertIndex].POS.y, &vertArray[vertIndex].POS.z);
			fscanf(modelFile, "Normal: %f %f %f\n", &vertArray[vertIndex].NORM.x, &vertArray[vertIndex].NORM.y, &vertArray[vertIndex].NORM.z);
			fscanf(modelFile, "TextCoord: %f %f\n", &vertArray[vertIndex].UV.x, &vertArray[vertIndex].UV.y);
		}

		uint32_t * indexArray = new uint32_t[indexCount];
		for (uint32_t index = 0; index < indexCount; ++index)
		{
			fscanf(modelFile, "Vertex Index: %d\n", &indexArray[index]);
		}
		meshes[meshIndex] = new Mesh();
		meshes[meshIndex]->Initialize(vertArray, vertCount, indexArray, indexCount);
	}


	for (uint32_t textureIndex = 0; textureIndex < textureCount; textureIndex++)
	{
		char buffer[1024];
		fscanf(modelFile, "FileName: %s\n", buffer);
		textures[textureIndex] = buffer;
	}

	//Bone* boneArray = new Bone[numBones];
	std::string* nameArray = new std::string[numBones];
	uint32_t* parentArray = new uint32_t[numBones];
	uint32_t* childCountArray = new uint32_t[numBones];
	AnimationClip* animationArray = new AnimationClip[numAnims];

	mBones.resize(numBones);
	for (uint32_t boneIndex = 0; boneIndex < numBones; boneIndex++)
	{
		Bone* temp = new Bone();
		char buffer[1024];
		fscanf(modelFile, "Name: %s\n", buffer);
		temp->mName = buffer;
		fscanf(modelFile, "Parent: %d\n", &temp->parentIndex);
		//boneArray[boneIndex].mName = buffer;
		//fscanf(modelFile, "Parent: %d\n", &boneArray[boneIndex].parentIndex);


		uint32_t childCount; //TODO take away this 0
		fscanf(modelFile, "Children: %d\n", &childCount);

		temp->childrenIndex.resize(childCount);
		//boneArray[boneIndex].childrenIndex.resize(childCount);

		for (uint32_t childIndex = 0; childIndex < childCount; childIndex++)
		{
			fscanf(modelFile, "%d ", &temp->childrenIndex[childIndex]);
			//fscanf(modelFile, "%d ", &boneArray[boneIndex].childrenIndex[childIndex]);
		}
		fscanf(modelFile, "Transform: %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			&temp->transform.matrix[0], &temp->transform.matrix[1], &temp->transform.matrix[2],
			&temp->transform.matrix[3], &temp->transform.matrix[4], &temp->transform.matrix[5],
			&temp->transform.matrix[6], &temp->transform.matrix[7], &temp->transform.matrix[8],
			&temp->transform.matrix[9], &temp->transform.matrix[10], &temp->transform.matrix[11],
			&temp->transform.matrix[12], &temp->transform.matrix[13], &temp->transform.matrix[14],
			&temp->transform.matrix[15]
		);

		fscanf(modelFile, "OffsetTransform: %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			&temp->offsetTransform.matrix[0],
			&temp->offsetTransform.matrix[1],
			&temp->offsetTransform.matrix[2],
			&temp->offsetTransform.matrix[3],
			&temp->offsetTransform.matrix[4],
			&temp->offsetTransform.matrix[5],
			&temp->offsetTransform.matrix[6],
			&temp->offsetTransform.matrix[7],
			&temp->offsetTransform.matrix[8],
			&temp->offsetTransform.matrix[9],
			&temp->offsetTransform.matrix[10],
			&temp->offsetTransform.matrix[11],
			&temp->offsetTransform.matrix[12],
			&temp->offsetTransform.matrix[13],
			&temp->offsetTransform.matrix[14],
			&temp->offsetTransform.matrix[15]);

		fscanf(modelFile, "Bone Index: %d\n", &temp->index);
		if (temp->parentIndex == -1)
		{
			mRoot = temp;
		}		
		mBones[boneIndex] = temp;
		//fscanf(modelFile, "Bone Index: %d\n", &boneArray[boneIndex].index);
	}

	mAnimationClips.resize(numAnims);
	for (uint32_t animIndex = 0; animIndex < numAnims; animIndex++)
	{
		AnimationClip* tempAnim = new AnimationClip();
		char buffer[1024];
		fscanf(modelFile, "Name: %s\n", buffer);
		tempAnim->mName = buffer;
		//animationArray[animIndex].mName = buffer;
		fscanf(modelFile, "Duration: %f\n", &tempAnim->duration);
		//fscanf(modelFile, "Duration: %f\n", &animationArray[animIndex].duration);

		fscanf(modelFile, "TicksPerSecond: %f\n", &tempAnim->ticksPerSecond);
		//fscanf(modelFile, "TicksPerSecond: %f\n", &animationArray[animIndex].ticksPerSecond);
		int numBoneAnims = 0;
		fscanf(modelFile, "BoneAnimations: %d\n", &numBoneAnims);

		tempAnim->boneAnimations.resize(numBones);
		//animationArray[animIndex].boneAnimations.resize(numBoneAnims);
		for (int boneAnimIndex = 0; boneAnimIndex < numBoneAnims; boneAnimIndex++)
		{
			BoneAnimation* boneAnim = new BoneAnimation();
			//animationArray[animIndex].boneAnimations[boneAnimIndex] = new BoneAnimation();

			fscanf(modelFile, "Bone Index: %d\n", &boneAnim->boneIndex);
			//fscanf(modelFile, "Bone Index: %d\n", &animationArray[animIndex].boneAnimations[boneAnimIndex]->boneIndex);

			fscanf(modelFile, "Keyframes: %d\n", &tempAnim->keyFrameCount);
			//fscanf(modelFile, "Keyframes: %d\n", &animationArray[animIndex].keyFrameCount);

			std::vector<KeyFrame>& temp = boneAnim->keyframes;
			temp.resize(tempAnim->keyFrameCount);
			//tempAnim->boneAnimations[boneAnimIndex]->keyframes.resize(tempAnim->keyFrameCount);

			//std::vector<KeyFrame>& temp = animationArray[animIndex].boneAnimations[boneAnimIndex]->keyframes;
			//temp.resize(animationArray[animIndex].keyFrameCount);
			for (uint32_t keyframeIndex = 0; keyframeIndex < tempAnim->keyFrameCount; keyframeIndex++)
			{
				fscanf(modelFile, "Keyframe %d: %f %f %f %f %f %f %f %f %f %f %f\n",

					&keyframeIndex,
					&temp[keyframeIndex].position.x,
					&temp[keyframeIndex].position.y,
					&temp[keyframeIndex].position.z,

					&temp[keyframeIndex].rotation.x,
					&temp[keyframeIndex].rotation.y,
					&temp[keyframeIndex].rotation.z,
					&temp[keyframeIndex].rotation.w,

					&temp[keyframeIndex].scale.x,
					&temp[keyframeIndex].scale.y,
					&temp[keyframeIndex].scale.z,

					&temp[keyframeIndex].time
				);
				tempAnim->boneAnimations[boneAnim->boneIndex] = boneAnim;
			}
		}
		mAnimationClips[animIndex] = tempAnim;
	}
	AssignBonePointers(numBones);

	fclose(modelFile);
	return true;
}

void Model::AssignBonePointers(int count)
{
	for (int i = 0; i < count; i++)
	{
		if (mBones[i]->parentIndex != -1)
		{
			mBones[i]->parent = mBones[mBones[i]->parentIndex];
		}
		else
		{
			mRoot = mBones[i];
		}

		if (!mBones[i]->childrenIndex.empty())
		{
			mBones[i]->children.resize(mBones[i]->childrenIndex.size());
			for (uint32_t j = 0; j < mBones[i]->childrenIndex.size(); j++)
			{
				mBones[i]->children[j] = mBones[mBones[i]->childrenIndex[j]];
			}
		}
	}
}


void Model::Unload()
{
	for (uint32_t currentMesh = 0; currentMesh < Meshes.size(); ++currentMesh)
	{
		SafeDelete(Meshes[currentMesh]);
		SafeDelete(MeshBuffers[currentMesh]);
	}

	for (uint32_t currentTexture = 0; currentTexture < Textures.size(); ++currentTexture)
	{
		mTextures[currentTexture].Terminate();
	}

	mWorldBuffer.Terminate();
}

void Model::SetPosition(Vector3 pos)
{
	mPosition = pos;
}
void Model::SetRotation(Vector3 rot, float angle)
{
	mRotationMatrix = Matrix::RotationAxis(rot, angle);
}
void Model::SetScale(Vector3 scale)
{
	mScale = scale;
}

void Model::Draw(Camera& cam)
{
	WorldInfo w;
	auto translate = Matrix::Translation(mPosition);
	auto scale = Matrix::MakeScaleMatrix(mScale);

	auto world = scale * mRotationMatrix * translate;

	Matrix view = cam.GetViewMatrix();
	Matrix projection = cam.GetProjectionMatrix();

	Matrix WVP = world * view * projection;

	w.world = Matrix::Transpose(world);
	w.wvp = Matrix::Transpose(WVP);

	w.cameraPosition = cam.GetPosition();

	mWorldBuffer.Set(w);

	mWorldBuffer.BindVS();
	mWorldBuffer.BindPS();

	for (uint32_t i = 0; i < Meshes.size(); ++i)
	{
		mTextures[i].BindPS(0);
		MeshBuffers[i]->Draw();
	}
}

void Graphics::Model::Update(float deltaTime)
{
	//mWorldTransform = mAnimation.Update(deltaTime);
}

Bone * Graphics::Model::FindBone(const char * name)
{
	for (auto bone : mBones)
	{
		if (strcmp(name, bone->mName.c_str()) == 0)
		{
			return bone;
		}
	}

	return nullptr;
}

AnimationClip* Graphics::Model::FindAnimationClip(const char * name)
{
	for (auto animClip : mAnimationClips)
	{
		if (strcmp(name, animClip->mName.c_str()) == 0)
		{
			return animClip;
		}
	}

	return nullptr;
}
