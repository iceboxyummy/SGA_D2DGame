#include "stdafx.h"
#include "MoveScriptComponent.h"
#include "TransformComponent.h"
#include "MeshRendererComponent.h"
#include "../Actor.h"

void MoveScriptComponent::Initialize()
{
}

void MoveScriptComponent::Update()
{
	D3DXVECTOR3 position = transform->GetPosition();

	auto input = context->GetSubsystem<InputManager>();

	input->GetKeyState(DIK_W) == KEY_HOLD || input->GetKeyState(DIK_W) == KEY_DOWN;
	input->GetKeyState(DIK_S);
	input->GetKeyState(DIK_A);
	input->GetKeyState(DIK_D);

	if (GetAsyncKeyState('W') & 0x8000) position.y += 3;
	if (GetAsyncKeyState('S') & 0x8000) position.y -= 3;
	if (GetAsyncKeyState('D') & 0x8000) position.x += 3;
	if (GetAsyncKeyState('A') & 0x8000) position.x -= 3;

	/*if (input->GetMouseState(MOUSE_LEFT) == KEY_DOWN)
	{
		position.x = input->GetMousePosition().x;
		position.y = input->GetMousePosition().y;
	}*/

	transform->SetPosition(position);

	if (ImGui::Begin("Transform"))
	{
		auto position = transform->GetPosition();
		auto scale = transform->GetScale();

		ImGui::InputFloat3("Position", position);

		transform->SetPosition(position);
		transform->SetScale(scale);
	}
	ImGui::End();

	if (ImGui::Begin("Transform"))
	{
		auto position = transform->GetPosition();
		auto scale = transform->GetScale();

		ImGui::SliderFloat3("Scale", scale, 0.0f, 300.0f);

		transform->SetPosition(position);
		transform->SetScale(scale);
	}
	ImGui::End();

	if(ImGui::Begin("Actor"))
	{
		auto renderer = actor->GetComponent<MeshRendererComponent>();
		bool mesh_is_enable = renderer->IsEnabled();

		ImGui::Checkbox("Render", &mesh_is_enable);

		renderer->SetEnabled(mesh_is_enable);
	}
	ImGui::End();
}

void MoveScriptComponent::Destroy()
{
}