#include "chBaseRenderer.h"
#include "chTexture.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chResources.h"

namespace ch
{
	BaseRenderer::BaseRenderer(eComponentType type)
		: Component(type)
		, mbIsChanged(false)
		, mbIsAnim(false)
		, mSpriteSize(Vector2::Zero)
	{
		// 디폴트 매시 지정
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"Rectmesh");

		SetMesh(mesh);
	}

	BaseRenderer::~BaseRenderer()
	{
	}

	void BaseRenderer::Initalize()
	{
	}

	void BaseRenderer::Update()
	{
	}

	void BaseRenderer::FixedUpdate()
	{
		if (mbIsChanged)
		{
			Transform* transform = GetOwner()->GetComponent<Transform>();

			Vector3 scale = transform->GetScale();
			Vector3 scaleTemp = transform->GetScale();

			scale.x = mWidthRatio;
			scale.y = mHeightRatio;

			scale *= scaleTemp;

			transform->SetScale(scale);

			mbIsChanged = false;
		}
	}

	void BaseRenderer::Render()
	{
	}
	

	
}
