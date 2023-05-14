#include "CharacterBase.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chCollider2D.h"
#include "chRigidbody.h"
#include "chInput.h"
#include "Convict.h"
#include "ConvictMove.h"

namespace ch 
{
	CharacterBase::CharacterBase()
	{
		SetLayerType(eLayerType::Player);

		GameObject* playerOBJ = dynamic_cast<CharacterBase*>(this);
			
		SpriteRenderer* sprite = playerOBJ->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		Transform* pTr = playerOBJ->GetComponent<Transform>();
		pTr->SetScale(Vector3(5.3f, 5.6f, 0.0f));
		pTr->SetPosition(Vector3(2.f, 1.f, 0.f));

		pAnima = playerOBJ->AddComponent<Animator>();
		playerOBJ->AddComponent<Collider2D>();
		playerOBJ->AddComponent<Rigidbody>();
		
		reset();

	}

	CharacterBase::~CharacterBase()
	{

	}

	void CharacterBase::Initalize()
	{
		GameObject::Initalize();
	}

	void CharacterBase::Update()
	{
		 


		GameObject::Update();
	}

	void CharacterBase::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void CharacterBase::Render()
	{
		GameObject::Render();
	}

	void CharacterBase::MouseAndPlayerAngle()
	{
		Vector3 mousePos = Input::GetMousPosition();

		Vector3 mousePositon = (mousePos / 100.f);

		Vector3 CharterPosition = GetCenterPos();
		mousePositon += CharterPosition;//���콺 ��ġ�� ȭ�鿡 �����Ǿ� �����Ƿ� ĳ���Ͱ� �̵��� ��ġ ��ŭ ������
		float aaa = atan2(mousePositon.y - CharterPosition.y, mousePositon.x - CharterPosition.x);
		c2mAngle = fmodf((aaa * (180.0f / XM_PI) + 360.0f), 360.0f);// C2Mangle 360��
	}
	void CharacterBase::playerLookingMouse()
	{
		
		if (c2mAngle >= 30 && c2mAngle < 60) //right back
		{
			pD = PlayerDirections::NE;
		}
		else if (c2mAngle >= 60 && c2mAngle < 120) //back
		{
			pD = PlayerDirections::North;
		}
		else if (c2mAngle >= 120 && c2mAngle < 150) //left Back
		{
			pD = PlayerDirections::NW;
		}
		else if (c2mAngle >= 150 && c2mAngle < 225) //left
		{
			pD = PlayerDirections::West;
		}
		else if (c2mAngle >= 225 && c2mAngle < 315)//front
		{
			pD = PlayerDirections::South;
		}
		else //right
		{
			pD = PlayerDirections::East;
		}

	}
	void CharacterBase::reset()
	{
		pD = PlayerDirections::South; //����
	}
}