#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"
#include "Scene/Actor.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/AiScriptComponent.h"

Execute::Execute()
{
	Graphics::Get().Initialize();
	Graphics::Get().CreateBackBuffer
	(
		static_cast<uint>(Settings::Get().GetWidth()),
		static_cast<uint>(Settings::Get().GetHeight())
	);

	// ===============================================
	// [Actor]
	// ===============================================

	// 카메라
	std::shared_ptr<Actor> camera = CreateActor();
	camera->AddComponent<CameraComponent>();
	camera->SetName("MainCamera");

	// 플레이어
	std::shared_ptr<Actor> player = CreateActor();
	player->AddComponent<MeshRendererComponent>();
	player->AddComponent<MoveScriptComponent>();

	player->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(100.0f, 100.0f, 1.0f));
	player->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(100.0f, 100.0f, 1.0f));

	// 몬스터

	std::shared_ptr<Actor> monster = CreateActor();
	monster->AddComponent<MeshRendererComponent>();
	monster->AddComponent<AiScriptComponent>();

	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(100.0f, 100.0f, 1.0f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-100.0f, 100.0f, 1.0f));

	// ===============================================
	// [Pipeline]
	// ===============================================
	pipeline = std::make_shared<D3D11_Pipeline>(&Graphics::Get());
}

Execute::~Execute()
{
}

void Execute::Update()
{
	for (const auto& actor : actors)
		actor->Update();
}

void Execute::Render()
{
	Graphics::Get().Begin();
	{
		for (const auto& actor : actors)
		{
			if(auto camera = actor->GetComponent<CameraComponent>())
			{
				camera->UpdateConstantBuffer();
				pipeline->SetConstantBuffer(0, ShaderScope_VS, camera->GetConstantBuffer().get());
			}
			actor->Render(pipeline.get());
		}
	}
	Graphics::Get().End();
}

const std::shared_ptr<class Actor> Execute::CreateActor(const bool& is_active)
{
	std::shared_ptr<class Actor>actor = std::make_shared<Actor>();
	actor->SetActive(is_active);
	AddActor(actor);

	return actor;
}

void Execute::AddActor(const std::shared_ptr<class Actor>& actor)
{
	actors.emplace_back(actor);
}