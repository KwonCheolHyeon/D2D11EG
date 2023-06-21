#include "ReloadButtonScr.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "chGameObject.h"
namespace ch 
{



	ReloadButtonScr::ReloadButtonScr()
	{
	}

	ReloadButtonScr::~ReloadButtonScr()
	{
	}

	void ReloadButtonScr::Initalize()
	{
		SpriteRenderer* sprite = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"ReloadButtonMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);
	}

	void ReloadButtonScr::Update()
	{
	}

	void ReloadButtonScr::FixedUpdate()
	{
	}

	void ReloadButtonScr::Render()
	{
	}

}