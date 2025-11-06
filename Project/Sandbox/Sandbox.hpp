#pragma once
#include <Engine.hpp>
#include "Player.hpp"

class Sandbox : public Unknown::Application
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	void UpdateViewport();
	void OnInitialize() override;
private:
	void OnGameRender();
	void ProcessInput();
private:
	Player mPlayer;
};