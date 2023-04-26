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
#include "chHeart_UI.h"
#include "Heart_Scr.h"
#include "chPlayerScr.h"
#include "MonsterBase.h"
#include "Bullet_Kin.h"
#include "chCollisionManager.h"
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

			{//횟불에 씀
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
#pragma region UI모음
		{
			{
				Heart_UI* heart0 = object::Instantiate<Heart_UI>(eLayerType::UI, this);
				heart0->SetName(L"HearUI");
				heart0->AddComponent<Heart_Scr>();
				Transform* htr0 = heart0->GetComponent<Transform>();
				htr0->SetPosition(Vector3(-6.5f, 4.9f, 0.f));
				htr0->SetScale(Vector3(0.7f, 0.65f, 0.f));


				Heart_UI* heart1 = object::Instantiate<Heart_UI>(eLayerType::UI, this);
				heart1->SetName(L"HearUI");
				heart1->AddComponent<Heart_Scr>();
				Transform* htr1 = heart1->GetComponent<Transform>();
				htr1->SetPosition(Vector3(-5.7f, 4.9f, 0.f));
				htr1->SetScale(Vector3(0.7f, 0.65f, 0.f));


				Heart_UI* heart2 = object::Instantiate<Heart_UI>(eLayerType::UI, this);
				heart2->SetName(L"HearUI");
				heart2->AddComponent<Heart_Scr>();
				Transform* htr2 = heart2->GetComponent<Transform>();
				htr2->SetPosition(Vector3(-4.9f, 4.9f, 0.f));
				htr2->SetScale(Vector3(0.7f, 0.65f, 0.f));

				HeartControl.push_back(heart0); //첫번째
				HeartControl.push_back(heart1); //두번째
				HeartControl.push_back(heart2); //세번째
			}



		}
#pragma endregion

		{//총알

			generateBullet(100);
		}

		{//플레이어
			player = object::Instantiate<mainPlayer>(eLayerType::Player, this);
			player->SetName(L"Player");

			player->GetComponent<PlayerScr>()->SetHeart_UI(HeartControl);

			GameObject* gunBox = object::Instantiate<GameObject>(eLayerType::Weapone, this);
			gunBox->SetName(L"GunBox");
			gunBox->GetComponent<Transform>()->SetPosition(Vector3(3.f, 3.f, 0.f));
			gunBox->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f,0.f));


			PlayerHand* hand = object::Instantiate<PlayerHand>(eLayerType::Hand, this);
			hand->SetName(L"PHand");
			hand->SetPlayer(player);

			Gun *gun = object::Instantiate<Gun>(eLayerType::Hand, this);
			gun->SetName(L"PGun");
			gun->SetHand(hand);
			gun->SetPool(pool);
			gun->SetGunBox(gunBox);
			gun->SetPlayer(player);
			


		}

		{//몬스터
			GameObject* monster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			monster->AddComponent<Bullet_Kin>();
		}
		
		{//back ground
			/*GameObject* back = object::Instantiate<GameObject>(eLayerType::BackGround, this);
			back->SetName(L"BG");
			Transform* backTr = back->GetComponent<Transform>();
			backTr->SetPosition(Vector3(1.0f, 1.1f, 0.1f));
			backTr->SetScale(Vector3(20.0f, 20.0f, 0.1f));

			SpriteRenderer* backSR = back->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> backmesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> backmaterial = Resources::Find<Material>(L"floatMaterial");
			backSR->SetMaterial(backmaterial);
			backSR->SetMesh(backmesh);*/
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
		CollisionManager::CollisionLayerCheck(eLayerType::Weapone, eLayerType::Monster);
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

			Collider2D* mCollider = bulletobj->AddComponent<Collider2D>();
			mCollider->SetName(L"billetKinCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(1.f, 1.f));

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
