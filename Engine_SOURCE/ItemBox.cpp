#include "ItemBox.h"
#include "ItemBoxScr.h"
namespace ch 
{
	ItemBox::ItemBox()
	{
	}

	ItemBox::~ItemBox()
	{
	}

	void ItemBox::Initalize()
	{
		this->AddComponent<ItemBoxScr>();
		GameObject::Initalize();
	}

	void ItemBox::Update()
	{
		GameObject::Update();
	}

	void ItemBox::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void ItemBox::Render()
	{
		GameObject::Render();
	}

}