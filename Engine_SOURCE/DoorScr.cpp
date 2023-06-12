#include "DoorScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
namespace ch
{
	DoorScr::DoorScr()
	{
	}

	DoorScr::~DoorScr()
	{
	}

	void DoorScr::Initalize()
	{



		tAnimator = GetOwner()->GetComponent<Animator>();
		if (GetOwner()->GetName() == L"DoorFront")
		{
			tAnimator->Play(L"D_empty");
			Collider2D* col = GetOwner()->AddComponent<Collider2D>();
			col->SetName(L"DoorCollider");
			col->SetType(eColliderType::Rect);
			col->SetSize(Vector2(0.3f, 0.2f));
			col->SetCenter(Vector2(0.f, -0.97f));
		}
		else if (GetOwner()->GetName() == L"DoorSide")
		{
			tAnimator->Play(L"D_empty");
			Collider2D* col = GetOwner()->AddComponent<Collider2D>();
			col->SetName(L"DoorCollider");
			col->SetType(eColliderType::Rect);
			col->SetSize(Vector2(0.05f, 0.3f));
			col->SetCenter(Vector2(0.f, -0.8f));
		}
		else
		{
			int a = 0;
		}
		door = dynamic_cast<DoorObj*>(GetOwner());

		doorKey = 0;

		oc = OpenClose::Defa;

		prevoc = OpenClose::Close;
		prevDoorState = false;
	}

	void DoorScr::Update()
	{
		//setState();

		switch (oc)
		{
		case OpenClose::Open:
			openDoor();
			break;
		case OpenClose::Close:
			closeDoor();
			break;
		case OpenClose::Defa:
			setState();
			break;
		default:
			break;
		}



	}

	void DoorScr::FixedUpdate()
	{
	}

	void DoorScr::Render()
	{
	}

	void DoorScr::OnCollisionEnter(Collider2D* oppo)
	{
	}

	void DoorScr::OnCollision(Collider2D* oppo)
	{
	}

	void DoorScr::OnCollisionExit(Collider2D* oppo)
	{
	}

	void DoorScr::openDoor()
	{
		if (GetOwner()->GetName() == L"DoorFront")
		{
			GetOwner()->SetLayerType(eLayerType::BackGround);
			tAnimator->Play(L"D_door_front_open", false);
		}
		else if (GetOwner()->GetName() == L"DoorSide")
		{
			GetOwner()->SetLayerType(eLayerType::BackGround);
			tAnimator->Play(L"D_door_side_open", false);
		}
		oc = OpenClose::Defa;
	}

	void DoorScr::closeDoor()
	{
		if (GetOwner()->GetName() == L"DoorFront")
		{

			tAnimator->Play(L"D_door_front_close", false);
			GetOwner()->SetLayerType(eLayerType::Wall);
		}
		else if (GetOwner()->GetName() == L"DoorSide")
		{

			tAnimator->Play(L"D_door_side_close", false);
			GetOwner()->SetLayerType(eLayerType::Wall);
		}
		oc = OpenClose::Defa;
	}

	void DoorScr::setState()
	{
		if (prevDoorState != door->GetisOpen()) 
		{
			prevDoorState = door->GetisOpen();
			if (door->GetisOpen() == true)
			{
				oc = OpenClose::Open;
			}
			else if (door->GetisOpen() == false)
			{
				oc = OpenClose::Close;
			}
		}
		
	}

}
