#pragma once
#include "Entity.hpp"
#include "Component.hpp"
#include <entt/entt.hpp>

namespace Unk
{
	template<typename T>
	class EntityView
	{
	public:
		EntityView(entt::registry& registry)
		{
			mRegistry = &registry;
			mView = registry.view<T>();
		}
		Entity Get(uint32_t index)
		{
			auto it = mView.begin();
			auto t = it + index;
			entt::entity e = *t;


			return Entity(*mRegistry, e);
		}
		uint32_t GetSize()
		{
			return mView.size();
		}
		Entity operator[](uint32_t index)
		{
			return Get(index);
		}
	private:
		decltype(std::declval<entt::registry>().view<T>()) mView;
		entt::registry* mRegistry;
	};

	class Scene
	{
	public:
		Entity Create(const char* name);
		void Destroy(Entity& entity);
		template<typename T>
		EntityView<T> GetView()
		{
			return EntityView<T>(mRegistry);
		}

		entt::registry* GetRegistryPtr() { return &mRegistry; }
	private:
		entt::registry mRegistry;
	};
}

