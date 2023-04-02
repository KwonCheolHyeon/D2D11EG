#pragma once
#include "chScript.h"

namespace ch
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		
	private:
		Camera* mCameraObject;
		GameObject* target;
		Vector3 targetPos;
	
	};
}
