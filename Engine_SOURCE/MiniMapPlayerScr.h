#pragma once
#include "chScript.h"

namespace ch
{
	class MiniMapPlayerScr : public Script
	{
	public:
		MiniMapPlayerScr();
		virtual ~MiniMapPlayerScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;



	};
}


//�̴ϸ� ���� 900/ 350		 9 / 3.5   scale��ŭ �����ָ� �ɵ�
// 
// 
// ���� 1899/2377�ȼ�    189.9 / 237.7  * 50 / 62.91f   ���� ���̴� ũ�� =   9495  / 14953.707
// �÷��� ������ �ΰ��� �� ������ mapTr->SetScale(Vector3(50.0f, 62.91f, 0.1f));
// ī�޶� ���� ������  1/100�� ���� 