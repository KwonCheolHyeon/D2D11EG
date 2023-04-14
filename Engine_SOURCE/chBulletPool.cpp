#include "chBulletPool.h"
#include "chtestBulletscr.h"
#include "chBulletScr.h"
namespace ch 
{
	BulletPool::BulletPool()
	{
	}
	
	BulletPool::~BulletPool()
	{
	}
	void BulletPool::Initalize()
	{
		pool = this;
		
		GameObject::Initalize();
	}
	void BulletPool::Update()
	{
		bulletCont = availableBullets.size();
		GameObject::Update();
	}
	void BulletPool::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void BulletPool::Render()
	{
		GameObject::Render();
	}
	
	Bullet* BulletPool::GetBullet()
	{
		if (!availableBullets.empty()) {
			// Get a pointer to the first available Bullet object
			Bullet* bullet = availableBullets.back();
			availableBullets.pop_back();
			

			return bullet;
		}
		else {//사용가능한 총알이 없다!
			// No available Bullet objects in the pool
			//Bullet* bull = new Bullet();
			//bull->AddComponent<BulletScr>();
			//bull->GetComponent<BulletScr>()->Initalize();
			return nullptr;
		}
	}
	void BulletPool::ReturnBullet(Bullet* bullet)
	{
		//초기화 시키기  bullet->


		availableBullets.push_back(bullet);
	}
}