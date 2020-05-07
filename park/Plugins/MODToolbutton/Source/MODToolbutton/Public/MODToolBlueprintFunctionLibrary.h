// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"
#include "MODToolBlueprintFunctionLibrary.generated.h"


/**
 * 
 */



//UENUM(BlueprintType)
//enum class EVarType : uint8
//{
//	INT,
//	FLOAT,
//	STRUCT
//};


UCLASS()
class MODTOOLBUTTON_API UMODToolBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "EUW")
	static FString FileCreate(FString file_name, FString in);


	static TSharedPtr<FJsonObject> LoadJsonObject(FString file_name);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	static int GetJsonValueinteger(FString file_name, FString field_name);

	//UFUNCTION(BlueprintCallable, Category = "EUW")
	//static int ToInt64();

	UFUNCTION(BlueprintPure, Category = "EUW")
	static int64 StringToInt64(FString in);

	UFUNCTION(BlueprintPure, Category = "EUW")
	static FString int64ToString(int64 in);

	UFUNCTION(BlueprintPure, Category = "EUW")
	static TArray<FString> StringSort_Outint(TArray<FString> in);
	/*UFUNCTION(BlueprintCallable, Category = "EUW")
	static void CreatePackage2(UObject* obj, FString file_name);*/
};

