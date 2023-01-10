#include "DmxWinch.h"
#include "../DMX/WinchInfo.h"
#include "../DMX/DmxListenerMaster.h"

#include "Engine/StaticMeshActor.h"

ADmxWinch::ADmxWinch()
{
	PrimaryActorTick.bCanEverTick = true;
	bRunConstructionScriptOnDrag = false;
	bCollideWhenPlacing = false;
	bReplicates = false;
	bBlockInput = true;
	bActorLabelEditable = false;

	DmxPortActivity = false;
	HawserLength = 17.f;
	_staticMeshes.SetNum(5);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ballMesh(TEXT("/Game/Meshes/Shape_Sphere"));
	_staticMeshes[static_cast<int>(WinchObjectsTypes::Sphere)] = ballMesh.Succeeded() ? ballMesh.Object : nullptr;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mirrorMesh(TEXT("/Game/Meshes/Shape_Torus"));
	_staticMeshes[static_cast<int>(WinchObjectsTypes::Mirror)] = mirrorMesh.Succeeded() ? mirrorMesh.Object : nullptr;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> stickMesh(TEXT("/Game/Meshes/Shape_Pipe"));
	_staticMeshes[static_cast<int>(WinchObjectsTypes::StickHorizontal)] =
		stickMesh.Succeeded() ? stickMesh.Object : nullptr;
}

void ADmxWinch::BeginPlay()
{
	const int winchCount = objectMatrix.X * objectMatrix.Y;
	DmxData.Reset(DmxListener::UniverseDataLength * 4);
	actors.Reset(winchCount);
	winchInfo.Reset(winchCount);
	if (selectedUniverses.Num() == 0)
	{
		selectedUniverses.Reserve(4);
	}
	auto& dmxMaster = DmxListenerMaster::GetInstance();
	DmxPortActivity = dmxMaster.FindPort(L"TestPort");

	for (int i = 0; i < objectMatrix.X; i++)
	{
		for (int j = 0; j < objectMatrix.Y; j++)
		{
			FActorSpawnParameters spawnInfo;
			spawnInfo.Owner = this;
			spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FTransform transform;
			transform.SetLocation(FVector(i * 400, j * 400, 0));
			AStaticMeshActor* actor =
				GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), transform, spawnInfo);
			actor->SetMobility(EComponentMobility::Movable);
			actor->SetReplicates(false);
			actor->bBlockInput = true;
			actor->bGenerateOverlapEventsDuringLevelStreaming = false;
			actor->GetStaticMeshComponent()->SetStaticMesh(_staticMeshes[static_cast<int>(WinchObjectsTypes::Sphere)]);
			actor->GetStaticMeshComponent()->SetEnableGravity(false);
			actor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
			actor->GetStaticMeshComponent()->SetGenerateOverlapEvents(false);
			actor->GetStaticMeshComponent()->SetSimulatePhysics(false);
			actor->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			actors.Push(actor);
		}
	}

	Super::BeginPlay();
}

void ADmxWinch::Tick(float deltaTime)
{
	DmxData.Empty(DmxListener::UniverseDataLength * selectedUniverses.Num());
	auto& dmxMaster = DmxListenerMaster::GetInstance();
	for (const auto& eachUniverse : selectedUniverses)
	{
		auto dataFromUniverse = dmxMaster.GetPacketFromUniverse(eachUniverse);
		if (dataFromUniverse.Num() > 0)
		{
			DmxData.Append(MoveTemp(dataFromUniverse));
		}
	}

	const int actorsNum = actors.Num();
	const int dmxDataNum = DmxData.Num();
	for (uint16_t i = 0; i < actorsNum && i < dmxDataNum; ++i)
	{
		FVector newLocation = actors[i]->GetActorLocation();
		newLocation.Z = DmxData[i].Roll * HawserLength;
		actors[i]->SetActorLocation(newLocation);
	}

	Super::Tick(deltaTime);
}
