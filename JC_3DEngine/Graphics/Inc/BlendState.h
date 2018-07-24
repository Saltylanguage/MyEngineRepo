#ifndef INCLUDED_GRAPHICS_BLENDSTATE_H
#define INCLUDED_GRAPHICS_BLENDSTATE_H

//====================================================================================================
// Filename:	BlendState.h
// Created by:	Peter Chan
// Description:	Class for controlling the blend state.
//====================================================================================================

namespace Graphics {

class BlendState
{
public:
	enum class Mode
	{
		Opaque,
		AlphaBlend,
		AlphaPremultiplied,
		Additive
	};

	BlendState();
	~BlendState();

	void Initialize(Mode mode);
	void Terminate();

	void Set();
	void Clear();

private:
	ID3D11BlendState* mBlendState;
};

} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_BLENDSTATE_H