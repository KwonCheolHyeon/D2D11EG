#include "Bullet_Kin_Gun.h"
#include "Bullet_Kin_Gun_Scr.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
namespace ch 
{

	Bullet_Kin_Gun::Bullet_Kin_Gun()
	{

	}

	Bullet_Kin_Gun::~Bullet_Kin_Gun()
	{
	}

	void Bullet_Kin_Gun::Initalize()
	{
		this->AddComponent<Bullet_Kin_Gun_Scr>();


		SpriteRenderer* sprite = this->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
		
		monsterGunAni = this->AddComponent<Animator>();
		{//¿œπ› 
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WGun_Idle", L"enterthe/enemy/bullet_Kin/gun_Idle.png");
			monsterGunAni->Create(L"WGun_Idle", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 16.0f), Vector2::Zero, 1, 0.1f);
		}
		{//√— ΩÚ∂ß
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WGun_Shot", L"enterthe/enemy/bullet_Kin/gun_shot.png");
			monsterGunAni->Create(L"WGun_Shot", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 16.0f), Vector2::Zero, 5, 0.1f);
		}

		
		GameObject::Initalize();
	}

	void Bullet_Kin_Gun::Update()
	{
		GameObject::Update();
	}

	void Bullet_Kin_Gun::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Bullet_Kin_Gun::Render()
	{
		GameObject::Render();
	}

}