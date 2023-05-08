#include "Convict.h"
#include "CharacterBase.h"
#include "ConvictMove.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chInput.h"
namespace ch
{
	Convict::Convict()
	{
			
	}

	Convict::~Convict()
	{
	}

	void Convict::Initalize()
	{
		pTr = GetOwner()->GetComponent<Transform>();
		pAnimator = GetOwner()->GetComponent<Animator>();
		pCollider = GetOwner()->GetComponent<Collider2D>();
		player = dynamic_cast<CharacterBase*>(this);

#pragma region Animator
		#pragma region 한손무기
		#pragma region 기본 상태
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleFront", L"enterthe/character/weap/Idle/WIdleFront.png");
			pAnimator->Create(L"P_O_Idle_Front", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		{//우측
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleRight", L"enterthe/character/weap/Idle/WIdleRight.png");
			pAnimator->Create(L"P_O_Idle_Right", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
			//이미지 편집 변경필요
		}
		{//뒤
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleBack", L"enterthe/character/weap/Idle/WIdleBack.png");
			pAnimator->Create(L"P_O_Idle_Back", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		{//뒤 우측
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WIdleBackRight", L"enterthe/character/weap/Idle/WIdleBackRight.png");
			pAnimator->Create(L"P_O_Idle_BackRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
	#pragma endregion
		#pragma region 걷기
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingFront", L"enterthe/character/weap/Walking/WWalkingFront.png");
			pAnimator->Create(L"P_O_WalkingFront", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 4, 0.1f);
		}
		{//우측
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingRight", L"enterthe/character/weap/Walking/WWalkingRight.png");
			pAnimator->Create(L"P_O_WalkingRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 4, 0.1f);
		}
		{//뒤
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingBack", L"enterthe/character/weap/Walking/WWalkingBack.png");
			pAnimator->Create(L"P_O_WalkingBack", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 4, 0.1f);
		}
		{//뒤 우측
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"WWalkingBackRight", L"enterthe/character/weap/Walking/WWalkingBackRight.png");
			pAnimator->Create(L"P_O_WalkingBackRight", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 4, 0.1f);
		}
	#pragma endregion
		#pragma region 구르기
		{//dodge
			{ // 정면
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeFront", L"enterthe/character/dodge/dodgeFront.png");
				pAnimator->Create(L"P_DodgeFront", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 24.0f), Vector2::Zero, 9, 0.11f);
			}
			{//우측
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeRight", L"enterthe/character/dodge/dodgeRight.png");
				pAnimator->Create(L"P_DodgeRight", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 9, 0.11f);
			}
			{ // 좌측
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeLeft", L"enterthe/character/dodge/dodgeLeft.png");
				pAnimator->Create(L"P_DodgeLeft", texture, Vector2(0.0f, 0.0f), Vector2(20.0f, 23.0f), Vector2::Zero, 9, 0.11f);
			}

			{ //뒤
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeBack", L"enterthe/character/dodge/dodgeBack.png");
				pAnimator->Create(L"P_DodgeBack", texture, Vector2(0.0f, 0.0f), Vector2(15.0f, 24.0f), Vector2::Zero, 9, 0.11f);
			}

			{//뒤 우측
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeBackRight", L"enterthe/character/dodge/dodgeBackRight.png");
				pAnimator->Create(L"P_DodgeBackRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 9, 0.11f);
			}

			{ // 뒤 좌측
				std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"DodgeBackLeft", L"enterthe/character/dodge/dodgeBackLeft.png");
				pAnimator->Create(L"P_DodgeBackLeft", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 9, 0.11f);
			}
		}

	#pragma endregion
		#pragma endregion
		#pragma region 두손무기

		#pragma region 기본 상태
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_IdleFront", L"enterthe/characterTwoHand/Idle/twohand_Idle_Front.png");
			pAnimator->Create(L"PT_IdleFront", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}

		{//오른쪽
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_IdleRight", L"enterthe/characterTwoHand/Idle/twohand_Idle_Right.png");
			pAnimator->Create(L"PT_IdleRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}

		{//뒤
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_IdleBack", L"enterthe/characterTwoHand/Idle/twohand_Idle_Back.png");
			pAnimator->Create(L"PT_IdleBack", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		{//뒤 오른쪽
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_IdleBackRight", L"enterthe/characterTwoHand/Idle/twohand_Idle_BackRight.png");
			pAnimator->Create(L"PT_IdleBackRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 20.0f), Vector2::Zero, 4, 0.1f);
		}
		#pragma endregion

		#pragma region 걷기
		{//정면
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_WalkFront", L"enterthe/characterTwoHand/Walking/twohand_Walk_Front.png");
			pAnimator->Create(L"PT_WalkFront", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 6, 0.1f);
		}

		{//오른쪽
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_WalkRight", L"enterthe/characterTwoHand/Walking/twohand_Walk_Right.png");
			pAnimator->Create(L"PT_WalkRight", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 23.0f), Vector2::Zero, 6, 0.1f);
		}

		{//뒤
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_WalkBack", L"enterthe/characterTwoHand/Walking/twohand_Walk_Back.png");
			pAnimator->Create(L"PT_WalkBack", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 6, 0.1f);
		}
		{//뒤 오른쪽
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"P_T_WalkBackRight", L"enterthe/characterTwoHand/Walking/twohand_Walk_BackRight.png");
			pAnimator->Create(L"PT_WalkBackRight", texture, Vector2(0.0f, 0.0f), Vector2(17.0f, 23.0f), Vector2::Zero, 6, 0.1f);
		}
		#pragma endregion
	
	#pragma endregion
#pragma endregion

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		pCollider = GetOwner()->GetComponent<Collider2D>();


	}

	void Convict::Update()
	{
		
	}

	void Convict::FixedUpdate()
	{
	}

	void Convict::Render()
	{
	}

	#pragma region 충돌 관련
	void Convict::OnCollisionEnter(Collider2D* oppo)
	{
	}

	void Convict::OnCollision(Collider2D* oppo)
	{
	}

	void Convict::OnCollisionExit(Collider2D* oppo)
	{
	}

	void Convict::OnTriggerEnter(Collider2D* oppo)
	{
	}

	void Convict::OnTrigger(Collider2D* oppo)
	{
	}

	void Convict::OnTriggerExit(Collider2D* oppo)
	{
	}
#pragma endregion

	void Convict::MouseAndPlayerAngle()
	{
		Vector3 mousePos = Input::GetMousPosition();

		Vector3 mousePositon = (mousePos / 100.f);

		Vector3 CharterPosition = GetOwner()->GetComponent<Transform>()->GetPosition();
		mousePositon += CharterPosition;//마우스 위치가 화면에 고정되어 있으므로 캐릭터가 이동한 위치 만큼 더해줌
		float aaa = atan2(mousePositon.y - CharterPosition.y, mousePositon.x - CharterPosition.x);
		c2mAngle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360각
	}

	void Convict::playerLookingMouse()
	{
		
	}

	void Convict::SetAnimation()
	{
		
		int a = player->GetComponent<ConvictMove>()->GetPS(); // playerState
		int b = player->GetPD(); // playerDirection
		int c = player->GetComponent<ConvictMove>()->GetPDD();//구르기 방향
		if(a == 1) //기본상태
		{
			if (b == 1)
			{

			}
			else if (b == 2)
			{

			}
			else if (b == 3)
			{

			}
			else if (b == 4)
			{

			}
			else if (b == 5)
			{

			}
			else if (b == 6)
			{

			}
		}
		else if (a == 2) //걷기 상태
		{
			if (b == 1)
			{

			}
			else if (b == 2)
			{

			}
			else if (b == 3)
			{

			}
			else if (b == 4)
			{

			}
			else if (b == 5)
			{

			}
			else if (b == 6)
			{

			}
		}
		
		
	}

	

}