#include "chTitleScene.h"
#include "chTransform.h"
#include "chMeshRenderer.h"
#include "chRenderer.h"
#include "chResources.h"
#include "chTexture.h"
#include "chPlayerScript.h"
#include "chCamera.h"
#include "chCameraScript.h"
#include "chSpriteRenderer.h"
#include "chGridScript.h"
#include "chObject.h"
#include "chInput.h"
#include "chCollider2D.h"
#include "chPlayer.h"
#include "chMonster.h"
#include "chCollisionManager.h"
#include "mainPlayer.h"
#include "chAnimator.h"

namespace ch
{
	TitleScene::TitleScene()
		:Scene(eSceneType::Tilte)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		{ //Camera UI
		/*	GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Perspective);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);*/
		}
			
		//{//player
		//	GameObject* standObj = object::Instantiate<GameObject>(eLayerType::Player);
		//	standObj->SetName(L"Player");
		//	Transform* standTr = standObj->GetComponent<Transform>();
		//	standTr->SetPosition(Vector3(1.0f, 0.8f, 1.7f));
		//	standTr->SetScale(Vector3(0.2f, 0.2f, 1.0f));

		//	SpriteRenderer* standsr = standObj->AddComponent<SpriteRenderer>();
		//	std::shared_ptr<Mesh> standmesh = Resources::Find<Mesh>(L"RectMesh");
		//	std::shared_ptr<Material> standmaterial = Resources::Find<Material>(L"pIdleMaterial");
		//	standsr->SetMaterial(standmaterial);
		//	standsr->SetMesh(standmesh);

		//	standObj->AddComponent<mainPlayer>();
		//}

		//{
		//	GameObject* back = object::Instantiate<GameObject>(eLayerType::Monster,this);
		//	back->SetName(L"BG");
		//	Transform* backTr = back->GetComponent<Transform>();
		//	backTr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
		//	backTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

		//	SpriteRenderer* backSR = back->AddComponent<SpriteRenderer>();
		//	std::shared_ptr<Mesh> backmesh = Resources::Find<Mesh>(L"RectMesh");
		//	std::shared_ptr<Material> backmaterial = Resources::Find<Material>(L"floatMaterial");
		//	backSR->SetMaterial(backmaterial);
		//	backSR->SetMesh(backmesh);
		//}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N)) 
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void TitleScene::OnExit()
	{
		Scene::OnExit();
	}
	void TitleScene::LoadResources()
	{
		Scene::LoadResources();
	}
}