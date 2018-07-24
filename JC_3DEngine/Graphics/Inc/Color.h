#pragma once

namespace Graphics
{
	struct Color
	{
		float r, g, b, a;

		Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
		Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		Color& operator=(const Color& other) { r = other.r; g = other.g; b = other.b; a = other.a; }
	
		static Color Red();
		static Color Green();
		static Color Blue();
		static Color Yellow();
		static Color Cyan();
		static Color Magenta();
		static Color Black();
		static Color White();
	};


	//====================================================================================================
	// Inline Definitions
	//====================================================================================================

	inline Color Color::Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
	inline Color Color::Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
	inline Color Color::Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
	inline Color Color::Yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }
	inline Color Color::Cyan() { return Color(0.0f, 1.0f, 1.0f, 1.0f); }
	inline Color Color::Magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }
	inline Color Color::Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
	inline Color Color::White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }

}