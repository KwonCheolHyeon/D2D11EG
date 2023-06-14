#include "HeartScr.h"
#include "chGameObject.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chLight.h"
namespace ch 
{
	HeartScr::HeartScr()
	{

	}

	HeartScr::~HeartScr()
	{

	}

	void HeartScr::Initalize()
	{
		Light* lightComp = GetOwner()->AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(2.5f);
		lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));


		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"FullHeartMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);

		Transform* mTr = GetOwner()->GetComponent<Transform>();
		mTr->SetPosition(Vector3(-16.1f, -3.23f, -9.f));
		mTr->SetScale(Vector3(0.5f, 0.5f, 0.1f));
	}
	

	void HeartScr::Update()
	{
	}

	void HeartScr::FixedUpdate()
	{
	}

	void HeartScr::Render()
	{
	}

	void HeartScr::OnCollisionEnter(Collider2D* collider)
	{
	}

	void HeartScr::OnCollisionStay(Collider2D* collider)
	{
	}

	void HeartScr::OnCollisionExit(Collider2D* collider)
	{
	}

}