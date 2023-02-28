#pragma once
#include "chEntity.h"
#include "chLayer.h"
#include "chGameObject.h"

namespace ch
{
	using namespace ch::enums;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj, const eLayerType type);
		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }
		std::vector<GameObject*> GetDontDestroyGameObjects();

	private:
		std::vector<Layer> mLayers;
	};
}
