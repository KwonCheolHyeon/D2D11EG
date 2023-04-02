#pragma once
#include "chScript.h"

namespace ch
{
	class PlayerHandScr
		:public Script
	{
	public:
		PlayerHandScr();
		virtual ~PlayerHandScr();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void handPosition();
	private:
		float handDistance;
		

	};
}
