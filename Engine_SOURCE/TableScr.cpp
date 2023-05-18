#include "TableScr.h"
#include "TableObject.h"
#include "chInput.h"
namespace ch 
{
	TableScr::TableScr()
	{
	}

	TableScr::~TableScr()
	{

	}

	void TableScr::Initalize()
	{
		directionNumber = 0;
		tAnimator = this->GetOwner()->GetComponent<Animator>();
	}

	void TableScr::Update()
	{
		if (directionNumber != 0) 
		{
			if (Input::GetKeyDown(eKeyCode::E)) 
			{
				this->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(5.f, 4.f, 1.f));
				if (directionNumber == 1)
				{
					tAnimator->Play(L"T_table_front_Ani",false);
				}
				else if (directionNumber == 2) 
				{
					tAnimator->Play(L"T_table_left_Ani",false);
				}
				else if (directionNumber == 3)
				{
					tAnimator->Play(L"T_table_back_Ani",false);
				}
				else if (directionNumber == 4)
				{
					tAnimator->Play(L"T_table_right_Ani",false);
				}
			}
		}
		
	}

	void TableScr::FixedUpdate()
	{
	}

	void TableScr::Render()
	{
	}

	void TableScr::OnCollisionEnter(Collider2D* oppo)
	{
		if (GetClosestDirection(oppo) == 1) //상
		{
			directionNumber = 1;
		}
		else if (GetClosestDirection(oppo) == 2)
		{
			directionNumber = 2;
		}
		else if (GetClosestDirection(oppo) == 3)
		{
			directionNumber = 3;
		}
		else if (GetClosestDirection(oppo) == 4)
		{
			directionNumber = 4;
		}
	}

	void TableScr::OnCollision(Collider2D* oppo)
	{
		
		if (GetClosestDirection(oppo) == 1) //상
		{
			directionNumber = 1;
		}
		else if (GetClosestDirection(oppo) == 2)
		{
			directionNumber = 2;
		}
		else if (GetClosestDirection(oppo) == 3)
		{
			directionNumber = 3;
		}
		else if (GetClosestDirection(oppo) == 4)
		{
			directionNumber = 4;
		}
	}

	void TableScr::OnCollisionExit(Collider2D* oppo)
	{
		directionNumber = 0;
	}

	void TableScr::OnTriggerEnter(Collider2D* oppo)
	{
	}

	void TableScr::OnTrigger(Collider2D* oppo)
	{
		if (GetClosestDirection(oppo) == 1) //상
		{
			directionNumber = 1;
		}
		else if (GetClosestDirection(oppo) == 2)
		{
			directionNumber = 2;
		}
		else if (GetClosestDirection(oppo) == 3)
		{
			directionNumber = 3;
		}
		else if (GetClosestDirection(oppo) == 4)
		{
			directionNumber = 4;
		}
	}

	void TableScr::OnTriggerExit(Collider2D* oppo)
	{
		directionNumber = 0;
	}

	int TableScr::GetClosestDirection(Collider2D* collider)
	{
		// Get the positions of the two colliders
		Vector3 playerPosition = collider->GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 objectPosition = this->GetOwner()->GetComponent<Transform>()->GetPosition();

		// Calculate the differences in x and y coordinates
		float dx = objectPosition.x - playerPosition.x;
		float dy = objectPosition.y - playerPosition.y;

		// Calculate the absolute differences
		float absDX = std::abs(dx);
		float absDY = std::abs(dy);

		// Determine the closest direction based on the differences
		if (absDX > absDY)
		{
			// Horizontal direction is closer
			if (dx > 0)
				return 4; // 우
			else
				return 2; // 좌
		}
		else
		{
			// Vertical direction is closer
			if (dy > 0)
				return 3; //상
			else
				return 1; //하
		}
	}

}