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
		{//															이동
			if (mState[(UINT)ePlayerState::Dodge] == false) {
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
		}
		{//															구르기 
			if (Input::GetKeyDown(eKeyCode::RBTN))
			{
				mState[(UINT)ePlayerState::Dodge] = true;

				if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true)
				{
					animator->Play(L"P_DodgeRight", false);
					rigidi->AddForce(Vector3(2000.f, 0.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeRight") = std::bind(&mainPlayerScript::IdleState, this);
				}
				else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true) 
				{
					animator->Play(L"P_DodgeLeft", false);
					rigidi->AddForce(Vector3(-2000.f, 0.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeLeft") = std::bind(&mainPlayerScript::IdleState, this);
				}
				else if (mState[(UINT)ePlayerState::Front] == true)
				{
					animator->Play(L"P_DodgeFront", false);

					rigidi->AddForce(Vector3(0.f, -2000.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeFront") = std::bind(&mainPlayerScript::IdleState, this);
				}
				else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
				{
					animator->Play(L"P_DodgeBackRight", false);
					rigidi->AddForce(Vector3(2000.f, 0.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&mainPlayerScript::IdleState, this);

				}
				else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
				{
					animator->Play(L"P_DodgeBackLeft", false);
					rigidi->AddForce(Vector3(-2000.f, 0.0f, 0.0f));
					animator->GetCompleteEvent(L"P_DodgeBackLeft") = std::bind(&mainPlayerScript::IdleState, this);
				}
				else if (mState[(UINT)ePlayerState::Back] == true)
				{
					animator->Play(L"P_DodgeBack", false);
					rigidi->AddForce(Vector3(0.f, 2000.0f, 0.0f));
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

