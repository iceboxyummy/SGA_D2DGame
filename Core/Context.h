#pragma once

#include "stdafx.h"
#include "Core/SubSystem/ISubSystem.h"

// Context.h

class Context final
{
public:
	Context() = default;

	~Context()
	{
		auto iter = subsystems.rbegin();
		auto iter = subsystems.rend();

		for (auto iter = subsystems.rbegin(); iter != subsystems.rend(); iter++)
			SAFE_DELETE(*iter);
	}

	const bool InitializeSubSystems()
	{
		bool result = true;

		for (const auto& subsystem : subsystems)
		{
			if (subsystem->Initialize() == false)
				result = false;
		}
		return result;
	}

	template<typename T>
	const T* const RegisterSubsystem()
	{

	}

	template<typename T>
	T* const GetSubsystem()
	{

	}

	void UpdateSubsystems()
	{

	}

	void RenderSubsystems()
	{

	}

private:
	std::vector<ISubsystem*> subsystems;
};