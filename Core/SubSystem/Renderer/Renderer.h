#pragma once

#include "Core/SubSystem/ISubsystem.h"

#include"Renderer_ConstantBuffers.h"
#include"Renderer_Types.h"

class Renderer : public ISubsystem
{
public:
	using ISubsystem::ISubsystem; 
	~Renderer();
	virtual bool Initialize() override;
	virtual void Update() override;

	void UpdateRenderables(class Scene* const scene);

private:

	void CreateConstantbuffers();
	void CreateRasterizerStates();
	void CreateBlendStates();

	void UpdateCameraBuffer();
	void UpdateObjectBuffer();

private:
	void PassMain();

private:
	class Graphics* graphics = nullptr;
	class CameraComponent* camera = nullptr;
	std::shared_ptr<class D3D11_Pipeline> pipeline;

	CAMERA_DATA cpu_camera_buffer;
	std::shared_ptr<class D3D11_ConstantBuffer> gpu_camera_buffer;

	TRANSFORM_DATA cpu_object_buffer;
	std::shared_ptr<class D3D11_ConstantBuffer> gpu_object_buffer;

private:
	std::map<RasterizerStateType, std::shared_ptr<class D3D11_RasterizerState>> rasterizers;
	std::map<BlendStateType, std::shared_ptr<class D3D11_Blend_state>> blend_states;

	std::unordered_map<RenderableType, std::vector<class Actor*>>renderables;
};