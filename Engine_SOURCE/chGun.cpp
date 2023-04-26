#include "chGun.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chInput.h"
#include "chPistol.h"
#include "chPistolScr.h"
#include "chFightSabreObject.h"
#include "chFightSabreScr.h"
#include "chBullet.h"
#include "chBulletScr.h"
#include "chtestBulletscr.h"
#include "chTime.h"
#include "chScene.h"
#include "chSceneManager.h"
#include "chPlayScene.h"

namespace ch 
{
	
	Gun::Gun()
	{
		
	}
	Gun::~Gun()
	{
		
	}
	void Gun::Initalize()
	{

		Pistol* pis = new Pistol();
		pis->AddComponent<PistolScr>();
		pis->GetComponent<PistolScr>()->SetpistolHand(GetHand());
		pis->GetComponent<PistolScr>()->SetpistolPool(GetPool());
		pis->GetComponent<PistolScr>()->SetGunBox(GetGunBox());
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(pis, eLayerType::Weapone);
		Guns.push_back(pis);//Guns[0] == 피스톨;


		//FightSabreObject* fightsabre = new FightSabreObject();
		//fightsabre->AddComponent<FightSabreScr>();
		//fightsabre->GetComponent<FightSabreScr>()->SetPlayer(GetPlayer());
		//fightsabre->GetComponent<FightSabreScr>()->SetpistolPool(GetPool());
		//fightsabre->GetComponent<FightSabreScr>()->SetGunBox(GetGunBox());
		//fightsabre->GetComponent<FightSabreScr>()->Initalize();
		//Guns.push_back(fightsabre);//Guns[1] == 파이트 사브레


		GameObject::Initalize();
	}
	void Gun::Update()
	{
		if (Input::GetKeyDown(eKeyCode::E)) //아이템 먹는 키 e
		{
		
		}
		SwapGun();

		GameObject::Update();
	}
	void Gun::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Gun::Render()
	{
		GameObject::Render();
	}
	
	void Gun::SwapGun()
	{
		if (Input::GetKeyDown(eKeyCode::NUM_1)) 
		{
			Guns[0]->GetComponent<PistolScr>()->pistolState.active = true;
			Guns[1]->GetComponent<FightSabreScr>()->pistolState.active = false;
		
		}
		if (Input::GetKeyDown(eKeyCode::NUM_2))
		{
			Guns[0]->GetComponent<PistolScr>()->pistolState.active = false;
			Guns[1]->GetComponent<FightSabreScr>()->pistolState.active = true;
		}
		if (Input::GetKeyDown(eKeyCode::NUM_3))
		{
			
		}
	
	}
	void Gun::angleFind()
	{
	
	}

	void Gun::HandDownAnimate(Vector3 handPos)
	{
	

	}

	void Gun::HandUpAnimate(Vector3 handPos)
	{
	

	}

	void Gun::HandDownPos(float cur)
	{
		
	}

	void Gun::HandUpPos(float cur)
	{
		
	}

	

	void Gun::GunLookCursor()
	{

	
	}


	
	 
	


}