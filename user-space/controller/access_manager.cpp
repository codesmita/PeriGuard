#include "access_manager.h"
AccessManager::AccessManager()
{
	deviceInUse = false;
}
bool AccessManager::requestAccess()
{
	if (!deviceInUse)
	{
		deviceInUse = true;
		return true;
	}
	return false;
}
void AccessManager::releaseAccess()
{
	deviceInUse = false;
}
