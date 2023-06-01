#include "chasePlayerOBJ.h"
#include "chasePlayerSCR.h"
#include "chTransform.h"
namespace ch 
{
	chasePlayerOBJ::chasePlayerOBJ()
	{
		this->AddComponent<chasePlayerSCR>();
		thisTr = GetComponent<Transform>();

	
		
	}

	chasePlayerOBJ::~chasePlayerOBJ()
	{
	}

	void chasePlayerOBJ::Initalize()
	{
		

		GameObject::Initalize();
	}

	void chasePlayerOBJ::Update()
	{
		thisTr->SetPosition(OwnerTr->GetPosition()); // �÷��̾� �i�� �ݶ��̴� ��ġ�� �׻� �ش� ���� ����
		

		GameObject::Update();
	}

	void chasePlayerOBJ::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void chasePlayerOBJ::Render()
	{
		GameObject::Render();
	}

}