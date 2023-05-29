#include "MonsterBase.h"

namespace ch 
{
	MonsterBase::MonsterBase()
	{

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
}