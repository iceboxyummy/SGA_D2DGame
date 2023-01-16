#pragma once

struct COLOR_DATA
{
	D3DXCOLOR color;
};

struct TRANSFORM_DATA
{
	D3DXMATRIX world;
};

enum Direction
{
	MIN ,
	U	= MIN,  
	UR	,  
	R	,  
	UL	,  
	D	,  
	DL	,  
	L	,  	 
	DR	,
	MAX = DR,
	COUNT
};

class Rect 
{
public:
	Rect(Graphics* graphics, const D3DXCOLOR& color);
	virtual ~Rect();

	void Update();
	void Render(D3D11_Pipeline* pipeline);
	virtual void Event() = 0;

	void SetPosition(const D3DXVECTOR3& position) { this->position = position; }
	void SetScale(const D3DXVECTOR3& scale) { this->scale = scale; }

	const D3DXVECTOR3& GetPosition() const { return position; }
	const D3DXVECTOR3& GetScale() const { return scale; }

	void SetActive(const bool& is_active) { this->is_active = is_active; }
	const bool& IsActive() const { return is_active; }

protected:
	virtual void Move() = 0;
	virtual void Restore() = 0;

protected:
	D3D11_VertexBuffer* vertex_buffer = nullptr;
	D3D11_IndexBuffer* index_buffer = nullptr;
	D3D11_InputLayout* input_layout = nullptr;
	D3D11_Shader* vertex_shader = nullptr;
	D3D11_ConstantBuffer* gpu_buffer = nullptr;
	D3D11_RasterizerState* rasterizer_state = nullptr;
	D3D11_Shader* pixel_shader = nullptr;

	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 scale = D3DXVECTOR3(100.0f, 100.0f, 1.0f);

	D3DXMATRIX world; // 4x4

	D3DXCOLOR intersect_color = D3DXCOLOR(1, 1, 1, 1);
	D3D11_ConstantBuffer* color_buffer = nullptr;

	bool is_active = true;

	Stopwatch restore_stopwatch;

	bool is_intersect = false;
};

