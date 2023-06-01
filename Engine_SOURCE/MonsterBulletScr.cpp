#include "MonsterBulletScr.h"
#include "chScene.h"
#include "chSceneManager.h"
#include "chLight.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chTime.h"
namespace ch 
{
	MonsterBulletScr::MonsterBulletScr()
	{
	}

	MonsterBulletScr::~MonsterBulletScr()
	{
	}

	void MonsterBulletScr::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::MonsterBullet);


		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(0.3f,0.3f,1.f));

		Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

		Collider2D* bulletColl = GetOwner()->AddComponent<Collider2D>();
		bulletColl->SetType(eColliderType::Rect);
		bulletColl->SetCenter(Vector2(0.0f, 0.0f));
		bulletColl->SetSize(Vector2(0.1f, 0.1f));

		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"Enemy_Bullet_material");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);

	}

	void MonsterBulletScr::Update()
	{
		
		bulletTime += Time::DeltaTime();
		MoveBullet();
		if (bulletTime >= 1.5f)
		{
			Reset();
		}
	}

	void MonsterBulletScr::FixedUpdate()
	{
	}

	void MonsterBulletScr::Render()
	{
	}

	void MonsterBulletScr::OnCollisionEnter(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::OnCollision(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::OnCollisionExit(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::OnTriggerEnter(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::OnTrigger(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::OnTriggerExit(Collider2D* oppo)
	{
	}

	void MonsterBulletScr::shootingBullet(float Gunangle, Vector3 pos)
	{
		Transform* mTr = GetOwner()->GetComponent<Transform>();
		bulletDirectionX = cos(Gunangle * (XM_PI / 180.0f));
		bulletDirectionY = sin(Gunangle * (XM_PI / 180.0f));

		mTr->SetPosition(pos);
	}

	void MonsterBulletScr::MoveBullet()
	{
		float speed = 10.0f; // Bullet's movement speed
		float bulletDistance = speed * Time::DeltaTime();
		Vector3 bulletPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		// Update bullet position based on direction and distance
		bulletPos += Vector3(bulletDirectionX, bulletDirectionY, 0.0f) * bulletDistance;

		GetOwner()->GetComponent<Transform>()->SetPosition(bulletPos);
	}
	void MonsterBulletScr::Reset()
	{
		GetOwner()->Death();
	}
}