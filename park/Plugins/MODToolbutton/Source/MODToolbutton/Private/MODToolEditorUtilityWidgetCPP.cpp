// Fill out your copyright notice in the Description page of Project Settings.
#include "MODToolEditorUtilityWidgetCPP.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "IPlatformFilePak.h"
#include "Dom/JsonObject.h"
#include "MODToolBlueprintFunctionLibrary.h"



#include <typeinfo>

UMODToolEditorUtilityWidgetCPP::UMODToolEditorUtilityWidgetCPP() {

	SetPrames();

	InitPlayerDefaultParame();
	InitPlayerMovementPrameParame();
	InitWeaponParam();
	
	//マップパラメーター
	StartAddress map_param_start;
	map_param_start.main_address = (int64)(&map_param.start);
	map_param_start.max_address = (int64)(&map_param_max.start);
	map_param_start.min_address = (int64)(&map_param_min.start);

	map_param_max.Health = 300;
	map_param_min.Health = 0;
	AddPrame(EPrameType::Map, map_param_start,
		TO_STRING(Health), typeid(map_param.Health).name(), &map_param.Health);
	map_param_max.Attack = 300;
	map_param_min.Attack = 0;
	AddPrame(EPrameType::Map, map_param_start,
		TO_STRING(Attack), typeid(map_param.Attack).name(), &map_param.Attack);
	map_param_max.Defense = 300;
	map_param_min.Defense = 0;
	AddPrame(EPrameType::Map, map_param_start,
		TO_STRING(Defense), typeid(map_param.Defense).name(), &map_param.Defense);
	map_param_max.Speed = 300;
	map_param_min.Speed = 0;
	AddPrame(EPrameType::Map, map_param_start,
		TO_STRING(Speed), typeid(map_param.Speed).name(), &map_param.Speed);
	map_param_max.test4 = "";
	map_param_min.test4 = "";
	AddPrame(EPrameType::Map, map_param_start,
		TO_STRING(test4), typeid(map_param.test4).name(), &map_param.test4);
	map_param_max.test5 = 300;
	map_param_min.test5 = 0;
	AddPrame(EPrameType::Map, map_param_start,
		TO_STRING(test5), typeid(map_param.test5).name(), &map_param.test5);

	//エネミーパラメーター
	//enemy_param_max.EnemyId = 400;
	//enemy_param_min.EnemyId = 0;
	AddEnemyPrame(TO_STRING(EnemyId), typeid(enemy_param_measurement.EnemyId).name(), &enemy_param_measurement.EnemyId);
	//enemy_param_max.Point = 400;
	//enemy_param_min.Point = 0;
	AddEnemyPrame(TO_STRING(Point), typeid(enemy_param_measurement.Point).name(), &enemy_param_measurement.Point);
	enemy_param_max.Count = 400;
	enemy_param_min.Count = 0;
	AddEnemyPrame(TO_STRING(Count), typeid(enemy_param_measurement.Count).name(), &enemy_param_measurement.Count);
	enemy_param_max.Limit = 400;
	enemy_param_min.Limit = 0;
	AddEnemyPrame(TO_STRING(Limit), typeid(enemy_param_measurement.Limit).name(), &enemy_param_measurement.Limit);

}

UMODToolEditorUtilityWidgetCPP::~UMODToolEditorUtilityWidgetCPP() {

}


void UMODToolEditorUtilityWidgetCPP::Initialization(TMap<EPrameType, UScrollBox*> set_scroll_box) {

	prame_scroll_box = set_scroll_box;
	//SetPrames();
}

