#include "chMainMenuScene.h"
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
#include "chAnimator.h"
#include "chResources.h"

namespace ch
{
	MainMenu::MainMenu()
		: Scene(eSceneType::Main)
		, chCamera(nullptr)
		, chUiCamera(nullptr)
	{
	}
	MainMenu::~MainMenu()
	{
	}
	void MainMenu::Initalize()
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		{
			// main 카메라
			chCamera = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraComp = chCamera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			chCamera->AddComponent<CameraScript>();
			mainCamera = cameraComp;
		}
		{
			// ui 카메라
			chUiCamera = object::Instantiate<GameObject>(eLayerType::Camera);
			Camera* cameraComp = chUiCamera->AddComponent<Camera>();
			cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
		}
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"Zelda");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 2.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			tr->SetScale(Vector3(0.3f, 0.2f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetCenter(Vector2(0.2f, 0.2f));
			//collider->SetSize(Vector2(1.5f, 1.5f));
			

			/*SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);*/
			obj->AddComponent<PlayerScript>();
			//object::DontDestroyOnLoad(obj);
		}
	
		{//mainmenu
			{//bg
				GameObject* rightObj = object::Instantiate<GameObject>(eLayerType::BackGround);
				rightObj->SetName(L"mainmenuBG");
				Transform* rightObjTr = rightObj->GetComponent<Transform>();
				rightObjTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				rightObjTr->SetScale(Vector3(10.0f, 10.0f, 2.0f));

				SpriteRenderer* rightsr = rightObj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> titlerightmaterial = Resources::Find<Material>(L"mainBgMaterial");
				rightsr->SetMaterial(titlerightmaterial);
				rightsr->SetMesh(mesh);
			}

			{//mainmenu
				GameObject* rightObj = object::Instantiate<GameObject>(eLayerType::BackGround);
				rightObj->SetName(L"mainmenu");
				Transform* rightObjTr = rightObj->GetComponent<Transform>();
				rightObjTr->SetPosition(Vector3(1.0f, 1.0f, 1.7f));
				rightObjTr->SetScale(Vector3(5.3f, 3.0f, 2.0f));

				SpriteRenderer* rightsr = rightObj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> titlerightmaterial = Resources::Find<Material>(L"mainMenuMaterial");
				rightsr->SetMaterial(titlerightmaterial);
				rightsr->SetMesh(mesh);
			}
		}

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