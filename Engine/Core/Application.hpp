#pragma once
#include <memory>
#include <Core/Window.hpp>
#include <LayerStack.hpp>
#include <Utility/Memory.hpp>
#include <Utility/Timer.hpp>
#include <Renderer/Renderer2D.hpp>

namespace Unknown
{
	struct ApplicationProperty
	{
		WindowProperty windowProperty{};
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

		Ref<Window> GetWindow() { return mWindow; }
		Ref<Renderer2D> GetRenderer2D() { return mRenderer2D; }
		Ref<LayerStack> GetLayerStack() { return mLayerStack; }



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
		Ref<Renderer2D> mRenderer2D;
		Ref<LayerStack> mLayerStack;
		Timer mTimer;

	private:
		void Initialize();

		void MainLoop();
		void Terminate();
		void ProcessEvent();
		void InitializeSystems();
	};
}