#include "chRigidbody.h"
#include "chGameObject.h"
#include "chTime.h"
namespace ch 
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		,mForce(Vector3::Zero)
		,mAccelation(Vector3::Zero)
		,mVelocity(Vector3::Zero)
		, mFriction(20.0f)
	{
		mLimitVelocity = 5.0f;
		mbGround = true;
		mGravity = Vector3(0.0f, 0.0f,0.0f);
		
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initalize()
	{
	}

	void Rigidbody::Update()
	{
		{
			//mAccelation = mForce / mMass;
			//mVelocity += mAccelation * Time::DeltaTime();

			//if (mbGround)
			//{
			//	// 땅위에 있을때
			//	Vector3 gravity = mGravity;
			//	gravity.Normalize();
			//	float dot = mVelocity.Dot(gravity);
			//	mVelocity -= gravity * dot;
			//}
			//else
			//{
			//	// 공중에 있을 때
			//	mVelocity += mGravity * Time::DeltaTime();
			//}

			//// 최대 속도 제한
			//Vector3 gravity = mGravity;
			//gravity.Normalize();
			//float dot = mVelocity.Dot(gravity);
			//gravity = gravity * dot;

			//Vector3 sideVelocity = mVelocity - gravity;
			//if (mLimitVelocity.y < gravity.Length())
			//{
			//	gravity.Normalize();
			//	gravity *= mLimitVelocity.y;
			//}
			//if (mLimitVelocity.x < sideVelocity.Length())
			//{
			//	sideVelocity.Normalize();
			//	sideVelocity *= mLimitVelocity.x;
			//}
			//mVelocity = gravity + sideVelocity;

			////마찰력 조건 ( 적용된 힘이 없고, 속도가 0 이 아닐 떄)
			//if (!(mVelocity == Vector3::Zero))
			//{
			//	// 속도에 반대 방향으로 마찰력을 적용
			//	Vector3 friction = -mVelocity;
			//	friction = friction.Normalizes() * mFriction * mMass * Time::DeltaTime();

			//	// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			//	if (mVelocity.Length() < friction.Length())
			//	{
			//		// 속도를 0 로 만든다.
			//		mVelocity = Vector3(0.f, 0.f, 0.f);
			//	}
			//	else
			//	{
			//		// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
			//		mVelocity += friction;
			//	}
			//}
			//// 속도에 맞게 물체를 이동시킨다.
			//Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			//pos = pos + mVelocity * Time::DeltaTime();
			//GetOwner()->GetComponent<Transform>()->SetPosition(pos);
			//mForce.clear(); //clear() ==  x = 0.0f, y=0.0f, z = 1.0f;
		}

		float fForce = mForce.Length();

		if (0.f != fForce)
		{
			mForce.Normalize();

			float Accel = fForce / mMass;

			mAccelation = mForce * Accel;

			mVelocity += mAccelation * Time::DeltaTime();
		}


		if (mVelocity != Vector3::Zero)
		{
			Vector3 FricDir = -mVelocity;
			FricDir.Normalize();

			Vector3 Friction = FricDir * mFriction * Time::DeltaTime();

			if (mVelocity.Length() <= Friction.Length())
			{
				mVelocity = Vector3(0.f, 0.f, 0.f);
			}
			else
			{
				mVelocity += Friction;
			}
		}

		if (mLimitVelocity < mVelocity.Length())
		{
			mVelocity.Normalize();
			mVelocity *= mLimitVelocity;
		}

		objectMove();

		mForce = Vector3(0.f, 0.f, 0.f);
	}

	void Rigidbody::FixedUpdate()
	{
	
	}

	void Rigidbody::Render()
	{
	}

	void Rigidbody::objectMove()
	{
		float Speed = mVelocity.Length();

		if (0.f != Speed)
		{
			// 이동방향
			Vector3 Dir = mVelocity;

			Dir.Normalize();

			Vector3 Pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			Pos += mVelocity * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(Pos);
		}
	}
	
}