#include "mainPlayerScript.h"
#include "chTransform.h"
#include "chTime.h"
#include "chAnimator.h"
#include "chInput.h"
#include "chGameObject.h"
#include "chRigidbody.h"

namespace ch
{
	mainPlayerScript::mainPlayerScript()
	{
		mState[(UINT)ePlayerState::Front] = true;
		mState[(UINT)ePlayerState::Back] = false;
		mState[(UINT)ePlayerState::Left] = false;
		mState[(UINT)ePlayerState::Right] = false;
		mState[(UINT)ePlayerState::FrontRight] = false;
		mState[(UINT)ePlayerState::FrontLeft] = false;
		mState[(UINT)ePlayerState::BackRight] = false;
		mState[(UINT)ePlayerState::BackLeft] = false;
		mState[(UINT)ePlayerState::Walking] = false;
		mState[(UINT)ePlayerState::Idle] = true;
		mState[(UINT)ePlayerState::Dodge] = false;
		mState[(UINT)ePlayerState::Attack] = false;
		mState[(UINT)ePlayerState::Reload] = false;
		mState[(UINT)ePlayerState::Fall] = false;
	}
	mainPlayerScript::~mainPlayerScript()
	{
	}
	void mainPlayerScript::Initalize()
	{

	}
	void mainPlayerScript::Update()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		animator = GetOwner()->GetComponent<Animator>();
		Rigidbody* rigidi = GetOwner()->GetComponent<Rigidbody>();
		Vector3 pos = transform->GetPosition();
		

		chWalking();




