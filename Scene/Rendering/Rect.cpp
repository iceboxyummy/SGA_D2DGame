#include "stdafx.h"
#include "Rect.h"

Rect::Rect(Graphics* graphics, const D3DXCOLOR& color)
{

	//================================================================================================
	// [Geometry]
	//================================================================================================
	D3D11_Geometry<D3D11_VertexColor>  geometry;
	Geometry_Generator::CreateQuad(geometry, color);

	//================================================================================================
	// [Vertex Buffer]
	//================================================================================================
	vertex_buffer = new D3D11_VertexBuffer(graphics);
	vertex_buffer->Create(geometry.GetVertices());

	//================================================================================================
	// [Index Buffer]
	//================================================================================================
	index_buffer = new D3D11_IndexBuffer(graphics);
	index_buffer->Create(geometry.GetIndices());

	//================================================================================================
	// [Vertex Shader]
	//================================================================================================
	vertex_shader = new D3D11_Shader(graphics);
	vertex_shader->Create(ShaderScope_VS, "./Assets/Shader/Color.hlsl");

	//================================================================================================
	// [Pixel Shader]
	//================================================================================================
	pixel_shader = new D3D11_Shader(graphics);
	pixel_shader->Create(ShaderScope_PS, "./Assets/Shader/Color.hlsl");

	//================================================================================================
	// [InputLayout]
	//================================================================================================
	input_layout = new D3D11_InputLayout(graphics);
	input_layout->Create(D3D11_VertexColor::descs, D3D11_VertexColor::count, vertex_shader->GetShaderBlob());

	//================================================================================================
	// [Constant Buffer]
	//================================================================================================
	gpu_buffer = new D3D11_ConstantBuffer(graphics);
	gpu_buffer->Create<TRANSFORM_DATA>();

	color_buffer = new D3D11_ConstantBuffer(graphics);
	color_buffer->Create<COLOR_DATA>();

	//================================================================================================
	// [Rasterizer State]
	//================================================================================================
	rasterizer_state = new D3D11_RasterizerState(graphics);
	rasterizer_state->Create(D3D11_CULL_BACK, D3D11_FILL_SOLID);

	// Create World
	{
		D3DXMatrixIdentity(&world);

		D3DXMATRIX S;
		D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
		std::cout << std::endl;

		D3DXMATRIX T;
		D3DXMatrixTranslation(&T, position.x, position.y, position.z);

		world = S * T;
	}
}

Rect::~Rect()
{
	SAFE_DELETE(rasterizer_state);
	SAFE_DELETE(gpu_buffer);
	SAFE_DELETE(input_layout);
	SAFE_DELETE(pixel_shader);
	SAFE_DELETE(vertex_shader);
	SAFE_DELETE(index_buffer);
	SAFE_DELETE(vertex_buffer);
}

void Rect::Update()
{
	if (is_intersect == true && restore_stopwatch.GetElapsedTimeMs() >= 2000)
	{
		Restore();
		is_intersect = false;
	}

	if (is_active == false) return;

	Move();



	D3DXMATRIX S;
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	std::cout << std::endl;

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * T;

	TRANSFORM_DATA* buffer = gpu_buffer->Map<TRANSFORM_DATA>();
	{
		D3DXMatrixTranspose(&buffer->world, &world);
	}
	gpu_buffer->Unmap();

	COLOR_DATA* color_data = color_buffer->Map<COLOR_DATA>();
	{
		color_data->color = intersect_color;
	}
	color_buffer->Unmap();
}

void Rect::Render(D3D11_Pipeline* pipeline)
{
	if (is_active == false) return;

	D3D11_PipelineState pipeline_state;
	pipeline_state.input_layout = input_layout;
	pipeline_state.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	pipeline_state.vertex_shader = vertex_shader;
	pipeline_state.pixel_shader = pixel_shader;
	pipeline_state.rasterizer_state = rasterizer_state;

	if (pipeline->Begin(pipeline_state))
	{
		pipeline->SetVertexBuffer(vertex_buffer);
		pipeline->SetIndexBuffer(index_buffer);
		pipeline->SetConstantBuffer(1, ShaderScope_VS, gpu_buffer);

		pipeline->SetConstantBuffer(2, ShaderScope_PS, color_buffer);

		pipeline->DrawIndexed(
			index_buffer->GetCount(),
			index_buffer->GetOffset(),
			vertex_buffer->GetOffset()
		);

		pipeline->End();
	}
}
