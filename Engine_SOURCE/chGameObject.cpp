#include "chGameObject.h"
#include "chTransform.h"

namespace ch
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mType(eLayerType::None)
		, mbDontDestroy(false)
	{
		mComponents.resize((UINT)eComponentType::End);
		AddComponent(new Transform());
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Component* scrComp : mScripts)
		{
			if (scrComp == nullptr)
				continue;

			delete scrComp;
			scrComp = nullptr;
		}
	}

	void GameObject::Initalize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Initalize();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Initalize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->FixedUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Render();
		}
	}

	void GameObject::AddComponent(Component* comp)
	{
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
	}
	void GameObject::SetPos(Vector3 _Value)
	{
		if (nullptr != GetComponent<Transform>())
		{
			GetComponent<Transform>()->SetPosition(_Value);
		}
	}
	void GameObject::SetScale(Vector3 _Value)
	{
		if (nullptr != GetComponent<Transform>())
		{
			GetComponent<Transform>()->SetScale(_Value);
		}
		if (nullptr != GetComponent<SpriteRenderer>())
		{
			GetComponent<SpriteRenderer>()->ChangeSize();
		}
		if (nullptr != GetComponent<MeshRenderer>())
		{
			GetComponent<MeshRenderer>()->ChangeSize();
		}
	}
	void GameObject::SetRotation(Vector3 _Value)
	{
	}
	Vector3 GameObject::GetPos()
	{
		return Vector3();
	}
	Vector3 GameObject::GetScale()
	{
		return Vector3();
	}
	Vector3 GameObject::GetRotation()
	{
		return Vector3();
	}
	void GameObject::SetMaterial(std::shared_ptr<Material> _Material)
	{
		if (nullptr != GetComponent<SpriteRenderer>())
		{
			GetComponent<SpriteRenderer>()->SetMaterial(_Material);
		}
	}

	void GameObject::SetMesh(std::shared_ptr<Mesh> _Mesh)
	{
		if (nullptr != GetComponent<SpriteRenderer>())
		{
			GetComponent<SpriteRenderer>()->SetMesh(_Mesh);
		}
	}
	void GameObject::Flip()
	{
		BaseRenderer* baseRenderer = GetComponent<BaseRenderer>();
		if (baseRenderer)
		{
			std::shared_ptr<Material> mtrl = baseRenderer->GetMaterial();
			if (mtrl)
			{

#define INVERSE -1
#define NORMAL 1


				int isInverse = mbIsLeft ? INVERSE : NORMAL;

				mtrl->SetData(eGPUParam::Int, &isInverse);
			}
		}
	}
}
