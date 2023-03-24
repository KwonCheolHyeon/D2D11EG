#include "chPaintShader.h"


namespace ch::graphics
{
	PaintShader::PaintShader()
		: ComputeShader()
		, mTarget(nullptr)
	{
	}

	PaintShader::~PaintShader()
	{
	}

	void PaintShader::Binds()
	{
		mTarget->BindUnorderedAccessView(0);

		mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1;//mTarget->GetWidth���� �����ϸ� �������� ���� �� �� �ִ�.
		mGroupY = mTarget->GetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}

	void PaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessView(0);
	}

}
