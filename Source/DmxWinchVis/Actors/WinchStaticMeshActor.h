#pragma once

#include "DmxWinchVis/DMX/WinchObjectsTypes.h"

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"

#include "WinchStaticMeshActor.generated.h"

UCLASS()
class DMXWINCHVIS_API AWinchStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
    AWinchStaticMeshActor();

	WinchObjectsTypes type;

	UStaticMesh* staticMesh;
	
	void ConfigureActor(WinchObjectsTypes meshType);

private:
	static UStaticMesh* GetWinchStaticMesh(WinchObjectsTypes meshType) noexcept;
};
