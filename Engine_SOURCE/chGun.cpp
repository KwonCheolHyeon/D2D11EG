#include "chGun.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chInput.h"
#include "chPistol.h"
#include "chBullet.h"
#include "chBulletScr.h"
#include "chtestBulletscr.h"
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
		gunTransform = gunObject->GetComponent<Transform>();
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
		angleFind();

		
		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			//Shot();

			Bullet* bull = new Bullet();
			bull->AddComponent<testBulletscr>();
			bull->GetComponent<testBulletscr>()->Initalize();

			Transform* bulletTrans = bull->GetComponent<Transform>();
			bull->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.3f, 0.2f));
			bulletTrans->SetPosition(playerHand->GetComponent<Transform>()->GetPosition());
			bull->GetComponent<testBulletscr>()->shootingBullet(angle, playerHand->GetComponent<Transform>()->GetPosition());

		}
		if (!bullets.empty())
		{
			if (bullets.back() != nullptr && bullets.back()->GetComponent<BulletScr>()->isReset())
			{
				ReturnBullet();
			}
		}
		
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
		bulletOBJ = bulletpool->GetBullet();
		if (bulletOBJ != nullptr) // Check if bulletOBJ is not nullptr before using it
		{
			bullets.push_back(bulletOBJ);
			bullets.back()->GetComponent<BulletScr>()->shootingBullet(angle, playerHand->GetComponent<Transform>()->GetPosition());
		}
	}

	void Gun::ReturnBullet()
	{

		if (!bullets.empty() && bullets.back() != nullptr)
		{
			bulletpool->ReturnBullet(bullets.back());
			bullets.pop_back();
		}
	}
	
	void Gun::SwapGun()
	{

	}
	void Gun::angleFind()
	{
		Vector3 handPosition = playerHand->GetComponent<Transform>()->GetPosition();
		Vector3 mousePos = Input::GetMousPosition();
		
		Vector3 characterPos = playerHand->GetComponent<Transform>()->GetPosition();

		Vector3 mouseRelative = (mousePos / 100.f);
		mouseRelative += characterPos;

		// Calculate the angle between the mouse cursor position and the character position
		float angle2 = atan2(mouseRelative.y - characterPos.y, mouseRelative.x - characterPos.x);

		float rotationZ = angle2 * (180.0f / XM_PI);

		angle = rotationZ;
	}
	void Gun::GunLookCursor()
	{

		if (playerHand->IsHandLeft()) //�޼�
		{
			gunObject->SetLeft();
			//gunPosition = handPosition + Vector3(-0.2f, 0.1f, 0.f);
			gunObject->SetRotation(Vector3(0.0f, 0.0f, 0.f));
		}
		else //������
		{
			gunObject->SetRight();
			
			
			gunObject->SetRotation(Vector3(180.0f, 0.0f, 0.f));
		}
		//gunTransform->SetPosition(gunPosition);
	}
}