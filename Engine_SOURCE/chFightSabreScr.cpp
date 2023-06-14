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

		SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_FightSabre_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

#pragma region �ִϸ�����
		anima = GetOwner()->GetComponent<Animator>();

		{//�⺻
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_Idle", L"enterthe/Waepone/FightSabre/idle/idle.png");
			anima->Create(L"W_FightSabre_Idle", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 14.0f), Vector2::Zero, 2, 0.5f);
		}
		{//�ѽ��
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_shot", L"enterthe/Waepone/FightSabre/shot/shot.png");
			anima->Create(L"W_FightSabre_shot", texture, Vector2(0.0f, 0.0f), Vector2(36.0f, 14.0f), Vector2::Zero, 2, 0.3f);
		}
		{//����
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_reload", L"enterthe/Waepone/FightSabre/reload.png");
			anima->Create(L"W_FightSabre_reload", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 41.0f), Vector2::Zero, 14, 0.2f);
		}
		{//������
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_Item", L"enterthe/Waepone/FightSabre/Item.png");
			anima->Create(L"W_FightSabre_Item", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 14.0f), Vector2::Zero, 1, 0.1f);
		}
		 
#pragma endregion

		
		fss = FightSabreState::SabreItemBox;
		prevFss = FightSabreState::SabrenonActive;
		touchGun = false;
		prevTouchGun = true;
	}

	void FightSabreScr::Update()
	{

		switch (fss)
		{
		case FightSabreState::SabreItemBox:
			ItemBox();
			break;
		case FightSabreState::SabreActive:
			Idle();
			break;
		case FightSabreState::SabrenonActive:
			nonActiveGun();
			break;
		case FightSabreState::SabreReload:
			Reload();
			break;
		case FightSabreState::SabreShot:
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

	void FightSabreScr::ItemBox()//������ �ڽ��� Ƣ��ͼ� �÷��̾ �ݱ���
	{
		
		
	}

	void FightSabreScr::Idle() // �⺻ ��� ������ 
	{
		anima->Play(L"W_FightSabre_Idle");
	}

	void FightSabreScr::nonActiveGun() // �ǽ���� ����������
	{
	}

	void FightSabreScr::Reload() // ����
	{
	}

	void FightSabreScr::Shot() //��
	{
	}

	

}