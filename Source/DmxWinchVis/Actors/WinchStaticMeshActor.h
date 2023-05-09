#pragma once

#include "DmxWinchVis/DMX/WinchObjectsTypes.h"
#include "DmxWinchVis/Dmx/WinchInfo.h"

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"

#include "WinchStaticMeshActor.generated.h"

UCLASS()
class DMXWINCHVIS_API AWinchStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AWinchStaticMeshActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FWinchInfo winchInfo;

	WinchObjectsTypes type;

	UStaticMesh* staticMesh;

	void ConfigureActor(WinchObjectsTypes meshType);

private:
	TArray<UStaticMesh*> allStaticMeshes;
};
