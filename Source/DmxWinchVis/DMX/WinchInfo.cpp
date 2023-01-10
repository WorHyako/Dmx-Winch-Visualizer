#include "WinchInfo.h"

WinchInfo::WinchInfo() noexcept
{
	_winchType = WinchObjectsTypes::None;
	_winchIndex = 0;
}

#pragma region Accessors

uint8 WinchInfo::GetSelectedByte(WinchByte byteType) const noexcept
{
	return _dmxData[byteType];
}

const FWinchPacket& WinchInfo::GetDmxData() const noexcept
{
	return _dmxData;
}

WinchObjectsTypes WinchInfo::GetWinchObjectsTypes() const noexcept
{
	return _winchType;
}

#pragma endregion Accessors

#pragma region Mutators

void WinchInfo::SetWinchIndex(int winchIndex) noexcept
{
	_winchIndex = winchIndex;
}

void WinchInfo::SetWinchType(WinchObjectsTypes winchType) noexcept
{
	_winchType = winchType;
}

void WinchInfo::SetDmxData(FWinchPacket dmxData) noexcept
{
	_dmxData = MoveTemp(dmxData);
}

#pragma endregion Mutators
