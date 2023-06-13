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

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_FightSabre_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

#pragma region 애니메이터
		anima = GetOwner()->AddComponent<Animator>();

		{//기본
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_Idle", L"enterthe/Waepone/FightSabre/idle/idle.png");
			anima->Create(L"W_FightSabre_Idle", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 14.0f), Vector2::Zero, 2, 0.5f);
		}
		{//총쏘기
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_shot", L"enterthe/Waepone/FightSabre/shot/shot.png");
			anima->Create(L"W_FightSabre_shot", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 14.0f), Vector2::Zero, 2, 0.3f);
		}
		{//장전
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_reload", L"enterthe/Waepone/FightSabre/reload.png");
			anima->Create(L"W_FightSabre_reload", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 41.0f), Vector2::Zero, 14, 0.2f);
		}
		{//아이템
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_Item", L"enterthe/Waepone/FightSabre/Item.png");
			anima->Create(L"W_FightSabre_Item", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 14.0f), Vector2::Zero, 1, 0.1f);
		}
		 
#pragma endregion

		
		fss = FightSabreState::ItemBox;
		prevFss = FightSabreState::nonActive;
		touchGun = false;
		prevTouchGun = true;
	}

	void FightSabreScr::Update()
	{

		switch (fss)
		{
		case FightSabreState::ItemBox:
			ItemBox();
			break;
		case FightSabreState::Active:
			Idle();
			break;
		case FightSabreState::nonActive:
			nonActiveGun();
			break;
		case FightSabreState::Reload:
			Reload();
			break;
		case FightSabreState::Shot:
			Shot();
			break;
		default:
			break;
		}
	

	}

	void FightSabreScr::FixedUpdate()
	{
	}

	void FightSabreScr::Render()
	{
	}

	void FightSabreScr::OnCollisionEnter(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player") 
		{
			touchGun = true;
		}
	}

	void FightSabreScr::OnCollision(Collider2D* oppo)
	{
	}

	void FightSabreScr::OnCollisionExit(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			touchGun = false;
		}
	}

	void FightSabreScr::ItemBox()//아이템 박스에 튀어나와서 플레이어가 줍기전
	{
		if (prevTouchGun != touchGun)
		{
			prevTouchGun = touchGun;
			if (touchGun == true) 
			{
			
				anima->Play(L"W_FightSabre_Idle");
			}
			else 
			{
				anima->Play(L"W_FightSabre_Item", false);
			}
		
		}
	
			
		
		
	}

	void FightSabreScr::Idle() // 기본 들고 있을때 
	{
		anima->Play(L"W_FightSabre_Idle");
	}

	void FightSabreScr::nonActiveGun() // 피스톨과 스왑했을때
	{
	}

	void FightSabreScr::Reload() // 장전
	{
	}

	void FightSabreScr::Shot() //쏠때
	{
	}

	

}