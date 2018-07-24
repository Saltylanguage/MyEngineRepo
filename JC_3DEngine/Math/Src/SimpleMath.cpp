#include "Precompiled.h"
#include "Math\Inc\SimpleMath.h"

float Math::General::Abs(float value)
{
	return value < 0 ? value * -1 : value;
}