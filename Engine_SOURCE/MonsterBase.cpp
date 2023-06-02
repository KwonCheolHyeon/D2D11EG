#include "MonsterBase.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
namespace ch 
{
	MonsterBase::MonsterBase()
	{
		GameObject* monsterOBJ = dynamic_cast<GameObject*>(this);

	
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
	void MonsterBase::SetMonsterChaseCollider(chasePlayerOBJ* _a)
	{
		monsterChaseCollider  =_a;
	}
}