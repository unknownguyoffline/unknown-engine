#include "Scene.hpp"

namespace Unknown
{
	Entity Scene::Create(const char* name)
	{
		entt::entity entt = mRegistry.create();
		Entity entity;
		entity.SetEntt(entt);
		entity.SetRegistry(mRegistry);
		EntityMetadataComponent metadata = { name };
		entity.AddComponent<EntityMetadataComponent>() = metadata;
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::Destroy(Entity& entity)
	{
		mRegistry.destroy(entity.GetEntt());
	}
}


// EntityView
