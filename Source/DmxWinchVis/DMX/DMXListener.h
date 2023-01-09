#pragma once

#include "CoreMinimal.h"
#include "DMXRuntime/Public/DMXSubsystem.h"

class DMXListener
{
public:
	bool FindPort(FString portName = "") noexcept;

protected:
	DMXListener();

	virtual ~DMXListener() = default;

private:
	UDMXSubsystem* _dmxSubsystem;

	FDMXInputPortReference _inputPortRef;

	FString _portName;

	int _universe;

public:
#pragma region Accessors

	[[nodiscard]] TArray<uint8> GetDataFromUniverse(int universe = -1) noexcept;

	[[nodiscard]] FString GetCurrentPortName() const noexcept;

	[[nodiscard]] int GetCurrentUniverse() const noexcept;

#pragma endregion Accessors

#pragma region Mutators

	void SetPortName(FString portName) noexcept;

	void SetUniverse(int universe) noexcept;

#pragma endregion Mutators
};
