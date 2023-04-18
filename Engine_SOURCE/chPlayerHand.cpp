#include "chPlayerHand.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chGun.h"
#include "chPlayerScr.h"
#include "chTime.h"
#include "chInput.h"


namespace ch 
{
	PlayerHand::PlayerHand()
	{
		handDistance = 0.f;
	}
	PlayerHand::~PlayerHand()
	{
	}
	void PlayerHand::Initalize()
	{
		GameObject* phand = this;

		phandTr = phand->GetComponent<Transform>();
		phandTr->SetScale(Vector3(0.1f, 0.1f, 1.0f));
		
		SpriteRenderer* sprite = phand->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pHandMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
		
		GameObject::Initalize();
	}
	void PlayerHand::Update()
	{
		HandLookCursor();
		if (Gun::reboundTrue == true) 
		{
			int a = 0;
		}
		else if(Gun::reboundTrue == false)
		{
			
		}
		HandPosition();
		GameObject::Update();
	}
	void PlayerHand::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void PlayerHand::Render()
	{
		GameObject::Render();
	}
	void PlayerHand::HandLookCursor()
	{
		Vector3 mousePos = Input::GetMousPosition();
		Vector3 handPosition = phandTr->GetPosition();
		Vector3 characterPos = player->GetComponent<Transform>()->GetPosition();

		Vector3 mouseRelative = (mousePos / 100.f) + characterPos;
		//mouseRelative += characterPos;
		float angle = atan2(mouseRelative.y - characterPos.y, mouseRelative.x - characterPos.x);
		// Set the rotation of the gun's hand
		float rotationZ = angle * (180.0f / XM_PI);

		phandTr->SetRotation(Vector3(180.0f, 0.0f, rotationZ));

	}


	void PlayerHand::HandPosition()
	{
		Vector3 characterPosition = player->GetComponent<Transform>()->GetPosition();
		Vector3 handPosition = phandTr->GetPosition();
		if (player->GetHand()) 
		{
			if (player->isLeft() == true)
			{
				handPosition = characterPosition + Vector3(-0.13f, -0.16f, 0.f);
				chHandLeft = true;
			}
			else
			{
				handPosition = characterPosition + Vector3(0.13f, -0.16f, 0.f);
				chHandLeft = false;
			}
		}
		else 
		{
			if (player->isLeft() == true)
			{
				handPosition = characterPosition + Vector3(-0.13f, -10.16f, 0.f);
				chHandLeft = true;
			}
			else
			{
				handPosition = characterPosition + Vector3(0.13f, -10.16f, 0.f);
				chHandLeft = false;
			}
		}
		
		phandTr->SetPosition(handPosition);
		
	}
}
