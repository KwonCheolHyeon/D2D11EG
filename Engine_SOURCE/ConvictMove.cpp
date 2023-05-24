#include "ConvictMove.h"
#include "CharacterBase.h"
#include "Convict.h"
#include "chInput.h"
#include "chTime.h"
namespace ch
{
	bool ConvictMove::canDodge = true;

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
		pS = PlayerState::Idle;
		canDodge = true;
		isDodging = false;
		
	}
	void ConvictMove::Update()
	{
		
		chState();
		

		if (Input::GetKeyDown(eKeyCode::RBTN) && !isDodging)
		{
			pS = PlayerState::Rolling;
		}
		
		switch (pS)
		{
		case PlayerState::Idle:
			Idle();
			break;
		case PlayerState::Walk:
			Walking();
			break;
		case PlayerState::Rolling:
			Dodging();
			break;
		default:
			
			break;
		}
		
		afterDodging();

		
		
		
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

		// Up
		if (Input::GetKey(eKeyCode::W))
		{
			direction += Vector3::Up;
		}
		// Down
		if (Input::GetKey(eKeyCode::S))
		{
			direction += Vector3::Down;
		}
		// Left
		if (Input::GetKey(eKeyCode::A))
		{
			direction += Vector3::Left;
		}
		// Right
		if (Input::GetKey(eKeyCode::D))
		{
			direction += Vector3::Right;
		}

		// Normalize diagonal movement
		if (direction != Vector3::Zero && direction != Vector3::Up && direction != Vector3::Down &&
			direction != Vector3::Left && direction != Vector3::Right)
		{
			direction.Normalize();
		}

		pos += direction * 3.5f * Time::DeltaTime();
		pTr->SetPosition(pos);
	}

	void ConvictMove::Idle()
	{
		
	}

	void ConvictMove::afterWalking()
	{
		if (Input::GetKeyUp(eKeyCode::W))
		{
			pS = PlayerState::Idle;
		}
		//					아래
		if (Input::GetKeyUp(eKeyCode::S))
		{
			pS = PlayerState::Idle;
		}
		//					왼쪽
		if (Input::GetKeyUp(eKeyCode::A)) //뒤집어서 
		{
			pS = PlayerState::Idle;
		}
		//					오른쪽
		if (Input::GetKeyUp(eKeyCode::D))
		{
			pS = PlayerState::Idle;
		}

	}

	void ConvictMove::Dodging()
	{
		isDodging = true;
		canDodge = false;
		float power = 8000.f;

		if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			pRb->SetVelocity(Vector3(-2.f, 2.0f, 0.0f) * power); // 방향  * power
			pDD = PlayerDodgeDirections::NWDodge;
		}
		else if ((Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			pRb->SetVelocity(Vector3(2.f, 2.0f, 0.0f) * power); // 방향  * power
			pDD = PlayerDodgeDirections::NEDodge;
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D)))
		{
			pRb->SetVelocity(Vector3(2.f, -2.0f, 0.0f) * power); // 방향  * power
			pDD = PlayerDodgeDirections::EastDodge;
		}
		else if ((Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S)) && (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A)))
		{
			pRb->SetVelocity(Vector3(-2.f, -2.0f, 0.0f) * power);
			pDD = PlayerDodgeDirections::WestDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			pRb->SetVelocity(Vector3::Down * power);
			pDD = PlayerDodgeDirections::SouthDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W))
		{
			pRb->SetVelocity(Vector3::Up * power);
			pDD = PlayerDodgeDirections::NorthDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			pRb->SetVelocity(Vector3::Left * power);
			pDD = PlayerDodgeDirections::WestDodge;
		}
		else if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			pRb->SetVelocity(Vector3::Right * power);
			pDD = PlayerDodgeDirections::EastDodge;
		}
		
	}

	void ConvictMove::afterDodging()
	{
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBackRight") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeFront") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeBack") = std::bind(&ConvictMove::gotoNormal, this);
		GetOwner()->GetComponent<Animator>()->GetCompleteEvent(L"P_DodgeRight") = std::bind(&ConvictMove::gotoNormal, this);
	}

	void ConvictMove::gotoNormal()
	{
		isDodging = false; // Reset isDodging flag
		canDodge = true; // Enable dodging again
		if (CheckKeyDirection())
		{
			pS = PlayerState::Walk;
		}
		else
		{
			pS = PlayerState::Idle;
		}

		// Reset the rolling state
		isRolling = false;
	}

	bool ConvictMove::CheckKeyDirection()
	{
		if (Input::GetKey(eKeyCode::D) == true || Input::GetKey(eKeyCode::A) == true || Input::GetKey(eKeyCode::W) == true || Input::GetKey(eKeyCode::S) == true) 
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void ConvictMove::chState()
	{
		if (canDodge) 
		{
			bool isWalking = false;

			if (Input::GetKey(eKeyCode::W) || Input::GetKey(eKeyCode::A) ||
				Input::GetKey(eKeyCode::S) || Input::GetKey(eKeyCode::D))
			{
				isWalking = true;
			}

			if (isWalking)
			{
				pS = PlayerState::Walk;
			}
			else
			{
				pS = PlayerState::Idle;
			}
		}
		else 
		{
			pS = PlayerState::Default;
		}

		
	}

}