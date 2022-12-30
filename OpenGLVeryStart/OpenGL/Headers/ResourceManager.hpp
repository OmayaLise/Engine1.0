#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Log.hpp"

namespace Resources 
{
	class IResource
	{
	protected:
		 unsigned int resourceID = 0;
		 std::string resourcePath = "";
		 std::string resourceName = "";
	public:
		virtual int GetResourceID();
		virtual ~IResource() {};

	};

	 class ResourceManager
	 {
	 public:
		 std::unordered_map<std::string, std::unique_ptr<IResource>> resourcesMap;

		 template <typename T> inline
		 T* Create(const std::string& name, std::string const& path);

		 template <typename T> inline
		 T* GetResource(const std::string& name);

		 void Remove(const std::string& name);
	 };

	 template <typename T>
	 T* ResourceManager::Create(const std::string& name, std::string const& path)
	 {
		 static_assert(std::is_base_of<IResource, T>::value, "Failed to create resource");
		 resourcesMap[name] = std::make_unique<T>(name, path, resourcesMap.size());
		 Core::Debug::Log::Print(name + " was sucessfully added to manager list\n");

		 return (T*)resourcesMap[name].get();
	 }


	 template <typename T>
	 T* ResourceManager::GetResource(const std::string& name)
	 {
		 if (resourcesMap[name].get())
			 return (T*)resourcesMap[name].get();
		 else
		 {
			 Core::Debug::Log::Print("Resource was not found");
			 return nullptr;
		 }
	 }

}