#include "chFightSabreObject.h"
#include"chFightSabreScr.h"
#include "chRigidbody.h"
namespace ch 
{

	FightSabreObject::FightSabreObject()
	{
	}

	FightSabreObject::~FightSabreObject()
	{
	}

	void FightSabreObject::Initalize()
	{
		FightSabreScr* a = this->AddComponent<FightSabreScr>();
		a->Initalize();
		this->AddComponent<Rigidbody>();

		Rigidbody* ri = this->GetComponent<Rigidbody>();
		ri->SetVelocity(Vector3(2.f, -2.0f, 0.0f) * 900.f);

		Collider2D* col = this->AddComponent<Collider2D>();
		col->SetName(L"GunCol");
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(1.f, 1.f));

		GameObject::Initalize();
	}

	void FightSabreObject::Update()
	{
		GameObject::Update();
	}

	void FightSabreObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void FightSabreObject::Render()
	{
		GameObject::Render();
	}

}