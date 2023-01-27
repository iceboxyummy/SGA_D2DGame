#include "stdafx.h"
#include "MeshRendererComponent.h"

void MeshRendererComponent::Initialize()
{
	SetStandardMesh();
	SetStandardMaterial();
}

void MeshRendererComponent::Update()
{
}

void MeshRendererComponent::Destroy()
{
}

void MeshRendererComponent::SetStandardMesh()
{
	//================================================================================================
	// [Geometry]
	//================================================================================================
	D3D11_Geometry<D3D11_VertexTexture>  geometry;
	Geometry_Generator::CreateQuad(geometry);

	//================================================================================================
	// [Vertex Buffer]
	//================================================================================================
	vertex_buffer = std::make_shared<D3D11_VertexBuffer>(context->GetSubsystem<Graphics>());
	vertex_buffer->Create(geometry.GetVertices());

	//================================================================================================
	// [Index Buffer]
	//================================================================================================
	index_buffer = std::make_shared<D3D11_IndexBuffer>(context->GetSubsystem<Graphics>());
	index_buffer->Create(geometry.GetIndices());
}

void MeshRendererComponent::SetStandardMaterial()
{
	//================================================================================================
	// [Vertex Shader]
	//================================================================================================
	vertex_shader = std::make_shared<D3D11_Shader>(context->GetSubsystem<Graphics>());
	vertex_shader->Create(ShaderScope_VS, "./Assets/Shader/Animation.hlsl");

	//================================================================================================
	// [Pixel Shader]
	//================================================================================================
	pixel_shader = std::make_shared<D3D11_Shader>(context->GetSubsystem<Graphics>());
	pixel_shader->Create(ShaderScope_PS, "./Assets/Shader/Animation.hlsl");

	//================================================================================================
	// [InputLayout]
	//================================================================================================
	input_layout = std::make_shared<D3D11_InputLayout>(context->GetSubsystem<Graphics>());
	input_layout->Create(D3D11_VertexTexture::descs, D3D11_VertexTexture::count, vertex_shader->GetShaderBlob());
}