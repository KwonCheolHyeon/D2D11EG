#pragma once
#include "chGameObject.h"

namespace ch 
{
	class PlayerSprite : public GameObject
	{
	public:
		PlayerSprite();
		virtual ~PlayerSprite();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}


