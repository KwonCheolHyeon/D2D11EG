#include "chCameraScript.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chInput.h"
#include "chTime.h"
#include "chCamera.h"

namespace ch
{
	CameraScript::CameraScript()
		: Script()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initalize()
	{
		mCameraObject = GetOwner()->GetComponent<Camera>();
		target = mCameraObject->GetTarget();
	}

	void CameraScript::Update()
	{
		
		if (target)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();//카메라 위치
			targetPos = target->GetComponent<Transform>()->GetPosition();
			//플레이어 위치
		
			tr->SetPosition(Vector3(targetPos.x, targetPos.y, pos.z));
		}
		else {
		
			Transform* tr = GetOwner()->GetComponent<Transform>();

			Vector3 pos = tr->GetPosition();

			if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
			{
				pos += 100.0f * tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
			{
				pos += 100.0f * -tr->Right() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
			{
				pos += 100.0f * tr->Foward() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
			{
				pos += 100.0f * -tr->Foward() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
			{
				pos += 100.0f * tr->Up() * Time::DeltaTime();
			}
			else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
			{
				pos += 100.0f * -tr->Up() * Time::DeltaTime();
			}
			tr->SetPosition(pos);
		}

	

		
	}
	void CameraScript::Render()
	{
	}
	
}