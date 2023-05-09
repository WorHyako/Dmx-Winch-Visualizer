#include "WinchInfo.h"

FWinchInfo::FWinchInfo() noexcept
{
	_winchType = WinchObjectsTypes::None;
	_winchOrder = WinchObjectOrder::First;
	Chanel = 0;
	Universe = -1;
}

#pragma region Accessors

WinchObjectsTypes FWinchInfo::GetWinchObjectsTypes() const noexcept
{
	return _winchType;
}

#pragma endregion Accessors

#pragma region Mutators

void FWinchInfo::SetWinchType(WinchObjectsTypes winchType) noexcept
{
	_winchType = winchType;
}

#pragma endregion Mutators
