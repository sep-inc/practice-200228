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
		FString WaveName;
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

USTRUCT(BlueprintType)
struct FPrameBase {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		TArray<FString> var_name;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		TArray<FString> var_Type;

	TArray<void*> var_address;

	void AddVar(const char* name, const char* type, void* aa) {
		var_name.Add(name);
		//printf("%s", typeid(var).name());
		//FString kata = (char*)typeid(var).name();
		var_Type.Add(type);

		var_address.Add(aa);
	}


	void GetPrame(int32 index, FString& var_type, FVar& var) {
		if (var_name.Num() > index && index >= 0) {
			FString type = var_Type[index];

			if (type == "bool") {
				var.bool_var = *((bool*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "int") {
				var.int32_var = *((int32*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "float") {
				var.float_var = *((float*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "class FString") {
				var.string_var = *((FString*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "__int64") {
				var.int64_var = *((int64*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "class TArray<int, class TSizedDefaultAllocator<32> >") {
				var.array_int32 = *((TArray<int32>*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "struct FEnergy") {
				var.energy_var = *((FEnergy*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "struct FSpecialGage_P") {
				var.special_gage_p_var = *((FSpecialGage_P*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "struct FGuardCrash") {
				var.guard_crash_var = *((FGuardCrash*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "struct FSpecialGage_W") {
				var.special_gage_w_var = *((FSpecialGage_W*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "struct FTwoHandCorrections") {
				var.two_hand_corrections_var = *((FTwoHandCorrections*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "class TArray<struct FKnockBackLevels, class TSizedDefaultAllocator<32> >") {
				var.array_knockBackLevels_var = *((TArray<FKnockBackLevels>*)var_address[index]);
				var_type = type;
				return;
			}
		}
	}


	void SetPrame(int32 index, FVar var) {
		if (var_name.Num() > index && index >= 0) {
			FString type = var_Type[index];

			//prame.AddVar(TO_STRING(Damage), typeid(prame.Damage).name());	//const char* kata = typeid(a).name();

			//FString kata = typeid(a).name();
			if (type == "bool") {
				*((bool*)var_address[index]) = var.bool_var;
				return;
			}
			else if (type == "int") {
				*((int32*)var_address[index]) = var.int32_var;
				return;
			}
			else if (type == "float") {
				*((float*)var_address[index]) = var.float_var;
				return;
			}
			else if (type == "class FString") {
				*((FString*)var_address[index]) = var.string_var;
				return;
			}
			else if (type == "__int64") {
				*((int64*)var_address[index]) = var.int64_var;
				return;
			}
			else if (type == "class TArray<int, class TSizedDefaultAllocator<32> >") {
				*((TArray<int32>*)var_address[index]) = var.array_int32;
				return;
			}
			else if (type == "struct FEnergy") {
				*((FEnergy*)var_address[index]) = var.energy_var;
				return;
			}
			else if (type == "struct FSpecialGage_P") {
				*((FSpecialGage_P*)var_address[index]) = var.special_gage_p_var;
				return;
			}
			else if (type == "struct FGuardCrash") {
				*((FGuardCrash*)var_address[index]) = var.guard_crash_var;
				return;
			}
			else if (type == "struct FSpecialGage_W") {
				*((FSpecialGage_W*)var_address[index]) = var.special_gage_w_var;
				return;
			}
			else if (type == "struct FTwoHandCorrections") {
				*((FTwoHandCorrections*)var_address[index]) = var.two_hand_corrections_var;
				return;
			}
			else if (type == "class TArray<struct FKnockBackLevels,class TSizedDefaultAllocator<32> >") {
				*((TArray<FKnockBackLevels>*)var_address[index]) = var.array_knockBackLevels_var;
				printf("aaa");
				return;
			}
		}
	}

	FString GetType(int32 index) {
		if (var_Type[index] == "__int64") return "int64";
		return var_Type[index];
	}

	FString GetName(int32 index) {
		return var_name[index];
	}
};

UENUM(BlueprintType)
enum class EEnemySlotType : uint8
{
	None,
	SoldierFigment,
	SoldierRookie,
	SoldierVeteran,
	SoldierGeneral,
	SoldierElite,
	SoldierEliteEx,
	SoldierDefender,
	SwordsmanVeteran,
	SwordsmanGeneral,
	SwordsmanGeneralEx,
	SmallOne,
	SmallOneEx,
	SniperRookie,
	SniperVeteran,
	SniperGeneral,
	TankVeteran,
	TankGeneral,
	TankGeneralEx,
	Gargantua

};

UENUM(BlueprintType)
enum class EWeaponSlotType : uint8
{
	None,
	Type1,
	Type2,
	Type3,
	Type4
};

USTRUCT(BlueprintType)
struct FEnemyParam {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FPrameBase search;

	int start;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		EEnemySlotType id;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 SkippableWait;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FString EnemyId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FString Point;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 Count;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int32 Limit;
};

USTRUCT(BlueprintType)
struct FSpawnWeaponParam {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FPrameBase search;

	int start;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		EWeaponSlotType id;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FString SpawnPointActor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FString WeaponClass;

};


UENUM(BlueprintType)
enum class ESortType : uint8
{
	Name,
	Type
};

UENUM(BlueprintType)
enum class EMapType : uint8
{
	type1,
	type2,
	type3,
	MAX
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

	static void SetJsonFieldVal_Num(TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, double InNumber);

	static void SetJsonFieldVal_String(TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, const FString& InString);

	static void SetJsonFieldVal_Bool(TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, bool InBool);

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

