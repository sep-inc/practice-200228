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
struct FIncreaseValues_P {
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 TakeDamage;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 DodgeByVHS;
};

USTRUCT(BlueprintType)
struct FSpecialGage_P {
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 MaxValue;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 DecreaseSpeed;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FIncreaseValues_P IncreaseValues;
};

USTRUCT(BlueprintType)
struct FGuardCrash {
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float Time;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float CameraBackDistance;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float CameraUpDistance;
};

USTRUCT(BlueprintType)
struct FOtherList {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 Id;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FString Name;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FString Level;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float LifeManaRate;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 MapColor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		bool bNextLevelEnable;
};

USTRUCT(BlueprintType)
struct FKnockBackLevels {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 Level;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float Distance;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float Time;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float WholeTime;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float CameraBackDistance;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float CameraUpDistance;
};

USTRUCT(BlueprintType)
struct FTwoHandCorrections {
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float DamageAmount;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float KnockBackAmount;
};

USTRUCT(BlueprintType)
struct FIncreaseValues_W {
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 Hit;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 Guard;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 Parry;

};

USTRUCT(BlueprintType)
struct FSpecialGage_W {
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FIncreaseValues_W IncreaseValues;
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
	FSpecialGage_P special_gage_p_var;
	FGuardCrash guard_crash_var;
	FSpecialGage_W special_gage_w_var;
	FTwoHandCorrections two_hand_corrections_var;
	TArray<FKnockBackLevels> array_knockBackLevels_var;
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

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FSpecialGage_P GetVarSPECIAL_GAGE_P(FVar var) {
		return var.special_gage_p_var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FGuardCrash GetVarGUARD_CRASH(FVar var) {
		return var.guard_crash_var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FSpecialGage_W GetVarSPECIAL_GAGE_W(FVar var) {
		return var.special_gage_w_var;
	}
	
	UFUNCTION(BlueprintPure, Category = "EUW")
		static FTwoHandCorrections GetVarTWO_HAND_CORRECTIONS(FVar var) {
		return var.two_hand_corrections_var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static TArray<FKnockBackLevels> GetVarARRAY_KNOCKBACKLEVELS(FVar var) {
		return var.array_knockBackLevels_var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarBOOL(bool in) {
		FVar var;
		var.bool_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarINT(int32 in) {
		FVar var;
		var.int32_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarINT64(int64 in) {
		FVar var;
		var.int64_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarFLOAT(float in) {
		FVar var;
		var.float_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarSTRING(FString in) {
		FVar var;
		var.string_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarARRAY_INT(TArray<int32> in) {
		FVar var;
		var.array_int32 = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarENERGY(FEnergy in) {
		FVar var;
		var.energy_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarSPECIAL_GAGE_P(FSpecialGage_P in) {
		FVar var;
		var.special_gage_p_var = in;
		return var;
	}


	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarGUARD_CRASH(FGuardCrash in) {
		FVar var;
		var.guard_crash_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarSPECIAL_GAGE_W(FSpecialGage_W in) {
		FVar var;
		var.special_gage_w_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarTWO_HAND_CORRECTIONS(FTwoHandCorrections in) {
		FVar var;
		var.two_hand_corrections_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		static FVar CreateVarARRAY_KNOCKBACKLEVELS(TArray<FKnockBackLevels> in) {
		FVar var;
		var.array_knockBackLevels_var = in;
		return var;
	}

};

