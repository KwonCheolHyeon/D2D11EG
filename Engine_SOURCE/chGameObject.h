#pragma once
#include "chComponent.h"
#include "chScript.h"
#include "chEntity.h"
#include "chMeshRenderer.h"
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

			for (auto c : mScripts)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					return comp;
			}

			return nullptr;
		}
		template <typename T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> components = {};

			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					components.push_back(comp);
			}

			return components;
		}


		const std::vector<Script*>& GetScripts() { return mScripts; }

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

	public:
		void SetPos(Vector3 _Value);
		//void SetScale(Vector3 _Value);
		void SetRotation(Vector3 _Value);

		Vector3 GetPos();
		//Vector3 GetScale();
		Vector3 GetRotation();

	public:
		void SetLeft() { mbIsLeft = true; }
		void SetRight() { mbIsLeft = false; }
		bool isLeft() { return mbIsLeft; }
		void Flip();

	public:
		void setHand() { mHand = true; }
		void setNoHand() { mHand = false; }
		bool GetHand() { return mHand; }
	private:
		bool mbIsLeft;//flip용
		bool prevIsLeft;
		bool mHand;//구르거나 오른쪽 뒤를 볼때 

	protected:
		std::vector<Component*> mComponents;

	private:
		eState mState;
		eLayerType mType;
		std::vector<Script*> mScripts;
		bool mbDontDestroy;
		//Scene* mScene;


		
		
	};
}

