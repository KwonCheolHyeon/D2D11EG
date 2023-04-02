#include "chPlayerScr.h"
#include "chInput.h"
#include "chTransform.h"
#include "chTime.h"
#include "chAnimator.h"
#include "chGameObject.h"
#include "chRigidbody.h"


namespace ch 
{
	PlayerScr::PlayerScr()
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


		C2Mangle = 0.f;
		
	}
	PlayerScr::~PlayerScr()
	{
		
	}
	void PlayerScr::Initalize()
	{
		mousePositon = Vector3::Zero;
		transform = GetOwner()->GetComponent<Transform>();
		animator = GetOwner()->GetComponent<Animator>();
	}
	void PlayerScr::Update()
	{
		mousePos();//마우스 위치
		playerLookMouse();
		chCheckDirectionKey();
		if (mState[(UINT)ePlayerState::Dodge] == false && mState[(UINT)ePlayerState::Walking] == true &&mState[(UINT)ePlayerState::Idle] == false)
		{ //							걷기 함수
			chWalkAni();
			chWalking();
		}
		if (mState[(UINT)ePlayerState::Idle] == true && mState[(UINT)ePlayerState::Walking] == false && mState[(UINT)ePlayerState::Dodge] == false)
		{
			chIdleAni();
		}

	

	}
	void PlayerScr::FixedUpdate()
	{
	}
	void PlayerScr::Render()
	{
	}

	#pragma region 충돌
	void PlayerScr::OnCollisionEnter(Collider2D* oppo)
	{
	}
	void PlayerScr::OnCollision(Collider2D* oppo)
	{
	}
	void PlayerScr::OnCollisionExit(Collider2D* oppo)
	{
	}
	void PlayerScr::OnTriggerEnter(Collider2D* oppo)
	{
	}
	void PlayerScr::OnTrigger(Collider2D* oppo)
	{
	}
	void PlayerScr::OnTriggerExit(Collider2D* oppo)
	{
	}
	
#pragma endregion
	


	void PlayerScr::chWalking()
	{
		Vector3 pos = transform->GetPosition();
		Vector3 direction = Vector3::Zero;
		{//														움직임
			//					위
			if (Input::GetKey(eKeyCode::W))
			{
				direction += 3.5f * Vector3::Up * Time::DeltaTime();
			}
			//					아래
			if (Input::GetKey(eKeyCode::S))
			{
				direction += 3.5f * Vector3::Down * Time::DeltaTime();
			}
			//					왼쪽
			if (Input::GetKey(eKeyCode::A)) //뒤집어서 
			{
				direction += 3.5f * Vector3::Left * Time::DeltaTime();
			}
			//					오른쪽
			if (Input::GetKey(eKeyCode::D))
			{
				direction += 3.5f * Vector3::Right * Time::DeltaTime();
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

	void PlayerScr::mousePos()
	{
		Vector3 mousePos = Input::GetMousPosition();

		mousePositon = (mousePos / 100.f);

		CharterPosition = this->GetOwner()->GetComponent<Transform>()->GetPosition();//현재 문제 카메라가 이동하면 캐릭터 기준이기 때문에 다른 결과가 나옴 나중에 카메라가 따라가면 캐릭터가 아닌 카메라 기준으로 맞춰야함
		mousePositon += CharterPosition;
		float aaa = atan2(mousePositon.y - CharterPosition.y, mousePositon.x - CharterPosition.x);
		C2Mangle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360각
	}
	bool PlayerScr::chCheckDirectionKey()
	{
		if (Input::GetKey(eKeyCode::D) == true || Input::GetKey(eKeyCode::A) == true || Input::GetKey(eKeyCode::W) == true || Input::GetKey(eKeyCode::S) == true)
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
	void PlayerScr::chIdleAni()
	{
		if (mPrevState != mState)
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
		}
		
	}
	void PlayerScr::chWalkAni()
	{
		if (mPrevState != mState)
		{
			if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Right] == true)
			{
				animator->Play(L"P_WWalkingRight", true);
			}
			else if (mState[(UINT)ePlayerState::Front] == true && mState[(UINT)ePlayerState::Left] == true)
			{
				animator->Play(L"P_WWalkingRight", true);
			}
			else if (mState[(UINT)ePlayerState::Front] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
			{
				animator->Play(L"P_WWalkingFront", true);
			}
			else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Right] == true)
			{
				animator->Play(L"P_WWalkingBackRight", true);
			}
			else if (mState[(UINT)ePlayerState::Back] == true && mState[(UINT)ePlayerState::Left] == true)
			{
				animator->Play(L"P_WWalkingBackRight", true);
			}
			else if (mState[(UINT)ePlayerState::Back] == true && (mState[(UINT)ePlayerState::Left] == false && mState[(UINT)ePlayerState::Right] == false))
			{
				animator->Play(L"P_WWalkingBack", true);
			}
		}
	}

	void PlayerScr::chState()
	{
		if (Input::GetKeyDown(eKeyCode::W))
		{
			//walking애니메이션 실행
			chWalkAni();
			mState[(UINT)ePlayerState::Idle] = false;
			mState[(UINT)ePlayerState::Walking] = true;
		}
		if (Input::GetKeyUp(eKeyCode::W))
		{
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
			}
			else
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				chWalkAni();
				
			}
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			//walking애니메이션 실행
			chWalkAni();
			mState[(UINT)ePlayerState::Idle] = false;
			mState[(UINT)ePlayerState::Walking] = true;
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
			}
			else									//다른키가 눌려져 있는 상태
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				chWalkAni();
			}
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			//walking애니메이션 실행

			chWalkAni();
			mState[(UINT)ePlayerState::Idle] = false;
			mState[(UINT)ePlayerState::Walking] = true;
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
			}
			else									//다른키가 눌려져 있는 상태
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				chWalkAni();
			}
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			//walking애니메이션 실행
			chWalkAni();
			mState[(UINT)ePlayerState::Idle] = false;
			mState[(UINT)ePlayerState::Walking] = true;
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			if (chCheckDirectionKey() == false)		//다른키가 눌러져 있지 않은 상태라면
			{
				//idle로 변경
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
			}
			else									//다른키가 눌려져 있는 상태
			{
				//walking상태 유지 //다른 키가 눌려져 있으면 그 키로 변경 
				chWalkAni();
			}
		}
	}

	void PlayerScr::gunHandSide()
	{
		if (C2Mangle >= 90 && C2Mangle < 270) //총 위치 왼쪽 //왼쪽 보기
		{
			GetOwner()->SetLeft();
		}
		else  //총 위치 오른쪽 // 오른쪽 보기
		{
			GetOwner()->SetRight();
		}
	}
	void PlayerScr::playerLookMouse()
	{
		mPrevState = mState;
		if (C2Mangle >= 30 && C2Mangle < 60) //right back
		{
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;

		}
		else if (C2Mangle >= 60 && C2Mangle < 120) //back
		{
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (C2Mangle >= 120 && C2Mangle < 150) //left Back
		{
			mState[(UINT)ePlayerState::Front] = false;
			mState[(UINT)ePlayerState::Back] = true;
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if(C2Mangle>=150 && C2Mangle <225) //left
		{
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = true;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else if (C2Mangle >= 225 && C2Mangle < 315)//front
		{
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = false;
		}
		else //right
		{
			mState[(UINT)ePlayerState::Front] = true;
			mState[(UINT)ePlayerState::Back] = false;
			mState[(UINT)ePlayerState::Left] = false;
			mState[(UINT)ePlayerState::Right] = true;
		}
		gunHandSide();
	}
}