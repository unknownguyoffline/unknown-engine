#include "Sandbox.hpp"

using namespace glm;
using namespace Unknown;

void Sandbox::OnInitialize()
{
	WindowProperty windowProperty = GetProperty().windowProperty;
	//windowProperty.fullscreen = true;
	SetProperty({ windowProperty });
}

void Sandbox::OnGameRender()
{
	GetRenderer2D()->BeginFrame();
	GetRenderer2D()->PushQuadrilateral({ vec3(0), vec3(0), vec3(100), Maths::HexRGBA(0xfc7b49ff)});
	mPlayer.Update();
	GetRenderer2D()->EndFrame();
}

void Sandbox::ProcessInput()
{
	if (GetInput().keyboard.keyK)
		Close();
}

void Sandbox::OnStart()
{
	mPlayer.Initialize();
}

void Sandbox::OnUpdate()
{
	UpdateViewport();
	ProcessInput();
	OnGameRender();
}

void Sandbox::OnEnd()
{
	mPlayer.Terminate();
}

void Sandbox::UpdateViewport()
{
	Viewport viewport;
	viewport.size = GetWindow()->GetSize();
	GetRenderer2D()->SetViewport(viewport);
}

CREATE_APPLICATION(Sandbox)


