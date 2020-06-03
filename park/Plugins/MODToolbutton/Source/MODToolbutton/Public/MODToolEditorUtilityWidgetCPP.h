// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Dom/JsonObject.h"
#include "Components/ScrollBox.h"
#include "MODToolEditorUtilityWidgetCPP.generated.h"

#define TO_STRING(VariableName) #VariableName

/**
 * 
 */
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

	
	void GetPrame(int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		if (var_name.Num() > index && index >= 0) {
			FString type = var_Type[index];

			if (type == "int") {
				int32_var = *((int32*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "float") {
				float_var = *((float*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "class FString") {
				string_var = *((FString*)var_address[index]);
				var_type = type;
				return;
			}
			else if (type == "__int64") {
				int64_var = *((int64*)var_address[index]);
				var_type = type;
				return;
			}

			var_type = type;
		}
	}

	
	void SetPrame(int32 index, int32 int32_var, float float_var, FString string_var, int64 int64_var) {
		if (var_name.Num() > index && index >= 0) {
			FString type = var_Type[index];

			//prame.AddVar(TO_STRING(Damage), typeid(prame.Damage).name());	//const char* kata = typeid(a).name();

			//FString kata = typeid(a).name();
			if (type == "int") {
				*((int32*)var_address[index]) = int32_var;
				return;
			}
			else if (type == "float") {
				*((float*)var_address[index]) = float_var;
				return;
			}
			else if (type == "class FString") {
				*((FString*)var_address[index]) = string_var;
				return;
			}
			else if (type == "__int64") {
				*((int64*)var_address[index]) = int64_var;
				return;
			}
		}
	}

	FString GetType(int32 index) {
		if (var_Type[index] == "__int64") return "int64";
		return var_Type[index];
	}
};

USTRUCT(BlueprintType)
struct FVar{
	GENERATED_USTRUCT_BODY()
	
	int32 int32_var;
	float float_var;
	FString string_var;
	int64 int64_var;
};


//ここに追加した要素はUMODToolEditorUtilityWidgetCPPのコンストラクタで登録してください
USTRUCT(BlueprintType)
struct FPlayerParam{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FPrameBase search;

	int start;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 Health;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 Attack;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 Defense;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 Speed;

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
struct FPlayerMovement {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FPrameBase search;

	int start;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	float ContinuedSpeedForward;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	float ContinuedSpeedBackward;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	float ContinuedSpeedHorizontal;

};

USTRUCT(BlueprintType)
struct FWeaponParam {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FPrameBase search;

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
struct FMapParam {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FPrameBase search;

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
struct FEnemyParam {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
		FPrameBase search;

	int start;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 id;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 param1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 param2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 param3;
};


USTRUCT(BlueprintType)
struct FMapWaveParam{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	TArray<FEnemyParam> enemy;

};

UENUM(BlueprintType)
enum class EUnDoType : uint8
{
	Prame,
	Wave
};

UENUM(BlueprintType)
enum class EVarType : uint8
{
	INT,
	INT64,
	FLOAT,
	STRING
};


UENUM(BlueprintType)
enum class EPrameType : uint8
{
	Player,
	Weapons,
	Map
};

USTRUCT(BlueprintType)
struct FUnDoLog {
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	//EUnDoType un_do_type;

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	//EPrameType prame_type;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	EVarType var_type;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 index;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 INT_var;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int64 INT64_type;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	float FLOAT_type;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FString STRING_type;

};



UENUM(BlueprintType)
enum class EMainWidgetName : uint8
{
	Parameter,
	Map,
	ModList,
	AssetList,
	MainMenu
};

UENUM(BlueprintType)
enum class EFilterType : uint8
{
	All,
	Blueprint,
	Material,
	WidgetBlueprint,
	ParticleSystem,
	World,
	BlackboardData,
	BehaviorTree,
	AnimBlueprint,
	NONE
};

struct VarPra
{
	FString name;
	FString type;
	int32 byte_count;
};


UCLASS()
class MODTOOLBUTTON_API UMODToolEditorUtilityWidgetCPP : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	//パラメーター
	UPROPERTY(EditAnywhere, Category = "ModEUW")
		FPlayerParam player_param;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
		FWeaponParam weapon_param;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
		FMapParam map_param;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModEUW")
		TArray<FMapWaveParam> map_wave_param;

	TMap<EPrameType, FPrameBase> prames;

	TMap<EPrameType, UScrollBox*> prame_scroll_box;



	//最大値
	FPlayerParam player_param_max;
	FWeaponParam weapon_param_max;
	FMapParam map_param_max;
	FEnemyParam enemy_param_max;

	//最低値
	FPlayerParam player_param_min;
	FWeaponParam weapon_param_min;
	FMapParam map_param_min;
	FEnemyParam enemy_param_min;


	UMODToolEditorUtilityWidgetCPP();
	~UMODToolEditorUtilityWidgetCPP();

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void Initialization(TMap<EPrameType, UScrollBox*> set_scroll_box);

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void Initialization(TMap<EPrameType, UScrollBox*> set_scroll_box);


	void AddPlayerPrame(const char* name, const char* type, void* aa);
	void AddWeaponPrame(const char* name, const char* type, void* aa);
	void AddMapPrame(const char* name, const char* type, void* aa);
	void AddEnemyPrame(const char* name, const char* type, void* aa);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void AddWave();

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void InsertWave(int32 index);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void RemoveWave(int32 index);

	UFUNCTION(BlueprintPure, Category = "EUW")
	void GetPrame(EPrameType prameType, int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		prames[prameType].GetPrame(index, var_type, int32_var, float_var, string_var, int64_var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void SetPrame(EPrameType prameType, int32 index, int32 int32_var, float float_var, FString string_var, int64 int64_var) {
		prames[prameType].SetPrame(index, int32_var, float_var, string_var, int64_var);
	}


	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetType(FPrameBase prame, int32 index) {
		if (prame.var_Type[index] == "__int64") return "int64";
		return prame.var_Type[index];
	}
	
	//ゲッター

	UFUNCTION(BlueprintPure, Category = "EUW")
	TMap<EPrameType, FPrameBase>GetPrames() {
		return prames;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	TMap<EPrameType, UScrollBox*> GetPrame_scroll_box() {
		return prame_scroll_box;
	}




	UFUNCTION(BlueprintPure, Category = "EUW")
		FPlayerParam GetPlayerParam() {
		return player_param;
	}
	UFUNCTION(BlueprintPure, Category = "EUW")
		FWeaponParam GetWeaponParam() {
		return weapon_param;
	}
	UFUNCTION(BlueprintPure, Category = "EUW")
		FMapParam GetMapParam() {
		return map_param;
	}


	UFUNCTION(BlueprintPure, Category = "EUW")
		int32 GetEnemyPrameItemCount() {
		return map_wave_param_addres.Num();
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetEnemyPrameName(int32 index) {
		return map_wave_param_addres[index].name;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetEnemyPrameType(int32 index) {
		if (map_wave_param_addres[index].type == "__int64") return "int64";
		return map_wave_param_addres[index].type;
	}


	UFUNCTION(BlueprintPure, Category = "EUW")
	int32 GetMaxWaveNum() {
		return map_wave_param.Num();
	}


	UFUNCTION(BlueprintCallable, Category = "EUW")
	void GetEnemyPrame(int32 wave,int32 index,int32 var_num, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		map_wave_param[wave - 1].enemy[index].search.GetPrame(var_num, var_type, int32_var, float_var, string_var, int64_var);
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FMapWaveParam GetMapWavePrame(int32 index) {
		return map_wave_param[index];
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	int32 GetMapWaveEnemyId(int32 wave,int32 index) {
		return map_wave_param[wave - 1].enemy[index].id;
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void SetEnemyPrame(int32 wave, int32 index, int32 var_num, int32 int32_var, float float_var, FString string_var, int64 int64_var) {
		map_wave_param[wave - 1].enemy[index].search.SetPrame(var_num, int32_var, float_var, string_var, int64_var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void SetMapWavePrame(int32 Wave, FMapWaveParam in) {
		map_wave_param[Wave - 1] = in;
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void SetMapWaveEnemyId(int32 Wave, int32 index, int32 id) {
		map_wave_param[Wave - 1].enemy[index].id = id;
	}

	//最大パラメーターゲット
	UFUNCTION(BlueprintCallable, Category = "EUW")
	void GetMaxPlayerPrame(int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		player_param_max.search.GetPrame(index, var_type, int32_var, float_var, string_var, int64_var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMaxWeaponPrame(int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		weapon_param_max.search.GetPrame(index, var_type, int32_var, float_var, string_var, int64_var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMaxMapPrame(int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		map_param_max.search.GetPrame(index, var_type, int32_var, float_var, string_var, int64_var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMaxEnemyPrame(int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		enemy_param_max.search.GetPrame(index, var_type, int32_var, float_var, string_var, int64_var);
	}

	//最小パラメーターゲット
	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMinPlayerPrame(int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		player_param_min.search.GetPrame(index, var_type, int32_var, float_var, string_var, int64_var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMinWeaponPrame(int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		weapon_param_min.search.GetPrame(index, var_type, int32_var, float_var, string_var, int64_var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMinMapPrame(int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		map_param_min.search.GetPrame(index, var_type, int32_var, float_var, string_var, int64_var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void GetMinEnemyPrame(int32 index, FString& var_type, int32& int32_var, float& float_var, FString& string_var, int64& int64_var) {
		enemy_param_min.search.GetPrame(index, var_type, int32_var, float_var, string_var, int64_var);
	}



	
private:

	TArray<VarPra> map_wave_param_addres;
	FEnemyParam enemy_param_measurement;		//計測用


};
