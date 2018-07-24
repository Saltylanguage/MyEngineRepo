#ifndef INCLUDED_ENGINE_CURSORCOMPONENT_H
#define INCLUDED_ENGINE_CURSORCOMPONENT_H

#include "Component.h"

class SpriteComponent;

class CursorComponent : public Component
{
public:
	META_CLASS_DECLARE;

	CursorComponent();
	~CursorComponent() override;

	void Initialize() override;
	void Update(f32 deltaTime) override;

private:
	SpriteComponent* mSpriteComponent;
};

#endif // #ifndef INCLUDED_ENGINE_CURSORCOMPONENT_H