#include "Entity.hpp"

namespace Unknown
{
	entt::entity Entity::GetEntt()
	{
		return mEntity;
	}

	void Entity::SetEntt(entt::entity entity)
	{
		mEntity = entity;
	}

	entt::registry* Entity::GetRegistry()
	{
		return mRegistry;
	}

	void Entity::SetRegistry(entt::registry& registry)
	{
		mRegistry = &registry;
	}
}
