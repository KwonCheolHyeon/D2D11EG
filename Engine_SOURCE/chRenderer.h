#pragma once
#include "CommonInclude.h"
#include "chMath.h"
#include "chGraphicDevice_DX11.h"
		 
#include "chMesh.h"
#include "chShader.h"
#include "chConstantBuffer.h"
#include "chCamera.h"
#include "chLight.h"

using namespace ch::math;
using namespace ch::graphics;

namespace ch::renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};

	CBUFFER(FadeEffectCB, CBSLOT_FADEEFFECT)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		float alphaAmount;
	};

	CBUFFER(AnimationCB, CBSLOT_ANIMATION)
	{
		Vector2 leftTop;
		Vector2 size;
		Vector2 offset;
		Vector2 atlasSize;

		UINT type;
	};


	extern Vertex vertexes[4];
	extern Camera* mainCamera;
	extern ConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<Camera*> cameras[];
	extern std::vector<DebugMesh> debugMeshes;
	extern std::vector<LightAttribute> lights;

	void Initialize();
	void Render();
	void Release();

	//Renderer
	

}

