#pragma once
#include <Scene/Scene.hpp>

namespace Unknown
{
	struct System
	{
		static void Initialize();
		static CameraProperty GetActiveCamera(Scene& scene);
		static void UpdateScripts(Scene& scene);
		static void StartScripts(Scene& scene);
		static void EndScripts(Scene& scene);
		static void RenderCircles(Scene& scene);


		static Mesh sQuad;
		static Material sCircleMaterial;
	};
}