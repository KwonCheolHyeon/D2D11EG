#include "chGun.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chInput.h"
#include "chPistol.h"
namespace ch 
{
	Gun::Gun()
	{
		pistol.bulletCount = 6;
		pistol.damage = 3;
		pistol.magazineCount = 300;
		pistol.speed = 10;

		
		
	}
	Gun::Gun(int a)
	{
		if (a == 1) 
		{
			pistol.bulletCount = 6;
			pistol.damage = 3;
			pistol.magazineCount = 300;
			pistol.speed = 10;

			SpriteRenderer* sprite = gunObject->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_pistol_Material");
			sprite->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sprite->SetMesh(mesh);
			GameObject::Initalize();
		}
		else if (a == 2) 
		{
			
		}
	}
	Gun::~Gun()
	{
	}
	void Gun::Initalize()
	{
		gunObject = this;
		gunTransform = gunObject->AddComponent<Transform>();
		gunTransform->SetScale(Vector3(3.28f, 3.23f, 1.0f));
		gunTransform->SetParent(playerHand->GetComponent<Transform>());

		Vector3 gunPosition = gunTransform->GetPosition();
		Vector3 handPosition = playerHand->GetComponent<Transform>()->GetPosition();
		gunTransform->SetPosition(gunPosition);

		SpriteRenderer* sprite = gunObject->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_pistol_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		GameObject::Initalize();
	}
	void Gun::Update()
	{

		GunLookCursor();
		GameObject::Update();
	}
	void Gun::FixedUpdate()
	{


		GameObject::FixedUpdate();
	}
	void Gun::Render()
	{
		GameObject::Render();
	}
	void Gun::Reload()
	{
	}
	void Gun::Shot()
	{
	}
	void Gun::SwapGun()
	{

	}
	void Gun::GunLookCursor()
	{

		if (playerHand->IsHandLeft()) //¿Þ¼Õ
		{
			gunObject->SetLeft();
			//gunPosition = handPosition + Vector3(-0.2f, 0.1f, 0.f);
			gunObject->SetRotation(Vector3(0.0f, 0.0f, 0.f));
		}
		else //¿À¸¥¼Õ
		{
			gunObject->SetRight();
			
			
			gunObject->SetRotation(Vector3(180.0f, 0.0f, 0.f));
		}
		//gunTransform->SetPosition(gunPosition);
	}
}