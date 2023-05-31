#include "Bullet_Kin_Gun_Scr.h"
#include "Bullet_Kin_Gun.h"
#include "Bullet_Kin.h"
namespace ch 
{
	Bullet_Kin_Gun_Scr::Bullet_Kin_Gun_Scr()
	{
	}
	Bullet_Kin_Gun_Scr::~Bullet_Kin_Gun_Scr()
	{
	}
	void Bullet_Kin_Gun_Scr::Initalize()
	{
		anima = GetOwner()->GetComponent<Animator>();

		anima->Play(L"WGun_Idle");

		thisTrans = GetOwner()->GetComponent<Transform>();

		Owner = dynamic_cast<Bullet_Kin_Gun*>(GetOwner());
		
	}
	void Bullet_Kin_Gun_Scr::Update()
	{
		if (Owner->GetOwnerMonster()->GetComponent<Bullet_Kin>()->GetShot() == true) 
		{
			Owner->GetOwnerMonster()->GetComponent<Bullet_Kin>()->SetShot(false);
			Shot();
		}
	}
	void Bullet_Kin_Gun_Scr::FixedUpdate()
	{
	}
	void Bullet_Kin_Gun_Scr::Render()
	{
	}
	void Bullet_Kin_Gun_Scr::OnCollisionEnter(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnCollision(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnCollisionExit(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnTriggerEnter(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnTrigger(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::OnTriggerExit(Collider2D* oppo)
	{
	}
	void Bullet_Kin_Gun_Scr::Shot()
	{
		Animator* monsterGunAni = GetOwner()->GetComponent<Animator>();
		monsterGunAni->Play(L"WGun_Shot",false);


	}
}