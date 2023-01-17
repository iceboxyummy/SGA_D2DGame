#pragma once
#include "IComponent.h"

struct CAMERA_DATA
{
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

class CameraComponent final : public IComponent
{
public:
	using IComponent::IComponent;
	~CameraComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	const D3DXMATRIX& GetViewMatrix() const { return view; }
	const D3DXMATRIX& GetProjectionMatrix() const { return projection; }

	//TODO:
	std::shared_ptr<D3D11_ConstantBuffer> GetConstantBuffer() const { return gpu_buffer; }
	void UpdateConstantBuffer();

private:
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

private:
	D3DXMATRIX view;
	D3DXMATRIX projection;

	std::shared_ptr<class D3D11_ConstantBuffer> gpu_buffer;
};

