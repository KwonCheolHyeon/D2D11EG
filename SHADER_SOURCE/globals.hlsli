
cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

cbuffer Grid : register(b2) 
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}

cbuffer Animation : register(b3)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}

cbuffer FadeEffect : register(b4) //16����
{
    float4 cameraPos;
    float2 cameraSca;
    float alphaAmount;
};

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

Texture2D defaultTexture : register(t0);
//Texture2D defaultTexture2 : register(t1);
//Texture2D defaultTexture3 : register(t2);

Texture2D atlasTexture : register(t12);