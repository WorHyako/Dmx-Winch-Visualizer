#pragma once

#include "CoreMinimal.h"

#include "DmxWinchVis/Dmx/WinchObjectsTypes.h"
#include "DmxWinchVis/Dmx/WinchPacket.h"

#include "WinchInfo.generated.h"

USTRUCT(BlueprintType)
struct FWinchInfo
{
	GENERATED_BODY()

	FWinchInfo() noexcept;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Chanel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Universe;

private:
	WinchObjectsTypes _winchType;

	WinchObjectOrder _winchOrder;

public:
#pragma region Accessors

	[[nodiscard]] uint8 GetSelectedByte(WinchByte byteType) const noexcept;

	[[nodiscard]] const FWinchPacket& GetDmxData() const noexcept;

	[[nodiscard]] WinchObjectsTypes GetWinchObjectsTypes() const noexcept;

#pragma endregion Accessors

#pragma region Mutators

	void SetWinchType(WinchObjectsTypes winchType) noexcept;

	void SetDmxData(FWinchPacket dmxData) noexcept;

#pragma endregion Mutators
};
