#include "chCameraScript.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chInput.h"
#include "chTime.h"

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
	}

	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos.x += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos.x -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos.z += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos.z -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			pos.y -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			pos.y += 3.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}
	void CameraScript::Render()
	{
	}
}