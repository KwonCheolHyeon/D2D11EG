#pragma once
#include "chComponent.h"
#include "chTransform.h"

namespace ch 
{

	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider);
		virtual void OnTriggerStay(Collider2D* collider);
		virtual void OnTriggerExit(Collider2D* collider);

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 center) { mCenter = center; }
		void SetRadius(float radius) { mRadius = radius; }
		bool IsTriiger() { return mbTrigger; }
		void SetPosition(Vector3 position) { mPosition = position; }

		UINT GetID() { return mID; }
		Vector3 GetPosition() { return mPosition; }
				
		Vector2 GetCenter() { return mCenter; }
		Vector2 GetSize() { return mSize; }
		eColliderType GetType() { return mType; }

		float GetRadius(Vector2 size) { return size.x * 0.5f; }
	private:
		static UINT ColliderNumber;
		UINT mID;
		eColliderType mType;
		Transform* mTransform;

		Vector2 mSize;
		Vector2 mCenter;
		Vector3 mPosition;
		float mRadius;
		bool mbTrigger;
	};

	
}

