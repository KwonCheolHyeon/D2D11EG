#include "chSpriteRenderer.h"
#include "chGameObject.h"
#include "chTransform.h"
#include "chAnimator.h"
namespace ch
{
	SpriteRenderer::SpriteRenderer()
		: BaseRenderer(eComponentType::SpriteRenderer)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initalize()
	{
		
	}

	void SpriteRenderer::Update()
	{
		
	}

	void SpriteRenderer::FixedUpdate()
	{
		
	}

	void SpriteRenderer::Render()
	{
		if (GetOwner() == nullptr) 
		{
			return;
			

		}
		if(GetOwner()->GetState() != GameObject::eState::Active )
		{
			return;
		
		}
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMesh()->BindBuffer();
		GetMaterial()->Bind();

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
		{
			animator->Binds();
		}

		GetMesh()->Render();
		GetMaterial()->Clear();

		if (animator)
		{
			animator->Clear();
		}
	}

}
