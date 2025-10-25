#pragma once
#include <string>
#include <Renderer/Types.hpp>
#include <Renderer/Mesh.hpp>
#include <Renderer/Material.hpp>
#include <Renderer/Camera.hpp>
#include <entt/entt.hpp>
#include <Application.hpp>

namespace Unk
{
	struct EntityMetadataComponent
	{
		std::string name;
	};

	struct TransformComponent
	{
		Transform transform;
	};

	struct RectangleComponent
	{
		glm::vec4 color;
	};

	struct CircleComponent
	{
		glm::vec4 color;
	};

	struct MeshRendererComponent
	{
		Mesh mesh;
		Material material;
	};

	struct CameraComponent
	{
		CameraType type = FirstPerson;
		CameraProjectionType projectionType = Perspective;
		float fov = 90.f;
		glm::vec2 size = { 800.f, 600.f };
		float nearPlane = 0.01f;
		float farPlane = 100.f;
		glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
		glm::vec3 position = glm::vec3(0, 0, -1);
		glm::vec3 lookAt = glm::vec3(0, 0, 1);
		bool selected = false;
	};

	struct Script
	{
		virtual void OnStart()
		{
		}
		virtual void OnUpdate()
		{
		}
		virtual void OnEnd()
		{
		}

		template <typename T> T& AddComponent()
		{
			return mRegistry->emplace<T>(mEntity);
		}

		template <typename T> T& GetComponent()
		{
			return mRegistry->get<T>(mEntity);
		}

		template <typename T> void RemoveComponent(T& t)
		{
			mRegistry->erase<T>(mEntity);
		}

		WindowInput GetInput()
		{
			return Application::GetInstance()->GetInput();
		}

		entt::entity mEntity;
		entt::registry* mRegistry;
	};
}
