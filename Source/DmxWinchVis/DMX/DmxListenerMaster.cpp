#include "DmxListenerMaster.hpp"

DmxListener& DmxListenerMaster::GetInstance()
{
	static DmxListenerMaster instance{};
	return instance;
}
