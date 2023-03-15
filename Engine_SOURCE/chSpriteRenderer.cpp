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
		BaseRenderer::Initalize();
	}

	void SpriteRenderer::Update()
	{
		BaseRenderer::Update();
	}

	void SpriteRenderer::FixedUpdate()
	{
		BaseRenderer::FixedUpdate();
	}

	void SpriteRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->Bind();

		GetMesh()->BindBuffer();

		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (animator)
			animator->Binds();


		GetMesh()->Render();

		GetMaterial()->Clear();

		if (animator)
			animator->Clear();

		//BaseRenderer::Render();
	}

}
