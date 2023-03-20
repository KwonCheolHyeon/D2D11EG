#pragma once
#include "chScript.h"

namespace ch 
{
	class MouseCursorScript : public Script
	{
	public :
		MouseCursorScript();
		virtual ~MouseCursorScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


	private:
		Transform* mTrans;
		Vector3 mPos;
		Vector3 mRot;

	};


}

