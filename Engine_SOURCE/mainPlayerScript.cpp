#include "mainPlayerScript.h"
#include "chTransform.h"
#include "chTime.h"
#include "chAnimator.h"
#include "chInput.h"
#include "chGameObject.h"


namespace ch
{
	mainPlayerScript::mainPlayerScript()
	{
		mState[(UINT)ePlayerState::Front] = true;
		mState[(UINT)ePlayerState::Back] = false;
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
		Animator* animator = GetOwner()->GetComponent<Animator>();

		{//															이동
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
					Vector3 pos = transform->GetPosition();
					pos.y += 2.0f * Time::DeltaTime();
					transform->SetPosition(pos);
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
					Vector3 pos = transform->GetPosition();
					pos.y -= 2.0f * Time::DeltaTime();
					transform->SetPosition(pos);
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
						Vector3 pos = transform->GetPosition();
						pos.x -= 2.0f * Time::DeltaTime();
						transform->SetPosition(pos);
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
						Vector3 pos = transform->GetPosition();
						pos.x -= 2.0f * Time::DeltaTime();
						transform->SetPosition(pos);
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
						Vector3 pos = transform->GetPosition();
						pos.x += 2.0f * Time::DeltaTime();
						transform->SetPosition(pos);
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
						Vector3 pos = transform->GetPosition();
						pos.x += 2.0f * Time::DeltaTime();
						transform->SetPosition(pos);
					}
					if (Input::GetKeyUp(eKeyCode::RIGHT))
					{
						animator->Play(L"P_IdleRight", true);
					}
				}
			}
		}

		{//															구르기 
			if (Input::GetKeyDown(eKeyCode::RBTN))
			{
				
				if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true) 
				{
					
					animator->Play(L"P_DodgeRight", false);

					const float ROLL_DURATION_SEC = 1.1f; // The roll lasts for 1.1 seconds
					float elapsedSec = 0.0f;

					while (elapsedSec < ROLL_DURATION_SEC) {
						// Update the elapsed time
						elapsedSec += Time::DeltaTime();
											
						// Use the animation's speed to adjust the player's position
						Vector3 pos = transform->GetPosition();
						pos += Vector3::Right * Time::DeltaTime() * 1.0f;
						transform->SetPosition(pos);

						// Update the player's animation
						animator->Update();

						// Wait for the next frame
						Yield();
					}
				}
				else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true) 
				{
					animator->Play(L"P_DodgeLeft", false);

					const float ROLL_DURATION_SEC = 1.1f; // The roll lasts for 1.1 seconds
					float elapsedSec = 0.0f;

					while (elapsedSec < ROLL_DURATION_SEC) {
						// Update the elapsed time
						elapsedSec += Time::DeltaTime();

						// Use the animation's speed to adjust the player's position
						Vector3 pos = transform->GetPosition();
						pos += Vector3::Left * Time::DeltaTime() * 1.0f;
						transform->SetPosition(pos);

						// Update the player's animation
						animator->Update();

						// Wait for the next frame
						Yield();
					}
				
				}
				else if (mState[(UINT)ePlayerState::Front] == true)
				{
					animator->Play(L"P_DodgeFront", false);

					const float ROLL_DURATION_SEC = 1.1f; // The roll lasts for 1.1 seconds
					float elapsedSec = 0.0f;

					while (elapsedSec < ROLL_DURATION_SEC) {
						// Update the elapsed time
						elapsedSec += Time::DeltaTime();

						// Use the animation's speed to adjust the player's position
						Vector3 pos = transform->GetPosition();
						pos += Vector3::Down * Time::DeltaTime() * 1.0f;
						transform->SetPosition(pos);

						// Update the player's animation
						animator->Update();

						// Wait for the next frame
						Yield();
					}
				}
				else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
				{
					animator->Play(L"P_DodgeBackRight", false);

					const float ROLL_DURATION_SEC = 1.1f; // The roll lasts for 1.1 seconds
					float elapsedSec = 0.0f;

					while (elapsedSec < ROLL_DURATION_SEC) {
						// Update the elapsed time
						elapsedSec += Time::DeltaTime();

						// Use the animation's speed to adjust the player's position
						Vector3 pos = transform->GetPosition();
						pos += Vector3::Right * Time::DeltaTime() * 1.0f;
						transform->SetPosition(pos);

						// Update the player's animation
						animator->Update();

						// Wait for the next frame
						Yield();
					}

				}
				else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
				{
					animator->Play(L"P_DodgeBackLeft", false);

					const float ROLL_DURATION_SEC = 1.1f; // The roll lasts for 1.1 seconds
					float elapsedSec = 0.0f;

					while (elapsedSec < ROLL_DURATION_SEC) {
						// Update the elapsed time
						elapsedSec += Time::DeltaTime();

						// Use the animation's speed to adjust the player's position
						Vector3 pos = transform->GetPosition();
						pos += Vector3::Left * Time::DeltaTime() * 1.0f;
						transform->SetPosition(pos);

						// Update the player's animation
						animator->Update();

						// Wait for the next frame
						Yield();
					}

				}
				else if (mState[(UINT)ePlayerState::Back] == true)
				{
					animator->Play(L"P_DodgeFront", false);

					const float ROLL_DURATION_SEC = 1.1f; // The roll lasts for 1.1 seconds
					float elapsedSec = 0.0f;

					while (elapsedSec < ROLL_DURATION_SEC) {
						// Update the elapsed time
						elapsedSec += Time::DeltaTime();

						// Use the animation's speed to adjust the player's position
						Vector3 pos = transform->GetPosition();
						pos += Vector3::Up * Time::DeltaTime() * 1.0f;
						transform->SetPosition(pos);

						// Update the player's animation
						animator->Update();

						// Wait for the next frame
						Yield();
					}
				}

			}
		}

		if (animator->GetEndEvent(L"P_DodgeRight"))
		{
			int a = 0;
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
}

