#pragma once

#include "chComponent.h"

namespace ch 
{
	using namespace math;

	class Camera :public Component
	{
	public :
		enum  eProjectionType
		{
			Perspective,//원근
			Orthographic,//직교 투영
		};

		__forceinline static Matrix& GetViewMatrix() { return View; }
		__forceinline static Matrix& GetProjectionMatrix() { return Projection; }

		Camera();
		virtual ~Camera();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void CreateViewMatirx();
		void CreatePrjectionMatrix();
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType layer, bool enable = true);
		void EnableLayerMasks() { mLayerMasks.set(); }
		void DisableLayerMasks() { mLayerMasks.reset(); }

		void SetProjectionType(eProjectionType type) { mType = type; }

	private:
		void sortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();
		void pushGameObjectToRenderingModes(GameObject* gameObj);
	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;

		float mNear;
		float mFar;
		float mScale;

		//std::bitset<(UINT)eLayerType::End> mLayerMasks;
		std::vector<GameObject*> mOpaqueGameObjects;//불투명
		std::vector<GameObject*> mCutoutGameObjects; //불투명과 투명 사이
		std::vector<GameObject*> mTransparentGameObjects; //투명 (그림자, 반사 같은 효과)



	};

}


