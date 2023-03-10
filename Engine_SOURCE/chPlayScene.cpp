#include "chPlayScene.h"  
#include "chSceneManager.h"
#include "chInput.h"
#include "chObject.h"
#include "chCamera.h"
#include "chCameraScript.h"
#include "chRenderer.h"
#include "chMeshRenderer.h"
#include "chPlayerScript.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "mainPlayer.h"

namespace ch
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
	{

	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{

	
		
		Scene::Initalize();
	}

	void PlayScene::Update()
	{

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		{ //Main Camera 
			GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraComp = cameraObj->AddComponent<Camera>();
			//cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraObj->AddComponent<CameraScript>();
			mainCamera = cameraComp;
		}

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}

		{//player
			GameObject* standObj = object::Instantiate<GameObject>(eLayerType::Player);
			standObj->SetName(L"Player");
			Transform* standTr = standObj->GetComponent<Transform>();
			standTr->SetPosition(Vector3(1.0f, 0.8f, 1.7f));
			standTr->SetScale(Vector3(0.2f, 0.2f, 1.0f));

			SpriteRenderer* standsr = standObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> standmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> standmaterial = Resources::Find<Material>(L"pIdleMaterial");
			standsr->SetMaterial(standmaterial);
			standsr->SetMesh(standmesh);

			standObj->AddComponent<mainPlayer>();
		}

		{//back ground
			GameObject* back = object::Instantiate<GameObject>(eLayerType::BackGround);
			back->SetName(L"BG");
			Transform* backTr = back->GetComponent<Transform>();
			backTr->SetPosition(Vector3(1.0f, 1.1f, 1.7f));
			backTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			SpriteRenderer* backSR = back->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> backmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> backmaterial = Resources::Find<Material>(L"floatMaterial");
			backSR->SetMaterial(backmaterial);
			backSR->SetMesh(backmesh);
						
		}
	}

	void PlayScene::OnExit()
	{
	}

}
