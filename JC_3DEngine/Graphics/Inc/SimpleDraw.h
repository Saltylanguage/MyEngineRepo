#ifndef INCLUDED_GRAPHICS_SIMPLEDRAW_H
#define INCLUDED_GRAPHICS_SIMPLEDRAW_H

//====================================================================================================
// Filename:	SimpleDraw.h
// Created by:	Josh Campbell
// Description:	Header containing some useful rendering functions for debug purposes.
//====================================================================================================

using namespace Math;

namespace Graphics {

class Camera;

namespace SimpleDraw {

// Functions to startup/shutdown simple draw
void Initialize(uint32_t maxVertices = 10000);
void Terminate();

// Functions for world space rendering
void AddLine(const Vector3& v0, const Vector3& v1, const Vector4& color);
void AddLine(float x0, float y0, float z0, float x1, float y1, float z1, const Vector4& color);
void AddAABB(const AABB& aabb, const Vector4& color);
void AddAABB(const Vector3& min, const Vector3& max, const Vector4& color);
void AddAABB(const Vector3& center, float radius, const Vector4& color);
void AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Vector4& color);
void AddOBB(const OBB& obb, const Vector4& color);
void AddSphere(const Sphere& sphere, const Vector4& color, uint32_t slices = 8, uint32_t rings = 4);
void AddSphere(const Vector3& center, float radius, const Vector4& color, uint32_t slices = 8, uint32_t rings = 4);
void AddSphere(float x, float y, float z, float radius, const Vector4& color, uint32_t slices = 8, uint32_t rings = 4);
void AddTransform(const Matrix& transform);
void AddPlane(const Plane& plane, const Vector3& referencePoint, float size, float spacing, Vector4 color);

// Functions for screen space rendering
void AddScreenLine(const Vector2& v0, const Vector2& v1, const Vector4& color);
void AddScreenLine(float x0, float y0, float x1, float y1, const Vector4& color);
void AddScreenRect(const Rect& rect, const Vector4& color);
void AddScreenRect(const Vector2& min, const Vector2& max, const Vector4& color);
void AddScreenRect(float left, float top, float right, float bottom, const Vector4& color);
void AddScreenCircle(const Circle& circle, const Vector4& color);
void AddScreenCircle(const Vector2& center, float r, const Vector4& color);
void AddScreenCircle(float x, float y, float r, const Vector4& color);

// Function to actually render all the geometry.
void Render(const Camera& camera);

} // namespace SimpleDraw
} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_SIMPLEDRAW_H