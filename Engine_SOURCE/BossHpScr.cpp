#include "BossHpScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"


namespace ch
{
	BossHpScr::BossHpScr()
	{
	}
	BossHpScr::~BossHpScr()
	{
	}
	void BossHpScr::Initalize()
	{
		ani = GetOwner()->AddComponent<Animator>();

		{//
			hpTexture = Resources::Load<Texture>(L"bossHpAni", L"enterthe/UI/BossHp/bossHpAni.png");
			ani->Create(L"B_bossHpAni", hpTexture, Vector2(0.0f, 0.0f), Vector2(166.0f, 8.0f), Vector2::Zero, 2, 0.1f);
		}
		
		
	

	}
	void BossHpScr::Update()
	{


	}
	void BossHpScr::FixedUpdate()
	{
	}
	void BossHpScr::Render()
	{
	}
}