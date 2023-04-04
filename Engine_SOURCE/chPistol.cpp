#include "chPistol.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chInput.h"
namespace ch 
{
	Pistol::Pistol()
	{
		
	}

	Pistol::~Pistol()
	{
	}

	void Pistol::Initalize()
	{
		pistolOBJ = this;

		pistolPosition = pistolOBJ->GetComponent<Transform>();
		pistolPosition->SetScale(Vector3(0.28f, 0.23f, 1.0f));
		pistolPosition->SetRotation(Vector3(0.f, 0.f, 70.f));
		SpriteRenderer* sprite = pistolOBJ->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"W_pistol_Material");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
		GameObject::Initalize();
	}

	void Pistol::Update()
	{
		pistolSetPosition();
		GameObject::Update();
	}

	void Pistol::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Pistol::Render()
	{
		Gun::Render();
	}

	void Pistol::pistolSetPosition()
	{
		Vector3 handPosition = pHand->GetComponent<Transform>()->GetPosition();
		Vector3 mousePos = Input::GetMousPosition();
		Vector3 weaphonePosition = pistolPosition->GetPosition();
		Vector3 rota = pistolPosition->GetRotation();
		Vector3 characterPos = player->GetComponent<Transform>()->GetPosition();

		//float handDistance = 0.05f;

		Vector3 mouseRelative = (mousePos / 100.f);
		mouseRelative += characterPos;
		
		// Calculate the angle between the mouse cursor position and the character position
		float angle = atan2(mouseRelative.y - characterPos.y, mouseRelative.x - characterPos.x);
		// Set the rotation of the gun's hand
		float rotationZ = angle * (180.0f / XM_PI);
		
		//Vector3 handRelative(cos(angle) * handDistance, sin(angle) * handDistance, 0.f);

		if (pHand->isHandLeft()) //¿Þ¼Õ
		{
			pistolOBJ->SetLeft();
			weaphonePosition = handPosition + Vector3(-0.2f, 0.1f, 0.f);
			pistolPosition->SetRotation(Vector3(180.0f, 0.0f, rotationZ));
		}
		else //¿À¸¥¼Õ
		{
			pistolOBJ->SetRight();
			weaphonePosition = handPosition + Vector3(0.2f, 0.1f, 0.f);
			pistolPosition->SetRotation(Vector3(0.0f, 0.0f, rotationZ));
		}
		//if (player->GetHand() == false) 
		//{
		//	if (pHand->isHandLeft()) //¿Þ¼Õ
		//	{
		//		pistolOBJ->SetRight();
		//		weaphonePosition = handPosition + Vector3(-0.2f,  10.16f, 0.f);
		//		pistolPosition->SetRotation(Vector3(180.0f, 0.0f, rotationZ));
		//	}
		//	else //¿À¸¥¼Õ
		//	{
		//		pistolOBJ->SetLeft();
		//		weaphonePosition = handPosition + Vector3(0.2f, 10.16f, 0.f);
		//		pistolPosition->SetRotation(Vector3(0.0f, 0.0f, rotationZ));
		//	}
		//}
		//else 
		//{
		//	
		//}
		

		pistolPosition->SetPosition(weaphonePosition);
		
	}

}