#include "mainPlayerScript.h"
#include "chTransform.h"
#include "chTime.h"
#include "chAnimator.h"
#include "chInput.h"
#include "chGameObject.h"
#include "chRigidbody.h"
#include "chInput.h"

namespace ch
{
	mainPlayerScript::mainPlayerScript()
	{
		mState[(UINT)ePlayerState::Front] = true;
		mState[(UINT)ePlayerState::Back] = false;
		mState[(UINT)ePlayerState::Left] = false;
		mState[(UINT)ePlayerState::Right] = false;
		mState[(UINT)ePlayerState::Walking] = false;
		mState[(UINT)ePlayerState::Idle] = true;
		mState[(UINT)ePlayerState::Dodge] = false;
		mState[(UINT)ePlayerState::Attack] = false;
		mState[(UINT)ePlayerState::Reload] = false;
		mState[(UINT)ePlayerState::Fall] = false;
		mState[(UINT)ePlayerState::Weapone] = false;
	}
	mainPlayerScript::~mainPlayerScript()
	{
		
	}
	void mainPlayerScript::Initalize()
	{
		transform = GetOwner()->GetComponent<Transform>();
		rigidi = GetOwner()->GetComponent<Rigidbody>();
	}
	void mainPlayerScript::Update()
	{
		animator = GetOwner()->GetComponent<Animator>();
		
		
		if (mState[(UINT)ePlayerState::Dodge] == false) 
		{ //							걷기 함수
			chCheckDirectionKey();
			chState();
			chWalking();
		}
		//								구르기 
		if (Input::GetKeyDown(eKeyCode::RBTN) && mState[(UINT)ePlayerState::Dodge] == false && chCheckDirectionKey() == true)
		{
			mState[(UINT)ePlayerState::Dodge] = true;
			DodgeState();
			chDodging();
			Rigidbody::dodgeForceReset = true;
		}
		
	}
	void mainPlayerScript::FixedUpdate()
	{
	}
	void mainPlayerScript::Render()
	{
	}

	//충돌 관련
	#pragma region Collision
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
	#pragma endregion

	//chWalking : 캐릭터 이동
	void mainPlayerScript::chWalking() //								움직임 함수
	{
		Vector3 pos = transform->GetPosition();
		Vector3 direction = Vector3::Zero;
		{//														움직임
			//					위
			if (Input::GetKey(eKeyCode::W))
			{
				direction += 3.5f * transform->Up() * Time::DeltaTime();
			}
			//					아래
			if (Input::GetKey(eKeyCode::S)) 
			{
				direction -= 3.5f * transform->Up() * Time::DeltaTime();
			}
			//					왼쪽
			if (Input::GetKey(eKeyCode::A)) //뒤집어서 
			{
				direction += 3.5f * transform->Right() * Time::DeltaTime();
			}
			//					오른쪽
			if (Input::GetKey(eKeyCode::D)) 
			{
				direction += 3.5f * transform->Right() * Time::DeltaTime();
			}
			//			대각선 방향 움직일때
			if (direction != Vector3::Zero && direction != Vector3::Up && direction != Vector3::Down &&
				direction != Vector3::Left && direction != Vector3::Right) 
			{
				direction.Normalize();
			}

			pos += direction * 2.0f * Time::DeltaTime();
			transform->SetPosition(pos);
		}
	}
	bool mainPlayerScript::chCheckDirectionKey()
	{//												상하좌우를 하나라도 누르고 있을때 true  혹시나 오류가 있으면 GetKeyDown추가 해주기
		if ( Input::GetKey(eKeyCode::D) == true  || Input::GetKey(eKeyCode::A) == true || Input::GetKey(eKeyCode::W) == true || Input::GetKey(eKeyCode::S) == true) 
		{
			mState[(UINT)ePlayerState::Walking] = true;
			mState[(UINT)ePlayerState::Idle] = false;
			return true;
		}
		else 
		{
			mState[(UINT)ePlayerState::Idle] = true;
			mState[(UINT)ePlayerState::Walking] = false;
			return false;
		}
	}
	bool mainPlayerScript::chCheckDirectionKeyDoge()
	{
		if (Input::GetKey(eKeyCode::D) == true || Input::GetKey(eKeyCode::A) == true || Input::GetKey(eKeyCode::W) == true || Input::GetKey(eKeyCode::S) == true)
		{
			
			allowDodge();

			return true;
		}
		else 
		{
			IdleState();
			return false;
		}
		
	}



