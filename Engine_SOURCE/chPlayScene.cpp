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
#include "ItemBoxScr.h"
#include "DoorObj.h"
#include "DoorScr.h"
#include "DoorColliderObj.h"



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

		generateObject();

		{
				player = object::Instantiate<CharacterBase>(eLayerType::Player, this);
				player->SetName(L"Player");
				player->GetComponent<Convict>()->SetHeart_UI(HeartControl);

				GameObject* gunBox = object::Instantiate<GameObject>(eLayerType::Weapone, this);
				gunBox->SetName(L"GunBox");
				gunBox->GetComponent<Transform>()->SetPosition(Vector3(-16.1f, -3.23f, 0.f));
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
#pragma region 스테이지1 몬스터
		{// 스테이지1 몬스터1
			
			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-4.86f, 11.44f, 0.1f));
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

			mainDoor1->SetMonsterBases(kinMonster);
		}
		{//스테이지1 몬스터2

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-7.86f, 5.44f, 0.1f));
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

			mainDoor1->SetMonsterBases(kinMonster);
		}
		{//스테이지1 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-6.86f, 9.44f, 0.1f));
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

			mainDoor1->SetMonsterBases(kinMonster);
		}
#pragma endregion

#pragma region 스테이지2 몬스터
		{//스테이지1 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-21.14f,5.77f, 0.1f));
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

			mainDoor2->SetMonsterBases(kinMonster);
		}
#pragma endregion

#pragma region 스테이지3 몬스터
		{//스테이지3 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(11.45f, 1.86f, 0.1f));
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

			mainDoor3->SetMonsterBases(kinMonster);
		}
		{//스테이지3 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(13.05f, -0.15f, 0.1f));
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

			mainDoor3->SetMonsterBases(kinMonster);
		}
		{//스테이지3 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(15.9f, 2.f, 0.1f));
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

			mainDoor3->SetMonsterBases(kinMonster);
		}

#pragma endregion


#pragma region 스테이지4 몬스터
		{//스테이지4 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(12.45f, -11.23f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);

			mainDoor4->SetMonsterBases(kinMonster);
		}
		{//스테이지3 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(12.45f, -11.53f, 0.1f));
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

			mainDoor4->SetMonsterBases(kinMonster);
		}
		

#pragma endregion

#pragma region 스테이지5 몬스터
		{//스테이지5 몬스터3

			MonsterBase* kinMonster = object::Instantiate<MonsterBase>(eLayerType::Monster, this);
			kinMonster->AddComponent<Bullet_Kin>();
			Transform* kinTransform = kinMonster->GetComponent<Transform>();
			kinTransform->SetPosition(Vector3(-13.7f, -15.046f, 0.1f));
			kinMonster->SetPlayer(player);

			chasePlayerOBJ* chaseCollier = object::Instantiate<chasePlayerOBJ>(eLayerType::MonsterCollider, this);
			chaseCollier->SetName(L"most");

			Collider2D* mCollider = chaseCollier->AddComponent<Collider2D>(); //오류 걸림
			mCollider->SetName(L"BossChaseCollider");
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(6.f, 6.f));

			chaseCollier->SetOwnerTransform(kinTransform);
			kinMonster->SetMonsterChaseCollider(chaseCollier);

			Bullet_Kin_Gun* gun = object::Instantiate<Bullet_Kin_Gun>(eLayerType::Dummy, this);
			gun->SetOwnerMoster(kinMonster);

			mainDoor5->SetMonsterBases(kinMonster);
		}


