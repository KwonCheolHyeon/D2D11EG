#include "chCamera.h"
#include "chTransform.h"
#include "chGameObject.h"
#include "chApplication.h"
#include "chRenderer.h"
#include "chScene.h"
#include "chSceneManager.h"
#include "chMaterial.h"
#include "chBaseRenderer.h"
#include "chSceneManager.h"

extern ch::Application application;

namespace ch
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Orthographic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mScale(1.0f)
		, mTargetOJ(nullptr)
		, mCamSpeed(1.f)
		, mCamDir(Vector3::Zero)
		, mFarDist(0.f)
		, mTime(0.3f)
		, mSmooth(false)
	{
		EnableLayerMasks();
	
	}

	Camera::~Camera()
	{
	}

	void Camera::Initalize()
	{
		
		RegisterCameraInRenderer();
	}

	void Camera::Update()
	{
		
	}

	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();

		RegisterCameraInRenderer();
	}

	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		sortGameObjects();

		renderOpaque();
		renderCutout();
		renderTransparent();
		renderPostProcess();
	}

	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// Crate Translate view matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);
		//ȸ�� ����

		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = foward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = foward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = foward.z;

		mView *= viewRotate;
	}

	void Camera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (winRect.right - winRect.left) * mScale;
		float height = (winRect.bottom - winRect.top) * mScale;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH
			(
				XM_2PI / 6.0f
				, mAspectRatio
				, mNear
				, mFar
			);
		}
		else
		{
			mProjection = Matrix::CreateOrthographicLH(width / 100 , height / 100 , mNear, mFar);
		}
	}

	void Camera::RegisterCameraInRenderer()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		renderer::cameras[(UINT)type].push_back(this);
	}

	void Camera::TurnLayerMask(eLayerType layer, bool enable)
	{
		mLayerMasks.set((UINT)layer, enable);
	}

	

	void Camera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutGameObjects.clear();
		mTransparentGameObjects.clear();
		mPostProcessGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMasks[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				GameObjects gameObjects = layer.GetGameObjects();
				if (gameObjects.size() == 0)
					continue;

				for (GameObject* obj : gameObjects)
				{

					Transform* tr = obj->GetComponent<Transform>();
					Vector3 pos = tr->GetPosition();

					Transform* camerTr = GetOwner()->GetComponent<Transform>();
					Vector3 cameraPos = camerTr->GetPosition();
					Vector2 windowSize = Vector2(1600.f, 900.f);
					windowSize += Vector2(400.f, 400.f);


					if (pos.x < cameraPos.x - (windowSize.x * 0.5f) || pos.x > cameraPos.x + (windowSize.x * 0.5f))
						continue;

					if (pos.y < cameraPos.y - (windowSize.y * 0.5f) || pos.y > cameraPos.y + (windowSize.y * 0.5f))
						continue;

					pushGameObjectToRenderingModes(obj);
				}
			}
		}
	}

	void Camera::renderOpaque()
	{
		for (GameObject* obj : mOpaqueGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderCutout()
	{
		for (GameObject* obj : mCutoutGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderTransparent()
	{
		for (GameObject* obj : mTransparentGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderPostProcess()
	{

		for (GameObject* obj : mPostProcessGameObjects)
		{
			if (obj == nullptr)
				continue;
			renderer::CopyRenderTarget();
			obj->Render();
		}
	}

	void Camera::pushGameObjectToRenderingModes(GameObject* gameObj)
	{
		BaseRenderer* renderer
			= gameObj->GetComponent<BaseRenderer>();
		if (renderer == nullptr)
			return;

		std::shared_ptr<Material> material = renderer->GetMaterial();
		//if (material == nullptr)
		//	continue;

		eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case ch::graphics::eRenderingMode::Opaque:
			mOpaqueGameObjects.push_back(gameObj);
			break;
		case ch::graphics::eRenderingMode::CutOut:
			mCutoutGameObjects.push_back(gameObj);
			break;
		case ch::graphics::eRenderingMode::Transparent:
			mTransparentGameObjects.push_back(gameObj);
			break;
		case ch::graphics::eRenderingMode::PostProcess:
			mPostProcessGameObjects.push_back(gameObj);
			break;
		default:
			break;
		}
	}
}
