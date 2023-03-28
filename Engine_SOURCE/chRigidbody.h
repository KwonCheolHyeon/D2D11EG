#pragma once
#include "chComponent.h"


using namespace ch::math;

namespace ch
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void AddForce(Vector3 force) { mForce += force; }
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		Vector3 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }

	public:
		static bool dodgeForceReset;//�����⶧ �� �ʱ�ȭ �Լ�
	
	private:
		// ���� �������� �̿��� �̵�
		float mMass; //����
		float mFriction; //����
		//float mDamping;//���� �ӵ�

		//float mMoveFriction;
		Vector3 mForce; //ũ��, ����
		Vector3 mVelocity; //�ӵ�(�ӷ� + ����)
		Vector3 mAccelation; //���ӵ�

		// �߷� �̿��� ����
		Vector3 mGravity;
		bool mbGround;
		float mLimitVelocity;

	private:
		float mForceResetTimer;

	private:
		void objectMove();
	};

}

