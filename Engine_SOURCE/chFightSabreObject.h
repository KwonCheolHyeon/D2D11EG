#pragma once
#include "chGun.h"
namespace ch
{
	class FightSabreObject :public Gun
	{
	public:
		FightSabreObject();
		virtual ~FightSabreObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


	};
}
