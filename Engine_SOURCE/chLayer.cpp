#include "chLayer.h"


namespace ch
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initalize()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Initalize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->FixedUpdate();
		}
	}

	void Layer::Destroy()
	{
		std::set<GameObject*> deleteObjects;
		// ������ ������Ʈ���� ���� ã�ƿ´�.
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Dead)
			{
				deleteObjects.insert(gameObj);
			}
		}

		// �������� ������Ʈ�� ���� ������Ʈ �����ȿ��� ����
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			std::set<GameObject*>::iterator deleteIter
				= deleteObjects.find(*iter);

			if (deleteIter != deleteObjects.end())
			{
				mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		// ������ ������Ʈ���� ���� ��(�޸�)���� ����
		for (GameObject* gameObj : deleteObjects)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}

	void Layer::Render()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mGameObjects.push_back(gameObject);
	}

	std::vector<GameObject*> Layer::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> donts;
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->IsDontDestroy() == true)
			{
				donts.push_back((*iter));
				mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		return donts;
	}
}