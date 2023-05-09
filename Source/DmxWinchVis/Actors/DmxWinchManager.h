#pragma once

#include "DmxWinchVis/Actors/WinchStaticMeshActor.h"

#include "Materials/MaterialLayersFunctions.h"
#include "Materials/MaterialInstance.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DmxWinchManager.generated.h"

constexpr uint8 WinchLength = 17;

UCLASS()
class DMXWINCHVIS_API ADmxWinchManager final : public AActor
{
	GENERATED_BODY()

public:
	ADmxWinchManager();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D ObjectMatrix;

	void Tick(float deltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ConfigureWinchObject();

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;

protected:
	void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool DmxPortActivity;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float HawserLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	WinchObjectsTypes UnionMeshType;
	
	UMaterial* winchMatInst;

	TArray<AWinchStaticMeshActor*> Actors;

	TArray<TArray<uint8>> DmxData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<uint8> SelectedUniverses;
};
