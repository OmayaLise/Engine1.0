#include "ResourceManager.hpp"
// IResource

namespace Resources
{
	int IResource::GetResourceID()
	{
		return resourceID;
	}

	void ResourceManager::Remove(const std::string& name)
	{
		// Remove from map AND delete object
		delete &resourcesMap[name];
		resourcesMap.erase(name);
	}

}