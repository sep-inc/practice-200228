// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"
#include "Dom/JsonObject.h"
#include "EUWBlueprintFunctionLibrary.generated.h"

//using FPakInputPair;

//bool CreatePakFile(const TCHAR* Filename, TArray<FPakInputPair>& FilesToAdd, const FPakCommandLineParameters& CmdLineParameters, const FKeyChain& InKeyChain);

/**
 * 
 */

UCLASS()
class TEST_API UEUWBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable)
	//	static void RunEditorUtilityWidget(UWidgetBlueprint* Blueprint);

	//UFUNCTION(BlueprintCallable)
	//	static void RunWidget(UWidgetBlueprint* Blueprint);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	static FString FileCreate(FString file_name, FString in);



	static TSharedPtr<FJsonObject> LoadJsonObject(FString file_name);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	static int GetJsonValueinteger(FString file_name, FString field_name);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	static void CreatePackage2(UObject* obj,FString file_name);

	FString PackageFolder();
};
