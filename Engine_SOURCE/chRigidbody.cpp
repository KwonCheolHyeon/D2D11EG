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
			// ������ ������
			Vector3 gravity = mGravity;
			gravity.Normalize();
			float dot = mVelocity.Dot(gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// ���߿� ���� ��
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �ִ� �ӵ� ����
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

		//������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ��)
		if (!(mVelocity == Vector3::Zero))
		{
			// �ӵ��� �ݴ� �������� �������� ����
			Vector3 friction = -mVelocity;
			friction = friction.Normalizes() * mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.Length() < friction.Length())
			{
				// �ӵ��� 0 �� �����.
				mVelocity = Vector3(0.f, 0.f, 0.f);
			}
			else
			{
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
				mVelocity += friction;
			}
		}
		// �ӵ��� �°� ��ü�� �̵���Ų��.
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