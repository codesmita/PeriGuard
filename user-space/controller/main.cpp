#include <iostream>
#include "access_manager.h"
enum class DeviceState
{
	AVAILABLE,
	IN_USE,
	FAULT,
	RECOVERY,
	SAFE_STATE,
};
class DeviceManager
{
private:
	DeviceState currentState;
public:
	DeviceManager();
	DeviceState getState() const;
};
DeviceManager::DeviceManager()
{
	currentState=DeviceState::AVAILABLE;
}
DeviceState DeviceManager::getState() const
{
	return currentState;
}
int main()
{
	DeviceManager deviceManager;
	if (deviceManager.getState() == DeviceState::AVAILABLE)
	{
		std::cout << "Device state: AVAILABLE" << std::endl;
	}
	AccessManager accessManager;
	if (accessManager.requestAccess())
	{
		std::cout << "Access granted" << std::endl;
	}
	if (accessManager.requestAccess())
	{
		std::cout << "Second access granted" << std::endl;
	}
	else
	{
		std::cout << "Second access denied" << std::endl;
	}
	accessManager.releaseAccess();
	if (accessManager.requestAccess())
	{
		std::cout << "Access granted after release" << std::endl;
	}
	return 0;
}

