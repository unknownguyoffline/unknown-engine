#include "System.hpp"
#include <Application.hpp>


namespace Unknown
{
	Mesh System::sQuad;
	Material System::sCircleMaterial;

	void System::Initialize()
	{
		sQuad = Mesh::QuadMesh();
		sCircleMaterial.shader = BASIC_CIRCLE_SHADER;
	}

	CameraProperty System::GetActiveCamera(Scene& scene)
	{
		EntityView<CameraComponent> cameraView = scene.GetView<CameraComponent>();

		for (int i = 0; i < cameraView.GetSize(); i++)
		{
			CameraComponent& component = cameraView.Get(i).GetComponent<CameraComponent>();

			if (component.selected)
			{
				CameraProperty property;
				property.type = component.type;
				property.projectionType = component.projectionType;
				property.fov = component.fov;
				property.size = component.size;
				property.nearPlane = component.nearPlane;
				property.farPlane = component.farPlane;
				property.up = component.up;
				property.position = component.position;
				property.lookAt = component.lookAt;
				return property;
			}
		}
		return CameraProperty();
	}


	void System::UpdateScripts(Scene& scene)
	{
		EntityView<Script*> scriptView = scene.GetView<Script*>();
		for (int i = 0; i < scriptView.GetSize(); i++)
		{
			scriptView.Get(i).GetComponent<Script*>()->OnUpdate();
		}
	}


	void System::StartScripts(Scene& scene)
	{
		EntityView<Script*> scriptView = scene.GetView<Script*>();
		for (int i = 0; i < scriptView.GetSize(); i++)
		{
			scriptView.Get(i).GetComponent<Script*>()->OnStart();
		}
	}

	void System::EndScripts(Scene& scene)
	{
		EntityView<Script*> scriptView = scene.GetView<Script*>();
		for (int i = 0; i < scriptView.GetSize(); i++)
		{
			scriptView.Get(i).GetComponent<Script*>()->OnEnd();
		}
	}

	void System::RenderCircles(Scene& scene)
	{
		Ref<Renderer> renderer = Application::GetInstance()->GetRenderer();
		EntityView<CircleComponent> view = scene.GetView<CircleComponent>();
		for (int i = 0; i < view.GetSize(); i++)
		{
			Entity entity = view[i];
			Transform transform = entity.GetComponent<TransformComponent>().transform;
			sCircleMaterial.color = entity.GetComponent<CircleComponent>().color;

			renderer->Submit(sQuad, sCircleMaterial, transform);
		}
	}
}
