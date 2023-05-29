#pragma once
#include "chGameObject.h"
#include "chCollider2D.h"
namespace ch
{
	class chasePlayerOBJ : public GameObject
	{
	public:
		chasePlayerOBJ();
		virtual ~chasePlayerOBJ();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	
	public:
		void SetOwnerObj(GameObject* _a) { OwnerObject = _a; }
		GameObject* GetOwnerObj() const { return OwnerObject; }

	private:
		GameObject* OwnerObject; // Declare the member variable
		
		Collider2D* mCollider;
	public:
	
		Transform* OwnerTr;
		Transform* thisTr;
	};

}

