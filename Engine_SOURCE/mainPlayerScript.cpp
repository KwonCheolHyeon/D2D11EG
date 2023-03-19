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


		{//위
			if (Input::GetKeyDown(eKeyCode::UP))
			{
				animator->Play(L"P_WalkingBack");
				mState[(UINT)ePlayerState::Front] = false;
				mState[(UINT)ePlayerState::Back] = true;
				
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

