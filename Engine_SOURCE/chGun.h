#pragma once
#include "chGameObject.h"
namespace ch
{
	class Gun : public GameObject
	{
	public:
		Gun();
		virtual ~Gun();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void Reload();
		void Shot();
	private:
		int bulletCount; // ÃÑ¾È¿¡ ÃÖ´ë ¹ß»ç °¹¼ö
		int magazineCount;//ÃÑ Åº¾à °¹¼ö
		

	};

}
