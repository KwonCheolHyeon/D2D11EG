#include "ConvictMove.h"
#include "CharacterBase.h"
#include "chInput.h"
#include "chTime.h"
namespace ch
{
	ConvictMove::ConvictMove()
	{
	}
	ConvictMove::~ConvictMove()
	{
	}
	void ConvictMove::Initalize()
	{
		pTr = GetOwner()->GetComponent<Transform>();
		pRb = GetOwner()->GetComponent<Rigidbody>();
		player = dynamic_cast<CharacterBase*>(this);
	}
	void ConvictMove::Update()
	{
		
		if (pS == 3) 
		{
			afterDodging();
		}
		else 
		{
			if (Input::GetKeyDown(eKeyCode::RBTN))
			{
				pS = PlayerState::Dodge;
				Dodging();
			}

			Walking();
		}
		
		
	}
	void ConvictMove::FixedUpdate()
	{
	}
	void ConvictMove::Render()
	{
	}

	void ConvictMove::Walking()
	{
		Vector3 pos = pTr->GetPosition();
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
			pTr->SetPosition(pos);
		}
	}

	void ConvictMove::Dodging()
	{
		float power = 200.f;

		if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			pRb->AddForce(Vector3(-1.f, 1.0f, 0.0f) * power); // 방향  * power
		}
		else if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			pRb->AddForce(Vector3(1.f, 1.0f, 0.0f) * power); // 방향  * power
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			pRb->AddForce(Vector3(1.f, -1.0f, 0.0f) * power); // 방향  * power
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			pRb->AddForce(Vector3(-1.f, -1.0f, 0.0f) * power);
		}
		else if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			pRb->AddForce(Vector3::Down * power);
		}
		else if (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W))
		{
			pRb->AddForce(Vector3::Up * power);
		}
		else if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			pRb->AddForce(Vector3::Left * power);
		}
		else if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			pRb->AddForce(Vector3::Right * power);
		}
	}

	void ConvictMove::afterDodging()
	{
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeLeft") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBackLeft") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeFront") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBack") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeLeft") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&ConvictMove::gotoNormal, this);
	}

	void ConvictMove::gotoNormal()
	{
		if (CheckKeyDirection() == true) 
		{
		
		}
		else 
		{

		}
	}

	bool ConvictMove::CheckKeyDirection()
	{
		if (Input::GetKey(eKeyCode::D) == true || Input::GetKey(eKeyCode::A) == true || Input::GetKey(eKeyCode::W) == true || Input::GetKey(eKeyCode::S) == true) 
		{
			pS = PlayerState::Walk;
			return true;
		}
		else
		{
			pS = PlayerState::Idle;
			return false;
		}
	}
	
}