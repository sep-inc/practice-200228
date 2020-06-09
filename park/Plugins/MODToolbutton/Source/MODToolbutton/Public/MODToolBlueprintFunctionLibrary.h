// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"
#include "MODToolBlueprintFunctionLibrary.generated.h"


/**
 * 
 */

USTRUCT(BlueprintType)
struct FEnergy {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 MaxValue;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 DelaySecondsForIncrementValue;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 IncrementValuePerSecond;
};


USTRUCT(BlueprintType)
struct FVar {
	GENERATED_USTRUCT_BODY()

		bool bool_var;
	int32 int32_var;
	float float_var;
	FString string_var;
	int64 int64_var;
	TArray<int32> array_int32;
	FEnergy energy_var;
};


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

	//ゲッター
	UFUNCTION(BlueprintPure, Category = "EUW")
		static bool GetVarBOOL(FVar var) {
		return var.bool_var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static int32 GetVarINT(FVar var) {
		return var.int32_var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static int64 GetVarINT64(FVar var) {
		return var.int64_var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static float GetVarFLOAT(FVar var) {
		return var.float_var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FString GetVarSTRING(FVar var) {
		return var.string_var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static TArray<int32> GetVarARRAY_INT(FVar var) {
		return var.array_int32;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FEnergy GetVarENERGY(FVar var) {
		return var.energy_var;
	}


};

