#include <iostream>
#include "access_manager.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>


int main()
{
	const char* devicePath = "/dev/periguard";

	int deviceFd = open(devicePath, O_RDWR);

	if (deviceFd == -1)
	{
		std::cerr << "Failed to open PeriGuard device" << std::endl;
		return 1;
	}

	const char* command = "ACCESS";

	ssize_t bytesWritten = write(deviceFd, command, 6);

	if (bytesWritten == -1)
	{
		std::cerr << "Failed to write to PeriGuard device" << std::endl;
		close(deviceFd);
		return 1;
	}

	char buffer[128];

	ssize_t bytesRead = read(deviceFd, buffer, sizeof(buffer)-1);

	if (bytesRead == -1)
	{
		std::cerr << "Failed to read from PeriGuard device" << std::endl;
		close(deviceFd);
		return 1;
	}
	buffer[bytesRead] = '\0';

	std::cout << "Driver response: " << buffer << std::endl;

	if (strcmp(buffer, "IN_USE\n") == 0)
	{
		std::cout << "Driver granted access." << std::endl;
		const char* releaseCommand = "RELEASE";
		ssize_t releaseBytes = write(deviceFd, releaseCommand, 7);

		if (releaseBytes == -1)
		{
			std::cerr << "Failed to release PeriGuard device" << std::endl;
			close(deviceFd);
			return 1;
		}
	}
	else if (strcmp(buffer, "DENIED\n") == 0)
	{
		std::cout << "Driver denied access." << std::endl;
	}
	else if (strcmp(buffer, "AVAILABLE\n") == 0)
	{
		std::cout << "Device is available." << std::endl;
	}
	close(deviceFd);
	return 0;
}

