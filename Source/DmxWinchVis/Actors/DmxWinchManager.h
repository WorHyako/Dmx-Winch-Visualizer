#pragma once

#include "DmxWinchVis/DMX/WinchInfo.hpp"
#include "DmxWinchVis//DMX/WinchPacket.h"
#include "DmxWinchVis/Actors/WinchStaticMeshActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <vector>

#include "DmxWinchManager.generated.h"

constexpr uint8 WinchLength = 17;

UCLASS()
class DMXWINCHVIS_API ADmxWinchManager final : public AActor
{
	GENERATED_BODY()

public:
	ADmxWinchManager();
`
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D ObjectMatrix;

	void Tick(float deltaTime) final;

	UFUNCTION(BlueprintCallable)
	void ConfigureWinchObject();

protected:
	void BeginPlay() final;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool DmxPortActivity;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere);
	float HawserLength;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<AWinchStaticMeshActor*> Actors;

	std::vector<WinchInfo> winchInfo;

	UPROPERTY(BlueprintReadWrite)
	TArray<FWinchPacket> DmxData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<uint8> SelectedUniverses;

private:
};