void UMODToolEditorUtilityWidgetCPP::InitPlayerDefaultParame() {

	//プレイヤーパラメーター
	StartAddress player_parame_start;
	player_parame_start.main_address = (int64)(&player_default_param.start);
	player_parame_start.max_address = (int64)(&player_default_param_max.start);
	player_parame_start.min_address = (int64)(&player_default_param_min.start);

	//player_default_param_max.Health = 100;
	//player_default_param_min.Health = 0;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(Health), typeid(player_default_param.Health).name(), &player_default_param.Health);
	player_default_param_max.AttackDamage = 100.f;
	player_default_param_min.AttackDamage = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(AttackDamage), typeid(player_default_param.AttackDamage).name(), &player_default_param.AttackDamage);
	player_default_param_max.DrainHealthValuePerSeconds = 100.f;
	player_default_param_min.DrainHealthValuePerSeconds = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(DrainHealthValuePerSeconds), typeid(player_default_param.DrainHealthValuePerSeconds).name(), &player_default_param.DrainHealthValuePerSeconds);



	player_default_param_max.energy.MaxValue = 100.f;
	player_default_param_min.energy.MaxValue = 0.f;
	player_default_param_max.energy.DelaySecondsForIncrementValue = 100.f;
	player_default_param_min.energy.DelaySecondsForIncrementValue = 0.f;
	player_default_param_max.energy.IncrementValuePerSecond = 100;
	player_default_param_min.energy.IncrementValuePerSecond = 0;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(Energy), typeid(player_default_param.energy).name(), &player_default_param.energy);
	

	player_default_param_max.SpecialGage_MaxValue = 100.f;
	player_default_param_min.SpecialGage_MaxValue = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(SpecialGage_MaxValue), typeid(player_default_param.SpecialGage_MaxValue).name(), &player_default_param.SpecialGage_MaxValue);
	player_default_param_max.SpecialGage_DecreaseSpeed = 100.f;
	player_default_param_min.SpecialGage_DecreaseSpeed = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(SpecialGage_DecreaseSpeed), typeid(player_default_param.SpecialGage_DecreaseSpeed).name(), &player_default_param.SpecialGage_DecreaseSpeed);
	player_default_param_max.SpecialGage_IncreaseValues_TakeDamage = 100.f;
	player_default_param_min.SpecialGage_IncreaseValues_TakeDamage = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(SpecialGage_IncreaseValues_TakeDamage), typeid(player_default_param.SpecialGage_IncreaseValues_TakeDamage).name(), &player_default_param.SpecialGage_IncreaseValues_TakeDamage);
	player_default_param_max.SpecialGage_IncreaseValues_DodgeByVHS = 100.f;
	player_default_param_min.SpecialGage_IncreaseValues_DodgeByVHS = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(SpecialGage_IncreaseValues_DodgeByVHS), typeid(player_default_param.SpecialGage_IncreaseValues_DodgeByVHS).name(), &player_default_param.SpecialGage_IncreaseValues_DodgeByVHS);



	player_default_param_max.ResuscitateDelayTime = 100.f;
	player_default_param_min.ResuscitateDelayTime = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(ResuscitateDelayTime), typeid(player_default_param.ResuscitateDelayTime).name(), &player_default_param.ResuscitateDelayTime);
	player_default_param_max.NotDominantHandDamageRate = 100.f;
	player_default_param_min.NotDominantHandDamageRate = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(NotDominantHandDamageRate), typeid(player_default_param.NotDominantHandDamageRate).name(), &player_default_param.NotDominantHandDamageRate);
	player_default_param_max.NotDominantHandDamageRate_Throw = 100.f;
	player_default_param_min.NotDominantHandDamageRate_Throw = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(NotDominantHandDamageRate_Throw), typeid(player_default_param.NotDominantHandDamageRate_Throw).name(), &player_default_param.NotDominantHandDamageRate_Throw);



	player_default_param_max.KnockBackLevel1_Distance = 100.f;
	player_default_param_min.KnockBackLevel1_Distance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel1_Distance), typeid(player_default_param.KnockBackLevel1_Distance).name(), &player_default_param.KnockBackLevel1_Distance);
	player_default_param_max.KnockBackLevel1_Time = 100.f;
	player_default_param_min.KnockBackLevel1_Time = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel1_Time), typeid(player_default_param.KnockBackLevel1_Time).name(), &player_default_param.KnockBackLevel1_Time);
	player_default_param_max.KnockBackLevel1_WholeTime = 100.f;
	player_default_param_min.KnockBackLevel1_WholeTime = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel1_WholeTime), typeid(player_default_param.KnockBackLevel1_WholeTime).name(), &player_default_param.KnockBackLevel1_WholeTime);
	player_default_param_max.KnockBackLevel1_CameraBackDistance = 100.f;
	player_default_param_min.KnockBackLevel1_CameraBackDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel1_CameraBackDistance), typeid(player_default_param.KnockBackLevel1_CameraBackDistance).name(), &player_default_param.KnockBackLevel1_CameraBackDistance);
	player_default_param_max.KnockBackLevel1_CameraUpDistance = 100.f;
	player_default_param_min.KnockBackLevel1_CameraUpDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel1_CameraUpDistance), typeid(player_default_param.KnockBackLevel1_CameraUpDistance).name(), &player_default_param.KnockBackLevel1_CameraUpDistance);



	player_default_param_max.KnockBackLevel2_Distance = 100.f;
	player_default_param_min.KnockBackLevel2_Distance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel2_Distance), typeid(player_default_param.KnockBackLevel2_Distance).name(), &player_default_param.KnockBackLevel2_Distance);
	player_default_param_max.KnockBackLevel2_Time = 100.f;
	player_default_param_min.KnockBackLevel2_Time = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel2_Time), typeid(player_default_param.KnockBackLevel2_Time).name(), &player_default_param.KnockBackLevel2_Time);
	player_default_param_max.KnockBackLevel2_WholeTime = 100.f;
	player_default_param_min.KnockBackLevel2_WholeTime = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel2_WholeTime), typeid(player_default_param.KnockBackLevel2_WholeTime).name(), &player_default_param.KnockBackLevel2_WholeTime);
	player_default_param_max.KnockBackLevel2_CameraBackDistance = 100.f;
	player_default_param_min.KnockBackLevel2_CameraBackDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel2_CameraBackDistance), typeid(player_default_param.KnockBackLevel2_CameraBackDistance).name(), &player_default_param.KnockBackLevel2_CameraBackDistance);
	player_default_param_max.KnockBackLevel2_CameraUpDistance = 100.f;
	player_default_param_min.KnockBackLevel2_CameraUpDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel2_CameraUpDistance), typeid(player_default_param.KnockBackLevel2_CameraUpDistance).name(), &player_default_param.KnockBackLevel2_CameraUpDistance);



	player_default_param_max.KnockBackLevel3_Distance = 100.f;
	player_default_param_min.KnockBackLevel3_Distance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel3_Distance), typeid(player_default_param.KnockBackLevel3_Distance).name(), &player_default_param.KnockBackLevel3_Distance);
	player_default_param_max.KnockBackLevel3_Time = 100.f;
	player_default_param_min.KnockBackLevel3_Time = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel3_Time), typeid(player_default_param.KnockBackLevel3_Time).name(), &player_default_param.KnockBackLevel3_Time);
	player_default_param_max.KnockBackLevel3_WholeTime = 100.f;
	player_default_param_min.KnockBackLevel3_WholeTime = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel3_WholeTime), typeid(player_default_param.KnockBackLevel3_WholeTime).name(), &player_default_param.KnockBackLevel3_WholeTime);
	player_default_param_max.KnockBackLevel3_CameraBackDistance = 100.f;
	player_default_param_min.KnockBackLevel3_CameraBackDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel3_CameraBackDistance), typeid(player_default_param.KnockBackLevel3_CameraBackDistance).name(), &player_default_param.KnockBackLevel3_CameraBackDistance);
	player_default_param_max.KnockBackLevel3_CameraUpDistance = 100.f;
	player_default_param_min.KnockBackLevel3_CameraUpDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel3_CameraUpDistance), typeid(player_default_param.KnockBackLevel3_CameraUpDistance).name(), &player_default_param.KnockBackLevel3_CameraUpDistance);



	player_default_param_max.KnockBackLevel4_Distance = 100.f;
	player_default_param_min.KnockBackLevel4_Distance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel4_Distance), typeid(player_default_param.KnockBackLevel4_Distance).name(), &player_default_param.KnockBackLevel4_Distance);
	player_default_param_max.KnockBackLevel4_Time = 100.f;
	player_default_param_min.KnockBackLevel4_Time = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel4_Time), typeid(player_default_param.KnockBackLevel4_Time).name(), &player_default_param.KnockBackLevel4_Time);
	player_default_param_max.KnockBackLevel4_WholeTime = 100.f;
	player_default_param_min.KnockBackLevel4_WholeTime = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel4_WholeTime), typeid(player_default_param.KnockBackLevel4_WholeTime).name(), &player_default_param.KnockBackLevel4_WholeTime);
	player_default_param_max.KnockBackLevel4_CameraBackDistance = 100.f;
	player_default_param_min.KnockBackLevel4_CameraBackDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel4_CameraBackDistance), typeid(player_default_param.KnockBackLevel4_CameraBackDistance).name(), &player_default_param.KnockBackLevel4_CameraBackDistance);
	player_default_param_max.KnockBackLevel4_CameraUpDistance = 100.f;
	player_default_param_min.KnockBackLevel4_CameraUpDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel4_CameraUpDistance), typeid(player_default_param.KnockBackLevel4_CameraUpDistance).name(), &player_default_param.KnockBackLevel4_CameraUpDistance);



	player_default_param_max.KnockBackLevel5_Distance = 100.f;
	player_default_param_min.KnockBackLevel5_Distance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel5_Distance), typeid(player_default_param.KnockBackLevel5_Distance).name(), &player_default_param.KnockBackLevel5_Distance);
	player_default_param_max.KnockBackLevel5_Time = 100.f;
	player_default_param_min.KnockBackLevel5_Time = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel5_Time), typeid(player_default_param.KnockBackLevel5_Time).name(), &player_default_param.KnockBackLevel5_Time);
	player_default_param_max.KnockBackLevel5_WholeTime = 100.f;
	player_default_param_min.KnockBackLevel5_WholeTime = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel5_WholeTime), typeid(player_default_param.KnockBackLevel5_WholeTime).name(), &player_default_param.KnockBackLevel5_WholeTime);
	player_default_param_max.KnockBackLevel5_CameraBackDistance = 100.f;
	player_default_param_min.KnockBackLevel5_CameraBackDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel5_CameraBackDistance), typeid(player_default_param.KnockBackLevel5_CameraBackDistance).name(), &player_default_param.KnockBackLevel5_CameraBackDistance);
	player_default_param_max.KnockBackLevel5_CameraUpDistance = 100.f;
	player_default_param_min.KnockBackLevel5_CameraUpDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel5_CameraUpDistance), typeid(player_default_param.KnockBackLevel5_CameraUpDistance).name(), &player_default_param.KnockBackLevel5_CameraUpDistance);



	player_default_param_max.GuardCrash_Time = 100.f;
	player_default_param_min.GuardCrash_Time = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevel5_Time), typeid(player_default_param.GuardCrash_Time).name(), &player_default_param.GuardCrash_Time);
	player_default_param_max.GuardCrash_CameraBackDistance = 100.f;
	player_default_param_min.GuardCrash_CameraBackDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(GuardCrash_CameraBackDistance), typeid(player_default_param.GuardCrash_CameraBackDistance).name(), &player_default_param.GuardCrash_CameraBackDistance);
	player_default_param_max.GuardCrash_CameraUpDistance = 100.f;
	player_default_param_min.GuardCrash_CameraUpDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(GuardCrash_CameraUpDistance), typeid(player_default_param.GuardCrash_CameraUpDistance).name(), &player_default_param.GuardCrash_CameraUpDistance);



	player_default_param_max.VHSCoolDownTime = 100.f;
	player_default_param_min.VHSCoolDownTime = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(VHSCoolDownTime), typeid(player_default_param.VHSCoolDownTime).name(), &player_default_param.VHSCoolDownTime);

}

