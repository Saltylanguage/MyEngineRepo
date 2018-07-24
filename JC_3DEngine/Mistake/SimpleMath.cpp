#include "Precompiled.h"
#include "SimpleMath.h"

float Math::General::Abs(float value)
{
	return value < 0 ? value * -1 : value;
}