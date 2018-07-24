#pragma once

//====================================================================================================
// Includes
//====================================================================================================

#include <Core\Inc\Core.h>
#include <Math\Inc\EngineMath.h>

//====================================================================================================
// Forward Declarations
//====================================================================================================


namespace DirectX
{
	class CommonStates;
	class SpriteBatch;
}
namespace Graphics
{

	class Texture;
	class GraphicsSystem;
	//====================================================================================================
	// Class Declarations
	//====================================================================================================

	class SpriteRenderer
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static SpriteRenderer* Get();

	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Initialize();
		void Terminate();

		void BeginRender();
		void EndRender();

		void Draw(Texture& texture, const Math::Vector2& position);

		DirectX::SpriteBatch* GetSpriteBatch() { return mpSpriteBatch; }

	private:
		NONCOPYABLE(SpriteRenderer);

		friend class Font;

		DirectX::CommonStates* mpStateObjects;
		DirectX::SpriteBatch* mpSpriteBatch;
	};
}