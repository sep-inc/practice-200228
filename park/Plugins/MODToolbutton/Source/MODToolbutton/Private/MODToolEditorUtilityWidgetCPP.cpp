// Fill out your copyright notice in the Description page of Project Settings.
#include "MODToolEditorUtilityWidgetCPP.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "IPlatformFilePak.h"
#include "Dom/JsonObject.h"
#include "MODToolBlueprintFunctionLibrary.h"

typedef UMODToolBlueprintFunctionLibrary FuncLib;


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

	player_default_param_max.Health = 100;
	player_default_param_min.Health = 0;
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



	player_default_param_max.Energy.MaxValue = 100.f;
	player_default_param_min.Energy.MaxValue = 0.f;
	player_default_param_max.Energy.DelaySecondsForIncrementValue = 100.f;
	player_default_param_min.Energy.DelaySecondsForIncrementValue = 0.f;
	player_default_param_max.Energy.IncrementValuePerSecond = 100;
	player_default_param_min.Energy.IncrementValuePerSecond = 0;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(Energy), typeid(player_default_param.Energy).name(), &player_default_param.Energy);
	
	player_default_param_max.SpecialGage.MaxValue = 100;
	player_default_param_min.SpecialGage.MaxValue = 0;
	player_default_param_max.SpecialGage.DecreaseSpeed = 100;
	player_default_param_min.SpecialGage.DecreaseSpeed = 0;
	player_default_param_max.SpecialGage.IncreaseValues.TakeDamage = 100;
	player_default_param_min.SpecialGage.IncreaseValues.TakeDamage = 0;
	player_default_param_max.SpecialGage.IncreaseValues.DodgeByVHS = 100;
	player_default_param_min.SpecialGage.IncreaseValues.DodgeByVHS = 0;

	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(SpecialGage), typeid(player_default_param.SpecialGage).name(), &player_default_param.SpecialGage);



	/*player_default_param_max.SpecialGage_MaxValue = 100.f;
	player_default_param_min.SpecialGage_MaxValue = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(SpecialGage_MaxValue), typeid(player_default_param.SpecialGage_MaxValue).name(), &player_default_param.SpecialGage_MaxValue);
	player_default_param_max.SpecialGage_DecreaseSpeed = 100.f;
	player_default_param_min.SpecialGage_DecreaseSpeed = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(SpecialGage_DecreaseSpeed), typeid(player_default_param.SpecialGage_DecreaseSpeed).name(), &player_default_param.SpecialGage_DecreaseSpeed);
	player_default_param_max.IncreaseValues.TakeDamage = 100.f;
	player_default_param_min.SpecialGage_IncreaseValues_TakeDamage = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(SpecialGage_IncreaseValues_TakeDamage), typeid(player_default_param.SpecialGage_IncreaseValues_TakeDamage).name(), &player_default_param.SpecialGage_IncreaseValues_TakeDamage);
	player_default_param_max.SpecialGage_IncreaseValues_DodgeByVHS = 100.f;
	player_default_param_min.SpecialGage_IncreaseValues_DodgeByVHS = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(SpecialGage_IncreaseValues_DodgeByVHS), typeid(player_default_param.SpecialGage_IncreaseValues_DodgeByVHS).name(), &player_default_param.SpecialGage_IncreaseValues_DodgeByVHS);*/



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

	player_default_param_max.KnockBackLevels.Add(FKnockBackLevels());
	player_default_param_min.KnockBackLevels.Add(FKnockBackLevels());

	player_default_param_max.KnockBackLevels[0].Level = 100.f;
	player_default_param_min.KnockBackLevels[0].Level = 0.f;
	player_default_param_max.KnockBackLevels[0].Distance = 100.f;
	player_default_param_min.KnockBackLevels[0].Distance = 0.f;
	player_default_param_max.KnockBackLevels[0].Time = 100.f;
	player_default_param_min.KnockBackLevels[0].Time = 0.f;
	player_default_param_max.KnockBackLevels[0].WholeTime = 100.f;
	player_default_param_min.KnockBackLevels[0].WholeTime = 0.f;
	player_default_param_max.KnockBackLevels[0].CameraBackDistance = 100.f;
	player_default_param_min.KnockBackLevels[0].CameraBackDistance = 0.f;
	player_default_param_max.KnockBackLevels[0].CameraUpDistance = 100.f;
	player_default_param_min.KnockBackLevels[0].CameraUpDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(KnockBackLevels), typeid(player_default_param.KnockBackLevels).name(), &player_default_param.KnockBackLevels);

	player_default_param_max.GuardCrash.Time = 100.f;
	player_default_param_min.GuardCrash.Time = 0.f;
	player_default_param_max.GuardCrash.CameraBackDistance = 100.f;
	player_default_param_min.GuardCrash.CameraBackDistance = 0.f;
	player_default_param_max.GuardCrash.CameraUpDistance = 100.f;
	player_default_param_min.GuardCrash.CameraUpDistance = 0.f;
	AddPrame(EPrameType::PlayerDefault, player_parame_start,
		TO_STRING(GuardCrash), typeid(player_default_param.GuardCrash).name(), &player_default_param.GuardCrash);

	/*player_default_param_max.GuardCrash_Time = 100.f;
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
*/


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
	weapon_param_max.TwoHandCorrections.DamageAmount = 200.f;
	weapon_param_min.TwoHandCorrections.DamageAmount = 0.f;
	weapon_param_max.TwoHandCorrections.KnockBackAmount = 200.f;
	weapon_param_min.TwoHandCorrections.KnockBackAmount = 0.f;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(TwoHandCorrections), typeid(weapon_param.TwoHandCorrections).name(), &weapon_param.TwoHandCorrections);
	weapon_param_max.SpecialGage.IncreaseValues.Hit = 200;
	weapon_param_min.SpecialGage.IncreaseValues.Hit = 0;
	weapon_param_max.SpecialGage.IncreaseValues.Guard = 200;
	weapon_param_min.SpecialGage.IncreaseValues.Guard = 0;
	weapon_param_max.SpecialGage.IncreaseValues.Parry = 200;
	weapon_param_min.SpecialGage.IncreaseValues.Parry = 0;
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

			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("Health"), player_default_param.Health);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("AttackDamage"), player_default_param.AttackDamage);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("DrainHealthValuePerSeconds"), player_default_param.DrainHealthValuePerSeconds);
			{
				TSharedPtr <FJsonObject> JsonArrayObject = MakeShareable(new FJsonObject);

				FuncLib::SetJsonFieldVal_Num(JsonArrayObject, TEXT("MaxValue"), player_default_param.Energy.MaxValue);
				FuncLib::SetJsonFieldVal_Num(JsonArrayObject, TEXT("DelaySecondsForIncrementValue"), player_default_param.Energy.DelaySecondsForIncrementValue);
				FuncLib::SetJsonFieldVal_Num(JsonArrayObject, TEXT("IncrementValuePerSecond"), player_default_param.Energy.IncrementValuePerSecond);

				JsonObject->SetObjectField("Energy", JsonArrayObject);
			}

			{
				TSharedPtr <FJsonObject> JsonArrayObject = MakeShareable(new FJsonObject);

				FuncLib::SetJsonFieldVal_Num(JsonArrayObject, TEXT("MaxValue"), player_default_param.SpecialGage.MaxValue);
				FuncLib::SetJsonFieldVal_Num(JsonArrayObject, TEXT("DecreaseSpeed"), player_default_param.SpecialGage.DecreaseSpeed);

				{
					TSharedPtr <FJsonObject> JsonArrayObject2 = MakeShareable(new FJsonObject);

					FuncLib::SetJsonFieldVal_Num(JsonArrayObject2, TEXT("TakeDamage"), player_default_param.SpecialGage.IncreaseValues.TakeDamage);
					FuncLib::SetJsonFieldVal_Num(JsonArrayObject2, TEXT("DodgeByVHS"), player_default_param.SpecialGage.IncreaseValues.DodgeByVHS);

					JsonArrayObject->SetObjectField("IncreaseValues", JsonArrayObject2);
				}

				JsonObject->SetObjectField("SpecialGage", JsonArrayObject);
			}

			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("ResuscitateDelayTime"), player_default_param.ResuscitateDelayTime);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("NotDominantHandDamageRate"), player_default_param.NotDominantHandDamageRate);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("NotDominantHandDamageRate_Throw"), player_default_param.NotDominantHandDamageRate_Throw);

			{
				TArray<TSharedPtr<FJsonValue>> JsonArrayObject;
				for (int KnockBackLevels_index = 0; KnockBackLevels_index < player_default_param.KnockBackLevels.Num(); KnockBackLevels_index++) {
					TSharedPtr <FJsonObject> JsonObject2 = MakeShareable(new FJsonObject);

					FuncLib::SetJsonFieldVal_Num(JsonObject2, TEXT("Level"), player_default_param.KnockBackLevels[KnockBackLevels_index].Level);
					FuncLib::SetJsonFieldVal_Num(JsonObject2, TEXT("Distance"), player_default_param.KnockBackLevels[KnockBackLevels_index].Distance);
					FuncLib::SetJsonFieldVal_Num(JsonObject2, TEXT("Time"), player_default_param.KnockBackLevels[KnockBackLevels_index].Time);
					FuncLib::SetJsonFieldVal_Num(JsonObject2, TEXT("WholeTime"), player_default_param.KnockBackLevels[KnockBackLevels_index].WholeTime);
					FuncLib::SetJsonFieldVal_Num(JsonObject2, TEXT("CameraBackDistance"), player_default_param.KnockBackLevels[KnockBackLevels_index].CameraBackDistance);
					FuncLib::SetJsonFieldVal_Num(JsonObject2, TEXT("CameraUpDistance"), player_default_param.KnockBackLevels[KnockBackLevels_index].CameraUpDistance);

					TSharedPtr<FJsonValueObject> obj = MakeShareable(new FJsonValueObject(JsonObject2));
					JsonArrayObject.Add(obj);
				}
				JsonObject->SetArrayField("KnockBackLevels", JsonArrayObject);
			}

			{
				TSharedPtr <FJsonObject> JsonArrayObject = MakeShareable(new FJsonObject);

				FuncLib::SetJsonFieldVal_Num(JsonArrayObject, TEXT("Time"), player_default_param.GuardCrash.Time);
				FuncLib::SetJsonFieldVal_Num(JsonArrayObject, TEXT("CameraBackDistance"), player_default_param.GuardCrash.CameraBackDistance);
				FuncLib::SetJsonFieldVal_Num(JsonArrayObject, TEXT("CameraUpDistance"), player_default_param.GuardCrash.CameraUpDistance);

				JsonObject->SetObjectField("GuardCrash", JsonArrayObject);
			}

			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("VHSCoolDownTime"), player_default_param.VHSCoolDownTime);

			FString OutputString;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

			UMODToolBlueprintFunctionLibrary::FileCreate(mod_name + ("/Character/playerdefault"), OutputString);
		}
		else if (validity_parames[i] == EPrameType::PlayerMovement) {
			TSharedPtr <FJsonObject> JsonObject = MakeShareable(new FJsonObject);

			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("ContinuedSpeedForward"), player_movement_prame.ContinuedSpeedForward);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("ContinuedSpeedBackward"), player_movement_prame.ContinuedSpeedBackward);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("ContinuedSpeedHorizontal"), player_movement_prame.ContinuedSpeedHorizontal);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("StepLengthForward"), player_movement_prame.StepLengthForward);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("StepLengthBackward"), player_movement_prame.StepLengthBackward);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("StepLengthHorizontal"), player_movement_prame.StepLengthHorizontal);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("StepMoveTime"), player_movement_prame.StepMoveTime);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("StepRigidTime"), player_movement_prame.StepRigidTime);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("LockOnRotateSpeed"), player_movement_prame.LockOnRotateSpeed);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("LockOnRotateLimit"), player_movement_prame.LockOnRotateLimit);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("LockOnHeadLimit"), player_movement_prame.LockOnHeadLimit);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("LockOnDistanceLimit"), player_movement_prame.LockOnDistanceLimit);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("TurnAngle"), player_movement_prame.TurnAngle);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("TurnAngleAuto"), player_movement_prame.TurnAngleAuto);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("TurnTime"), player_movement_prame.TurnTime);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("TurnInterval"), player_movement_prame.TurnInterval);
			FuncLib::SetJsonFieldVal_Num(JsonObject, TEXT("FreeRotationSpeed"), player_movement_prame.FreeRotationSpeed);
			
			FString OutputString;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

			UMODToolBlueprintFunctionLibrary::FileCreate(mod_name + ("/Character/player_movement"), OutputString);
		}
	}

	TSharedPtr <FJsonObject> JsonObject1 = MakeShareable(new FJsonObject);

	FuncLib::SetJsonFieldVal_Num(JsonObject1, TEXT("PlayerStartTagPrefix"), player_movement_prame.FreeRotationSpeed);
	FuncLib::SetJsonFieldVal_Num(JsonObject1, TEXT("RoomId"), player_movement_prame.FreeRotationSpeed);
	FuncLib::SetJsonFieldVal_Num(JsonObject1, TEXT("Wave"), player_movement_prame.FreeRotationSpeed);

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