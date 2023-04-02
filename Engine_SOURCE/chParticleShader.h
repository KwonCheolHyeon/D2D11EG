#pragma once
#include "chComputeShader.h"
#include "chStructedBuffer.h"

namespace ch::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetStrcutedBuffer(StructedBuffer* buffer);

	private:
		StructedBuffer* mBuffer;
	};
}