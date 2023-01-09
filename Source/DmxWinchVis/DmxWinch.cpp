// Fill out your copyright notice in the Description page of Project Settings.

#include "DmxWinch.h"
#include "DMX/Winchinfo.h"
#include "DMX/DMXListenerMaster.h"

#include "Engine/StaticMeshActor.h"

ADmxWinch::ADmxWinch()
{
	PrimaryActorTick.bCanEverTick = true;
	bRunConstructionScriptOnDrag = false;
	bReplicates = false;
	bBlockInput = true;
	bActorLabelEditable = false;

	objectMatrix = {0, 0};
	dmxValue.Reset(2048);
	actors.Reset(200);
	selectedUniverses.Reserve(4);

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
	auto& dmxMaster = DMXListenerMaster::GetInstance();
	bool found = dmxMaster.FindPort(L"TestPort");

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

void ADmxWinch::Tick(float DeltaTime)
{
	dmxValue.Empty(2048);
	auto& dmxMaster = DMXListenerMaster::GetInstance();
	for (const auto& eachUniverse : selectedUniverses)
	{
		auto dataFromUniverse = dmxMaster.GetDataFromUniverse(eachUniverse);
		if (dataFromUniverse.Num() > 0)
		{
			dmxValue.Append(dataFromUniverse);
		}
	}

	const int dmxCount = dmxValue.Num();
	constexpr int packetLength = 10;
	const int maxCount = dmxCount / packetLength;
	for (int i = 0; i < maxCount; ++i)
	{
		FVector newLocation = actors[i]->GetActorLocation();
		newLocation.Z = dmxValue[6 + i * 10];
		actors[i]->SetActorLocation(newLocation);
	}

	Super::Tick(DeltaTime);
}
