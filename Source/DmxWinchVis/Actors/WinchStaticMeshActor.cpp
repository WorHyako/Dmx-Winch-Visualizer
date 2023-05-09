#include "WinchStaticMeshActor.h"

AWinchStaticMeshActor::AWinchStaticMeshActor():
	type{WinchObjectsTypes::Sphere},
	staticMesh{nullptr}
{
	auto* meshComponent = GetStaticMeshComponent();
	meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComponent->SetIsReplicated(false);
	meshComponent->SetSimulatePhysics(false);
	meshComponent->SetCastShadow(false);
	PrimaryActorTick.bCanEverTick = true;
	bRunConstructionScriptOnDrag = false;
	bCollideWhenPlacing = false;
	bReplicates = false;
	bBlockInput = true;
	bActorLabelEditable = false;

	allStaticMeshes.SetNum(5);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ballMesh(L"/Game/Meshes/SphereOld");
	allStaticMeshes[static_cast<int>(WinchObjectsTypes::Sphere)] =
		ballMesh.Succeeded() ? ballMesh.Object : nullptr;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> stickVerticalMesh(L"/Game/Meshes/StickVertical");
	allStaticMeshes[static_cast<int>(WinchObjectsTypes::StickVertical)] =
		stickVerticalMesh.Succeeded() ? stickVerticalMesh.Object : nullptr;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mirrorMesh(L"/Game/Meshes/Mirror");
	allStaticMeshes[static_cast<int>(WinchObjectsTypes::Mirror)] =
		mirrorMesh.Succeeded() ? mirrorMesh.Object : nullptr;
	ConfigureActor(type);
}

void AWinchStaticMeshActor::ConfigureActor(WinchObjectsTypes meshType)
{
	staticMesh = allStaticMeshes[static_cast<int>(meshType)];
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
