#include "chtestBulletscr.h"
#include "chTime.h"
#include "chGameObject.h"
#include "chPlayScene.h"
#include "chSceneManager.h"
#include "chGun.h"
#include "chScene.h"
#include "chTransform.h"
#include "chInput.h"
#include "chResources.h"
#include "chSpriteRenderer.h"


namespace ch
{
	testBulletscr::testBulletscr()
		: Script()
		, speed(0.0f)
		, bulletDirectionX(0.f)
		, bulletDirectionY(0.f)
		, bulletTime(0.0f)
	{
	}
	testBulletscr::~testBulletscr()
	{
	}
	void testBulletscr::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::Weapone);

		SpriteRenderer* render = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bulletMaterial = Resources::Find<Material>(L"W_BulletMaterial");
		render->SetMaterial(bulletMaterial);
		std::shared_ptr<Mesh> bulletMesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(bulletMesh);


		mState[(UINT)eBulletState::wait] = true; //대기 상태
		mState[(UINT)eBulletState::live] = true; // 쏘고 움직이는 상태
		mState[(UINT)eBulletState::Dead] = false;
	}
	void testBulletscr::Update()
	{
		if (mState[(UINT)eBulletState::wait] == false && mState[(UINT)eBulletState::Dead] == false && mState[(UINT)eBulletState::live] == true)
		{
			bulletTime += Time::DeltaTime();
			MoveBullet();
		}
		if (bulletTime >= 3.0f)
		{
			Reset();
		}
	}
	void testBulletscr::FixedUpdate()
	{
	}
	void testBulletscr::Render()
	{
	}
	void testBulletscr::OnCollisionEnter(Collider2D* collider)
	{
	}
	void testBulletscr::OnCollisionStay(Collider2D* collider)
	{
	}
	void testBulletscr::OnCollisionExit(Collider2D* collider)
	{
	}
	void testBulletscr::OnTriggerEnter(Collider2D* collider)
	{
	}
	void testBulletscr::OnTriggerStay(Collider2D* collider)
	{
	}
	void testBulletscr::OnTriggerExit(Collider2D* collider)
	{
	}
	void testBulletscr::shootingBullet(float Gunangle, Vector3 pos)
	{
		mTr = GetOwner()->GetComponent<Transform>();
		bulletDirectionX = cos(Gunangle * (XM_PI / 180.0f));
		bulletDirectionY = sin(Gunangle * (XM_PI / 180.0f));

		mTr->SetPosition(pos);

		mState[(UINT)eBulletState::wait] = false;
		mState[(UINT)eBulletState::live] = true;
		mState[(UINT)eBulletState::Dead] = false;
	}
	void testBulletscr::MoveBullet()
	{
		speed = 10.0f; // Bullet's movement speed
		float bulletDistance = speed * Time::DeltaTime();
		Vector3 bulletPos = mTr->GetPosition();

		// Update bullet position based on direction and distance
		bulletPos += Vector3(bulletDirectionX, bulletDirectionY, 0.0f) * bulletDistance;

		mTr->SetPosition(bulletPos);
	}
	void testBulletscr::Reset()
	{
		bulletTime = 0;
		speed = 0;
		bulletDirectionX = 0;
		bulletDirectionY = 0;
		mTr->SetPosition(Vector3(0.f, 0.f, 0.f));
		mTr->SetRotation(Vector3(0.f, 0.f, 0.f));
		mState[(UINT)eBulletState::Dead] = true;
		mState[(UINT)eBulletState::live] = false;
		mState[(UINT)eBulletState::wait] = true;
	}
	bool testBulletscr::isReset()
	{
		if (mState[(UINT)eBulletState::wait] == true && mState[(UINT)eBulletState::Dead] == true && mState[(UINT)eBulletState::live] == false)
		{
			return true;
			mState[(UINT)eBulletState::wait] = true;
			mState[(UINT)eBulletState::live] = true;
			mState[(UINT)eBulletState::Dead] = false;
		}
		else
		{
			return false;
		}
	}
}