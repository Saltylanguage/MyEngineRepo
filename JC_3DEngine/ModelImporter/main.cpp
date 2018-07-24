#include <Graphics\Inc\Graphics.h>
#include <assimp/Importer.hpp>  //C++ importer interface
#include <assimp/scene.h>		// Output Data Structure
#include <assimp/postprocess.h> // Post Proecessing Flags
#include <cstdio>
#include <cstdlib>
#include <vector>

#pragma comment(lib, "assimp.lib")

typedef std::vector<Graphics::Mesh*> MeshList;
typedef std::vector<std::string> TextureList;
typedef std::map<std::string, uint32_t> BoneIndexMap;
typedef std::vector<Graphics::AnimationClip*> AnimationList;


Graphics::Bones gBones;
BoneIndexMap gBoneIndexMap;
Graphics::Bone* gRoot;
AnimationList gAnimations;

//TODO edit Argument names in Properties -> Command Arguments
struct Params
{

	Params()
		:inputFileName(nullptr),
		outputFileName(nullptr)
	{}

	const char* inputFileName;
	const char* outputFileName;
};



void PrintHelp()
{

	printf(
		"== ModelImporter help ==\n"
		"\n"
		"Usage:\n"
		"\n"
		"ModelImporter.exe <InputFile> <OutputFile>\n"
		"\n"
		"Options\n"
		"\n"
		"n/a\n"
		"\n"
		);
}

void ParseArg(int argc, char* argv[], Params& params)
{
	params.inputFileName = argv[argc - 2];
	params.outputFileName = argv[argc - 1];


}

Matrix GetAiMatrix(const aiMatrix4x4& aiMatrix)
{
	
	Matrix mat = *(Matrix*)&aiMatrix;
	mat = Matrix::Transpose(mat);
	return mat;
}


uint32_t GetBoneIndex(aiBone* bone)
{
	auto iter = gBoneIndexMap.find(bone->mName.C_Str());
	if (iter != gBoneIndexMap.end())
	{
		return iter->second;
	}

	uint32_t boneIndex = gBones.size();

	Graphics::Bone* newBone = new Graphics::Bone();

	ASSERT(bone->mName.length > 0, "Error: Bone %d doesn't have a name!", boneIndex);

	newBone->mName = bone->mName.C_Str();
	newBone->index = boneIndex;
	newBone->offsetTransform = GetAiMatrix(bone->mOffsetMatrix);

	gBones.push_back(newBone);
	gBoneIndexMap.insert(std::make_pair(newBone->mName.c_str(), boneIndex));

	return boneIndex;
}


Graphics::Bone* BuildSkeleton(aiNode& aiNode, Graphics::Bone* parent)
{
	Graphics::Bone* bone = nullptr;

	auto iter = gBoneIndexMap.find(aiNode.mName.C_Str());
	if (iter == gBoneIndexMap.end())
	{
		const uint32_t boneIndex = gBones.size();

		bone = new Graphics::Bone();
		bone->index = boneIndex;
		Matrix matrix;
		matrix.Identity();
		bone->offsetTransform = GetAiMatrix(aiNode.mTransformation);

		if (aiNode.mName.length > 0)  // if the bone already has a name use that name
		{
			bone->mName = aiNode.mName.C_Str();
		}
		else // otherwise give it a name ensuring all bones have a valid name
		{
			char buffer[128];
			sprintf_s(buffer, 128, "unamed_%u", boneIndex);
			printf("Warning: Bone %u has no name, renamed to %s\n",
				boneIndex, buffer);
			bone->mName = buffer;
		}

		gBones.push_back(bone);
		gBoneIndexMap.insert(std::make_pair(bone->mName, bone->index));
	}
	else
	{
		bone = gBones[iter->second];
	}

	bone->transform = GetAiMatrix(aiNode.mTransformation);
	bone->parent = parent;	
	
	if (bone->parent)
	{
		bone->parentIndex = parent->index;
	}

	for (uint32_t i = 0; i < aiNode.mNumChildren; i++)
	{
		Graphics::Bone* child = BuildSkeleton(*(aiNode.mChildren[i]), bone);
		bone->children.push_back(child);
		bone->childrenIndex.push_back(child->index);
	}

	return bone;

}


