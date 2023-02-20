#include "chSceneManager.h"
#include "chTransform.h"
#include "chMeshRenderer.h"
#include "chRenderer.h"
#include "chResources.h"
#include "chTexture.h"
#include "chPlayerScript.h"
#include "chCamera.h"
#include "chCameraScript.h"
#include "chSpriteRenderer.h"

namespace ch
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initalize()
	{
		mActiveScene = new Scene();
		mActiveScene->Initalize();

		// Camera Game Object
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraObj->AddComponent(cameraComp);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		CameraScript* cameraScript = new CameraScript();
		cameraObj->AddComponent(cameraScript);
		mActiveScene->AddGameObject(cameraObj, eLayerType::Camera);

		GameObject* cameraUIObj = new GameObject();
		Transform* cameraUITr = new Transform();
		cameraUITr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraUIObj->AddComponent(cameraUITr);
		Camera* cameraUIComp = new Camera();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIObj->AddComponent(cameraUIComp);
		mActiveScene->AddGameObject(cameraUIObj, eLayerType::Camera);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		// Light Object
		GameObject* spriteObj = new GameObject();
		spriteObj->SetName(L"LIGHT");
		Transform* spriteTr = new Transform();
		spriteTr->SetPosition(Vector3(0.0f, 0.0f, 11.0f));
		spriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		spriteObj->AddComponent(spriteTr);

		SpriteRenderer* sr = new SpriteRenderer();
		spriteObj->AddComponent(sr);

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");

		//Vector2 vec2(1.0f, 1.0f);
		//spriteMaterial->SetData(eGPUParam::Vector2, &vec2);

		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);

		mActiveScene->AddGameObject(spriteObj, eLayerType::Player);

		//SMILE RECT
		GameObject* obj = new GameObject();
		obj->SetName(L"SMILE");
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(-3.0f, 0.0f, 11.0f));
		tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.0f, 1.0f);
		mateiral->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMaterial(mateiral);
		mr->SetMesh(mesh);

		PlayerScript* playerScript = new PlayerScript();
		obj->AddComponent(playerScript);
		mActiveScene->AddGameObject(obj, eLayerType::Player);

		//SMILE RECT CHild
		GameObject* child = new GameObject();
		child->SetName(L"SMILE");
		Transform* childTr = new Transform();
		childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		child->AddComponent(childTr);
		childTr->SetParent(tr);

		MeshRenderer* childMr = new MeshRenderer();
		child->AddComponent(childMr);




		std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");

		childMr->SetMaterial(childmateiral);
		childMr->SetMesh(mesh);

		mActiveScene->AddGameObject(child, eLayerType::Player);

		// HPBAR
		GameObject* hpBar = new GameObject();
		hpBar->SetName(L"HPBAR");
		Transform* hpBarTR = new Transform();
		hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 12.0f));
		hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		hpBar->AddComponent(hpBarTR);

		SpriteRenderer* hpsr = new SpriteRenderer();
		hpBar->AddComponent(hpsr);

		std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
		//.std::shared_ptr <Texture> hpTexture = Resources::Find<Texture>(L"HPBarTexture");
		//spriteMaterial->SetTexture(hpTexture);

		hpsr->SetMesh(hpmesh);
		hpsr->SetMaterial(hpspriteMaterial);
		mActiveScene->AddGameObject(hpBar, eLayerType::UI);

		mActiveScene->Initalize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	void SceneManager::Release()
	{
		delete mActiveScene;
		mActiveScene = nullptr;
	}
}