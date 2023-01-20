#pragma once

#include "Core/SubSystem/ISubsystem.h"

enum class RenderableType :uint
{
	Opaque,
	Camera
};

class Renderer : public ISubsystem
{
public:
	using ISubsystem::ISubsystem; 
	~Renderer();

	virtual bool Initialize() override;
	virtual void Update() override;

	void UpdateRenderables(class Scene* const scene);

private:
	void PassMain();

private:
	class Graphics* graphics = nullptr;
	class CameraComponent* camera = nullptr;
	std::shared_ptr<class D3D11_Pipeline> pipeline;

private:
	std::unordered_map<RenderableType, std::vector<class Actor*>>renderables;
};