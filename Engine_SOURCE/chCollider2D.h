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

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 center) { mCenter = center; }

	private:
		eColliderType mType;
		Transform* mTransform;

		Vector2 mSize;
		Vector2 mCenter;
		bool mbTrigger;
	};

	
}