	//chState : 캐릭터 상태 체크후 애니메이션 실행
	void mainPlayerScript::chState()
	{
		if(Input::GetKeyDown(eKeyCode::W)) 
		{
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Front] = false;
			if (Input::GetKey(eKeyCode::A))
			{
				mState[(UINT)ePlayerState::Left] = true;
				mState[(UINT)ePlayerState::Right] = false;
				GetOwner()->SetLeft();
			}
			else if(Input::GetKey(eKeyCode::D))
			{
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = true;
				GetOwner()->SetRight();
			}
			else if (((Input::GetKeyDown(eKeyCode::A) == true || Input::GetKey(eKeyCode::A) == true) && (Input::GetKeyDown(eKeyCode::D) == true || Input::GetKey(eKeyCode::D) == true) )!= true)
			{
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = false;
			}
			//walking애니메이션 실행
			WalkingState();
		}
		if (Input::GetKeyUp(eKeyCode::W))
		{
			if(chCheckDirectionKey()== false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				IdleState();
			}
			else 
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				WalkingState();
			}
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Front] = true;
			if (Input::GetKey(eKeyCode::A))
			{
				mState[(UINT)ePlayerState::Left] = true;
				mState[(UINT)ePlayerState::Right] = false;
				GetOwner()->SetLeft();
			}
			else if (Input::GetKey(eKeyCode::D))
			{
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = true;
				GetOwner()->SetRight();
			}
			else if (((Input::GetKeyDown(eKeyCode::A) == true || Input::GetKey(eKeyCode::A) == true) && (Input::GetKeyDown(eKeyCode::D) == true || Input::GetKey(eKeyCode::D) == true)) != true)
			{
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = false;
			}
			//walking애니메이션 실행
			WalkingState();
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				IdleState();
			}
			else									//다른키가 눌려져 있는 상태
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				WalkingState();
			}
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
			GetOwner()->SetLeft();
			if (Input::GetKey(eKeyCode::W))
			{
				mState[(UINT)ePlayerState::Back] = true;
				mState[(UINT)ePlayerState::Front] = false;
			}
			else if (Input::GetKey(eKeyCode::S))
			{
				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = true;
			}
			else if(Input::GetKeyUp(eKeyCode::S) == true && Input::GetKeyUp(eKeyCode::W) == true)
			{
				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = false;
			}
			
			//walking애니메이션 실행

			WalkingState();
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				IdleState();
			}
			else									//다른키가 눌려져 있는 상태
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				WalkingState();
			}
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;
			GetOwner()->SetRight();
			if (Input::GetKey(eKeyCode::W))
			{
				mState[(UINT)ePlayerState::Back] = true;
				mState[(UINT)ePlayerState::Front] = false;
			}
			else if (Input::GetKey(eKeyCode::S))
			{
				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = true;
			}
			else if(Input::GetKeyUp(eKeyCode::S)==true && Input::GetKeyUp(eKeyCode::W)==true)
			{
				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = false;
			}
			//walking애니메이션 실행
			WalkingState();
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				IdleState();
			}
			else									//다른키가 눌려져 있는 상태
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				WalkingState();
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
			animator->Play(L"P_IdleRight", true);
		}
		else if (mState[(UINT)ePlayerState::Front] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
		{
			animator->Play(L"P_IdleFront", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true) 
		{
			animator->Play(L"P_IdleBackRight", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true) 
		{
			animator->Play(L"P_IdleBackRight", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
		{
			animator->Play(L"P_IdleBack", true);
		}

		mState[(UINT)ePlayerState::Dodge] = false;
	}
	void mainPlayerScript::WalkingState()
	{
		if ( (Input::GetKeyDown(eKeyCode::W) == true || Input::GetKey(eKeyCode::W) == true) && (Input::GetKeyDown(eKeyCode::A) == true || Input::GetKey(eKeyCode::A) == true))
		{
			animator->Play(L"P_WalkingBackRight", true);
			GetOwner()->SetLeft();
		}
		else if ((Input::GetKeyDown(eKeyCode::W) == true || Input::GetKey(eKeyCode::W) == true) && (Input::GetKeyDown(eKeyCode::D) == true || Input::GetKey(eKeyCode::D) == true))
		{
			animator->Play(L"P_WalkingBackRight", true);
			GetOwner()->SetRight();
		}
		else if ((Input::GetKeyDown(eKeyCode::S) == true || Input::GetKey(eKeyCode::S) == true) && (Input::GetKeyDown(eKeyCode::A) == true || Input::GetKey(eKeyCode::A) == true))
		{
			animator->Play(L"P_WalkingRight", true);
			GetOwner()->SetLeft();
		}
		else if ((Input::GetKeyDown(eKeyCode::S) == true || Input::GetKey(eKeyCode::S) == true) && (Input::GetKeyDown(eKeyCode::D) == true || Input::GetKey(eKeyCode::D) == true))
		{
			animator->Play(L"P_WalkingRight", true);
			GetOwner()->SetRight();
		}
		else if ((Input::GetKeyDown(eKeyCode::W) == true || Input::GetKey(eKeyCode::W) == true))
		{
			animator->Play(L"P_WalkingBack", true);
		}
		else if ((Input::GetKeyDown(eKeyCode::S) == true || Input::GetKey(eKeyCode::S) == true))
		{
			animator->Play(L"P_WalkingFront", true);
		}
		else if ((Input::GetKeyDown(eKeyCode::A) == true || Input::GetKey(eKeyCode::A) == true))
		{
			if (mState[(UINT)ePlayerState::Back] == true) 
			{
				animator->Play(L"P_WalkingRight", true);
				GetOwner()->SetLeft();
			}
			else if (mState[(UINT)ePlayerState::Front] == true) 
			{
				animator->Play(L"P_WalkingRight", true);
				GetOwner()->SetLeft();
			}
		}
		else if ((Input::GetKeyDown(eKeyCode::D) == true || Input::GetKey(eKeyCode::D) == true))
		{
			if (mState[(UINT)ePlayerState::Back] == true)
			{
				animator->Play(L"P_WalkingBackRight", true);
				GetOwner()->SetRight();
			}
			else if (mState[(UINT)ePlayerState::Front] == true)
			{
				animator->Play(L"P_WalkingRight", true);
				GetOwner()->SetRight();
			}
		}
	}
	//걷기, 기본 행동 

#pragma region Weapone


	void mainPlayerScript::WeaponeIdleState()
	{
		if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true)
		{
			animator->Play(L"P_WIdleRight", true);
		}
		else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true)
		{
			animator->Play(L"P_WIdleRight", true);
		}
		else if (mState[(UINT)ePlayerState::Front] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
		{
			animator->Play(L"P_WIdleFront", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
		{
			animator->Play(L"P_WIdleBackRight", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
		{
			animator->Play(L"P_WIdleBackRight", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
		{
			animator->Play(L"P_WIdleBack", true);
		}

		mState[(UINT)ePlayerState::Dodge] = false;
	}

	void mainPlayerScript::WeaponeWalkingState()
	{


	}
#pragma endregion

	//구르기 관련
	void mainPlayerScript::chDodging()
	{
		if ( (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W) ) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)) ) 
		{
			rigidi->AddForce(Vector3(-2000.f, 2000.0f, 0.0f));
		}
		else if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))) 
		{
			rigidi->AddForce(Vector3(2000.f, 2000.0f, 0.0f));
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			rigidi->AddForce(Vector3(2000.f, -2000.0f, 0.0f));
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			rigidi->AddForce(Vector3(-2000.f, -2000.0f, 0.0f));
		}
		else if ( Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S) )
		{
			rigidi->AddForce(Vector3(0.f, -2000.0f, 0.0f));
		}
		else if ( Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W) )
		{
			rigidi->AddForce(Vector3(0.f, 2000.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			rigidi->AddForce(Vector3(-2000.f, 0.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			rigidi->AddForce(Vector3(2000.f, 0.0f, 0.0f));
		}
	}
	void mainPlayerScript::DodgeState()
	{
		if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			animator->Play(L"P_DodgeBackLeft", false);
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			animator->Play(L"P_DodgeBackRight", false);
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			animator->Play(L"P_DodgeRight", false);
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			animator->Play(L"P_DodgeLeft", false);
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			animator->Play(L"P_DodgeFront", false);
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W))
		{
			animator->Play(L"P_DodgeBack", false);
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
			if (mState[(UINT)ePlayerState::Back] == true)
			{
				animator->Play(L"P_DodgeBackLeft", false);
			}
			else if (mState[(UINT)ePlayerState::Front] == true)
			{
				animator->Play(L"P_DodgeLeft", false);
			}
		}
		else if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;

			if (mState[(UINT)ePlayerState::Back] == true)
			{
				animator->Play(L"P_DodgeBackRight", false);
			}
			else if (mState[(UINT)ePlayerState::Front] == true)
			{
				animator->Play(L"P_DodgeRight", false);
			}
		}
		afterDodge();

	
	}
	void mainPlayerScript::afterDodge()
	{
		animator->GetCompleteEvent(L"P_DodgeRight") = std::bind(&mainPlayerScript::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeLeft") = std::bind(&mainPlayerScript::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&mainPlayerScript::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeBackLeft") = std::bind(&mainPlayerScript::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeFront") = std::bind(&mainPlayerScript::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeBack") = std::bind(&mainPlayerScript::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeLeft") = std::bind(&mainPlayerScript::chCheckDirectionKeyDoge, this);
		animator->GetCompleteEvent(L"P_DodgeRight") = std::bind(&mainPlayerScript::chCheckDirectionKeyDoge, this);
	
	}
	void mainPlayerScript::allowDodge()
	{
		mState[(UINT)ePlayerState::Dodge] = false;
		WalkingState();
	}





}

