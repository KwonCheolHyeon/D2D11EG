#include "ItemBoxScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chInput.h"
#include "chObject.h"
#include "chFightSabreObject.h"
#include "chRigidbody.h"
#include "chTransform.h"
namespace ch 
{
	ItemBoxScr::ItemBoxScr()
	{
	}
	ItemBoxScr::~ItemBoxScr()
	{
	}
	void ItemBoxScr::Initalize()
	{
		bAnimator = GetOwner()->AddComponent<Animator>();
		{//front
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"itemBox", L"enterthe/object/itemBox/itemBox.png");
			bAnimator->Create(L"D_itemBox", texture, Vector2(0.0f, 0.0f), Vector2(29.0f, 26.0f), Vector2::Zero, 1, 0.1f);
		}
		{//front
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"itemBox_open", L"enterthe/object/itemBox/itemBox_open.png");
			bAnimator->Create(L"D_itemBox_open", texture, Vector2(0.0f, 0.0f), Vector2(29.0f, 26.0f), Vector2::Zero, 3, 0.1f);
		}

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

		Collider2D* col = GetOwner()->AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(0.1f, 0.1f));

		bAnimator->Play(L"D_itemBox", false);
		ibs = itemBoxState::CloseBox;
		oneOpen = false;
		p2bOn = false;
		p2bOnKey = false;
	}
	void ItemBoxScr::Update()
	{
		switch (ibs)
		{
		case itemBoxState::CloseBox:
			closeBox();
			break;
		case itemBoxState::OpenBox:
			openBox();
			break;
		default:
			break;
		}

		
	}
	void ItemBoxScr::FixedUpdate()
	{
	}
	void ItemBoxScr::Render()
	{
	}
	void ItemBoxScr::OnCollisionEnter(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			p2bOn = true;
		}

	}
	void ItemBoxScr::OnCollision(Collider2D* oppo)
	{
	

	}
	void ItemBoxScr::OnCollisionExit(Collider2D* oppo)
	{
		if (oppo->GetOwner()->GetName() == L"Player")
		{
			p2bOn = false;
		}
	}
	void ItemBoxScr::openBox()
	{
		if(oneOpen == false)
		{
			oneOpen = true;
			bAnimator->Play(L"D_itemBox_open",false);

			FightSabreObject* fightsa = object::Instantiate<FightSabreObject>(eLayerType::Object);
			fightsa->Initalize();
			Transform* tr = fightsa->GetComponent<Transform>();
			tr->SetScale(Vector3(5.f, 5.f, 0.1f));
			tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		} 


	}
	void ItemBoxScr::closeBox()
	{
		if (p2bOn == true) 
		{
			if (Input::GetKeyDown(eKeyCode::E))
			{
				ibs = itemBoxState::OpenBox;
			}
		
		}
		

	}
}