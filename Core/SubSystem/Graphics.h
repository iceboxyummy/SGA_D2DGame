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
	ID3D11Device*			device = nullptr;				// DX에서 사용할 자원 생성
	ID3D11DeviceContext*	device_context = nullptr;		// 파이프 라인에 연결할 때 사용
	IDXGISwapChain*			swap_chain = nullptr;			// 더블 버퍼링, 백버퍼 관리
	ID3D11RenderTargetView* render_target_view = nullptr;	// 도화지
	D3D11_Viewport			viewport;						// 그려질 영역
	D3DXCOLOR				clear_color = 0xff555566;		// 화면을 지울 때 초기화할 색	
};

/*
	I가 붙으면 Com interface
		- 직접 메모리에 할당할 수 없다 .
		- 할당을 요청하기 때문에 Desc(설명서)가 필요하다.
		- new나 delete를 사용하지 못하고 함수를 통해 요청한다.

	DXGI
		- DX 그래픽 하부구조
		- 그래픽 카드가 제조사마다 다르기 때문에 프로그래머가 쉽게 사용할 수 있도록 해주는 것

	SwapChain
		- 더블 버퍼링에 사용한다.
		- 백버퍼를 관리해준다.

	RenderTargetView 
		- 도화지
		- 렌더링 대상이 되는 버퍼

	VIEWPORT
		- 게임 화면에서 그림이 그려질 영역을 지정한다.

	COLOR 
		- R G B A(투명도, 선명도)
		- 0 ~ 255 범위를 0 ~ 1(정규화) 하여 관리한다.
	
*/

// Rendering Pipeline : 렌더링을 하기 위한 수행 단계
// IA - VS - RS - PS - OM
// Input Assembler
// Vertex Shader
// Rasterizer
// Pixel Shader
// Output Merger

// DirectX : GPU를 다루는 API, SDK

/*
	CPU : 대학생 8 -> 고급 작업
	GPU : 초등학생 4000 -> 간단한 작업을 처리할 때 유리(렌더링)
*/