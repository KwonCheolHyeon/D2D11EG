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
#include "TableObject.h"
#include "MapObject.h"
#include "chCollisionManager.h"
#include "CharacterBase.h"
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
			

			}
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

		{

		}

		{//몬스터
			GameObject* monster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			monster->AddComponent<Bullet_Kin>();
		}


		
		generateMap();
		generateObject();


		chCameraOBJ->GetComponent<Camera>()->SetTarget(player);
		Scene::Initalize();

		
		
	}

	void PlayScene::Update()
	{

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Main);
		}
		if (Input::GetKeyDown(eKeyCode::H))
		{
			mapTr->SetPosition(Vector3(1000.0f, 1000.0f, 0.1f));
		}
		if (Input::GetKeyDown(eKeyCode::G))
		{
			mapTr->SetPosition(Vector3(0.0f, 0.0f, 0.1f));
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
		CollisionManager::CollisionLayerCheck(eLayerType::Object, eLayerType::Player); // 책상과 플레이어
		CollisionManager::CollisionLayerCheck(eLayerType::Object, eLayerType::Weapone);//총알과 책상
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

	void PlayScene::generateMap()
	{
		{//back ground01
			GameObject* back = object::Instantiate<MapObject>(eLayerType::BackGround, this);
			back->SetName(L"BG01");

			mapTr = back->GetComponent<Transform>();
			mapTr->SetPosition(Vector3(0.0f, 0.0f, 0.1f));
			mapTr->SetScale(Vector3(50.0f, 61.3f, 0.1f));
		}
#pragma region 콜라이더
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(5.5f, -0.25f, 0.0f));
			mapColliderTr->SetScale(Vector3(7.3f, 1.0f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(12.1f, 1.1f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.68f, 4.0f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
			mapCollider->SetCenter(Vector2(0.0f, 0.0f));
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(18.32f, -0.2f, 0.0f));
			mapColliderTr->SetScale(Vector3(7.79f, 5.5f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
			
		
		}


		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(11.55f, -6.2f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.7f, 8.25f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);


		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(3.74f, -8.5f, 1.0f));
			mapColliderTr->SetScale(Vector3(9.68f, 1.41f, 0.0f));
			
			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);


		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-4.22f, -7.88f, 1.0f));
			mapColliderTr->SetScale(Vector3(6.73f, 5.02f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(6.49f, -22.885f, 1.0f));
			mapColliderTr->SetScale(Vector3(4.4f, 10.85f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-5.92f, -28.3f, 1.0f));
			mapColliderTr->SetScale(Vector3(6.7f, 4.2f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(11.57f, -14.5f, 1.0f));
			mapColliderTr->SetScale(Vector3(6.7f, 5.91f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(14.8f, -14.9f, 1.0f));
			mapColliderTr->SetScale(Vector3(1.26f, 5.6f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-2.14f, 7.72f, 1.0f));
			mapColliderTr->SetScale(Vector3(10.4f, 5.6f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(12.1f, 8.04f, 1.0f));
			mapColliderTr->SetScale(Vector3(6.7f, 7.4f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(6.82f, 7.7f, 1.0f));
			mapColliderTr->SetScale(Vector3(5.25f, 5.5f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}


		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-4.5f, 1.96f, 1.0f));
			mapColliderTr->SetScale(Vector3(12.9f, 6.125f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(20.148f, -8.3535f, 1.0f));
			mapColliderTr->SetScale(Vector3(-10.574f, 1.553f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-9.82f, -3.6f, 1.0f));
			mapColliderTr->SetScale(Vector3(4.5f, 5.5f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-16.7f, -3.6f, 1.0f));
			mapColliderTr->SetScale(Vector3(7.f, 5.5f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-4.25f, -13.79f, 1.0f));
			mapColliderTr->SetScale(Vector3(6.65f, 4.5f, 0.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		

#pragma endregion

	}

	void PlayScene::generateObject()
	{
		{//책상
			GameObject* tableObject = object::Instantiate<TableObject>(eLayerType::Object, this);
			tableObject->SetName(L"table1");

			Transform* mapColliderTr = tableObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-1.5f, 0.5f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.2f, 0.75f, 0.1f));
		}

		{//책상
			GameObject* tableObject = object::Instantiate<TableObject>(eLayerType::Object, this);
			tableObject->SetName(L"table1");

			Transform* mapColliderTr = tableObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(0.5f, 2.0f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.2f, 0.75f, 0.1f));
		}

		{//책상
			GameObject* tableObject = object::Instantiate<TableObject>(eLayerType::Object, this);
			tableObject->SetName(L"table1");

			Transform* mapColliderTr = tableObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(3.5f, 2.0f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.2f, 0.75f, 0.1f));
		}


	}



}
