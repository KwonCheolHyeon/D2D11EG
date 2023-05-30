#include "MonsterBase.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
namespace ch 
{
	MonsterBase::MonsterBase()
	{
		GameObject* monsterOBJ = dynamic_cast<GameObject*>(this);

		SpriteRenderer* sprite = monsterOBJ->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"pIdleMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);

	}
	MonsterBase::~MonsterBase()
	{
	}
	void MonsterBase::Initalize()
	{
		GameObject::Initalize();
	}
	void MonsterBase::Update()
	{
		GameObject::Update();
	}
	void MonsterBase::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void MonsterBase::Render()
	{
		GameObject::Render();
	}
	void MonsterBase::SetMonsterChaseCollider(GameObject* _a)
	{
		monsterChaseCollider  =_a;
	}
}