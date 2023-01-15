#include "DmxWinchManager.h"

#include "DmxWinchVis//DMX/DmxListenerMaster.hpp"

ADmxWinchManager::ADmxWinchManager()
{
	winchInfo.reserve(200);
	PrimaryActorTick.bCanEverTick = true;
	bRunConstructionScriptOnDrag = false;
	bCollideWhenPlacing = false;
	bReplicates = false;
	bBlockInput = true;
	bActorLabelEditable = false;

	DmxPortActivity = false;
	HawserLength = 17.0f;
}

void ADmxWinchManager::BeginPlay()
{
	const int winchCount = ObjectMatrix.X * ObjectMatrix.Y;
	DmxData.Reset(DmxListener::UniverseDataLength * 4);
	Actors.Reset(winchCount);
	winchInfo.reserve(winchCount);
	if (SelectedUniverses.Num() == 0)
	{
		SelectedUniverses.Reserve(4);
	}
	auto& dmxMaster = DmxListenerMaster::GetInstance();
	DmxPortActivity = dmxMaster.FindPort(L"TestPort");

	for (int i = 0; i < ObjectMatrix.X; i++)
	{
		for (int j = 0; j < ObjectMatrix.Y; j++)
		{
			FActorSpawnParameters spawnInfo;
			spawnInfo.Owner = this;
			spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FTransform transform;
			transform.SetLocation(FVector(i * 400, j * 400, 0));
			AWinchStaticMeshActor* actor =
				GetWorld()->SpawnActor<AWinchStaticMeshActor>(AWinchStaticMeshActor::StaticClass(), transform,
				                                              spawnInfo);
			Actors.Push(actor);
		}
	}

	Super::BeginPlay();
}

void ADmxWinchManager::Tick(float deltaTime)
{
	DmxData.Empty(DmxListener::UniverseDataLength * SelectedUniverses.Num());
	auto& dmxMaster = DmxListenerMaster::GetInstance();
	for (const auto& eachUniverse : SelectedUniverses)
	{
		auto dataFromUniverse = dmxMaster.GetPacketFromUniverse(eachUniverse);
		if (dataFromUniverse.Num() > 0)
		{
			DmxData.Append(MoveTemp(dataFromUniverse));
		}
	}

	const int actorsNum = Actors.Num();
	const int dmxDataNum = DmxData.Num();
	for (uint16_t i = 0; i < actorsNum && i < dmxDataNum; ++i)
	{
		FVector newLocation = Actors[i]->GetActorLocation();
		newLocation.Z = DmxData[i].Roll * HawserLength;
		Actors[i]->SetActorLocation(newLocation);
	}

	Super::Tick(deltaTime);
}

void ADmxWinchManager::ConfigureWinchObject()
{
	for (auto& each : Actors)
	{
		each->ConfigureActor();
	}
}
