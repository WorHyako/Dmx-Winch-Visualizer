#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class WinchObjectsTypes : uint8
{
	None UMETA(DisplayName="None"),
	StickHorizontal UMETA(DisplayName="StickHorizontal"),
	StickVertical UMETA(DisplayName="StickVertical"),
	Mirror UMETA(DisplayName="Mirror"),
	Sphere UMETA(DisplayName="Sphere"),
};

UENUM(BlueprintType)
enum class WinchObjectOrder : uint8
{
	First UMETA(DisplayName="First"),
	Second UMETA(DisplayName="Second"),
	Third UMETA(DisplayName="Third"),
};
