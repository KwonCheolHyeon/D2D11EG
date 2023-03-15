#pragma once
#include "chComponent.h"
#include "chMesh.h"
#include "chMaterial.h"

namespace ch
{
	class BaseRenderer : public Component
	{
	public:
		BaseRenderer(eComponentType type);
		virtual ~BaseRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr <Material> shader) { mMaterial = shader; }
		std::shared_ptr<Mesh> GetMesh() { return mMesh; }
		std::shared_ptr <Material> GetMaterial() { return mMaterial; }

		void ChangeSize() { mbIsChanged = true; }
	private:
		std::shared_ptr <Mesh> mMesh;
		std::shared_ptr <Material> mMaterial;

		float mWidthRatio;
		float mHeightRatio;

		bool mbIsChanged;
		bool mbIsAnim;

		Vector2 mSpriteSize;
	};
}
