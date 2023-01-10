#pragma once

#include "../DMX/WinchInfo.h"
#include "../DMX/WinchPacket.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DmxWinch.generated.h"

constexpr uint8 WinchLength = 17;

UCLASS()
class DMXWINCHVIS_API ADmxWinch : public AActor
{
	GENERATED_BODY()

public:
	ADmxWinch();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D objectMatrix;

	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool DmxPortActivity;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere);
	float HawserLength;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> actors;

	TArray<WinchInfo> winchInfo;

	UPROPERTY(BlueprintReadWrite)
	TArray<FWinchPacket> DmxData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<uint8> selectedUniverses;

private:
	TArray<UStaticMesh*> _staticMeshes;
};
