#pragma once

#include"ISubSystem.h"

class SceneManager final :public ISubsystem
{
public:
	using ISubsystem::ISubsystem;
	~SceneManager() = default;

	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Render() override;

	const std::map<std::string, std::shared_ptr<class Scene>>& GetAllScenes() const { return scenes; }

	class Scene* const GetCurrentScene();
	void SetCurrentScene(const std::string& scene_name);
	class Scene* const RegisterScene(const std::string& scene_name);

private:
	std::map<std::string,std::shared_ptr<class Scene>>scenes;
	std::weak_ptr<Scene> current_scene;
};