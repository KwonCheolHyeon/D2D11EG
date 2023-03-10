#include "mainPlayer.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chInput.h"
#include "chTime.h"
#include "chFadeEffect.h"
#include "chMeshRenderer.h"
#include "chMaterial.h"
#include "chMesh.h"
#include "chResources.h"
#include "chPlayerScript.h"
#include "chTransform.h"


namespace ch
{
	mainPlayer::mainPlayer()
		: Script()
	{
	}

	mainPlayer::~mainPlayer()
	{
	}

	void mainPlayer::Initialize()
	{
	
	}

	void mainPlayer::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		
		

		if (Input::GetKey(eKeyCode::RIGHT))
		{
		
			Vector3 pos = tr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			Vector3 pos = tr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			pos.y -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos.y += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

	
	}

	void mainPlayer::Render()
	{
	}

	void mainPlayer::OnCollisionEnter(Collider2D* collider)
	{
	}

	void mainPlayer::OnCollisionStay(Collider2D* collider)
	{
	}

	void mainPlayer::OnCollisionExit(Collider2D* collider)
	{
	}

}