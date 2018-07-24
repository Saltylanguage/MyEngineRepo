#ifndef INCLUDED_GRAPHICS_BONE_H
#define INCLUDED_GRAPHICS_BONE_H
#include "Core\Inc\Core.h"

//====================================================================================================
// Filename:	Bone.h
// Created by:	Peter Chan
// Description:	Struct for a skeleton bone.
//====================================================================================================

namespace Graphics {

struct Bone;

typedef std::vector<Bone*> Bones;

struct Bone
{
	Bone()
		: parent(nullptr)
		, parentIndex(-1)
		, index(0)
	{}

	std::string mName;

	Bone* parent;
	Bones children;

	int parentIndex;
	std::vector<uint32_t> childrenIndex;

	Matrix transform;
	Matrix offsetTransform;

	uint32_t index;
};

} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_BONE_H