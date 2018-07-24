#ifndef INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

//Description: Class for the game application

#include <Core\Inc\Core.h>
#include <Graphics\Inc\Graphics.h>
#include <Input\Inc\Input.h>
#include <PhysicsLibrary\Inc\Physics.h>

class GameApp : public Core::Application
{
public:
	GameApp();

	virtual ~GameApp();

private:
	virtual void OnInitialize(uint32_t width, uint32_t height) override;
	virtual void OnTerminate() override;
	virtual void OnUpdate() override;

	void SpawnParticles();

	//Window
	Core::Window mWindow;
	Core::Timer mTimer;

	Physics::PhysicsWorld mWorld;

	Graphics::Camera mCamera;

	

};

#endif //ifndef INCLUDED_GAMEAPP_H