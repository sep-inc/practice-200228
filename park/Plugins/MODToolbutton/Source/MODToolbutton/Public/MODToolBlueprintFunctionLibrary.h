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
	//�t�@�C���쐬
	UFUNCTION(BlueprintCallable, Category = "EUW")
	static FString FileCreate(FString file_name, FString in);

	//Json�t�@�C����ǂݍ���
	static TSharedPtr<FJsonObject> LoadJsonObject(FString file_name);

	//Json�t�@�C���̒l��ǂݍ���
	UFUNCTION(BlueprintCallable, Category = "EUW")
	static int GetJsonValueinteger(FString file_name, FString field_name);

	//string��int64�ɕϊ�����
	UFUNCTION(BlueprintPure, Category = "EUW")
	static int64 StringToInt64(FString in);

	//int64��string�ɕϊ�����
	UFUNCTION(BlueprintPure, Category = "EUW")
	static FString int64ToString(int64 in);

	//string�\�[�g�i�A���t�@�x�b�g���j
	UFUNCTION(BlueprintCallable, Category = "EUW")
	static TArray<int32> StringSort_OutNum(TArray<FString> in, bool ascending_worder);
};

