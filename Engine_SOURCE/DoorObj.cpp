#include "DoorObj.h"
#include "DoorScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
namespace ch 
{
	bool DoorObj::isOpen = true;
	
	DoorObj::DoorObj()
	{
		SetLayerType(eLayerType::Wall);
		
		GameObject* DoorOBJ = dynamic_cast<GameObject*>(this);

		tAnimator = DoorOBJ->AddComponent<Animator>();
		{//front
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_front_close", L"enterthe/object/door/front_close.png");
			tAnimator->Create(L"D_door_front_close", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 112.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_front_open", L"enterthe/object/door/front_open.png");
			tAnimator->Create(L"D_door_front_open", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 112.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_front_default", L"enterthe/object/door/front_default.png");
			tAnimator->Create(L"D_door_front_default", texture, Vector2(0.0f, 0.0f), Vector2(34.0f, 112.0f), Vector2::Zero, 1, 0.1f);
		}


		{//side
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_side_close", L"enterthe/object/door/side_close.png");
			tAnimator->Create(L"D_door_side_close", texture, Vector2(0.0f, 0.0f), Vector2(8.0f, 102.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_side_open", L"enterthe/object/door/side_open.png");
			tAnimator->Create(L"D_door_side_open", texture, Vector2(0.0f, 0.0f), Vector2(8.0f, 102.0f), Vector2::Zero, 3, 0.1f);
		}
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"door_side_default", L"enterthe/object/door/side_default.png");
			tAnimator->Create(L"D_door_side_default", texture, Vector2(0.0f, 0.0f), Vector2(8.0f, 102.0f), Vector2::Zero, 1, 0.1f);
		}

		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"empty", L"empty.png");
			tAnimator->Create(L"D_empty", texture, Vector2(0.0f, 0.0f), Vector2(12.0f, 102.0f), Vector2::Zero, 1, 0.1f);
		}

		tAnimator->Play(L"D_empty");

		SpriteRenderer* sprite = DoorOBJ->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);


		isOpen = true;
		mainDoor = false;
		endRoom = false;
		endRoomKey = 0;
		deathCol = false;
		monsterBases.clear();
	}
	
	DoorObj::~DoorObj()
	{
	


	}
	void DoorObj::Initalize()
	{
		GameObject::Initalize();
	}
	void DoorObj::Update()
	{
		if (endRoom == true && endRoomKey == 1)
		{
			endRoomKey += 1;
			isOpen = true;
			
			deathCol = true;
		}

		if (!monsterBases.empty())
		{
			int numMonsters = monsterBases.size();

			bool allMonstersDead = false;
			
			switch (numMonsters)
			{
			case 1:
				if (monsterBases[0]->IsDead() == true) 
				{
					allMonstersDead = true;
				}
				break;
			case 2:
				if (monsterBases[0]->IsDead() == true && monsterBases[1]->IsDead() == true)
				{
					allMonstersDead = true;
				}
				break;
			case 3:
				if (monsterBases[0]->IsDead() == true && monsterBases[1]->IsDead() == true && monsterBases[2]->IsDead() == true)
				{
					allMonstersDead = true;
				}
				break;
			case 4:
				if (monsterBases[0]->IsDead() == true && monsterBases[1]->IsDead() == true && monsterBases[2]->IsDead() == true && monsterBases[3]->IsDead() == true)
				{
					allMonstersDead = true;
				}
				break;
			default:
				break;
			}


			if (allMonstersDead)
			{
				endRoom = true;
				endRoomKey += 1;
			}

		}


		GameObject::Update();
	}
	void DoorObj::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void DoorObj::Render()
	{
		GameObject::Render();
	}
}