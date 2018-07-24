#pragma once

namespace Graphics
{
	class HeightMap
	{
	public:
		HeightMap();
		~HeightMap();

		void GenerateFromRAW(const char* filename, uint32_t columns, uint32_t rows);
		void Clear();

		float GetHeight(uint32_t x, uint32_t y) const;
		uint32_t GetColumns() const { return mColumns; }
		uint32_t GetRows() const { return mRows; }

	private:
		NONCOPYABLE(HeightMap);

		float* mHeightValues;
		uint32_t mColumns;
		uint32_t mRows;

	};
}