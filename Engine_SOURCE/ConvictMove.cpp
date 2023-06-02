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
		isWall = false;
		wallPosition = Vector3::Zero;
		GetOwner()->setHand();
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
			GetOwner()->setNoHand();
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

	void ConvictMove::OnCollisionEnter(Collider2D* oppo)
	{

		if (oppo->GetOwner()->GetLayerType() == eLayerType::Wall || oppo->GetOwner()->GetName() == (L"MapWall"))
		{
			isWall = true;
			pRb->SetVelocity(Vector3::Zero);
		}

	}

	void ConvictMove::OnCollision(Collider2D* oppo)
	{
		
	}

	void ConvictMove::OnCollisionExit(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetLayerType() == eLayerType::Wall || oppo->GetOwner()->GetName() == (L"MapWall"))
		{
			isWall = false;

		}
	}

	void ConvictMove::OnTriggerEnter(Collider2D* oppo)
	{
	}

	void ConvictMove::OnTrigger(Collider2D* oppo)
	{
	}

	void ConvictMove::Walking()
	{
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

		float speed = 3.5f;
		Vector3 velocity = direction * speed;
		if (isWall == true) 
		{
			pRb->SetVelocity(-velocity);
		}
		else 
		{
		
			pRb->SetVelocity(velocity);
		}
		
	}

	void ConvictMove::Idle()
	{
		
	}

	void ConvictMove::OnTriggerExit(Collider2D* oppo)
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
		float power = 800.f;

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
			pRb->SetVelocity(Vector3(0.f, -2.0f, 0.0f) * power);
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
		GetOwner()->setHand();
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