#pragma once
#include "chBaseRenderer.h"
#include "chParticleShader.h"

namespace ch
{
	class ParticleSystem : public BaseRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		class StructedBuffer* mBuffer;
		std::shared_ptr<graphics::ParticleShader> mCS;

		UINT mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mStartLifeTime;
	};
}
