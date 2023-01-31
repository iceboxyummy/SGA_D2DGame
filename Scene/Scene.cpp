#include "stdafx.h"
#include "Scene.h"
#include "Scene/Actor.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/AiScriptComponent.h"
#include "Scene/Component/TargetTraceComponent.h"
#include "Scene/Component/AnimatorComponent.h"

Scene::Scene(Context* const context)
	:context(context)
{
	renderer = context->GetSubsystem<Renderer>();

	// ===============================================
	// [Animation]
	// ===============================================
	//std::shared_ptr<Animation> idle_animation = std::make_shared<Animation>(context);

	//idle_animation->AddKeyframe(D3DXVECTOR2(4.0f, 1.0f),  D3DXVECTOR2(30.0f, 40.0f), 200);
	//idle_animation->AddKeyframe(D3DXVECTOR2(34.0f, 1.0f), D3DXVECTOR2(30.0f, 40.0f), 200);
	//idle_animation->AddKeyframe(D3DXVECTOR2(64.0f, 1.0f), D3DXVECTOR2(30.0f, 40.0f), 200);
	//idle_animation->SetRepeatType(RepeatType::Loop);
	//idle_animation->SetSpriteTexture("Assets/Texture/metalslug.png");
	//idle_animation->SetSpriteTextureSize(D3DXVECTOR2(400.0f, 600.0f));
	//idle_animation->SetResourceName("Idle");
	//idle_animation->SaveToFile("Assets/Animation/Idle.xml");

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

	auto animator = player->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/Idle.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Idle");

	player->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(60.0f, 80.0f, 1.0f));
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