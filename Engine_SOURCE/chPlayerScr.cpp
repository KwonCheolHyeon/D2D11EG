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
		mousePos();//���콺 ��ġ
		playerLookMouse();
		chCheckDirectionKey();
		if (mState[(UINT)ePlayerState::Dodge] == false && mState[(UINT)ePlayerState::Walking] == true &&mState[(UINT)ePlayerState::Idle] == false)
		{ //							�ȱ� �Լ�
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

	#pragma region �浹
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
		{//														������
			//					��
			if (Input::GetKey(eKeyCode::W))
			{
				direction += 3.5f * Vector3::Up * Time::DeltaTime();
			}
			//					�Ʒ�
			if (Input::GetKey(eKeyCode::S))
			{
				direction += 3.5f * Vector3::Down * Time::DeltaTime();
			}
			//					����
			if (Input::GetKey(eKeyCode::A)) //����� 
			{
				direction += 3.5f * Vector3::Left * Time::DeltaTime();
			}
			//					������
			if (Input::GetKey(eKeyCode::D))
			{
				direction += 3.5f * Vector3::Right * Time::DeltaTime();
			}
			//			�밢�� ���� �����϶�
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

		CharterPosition = this->GetOwner()->GetComponent<Transform>()->GetPosition();//���� ���� ī�޶� �̵��ϸ� ĳ���� �����̱� ������ �ٸ� ����� ���� ���߿� ī�޶� ���󰡸� ĳ���Ͱ� �ƴ� ī�޶� �������� �������
		mousePositon += CharterPosition;
		float aaa = atan2(mousePositon.y - CharterPosition.y, mousePositon.x - CharterPosition.x);
		C2Mangle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360��
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
			//walking�ִϸ��̼� ����
			chWalkAni();
			mState[(UINT)ePlayerState::Idle] = false;
			mState[(UINT)ePlayerState::Walking] = true;
		}
		if (Input::GetKeyUp(eKeyCode::W))
		{
			if (chCheckDirectionKey() == false)		//�ٸ�Ű�� ������ ���� ���� ���¶��
			{
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
			}
			else
			{
				//walking���� ���� //�ٸ� Ű�� ������ ������ �� Ű�� ���� 
				chWalkAni();
				
			}
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			//walking�ִϸ��̼� ����
			chWalkAni();
			mState[(UINT)ePlayerState::Idle] = false;
			mState[(UINT)ePlayerState::Walking] = true;
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			if (chCheckDirectionKey() == false)		//�ٸ�Ű�� ������ ���� ���� ���¶��
			{
				//idle�� ����
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
			}
			else									//�ٸ�Ű�� ������ �ִ� ����
			{
				//walking���� ���� //�ٸ� Ű�� ������ ������ �� Ű�� ���� 
				chWalkAni();
			}
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			//walking�ִϸ��̼� ����

			chWalkAni();
			mState[(UINT)ePlayerState::Idle] = false;
			mState[(UINT)ePlayerState::Walking] = true;
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			if (chCheckDirectionKey() == false)		//�ٸ�Ű�� ������ ���� ���� ���¶��
			{
				//idle�� ����
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
			}
			else									//�ٸ�Ű�� ������ �ִ� ����
			{
				//walking���� ���� //�ٸ� Ű�� ������ ������ �� Ű�� ���� 
				chWalkAni();
			}
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			//walking�ִϸ��̼� ����
			chWalkAni();
			mState[(UINT)ePlayerState::Idle] = false;
			mState[(UINT)ePlayerState::Walking] = true;
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			if (chCheckDirectionKey() == false)		//�ٸ�Ű�� ������ ���� ���� ���¶��
			{
				//idle�� ����
				mState[(UINT)ePlayerState::Idle] = true;
				mState[(UINT)ePlayerState::Walking] = false;
			}
			else									//�ٸ�Ű�� ������ �ִ� ����
			{
				//walking���� ���� //�ٸ� Ű�� ������ ������ �� Ű�� ���� 
				chWalkAni();
			}
		}
	}

	void PlayerScr::gunHandSide()
	{
		if (C2Mangle >= 90 && C2Mangle < 270) //�� ��ġ ���� //���� ����
		{
			GetOwner()->SetLeft();
		}
		else  //�� ��ġ ������ // ������ ����
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