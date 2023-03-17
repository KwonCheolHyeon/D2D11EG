#include "chPlayer.h"


namespace ch
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	void Player::Initalize()
	{
		GameObject::Initalize();
	}

	void Player::Update()
	{
		GameObject::Update();
		//head->update();
		//body->update();

	}

	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}
