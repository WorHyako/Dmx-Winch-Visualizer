#pragma once

#include "DMXListener.h"

class DMXListenerMaster final : protected DMXListener
{
public:
	DMXListenerMaster(const DMXListenerMaster &) = delete;

	DMXListenerMaster &operator=(const DMXListenerMaster) = delete;

#pragma region Accessors

	static DMXListener &GetInstance();

#pragma endregion Accessors

protected:
	~DMXListenerMaster() final = default;

	DMXListenerMaster() = default;
};
