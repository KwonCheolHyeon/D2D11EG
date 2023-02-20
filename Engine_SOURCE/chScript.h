#pragma once
#include "chComponent.h"

namespace ch
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		//std::vector<Script*> mScripts;
		//state jump;
		//state Attack;
	};
}
