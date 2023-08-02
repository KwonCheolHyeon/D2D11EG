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


float3 convertRgbToLinearRgb(const float3 rgb)
{
    return pow(rgb, float3(2.2, 2.2, 2.2));
}

float3 convertLinearRgbToRgb(const float3 linear_rgb)
{
    return pow(linear_rgb, float3(1.0 / 2.2, 1.0 / 2.2, 1.0 / 2.2));
}

float3 applyBrightnessEffect(const float3 linear_rgb, const float brightness)
{
    const float scale = 20.0; // Adjust this scale value for different brightness intensity
    return linear_rgb * (1.0 + brightness * scale);
}

float3 enhance(float3 color, float brightness)
{
    // Retrieve enhancement parameters
    brightness = saturate(brightness - 0.5);

    float3 linear_rgb = convertRgbToLinearRgb(color);

    // Brightness
    linear_rgb = applyBrightnessEffect(linear_rgb, brightness);

    return saturate(convertLinearRgbToRgb(linear_rgb));
}

float4 main(VSIn In) : SV_Target
{
    // Get brightness value from the constant buffer
    float bright = brightnessCB1;

    // Sample the texture color
    float4 color = defaultTexture.Sample(pointSampler, In.UV);

    // Apply brightness enhancement
    color.rgb = enhance(color.rgb, bright);
   

    return color;
    
}