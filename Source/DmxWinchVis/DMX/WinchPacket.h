#pragma once

#include "CoreMinimal.h"

#include "WinchPacket.generated.h"

UENUM(BlueprintType)
enum class WinchByte : uint8
{
	Dimmer UMETA(DisplayName="Dimmer"),

	Red UMETA(DisplayName="Red"),

	Green UMETA(DisplayName="Green"),

	Blue UMETA(DisplayName="Blue"),

	/// maybe unused
	// White UMETA(DisplayName="White"),

	/// maybe unused
	// Strob UMETA(DisplayName="Strob"),

	Roll UMETA(DisplayName="Roll"),

	/// maybe unused
	// RollFine UMETA(DisplayName="RollFine"),

	Speed UMETA(DisplayName="Speed"),

	Ctrl UMETA(DisplayName="Ctrl"),
};

USTRUCT(BlueprintType)
struct FWinchPacket
{
	GENERATED_BODY()

	static constexpr uint8_t WinchPacketLength = 10;

	static constexpr uint8_t WinchUsefulPacketLength = 7;

	FWinchPacket() noexcept;

	UPROPERTY(BlueprintReadWrite)
	int Dimer;

	UPROPERTY(BlueprintReadWrite)
	int Red;

	UPROPERTY(BlueprintReadWrite)
	int Green;

	UPROPERTY(BlueprintReadWrite)
	int Blue;

	UPROPERTY(BlueprintReadWrite)
	int Roll;

	UPROPERTY(BlueprintReadWrite)
	int Speed;

	UPROPERTY(BlueprintReadWrite)
	int Ctrl;

#pragma region Operators

	int operator[](WinchByte byte) const noexcept;

	int& operator[](WinchByte byte) noexcept;

#pragma endregion Operators
};
