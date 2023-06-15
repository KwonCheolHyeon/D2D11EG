#include "chFightSabreObject.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
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
		
		SpriteRenderer* sprite = this->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_FightSabre_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
	
		obRigid = this->AddComponent<Rigidbody>();
		obCollider = this->AddComponent<Collider2D>();
		obCollider->SetName(L"FightSabreCol");
		obCollider->SetType(eColliderType::Rect);
		obCollider->SetSize(Vector2(0.15f, 0.1f));

		obAnima = this->AddComponent<Animator>();
		{//아이템
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_Item", L"enterthe/Waepone/FightSabre/Item.png");
			obAnima->Create(L"W_FightSabre_Item", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 14.0f), Vector2::Zero, 1, 0.1f);
		}
		{//기본
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_Idle", L"enterthe/Waepone/FightSabre/idle/idle.png");
			obAnima->Create(L"W_FightSabre_Idle", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 14.0f), Vector2::Zero, 2, 0.5f);
		}
		obAnima->Play(L"W_FightSabre_Item");
		firstKey = false;
		equipItem = false;
		GameObject::Initalize();
	}

	void FightSabreObject::Update()
	{

		if (firstKey == false) 
		{
			firstKey = true;
			obRigid->SetVelocity(Vector3(0.f, -2.0f, 0.0f) * 3.f);
			obAnima->Play(L"W_FightSabre_Idle");
		}
		if (equipItem == true) 
		{
			SpriteRenderer* sprite = this->GetComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
			sprite->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sprite->SetMesh(mesh);

			obCollider->SetSize(Vector2(0.f, 0.f));
		}
		
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