		/*
		{//													이동
			{
			
				{//위
					if (Input::GetKeyDown(eKeyCode::UP))
					{
						animator->Play(L"P_WalkingBack");
						mState[(UINT)ePlayerState::Front] = false;
						mState[(UINT)ePlayerState::Back] = true;
						mState[(UINT)ePlayerState::Left] = false;
						mState[(UINT)ePlayerState::Right] = false;

					}
					if (Input::GetKey(eKeyCode::UP))
					{
						
						pos.y += 1.0f * Time::DeltaTime();
						
					}
					if (Input::GetKeyUp(eKeyCode::UP))
					{
						animator->Play(L"P_IdleBack", true);
					}
				}
				{//아래
					if (Input::GetKeyDown(eKeyCode::DOWN))
					{
						animator->Play(L"P_WalkingFront");
						mState[(UINT)ePlayerState::Back] = false;
						mState[(UINT)ePlayerState::Front] = true;
						mState[(UINT)ePlayerState::Left] = false;
						mState[(UINT)ePlayerState::Right] = false;
					}
					if (Input::GetKey(eKeyCode::DOWN))
					{
						//Vector3 pos = transform->GetPosition();
						pos.y -= 1.0f * Time::DeltaTime();
						//transform->SetPosition(pos);
					}
					if (Input::GetKeyUp(eKeyCode::DOWN))
					{
						animator->Play(L"P_IdleFront", true);
					}
				}
				{//좌측			
					if (mState[(UINT)ePlayerState::Back] == true)
					{
						if (Input::GetKeyDown(eKeyCode::LEFT))
						{
							animator->Play(L"P_WalkingBackLeft");
							mState[(UINT)ePlayerState::Left] = true;
							mState[(UINT)ePlayerState::Right] = false;
						}
						if (Input::GetKey(eKeyCode::LEFT))
						{
							
							pos.x -= 1.0f * Time::DeltaTime();
							
						}
						if (Input::GetKeyUp(eKeyCode::LEFT))
						{
							animator->Play(L"P_IdleBackLeft", true);
						}
					}
					else if (mState[(UINT)ePlayerState::Front] = true)
					{
						if (Input::GetKeyDown(eKeyCode::LEFT))
						{
							animator->Play(L"P_WalkingLeft");
							mState[(UINT)ePlayerState::Left] = true;
							mState[(UINT)ePlayerState::Right] = false;
						}
						if (Input::GetKey(eKeyCode::LEFT))
						{
							
							pos.x -= 1.0f * Time::DeltaTime();
							
						}
						if (Input::GetKeyUp(eKeyCode::LEFT))
						{
							animator->Play(L"P_IdleLeft", true);
						}
					}
				}
				{//우측			
					if (mState[(UINT)ePlayerState::Back] == true)
					{
						if (Input::GetKeyDown(eKeyCode::RIGHT))
						{
							animator->Play(L"P_WalkingBackRight");
							mState[(UINT)ePlayerState::Left] = false;
							mState[(UINT)ePlayerState::Right] = true;
						}
						if (Input::GetKey(eKeyCode::RIGHT))
						{
							
							pos.x += 1.0f * Time::DeltaTime();
							
						}
						if (Input::GetKeyUp(eKeyCode::RIGHT))
						{
							animator->Play(L"P_IdleBackRight", true);
						}
					}
					else if (mState[(UINT)ePlayerState::Front] = true)
					{
						if (Input::GetKeyDown(eKeyCode::RIGHT))
						{
							animator->Play(L"P_WalkingRight");
							mState[(UINT)ePlayerState::Left] = false;
							mState[(UINT)ePlayerState::Right] = true;
						}
						if (Input::GetKey(eKeyCode::RIGHT))
						{
							
							pos.x += 1.0f * Time::DeltaTime();
						
						}
						if (Input::GetKeyUp(eKeyCode::RIGHT))
						{
							animator->Play(L"P_IdleRight", true);
						}
					}
				}
				/*
				{//위 + 오른쪽
					if (Input::GetKeyDown(eKeyCode::UP) && Input::GetKeyDown(eKeyCode::RIGHT))
					{
						animator->Play(L"P_WalkingBackRight");
						mState[(UINT)ePlayerState::BackRight] = true;
					}
					if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::RIGHT))
					{
						Vector3 pos = transform->GetPosition();
						pos += Vector3(0.2f, 0.2f, 0.0f) * Time::DeltaTime();
						transform->SetPosition(pos);
					}
					if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::RIGHT))
					{
						animator->Play(L"P_IdleBackRight", true);
					}
				}
				{//위 + 왼쪽
					if (Input::GetKeyDown(eKeyCode::UP) && Input::GetKeyDown(eKeyCode::LEFT))
					{
						animator->Play(L"P_WalkingLeft");
						mState[(UINT)ePlayerState::BackLeft] = true;
					}
					if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::LEFT))
					{
						Vector3 pos = transform->GetPosition();
						pos += Vector3(-0.2f, 0.2f, 0.0f) * Time::DeltaTime();
						transform->SetPosition(pos);
					}
					if (Input::GetKeyUp(eKeyCode::UP) && Input::GetKeyUp(eKeyCode::LEFT))
					{
						animator->Play(L"P_IdleBackLeft", true);
					}
				}
				{//아래 + 왼쪽
					if (Input::GetKeyDown(eKeyCode::DOWN) && Input::GetKeyDown(eKeyCode::LEFT))
					{
						animator->Play(L"P_WalkingBackLeft");
						mState[(UINT)ePlayerState::BackLeft] = true;
					}
					if (Input::GetKey(eKeyCode::DOWN) && Input::GetKey(eKeyCode::LEFT))
					{
						Vector3 pos = transform->GetPosition();
						pos += Vector3(-0.2f, -0.2f, 0.0f) * Time::DeltaTime();
						transform->SetPosition(pos);
					}
					if (Input::GetKeyUp(eKeyCode::DOWN) && Input::GetKeyUp(eKeyCode::LEFT))
					{
						animator->Play(L"P_IdleLeft", true);
					}
				}
				{//아래 + 오른쪽
					if (Input::GetKeyDown(eKeyCode::DOWN) && Input::GetKeyDown(eKeyCode::RIGHT))
					{
						animator->Play(L"P_WalkingRight");
						mState[(UINT)ePlayerState::BackRight] = true;
					}
					if (Input::GetKey(eKeyCode::DOWN) && Input::GetKey(eKeyCode::RIGHT))
					{
						Vector3 pos = transform->GetPosition();
						pos += Vector3(0.2f, -0.2f, 0.0f) * Time::DeltaTime();
						transform->SetPosition(pos);
					}
					if (Input::GetKeyUp(eKeyCode::DOWN) && Input::GetKeyUp(eKeyCode::RIGHT))
					{
						animator->Play(L"P_IdleRight", true);
					}
				}
				
				transform->SetPosition(pos);
			}
		}
		*/
		{//															구르기 
			if (Input::GetKeyDown(eKeyCode::RBTN))
			{
				mState[(UINT)ePlayerState::Dodge] = true;

				if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true)
				{
					animator->Play(L"P_DodgeRight", false);
					rigidi->AddForce(Vector3(200.f, -200.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeRight") = std::bind(&mainPlayerScript::IdleState, this);
				}
				else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true) 
				{
					animator->Play(L"P_DodgeLeft", false);
					rigidi->AddForce(Vector3(-200.f, -200.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeLeft") = std::bind(&mainPlayerScript::IdleState, this);
				}
				else if (mState[(UINT)ePlayerState::Front] == true)
				{
					animator->Play(L"P_DodgeFront", false);

					rigidi->AddForce(Vector3(0.f, -200.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeFront") = std::bind(&mainPlayerScript::IdleState, this);
				}
				else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
				{
					animator->Play(L"P_DodgeBackRight", false);
					rigidi->AddForce(Vector3(200.f, 200.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&mainPlayerScript::IdleState, this);

				}
				else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
				{
					animator->Play(L"P_DodgeBackLeft", false);
					rigidi->AddForce(Vector3(-200.f, 200.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeBackLeft") = std::bind(&mainPlayerScript::IdleState, this);
				}
				else if (mState[(UINT)ePlayerState::Back] == true)
				{
					animator->Play(L"P_DodgeBack", false);
					rigidi->AddForce(Vector3(0.f, 200.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeBack") = std::bind(&mainPlayerScript::IdleState, this);
				}

			}
		}
	}
	void mainPlayerScript::FixedUpdate()
	{
	}
	void mainPlayerScript::Render()
	{
	}
	void mainPlayerScript::OnCollisionEnter(Collider2D* oppo)
	{
	}
	void mainPlayerScript::OnCollision(Collider2D* oppo)
	{
	}
	void mainPlayerScript::OnCollisionExit(Collider2D* oppo)
	{
	}
	void mainPlayerScript::OnTriggerEnter(Collider2D* oppo)
	{
	}
	void mainPlayerScript::OnTrigger(Collider2D* oppo)
	{
	}
	void mainPlayerScript::OnTriggerExit(Collider2D* oppo)
	{
	}
	void mainPlayerScript::chWalking()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector3 pos = transform->GetPosition();

		Vector3 direction = Vector3::Zero;
		{//움직임

			//					위
			if (Input::GetKeyDown(eKeyCode::UP))
			{
				mState[(UINT)ePlayerState::Back] = true;
				mState[(UINT)ePlayerState::Walking] = true;

				mState[(UINT)ePlayerState::Front] = false;
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = false;

				if (direction == Vector3::Left) {
					mState[(UINT)ePlayerState::Left] = true;
				}
				else if (direction == Vector3::Right) {
					mState[(UINT)ePlayerState::Right] = true;
				}
				else {
					mState[(UINT)ePlayerState::Left] = false;
					mState[(UINT)ePlayerState::Right] = false;
				}

				chState();
			}
			if (Input::GetKey(eKeyCode::UP))
			{
				direction += Vector3::Up;
			}
			if (Input::GetKeyUp(eKeyCode::UP))
			{
				mState[(UINT)ePlayerState::Walking] = false;
				mState[(UINT)ePlayerState::Idle] = true;
				chState();
			}


			//					아래
			if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				mState[(UINT)ePlayerState::Front] = true;
				mState[(UINT)ePlayerState::Walking] = true;

				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = false;

				if (direction == Vector3::Left) {
					mState[(UINT)ePlayerState::Left] = true;
				}
				else if (direction == Vector3::Right) {
					mState[(UINT)ePlayerState::Right] = true;
				}
				else {
					mState[(UINT)ePlayerState::Left] = false;
					mState[(UINT)ePlayerState::Right] = false;
				}

				chState();

			}
			if (Input::GetKey(eKeyCode::DOWN)) {
				direction += Vector3::Down;
			}
			if (Input::GetKeyUp(eKeyCode::DOWN))
			{
				mState[(UINT)ePlayerState::Walking] = false;
				mState[(UINT)ePlayerState::Idle] = true;
				chState();
			}


			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				mState[(UINT)ePlayerState::Left] = true;
				mState[(UINT)ePlayerState::Walking] = true;

				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = false;
				mState[(UINT)ePlayerState::Right] = false;

				if (direction == Vector3::Up) {
					mState[(UINT)ePlayerState::Back] = true;
				}
				else if (direction == Vector3::Down) {
					mState[(UINT)ePlayerState::Front] = true;
				}
				else {
					mState[(UINT)ePlayerState::Back] = false;
					mState[(UINT)ePlayerState::Front] = false;
				}
				chState();
			}
			if (Input::GetKey(eKeyCode::LEFT)) {
				direction += Vector3::Left;

			}
			if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				mState[(UINT)ePlayerState::Walking] = false;
				mState[(UINT)ePlayerState::Idle] = true;
				chState();
			}



			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				mState[(UINT)ePlayerState::Right] = true;
				mState[(UINT)ePlayerState::Walking] = true;

				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = false;
				mState[(UINT)ePlayerState::Left] = false;

				if (direction == Vector3::Up) {
					mState[(UINT)ePlayerState::Back] = true;
				}
				else if (direction == Vector3::Down) {
					mState[(UINT)ePlayerState::Front] = true;
				}
				else {
					mState[(UINT)ePlayerState::Back] = false;
					mState[(UINT)ePlayerState::Front] = false;
				}
				chState();
			}
			if (Input::GetKey(eKeyCode::RIGHT)) {
				direction += Vector3::Right;
			}
			if (Input::GetKeyUp(eKeyCode::RIGHT))
			{
				mState[(UINT)ePlayerState::Walking] = false;
				mState[(UINT)ePlayerState::Idle] = true;
				chState();
			}
		}

		if (direction != Vector3::Zero && direction != Vector3::Up && direction != Vector3::Down &&
			direction != Vector3::Left && direction != Vector3::Right) {
			direction.Normalize();
		}
		
		// Move the character based on the direction
		pos += direction * 1.0f * Time::DeltaTime();
		transform->SetPosition(pos);
	}
	void mainPlayerScript::chState()
	{
		if (mState[(UINT)ePlayerState::Idle] == true) {
			if (mState[(UINT)ePlayerState::Front] == true)
			{
				animator->Play(L"P_IdleFront");
			}
			else if (mState[(UINT)ePlayerState::Back] == true)
			{
				animator->Play(L"P_IdleBack");
			}
			else if (mState[(UINT)ePlayerState::Left] == true)
			{
				animator->Play(L"P_IdleLeft");
			}
			else if (mState[(UINT)ePlayerState::Right] == true)
			{
				animator->Play(L"P_IdleRight");
			}
		}
		
		if (mState[(UINT)ePlayerState::Walking] == true) 
		{
			if (mState[(UINT)ePlayerState::Front] == true)
			{
				animator->Play(L"P_WalkingFront");
			}
			if (mState[(UINT)ePlayerState::Back] == true)
			{
				animator->Play(L"P_WalkingBack");
			}
			if (mState[(UINT)ePlayerState::Left] == true)
			{
				if (mState[(UINT)ePlayerState::Front] == true) 
				{
					animator->Play(L"P_WalkingLeft");
				}
				else if (mState[(UINT)ePlayerState::Back] == true) 
				{
					animator->Play(L"P_WalkingBackLeft");
				}
				else 
				{
					animator->Play(L"P_WalkingLeft");
				}
			}
			else if (mState[(UINT)ePlayerState::Right] == true)
			{
				if (mState[(UINT)ePlayerState::Front] == true)
				{
					animator->Play(L"P_WalkingRight");
				}
				else if (mState[(UINT)ePlayerState::Back] == true)
				{
					animator->Play(L"P_WalkingBackRight");
				}
				else
				{
					animator->Play(L"P_WalkingRight");
				}
			}
		
		}

	}
	void mainPlayerScript::IdleState()
	{
		if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true) 
		{
			animator->Play(L"P_IdleRight", true);
		}
		else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true)
		{
			animator->Play(L"P_IdleLeft", true);
		}
		else if (mState[(UINT)ePlayerState::Front] == true) 
		{
			animator->Play(L"P_IdleFront", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true) 
		{
			animator->Play(L"P_IdleBackRight", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true) 
		{
			animator->Play(L"P_IdleBackLeft", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true)
		{
			animator->Play(L"P_IdleBack", true);
		}

		mState[(UINT)ePlayerState::Dodge] = false;
	}
}

