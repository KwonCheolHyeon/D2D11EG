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

	}
	void CameraScript::Render()
	{
	}
	
}