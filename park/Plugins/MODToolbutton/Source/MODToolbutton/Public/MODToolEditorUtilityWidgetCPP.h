// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Dom/JsonObject.h"
#include "MODToolEditorUtilityWidgetCPP.generated.h"

#define TO_STRING(VariableName) #VariableName

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPrameBase {
	GENERATED_USTRUCT_BODY()

	TArray<FString> var_name;
	TArray<FString> var_Type;
	TArray<void*> var_address;

	void AddVar(const char* name, const char* type, void* aa) {
		var_name.Add(name);
		//printf("%s", typeid(var).name());
		//FString kata = (char*)typeid(var).name();
		var_Type.Add(type);

		var_address.Add(aa);
	}

	void GetPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		if (var_name.Num() > index && index >= 0) {
			FString type = var_Type[index];

			if (type == "int") {
				out1 = *((int32*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "float") {
				out2 = *((float*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "class FString") {
				out3 = *((FString*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "__int64") {
				out4 = *((int64*)var_address[index]);
				var_type = type;
				return;
			}

			var_type = type;
		}
	}

	void SetPrame(int32 index, int32 in1, float in2, FString in3, int64 in4) {
		if (var_name.Num() > index && index >= 0) {
			FString type = var_Type[index];

			//prame.AddVar(TO_STRING(Damage), typeid(prame.Damage).name());	//const char* kata = typeid(a).name();

			//FString kata = typeid(a).name();
			if (type == "int") {
				*((int32*)var_address[index]) = in1;
				return;
			}
			else if (type == "float") {
				*((float*)var_address[index]) = in2;
				return;
			}
			else if (type == "class FString") {
				*((FString*)var_address[index]) = in3;
				return;
			}
			else if (type == "__int64") {
				*((int64*)var_address[index]) = in4;
				return;
			}
		}
	}
};

//ここに追加した要素はUMODToolEditorUtilityWidgetCPPのコンストラクタで登録してください
USTRUCT(BlueprintType)
struct FPlayerParam : public FPrameBase{
	GENERATED_USTRUCT_BODY()

	int start;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	float Health;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	float Attack;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int64 Defense;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	float Speed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 int32_var;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	float float_var;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FString string_var;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int64 int64_var;

};

USTRUCT(BlueprintType)
struct FWeaponParam : public FPrameBase {
	GENERATED_USTRUCT_BODY()

		int start;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float Durability;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float Attack;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int64 Defense;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float Weight;

};

USTRUCT(BlueprintType)
struct FMapParam : public FPrameBase {
	GENERATED_USTRUCT_BODY()

		int start;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
			float Health;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float Attack;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		int64 Defense;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float Speed;

	//攻撃モーションスピード
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FString test4;

	//攻撃モーションスピード
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		float test5;

};

USTRUCT(BlueprintType)
struct FMapWaveParam{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		TArray<int32> enemy_id;

};


UENUM(BlueprintType)
enum class EPrameType : uint8
{
	Player,
	Weapons,
	Map
};

UCLASS()
class MODTOOLBUTTON_API UMODToolEditorUtilityWidgetCPP : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UMODToolEditorUtilityWidgetCPP();

	void AddPlayerPrame(const char* name, const char* type, void* aa);
	void AddWeaponPrame(const char* name, const char* type, void* aa);
	void AddMapPrame(const char* name, const char* type, void* aa);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void AddWave();


	//ゲッター
	UFUNCTION(BlueprintPure, Category = "EUW")
	int32 GetPlayerPrameItemCount() {
		return player_param.var_name.Num();
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		int32 GetWeaponPrameItemCount() {
		return weapon_param.var_name.Num();
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		int32 GetMapPrameItemCount() {
		return map_param.var_name.Num();
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetPlayerPrameName(int32 index) {
		return player_param.var_name[index];
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetWeaponPrameName(int32 index) {
		return weapon_param.var_name[index];
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetMapPrameName(int32 index) {
		return map_param.var_name[index];
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetPlayerPrameType(int32 index) {
		if (player_param.var_Type[index] == "__int64") return "int64";
		return player_param.var_Type[index];
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetWeaponPrameType(int32 index) {
		if (weapon_param.var_Type[index] == "__int64") return "int64";
		return weapon_param.var_Type[index];
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetMapPrameType(int32 index) {
		if (map_param.var_Type[index] == "__int64") return "int64";
		return map_param.var_Type[index];
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	int32 GetMaxWaveNum() {
		return map_wave_param.Num();
	}

	//パラメーターゲット
	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetPlayerPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		player_param.GetPrame(index, var_type, out1, out2, out3, out4);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetWeaponPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		weapon_param.GetPrame(index, var_type, out1, out2, out3, out4);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMapPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		map_param.GetPrame(index, var_type, out1, out2, out3, out4);
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FMapWaveParam GetMapWavePrame(int32 index) {
		return map_wave_param[index];
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	int32 GetMapWaveEnemyId(int32 wave,int32 index) {
		return map_wave_param[wave - 1].enemy_id[index];
	}

	//最大パラメーターゲット
	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMaxPlayerPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		player_param_max.GetPrame(index, var_type, out1, out2, out3, out4);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMaxWeaponPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		weapon_param_max.GetPrame(index, var_type, out1, out2, out3, out4);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMaxMapPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		map_param_max.GetPrame(index, var_type, out1, out2, out3, out4);
	}

	//最小パラメーターゲット
	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMinPlayerPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		player_param_min.GetPrame(index, var_type, out1, out2, out3, out4);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMinWeaponPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		weapon_param_min.GetPrame(index, var_type, out1, out2, out3, out4);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMinMapPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
		map_param_min.GetPrame(index, var_type, out1, out2, out3, out4);
	}

	//セット
	UFUNCTION(BlueprintCallable, Category = "EUW")
		void SetPlayerPrame(int32 index, int32 in1, float in2, FString in3, int64 in4) {
		player_param.SetPrame(index, in1, in2, in3, in4);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void SetWeaponPrame(int32 index, int32 in1, float in2, FString in3, int64 in4) {
		weapon_param.SetPrame(index, in1, in2, in3, in4);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void SetMapPrame(int32 index, int32 in1, float in2, FString in3, int64 in4) {
		map_param.SetPrame(index, in1, in2, in3, in4);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void SetMapWavePrame(int32 Wave,FMapWaveParam in) {
		map_wave_param[Wave - 1] = in;
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void SetMapWaveEnemyId(int32 Wave, int32 index,int32 id) {
		map_wave_param[Wave - 1].enemy_id[index] = id;
	}

	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FPlayerParam player_param;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FWeaponParam weapon_param;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FMapParam map_param;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModEUW")
	TArray<FMapWaveParam> map_wave_param;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FPlayerParam player_param_max;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FWeaponParam weapon_param_max;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FMapParam map_param_max;


	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FPlayerParam player_param_min;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FWeaponParam weapon_param_min;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FMapParam map_param_min;


};
