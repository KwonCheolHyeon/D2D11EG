#include "chRigidbody.h"
#include "chGameObject.h"
#include "chTime.h"
namespace ch 
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(150.0f)
	{
		mLimitVelocity.x = 200.f;
		mLimitVelocity.y = 200.f;
		mLimitVelocity.z = 200.f;
		mbGround = false;
		mGravity = Vector3(0.0f, 0.0f,100.0f);
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initalize()
	{
	}

	void Rigidbody::Update()
	{
		
	}

	void Rigidbody::FixedUpdate()
	{
		mAccelation = mForce / mMass;
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// 땅위에 있을때
			Vector3 gravity = mGravity;
			gravity.Normalize();
			float dot = mVelocity.Dot(gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// 공중에 있을 때
			mVelocity += mGravity * Time::DeltaTime();
		}

		// 최대 속도 제한
		Vector3 gravity = mGravity;
		gravity.Normalize();
		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;

		Vector3 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}
		if (mLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		//마찰력 조건 ( 적용된 힘이 없고, 속도가 0 이 아닐 떄)
		if (!(mVelocity == Vector3::Zero))
		{
			// 속도에 반대 방향으로 마찰력을 적용
			Vector3 friction = -mVelocity;
			friction = friction.Normalizes() * mFriction * mMass * Time::DeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.Length() < friction.Length())
			{
				// 속도를 0 로 만든다.
				mVelocity = Vector3(0.f, 0.f, 0.f);
			}
			else
			{
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				mVelocity += friction;
			}
		}
		// 속도에 맞게 물체를 이동시킨다.
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();
		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		mForce.clear();
	}

	void Rigidbody::Render()
	{
	}

	void Rigidbody::AddForce(Vector3 force)
	{
		mForce += force;
	}

	
}