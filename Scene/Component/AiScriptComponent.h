#pragma once

#include "IComponent.h"

class AiScriptComponent : public IComponent
{
private:
	enum Direction
	{
		MIN,
		U = MIN,
		UR,
		R,
		UL,
		D,
		DL,
		L,
		DR,
		MAX = DR,
		COUNT
	};

public:
	using IComponent::IComponent;
	~AiScriptComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

private:
	Stopwatch stopwatch;
	Direction direction = Direction::R;
};