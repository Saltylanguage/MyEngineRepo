#include "Precompiled.h"
#include "HeightMap.h"
#include <fstream>

using namespace Graphics;

namespace
{
	inline uint32_t GetIndex(uint32_t x, uint32_t y, uint32_t width)
	{
		return x + (y *width);
	}
}

HeightMap::HeightMap() : mHeightValues(nullptr), mColumns(0), mRows(0)
{
}

HeightMap::~HeightMap()
{
	ASSERT(mHeightValues == nullptr, "[HeightMap] HeightMap values not freed");
}

void Graphics::HeightMap::GenerateFromRAW(const char * filename, uint32_t columns, uint32_t rows)
{

	ASSERT(mHeightValues == nullptr, "[HeightMap] is already initialized.");
	ASSERT(columns > 0, "[HeightMap] invalid value for columns.");
	ASSERT(rows > 0, "[HeightMap] invalid value for rows.");

	std::ifstream fileI(filename, std::ios::binary); // file loading as binary

	uint32_t byteSize = columns * rows * 4;

	char* buffer = new char[byteSize];



	fileI.read(buffer, byteSize);

	mHeightValues = reinterpret_cast<float*>(buffer);

	// Normalize height values so they are between 0 to 1
	for (uint32_t i = 0; i < columns * rows; ++i)
	{
		mHeightValues[i] /= 255.0f;
	}

	mColumns = columns;
	mRows = rows;
	


}

void Graphics::HeightMap::Clear()
{
	SafeDeleteArrays(mHeightValues);
	mColumns = 0;
	mRows = 0;
}

float Graphics::HeightMap::GetHeight(uint32_t x, uint32_t y) const
{
	ASSERT(x < mColumns, "[Heightmap] Invalid value for x.");
	ASSERT(y < mRows, "[Heightmap] Invalid value for y.");
	return mHeightValues[GetIndex(x, y, mColumns)];
}


