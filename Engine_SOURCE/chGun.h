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
		int bulletCount; // �Ѿȿ� �ִ� �߻� ����
		int magazineCount;//�� ź�� ����
		

	};

}
