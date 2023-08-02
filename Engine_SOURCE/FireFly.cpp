#include "FireFly.h"
#include "chGameObject.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chTime.h"
#include "chInput.h"
#include <cmath>
namespace ch
{
	FireFly::FireFly()
		: tr(nullptr)
		, timer(0.f)
		, brightness(0.f)
		, increasing(true)
	{
	}
	FireFly::~FireFly()
	{
	}
	void FireFly::Initalize()
	{

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"BrightenEffectMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMaterial(mateiral);
		sprite->SetMesh(mesh);

		tr = GetOwner()->GetComponent<Transform>();

	}
	void FireFly::Update()
	{

		Vector3 mousePos = Input::GetWorldMousPosition();

		
		tr->SetPosition(mousePos);
		
		
		const float duration = 1.0f;
		if (increasing)
		{
			timer += Time::DeltaTime();
			if (timer >= duration)
			{
				timer = duration;
				increasing = false;
			}
		}
		else
		{
			timer -= Time::DeltaTime();
			if (timer <= 0.0f)
			{
				timer = 0.0f;
				increasing = true;
			}
		}

		// Normalize the timer value to get the brightness between 0 and 10
		brightness = timer / duration;

	}
	void FireFly::FixedUpdate()
	{
	}
	void FireFly::Render()
	{
		renderer::BrightEffectCB brightcb = {};
		float bright = brightness;
		brightcb.brightnessCB1 = bright;
		brightcb.brightnessCB2 = 0;
		brightcb.brightnessCB3 = 0;
		brightcb.brightnessCB4 = 0;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::BrightenEffect];
		cb->SetData(&brightcb);
		cb->Bind(eShaderStage::ALL);

	}
}

