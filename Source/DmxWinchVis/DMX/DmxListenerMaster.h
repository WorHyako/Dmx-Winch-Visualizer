#pragma once

#include "DmxListener.h"

class DmxListenerMaster final : protected DmxListener
{
public:
	DmxListenerMaster(const DmxListenerMaster &) = delete;

	DmxListenerMaster &operator=(const DmxListenerMaster) = delete;

#pragma region Accessors

	static DmxListener &GetInstance();

#pragma endregion Accessors

protected:
	~DmxListenerMaster() final = default;

	DmxListenerMaster() = default;
};