void UMODToolEditorUtilityWidgetCPP::InitPlayerMovementPrameParame() {
	//プレイヤームーブメントパラメーター
	StartAddress player_movement_parame_start;
	player_movement_parame_start.main_address = (int64)(&player_movement_prame.start);
	player_movement_parame_start.max_address = (int64)(&player_movement_max.start);
	player_movement_parame_start.min_address = (int64)(&player_movement_min.start);

	player_movement_max.ContinuedSpeedForward = 5000.f;
	player_movement_min.ContinuedSpeedForward = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(ContinuedSpeedForward), typeid(player_movement_prame.ContinuedSpeedForward).name(), &player_movement_prame.ContinuedSpeedForward);
	player_movement_max.ContinuedSpeedBackward = 5000.f;
	player_movement_min.ContinuedSpeedBackward = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(ContinuedSpeedBackward), typeid(player_movement_prame.ContinuedSpeedBackward).name(), &player_movement_prame.ContinuedSpeedBackward);
	player_movement_max.ContinuedSpeedHorizontal = 5000.f;
	player_movement_min.ContinuedSpeedHorizontal = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(ContinuedSpeedForward), typeid(player_movement_prame.ContinuedSpeedHorizontal).name(), &player_movement_prame.ContinuedSpeedHorizontal);



	player_movement_max.StepLengthForward = 5000.f;
	player_movement_min.StepLengthForward = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(StepLengthForward), typeid(player_movement_prame.StepLengthForward).name(), &player_movement_prame.StepLengthForward);
	player_movement_max.StepLengthBackward = 5000.f;
	player_movement_min.StepLengthBackward = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(StepLengthBackward), typeid(player_movement_prame.StepLengthBackward).name(), &player_movement_prame.StepLengthBackward);
	player_movement_max.StepLengthHorizontal = 5000.f;
	player_movement_min.StepLengthHorizontal = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(StepLengthHorizontal), typeid(player_movement_prame.StepLengthHorizontal).name(), &player_movement_prame.StepLengthHorizontal);
	player_movement_max.StepMoveTime = 5000.f;
	player_movement_min.StepMoveTime = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(StepMoveTime), typeid(player_movement_prame.StepMoveTime).name(), &player_movement_prame.StepMoveTime);
	player_movement_max.StepRigidTime = 5000.f;
	player_movement_min.StepRigidTime = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(StepRigidTime), typeid(player_movement_prame.StepRigidTime).name(), &player_movement_prame.StepRigidTime);



	player_movement_max.LockOnRotateSpeed = 5000.f;
	player_movement_min.LockOnRotateSpeed = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(LockOnRotateSpeed), typeid(player_movement_prame.LockOnRotateSpeed).name(), &player_movement_prame.LockOnRotateSpeed);
	player_movement_max.LockOnRotateLimit = 5000.f;
	player_movement_min.LockOnRotateLimit = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(LockOnRotateLimit), typeid(player_movement_prame.LockOnRotateLimit).name(), &player_movement_prame.LockOnRotateLimit);
	player_movement_max.LockOnHeadLimit = 5000.f;
	player_movement_min.LockOnHeadLimit = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(LockOnHeadLimit), typeid(player_movement_prame.LockOnHeadLimit).name(), &player_movement_prame.LockOnHeadLimit);
	player_movement_max.LockOnDistanceLimit = 5000.f;
	player_movement_min.LockOnDistanceLimit = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(LockOnDistanceLimit), typeid(player_movement_prame.LockOnDistanceLimit).name(), &player_movement_prame.LockOnDistanceLimit);



	player_movement_max.TurnAngle = 5000.f;
	player_movement_min.TurnAngle = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(TurnAngle), typeid(player_movement_prame.TurnAngle).name(), &player_movement_prame.TurnAngle);
	player_movement_max.TurnAngleAuto = 5000.f;
	player_movement_min.TurnAngleAuto = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(TurnAngleAuto), typeid(player_movement_prame.TurnAngleAuto).name(), &player_movement_prame.TurnAngleAuto);
	player_movement_max.TurnTime = 5000.f;
	player_movement_min.TurnTime = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(TurnTime), typeid(player_movement_prame.TurnTime).name(), &player_movement_prame.TurnTime);
	player_movement_max.TurnInterval = 5000.f;
	player_movement_min.TurnInterval = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(TurnInterval), typeid(player_movement_prame.TurnInterval).name(), &player_movement_prame.TurnInterval);
	player_movement_max.FreeRotationSpeed = 5000.f;
	player_movement_min.FreeRotationSpeed = 0.f;
	AddPrame(EPrameType::PlayerMovement, player_movement_parame_start,
		TO_STRING(FreeRotationSpeed), typeid(player_movement_prame.FreeRotationSpeed).name(), &player_movement_prame.FreeRotationSpeed);

}

