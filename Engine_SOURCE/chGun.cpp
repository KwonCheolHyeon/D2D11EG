#include "chGun.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chInput.h"
#include "chPistol.h"
#include "chBullet.h"
#include "chBulletScr.h"
#include "chtestBulletscr.h"
#include "chTime.h"


namespace ch 
{
	bool Gun::reboundTrue = false;
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
		genericAnimator.Update(Time::DeltaTime());
		GunLookCursor();
		angleFind();

		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			Shot();
			HandDownAnimate(Vector3(0.f, 0.1f, 0.f));
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

		if (!bullets.empty()) // 먼저 bullets 벡터가 비어있는지 체크
		{
			if (bullets.back() != nullptr) // bullets.back()이 nullptr이 아닌지 체크
			{
				bulletpool->ReturnBullet(bullets.back());
				bullets.pop_back();
			}
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

	void Gun::HandDownAnimate(Vector3 handPos)
	{
		if (genericAnimator.IsRunning())
			genericAnimator.Stop();

		reboundTrue = true;
		rebound = handPos;
		// Set animation parameters
		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 0.f;
		param.EndValue = 0.3f;
		param.DurationTime = 0.2f;
		param.DurationFunc = [this](float InCurValue) {
			HandDownPos(InCurValue);
		};
		param.CompleteFunc = [this](float InCurValue) {
			// This function will be called when the animation is finished
		// This function will be called on every tick of the animation
			
			HandUpAnimate(rebound);

		};

		genericAnimator.Start(param);

	}

	void Gun::HandUpAnimate(Vector3 handPos)
	{
		if (genericAnimator.IsRunning())
			genericAnimator.Stop();

		
		rebound = handPos;
		// Set animation parameters
		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 0.f;
		param.EndValue = 0.3f;
		param.DurationTime = 0.2f;
		param.DurationFunc = [this](float InCurValue) {
			HandUpPos(InCurValue);
		};
		param.CompleteFunc = [this](float InCurValue) {
		
			reboundTrue = false;
		};

		genericAnimator.Start(param);

	}

	void Gun::HandDownPos(float cur)
	{
		Vector3 Hand = playerHand->GetComponent<Transform>()->GetPosition();
		Vector3 pPos = playerHand->GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector3 diff = pPos - Hand;
		Hand -= (rebound * cur * Time::DeltaTime()) + diff;
		playerHand->GetComponent<Transform>()->SetPosition(Hand);
	}

	void Gun::HandUpPos(float cur)
	{
		Vector3 Hand = playerHand->GetComponent<Transform>()->GetPosition();
		Vector3 pPos = playerHand->GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector3 diff = pPos - Hand;
		Hand += (rebound * cur * Time::DeltaTime()) + diff;
		playerHand->GetComponent<Transform>()->SetPosition(Hand);
	}

	

	void Gun::GunLookCursor()
	{

		if (playerHand->IsHandLeft()) //왼손
		{
			gunObject->SetLeft();
			//gunPosition = handPosition + Vector3(-0.2f, 0.1f, 0.f);
			gunObject->SetRotation(Vector3(0.0f, 0.0f, 0.f));
		}
		else //오른손
		{
			gunObject->SetRight();
			gunObject->SetRotation(Vector3(180.0f, 0.0f, 0.f));
		}
		//gunTransform->SetPosition(gunPosition);
	}


	
	 
	


}