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

		transform = GetOwner()->GetComponent<Transform>();

	}
	void mainPlayerScript::Update()
	{
		animator = GetOwner()->GetComponent<Animator>();
		rigidi = GetOwner()->GetComponent<Rigidbody>();
		
		if (mState[(UINT)ePlayerState::Dodge] == false) 
		{ //							걷기 함수
			
			chCheckDirectionKey();
			chState();
			chWalking();
		}
		//								구르기 
		if (Input::GetKeyDown(eKeyCode::RBTN) && mState[(UINT)ePlayerState::Dodge] == false)
		{
			mState[(UINT)ePlayerState::Dodge] = true;
			DodgeState();
			chDodging();


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
	//chWalking : 캐릭터 이동
	void mainPlayerScript::chWalking() //								움직임 함수
	{
		
		Vector3 pos = transform->GetPosition();
		Vector3 direction = Vector3::Zero;
		{//														움직임

			//					위
			if (Input::GetKey(eKeyCode::UP))
			{
				direction += Vector3::Up;
			}
			//					아래
			if (Input::GetKey(eKeyCode::DOWN)) 
			{
				direction += Vector3::Down;
			}
			//					왼쪽
			if (Input::GetKey(eKeyCode::LEFT)) 
			{
				direction += Vector3::Left;
			}
			//					오른쪽
			if (Input::GetKey(eKeyCode::RIGHT)) 
			{
				direction += Vector3::Right;
			}
			//			대각선 방향 움직일때
			if (direction != Vector3::Zero && direction != Vector3::Up && direction != Vector3::Down &&
				direction != Vector3::Left && direction != Vector3::Right) 
			{
				direction.Normalize();
			}

			pos += direction * 1.0f * Time::DeltaTime();
			transform->SetPosition(pos);
		}
	}

	//
	bool mainPlayerScript::chCheckDirectionKey()
	{//												상하좌우를 하나라도 누르고 있을때 true  혹시나 오류가 있으면 GetKeyDown추가 해주기
		if ( Input::GetKey(eKeyCode::RIGHT) == true  || Input::GetKey(eKeyCode::LEFT) == true || Input::GetKey(eKeyCode::UP) == true || Input::GetKey(eKeyCode::DOWN) == true) 
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
		if (Input::GetKey(eKeyCode::RIGHT) == true || Input::GetKey(eKeyCode::LEFT) == true || Input::GetKey(eKeyCode::UP) == true || Input::GetKey(eKeyCode::DOWN) == true)
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
		if(Input::GetKeyDown(eKeyCode::UP)) 
		{
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Front] = false;
			if (Input::GetKey(eKeyCode::LEFT))
			{
				mState[(UINT)ePlayerState::Left] = true;
				mState[(UINT)ePlayerState::Right] = false;
			}
			else if(Input::GetKey(eKeyCode::RIGHT))
			{
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = true;
			}
			else if (((Input::GetKeyDown(eKeyCode::LEFT) == true || Input::GetKey(eKeyCode::LEFT) == true) && (Input::GetKeyDown(eKeyCode::RIGHT) == true || Input::GetKey(eKeyCode::RIGHT) == true) )!= true)
			{
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = false;
			}
			//walking애니메이션 실행
			WalkingState();
		}
		if (Input::GetKeyUp(eKeyCode::UP))
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

		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Front] = true;
			if (Input::GetKey(eKeyCode::LEFT))
			{
				mState[(UINT)ePlayerState::Left] = true;
				mState[(UINT)ePlayerState::Right] = false;
			}
			else if (Input::GetKey(eKeyCode::RIGHT))
			{
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = true;
			}
			else if (((Input::GetKeyDown(eKeyCode::LEFT) == true || Input::GetKey(eKeyCode::LEFT) == true) && (Input::GetKeyDown(eKeyCode::RIGHT) == true || Input::GetKey(eKeyCode::RIGHT) == true)) != true)
			{
				mState[(UINT)ePlayerState::Left] = false;
				mState[(UINT)ePlayerState::Right] = false;
			}
			//walking애니메이션 실행
			WalkingState();
		}
		if (Input::GetKeyUp(eKeyCode::DOWN))
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

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;

			if (Input::GetKey(eKeyCode::UP))
			{
				mState[(UINT)ePlayerState::Back] = true;
				mState[(UINT)ePlayerState::Front] = false;
			}
			else if (Input::GetKey(eKeyCode::DOWN))
			{
				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = true;
			}
			else if(Input::GetKeyUp(eKeyCode::DOWN) == true && Input::GetKeyUp(eKeyCode::UP) == true)
			{
				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = false;
			}
			
			//walking애니메이션 실행

			WalkingState();
		}
		if (Input::GetKeyUp(eKeyCode::LEFT))
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

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;
			if (Input::GetKey(eKeyCode::UP))
			{
				mState[(UINT)ePlayerState::Back] = true;
				mState[(UINT)ePlayerState::Front] = false;
			}
			else if (Input::GetKey(eKeyCode::DOWN))
			{
				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = true;
			}
			else if(Input::GetKeyUp(eKeyCode::DOWN)==true && Input::GetKeyUp(eKeyCode::UP)==true)
			{
				mState[(UINT)ePlayerState::Back] = false;
				mState[(UINT)ePlayerState::Front] = false;
			}
			//walking애니메이션 실행
			WalkingState();
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT))
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
			animator->Play(L"P_IdleLeft", true);
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
			animator->Play(L"P_IdleBackLeft", true);
		}
		else if (mState[(UINT)ePlayerState::Back] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
		{
			animator->Play(L"P_IdleBack", true);
		}

		mState[(UINT)ePlayerState::Dodge] = false;
	}
	void mainPlayerScript::WalkingState()
	{
		if ( (Input::GetKeyDown(eKeyCode::UP) == true || Input::GetKey(eKeyCode::UP) == true) && (Input::GetKeyDown(eKeyCode::LEFT) == true || Input::GetKey(eKeyCode::LEFT) == true))
		{
			animator->Play(L"P_WalkingBackLeft", true);
		}
		else if ((Input::GetKeyDown(eKeyCode::UP) == true || Input::GetKey(eKeyCode::UP) == true) && (Input::GetKeyDown(eKeyCode::RIGHT) == true || Input::GetKey(eKeyCode::RIGHT) == true))
		{
			animator->Play(L"P_WalkingBackRight", true);
		}
		else if ((Input::GetKeyDown(eKeyCode::DOWN) == true || Input::GetKey(eKeyCode::DOWN) == true) && (Input::GetKeyDown(eKeyCode::LEFT) == true || Input::GetKey(eKeyCode::LEFT) == true))
		{
			animator->Play(L"P_WalkingLeft", true);
		}
		else if ((Input::GetKeyDown(eKeyCode::DOWN) == true || Input::GetKey(eKeyCode::DOWN) == true) && (Input::GetKeyDown(eKeyCode::RIGHT) == true || Input::GetKey(eKeyCode::RIGHT) == true))
		{
			animator->Play(L"P_WalkingRight", true);
		}
		else if ((Input::GetKeyDown(eKeyCode::UP) == true || Input::GetKey(eKeyCode::UP) == true))
		{
			animator->Play(L"P_WalkingBack", true);
		}
		else if ((Input::GetKeyDown(eKeyCode::DOWN) == true || Input::GetKey(eKeyCode::DOWN) == true))
		{
			animator->Play(L"P_WalkingFront", true);
		}
		else if ((Input::GetKeyDown(eKeyCode::LEFT) == true || Input::GetKey(eKeyCode::LEFT) == true))
		{
			if (mState[(UINT)ePlayerState::Back] == true) 
			{
				animator->Play(L"P_WalkingBackLeft", true);
			}
			else if (mState[(UINT)ePlayerState::Front] == true) 
			{
				animator->Play(L"P_WalkingLeft", true);
			}
		}
		else if ((Input::GetKeyDown(eKeyCode::RIGHT) == true || Input::GetKey(eKeyCode::RIGHT) == true))
		{
			if (mState[(UINT)ePlayerState::Back] == true)
			{
				animator->Play(L"P_WalkingBackRight", true);
			}
			else if (mState[(UINT)ePlayerState::Front] == true)
			{
				animator->Play(L"P_WalkingRight", true);
			}
		}

	}
	//걷기, 기본 행동 
	// 
	// 
	//구르기 관련
	void mainPlayerScript::chDodging()
	{
		if ( (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP) ) && (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)) ) 
		{
			rigidi->AddForce(Vector3(-2000.f, 2000.0f, 0.0f));
		}
		else if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP)) && (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))) 
		{
			rigidi->AddForce(Vector3(2000.f, 2000.0f, 0.0f));
		}
		else if ((Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN)) && (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
		{
			rigidi->AddForce(Vector3(2000.f, -2000.0f, 0.0f));
		}
		else if ((Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN)) && (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
		{
			rigidi->AddForce(Vector3(-2000.f, -2000.0f, 0.0f));
		}
		else if ( Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN) )
		{
			rigidi->AddForce(Vector3(0.f, -2000.0f, 0.0f));
		}
		else if ( Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP) )
		{
			rigidi->AddForce(Vector3(0.f, 2000.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
		{
			rigidi->AddForce(Vector3(-2000.f, 0.0f, 0.0f));
		}
		else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
		{
			rigidi->AddForce(Vector3(2000.f, 0.0f, 0.0f));
		}
	}
	void mainPlayerScript::DodgeState()
	{
		if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP)) && (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
		{
			animator->Play(L"P_DodgeBackLeft", false);
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if ((Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP)) && (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
		{
			animator->Play(L"P_DodgeBackRight", false);
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;
		}
		else if ((Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN)) && (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
		{
			animator->Play(L"P_DodgeRight", false);
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;
		}
		else if ((Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN)) && (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
		{
			animator->Play(L"P_DodgeLeft", false);
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN))
		{
			animator->Play(L"P_DodgeFront", false);
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
		{
			animator->Play(L"P_DodgeBack", false);
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
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
		else if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
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

