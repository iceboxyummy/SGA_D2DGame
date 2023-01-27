struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float2 uv : TEXCOORD0;
};

cbuffer CameraBuffer : register(b0)
{
	matrix view;
	matrix projection;
}

cbuffer TransformBuffer : register(b1)
{
	matrix world;
}

cbuffer AnimationBuffer : register(b2)
{
    float2 sprite_offset;
    float2 sprite_size;
    float2 texture_size;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.uv = input.uv;
	
    output.uv *= sprite_size / texture_size;
    output.uv += sprite_offset / texture_size;

	return output; 
}

Texture2D source_texture : register(t0);
SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
	return source_texture.Sample(samp, input.uv);
}
