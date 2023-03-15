#pragma once
#include "..\External\DirectXTex\Include\DirectXTex.h"
#include "chResource.h"
#include "chGraphicDevice_DX11.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib") 
#else 
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib") 
#endif


using namespace ch::enums;
namespace ch::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		static void Clear(UINT startSlot);
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT slot);
		void Clear();

		size_t GetHeight() { return mImage.GetMetadata().height; }
		size_t GetWidth() { return mImage.GetMetadata().width; }

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};

}
