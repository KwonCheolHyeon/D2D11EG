#include "BossSceneScr.h"
#include "EventScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chTime.h"
namespace ch 
{
	BossSceneScr::BossSceneScr()
	{
	}

	BossSceneScr::~BossSceneScr()
	{
	}

	void BossSceneScr::Initalize()
	{
		ani = GetOwner()->AddComponent<Animator>();
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bossScene", L"enterthe/BossScene/bossScene.png");
			ani->Create(L"boss_Scene", texture, Vector2(0.0f, 0.0f), Vector2(427.0f, 240.0f), Vector2::Zero, 32, 0.2f);
		}
	}

	void BossSceneScr::Update()
	{
		if (eventObj->GetComponent<EventScr>()->GetEventState() == true)
		{
			timer += Time::DeltaTime();
			if (ani->IsAnimationRunning(L"boss_Scene") == false) {
				ani->Play(L"boss_Scene", false);
			}
			if (timer >= 6.45) 
			{
				GetOwner()->Death();
			}
		}
	}

	void BossSceneScr::FixedUpdate()
	{
	}

	void BossSceneScr::Render()
	{
	}

	

}
