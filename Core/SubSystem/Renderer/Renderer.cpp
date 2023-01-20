#include "stdafx.h"
#include "Renderer.h"
#include"Scene/Actor.h"
#include"Scene/Scene.h"
#include"Scene/Component/CameraComponent.h"
#include"Scene/Component/TransformComponent.h"

#include"Renderer_ConstantBuffers.h"

Renderer::~Renderer()
{
}

bool Renderer::Initialize()
{
    graphics = context->GetSubsystem<Graphics>();
    graphics->CreateBackBuffer(
        static_cast<uint>(Settings::Get().GetWidth()),
        static_cast<uint>(Settings::Get().GetWidth())
    );

    pipeline = std::make_shared<D3D11_Pipeline>(graphics);

    return true;
}

void Renderer::Update()
{
}

void Renderer::UpdateRenderables(Scene* const scene)
{
    renderables[RenderableType::Camera].clear();
    renderables[RenderableType::Opaque].clear();

    auto actors = scene->GetActors();

    if (actors.empty() == true) return;
}