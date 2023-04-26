#include "chFightSabreScr.h"
#include "chScene.h"
#include "chSceneManager.h"
#include "chPlayScene.h"
#include "chSpriteRenderer.h"
#include "chAnimation.h"
#include "chResources.h"
#include "chInput.h"
#include "chBullet.h"
#include "chBulletScr.h"
#include "chTime.h"
namespace ch 
{
	FightSabreScr::FightSabreScr()
	{
	}

	FightSabreScr::~FightSabreScr()
	{
	}

	void FightSabreScr::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::TwoHandWeapone);

		gunObject = GetOwner();
		gunTransform = gunObject->GetComponent<Transform>();
		gunTransform->SetScale(Vector3(1.28f, 1.23f, 1.0f));
		gunTransform->SetParent(gunBox->GetComponent<Transform>());

		Vector3 gunPosition = gunTransform->GetPosition();
		
		gunTransform->SetPosition(gunPosition);

		SpriteRenderer* sprite = gunObject->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_FightSabre_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

#pragma region 애니메이터
		gAnimator = gunObject->AddComponent<Animator>();

		{//기본
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_Idle", L"enterthe/Waepone/FightSabre/idle/idle.png");
			gAnimator->Create(L"W_FightSabre_Idle", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 14.0f), Vector2::Zero, 2, 0.5f);
		}
		{//총쏘기
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_shot", L"enterthe/Waepone/FightSabre/shot/shot.png");
			gAnimator->Create(L"W_FightSabre_shot", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 14.0f), Vector2::Zero, 2, 0.3f);
		}
		{//장전
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_reload", L"enterthe/Waepone/FightSabre/reload.png");
			gAnimator->Create(L"W_FightSabre_reload", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 41.0f), Vector2::Zero, 14, 0.2f);
		}
#pragma endregion

		pistolState.GunNum = 2;
		pistolState.active = true;
	}

	void FightSabreScr::Update()
	{
		if (pistolState.active == true)
		{
			gunTransform->SetParent(player->GetComponent<Transform>());
			gunTransform->SetOffset(Vector3(-1.f,-1.f,0.f));
			gunTransform->SetScale(Vector3(1.f, 1.2f, 0.f));
			if (Input::GetKeyDown(eKeyCode::F)) 
			{
				gAnimator->Play(L"W_FightSabre_Idle", true);
			}
			if (Input::GetKeyDown(eKeyCode::G))
			{
				gAnimator->Play(L"W_FightSabre_shot", true);
			}
			if (Input::GetKeyDown(eKeyCode::H))
			{
				gAnimator->Play(L"W_FightSabre_reload", false);
			}
		}
		else
		{
			notActiveState();
		}

	}

	void FightSabreScr::FixedUpdate()
	{
	}

	void FightSabreScr::Render()
	{
	}

	void FightSabreScr::Reload()
	{
	}

	void FightSabreScr::Shot()
	{
	}

	void FightSabreScr::ReturnBullet()
	{
	}

	void FightSabreScr::angleFind()
	{
	}

	void FightSabreScr::notActiveState()
	{
		gunTransform->SetParent(gunBox->GetComponent<Transform>());
	}

	void FightSabreScr::HandDownAnimate(Vector3 handPos)
	{
	}

	void FightSabreScr::HandUpAnimate(Vector3 handPos)
	{
	}

	void FightSabreScr::HandDownPos(float cur)
	{
	}

	void FightSabreScr::HandUpPos(float cur)
	{
	}

	void FightSabreScr::GunLookCursor()
	{
	}

}