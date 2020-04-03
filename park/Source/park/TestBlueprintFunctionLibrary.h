// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"
#include "TestBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PARK_API UTestBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		static void RunEditorUtilityWidget(UWidgetBlueprint* Blueprint);

	UFUNCTION(BlueprintCallable)
		static void RunWidget(UWidgetBlueprint* Blueprint);
};