void UMODToolEditorUtilityWidgetCPP::InitWeaponParam() {
	//ウェポンパラメーター
	StartAddress weapon_param_start;
	weapon_param_start.main_address = (int64)(&weapon_param.start);
	weapon_param_start.max_address = (int64)(&weapon_param_max.start);
	weapon_param_start.min_address = (int64)(&weapon_param_min.start);

	weapon_param_max.ID = 200;
	weapon_param_min.ID = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(ID), typeid(weapon_param.ID).name(), &weapon_param.ID);
	weapon_param_max.DamageAmount = 200;
	weapon_param_min.DamageAmount = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(DamageAmount), typeid(weapon_param.DamageAmount).name(), &weapon_param.DamageAmount);
	weapon_param_max.MinimumDamageRate = 200;
	weapon_param_min.MinimumDamageRate = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(MinimumDamageRate), typeid(weapon_param.MinimumDamageRate).name(), &weapon_param.MinimumDamageRate);
	weapon_param_max.KnockBackAmount = 200;
	weapon_param_min.KnockBackAmount = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(KnockBackAmount), typeid(weapon_param.KnockBackAmount).name(), &weapon_param.KnockBackAmount);
	weapon_param_max.DamageAmountCorrectionRateByWeakPoint = 200;
	weapon_param_min.DamageAmountCorrectionRateByWeakPoint = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(DamageAmountCorrectionRateByWeakPoint), typeid(weapon_param.DamageAmountCorrectionRateByWeakPoint).name(), &weapon_param.DamageAmountCorrectionRateByWeakPoint);
	weapon_param_max.MaxPowerChargeTime = 200;
	weapon_param_min.MaxPowerChargeTime = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(MaxPowerChargeTime), typeid(weapon_param.MaxPowerChargeTime).name(), &weapon_param.MaxPowerChargeTime);
	weapon_param_max.EnergyDamageAmount = 200;
	weapon_param_min.EnergyDamageAmount = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(EnergyDamageAmount), typeid(weapon_param.EnergyDamageAmount).name(), &weapon_param.MaxPowerChargeTime);
	weapon_param_max.EnergyDamageAmount_Parry = 200;
	weapon_param_min.EnergyDamageAmount_Parry = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(EnergyDamageAmount_Parry), typeid(weapon_param.EnergyDamageAmount_Parry).name(), &weapon_param.EnergyDamageAmount_Parry);
	weapon_param_max.Durability = 200;
	weapon_param_min.Durability = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(Durability), typeid(weapon_param.Durability).name(), &weapon_param.Durability);
	weapon_param_max.DurabilityDamageRate_Parry = 200;
	weapon_param_min.DurabilityDamageRate_Parry = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(DurabilityDamageRate_Parry), typeid(weapon_param.DurabilityDamageRate_Parry).name(), &weapon_param.DurabilityDamageRate_Parry);
	weapon_param_max.DurabilityDamageRate_Guard = 200;
	weapon_param_min.DurabilityDamageRate_Guard = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(DurabilityDamageRate_Guard), typeid(weapon_param.DurabilityDamageRate_Guard).name(), &weapon_param.DurabilityDamageRate_Guard);
	weapon_param_max.ParryThreshold = 200;
	weapon_param_min.ParryThreshold = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(ParryThreshold), typeid(weapon_param.ParryThreshold).name(), &weapon_param.ParryThreshold);
	weapon_param_max.WalkSpeed = 200;
	weapon_param_min.WalkSpeed = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(WalkSpeed), typeid(weapon_param.WalkSpeed).name(), &weapon_param.WalkSpeed);
	weapon_param_max.CrackDamageRate = 200;
	weapon_param_min.CrackDamageRate = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(CrackDamageRate), typeid(weapon_param.CrackDamageRate).name(), &weapon_param.CrackDamageRate);
	weapon_param_max.WearingRecoveryDurabilityAmount = 200;
	weapon_param_min.WearingRecoveryDurabilityAmount = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(WearingRecoveryDurabilityAmount), typeid(weapon_param.WearingRecoveryDurabilityAmount).name(), &weapon_param.WearingRecoveryDurabilityAmount);
	//weapon_param_max.TwoHandCorrections = 200;
	//weapon_param_min.TwoHandCorrections = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(TwoHandCorrections), typeid(weapon_param.TwoHandCorrections).name(), &weapon_param.TwoHandCorrections);
	//weapon_param_max.SpecialGage = 200;
	//weapon_param_min.SpecialGage = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(SpecialGage), typeid(weapon_param.SpecialGage).name(), &weapon_param.SpecialGage);
	weapon_param_max.DamageAmountCorrectionRateByThrown = 200;
	weapon_param_min.DamageAmountCorrectionRateByThrown = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(DamageAmountCorrectionRateByThrown), typeid(weapon_param.DamageAmountCorrectionRateByThrown).name(), &weapon_param.DamageAmountCorrectionRateByThrown);
	weapon_param_max.KnockBackAmountCorrectionRateByThrown = 200;
	weapon_param_min.KnockBackAmountCorrectionRateByThrown = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(KnockBackAmountCorrectionRateByThrown), typeid(weapon_param.KnockBackAmountCorrectionRateByThrown).name(), &weapon_param.KnockBackAmountCorrectionRateByThrown);
	weapon_param_max.ConsumeDurabilityCorrectionRateByThrown = 200;
	weapon_param_min.ConsumeDurabilityCorrectionRateByThrown = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(ConsumeDurabilityCorrectionRateByThrown), typeid(weapon_param.ConsumeDurabilityCorrectionRateByThrown).name(), &weapon_param.ConsumeDurabilityCorrectionRateByThrown);
}


