#include "chMainMenu.h"
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

namespace ch
{
	MainMenu::MainMenu()
		: Scene(eSceneType::Main)
	{
	}
	MainMenu::~MainMenu()
	{
	}
	void MainMenu::Initalize()
	{
		LoadResources();

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		

		//UI CameraObj
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);


		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		{//mainmenu
			{//bg
				GameObject* rightObj = object::Instantiate<GameObject>(eLayerType::BackGround);
				rightObj->SetName(L"mainmenuBG");
				Transform* rightObjTr = rightObj->GetComponent<Transform>();
				rightObjTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				rightObjTr->SetScale(Vector3(20.0f, 18.0F, 1.0f));

				SpriteRenderer* rightsr = rightObj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> titlerightmaterial = Resources::Find<Material>(L"mainBgMaterial");
				rightsr->SetMaterial(titlerightmaterial);
				rightsr->SetMesh(mesh);
			}

			{//mainmenu
				GameObject* rightObj = object::Instantiate<GameObject>(eLayerType::BackGround);
				rightObj->SetName(L"mainmenu");
				Transform* rightObjTr = rightObj->GetComponent<Transform>();
				rightObjTr->SetPosition(Vector3(0.0f, 0.0f, 1.7f));
				rightObjTr->SetScale(Vector3(18.0f, 11.0f, 1.0f));

				SpriteRenderer* rightsr = rightObj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> titlerightmaterial = Resources::Find<Material>(L"mainMenuMaterial");
				rightsr->SetMaterial(titlerightmaterial);
				rightsr->SetMesh(mesh);
			}
		}



		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		Scene::Initalize();
	}
	void MainMenu::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}
	void MainMenu::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void MainMenu::Render()
	{
		Scene::Render();
	}
	void MainMenu::OnEnter()
	{
		Scene::OnEnter();
	}
	void MainMenu::OnExit()
	{
		Scene::OnExit();
	}
	void MainMenu::LoadResources()
	{
		Scene::OnExit();
	}
}