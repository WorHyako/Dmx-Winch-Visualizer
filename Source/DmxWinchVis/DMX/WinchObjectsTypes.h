#pragma once

#include "CoreMinimal.h"

#include "WinchObjectsTypes.generated.h"

UENUM(BlueprintType)
enum class WinchObjectsTypes : uint8
{
	None UMETA(DisplayName="None"),
	StickHorizontal UMETA(DisplayName="StickHorizontal"),
	StickVertical UMETA(DisplayName="StickVertical"),
	Mirror UMETA(DisplayName="Mirror"),
	Sphere UMETA(DisplayName="Sphere"),
};
