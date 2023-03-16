#include "chPlayer.h"
#include "chPlayerScript.h"
#include "chSpriteRenderer.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chMesh.h"
#include "chTransform.h"
#include "chInput.h"
#include "chTime.h"
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
