#include "chPlayScene.h"  
#include "chSceneManager.h"
#include "chInput.h"
#include "chObject.h"
#include "chCamera.h"
#include "chCameraScript.h"
#include "chRenderer.h"
#include "chMeshRenderer.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "mainPlayer.h"
#include "chMouseCursorScript.h"


namespace ch
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
		, chUiCursor(nullptr)
	{

	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{

		{
			{
				GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
				directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
				Light* lightComp = directionalLight->AddComponent<Light>();
				lightComp->SetType(eLightType::Directional);
				lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			}

			{
				/*GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
				directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
				Light* lightComp = directionalLight->AddComponent<Light>();
				lightComp->SetType(eLightType::Point);
				lightComp->SetRadius(10.0f);
				lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));*/
			}
		
		
		}
		{ //Main Camera 
			GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraComp = cameraObj->AddComponent<Camera>();
			//cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraObj->AddComponent<CameraScript>();
			mainCamera = cameraComp;
		}

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}
		{//플레이어
			mainPlayer* player = object::Instantiate<mainPlayer>(eLayerType::Player, this);
			player->SetName(L"Player");

		}
		{//UI
			chUiCursor = object::Instantiate<GameObject>(eLayerType::UI, this);
			chUiCursor->SetName(L"MouseCursor");

			chUiCursor->AddComponent<MouseCursorScript>();
			chUiCursorTR = chUiCursor->GetComponent<Transform>();
			chUiCursorTR->SetPosition(Input::GetMousPosition());
			chUiCursorTR->SetScale(Vector3(0.5f, 0.5f, 1.f));

			SpriteRenderer* hpsr = chUiCursor->AddComponent<SpriteRenderer>();
			chUiCursor->AddComponent(hpsr);
			std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> hpspritematerial = Resources::Find<Material>(L"crossHairMaterial");
			hpsr->SetMesh(hpmesh);
			hpsr->SetMaterial(hpspritematerial);

			
			
		}


		{//back ground
			/*GameObject* back = object::Instantiate<GameObject>(eLayerType::BackGround, this);
			back->SetName(L"BG");
			Transform* backTr = back->GetComponent<Transform>();
			backTr->SetPosition(Vector3(1.0f, 1.1f, 0.1f));
			backTr->SetScale(Vector3(6.0f, 5.0f, 0.1f));

			SpriteRenderer* backSR = back->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> backmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> backmaterial = Resources::Find<Material>(L"floatMaterial");
			backSR->SetMaterial(backmaterial);
			backSR->SetMesh(backmesh);*/
		}

		Scene::Initalize();
	}

	void PlayScene::Update()
	{

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Main);
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
		
		Scene::OnEnter();
	}

	void PlayScene::OnExit()
	{
		Scene::OnExit();

	}



}
