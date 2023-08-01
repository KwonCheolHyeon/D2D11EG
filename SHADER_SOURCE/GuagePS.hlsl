#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_Target
{
    float bossGauge = 0.0f;

    bossGauge = bossHpCB;
    
    //bossGauge = 0.7;
    if (bossGauge <= In.UV.x)
        discard;
    
    float4 color = (float) 0.0f;
    color = defaultTexture.Sample(anisotropicSampler, In.UV);
    
    if (color.a <= 0.1f)
        discard;
    
    return color;
}