void UMODToolEditorUtilityWidgetCPP::SetPrames() {
	prames.Add(EPrameType::PlayerDefault, player_default_param.search);
	prames.Add(EPrameType::PlayerMovement, player_movement_prame.search);
	prames.Add(EPrameType::Weapons, weapon_param.search);
	prames.Add(EPrameType::Map, map_param.search);

	max_prames.Add(EPrameType::PlayerDefault, player_default_param_max.search);
	max_prames.Add(EPrameType::PlayerMovement, player_movement_max.search);
	max_prames.Add(EPrameType::Weapons, weapon_param_max.search);
	max_prames.Add(EPrameType::Map, map_param_max.search);

	min_prames.Add(EPrameType::PlayerDefault, player_default_param_min.search);
	min_prames.Add(EPrameType::PlayerMovement, player_movement_min.search);
	min_prames.Add(EPrameType::Weapons, weapon_param_min.search);
	min_prames.Add(EPrameType::Map, map_param_min.search);

}

bool UMODToolEditorUtilityWidgetCPP::AddValidityParames(EPrameType type) {
	
	if (validity_parames.Find(type) == INDEX_NONE) {
		validity_parames.Add(type);
		return true;
	}
	return false;
}


void UMODToolEditorUtilityWidgetCPP::CreateLocalMod(FString mod_name) {

	for (int i = 0; i < validity_parames.Num(); i++) {
		if (validity_parames[i] == EPrameType::PlayerDefault) {
			TSharedPtr <FJsonObject> JsonObject = MakeShareable(new FJsonObject);

			{
				//TSharedPtr<FJsonValueNumber> value1_1 = MakeShareable(new FJsonValueNumber(player_default_param.Health));
				//JsonObject->SetField(TEXT("Health"), value1_1);
				TSharedPtr<FJsonValueNumber> value1_2 = MakeShareable(new FJsonValueNumber(player_default_param.AttackDamage));
				JsonObject->SetField(TEXT("AttackDamage"), value1_2);
				TSharedPtr<FJsonValueNumber> value1_3 = MakeShareable(new FJsonValueNumber(player_default_param.DrainHealthValuePerSeconds));
				JsonObject->SetField(TEXT("DrainHealthValuePerSeconds"), value1_3);

			}

			{
				TSharedPtr <FJsonObject> JsonArrayObject = MakeShareable(new FJsonObject);

				TSharedPtr<FJsonValueNumber> value2_1 = MakeShareable(new FJsonValueNumber(player_default_param.energy.MaxValue));
				JsonArrayObject->SetField(TEXT("MaxValue"), value2_1);
				TSharedPtr<FJsonValueNumber> value2_2 = MakeShareable(new FJsonValueNumber(player_default_param.energy.DelaySecondsForIncrementValue));
				JsonArrayObject->SetField(TEXT("DelaySecondsForIncrementValue"), value2_2);
				TSharedPtr<FJsonValueNumber> value2_3 = MakeShareable(new FJsonValueNumber(player_default_param.energy.IncrementValuePerSecond));
				JsonArrayObject->SetField(TEXT("IncrementValuePerSecond"), value2_3);

				JsonObject->SetObjectField("Energy", JsonArrayObject);
			}

			{
				TSharedPtr <FJsonObject> JsonArrayObject = MakeShareable(new FJsonObject);

				TSharedPtr<FJsonValueNumber> value3_1 = MakeShareable(new FJsonValueNumber(player_default_param.SpecialGage_MaxValue));
				JsonArrayObject->SetField(TEXT("MaxValue"), value3_1);
				TSharedPtr<FJsonValueNumber> value3_2 = MakeShareable(new FJsonValueNumber(player_default_param.SpecialGage_DecreaseSpeed));
				JsonArrayObject->SetField(TEXT("DecreaseSpeed"), value3_2);
				{
					TSharedPtr <FJsonObject> JsonArrayObject2 = MakeShareable(new FJsonObject);
					TSharedPtr<FJsonValueNumber> value3_3 = MakeShareable(new FJsonValueNumber(player_default_param.SpecialGage_IncreaseValues_TakeDamage));
					JsonArrayObject2->SetField(TEXT("TakeDamage"), value3_3);
					TSharedPtr<FJsonValueNumber> value3_4 = MakeShareable(new FJsonValueNumber(player_default_param.SpecialGage_IncreaseValues_DodgeByVHS));
					JsonArrayObject2->SetField(TEXT("DodgeByVHS"), value3_4);

					JsonArrayObject->SetObjectField("IncreaseValues", JsonArrayObject2);
				}

				JsonObject->SetObjectField("SpecialGage", JsonArrayObject);

			}

			{
				TSharedPtr<FJsonValueNumber> value4_1 = MakeShareable(new FJsonValueNumber(player_default_param.ResuscitateDelayTime));
				JsonObject->SetField(TEXT("ResuscitateDelayTime"), value4_1);
				TSharedPtr<FJsonValueNumber> value4_2 = MakeShareable(new FJsonValueNumber(player_default_param.NotDominantHandDamageRate));
				JsonObject->SetField(TEXT("NotDominantHandDamageRate"), value4_2);
				TSharedPtr<FJsonValueNumber> value4_3 = MakeShareable(new FJsonValueNumber(player_default_param.NotDominantHandDamageRate_Throw));
				JsonObject->SetField(TEXT("NotDominantHandDamageRate_Throw"), value4_3);

			}

			{
				TArray<TSharedPtr<FJsonValue>> JsonArrayObject;
				{
					TSharedPtr <FJsonObject> JsonObject2 = MakeShareable(new FJsonObject);

					TSharedPtr<FJsonValueNumber> value3_1 = MakeShareable(new FJsonValueNumber(1));
					JsonObject2->SetField(TEXT("Level"), value3_1);
					TSharedPtr<FJsonValueNumber> value3_2 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel1_Distance));
					JsonObject2->SetField(TEXT("Distance"), value3_2);
					TSharedPtr<FJsonValueNumber> value3_3 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel1_Time));
					JsonObject2->SetField(TEXT("Time"), value3_3);
					TSharedPtr<FJsonValueNumber> value3_4 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel1_WholeTime));
					JsonObject2->SetField(TEXT("WholeTime"), value3_4);
					TSharedPtr<FJsonValueNumber> value3_5 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel1_CameraBackDistance));
					JsonObject2->SetField(TEXT("CameraBackDistance"), value3_5);
					TSharedPtr<FJsonValueNumber> value3_6 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel1_CameraUpDistance));
					JsonObject2->SetField(TEXT("CameraUpDistance"), value3_6);

					TSharedPtr<FJsonValueObject> obj = MakeShareable(new FJsonValueObject(JsonObject2));
					JsonArrayObject.Add(obj);
				}

				{
					TSharedPtr <FJsonObject> JsonObject2 = MakeShareable(new FJsonObject);

					TSharedPtr<FJsonValueNumber> value3_1 = MakeShareable(new FJsonValueNumber(2));
					JsonObject2->SetField(TEXT("Level"), value3_1);
					TSharedPtr<FJsonValueNumber> value3_2 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel2_Distance));
					JsonObject2->SetField(TEXT("Distance"), value3_2);
					TSharedPtr<FJsonValueNumber> value3_3 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel2_Time));
					JsonObject2->SetField(TEXT("Time"), value3_3);
					TSharedPtr<FJsonValueNumber> value3_4 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel2_WholeTime));
					JsonObject2->SetField(TEXT("WholeTime"), value3_4);
					TSharedPtr<FJsonValueNumber> value3_5 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel2_CameraBackDistance));
					JsonObject2->SetField(TEXT("CameraBackDistance"), value3_5);
					TSharedPtr<FJsonValueNumber> value3_6 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel2_CameraUpDistance));
					JsonObject2->SetField(TEXT("CameraUpDistance"), value3_6);

					TSharedPtr<FJsonValueObject> obj = MakeShareable(new FJsonValueObject(JsonObject2));
					JsonArrayObject.Add(obj);
				}

				{
					TSharedPtr <FJsonObject> JsonObject2 = MakeShareable(new FJsonObject);

					TSharedPtr<FJsonValueNumber> value3_1 = MakeShareable(new FJsonValueNumber(3));
					JsonObject2->SetField(TEXT("Level"), value3_1);
					TSharedPtr<FJsonValueNumber> value3_2 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel3_Distance));
					JsonObject2->SetField(TEXT("Distance"), value3_2);
					TSharedPtr<FJsonValueNumber> value3_3 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel3_Time));
					JsonObject2->SetField(TEXT("Time"), value3_3);
					TSharedPtr<FJsonValueNumber> value3_4 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel3_WholeTime));
					JsonObject2->SetField(TEXT("WholeTime"), value3_4);
					TSharedPtr<FJsonValueNumber> value3_5 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel3_CameraBackDistance));
					JsonObject2->SetField(TEXT("CameraBackDistance"), value3_5);
					TSharedPtr<FJsonValueNumber> value3_6 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel3_CameraUpDistance));
					JsonObject2->SetField(TEXT("CameraUpDistance"), value3_6);

					TSharedPtr<FJsonValueObject> obj = MakeShareable(new FJsonValueObject(JsonObject2));
					JsonArrayObject.Add(obj);
				}

				{
					TSharedPtr <FJsonObject> JsonObject2 = MakeShareable(new FJsonObject);

					TSharedPtr<FJsonValueNumber> value3_1 = MakeShareable(new FJsonValueNumber(4));
					JsonObject2->SetField(TEXT("Level"), value3_1);
					TSharedPtr<FJsonValueNumber> value3_2 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel4_Distance));
					JsonObject2->SetField(TEXT("Distance"), value3_2);
					TSharedPtr<FJsonValueNumber> value3_3 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel4_Time));
					JsonObject2->SetField(TEXT("Time"), value3_3);
					TSharedPtr<FJsonValueNumber> value3_4 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel4_WholeTime));
					JsonObject2->SetField(TEXT("WholeTime"), value3_4);
					TSharedPtr<FJsonValueNumber> value3_5 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel4_CameraBackDistance));
					JsonObject2->SetField(TEXT("CameraBackDistance"), value3_5);
					TSharedPtr<FJsonValueNumber> value3_6 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel4_CameraUpDistance));
					JsonObject2->SetField(TEXT("CameraUpDistance"), value3_6);

					TSharedPtr<FJsonValueObject> obj = MakeShareable(new FJsonValueObject(JsonObject2));
					JsonArrayObject.Add(obj);
				}

				{
					TSharedPtr <FJsonObject> JsonObject2 = MakeShareable(new FJsonObject);

					TSharedPtr<FJsonValueNumber> value3_1 = MakeShareable(new FJsonValueNumber(5));
					JsonObject2->SetField(TEXT("Level"), value3_1);
					TSharedPtr<FJsonValueNumber> value3_2 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel5_Distance));
					JsonObject2->SetField(TEXT("Distance"), value3_2);
					TSharedPtr<FJsonValueNumber> value3_3 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel5_Time));
					JsonObject2->SetField(TEXT("Time"), value3_3);
					TSharedPtr<FJsonValueNumber> value3_4 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel5_WholeTime));
					JsonObject2->SetField(TEXT("WholeTime"), value3_4);
					TSharedPtr<FJsonValueNumber> value3_5 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel5_CameraBackDistance));
					JsonObject2->SetField(TEXT("CameraBackDistance"), value3_5);
					TSharedPtr<FJsonValueNumber> value3_6 = MakeShareable(new FJsonValueNumber(player_default_param.KnockBackLevel5_CameraUpDistance));
					JsonObject2->SetField(TEXT("CameraUpDistance"), value3_6);

					TSharedPtr<FJsonValueObject> obj = MakeShareable(new FJsonValueObject(JsonObject2));
					JsonArrayObject.Add(obj);
				}

				JsonObject->SetArrayField("KnockBackLevels", JsonArrayObject);
			}

			{
				TSharedPtr <FJsonObject> JsonArrayObject = MakeShareable(new FJsonObject);

				TSharedPtr<FJsonValueNumber> value4_1 = MakeShareable(new FJsonValueNumber(player_default_param.GuardCrash_Time));
				JsonArrayObject->SetField(TEXT("Time"), value4_1);
				TSharedPtr<FJsonValueNumber> value4_2 = MakeShareable(new FJsonValueNumber(player_default_param.GuardCrash_CameraBackDistance));
				JsonArrayObject->SetField(TEXT("CameraBackDistance"), value4_2);
				TSharedPtr<FJsonValueNumber> value4_3 = MakeShareable(new FJsonValueNumber(player_default_param.GuardCrash_CameraUpDistance));
				JsonArrayObject->SetField(TEXT("CameraUpDistance"), value4_3);

				JsonObject->SetObjectField("GuardCrash", JsonArrayObject);
			}

			TSharedPtr<FJsonValueNumber> value5_1 = MakeShareable(new FJsonValueNumber(player_default_param.VHSCoolDownTime));
			JsonObject->SetField(TEXT("VHSCoolDownTime"), value5_1);

			FString OutputString;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

			UMODToolBlueprintFunctionLibrary::FileCreate(mod_name + ("/Character/playerdefault"), OutputString);
		}
		else if (validity_parames[i] == EPrameType::PlayerMovement) {
			TSharedPtr <FJsonObject> JsonObject = MakeShareable(new FJsonObject);

			{
				TSharedPtr<FJsonValueNumber> value1_1 = MakeShareable(new FJsonValueNumber(player_movement_prame.ContinuedSpeedForward));
				JsonObject->SetField(TEXT("ContinuedSpeedForward"), value1_1);

				TSharedPtr<FJsonValueNumber> value1_2 = MakeShareable(new FJsonValueNumber(player_movement_prame.ContinuedSpeedBackward));
				JsonObject->SetField(TEXT("ContinuedSpeedBackward"), value1_2);

				TSharedPtr<FJsonValueNumber> value1_3 = MakeShareable(new FJsonValueNumber(player_movement_prame.ContinuedSpeedHorizontal));
				JsonObject->SetField(TEXT("ContinuedSpeedHorizontal"), value1_3);
			}

			{
				TSharedPtr<FJsonValueNumber> value2_1 = MakeShareable(new FJsonValueNumber(player_movement_prame.StepLengthForward));
				JsonObject->SetField(TEXT("StepLengthForward"), value2_1);

				TSharedPtr<FJsonValueNumber> value2_2 = MakeShareable(new FJsonValueNumber(player_movement_prame.StepLengthBackward));
				JsonObject->SetField(TEXT("StepLengthBackward"), value2_2);

				TSharedPtr<FJsonValueNumber> value2_3 = MakeShareable(new FJsonValueNumber(player_movement_prame.StepLengthHorizontal));
				JsonObject->SetField(TEXT("StepLengthHorizontal"), value2_3);

				TSharedPtr<FJsonValueNumber> value2_4 = MakeShareable(new FJsonValueNumber(player_movement_prame.StepMoveTime));
				JsonObject->SetField(TEXT("StepMoveTime"), value2_4);

				TSharedPtr<FJsonValueNumber> value2_5 = MakeShareable(new FJsonValueNumber(player_movement_prame.StepRigidTime));
				JsonObject->SetField(TEXT("StepRigidTime"), value2_5);
			}

			{
				TSharedPtr<FJsonValueNumber> value3_1 = MakeShareable(new FJsonValueNumber(player_movement_prame.LockOnRotateSpeed));
				JsonObject->SetField(TEXT("LockOnRotateSpeed"), value3_1);

				TSharedPtr<FJsonValueNumber> value3_2 = MakeShareable(new FJsonValueNumber(player_movement_prame.LockOnRotateLimit));
				JsonObject->SetField(TEXT("LockOnRotateLimit"), value3_2);

				TSharedPtr<FJsonValueNumber> value3_3 = MakeShareable(new FJsonValueNumber(player_movement_prame.LockOnHeadLimit));
				JsonObject->SetField(TEXT("LockOnHeadLimit"), value3_3);

				TSharedPtr<FJsonValueNumber> value3_4 = MakeShareable(new FJsonValueNumber(player_movement_prame.LockOnDistanceLimit));
				JsonObject->SetField(TEXT("LockOnDistanceLimit"), value3_4);
			}

			{
				TSharedPtr<FJsonValueNumber> value4_1 = MakeShareable(new FJsonValueNumber(player_movement_prame.TurnAngle));
				JsonObject->SetField(TEXT("TurnAngle"), value4_1);

				TSharedPtr<FJsonValueNumber> value4_2 = MakeShareable(new FJsonValueNumber(player_movement_prame.TurnAngleAuto));
				JsonObject->SetField(TEXT("TurnAngleAuto"), value4_2);

				TSharedPtr<FJsonValueNumber> value4_3 = MakeShareable(new FJsonValueNumber(player_movement_prame.TurnTime));
				JsonObject->SetField(TEXT("TurnTime"), value4_3);

				TSharedPtr<FJsonValueNumber> value4_4 = MakeShareable(new FJsonValueNumber(player_movement_prame.TurnInterval));
				JsonObject->SetField(TEXT("TurnInterval"), value4_4);
			}

			{
				TSharedPtr<FJsonValueNumber> value5 = MakeShareable(new FJsonValueNumber(player_movement_prame.FreeRotationSpeed));
				JsonObject->SetField(TEXT("FreeRotationSpeed"), value5);
			}
			FString OutputString;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

			UMODToolBlueprintFunctionLibrary::FileCreate(mod_name + ("/Character/player_movement"), OutputString);
		}
	}

	TSharedPtr <FJsonObject> JsonObject1 = MakeShareable(new FJsonObject);

	TSharedPtr<FJsonValueNumber> value1 = MakeShareable(new FJsonValueNumber(player_movement_prame.FreeRotationSpeed));
	JsonObject1->SetField(TEXT("PlayerStartTagPrefix"), value1);
	TSharedPtr<FJsonValueNumber> value2 = MakeShareable(new FJsonValueNumber(player_movement_prame.FreeRotationSpeed));
	JsonObject1->SetField(TEXT("RoomId"), value2);
	TSharedPtr<FJsonValueNumber> value3 = MakeShareable(new FJsonValueNumber(player_movement_prame.FreeRotationSpeed));
	JsonObject1->SetField(TEXT("Wave"), value3);

	TSharedPtr<FJsonValueObject> a = MakeShareable(new FJsonValueObject(JsonObject1));

	TArray<TSharedPtr<FJsonValue>> JsonArrayObject1;
	JsonArrayObject1.Add(a);
	TArray<TSharedPtr<FJsonValue>> JsonArrayObject2;
	TSharedPtr<FJsonValueArray> b = MakeShareable(new FJsonValueArray(JsonArrayObject1));
	JsonArrayObject2.Add(b);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonArrayObject2, Writer);

	UMODToolBlueprintFunctionLibrary::FileCreate(mod_name + ("/Character/test"), OutputString);
}


