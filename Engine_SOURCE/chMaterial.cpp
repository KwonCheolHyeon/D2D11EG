#include "chMaterial.h"
#include "chResources.h"

namespace ch::graphics
{
    Material::Material()
        : Resource(eResourceType::Material)
        , mMode(eRenderingMode::Opaque)
    {

    }
    Material::Material(std::wstring _TextureName, std::wstring _ShaderName)
        : Resource(eResourceType::Material)
        , mMode(eRenderingMode::Transparent)
    {
        mTexture = Resources::Find<Texture>(_TextureName);
        mShader = Resources::Find<Shader>(_ShaderName);
    }

    Material::~Material()
    {

    }

    HRESULT Material::Load(const std::wstring& path)
    {



        return E_NOTIMPL;
    }

    void Material::SetData(eGPUParam param, void* data)
    {
        switch (param)
        {
        case ch::graphics::eGPUParam::Int:
            mCB.iData = *static_cast<int*>(data);
            break;
        case ch::graphics::eGPUParam::Float:
            mCB.fData = *static_cast<float*>(data);
            break;
        case ch::graphics::eGPUParam::Vector2:
            mCB.xy = *static_cast<Vector2*>(data);
            break;
        case ch::graphics::eGPUParam::Vector3:
            mCB.xyz = *static_cast<Vector3*>(data);
            break;
        case ch::graphics::eGPUParam::Vector4:
            mCB.xyzw = *static_cast<Vector4*>(data);
            break;
        case ch::graphics::eGPUParam::Matrix:
            mCB.matrix = *static_cast<Matrix*>(data);
            break;
       
        default:
            break;
        }

    }

    void Material::Bind()
    {
        if (mTexture)
            mTexture->BindShader(eShaderStage::PS, 0);

        ConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::Material];
        pCB->SetData(&mCB);
        pCB->Bind(eShaderStage::VS);
        pCB->Bind(eShaderStage::PS);

        mShader->Binds();
    }

    void Material::Clear()
    {
        mTexture->Clear();
    }
}