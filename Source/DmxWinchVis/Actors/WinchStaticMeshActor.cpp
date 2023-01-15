#include "WinchStaticMeshActor.h"

AWinchStaticMeshActor::AWinchStaticMeshActor():
	type{WinchObjectsTypes::Sphere},
	staticMesh{nullptr}
{
	ConfigureActor(type);
}

UStaticMesh* AWinchStaticMeshActor::GetWinchStaticMesh(WinchObjectsTypes meshType) noexcept
{
	UStaticMesh* staticMesh = nullptr;
	switch (meshType)
	{
	case WinchObjectsTypes::None:
		return staticMesh;
	case WinchObjectsTypes::StickHorizontal:
	case WinchObjectsTypes::StickVertical:
		{
			static ConstructorHelpers::FObjectFinder<UStaticMesh> stickMesh(TEXT("/Game/Meshes/Stick"));
			staticMesh = stickMesh.Succeeded() ? stickMesh.Object : nullptr;
			return staticMesh;
		}
	case WinchObjectsTypes::Mirror:
		{
			static ConstructorHelpers::FObjectFinder<UStaticMesh> mirrorMesh(TEXT("/Game/Meshes/Mirror"));
			staticMesh = mirrorMesh.Succeeded() ? mirrorMesh.Object : nullptr;
			return staticMesh;
		}
	case WinchObjectsTypes::Sphere:
		{
			static ConstructorHelpers::FObjectFinder<UStaticMesh> ballMesh(TEXT("/Game/Meshes/Sphere"));
			staticMesh = ballMesh.Succeeded() ? ballMesh.Object : nullptr;
			return staticMesh;
		}
	default:
		return nullptr;
	}
}

void AWinchStaticMeshActor::ConfigureActor(WinchObjectsTypes meshType)
{
	staticMesh = GetWinchStaticMesh(meshType);
	GetStaticMeshComponent()->SetStaticMesh(staticMesh);
	SetMobility(EComponentMobility::Movable);
	SetReplicates(false);
	bBlockInput = true;
	bGenerateOverlapEventsDuringLevelStreaming = false;
	GetStaticMeshComponent()->SetEnableGravity(false);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetGenerateOverlapEvents(false);
	GetStaticMeshComponent()->SetSimulatePhysics(false);
	GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
