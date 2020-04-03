// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartEuwCPP.generated.h"

UCLASS()
class PARK_API AStartEuwCPP : public AActor
{
	GENERATED_BODY()
	
public:	

	// The default action called when the widget is invoked if bAutoRunDefaultAction=true (it is never called otherwise)
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vehicle")
	void StartEUW();

	// Sets default values for this actor's properties
	AStartEuwCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
