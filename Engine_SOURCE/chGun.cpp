#include "chGun.h"
#include "chSpriteRenderer.h"
#include "chResources.h"
#include "chInput.h"
#include "chPistolScr.h"
#include "BasicGunScript.h"
#include "chFightSabreObject.h"
#include "chFightSabreScr.h"
#include "chBullet.h"
#include "chBulletScr.h"
#include "chtestBulletscr.h"
#include "chTime.h"


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

		this->AddComponent<Animator>();

		SpriteRenderer* sprite = this->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EmptyMaterial");
		sprite->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sprite->SetMesh(mesh);


		BasicGunScript* Scr1 = this->AddComponent<BasicGunScript>();
		Scr1->SetpistolHand(GetHand());
		Scr1->SetpistolPool(GetPool());
		Scr1->SetGunBox(GetGunBox());

		FightSabreScr* Scr2 = this->AddComponent<FightSabreScr>();
		Scr2->SetpistolHand(GetHand());
	
		this->GetComponent<FightSabreScr>()->FightSabreOff();



		
		GameObject::Initalize();
	}
	void Gun::Update()
	{
		if (Input::GetKeyDown(eKeyCode::E)) //������ �Դ� Ű e
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
			this->GetComponent<FightSabreScr>()->FightSabreOff();
			this->GetComponent<BasicGunScript>()->PistolOn();
			
		}
		if (Input::GetKeyDown(eKeyCode::NUM_2))
		{
			this->GetComponent<BasicGunScript>()->PistolOff();
			this->GetComponent<FightSabreScr>()->FightSabreOn();
			
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