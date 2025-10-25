#pragma once
#include <entt/entt.hpp>
#include "Component.hpp"

namespace Unk
{
	class Entity
	{
	public:
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
			mRegistry->remove<T>(mEntity);
		}

		template <typename T> void AddScript()
		{
			AddComponent<Script*>() = new T;
			GetComponent<Script*>()->mEntity = mEntity;
			GetComponent<Script*>()->mRegistry = mRegistry;
		}

		entt::entity GetEntt();
		void SetEntt(entt::entity entity);

		entt::registry* GetRegistry();
		void SetRegistry(entt::registry& registry);

		Entity(entt::registry& registry, entt::entity entt)
		{
			mRegistry = &registry;
			mEntity = entt;
		}
		Entity()
		{
		}

	private:
		entt::entity mEntity;
		entt::registry* mRegistry;
	};
}
