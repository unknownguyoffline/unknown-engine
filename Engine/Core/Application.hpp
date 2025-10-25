#pragma once
#include <memory>
#include <Core/Window.hpp>
#include <Renderer/Renderer.hpp>
#include <LayerStack.hpp>
#include <Utility/Memory.hpp>
#include <Utility/Timer.hpp>

namespace Unknown
{
	struct ApplicationProperty
	{
		WindowProperty windowProperty{};
		RendererProperty rendererProperty{};
	};


	class Application
	{
	public:
		static Application* GetInstance() { return mInstance; }

		void Close();

		Timer GetTimer();
		Timer& GetTimerRef();
		WindowInput GetInput() { return mWindow->GetInput(); }
		ApplicationProperty GetProperty() const { return mProperty; }
		void SetProperty(const ApplicationProperty& properties) { mProperty = properties; }

		Ref<Window> GetWindow() const { return mWindow; }
		Ref<Renderer> GetRenderer() const { return mRenderer; }
		Ref<LayerStack> GetLayerStack() const { return mLayerStack; }



		Application();
		~Application();

		void Run();


	protected:
		virtual void OnInitialize() {}
		virtual void OnStart() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnEnd() {}

	private:
		ApplicationProperty mProperty;
		static Application* mInstance;
		bool mRunning = true;
		Ref<Window> mWindow;
		Ref<Renderer> mRenderer;
		Ref<LayerStack> mLayerStack;
		Timer mTimer;

	private:
		void Initialize();

		void MainLoop();
		void Terminate();
		void ProcessEvent();
	};
}