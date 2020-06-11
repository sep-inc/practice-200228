﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Dom/JsonObject.h"
#include "Components/ScrollBox.h"
#include "MODToolEditorUtilityWidgetCPP.generated.h"

#define TO_STRING(VariableName) #VariableName





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
			else if (type == "class TArray<struct FKnockBackLevels, class TSizedDefaultAllocator<32> >") {
				var.array_knockBackLevels = *((TArray<FKnockBackLevels>*)var_address[index]);
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
			else if (type == "class TArray<struct FKnockBackLevels, class TSizedDefaultAllocator<32> >") {
				*((TArray<FKnockBackLevels>*)var_address[index]) = var.array_knockBackLevels;
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



//ここに追加した要素はUMODToolEditorUtilityWidgetCPPのコンストラクタで登録してください
USTRUCT(BlueprintType)
struct FPlayerDefaultParame{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FPrameBase search;

	int start;


	TArray<FKnockBackLevels> Health;								//プレイヤーのHP値。
	float AttackDamage;									//プレイヤーの持つ攻撃力。武器の攻撃力にこの数値が上乗せされます。
	int32 DrainHealthValuePerSeconds;					//１秒間に吸収できるライフマナの量。


	FEnergy energy;

	int32 SpecialGage_MaxValue;							//スタミナが回復するまでのインターバル。
	int32 SpecialGage_DecreaseSpeed;					//エンチャント発動中のスペシャルゲージ減少量(秒速)。
														//MaxValueが100で、DecreaseSpeedが10の場合、エンチャント効果時間は10秒になります。
	int32 SpecialGage_IncreaseValues_TakeDamage;		//敵からダメージを受けた時のスペシャルゲージ蓄積量。
	int32 SpecialGage_IncreaseValues_DodgeByVHS;		//敵の攻撃をタイミングよく回避した時のスペシャルゲージ蓄積量。

	float ResuscitateDelayTime;							//味方を蘇生するまでにかかる時間。
	float NotDominantHandDamageRate;					//利き手ではない手でのダメージ倍率。
	float NotDominantHandDamageRate_Throw;				//利き手ではない手での投げダメージ倍率。

	float KnockBackLevel1_Distance;						//ノックバック時に後退する距離。
	float KnockBackLevel1_Time;							//ノックバック時の後退時間。
	float KnockBackLevel1_WholeTime;					//ノックバック判定の全体時間。
	float KnockBackLevel1_CameraBackDistance;			//ノックバック時の3人称視点に移行した時のカメラの後退する距離。
	float KnockBackLevel1_CameraUpDistance;				//ノックバック時の3人称視点に移行した時のカメラの上昇する距離。

	float KnockBackLevel2_Distance;
	float KnockBackLevel2_Time;
	float KnockBackLevel2_WholeTime;
	float KnockBackLevel2_CameraBackDistance;
	float KnockBackLevel2_CameraUpDistance;

	float KnockBackLevel3_Distance;
	float KnockBackLevel3_Time;
	float KnockBackLevel3_WholeTime;
	float KnockBackLevel3_CameraBackDistance;
	float KnockBackLevel3_CameraUpDistance;

	float KnockBackLevel4_Distance;
	float KnockBackLevel4_Time;
	float KnockBackLevel4_WholeTime;
	float KnockBackLevel4_CameraBackDistance;
	float KnockBackLevel4_CameraUpDistance;

	float KnockBackLevel5_Distance;
	float KnockBackLevel5_Time;
	float KnockBackLevel5_WholeTime;
	float KnockBackLevel5_CameraBackDistance;
	float KnockBackLevel5_CameraUpDistance;

	float GuardCrash_Time;								//ガードクラッシュ状態の全体時間。
	float GuardCrash_CameraBackDistance;				//ガードクラッシュ時の3人称視点に移行した時のカメラの後退する距離。
	float GuardCrash_CameraUpDistance;					//ガードクラッシュ時の3人称視点に移行した時のカメラの上昇する距離。

	float VHSCoolDownTime;								//ステップを行った際のクールタイム。
};

USTRUCT(BlueprintType)
struct FPlayerMovementPrame {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FPrameBase search;

	int start;

	float ContinuedSpeedForward;						//通常移動時の前方向スピード（cm/s）
	float ContinuedSpeedBackward;						//通常移動時の後方向スピード（cm/s）
	float ContinuedSpeedHorizontal;						//通常移動時の横方向スピード（cm/s）

	float StepLengthForward;							//ステップ移動時の前方向移動量（cm）
	float StepLengthBackward;							//ステップ移動時の後方向移動量（cm）
	float StepLengthHorizontal;							//ステップ移動時の横方向移動量（cm）
	float StepMoveTime;									//ステップ移動にかかる時間（s）
	float StepRigidTime;								//ステップ移動後の硬直時間（s）

	float LockOnRotateSpeed;							//ロックオン時の回転スピード(degree/s)
														//これ以上ターゲットとの角度が離れるとロックオンが強制解除されます。
	float LockOnRotateLimit;							//ロックオン時の回転の限界角度(degree)
														//これ以上回転するとロックオンが強制解除されます。
	float LockOnHeadLimit;								//ロックオン時の頭の限界角度(degree)
														//これ以上首を振るとロックオンが強制解除されます。
	float LockOnDistanceLimit;							//ロックオン時プレイヤーとロックオンした敵の距離限界
														//これ以上距離が離れるとロックオンが強制解除されます。

	float TurnAngle;									//一回あたりの回転操作での回転量(degree)。
	float TurnAngleAuto;								//一回あたりの自動ターンでの回転量(degree)。
	float TurnTime;										//回転にかかる時間(s)。
	float TurnInterval;									//自動ターンが始まるまでのインターバル(s)。
	float FreeRotationSpeed;							//フリー回転のスピード。

};

USTRUCT(BlueprintType)
struct FWeaponParam {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FPrameBase search;

	int start;

	int32 ID;
	int32 DamageAmount;
	float MinimumDamageRate;
	int32 KnockBackAmount;
	float DamageAmountCorrectionRateByWeakPoint;
	float MaxPowerChargeTime;
	int32 EnergyDamageAmount;
	int32 EnergyDamageAmount_Parry;
	int32 Durability;
	float DurabilityDamageRate_Parry;
	float DurabilityDamageRate_Guard;
	float ParryThreshold;
	float WalkSpeed;
	float CrackDamageRate;
	float WearingRecoveryDurabilityAmount;
	FTwoHandCorrections TwoHandCorrections;
	FSpecialGage_W SpecialGage;
	float DamageAmountCorrectionRateByThrown;
	float KnockBackAmountCorrectionRateByThrown;
	float ConsumeDurabilityCorrectionRateByThrown;
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
	FString EnemyId;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FString Point;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 Count;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 Limit;
};


USTRUCT(BlueprintType)
struct FMapWaveParam{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	TArray<FEnemyParam> enemy;
};

USTRUCT(BlueprintType)
struct FMapQuestParam {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	TArray<FMapWaveParam> wave;

	FOtherList other_list;
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
	BOOL,
	INT,
	INT64,
	FLOAT,
	STRING,
	ARRAY_INT,
	ENERGY,
	ARRAY_KNOCKBACKLEVELS
};


UENUM(BlueprintType)
enum class EPrameType : uint8
{
	PlayerDefault,
	PlayerMovement,
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
	bool BOOL_var;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int32 INT_var;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	int64 INT64_type;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	float FLOAT_type;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FString STRING_type;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	TArray<int32> ARRAY_INT_type;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Prame")
	FEnergy ENERGY_type;


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

struct StartAddress
{
	int64 main_address;
	int64 max_address;
	int64 min_address;
};


UCLASS()
class MODTOOLBUTTON_API UMODToolEditorUtilityWidgetCPP : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	//パラメーター
	UPROPERTY(EditAnywhere, Category = "ModEUW")
		FPlayerDefaultParame player_default_param;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
		FPlayerMovementPrame player_movement_prame;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
		FWeaponParam weapon_param;

	UPROPERTY(EditAnywhere, Category = "ModEUW")
		FMapParam map_param;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ModEUW")
		TArray<FMapQuestParam> map_quest_param;

	int32 quest_num;

	TMap<EPrameType, FPrameBase> prames;

	TMap<EPrameType, FPrameBase> max_prames;
	TMap<EPrameType, FPrameBase> min_prames;

	TMap<EPrameType, UScrollBox*> prame_scroll_box;

	//書き出すパラメーター
	TArray<EPrameType> validity_parames;

	//最大値
	FPlayerDefaultParame player_default_param_max;
	FPlayerMovementPrame player_movement_max;
	FWeaponParam weapon_param_max;
	FMapParam map_param_max;
	FEnemyParam enemy_param_max;

	//最低値
	FPlayerDefaultParame player_default_param_min;
	FPlayerMovementPrame player_movement_min;
	FWeaponParam weapon_param_min;
	FMapParam map_param_min;
	FEnemyParam enemy_param_min;


	UMODToolEditorUtilityWidgetCPP();
	~UMODToolEditorUtilityWidgetCPP();

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void Initialization(TMap<EPrameType, UScrollBox*> set_scroll_box);

	void InitPlayerDefaultParame();
	void InitPlayerMovementPrameParame();
	void InitWeaponParam();

	void SetPrames();

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void CreateLocalMod(FString mod_name);

	void AddPrame(EPrameType type, StartAddress s_a, const char* name, const char* var_type, void* aa);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	bool AddValidityParames(EPrameType type);

	void AddEnemyPrame(const char* name, const char* type, void* aa);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void AddWave();

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void AddQuest();

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void InsertWave(int32 index);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void RemoveWave(int32 index);

	UFUNCTION(BlueprintPure, Category = "EUW")
	void GetPrame(EPrameType prameType, int32 index, FString& var_type, FVar& var) {
		prames[prameType].GetPrame(index, var_type, var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void SetPrame(EPrameType prameType, int32 index, FVar var) {
		prames[prameType].SetPrame(index, var);
	}


	UFUNCTION(BlueprintPure, Category = "EUW")
	FString GetType(FPrameBase prame, int32 index) {
		if (prame.var_Type[index] == "__int64") return "int64";
		return prame.var_Type[index];
	}
	
	UFUNCTION(BlueprintPure, Category = "EUW")
	FVar CreateVarBOOL(bool in) {
		FVar var;
		var.bool_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FVar CreateVarINT(int32 in) {
		FVar var;
		var.int32_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FVar CreateVarINT64(int64 in) {
		FVar var;
		var.int64_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FVar CreateVarFLOAT(float in) {
		FVar var;
		var.float_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FVar CreateVarSTRING(FString in) {
		FVar var;
		var.string_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FVar CreateVarARRAY_INT(TArray<int32> in) {
		FVar var;
		var.array_int32 = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		FVar CreateVarENERGY(FEnergy in) {
		FVar var;
		var.energy_var = in;
		return var;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		FVar CreateVarARRAY_KNOCKBACKLEVELS(TArray<FKnockBackLevels> in) {
		FVar var;
		var.array_knockBackLevels = in;
		return var;
	}

	

	UFUNCTION(BlueprintPure, Category = "EUW")
	TMap<EPrameType, FPrameBase>GetPrames() {
		return prames;
	}


	UFUNCTION(BlueprintPure, Category = "EUW")
	TMap<EPrameType, UScrollBox*> GetPrame_scroll_box() {
		return prame_scroll_box;
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		FPlayerDefaultParame GetPlayerDefaultParame() {
		return player_default_param;
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
		FPlayerMovementPrame GetPlayerMovementPrame() {
		return player_movement_prame;
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
		return map_quest_param[quest_num - 1].wave.Num();
	}


	UFUNCTION(BlueprintCallable, Category = "EUW")
	void GetEnemyPrame(int32 wave,int32 index,int32 var_num, FString& var_type, FVar& var) {
		map_quest_param[quest_num - 1].wave[wave - 1].enemy[index].search.GetPrame(var_num, var_type, var);
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
	FMapWaveParam GetMapWavePrame(int32 index) {
		return map_quest_param[quest_num - 1].wave[index];
	}

	UFUNCTION(BlueprintPure, Category = "EUW")
		FString GetMapWaveEnemyId(int32 wave,int32 index) {
		return map_quest_param[quest_num - 1].wave[wave - 1].enemy[index].EnemyId;
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void SetEnemyPrame(int32 wave, int32 index, int32 var_num, FVar var) {
		map_quest_param[quest_num - 1].wave[wave - 1].enemy[index].search.SetPrame(var_num, var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void SetMapWavePrame(int32 Wave, FMapWaveParam in) {
		map_quest_param[quest_num - 1].wave[Wave - 1] = in;
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void SetMapWaveEnemyId(int32 Wave, int32 index, FString id) {
		map_quest_param[quest_num - 1].wave[Wave - 1].enemy[index].EnemyId = id;
	}


	//最大パラメーターゲット
	UFUNCTION(BlueprintCallable, Category = "EUW")
	void GetMaxPrame(EPrameType prameType, int32 index, FString& var_type, FVar& var) {
		max_prames[prameType].GetPrame(index, var_type, var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMaxEnemyPrame(int32 index, FString& var_type, FVar& var) {
		enemy_param_max.search.GetPrame(index, var_type, var);
	}

	//最小パラメーターゲット
	UFUNCTION(BlueprintCallable, Category = "EUW")
		void GetMinPrame(EPrameType prameType, int32 index, FString& var_type, FVar& var) {
		min_prames[prameType].GetPrame(index, var_type, var);
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void GetMinEnemyPrame(int32 index, FString& var_type, FVar& var) {
		enemy_param_min.search.GetPrame(index, var_type, var);
	}

	
private:

	TArray<VarPra> map_wave_param_addres;
	FEnemyParam enemy_param_measurement;		//計測用


};
