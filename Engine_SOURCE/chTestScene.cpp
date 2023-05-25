#include "chTestScene.h"
#include "chSceneManager.h"
#include "chInput.h"
#include "chObject.h"
#include "chCamera.h"
#include "chCameraScript.h"
#include "chRenderer.h"
#include "chMeshRenderer.h"
#include "chResources.h"
#include "chSpriteRenderer.h"
#include "MapObject.h"
#include "CharacterBase.h"
#include "MonsterBase.h"
#include "chBoss.h"
namespace ch 
{
	TestScene::TestScene()
		: Scene(eSceneType::Test)
	{

	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initalize()
	{
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		{ //Main Camera 
			chCameraOBJ = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraComp = chCameraOBJ->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			//cameraComp->RegisterCameraInRenderer();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			chCameraOBJ->AddComponent<CameraScript>();
			mainCamera = cameraComp;
		}
		{
			player = object::Instantiate<CharacterBase>(eLayerType::Player, this);
			player->SetName(L"Player");		
		}
		{
			GameObject* BossMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			BossMonster->AddComponent<Boss>();
		}

		chCameraOBJ->GetComponent<Camera>()->SetTarget(player);
		Scene::Initalize();
	}

	void TestScene::Update()
	{
		Scene::Update();
	}

	void TestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TestScene::Render()
	{
		Scene::Render();
	}

	void TestScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void TestScene::OnExit()
	{
		Scene::OnExit();
	}

}