// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DmxWinch.generated.h"

UCLASS()
class DMXWINCHVIS_API ADmxWinch : public AActor
{
	GENERATED_BODY()

public:
	ADmxWinch();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D objectMatrix;
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> actors;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<uint8> dmxValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<int> selectedUniverses;

private:
	TArray<UStaticMesh*> _staticMeshes;
};
