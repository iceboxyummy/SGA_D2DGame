#pragma once

#include"Core/D3D11/Rasterizer/D3D11_Viewport.h"
#include"ISubSystem.h"

class Graphics final : public ISubsystem
{
public:
	using ISubsystem::ISubsystem;
	~Graphics();

	virtual bool Initialize() override;
	virtual void Update() override;

	void CreateBackBuffer(const uint& width, const uint& height);

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return device_context; }

	void Begin();
	void End();

private:
	ID3D11Device*			device = nullptr;				// DX���� ����� �ڿ� ����
	ID3D11DeviceContext*	device_context = nullptr;		// ������ ���ο� ������ �� ���
	IDXGISwapChain*			swap_chain = nullptr;			// ���� ���۸�, ����� ����
	ID3D11RenderTargetView* render_target_view = nullptr;	// ��ȭ��
	D3D11_Viewport			viewport;						// �׷��� ����
	D3DXCOLOR				clear_color = 0xff555566;		// ȭ���� ���� �� �ʱ�ȭ�� ��	
};

/*
	I�� ������ Com interface
		- ���� �޸𸮿� �Ҵ��� �� ���� .
		- �Ҵ��� ��û�ϱ� ������ Desc(����)�� �ʿ��ϴ�.
		- new�� delete�� ������� ���ϰ� �Լ��� ���� ��û�Ѵ�.

	DXGI
		- DX �׷��� �Ϻα���
		- �׷��� ī�尡 �����縶�� �ٸ��� ������ ���α׷��Ӱ� ���� ����� �� �ֵ��� ���ִ� ��

	SwapChain
		- ���� ���۸��� ����Ѵ�.
		- ����۸� �������ش�.

	RenderTargetView 
		- ��ȭ��
		- ������ ����� �Ǵ� ����

	VIEWPORT
		- ���� ȭ�鿡�� �׸��� �׷��� ������ �����Ѵ�.

	COLOR 
		- R G B A(����, ����)
		- 0 ~ 255 ������ 0 ~ 1(����ȭ) �Ͽ� �����Ѵ�.
	
*/

// Rendering Pipeline : �������� �ϱ� ���� ���� �ܰ�
// IA - VS - RS - PS - OM
// Input Assembler
// Vertex Shader
// Rasterizer
// Pixel Shader
// Output Merger

// DirectX : GPU�� �ٷ�� API, SDK

/*
	CPU : ���л� 8 -> ��� �۾�
	GPU : �ʵ��л� 4000 -> ������ �۾��� ó���� �� ����(������)
*/