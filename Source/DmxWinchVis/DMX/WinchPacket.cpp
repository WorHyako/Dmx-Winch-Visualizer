#include "WinchPacket.h"

FWinchPacket::FWinchPacket() noexcept
{
	Dimer = 0;
	Red = 0;
	Green = 0;
	Blue = 0;
	Roll = 0;
	Speed = 0;
	Ctrl = 0;
}

#pragma region Operators

int FWinchPacket::operator[](WinchByte byte) const noexcept
{
	uint8_t resultValue;
	switch (byte)
	{
	case WinchByte::Dimmer:
		resultValue = Dimer;
		break;
	case WinchByte::Red:
		resultValue = Red;
		break;
	case WinchByte::Green:
		resultValue = Green;
		break;
	case WinchByte::Blue:
		resultValue = Blue;
		break;
	case WinchByte::Roll:
		resultValue = Roll;
		break;
	case WinchByte::Speed:
		resultValue = Speed;
		break;
	case WinchByte::Ctrl:
		resultValue = Ctrl;
		break;
	default:
		resultValue = -1;
	}
	return resultValue;
}

int& FWinchPacket::operator[](WinchByte byte) noexcept
{
	switch (byte)
	{
	case WinchByte::Dimmer:
		return Dimer;
	case WinchByte::Red:
		return Red;
	case WinchByte::Green:
		return Green;
	case WinchByte::Blue:
		return Blue;
	case WinchByte::Roll:
		return Roll;
	case WinchByte::Speed:
		return Speed;
	case WinchByte::Ctrl:
	default:
		return Ctrl;
	}
}

#pragma endregion Operators
