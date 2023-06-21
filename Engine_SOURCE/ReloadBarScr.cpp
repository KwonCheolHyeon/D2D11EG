#include "ReloadBarScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chGameObject.h"
namespace ch 
{



	ReloadBarScr::ReloadBarScr()
	{
	}

	ReloadBarScr::~ReloadBarScr()
	{
	}

	void ReloadBarScr::Initalize()
	{

		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"ReloadBarMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
	}

	void ReloadBarScr::Update()
	{
	}

	void ReloadBarScr::FixedUpdate()
	{
	}

	void ReloadBarScr::Render()
	{
	}

}