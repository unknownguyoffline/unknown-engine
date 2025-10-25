#pragma once

namespace Unk
{
	class Layer
	{
	public:
		virtual void OnStart() {}
		virtual void OnUpdate() {}
		virtual void OnEnd() {}

		bool isEnabled();

		void enable();
		void disable();

	private:
		bool mEnabled = true;
	};
}
