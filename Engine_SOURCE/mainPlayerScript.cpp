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

					float moveDuration = 1.1f; // adjust the duration as needed
					float elapsedTime = 0.0f;

					Vector3 startPos = transform->GetPosition();
					Vector3 targetPos = startPos + Vector3(0.3f, 0.0f, 0.0f); // adjust the target position as needed

					Vector3 velocity = (targetPos - startPos) / moveDuration; // calculate the velocity

					while (elapsedTime < moveDuration)
					{
						Vector3 pos = transform->GetPosition() + velocity * Time::DeltaTime(); // update the position based on velocity and time
						transform->SetPosition(pos);

						elapsedTime += Time::DeltaTime();
					}
				}
				else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true) 
				{
					animator->Play(L"P_DodgeLeft", false);

					float moveDuration = 1.1f; // adjust the duration as needed
					float elapsedTime = 0.0f;

					Vector3 startPos = transform->GetPosition();
					Vector3 targetPos = startPos + Vector3(-0.3f, 0.0f, 0.0f); // adjust the target position as needed

					//Vector3 velocity = (targetPos - startPos) / moveDuration; // calculate the velocity

					while (elapsedTime < moveDuration)
					{
						float t = elapsedTime / moveDuration; // calculate the interpolation factor
						Vector3 pos = Vector3::Lerp(startPos, targetPos, t);
						transform->SetPosition(pos);

						elapsedTime += Time::DeltaTime();
					}
				
				}
				else if (mState[(UINT)ePlayerState::Front] == true)
				{
					animator->Play(L"P_DodgeFront", false);

					float moveDuration = 1.1f; // adjust the duration as needed
					float elapsedTime = 0.0f;

					Vector3 startPos = transform->GetPosition();
					Vector3 targetPos = startPos + Vector3(0.0f, -0.3f, 0.0f); // adjust the target position as needed

					Vector3 velocity = (targetPos - startPos) / moveDuration; // calculate the velocity

					while (elapsedTime < moveDuration)
					{
						Vector3 pos = transform->GetPosition() + velocity * Time::DeltaTime(); // update the position based on velocity and time
						transform->SetPosition(pos);

						elapsedTime += Time::DeltaTime();
					}
				}
				else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
				{
					animator->Play(L"P_DodgeBackRight", false);

					float moveDuration = 1.1f; // adjust the duration as needed
					float elapsedTime = 0.0f;

					Vector3 startPos = transform->GetPosition();
					Vector3 targetPos = startPos + Vector3(0.3f, 0.0f, 0.0f); // adjust the target position as needed

					Vector3 velocity = (targetPos - startPos) / moveDuration; // calculate the velocity

					while (elapsedTime < moveDuration)
					{
						Vector3 pos = transform->GetPosition() + velocity * Time::DeltaTime(); // update the position based on velocity and time
						transform->SetPosition(pos);

						elapsedTime += Time::DeltaTime();
					}

				}
				else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
				{
					animator->Play(L"P_DodgeBackLeft", false);

					float moveDuration = 1.1f; // adjust the duration as needed
					float elapsedTime = 0.0f;

					Vector3 startPos = transform->GetPosition();
					Vector3 targetPos = startPos + Vector3(-0.3f, 0.0f, 0.0f); // adjust the target position as needed

					Vector3 velocity = (targetPos - startPos) / moveDuration; // calculate the velocity

					while (elapsedTime < moveDuration)
					{
						Vector3 pos = transform->GetPosition() + velocity * Time::DeltaTime(); // update the position based on velocity and time
						transform->SetPosition(pos);

						elapsedTime += Time::DeltaTime();
					}

				}
				else if (mState[(UINT)ePlayerState::Back] == true)
				{
					animator->Play(L"P_DodgeBack", false);

					float moveDuration = 1.1f; // adjust the duration as needed
					float elapsedTime = 0.0f;

					Vector3 startPos = transform->GetPosition();
					Vector3 targetPos = startPos + Vector3(0.0f, 0.3f, 0.0f); // adjust the target position as needed

					Vector3 velocity = (targetPos - startPos) / moveDuration; // calculate the velocity

					while (elapsedTime < moveDuration)
					{
						Vector3 pos = transform->GetPosition() + velocity * Time::DeltaTime(); // update the position based on velocity and time
						transform->SetPosition(pos);

						elapsedTime += Time::DeltaTime();
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

