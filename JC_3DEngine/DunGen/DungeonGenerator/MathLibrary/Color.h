#pragma once

class Color
{
	Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f)
	{}
	Color(float red, float green, float blue, float alpha) : 
	r(red), g(green), b(blue), a(alpha)
	{}

	float r; 
	float g;
	float b;
	float a;

	static Color White;
	static Color Black;
	static Color Red;
	static Color Green;
	static Color Blue;
	static Color Yellow;
	static Color Orange;
	static Color Cyan;
	static Color Purple;
	static Color Magenta;

};