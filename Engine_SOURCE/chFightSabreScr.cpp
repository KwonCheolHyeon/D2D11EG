#include "chFightSabreScr.h"
#include "chScene.h"
#include "chSceneManager.h"
#include "chPlayScene.h"
#include "chObject.h"
#include "chSpriteRenderer.h"
#include "chAnimation.h"
#include "chResources.h"
#include "chInput.h"
#include "FightSabreBullet.h"
#include "FightSabreBulletScr.h"
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
		gunObj = dynamic_cast<Gun*>(GetOwner());


		gunTransform = gunObj->GetComponent<Transform>();
		
		gunTransform->SetParent(playerHand->GetComponent<Transform>());
		gunTransform->SetInheritParentScale(false);

		Vector3 gunPosition = gunTransform->GetPosition();
		Vector3 handPosition = playerHand->GetComponent<Transform>()->GetPosition();
		gunTransform->SetPosition(gunPosition);

		SpriteRenderer* sprite = gunObj->GetComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_FightSabre_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

#pragma region �ִϸ�����
		anima = gunObj->GetComponent<Animator>();

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
		{//����
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"FightSabre_empty", L"empty.png");
			anima->Create(L"W_FightSabre_empty", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 14.0f), Vector2::Zero, 1, 0.1f);
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
			Active();
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

	void FightSabreScr::Active() // �⺻ ��� ������ 
	{
		if (prevFss != fss) 
		{
			gunTransform->SetScale(Vector3(6.f, 5.f, 1.0f));
			prevFss = fss;
			anima->Play(L"W_FightSabre_Idle", true);
		}
		angleFind();
		GunLookCursor();

		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			fss = FightSabreState::SabreShot;
		}

	}

	void FightSabreScr::nonActiveGun() // �ǽ���� ����������
	{
		prevFss = fss;
		

	}
	
	void FightSabreScr::Reload() // ����
	{


	}

	void FightSabreScr::Shot() //��
	{
		prevFss = fss;
		
		anima->Play(L"W_FightSabre_shot", false);

		FightSabreBullet* bullet = object::Instantiate<FightSabreBullet>(eLayerType::Weapone);
		FightSabreBulletScr* scr = bullet->AddComponent<FightSabreBulletScr>();
		scr->Initalize();
		scr->shootingBullet(angle, playerHand->GetComponent<Transform>()->GetPosition());

		fss = FightSabreState::SabreActive;
	}

	void FightSabreScr::angleFind()
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

	void FightSabreScr::GunLookCursor()
	{

		if (playerHand->IsHandLeft()) //�޼�
		{
			gunTransform->SetScale(Vector3(4.28f, 4.23f, 1.0f));
			gunObj->SetLeft();
			gunObj->SetRotation(Vector3(0.0f, 0.f, 0.f));
			gunObj->GetComponent<Transform>()->SetOffset(Vector3(-0.85f, -0.9f, 0.f));
		}
		else //������
		{
			gunTransform->SetScale(Vector3(4.28f, 4.23f, 1.0f));
			gunObj->SetLeft();
			gunObj->SetRotation(Vector3(180.0f, 0.0f, 0.f));
			gunObj->GetComponent<Transform>()->SetOffset(Vector3(-0.85f, -1.1f, 0.f));
		}
	}

	

}