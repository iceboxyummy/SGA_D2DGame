#include "stdafx.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

void CameraComponent::Initialize()
{
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void CameraComponent::Update()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void CameraComponent::Destroy()
{
}

void CameraComponent::UpdateViewMatrix()
{
	D3DXVECTOR3 position = transform->GetPosition();
	D3DXVECTOR3 at = position + transform->GetForward();
	D3DXVECTOR3 up = transform->GetUp();

	D3DXMatrixLookAtLH(&view, &position, &at, &up);
}

void CameraComponent::UpdateProjectionMatrix()
{
	D3DXMatrixOrthoLH(&projection, Settings::Get().GetWidth(), Settings::Get().GetHeight(), 0.0, 1.0f);
}

void CameraComponent::UpdateConstantBuffer()
{
	if (gpu_buffer == nullptr)
	{
		gpu_buffer = std::make_shared<D3D11_ConstantBuffer>(context->GetSubsystem<Graphics>());
		gpu_buffer->Create<CAMERA_DATA>();
	}

	CAMERA_DATA* buffer = gpu_buffer->Map<CAMERA_DATA>();
	{
		D3DXMatrixTranspose(&buffer->view, &view);
		D3DXMatrixTranspose(&buffer->projection, &projection);
	}
	gpu_buffer->Unmap();
}