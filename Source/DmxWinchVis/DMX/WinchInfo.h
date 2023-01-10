#pragma once

#include "CoreMinimal.h"

#include "WinchObjectsTypes.h"
#include "WinchPacket.h"

struct WinchInfo
{
	WinchInfo() noexcept;

private:
	int _winchIndex;

	FWinchPacket _dmxData;

	WinchObjectsTypes _winchType;

public:
#pragma region Accessors

	[[nodiscard]] uint8 GetSelectedByte(WinchByte byteType) const noexcept;

	[[nodiscard]] const FWinchPacket& GetDmxData() const noexcept;

	[[nodiscard]] WinchObjectsTypes GetWinchObjectsTypes() const noexcept;

#pragma endregion Accessors

#pragma region Mutators

	void SetWinchIndex(int winchIndex) noexcept;

	void SetWinchType(WinchObjectsTypes winchType) noexcept;

	void SetDmxData(FWinchPacket dmxData) noexcept;

#pragma endregion Mutators
};
