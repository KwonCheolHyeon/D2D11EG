#pragma once
#include "chGameObject.h"

namespace ch
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void FixedUpdate() override;

	private:
	};
}
