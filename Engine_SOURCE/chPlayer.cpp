#include "chPlayer.h"
#include "chPlayerScript.h"
#include "chSpriteRenderer.h"
#include "chAnimator.h"
#include "chResources.h"
#include "chMesh.h"
namespace ch
{
	Player::Player()
	{
		SetLayerType(eLayerType::Player);
		this->AddComponent<PlayerScript>();

		GameObject* playerObj = dynamic_cast<GameObject*>(this);

		Collider2D* coll = playerObj->AddComponent<Collider2D>();
		coll->SetName(L"_player");
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(0.3f, 0.2f));

		SpriteRenderer* SpRenderer = playerObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> standmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> standmaterial = Resources::Find<Material>(L"pIdleMaterial");
		SpRenderer->SetMaterial(standmaterial);
		SpRenderer->SetMesh(standmesh);

		Animator* animator = playerObj->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Zelda.png");
		animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 3, 0.1f);
		animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);

		animator->Play(L"Idle", true);

		/*SpriteRenderer* mr = playerObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);*/
		
	}

	Player::~Player()
	{
	}

	void Player::Initalize()
	{
		GameObject::Initalize();
	}

	void Player::Update()
	{
	
		GameObject::Update();
	}

	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}
