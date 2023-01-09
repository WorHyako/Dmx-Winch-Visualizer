#pragma once

#include "CoreMinimal.h"

#include "WinchObjectsTypes.h"
#include "Winchinfo.generated.h"

UENUM()
enum class WinchByte : uint8
{
	Dimmer UMETA(DisplayName="Dimmer"),

	Red UMETA(DisplayName="Red"),

	Green UMETA(DisplayName="Green"),

	Blue UMETA(DisplayName="Blue"),

	/// maybe unused
	White UMETA(DisplayName="White"),

	/// maybe unused
	Strob UMETA(DisplayName="Strob"),

	Roll UMETA(DisplayName="Roll"),

	/// maybe unused
	RollFine UMETA(DisplayName="RollFine"),

	Speed UMETA(DisplayName="Speed"),

	Ctrl UMETA(DisplayName="Ctrl"),
};

struct WinchInfo
{
	WinchInfo() noexcept;

private:
	int _winchIndex;

	TArray<uint8> _dmxData;

	WinchObjectsTypes _winchType;

public:
#pragma region Accessors

	[[nodiscard]] uint8 GetSelectedByte(WinchByte byteType) const noexcept;

	[[nodiscard]] const TArray<uint8>& GetDmxData() const noexcept;

	[[nodiscard]] WinchObjectsTypes GetWinchObjectsTypes() const noexcept;

#pragma endregion Accessors

#pragma region Mutators

	void SetWinchIndex(int index) noexcept;

	void SetWinchType(WinchObjectsTypes winchType) noexcept;

	void SetDmxData(TArray<uint8> dmxData) noexcept;

#pragma endregion Mutators
};
