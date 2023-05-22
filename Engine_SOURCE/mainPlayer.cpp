#include "mainPlayer.h"
#include "chGameObject.h"
#include "chMouseCursorScript.h"
#include "chPlayerScr.h"
#include "chResources.h"
#include "chAnimator.h"
#include "chSpriteRenderer.h"
#include "chInput.h"
#include "chRigidbody.h"
#include "chPlayerHand.h"

namespace ch
{

	mainPlayer::mainPlayer()
	{
		SetLayerType(eLayerType::Player);
		

		GameObject* playerOBJ = dynamic_cast<GameObject*>(this);

		{///�ִϸ�����
			pAnimator = playerOBJ->AddComponent<Animator>();

		#pragma region NoWeapon
			#pragma region IDLE
			{
				{//����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"IdleFront", L"enterthe/character/idle/idleFront.png");
					pAnimator->Create(L"P_IdleFront", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
				}
				{//����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"IdleRight", L"enterthe/character/idle/idleRight.png");
					pAnimator->Create(L"P_IdleRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
				}
				{//����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"IdleLeft", L"enterthe/character/idle/idleLeft.png");
					pAnimator->Create(L"P_IdleLeft", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
				}
				{//��
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"IdleBack", L"enterthe/character/idle/idleBack.png");
					pAnimator->Create(L"P_IdleBack", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
				}
				{//�ڿ���
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"IdleBackRight", L"enterthe/character/idle/idleBackRight.png");
					pAnimator->Create(L"P_IdleBackRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
				}
				{//������
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"IdleBackLeft", L"enterthe/character/idle/idleBackLeft.png");
					pAnimator->Create(L"P_IdleBackLeft", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
				}		
			}
#pragma endregion
			#pragma region WALKING
			{//walking
				{//����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WalkingFront", L"enterthe/character/walking/walkingFront.png");
					pAnimator->Create(L"P_WalkingFront", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 6, 0.1f);
				}
				{//����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WalkingRight", L"enterthe/character/walking/walkingRight.png");
					pAnimator->Create(L"P_WalkingRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 6, 0.1f);
				}
				{//����
					/*std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WalkingLeft", L"enterthe/character/walking/walkingLeft.png");
					pAnimator->Create(L"P_WalkingLeft", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 6, 0.1f);*/
				}
				{//��
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WalkingBack", L"enterthe/character/walking/walkingBack.png");
					pAnimator->Create(L"P_WalkingBack", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 6, 0.1f);
				}
				{//�ڿ���
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WalkingBackRight", L"enterthe/character/walking/walkingBackRight.png");
					pAnimator->Create(L"P_WalkingBackRight", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 6, 0.1f);
				}
				{//������
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WalkingBackLeft", L"enterthe/character/walking/walkingBackLeft.png");
					pAnimator->Create(L"P_WalkingBackLeft", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 6, 0.1f);
				}
			}
#pragma endregion
			#pragma region DODGE
			{//dodge
				{ // ����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeFront", L"enterthe/character/dodge/dodgeFront.png");
					pAnimator->Create(L"P_DodgeFront", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 24.0f), Vector2::Zero, 9, 0.11f);
				}
				{//����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeRight", L"enterthe/character/dodge/dodgeRight.png");
					pAnimator->Create(L"P_DodgeRight", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 9, 0.11f);
				}
				{ // ����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeLeft", L"enterthe/character/dodge/dodgeLeft.png");
					pAnimator->Create(L"P_DodgeLeft", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 9, 0.11f);
				}
				
				{ //��
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeBack", L"enterthe/character/dodge/dodgeBack.png");
					pAnimator->Create(L"P_DodgeBack", texture, Vector2(0.0f, 0.0f), Vector2(15.0f, 24.0f), Vector2::Zero, 9, 0.11f);
				}
			
				{//�� ����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeBackRight", L"enterthe/character/dodge/dodgeBackRight.png");
					pAnimator->Create(L"P_DodgeBackRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 9, 0.11f);
				}

				{ // �� ����
					std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeBackLeft", L"enterthe/character/dodge/dodgeBackLeft.png");
					pAnimator->Create(L"P_DodgeBackLeft", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 9, 0.11f);
				}
			}
#pragma endregion
		#pragma endregion

		#pragma region Weapon
			//P_ �÷��̾�  W : Weapon
		#pragma region Idle
			
			{//����
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleFront", L"enterthe/character/weap/Idle/WIdleFront.png");
				pAnimator->Create(L"P_WIdleFront", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
			}
			{//����
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleRight", L"enterthe/character/weap/Idle/WIdleRight.png");
				pAnimator->Create(L"P_WIdleRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
				//�̹��� ���� �����ʿ�
			}
			{//��
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleBack", L"enterthe/character/weap/Idle/WIdleBack.png");
				pAnimator->Create(L"P_WIdleBack", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
			}
			{//�� ����
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleBackRight", L"enterthe/character/weap/Idle/WIdleBackRight.png");
				pAnimator->Create(L"P_WIdleBackRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
			}
			

		#pragma endregion

		#pragma region Walking
			{//����
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingFront", L"enterthe/character/weap/Walking/WWalkingFront.png");
				pAnimator->Create(L"P_WWalkingFront", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 4, 0.1f);
			}
			{//����
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingRight", L"enterthe/character/weap/Walking/WWalkingRight.png");
				pAnimator->Create(L"P_WWalkingRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 4, 0.1f);
			}
			{//��
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingBack", L"enterthe/character/weap/Walking/WWalkingBack.png");
				pAnimator->Create(L"P_WWalkingBack", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 4, 0.1f);
			}
			{//�� ����
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingBackRight", L"enterthe/character/weap/Walking/WWalkingBackRight.png");
				pAnimator->Create(L"P_WWalkingBackRight", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 4, 0.1f);
			}

		#pragma endregion


#pragma endregion
			pAnimator->Play(L"P_WIdleFront", true);

		}

		SpriteRenderer* sprite = playerOBJ->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
		
		pTr = playerOBJ->GetComponent<Transform>();
		pTr->SetScale(Vector3(5.3f, 5.6f, 0.0f));
		pTr->SetPosition(Vector3(2.f, 1.f, 0.f));

		pCollider = playerOBJ->AddComponent<Collider2D>();
		pCollider->SetName(L"playerCollider");
		pCollider->SetType(eColliderType::Rect);
		pCollider->SetSize(Vector2(.075f, .1f));
		

		playerOBJ->AddComponent<Rigidbody>();
		playerOBJ->AddComponent<PlayerScr>();
	}

	mainPlayer::~mainPlayer()
	{


	}

	void mainPlayer::Initalize()
	{
		


		GameObject::Initalize();
	
	}

	void mainPlayer::Update()
	{
		
		
		GameObject::Update();
	}

	void mainPlayer::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void mainPlayer::Render()
	{
		GameObject::Render();
	}



}