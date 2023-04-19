#include "chHeart_UI.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chInput.h"

namespace ch 
{
	Heart_UI::Heart_UI()
	{

	}
	Heart_UI::~Heart_UI()
	{

	}
	void Heart_UI::Initalize()
	{
		heartObject = this;
		countHeart = 2;
		prevHeartCount = 0;

		SpriteRenderer* sprite = heartObject->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"FullHeartSprite");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMaterial(mateiral);
		sprite->SetMesh(mesh);

		GameObject::Initalize();
	}
	void Heart_UI::Update()
	{

	/*	if (prevHeartCount != countHeart) 
		{
			if (countHeart == 0)
			{
				prevHeartCount = countHeart;
				SpriteRenderer* sprite = heartObject->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"NoHeartSprite");
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				sprite->SetMaterial(mateiral);
				sprite->SetMesh(mesh);
			}
			else if (countHeart == 1)
			{
				prevHeartCount = countHeart;
				SpriteRenderer* sprite = heartObject->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"HalfHeartSprite");
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				sprite->SetMaterial(mateiral);
				sprite->SetMesh(mesh);
			}
			else if (countHeart == 2)
			{
				prevHeartCount = countHeart;
				SpriteRenderer* sprite = heartObject->GetComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"FullHeartSprite");
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				sprite->SetMaterial(mateiral);
				sprite->SetMesh(mesh);
			}
		}*/

	


		if (Input::GetKeyDown(eKeyCode::Z))
		{
			countHeart = 0;
		}
		if (Input::GetKeyDown(eKeyCode::X)) 
		{
			countHeart = 1;
		}
		
		GameObject::Update();
	}
	void Heart_UI::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}
	void Heart_UI::Render()
	{


		GameObject::Render();
	}
}