#pragma endregion

		{ //보스

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
			mapTr->SetPosition(Vector3(0.0f, 0.0f, 5.1f));
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

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-7.47f, -17.145f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.64f, 3.55f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-13.05f, -21.057f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.975f, 4.686f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-18.3945f, -21.0669f, 0.0f));
			mapColliderTr->SetScale(Vector3(2.789f, 4.6482f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-19.045f, -14.8275f, 0.0f));
			mapColliderTr->SetScale(Vector3(2.201f, 8.075f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(5.8106f, -17.952f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.6181f, 5.136f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}


		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(8.466f, -18.15f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.312f, 4.718f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(1.51025f, -25.133133f, 0.0f));
			mapColliderTr->SetScale(Vector3(3.7605f, 9.209f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-1.6754f, -21.2955f, 0.0f));
			mapColliderTr->SetScale(Vector3(9.5908f, 8.039f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(5.79209f, -11.289675f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.68518f, 6.2085f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(6.2376f, -5.59004f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.6972f, 5.17090661f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(11.66f, -5.833f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.3071f, 4.7041f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(13.27f, -18.19995f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.4287f, 4.7f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(16.34f, -5.861f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.14f, 4.763f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(16.8244f, -11.832f, 0.0f));
			mapColliderTr->SetScale(Vector3(1.1668f, 9.062f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}


		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(7.28f, -28.73645f, 0.0f));
			mapColliderTr->SetScale(Vector3(8.164f, 1.0171f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(11.2755f, -24.11525f, 0.0f));
			mapColliderTr->SetScale(Vector3(0.581f, 8.2049f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(17.0536f, 0.3545f, 0.0f));
			mapColliderTr->SetScale(Vector3(0.6872f, 7.693f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(11.7725f, 6.32398f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.095f, 4.17116f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(6.2575f, 3.2f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.675f, 10.43256f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(17.3671f, 6.274f, 0.0f));
			mapColliderTr->SetScale(Vector3(3.2342f, 4.24472f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}


		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(10.245f, 14.5855f, 0.0f));
			mapColliderTr->SetScale(Vector3(9.07f, 4.74f, 1.0f));

			Collider2D* mapCollider = mapColliderObject->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}

		{
			GameObject* mapColliderObject = object::Instantiate<GameObject>(eLayerType::Wall, this);
			mapColliderObject->SetName(L"MapWall");

			Transform* mapColliderTr = mapColliderObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(20.1622f, 14.5957f, 0.0f));
			mapColliderTr->SetScale(Vector3(8.8444f, 4.704f, 1.0f));

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


		


		{//스테이지 1 문
			mainDoor1 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor1->SetName(L"DoorSide");

			mainDoor1->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor1->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-9.57f, 14.34f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol");
			DoorColObject->SetDoor(mainDoor1);

			mainDoor1->isMainDoorTrue();
		}

		{//문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-0.8f, 3.5f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}
		{//문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorSide");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-9.6f, 7.2f, -1.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));
		}
		
		{//스테이지2 문
			mainDoor2 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor2->SetName(L"DoorSide");

			mainDoor2->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor2->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-14.9f, 7.2f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol");
			DoorColObject->SetDoor(mainDoor2);

			mainDoor2->isMainDoorTrue();
		}

		{//스테이지3 문
			mainDoor3 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor3->SetName(L"DoorSide");

			mainDoor3->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor3->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(8.955f, -1.34f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol");
			DoorColObject->SetDoor(mainDoor3);

			mainDoor3->isMainDoorTrue();
		}
		{//문3
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(15.32f, 5.73f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}
		{//문3
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(15.32f, -2.92f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}

		{//스테이지4 문1
			mainDoor4 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor4->SetName(L"DoorFront");

			mainDoor4->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor4->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(15.31f, -6.7f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol");
			DoorColObject->SetDoor(mainDoor4);

			mainDoor4->isMainDoorTrue();
		}

		{//스테이지4 문3
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(9.661f, -15.3f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}

		{//스테이지4  문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorSide");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(8.471f,-13.73f, -1.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));
		}



		{//스테이지5 문
			mainDoor5 = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			mainDoor5->SetName(L"DoorSide");

			mainDoor5->AddComponent<DoorScr>();

			Transform* mapColliderTr = mainDoor5->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-10.24f, -14.05f, 0.0f));
			mapColliderTr->SetScale(Vector3(5.f, 5.f, 0.1f));

			DoorColliderObj* DoorColObject = object::Instantiate<DoorColliderObj>(eLayerType::MonsterCollider, this);
			DoorColObject->SetName(L"DoorSideCol");
			DoorColObject->SetDoor(mainDoor5);

			mainDoor5->isMainDoorTrue();
		}
		{//스테이지5 문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-14.6f, -9.6f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}
		{//스테이지5 문
			DoorObj* DoorObject = object::Instantiate<DoorObj>(eLayerType::Wall, this);
			DoorObject->SetName(L"DoorFront");

			DoorObject->AddComponent<DoorScr>();

			Transform* mapColliderTr = DoorObject->GetComponent<Transform>();
			mapColliderTr->SetPosition(Vector3(-16.5f, -18.23f, 0.0f));
			mapColliderTr->SetScale(Vector3(6.f, 5.f, 0.1f));
		}



		{//itemBox
			GameObject* itemGunBox = object::Instantiate<GameObject>(eLayerType::Object, this);
			itemGunBox->AddComponent<ItemBoxScr>();

			Transform* itemTr = itemGunBox->GetComponent<Transform>();
			itemTr->SetPosition(Vector3(-16.84f, -4.f, 0.1f));
			itemTr->SetScale(Vector3(5.f, 5.f, 1.f));
		}

	}



}
