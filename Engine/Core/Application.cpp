#include <Core/Application.hpp>
#include <Utility/Timer.hpp>
#include "Macro.hpp"

namespace Unk
{
	void Application::Initialize()
	{
		UNK_CORE_ASSERT("Application already created", mInstance != nullptr);

		mTimer.Start();

		OnInitialize();

		mWindow.reset(Window::Create(mProperty.windowProperty));
		mRenderer.reset(new Renderer(mProperty.rendererProperty));
		mLayerStack.reset(new LayerStack);

		OnStart();
		mLayerStack->RunOnStart();
	}

	void Application::Run()
	{
		Initialize();
		MainLoop();
		Terminate();
	}

	void Application::MainLoop()
	{
		float dt = 0;
		Timer frameTimer;

		while (mRunning)
		{
			frameTimer.Start();

			ProcessEvent();
			mRunning = !mWindow->GetProperty().closed;
			OnUpdate(dt);
			mLayerStack->RunOnUpdate();

			mWindow->SwapBuffer();

			dt = frameTimer.End();
		}
	}

	void Application::Terminate()
	{
		OnEnd();
		mLayerStack->RunOnEnd();
	}

	void Application::Close()
	{
		mRunning = false;
	}

	Timer& Application::GetTimerRef()
	{
		return mTimer;
	}

	Timer Application::GetTimer()
	{
		return mTimer;
	}

	Application::Application()
	{
		UNK_CORE_ASSERT("Application already created", mInstance == nullptr);
		mInstance = this;
	}

	Application::~Application()
	{

	}

	void Application::ProcessEvent()
	{
		mWindow->ProcessInput();
	}

	Application* Application::mInstance = nullptr;
}