#include "DMXListenerMaster.h"

DMXListener& DMXListenerMaster::GetInstance()
{
	static DMXListenerMaster instance{};
	return instance;
}