bool ImportModel(const Params& params, MeshList& meshes, TextureList& textures)
{
	//Create an instance of the importer class...
	Assimp::Importer importer;

	//...and have it read the given file with some example postprocessing.
	//Usually - if speed is not the most imporotant aspect for you - you'll
	// probably want to request more post processingthan we do in this example
	const uint32_t flags =
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_FlipUVs;
		aiProcess_ConvertToLeftHanded;

	const aiScene* scene = importer.ReadFile(params.inputFileName, flags);

	//if the import failed, report it
	if (scene == nullptr)
	{
		printf("ModelImporter -- Error: %s\n", importer.GetErrorString());
		return false;
	}

	//read mesh data
	if (scene->HasMeshes())
	{
		printf("Reading Mesh Data");

		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			aiMesh* aiMesh = scene->mMeshes[meshIndex];

			Graphics::Vertex* vertices = new Graphics::Vertex[aiMesh->mNumVertices];

			//vertex POS info
			printf("Reading positions....\n");
			for (uint32_t i = 0; i < aiMesh->mNumVertices; ++i)
			{
				Graphics::Vertex& vertex = vertices[i];
				vertex.POS.x = aiMesh->mVertices[i].x;
				vertex.POS.y = aiMesh->mVertices[i].y;
				vertex.POS.z = aiMesh->mVertices[i].z;
			}

			//vertex NORM info
			if (aiMesh->HasNormals())
			{
				printf("Reading Normals...\n");

				for (uint32_t i = 0; i < aiMesh->mNumVertices; ++i)
				{
					Graphics::Vertex& vertex = vertices[i];
					vertex.NORM.x = aiMesh->mNormals[i].x;
					vertex.NORM.y = aiMesh->mNormals[i].y;
					vertex.NORM.z = aiMesh->mNormals[i].z;
				}
			}

			//vertex UV info
			if (aiMesh->HasTextureCoords(0))
			{
				printf("Reading Texture Coordinates...\n");

				for (uint32_t i = 0; i < aiMesh->mNumVertices; ++i)
				{
					Graphics::Vertex& vertex = vertices[i];
					vertex.UV.x = aiMesh->mTextureCoords[0][i].x;
					vertex.UV.y = aiMesh->mTextureCoords[0][i].y;
				}			  
			}
			//indices info
			printf("Reading Indices...\n");

			uint32_t* indices = new uint32_t[aiMesh->mNumFaces * 3];

			for (uint32_t face = 0, index = 0; face < aiMesh->mNumFaces; ++face, index += 3)
			{
				indices[index] = aiMesh->mFaces[face].mIndices[0];
				indices[index + 1] = aiMesh->mFaces[face].mIndices[1];
				indices[index + 2] = aiMesh->mFaces[face].mIndices[2];
			}

			//add mesh to our list

			Graphics::Mesh* mesh = new Graphics::Mesh();
			Graphics::MeshBuilder::GenerateMesh(*mesh, vertices, aiMesh->mNumVertices, indices, aiMesh->mNumFaces * 3);
			meshes.push_back(mesh);

			if (aiMesh->HasBones())
			{
				printf("Reading bone weights....\n");

				std::vector<uint32_t> numWeights;
				numWeights.resize(mesh->GetVertexCount(), 0);

				for (uint32_t i = 0; i < aiMesh->mNumBones; i++)
				{
					aiBone* aiBone = aiMesh->mBones[i];
					uint32_t boneIndex = GetBoneIndex(aiBone);



					for (uint32_t j = 0; j < aiBone->mNumWeights; j++)
					{
						const aiVertexWeight& aiVertexWeight = aiBone->mWeights[j];
						const uint32_t vertexIndex = aiVertexWeight.mVertexId;

						if (numWeights[vertexIndex] < 4)
						{
							const uint32_t weightIndex = numWeights[vertexIndex]++;
							mesh->GetVertex(vertexIndex).boneIndex[weightIndex] = (int)boneIndex;
							mesh->GetVertex(vertexIndex).boneIndex[weightIndex] = (int)aiVertexWeight.mWeight;

							gBones[boneIndex]->offsetTransform = GetAiMatrix(aiBone->mOffsetMatrix);
						}
					}
				}
			}
		}
	}

	//read material data
	if (scene->HasMaterials())
	{
		printf("Reading Materials...\n");

		for (uint32_t i = 0; i < scene->mNumMaterials; ++i)
		{
			const aiMaterial* material = scene->mMaterials[i];

			const uint32_t textureCount = material->GetTextureCount(aiTextureType_DIFFUSE);
			if (textureCount > 0)
			{
				aiString texturePath;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
				{
					//copy from the last \ if there is one
					const char* filename = strrchr(texturePath.C_Str(), '\\');
					if (filename == nullptr)
					{
						//if no \ found, copy from the last / if there is one
						filename = strrchr(texturePath.C_Str(), '/');
						if (filename == nullptr)
						{
							//if no / found just ocpy the string as is
							filename = texturePath.C_Str();
						}
						else
						{
							filename++;
						}
					}
					else
					{
						filename++;
					}
					printf("Info: adding texture %s\n", filename);
					textures.push_back(filename);
				}
			}

		}
	}

	gRoot = BuildSkeleton(*scene->mRootNode, nullptr);  // find the root bone

	if (scene->HasAnimations())
	{
		for (uint32_t animIndex = 0; animIndex < scene->mNumAnimations; ++animIndex)
		{
			aiAnimation* aiAnim = scene->mAnimations[animIndex];
			
			Graphics::AnimationClip* animClip = new Graphics::AnimationClip();

			if (aiAnim->mName.length > 0)  // if the animation already has a name use it
			{
				aiAnim->mName = aiAnim->mName.C_Str();
			}
			else // otherwise give it a name to ensure all animations have a valid name
			{
				char buffer[128];
				sprintf_s(buffer, 128, "Anim%d", animIndex);
				animClip->mName = buffer;
				printf("Warning: Animation %u has no name, renamed to %s\n", gAnimations.size(), buffer);				
			}

			animClip->duration = (float)aiAnim->mDuration;
			animClip->ticksPerSecond = (float)aiAnim->mTicksPerSecond;
			
			if (animClip->ticksPerSecond == 0.0f)
			{
				printf("Warning: Animation %s has ticks per second 0.0. Assuming 1.0.\n", animClip->mName.c_str());
				animClip->ticksPerSecond = 1.0f;
			}
			

			for (uint32_t boneAnimationIndex = 0; boneAnimationIndex < aiAnim->mNumChannels; ++boneAnimationIndex)
			{
				aiNodeAnim* aiNodeAnim = aiAnim->mChannels[boneAnimationIndex];

				Graphics::BoneAnimation* boneAnim = new Graphics::BoneAnimation();
				boneAnim->boneIndex = gBoneIndexMap.at(aiNodeAnim->mNodeName.C_Str());

				ASSERT(aiNodeAnim->mNumPositionKeys == aiNodeAnim->mNumRotationKeys, "Mismatched key Count");
				ASSERT(aiNodeAnim->mNumPositionKeys == aiNodeAnim->mNumScalingKeys, "Mismatched key Count");

				boneAnim->keyframes.resize(aiNodeAnim->mNumPositionKeys);

				for (uint32_t keyIndex = 0; keyIndex < aiNodeAnim->mNumPositionKeys; ++keyIndex)
				{
					const aiVectorKey& posKey = aiNodeAnim->mPositionKeys[keyIndex];
					const aiQuatKey& rotKey = aiNodeAnim->mRotationKeys[keyIndex];
					const aiVectorKey& scaleKey = aiNodeAnim->mScalingKeys[keyIndex];

					ASSERT(posKey.mTime == rotKey.mTime, "Mismatched key time.");
					ASSERT(posKey.mTime == scaleKey.mTime, "Mismatched key time.");

					boneAnim->keyframes[keyIndex].position = Vector3(posKey.mValue.x, posKey.mValue.y, posKey.mValue.z);
					boneAnim->keyframes[keyIndex].rotation = Quaternion(rotKey.mValue.x, rotKey.mValue.y, rotKey.mValue.z, rotKey.mValue.w);
					boneAnim->keyframes[keyIndex].scale = Vector3(scaleKey.mValue.x, scaleKey.mValue.y, scaleKey.mValue.z);
					boneAnim->keyframes[keyIndex].time = (float)posKey.mTime;
					
				
				}
				//animClip->keyFrameCount = aiNodeAnim->mNumPositionKeys;
				//gAnimations[animIndex]->keyFrameCount = animClip->keyFrameCount;
				animClip->boneAnimations.push_back(boneAnim);
				

			}

			gAnimations.push_back(animClip);
		}

	}

	return true;
}


