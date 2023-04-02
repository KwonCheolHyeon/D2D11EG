#include "chMouseCursorScript.h"
#include "chInput.h"
#include "chGameObject.h"

namespace ch 
{
	MouseCursorScript::MouseCursorScript()
		: Script(),
		mTrans(nullptr),
		mPos(),
		mRot()
	{
	}
	MouseCursorScript::~MouseCursorScript()
	{
	}
	void MouseCursorScript::Initalize()
	{
		mTrans = GetOwner()->GetComponent<Transform>();
	}
	void MouseCursorScript::Update()
	{
		mPos = Input::GetMousPosition();

		mTrans->SetPosition(mPos/100.f );
	}
	void MouseCursorScript::FixedUpdate()
	{
	}
	void MouseCursorScript::Render()
	{
	}
}