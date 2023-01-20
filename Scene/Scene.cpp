#include "stdafx.h"
#include "Scene.h"
#include "Scene/Actor.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/AiScriptComponent.h"
#include "Scene/Component/TargetTraceComponent.h"

Scene::Scene(Context* const context)
	:context(context)
{
	renderer = context->GetSubsystem<Renderer>();

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
	// monster->AddComponent<AiScriptComponent>();

	monster->AddComponent<TargetTraceComponent>();
	auto target_trace = monster->AddComponent<TargetTraceComponent>();
	target_trace->SetTarget(player);

	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(100.0f, 100.0f, 1.0f));
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-100.0f, 100.0f, 1.0f));
}

Scene::~Scene()
{
}

void Scene::Update()
{
	for (const auto& actor : actors)
		actor->Update();

	if (is_update == true) 
	{
		renderer->UpdateRenderables(this);
		is_update = false;
	}
}

const std::shared_ptr<class Actor> Scene::CreateActor(const bool& is_active)
{
	is_update = true;
	std::shared_ptr<class Actor>actor = std::make_shared<Actor>(context);
	actor->SetActive(is_active);
	AddActor(actor);

	return actor;
}

void Scene::AddActor(const std::shared_ptr<class Actor>& actor)
{
	actors.emplace_back(actor);
}