#include "chRigidbody.h"
#include "chGameObject.h"
#include "chTime.h"
namespace ch 
{
	bool Rigidbody::dodgeForceReset = false;


	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		,mForce(Vector3::Zero)
		,mAccelation(Vector3::Zero)
		,mVelocity(Vector3::Zero)
		, mFriction(15.0f)
	{
		mLimitVelocity = 5.0f;
		mbGround = true;
		mGravity = Vector3(0.0f, 0.0f,0.1f);
		mForceResetTimer = 0.0f;
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initalize()
	{
	}

	void Rigidbody::Update()
	{
		if (dodgeForceReset == true)
		{
			mForceResetTimer += Time::DeltaTime();

		}

		if (mForceResetTimer >= 0.91f) 
		{
			mForce = Vector3::Zero; // reset force
			mForceResetTimer = 0.0f; // reset timer
			dodgeForceReset = false;
			mVelocity = Vector3::Zero;
		}

		float fForce = mForce.Length();

		if (0.f != fForce)
		{
			mForce.Normalize();

			float Accel = fForce / mMass;

			mAccelation = mForce * Accel;

			mVelocity += mAccelation * Time::DeltaTime();
		}

		// Apply friction to velocity
		if (mVelocity != Vector3::Zero)
		{
			Vector3 FricDir = -mVelocity;
			FricDir.Normalize();

			Vector3 Friction = FricDir * mFriction * Time::DeltaTime();

			if (mVelocity.Length() <= Friction.Length())
			{
				mVelocity = Vector3::Zero; // stop the object immediately
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