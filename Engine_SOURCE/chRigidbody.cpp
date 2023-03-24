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
			//	// ������ ������
			//	Vector3 gravity = mGravity;
			//	gravity.Normalize();
			//	float dot = mVelocity.Dot(gravity);
			//	mVelocity -= gravity * dot;
			//}
			//else
			//{
			//	// ���߿� ���� ��
			//	mVelocity += mGravity * Time::DeltaTime();
			//}

			//// �ִ� �ӵ� ����
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

			////������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ��)
			//if (!(mVelocity == Vector3::Zero))
			//{
			//	// �ӵ��� �ݴ� �������� �������� ����
			//	Vector3 friction = -mVelocity;
			//	friction = friction.Normalizes() * mFriction * mMass * Time::DeltaTime();

			//	// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			//	if (mVelocity.Length() < friction.Length())
			//	{
			//		// �ӵ��� 0 �� �����.
			//		mVelocity = Vector3(0.f, 0.f, 0.f);
			//	}
			//	else
			//	{
			//		// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
			//		mVelocity += friction;
			//	}
			//}
			//// �ӵ��� �°� ��ü�� �̵���Ų��.
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
			// �̵�����
			Vector3 Dir = mVelocity;

			Dir.Normalize();

			Vector3 Pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			Pos += mVelocity * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(Pos);
		}
	}
	
}