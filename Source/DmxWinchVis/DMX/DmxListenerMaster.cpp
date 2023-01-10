#include "DmxListenerMaster.h"

DmxListener& DmxListenerMaster::GetInstance()
{
	static DmxListenerMaster instance{};
	return instance;
}
