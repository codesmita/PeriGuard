#include <iostream>
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
	return 0;
}

