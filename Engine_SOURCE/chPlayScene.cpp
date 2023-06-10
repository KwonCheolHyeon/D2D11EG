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
#include "Bullet_Kin_Gun.h"
#include "chBoss.h"
#include "Convict.h"
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

		//{//플레이어
		//	player = object::Instantiate<mainPlayer>(eLayerType::Player, this);
		//	player->SetName(L"Player");

		//	player->GetComponent<PlayerScr>()->SetHeart_UI(HeartControl);

		//	GameObject* gunBox = object::Instantiate<GameObject>(eLayerType::Weapone, this);
		//	gunBox->SetName(L"GunBox");
		//	gunBox->GetComponent<Transform>()->SetPosition(Vector3(3.f, 3.f, 0.f));
		//	gunBox->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f,0.f));



		//	PlayerHand* hand = object::Instantiate<PlayerHand>(eLayerType::Hand, this);
		//	hand->SetName(L"PHand");
		//	hand->SetPlayer(player);

		//	Gun *gun = object::Instantiate<Gun>(eLayerType::Hand, this);
		//	gun->SetName(L"PGun");
		//	gun->SetHand(hand);
		//	gun->SetPool(pool);
		//	gun->SetGunBox(gunBox);
		//	gun->SetPlayer(player);
		//}



		{
				player = object::Instantiate<CharacterBase>(eLayerType::Player, this);
				player->SetName(L"Player");
				player->GetComponent<Convict>()->SetHeart_UI(HeartControl);

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
			
			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(10.f, 10.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);
		}

		{

			MonsterBase* BossMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			BossMonster->AddComponent<Boss>();
			Transform* bossTr = BossMonster->GetComponent<Transform>();
			BossMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCol = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCol->SetName(L"Boss");

			Collider2D* mCollider = chaseCol->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(15.f, 15.f));

			chaseCol->SetOwnerTransform(bossTr);
			BossMonster->SetMonsterChaseCollider(chaseCol);
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
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Vector3 mouse = Input::GetWorldMousPosition();
			Vector2 mouse2 = Input::GetWorldMousPosition2();
			Vector3 chara = player->GetComponent<Transform>()->GetPosition();
 			int b = 0;
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
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Wall);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MonsterBullet);
		CollisionManager::CollisionLayerCheck(eLayerType::Wall, eLayerType::MonsterBullet);
		CollisionManager::CollisionLayerCheck(eLayerType::Wall, eLayerType::Weapone);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MonsterCollider);
		

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
			mapTr->SetScale(Vector3(50.0f, 62.91f, 0.1f));
		}
#pragma region 콜라이더
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-17.95f, -8.65f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.8f, 4.73f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-12.18f, -8.685f, 0.0f));
			mapColliderTr->SetScale(Vector3(3.838f, 4.7f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-12.18f, -8.685f, 0.0f));
			mapColliderTr->SetScale(Vector3(3.838f, 4.7f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-7.44f, -12.3f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.7f, 4.12f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-0.849f, -12.72f, 0.0f));
			mapColliderTr->SetScale(Vector3(7.61f, 1.44f, 1.0f));

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
			mapColliderTr->SetPosition(Vector3(-12.5f, -8.f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.2f, 0.75f, 0.1f));
		}

		{//책상
			GameObject* tableObject = object::Instantiate<TableObject>(eLayerType::Object, this);
			tableObject->SetName(L"table1");

			Transform* mapColliderTr = tableObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-15.5f, -8.0f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.2f, 0.75f, 0.1f));
		}

		{//책상
			GameObject* tableObject = object::Instantiate<TableObject>(eLayerType::Object, this);
			tableObject->SetName(L"table1");

			Transform* mapColliderTr = tableObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-12.5f, -13.0f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.2f, 0.75f, 0.1f));
		}


	}



}
