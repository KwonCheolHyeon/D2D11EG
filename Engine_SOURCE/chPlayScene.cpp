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
#include "chPlayerHand.h"
#include "chGun.h"
#include "chBulletPool.h"
#include "chBulletScr.h"
#include "chPaintShader.h"
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

			{//È½ºÒ¿¡ ¾¸
				/*GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
				directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
				Light* lightComp = directionalLight->AddComponent<Light>();
				lightComp->SetType(eLightType::Point);
				lightComp->SetRadius(10.0f);
				lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));*/
			}
		
		
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

		{ //Camera UI
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}
		{//ÃÑ¾Ë

			generateBullet(10);
		}

		{//ÇÃ·¹ÀÌ¾î
			player = object::Instantiate<mainPlayer>(eLayerType::Player, this);
			player->SetName(L"Player");

			PlayerHand* hand = object::Instantiate<PlayerHand>(eLayerType::Hand, this);
			hand->SetName(L"PHand");
			hand->SetPlayer(player);

			Gun *gun = object::Instantiate<Gun>(eLayerType::Hand, this);
			gun->SetName(L"PGun");
			gun->SetHand(hand);
			gun->SetPool(pool);

		}
		



		//UI
		{
			/*chUiCursor = object::Instantiate<GameObject>(eLayerType::UI, this);
			chUiCursor->SetName(L"MouseCursor");

			chUiCursor->AddComponent<MouseCursorScript>()->SetTarget(player);
			chUiCursorTR = chUiCursor->GetComponent<Transform>();
			chUiCursorTR->SetPosition(Input::GetMousPosition());
			chUiCursorTR->SetScale(Vector3(0.5f, 0.5f, 1.f));

			SpriteRenderer* hpsr = chUiCursor->AddComponent<SpriteRenderer>();
			chUiCursor->AddComponent(hpsr);
			std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> hpspritematerial = Resources::Find<Material>(L"crossHairMaterial");
			hpsr->SetMesh(hpmesh);
			hpsr->SetMaterial(hpspritematerial);*/

			
		}

		

		
		

		{//back ground
			GameObject* back = object::Instantiate<GameObject>(eLayerType::BackGround, this);
			back->SetName(L"BG");
			Transform* backTr = back->GetComponent<Transform>();
			backTr->SetPosition(Vector3(1.0f, 1.1f, 0.1f));
			backTr->SetScale(Vector3(20.0f, 20.0f, 0.1f));

			SpriteRenderer* backSR = back->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> backmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> backmaterial = Resources::Find<Material>(L"floatMaterial");
			backSR->SetMaterial(backmaterial);
			backSR->SetMesh(backmesh);
		}



		chCameraOBJ->GetComponent<Camera>()->SetTarget(player);
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

	void PlayScene::generateBullet(int size)
	{
		pool = object::Instantiate<BulletPool>(eLayerType::Weapone, this);

		for (size_t i = 0; i < size; i++)
		{
			Bullet* bulletobj = object::Instantiate<Bullet>(eLayerType::Weapone, this);
			containBullets.push_back(bulletobj);
			containBullets[i]->SetLayerType(eLayerType::Weapone);
			containBullets[i]->SetName(L"Bullet" + i);
			containBullets[i]->GetComponent<Transform>()->SetPosition(Vector3(100.0f,100.0f, 0.0f));
			containBullets[i]->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.3f, 0.2f));
			SpriteRenderer* render = containBullets[i]->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> bulletMaterial = Resources::Find<Material>(L"W_BulletMaterial");
			render->SetMaterial(bulletMaterial);
			std::shared_ptr<Mesh> bulletMesh = Resources::Find<Mesh>(L"RectMesh");
			render->SetMesh(bulletMesh);

			containBullets[i]->AddComponent<BulletScr>();
			pool->SetBullets(containBullets[i]);

		}

	}



}
