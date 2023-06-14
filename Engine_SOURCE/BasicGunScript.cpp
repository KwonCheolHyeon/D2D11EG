#include "BasicGunScript.h"
#include "chInput.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chTime.h"
#include "chBulletScr.h"
namespace ch 
{
	BasicGunScript::BasicGunScript()
	{
	}
	BasicGunScript::~BasicGunScript()
	{
	}
	void BasicGunScript::Initalize()
	{
		gunObj = dynamic_cast<Gun*>(GetOwner());
		gunTransform = gunObj->GetComponent<Transform>();
		gunTransform->SetScale(Vector3(3.28f, 3.23f, 1.0f));
		gunTransform->SetParent(playerHand->GetComponent<Transform>());

		Vector3 gunPosition = gunTransform->GetPosition();
		Vector3 handPosition = playerHand->GetComponent<Transform>()->GetPosition();
		gunTransform->SetPosition(gunPosition);

		SpriteRenderer* sprite = gunObj->GetComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_pistol_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);



		ps = PistolState::PistolActive;
		reboundTrue = false;
	}
	void BasicGunScript::Update()
	{
		switch (ps)
		{
		case PistolState::PistolActive:
			Active();
			break;
		case PistolState::PistolnonActive:
			Disable();
			break;
		case PistolState::PistolReload:
			Reload();
			break;
		case PistolState::PistolShot:
			Shot();
			break;
		default:
			break;
		}
	}
	void BasicGunScript::FixedUpdate()
	{

	}
	void BasicGunScript::Render()
	{

	}
	void BasicGunScript::Active()
	{

		SpriteRenderer* sprite = gunObj->GetComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_pistol_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		shotTimer += Time::DeltaTime();
		//gunTransform->SetParent(playerHand->GetComponent<Transform>());
		genericAnimator.Update(Time::DeltaTime());
		GunLookCursor();
		angleFind();

		if (shotTimer >= 0.5f) // Adjust the time delay (0.5f) to your desired value
		{
			if (Input::GetKeyDown(eKeyCode::LBTN))
			{
				Shot();// ps = PistolState::Shot;
				HandDownAnimate(Vector3(0.f, 0.1f, 0.f));

				Vector3 a = Input::GetWorldMousPosition();
				a.x;
				a.y;
				a.z;

				int c = 0;
			}
		}
		if (!bullets.empty())
		{
			if (bullets.back() != nullptr && bullets.back()->GetComponent<BulletScr>()->isReset())
			{
				ReturnBullet();
			}
		}
	}
	void BasicGunScript::Disable()
	{

		SpriteRenderer* sprite = gunObj->GetComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

	}
	void BasicGunScript::Shot()
	{
		bulletOBJ = bulletpool->GetBullet();
		if (bulletOBJ != nullptr)
		{
			bullets.push_back(bulletOBJ);
			bullets.back()->GetComponent<BulletScr>()->shootingBullet(angle, playerHand->GetComponent<Transform>()->GetPosition());

			// Reset shot timer
			shotTimer = 0.0f;
		}
	}
	void BasicGunScript::Reload()
	{


	}

	void BasicGunScript::ReturnBullet()
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


	void BasicGunScript::angleFind()
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

	void BasicGunScript::GunLookCursor()
	{
		if (playerHand->IsHandLeft()) //왼손
		{
			gunObj->SetLeft();
			gunObj->SetRotation(Vector3(0.0f, 0.0f, 0.f));
			gunObj->GetComponent<Transform>()->SetOffset(Vector3(0.0f, 0.0f, 0.f));
		}
		else //오른손
		{
			gunObj->SetRight();
			gunObj->SetRotation(Vector3(180.0f, 0.0f, 0.f));
			gunObj->GetComponent<Transform>()->SetOffset(Vector3(0.2f, -1.5f, 0.f));
		}
	}
	void BasicGunScript::HandDownAnimate(Vector3 handPos)
	{
		if (genericAnimator.IsRunning())
			genericAnimator.Stop();

		reboundTrue = true;
		rebound = handPos;
		// Set animation parameters
		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 0.f;
		param.EndValue = 0.2f;
		param.DurationTime = 0.1f;
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
	void BasicGunScript::HandUpAnimate(Vector3 handPos)
	{
		if (genericAnimator.IsRunning())
			genericAnimator.Stop();


		rebound = handPos;
		// Set animation parameters
		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 0.f;
		param.EndValue = 0.2f;
		param.DurationTime = 0.1f;
		param.DurationFunc = [this](float InCurValue) {
			HandUpPos(InCurValue);
		};
		param.CompleteFunc = [this](float InCurValue) {

			reboundTrue = false;
		};

		genericAnimator.Start(param);
	}
	void BasicGunScript::HandDownPos(float cur)
	{
		Vector3 Hand = playerHand->GetComponent<Transform>()->GetPosition();
		Vector3 pPos = playerHand->GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector3 diff = pPos - Hand;
		Hand -= (rebound * cur * Time::DeltaTime()) + diff;
		playerHand->GetComponent<Transform>()->SetPosition(Hand);
	}
	void BasicGunScript::HandUpPos(float cur)
	{
		Vector3 Hand = playerHand->GetComponent<Transform>()->GetPosition();
		Vector3 pPos = playerHand->GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector3 diff = pPos - Hand;
		Hand += (rebound * cur * Time::DeltaTime()) + diff;
		playerHand->GetComponent<Transform>()->SetPosition(Hand);
	}
}