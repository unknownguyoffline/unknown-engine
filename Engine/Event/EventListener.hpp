#pragma once
#include <functional>

namespace Unk
{
	class EventListener
	{
	public:
		std::function<void(void* data)> callback;
	};
}