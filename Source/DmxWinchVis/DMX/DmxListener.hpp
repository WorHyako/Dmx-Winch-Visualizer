#pragma once

#include "WinchPacket.h"

#include "CoreMinimal.h"
#include "DMXRuntime/Public/DMXSubsystem.h"
#include "Containers/Array.h"

class DmxListener
{
public:
	UENUM()
	enum class DmxListenerState
	{
		ZeroCheck UMETA(DisplayName="ZeroCheck"),
		PortFounded UMETA(DisplayName="PortFounded")
	} state;

	[[nodiscard]] bool FindPort(FString portName = "") noexcept;

	static constexpr uint16_t UniverseDataLength = 512;

	static constexpr uint8_t UniversalPacketCount =
		(UniverseDataLength - UniverseDataLength % 100) / FWinchPacket::WinchPacketLength;

protected:
	DmxListener();

	virtual ~DmxListener() = default;

private:
	UDMXSubsystem* _dmxSubsystem;

	FDMXInputPortReference _inputPortRef;

	FString _portName;

	int _universe;

public:
#pragma region Accessors

	[[nodiscard]] TArray<uint8> GetDataFromUniverse(int universe = -1) const noexcept;

	[[nodiscard]] TArray<FWinchPacket> GetPacketFromUniverse(int universe = -1) const noexcept;

	[[nodiscard]] const FString& GetCurrentPortName() const noexcept;

	[[nodiscard]] int GetCurrentUniverse() const noexcept;

#pragma endregion Accessors

#pragma region Mutators

	void SetPortName(const FString& portName) noexcept;

	void SetUniverse(int universe) noexcept;

#pragma endregion Mutators
};
