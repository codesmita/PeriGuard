#ifndef ACCESS_MANAGER_H
#define ACCESS_MANAGER_H

class AccessManager
{
public:
	AccessManager();
	bool requestAccess();
	void releaseAccess();
private:
	bool deviceInUse;
};
#endif
