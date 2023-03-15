#pragma once
#include "chComponent.h"
#include "chScript.h"
#include "chEntity.h"
#include "chMesh.h"
#include "chTransform.h"
#include "chSpriteRenderer.h"
#include "chMeshRenderer.h"
#include "chComponent.h"

namespace ch
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			eComponentType order = comp->GetOrder();

			if (order != eComponentType::Script)
			{
				mComponents[(UINT)order] = comp;
				mComponents[(UINT)order]->SetOwner(this);
			}
			else
			{
				mScripts.push_back(dynamic_cast<Script*>(comp));
				comp->SetOwner(this);
			}

			return comp;
		}
		void AddComponent(Component* comp);

		template <typename T>
		T* GetComponent()
		{
			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					return comp;
			}

			return nullptr;
		}
		const std::vector<Script*>& GetScripts() { return mScripts; }

		void SetPos(Vector3 _Value);
		void SetScale(Vector3 _Value);
		void SetRotation(Vector3 _Value);

		Vector3 GetPos();
		Vector3 GetScale();
		Vector3 GetRotation();

		void SetMaterial(std::shared_ptr<Material> _Material);
		void SetMesh(std::shared_ptr<Mesh> _Mesh);

		bool IsDead()
		{
			if (mState == eState::Dead)
				return true;

			return false;
		}
		void Pause() { mState = eState::Paused; }
		void Death() { mState = eState::Dead; }
		eState GetState() { return mState; }

		bool IsDontDestroy() { return mbDontDestroy; }
		void DontDestroy(bool enable) { mbDontDestroy = enable; }
		eLayerType GetLayerType() { return mType; }
		void SetLayerType(eLayerType type) { mType = type; }

		void Flip();
	protected:
		std::vector<Component*> mComponents;

	private:
		eState mState;
		eLayerType mType;
		std::vector<Script*> mScripts;
		bool mbDontDestroy;
		//Scene* mScene;
		bool mbIsLeft;
	};
}

