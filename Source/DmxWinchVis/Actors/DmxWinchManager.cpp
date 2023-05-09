#include "DmxWinchManager.h"

#include "DmxWinchVis/DMX/DmxListenerMaster.hpp"

ADmxWinchManager::ADmxWinchManager()
{
	PrimaryActorTick.bCanEverTick = true;
	bRunConstructionScriptOnDrag = false;
	bCollideWhenPlacing = false;
	bReplicates = false;
	bBlockInput = true;
	bActorLabelEditable = false;

	DmxPortActivity = false;
	HawserLength = 17.0f;
	UnionMeshType = WinchObjectsTypes::Sphere;
	static ConstructorHelpers::FObjectFinder<UMaterial> baseMatInst(L"/Game/Materials/Winch/BaseWinchMat");
	winchMatInst = baseMatInst.Succeeded() ? baseMatInst.Object : nullptr;
}

void ADmxWinchManager::BeginPlay()
{
	const int winchCount = ObjectMatrix.X * ObjectMatrix.Y;
	Actors.Reset(winchCount);
	if (SelectedUniverses.Num() == 0)
	{
		SelectedUniverses.SetNum(4);
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
			actor->GetStaticMeshComponent()->SetMaterial(0, winchMatInst);
			Actors.Push(actor);
		}
	}

	int universeCount = 1;
	int chanelCount = 0;
	const int ActorNum = Actors.Num();
	for (int i = 0; i < ActorNum; ++i)
	{
		Actors[i]->ConfigureActor(UnionMeshType);
		if (i == 51 || i == 102 || i == 153)
		{
			universeCount++;
			chanelCount = 0;
		}
		constexpr int chanelOffset = 10;
		Actors[i]->winchInfo.Chanel = chanelCount * chanelOffset;
		Actors[i]->winchInfo.Universe = universeCount;
		chanelCount++;
	}

	Super::BeginPlay();
}

void ADmxWinchManager::Tick(float deltaTime)
{
	DmxData.Empty(SelectedUniverses.Num());
	DmxData.SetNum(SelectedUniverses.Num());
	for (auto& each : DmxData)
	{
		each.Empty();
	}
	const auto& dmxMaster = DmxListenerMaster::GetInstance();
	int universeCount = 0;
	for (const auto& eachUniverse : SelectedUniverses)
	{
		DmxData[universeCount] = dmxMaster.GetDataFromUniverse(eachUniverse);
		++universeCount;
	}

	const int actorsNum = Actors.Num();
	for (uint16_t i = 0; i < actorsNum; ++i)
	{
		const int currentUniverse = Actors[i]->winchInfo.Universe;
		const int currentChanel = Actors[i]->winchInfo.Chanel;
		if (currentUniverse < 0)
		{
			continue;
		}
		const auto& universe = DmxData[currentUniverse - 1];
		if (universe.Num() < 1)
		{
			continue;
		}
		FVector newLocation = Actors[i]->GetActorLocation();
		newLocation.Z = universe[currentChanel + static_cast<int>(WinchByte::Roll)] * HawserLength;
		Actors[i]->SetActorLocation(newLocation);
		constexpr float dmxMaxValue = 255.0f;
		const float red = universe[currentChanel + static_cast<int>(WinchByte::Red)] / dmxMaxValue;
		const float green = universe[currentChanel + static_cast<int>(WinchByte::Green)] / dmxMaxValue;
		const float blue = universe[currentChanel + static_cast<int>(WinchByte::Blue)] / dmxMaxValue;
		FLinearColor rbg{red, green, blue};
		const float emissive = universe[currentChanel + static_cast<int>(WinchByte::Dimmer)];
		UMaterialInterface* Material = Actors[i]->GetStaticMeshComponent()->GetMaterial(0);
		UMaterialInstanceDynamic* matInstance = Actors[i]->GetStaticMeshComponent()->
		                                                   CreateDynamicMaterialInstance(0, Material);
		if (matInstance != nullptr)
		{
			matInstance->SetVectorParameterValue("Color", rbg);
			matInstance->SetScalarParameterValue("Emissive", emissive);
		}
		Actors[i]->GetStaticMeshComponent()->SetMaterial(0, matInstance);
	}

	Super::Tick(deltaTime);
}

void ADmxWinchManager::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{

	const FName PropertyName(PropertyChangedEvent.Property->GetFName());
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ADmxWinchManager, SelectedUniverses))
	{
		const auto& name = PropertyChangedEvent.GetPropertyName();
		auto index = PropertyChangedEvent.GetArrayIndex(name.ToString());
	}
	
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}

void ADmxWinchManager::ConfigureWinchObject()
{
	for (auto& each : Actors)
	{
		// each->ConfigureActor();
	}
}
