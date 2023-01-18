#include "stdafx.h"
#include "TargetTraceComponent.h"
#include "TransformComponent.h"
#include "Scene/Actor.h"

void TargetTraceComponent::Initialize()
{
	Timer.Start();
}

void TargetTraceComponent::Update()
{
	if (target.expired() == true) return;

	D3DXVECTOR3 my_position = transform->GetPosition();

	D3DXVECTOR3 target_position = target.lock()->GetTransform()->GetPosition();

	/*if (my_position.x >= target_position.x) my_position.x--;
	else my_position.x++;

	if (my_position.y >= target_position.y) my_position.y--;
	else my_position.y++;*/

	// A - B = B���� A�� ���ϴ� ����
	D3DXVECTOR3 vector = target_position - my_position;

	// ��Ÿ����� ������ �̿��� ���� ���ϱ�
	// ����(����)^2 = �غ�^2 + ����^2 
	// -> �����^2 = -> ��(�غ�^2 + ����^2)
	// -> ���� = ��(�غ�^2 + ����^2)
	float distance = sqrt(vector.x * vector.x + vector.y * vector.y);

	// ���� ���ͷ� ����� ������ ���Ⱚ���� �ٲ۴�.
	D3DXVECTOR3 direction;
	D3DXVec3Normalize(&direction, &vector);


	// ���� ��ġ ����
	D3DXVECTOR3 move_position;
	move_position = my_position + direction * speed * Timer.GetElapsedTimeSec();

	Timer.Start();

	transform->SetPosition(move_position);
}

void TargetTraceComponent::Destroy()
{
}

void TargetTraceComponent::SetTarget(const std::shared_ptr<const class Actor> target)
{
	if (actor == target.get()) return;

	this->target = target;
}