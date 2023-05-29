#include "chasePlayerOBJ.h"
#include "chasePlayerSCR.h"
#include "chTransform.h"
namespace ch 
{
	chasePlayerOBJ::chasePlayerOBJ()
		:OwnerObject(nullptr)
	{
		this->AddComponent<chasePlayerSCR>();

		
		thisTr = GetComponent<Transform>();

		mCollider = this->AddComponent<Collider2D>(); //���� �ɸ�
		mCollider->SetName(L"MonsterChaseCollider");
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(2.f, 2.f));
	}

	chasePlayerOBJ::~chasePlayerOBJ()
	{
	}

	void chasePlayerOBJ::Initalize()
	{
		OwnerTr = OwnerObject->GetComponent<Transform>();

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