void UMODToolEditorUtilityWidgetCPP::AddPrame(EPrameType type, StartAddress s_a, const char* name, const char* var_type, void* aa) {
	prames[type].AddVar(name, var_type, aa);
	int64 byte_count = (int64)(aa) - s_a.main_address;

	int64 max_address = s_a.max_address + byte_count;
	int64 min_address = s_a.min_address + byte_count;

	max_prames[type].AddVar(name, var_type, (void*)max_address);
	min_prames[type].AddVar(name, var_type, (void*)min_address);

}

void UMODToolEditorUtilityWidgetCPP::AddEnemyPrame(const char* name, const char* type, void* aa) {
	VarPra inst;
	inst.name = name;
	inst.type = type;

	int64 byte_count = (int64)(aa)-(int64)(&enemy_param_measurement.start);
	inst.byte_count = byte_count;

	map_wave_param_addres.Add(inst);

	int64 max_address = (int64)(&enemy_param_max.start) + byte_count;
	int64 min_address = (int64)(&enemy_param_min.start) + byte_count;

	enemy_param_max.search.AddVar(name, type, (void*)max_address);
	enemy_param_min.search.AddVar(name, type, (void*)min_address);
}

void UMODToolEditorUtilityWidgetCPP::AddWave() {
	map_quest_param[GetQuestIndex()].wave.Add(FMapWaveParam());
	int32 index_num = map_quest_param[GetQuestIndex()].wave.Num() - 1;
	map_quest_param[GetQuestIndex()].wave[index_num].enemy.Init(FEnemyParam(),6);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < map_wave_param_addres.Num(); j++) {
			int64 address = (int64)(&map_quest_param[GetQuestIndex()].wave[index_num].enemy[i].start) + map_wave_param_addres[j].byte_count;
			map_quest_param[GetQuestIndex()].wave[index_num].enemy[i].search.AddVar(
				TCHAR_TO_ANSI(*map_wave_param_addres[j].name),
				TCHAR_TO_ANSI(*map_wave_param_addres[j].type),
				(void*)address
				);
		}
	}

}

void UMODToolEditorUtilityWidgetCPP::AddQuest() {
	map_quest_param.Add(FMapQuestParam());
	quest_num++;
}

void UMODToolEditorUtilityWidgetCPP::InsertWave(int32 index) {
	int32 set_index = map_quest_param[GetQuestIndex()].wave.Insert(FMapWaveParam(), index - 1);
	map_quest_param[GetQuestIndex()].wave[set_index].enemy.Init(FEnemyParam(), 6);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < map_wave_param_addres.Num(); j++) {
			int64 address = (int64)(&map_quest_param[GetQuestIndex()].wave[set_index].enemy[i].start) + map_wave_param_addres[j].byte_count;
			map_quest_param[GetQuestIndex()].wave[set_index].enemy[i].search.AddVar(
				TCHAR_TO_ANSI(*map_wave_param_addres[j].name),
				TCHAR_TO_ANSI(*map_wave_param_addres[j].type),
				(void*)address
			);
		}
	}
}

void UMODToolEditorUtilityWidgetCPP::RemoveWave(int32 index) {
	if (index < 1 || index > map_quest_param[GetQuestIndex()].wave.Num() + 1) {
		return;
	}
	map_quest_param[GetQuestIndex()].wave.RemoveAt(index - 1);
}