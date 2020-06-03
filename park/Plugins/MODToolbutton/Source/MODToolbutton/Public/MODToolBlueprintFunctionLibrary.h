// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"
#include "MODToolBlueprintFunctionLibrary.generated.h"


/**
 * 
 */



UENUM(BlueprintType)
enum class ESortType : uint8
{
	Name,
	Type
};


UCLASS()
class MODTOOLBUTTON_API UMODToolBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()
public:
	//ファイル作成
	UFUNCTION(BlueprintCallable, Category = "EUW")
	static FString FileCreate(FString file_name, FString in);

	//Jsonファイルを読み込む
	static TSharedPtr<FJsonObject> LoadJsonObject(FString file_name);

	//Jsonファイルの値を読み込む
	UFUNCTION(BlueprintCallable, Category = "EUW")
	static int GetJsonValueinteger(FString file_name, FString field_name);

	//stringをint64に変換する
	UFUNCTION(BlueprintPure, Category = "EUW")
	static int64 StringToInt64(FString in);

	//int64をstringに変換する
	UFUNCTION(BlueprintPure, Category = "EUW")
	static FString int64ToString(int64 in);

	//stringソート（アルファベット順）
	UFUNCTION(BlueprintCallable, Category = "EUW")
	static TArray<int32> StringSort_OutNum(TArray<FString> in, bool ascending_worder);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	static void CreateModPackage(bool& ErrorFrag);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	static void GetPackageFolderNames(TArray<FString>& out);


};

