#pragma once
#include "chComponent.h"

using namespace ch::math;
namespace ch
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

		void SetParent(Transform* parent) { mParent = parent; }
		Transform* GetParent() { return mParent; }

		void SetOffset(Vector3 offset) { moffSet = offset; }
		void SetPosition(Vector3 position) { mPosition = position + moffSet; };
		
		void SetRotation(Vector3 degree) { mRotation = degree; };
		void SetScale(Vector3 scale) { mScale = scale; };


		Vector3 GetPosition() { return mPosition; };
		
		Vector3 GetRotation() { return mRotation; };
		Vector3 GetScale() { return mScale; };
		
		Vector3 Foward() { return mFoward; }

		Vector3 Right() { return mRight; }

		Vector3 Up() { return mUp; }

		Matrix& GetWolrdMatrix() { return mWorld; }

		

	private:
		Transform* mParent;
		Vector3 mFoward;
		Vector3 mRight;
		Vector3 mUp;
		Vector3 mPosition;
		Vector3 moffSet;
	
		Vector3 mRotation;
		Vector3 mScale;
		Matrix mWorld;
	};
}