bool SaveModel(const Params& params, const MeshList& meshes, const TextureList& textures)
{
	//homework
	//Save the data into a text file
	// - use FILE* file, fopen_s, fclose, fprintf
	//Bone Formatting
	//	Name: Hand_Left
	//	Parent : 4
	//	Children : 2
	//	46 1
	//	Transform : 0.999032 0.008157 0.043240 0.000000 0.010838 0.906787 -0.421451 0.000000 -0.042647 0.421511 0.905820 -0.000000 0.283514 0.000000 -0.000000 1.000000
	//	Transform : 0.722701 - 0.127437 - 0.679311 0.000000 - 0.668992 0.117955 - 0.733851 0.000000 0.173648 0.984808 - 0.000009 - 0.000000 0.291244 - 0.064009 1.182338 1.000000
	//	Index : 0

	FILE* modelFile;

	fopen_s(&modelFile, params.outputFileName, "w");

	fprintf(modelFile, "MeshCount = %d\n", meshes.size());
	fprintf(modelFile, "TextureCount = %d\n", textures.size());
	fprintf(modelFile, "BoneCount: %d\n", gBones.size());
	fprintf(modelFile, "AnimationCount: %d\n", gAnimations.size());

	for (uint32_t meshIndex = 0; meshIndex < meshes.size(); meshIndex++)
	{
		fprintf(modelFile, "VertexCount = %d\n", meshes[meshIndex]->GetVertexCount());
		fprintf(modelFile, "IndexCount = %d\n", meshes[meshIndex]->GetIndexCount());
		for (uint32_t vertIndex = 0; vertIndex < meshes[meshIndex]->GetVertexCount(); vertIndex++)
		{
			fprintf(modelFile, "Position: %f %f %f\n", meshes[meshIndex]->GetVertices()[vertIndex].POS.x, meshes[meshIndex]->GetVertices()[vertIndex].POS.y, meshes[meshIndex]->GetVertices()[vertIndex].POS.z);
			fprintf(modelFile, "Normal: %f %f %f\n", meshes[meshIndex]->GetVertices()[vertIndex].NORM.x, meshes[meshIndex]->GetVertices()[vertIndex].NORM.y, meshes[meshIndex]->GetVertices()[vertIndex].NORM.z);
			fprintf(modelFile, "TextCoord: %f %f\n", meshes[meshIndex]->GetVertices()[vertIndex].UV.x, meshes[meshIndex]->GetVertices()[vertIndex].UV.y);
		}
		for (uint32_t index = 0; index < meshes[meshIndex]->GetIndexCount(); index++)
		{
			fprintf(modelFile, "Vertex Index: %d\n", meshes[meshIndex]->indices[index]);
		}
	}

	for (uint32_t textureIndex = 0; textureIndex < textures.size(); textureIndex++)
	{
		fprintf(modelFile, "FileName: %s\n", textures[textureIndex].c_str());
	}

	for (uint32_t boneIndex = 0; boneIndex < gBones.size(); boneIndex++)
	{
		fprintf(modelFile, "Name: %s\n", gBones[boneIndex]->mName.c_str());
		fprintf(modelFile, "Parent: %d\n", gBones[boneIndex]->parentIndex);

		fprintf(modelFile, "Children: %d\n", gBones[boneIndex]->children.size());

		for (uint32_t childIndex = 0; childIndex < gBones[boneIndex]->children.size(); childIndex++)
		{
			fprintf(modelFile, "%d ", gBones[boneIndex]->childrenIndex[childIndex]);
		}

		if (gBones[boneIndex]->children.size() > 0)
		{
			fprintf(modelFile, "\n");
		}

		fprintf(modelFile, "Transform: %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			gBones[boneIndex]->transform.matrix[0],
			gBones[boneIndex]->transform.matrix[1],
			gBones[boneIndex]->transform.matrix[2],
			gBones[boneIndex]->transform.matrix[3],
			gBones[boneIndex]->transform.matrix[4],
			gBones[boneIndex]->transform.matrix[5],
			gBones[boneIndex]->transform.matrix[6],
			gBones[boneIndex]->transform.matrix[7],
			gBones[boneIndex]->transform.matrix[8],
			gBones[boneIndex]->transform.matrix[9],
			gBones[boneIndex]->transform.matrix[10],
			gBones[boneIndex]->transform.matrix[11],
			gBones[boneIndex]->transform.matrix[12],
			gBones[boneIndex]->transform.matrix[13],
			gBones[boneIndex]->transform.matrix[14],
			gBones[boneIndex]->transform.matrix[15]);

		fprintf(modelFile, "OffsetTransform: %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			gBones[boneIndex]->offsetTransform.matrix[0],
			gBones[boneIndex]->offsetTransform.matrix[1],
			gBones[boneIndex]->offsetTransform.matrix[2],
			gBones[boneIndex]->offsetTransform.matrix[3],
			gBones[boneIndex]->offsetTransform.matrix[4],
			gBones[boneIndex]->offsetTransform.matrix[5],
			gBones[boneIndex]->offsetTransform.matrix[6],
			gBones[boneIndex]->offsetTransform.matrix[7],
			gBones[boneIndex]->offsetTransform.matrix[8],
			gBones[boneIndex]->offsetTransform.matrix[9],
			gBones[boneIndex]->offsetTransform.matrix[10],
			gBones[boneIndex]->offsetTransform.matrix[11],
			gBones[boneIndex]->offsetTransform.matrix[12],
			gBones[boneIndex]->offsetTransform.matrix[13],
			gBones[boneIndex]->offsetTransform.matrix[14],
			gBones[boneIndex]->offsetTransform.matrix[15]);

		fprintf(modelFile, "Bone Index: %d\n", gBones[boneIndex]->index);
	}

	for (size_t animIndex = 0; animIndex < gAnimations.size(); animIndex++)
	{
		fprintf(modelFile, "Name: %s\n", gAnimations[animIndex]->mName.c_str());
		fprintf(modelFile, "Duration: %f\n", gAnimations[animIndex]->duration);
		fprintf(modelFile, "TicksPerSecond: %f\n", gAnimations[animIndex]->ticksPerSecond);
		fprintf(modelFile, "BoneAnimations: %d\n", gAnimations[animIndex]->boneAnimations.size());
		for (size_t boneAnimIndex = 0; boneAnimIndex < gAnimations[animIndex]->boneAnimations.size(); boneAnimIndex++)
		{
			fprintf(modelFile, "BoneIndex: %d\n", gAnimations[animIndex]->boneAnimations[boneAnimIndex]->boneIndex);
			fprintf(modelFile, "Keyframes: %d\n", gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes.size());
			for (size_t keyframeIndex = 0; keyframeIndex < gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes.size(); keyframeIndex++)
			{

				// KeyFrame:
				// 3 Values for Position
				// 4 Values for Rotation
				// 3 Values for Scale
				// 1 Value for time

				fprintf(modelFile, "Keyframe %d: %f %f %f %f %f %f %f %f %f %f %f\n",

					keyframeIndex,
					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].position.x,
					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].position.y,
					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].position.z,

					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].rotation.x,
					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].rotation.y,
					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].rotation.z,
					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].rotation.w,

					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].scale.x,
					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].scale.y,
					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].scale.z,

					gAnimations[animIndex]->boneAnimations[boneAnimIndex]->keyframes[keyframeIndex].time

					);
			}
		}

	}

	//Graphics::Bones gBones;
	//BoneIndexMap gBoneIndexMap;
	//Graphics::Bone* gRoot;
	//AnimationList gAnimations;

	return true;
}

int main(int argc, char* argv[])
{

	if (argc < 3)
	{
		PrintHelp();
		return -1;
	}

	Params params;
	ParseArg(argc, argv, params);

	MeshList meshes;
	TextureList textures;
	if (!ImportModel(params, meshes, textures))
	{
		printf("ModelImporter -- Import Failed\n");
		return -1;
	}

	if (!SaveModel(params, meshes, textures))
	{
		printf("ModelImporter -- Save Failed\n");
		return -1;
	}

	//clean up
	std::for_each(meshes.begin(), meshes.end(), [](auto m) {m->Terminate(); delete m; });
	meshes.clear();

	printf("Success!\n");
	return 0;
}


//feed one of the models in
//write bone count and animation count

//write bone info:
//name : Hand_Left
//parent : 4
//children: 2


//write anim info
//name: anim1
//duration: 12800.00000
//ticksPersecond: 1.0000000
//boneanimations: 35
//boneindex: 25
//keyframes: 81
