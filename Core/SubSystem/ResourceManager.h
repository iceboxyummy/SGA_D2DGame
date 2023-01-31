#pragma once
#include"ISubSystem.h"
#include"Resource/IResource.h"

enum class AssetType : uint
{
	Texture,
	Shader,
	Animation
};

class ResourceManager final : public ISubsystem
{
public:
	ResourceManager(class Context* context);
	~ResourceManager();

	virtual bool Initialize() override;
	virtual void Update() override;

	// ===========================================
	//  [Resource]
	// ===========================================
	template <typename T>
	const std::shared_ptr<T> Load(const std::string& path);

	template <typename T>
	const std::shared_ptr<T> GetResourceFromName(const std::string& name);

	template <typename T>
	const std::shared_ptr<T> GetResourceFromPath(const std::string& path);

	template <typename T>
	void RegisterResource(const std::shared_ptr<T>& resource);

	bool HasResource(const std::string& resource_name, const ResourceType& resource_type);

	// ===========================================
	//  [Directory]
	// ===========================================
	const std::string GetAssetDirectory() const { return "Assets/"; }

	const std::string GetAssetDirectory(const AssetType& type);

private:
	void RegisterDirectory(const AssetType& type, const std::string& directory);

private:
	using resource_proups_t = std::vector<std::shared_ptr<IResource>>;
	std::map<ResourceType, resource_proups_t> resource_groups;

	std::mutex resource_mutex;
	std::map<AssetType, std::string> asset_directories;
};