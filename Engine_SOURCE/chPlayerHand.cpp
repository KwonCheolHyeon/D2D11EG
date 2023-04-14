#include "chPlayerHand.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
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




		//Vector3 mPos = Input::GetMousPosition();
		//Vector3 characterPosition = player->GetComponent<Transform>()->GetPosition();

		//Vector3 mousePosition = (mPos / 100.f );
		//mousePosition += characterPosition;
		//Vector3 handPosition = phandTr->GetPosition();

		//// calculate the angle between the mouse position and the character position
		//float angle = atan2(mousePosition.y - characterPosition.y, mousePosition.x - characterPosition.x);

		//// set the hand position
		//Vector3 handRelative(cos(angle) * handDistance, sin(angle) * handDistance, 0.f);
		//handPosition = characterPosition + handRelative;
		//phandTr->SetPosition(handPosition);

		//// set the hand rotation
		//float rotationZ = angle * (180.0f / XM_PI);
		//phandTr->SetRotation(Vector3(0.0f, 0.0f, rotationZ));