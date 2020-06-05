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

	//プレイヤーパラメーター
	StartAddress player_parame_start;
	player_parame_start.main_address = (int64)(&player_param.start);
	player_parame_start.max_address = (int64)(&player_param_max.start);
	player_parame_start.min_address = (int64)(&player_param_min.start);

	player_param_max.Health = 100.f;
	player_param_min.Health = 0.f;
	AddPrame(EPrameType::Player, player_parame_start,
		TO_STRING(Health), typeid(player_param.Health).name(), &player_param.Health);
	player_param_max.Attack = 100.f;
	player_param_min.Attack = 0.f;
	AddPrame(EPrameType::Player, player_parame_start,
		TO_STRING(Attack), typeid(player_param.Attack).name(), &player_param.Attack);
	player_param_max.Defense = 100.f;
	player_param_min.Defense = 0.f;
	AddPrame(EPrameType::Player, player_parame_start,
		TO_STRING(Defense), typeid(player_param.Defense).name(), &player_param.Defense);
	player_param_max.Speed = 100.f;
	player_param_min.Speed = 0.f;
	AddPrame(EPrameType::Player, player_parame_start,
		TO_STRING(Speed), typeid(player_param.Speed).name(), &player_param.Speed);
	player_param_max.int32_var = 100.f;
	player_param_min.int32_var = 0.f;
	AddPrame(EPrameType::Player, player_parame_start,
		TO_STRING(int32_var), typeid(player_param.int32_var).name(), &player_param.int32_var);
	player_param_max.float_var = 100.f;
	player_param_min.float_var = 0.f;
	AddPrame(EPrameType::Player, player_parame_start,
		TO_STRING(float_var), typeid(player_param.float_var).name(), &player_param.float_var);
	player_param_max.string_var = "";
	player_param_min.string_var = "";
	AddPrame(EPrameType::Player, player_parame_start,
		TO_STRING(string_var), typeid(player_param.string_var).name(), &player_param.string_var);
	player_param_max.int64_var = 100.f;
	player_param_min.int64_var = 0.f;
	AddPrame(EPrameType::Player, player_parame_start,
		TO_STRING(int64_var), typeid(player_param.int64_var).name(), &player_param.int64_var);

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

	//ウェポンパラメーター
	StartAddress weapon_param_start;
	weapon_param_start.main_address = (int64)(&weapon_param.start);
	weapon_param_start.max_address = (int64)(&weapon_param_max.start);
	weapon_param_start.min_address = (int64)(&weapon_param_min.start);

	weapon_param_max.Durability = 200;
	weapon_param_min.Durability = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(Durability), typeid(weapon_param.Durability).name(), &weapon_param.Durability);
	weapon_param_max.Attack = 200;
	weapon_param_min.Attack = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(Attack), typeid(weapon_param.Attack).name(), &weapon_param.Attack);
	weapon_param_max.Defense = 200;
	weapon_param_min.Defense = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(Defense), typeid(weapon_param.Defense).name(), &weapon_param.Defense);
	weapon_param_max.Weight = 200;
	weapon_param_min.Weight = 0;
	AddPrame(EPrameType::Weapons, weapon_param_start,
		TO_STRING(Weight), typeid(weapon_param.Weight).name(), &weapon_param.Weight);

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
	enemy_param_max.param1 = 400;
	enemy_param_min.param1 = 0;
	AddEnemyPrame(TO_STRING(param1), typeid(enemy_param_measurement.param1).name(), &enemy_param_measurement.param1);
	enemy_param_max.param2 = 400;
	enemy_param_min.param2 = 0;
	AddEnemyPrame(TO_STRING(param2), typeid(enemy_param_measurement.param2).name(), &enemy_param_measurement.param2);
	enemy_param_max.param3 = 400;
	enemy_param_min.param3 = 0;
	AddEnemyPrame(TO_STRING(param3), typeid(enemy_param_measurement.param3).name(), &enemy_param_measurement.param3);

	

}

UMODToolEditorUtilityWidgetCPP::~UMODToolEditorUtilityWidgetCPP() {

}


void UMODToolEditorUtilityWidgetCPP::Initialization(TMap<EPrameType, UScrollBox*> set_scroll_box) {

	prame_scroll_box = set_scroll_box;
	//SetPrames();
}

void UMODToolEditorUtilityWidgetCPP::SetPrames() {
	prames.Add(EPrameType::Player, player_param.search);
	prames.Add(EPrameType::PlayerMovement, player_movement_prame.search);
	prames.Add(EPrameType::Weapons, weapon_param.search);
	prames.Add(EPrameType::Map, map_param.search);

	max_prames.Add(EPrameType::Player, player_param_max.search);
	max_prames.Add(EPrameType::PlayerMovement, player_movement_max.search);
	max_prames.Add(EPrameType::Weapons, weapon_param_max.search);
	max_prames.Add(EPrameType::Map, map_param_max.search);

	min_prames.Add(EPrameType::Player, player_param_min.search);
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
		if (validity_parames[i] == EPrameType::PlayerMovement) {
			TSharedPtr <FJsonObject> JsonObject = MakeShareable(new FJsonObject);
			TSharedPtr<FJsonValueNumber> value1 = MakeShareable(new FJsonValueNumber(player_movement_prame.ContinuedSpeedForward));
			JsonObject->SetField(TEXT("ContinuedSpeedForward"), value1);

			TSharedPtr<FJsonValueNumber> value2 = MakeShareable(new FJsonValueNumber(player_movement_prame.ContinuedSpeedBackward));
			JsonObject->SetField(TEXT("ContinuedSpeedBackward"), value2);

			TSharedPtr<FJsonValueNumber> value3 = MakeShareable(new FJsonValueNumber(player_movement_prame.ContinuedSpeedHorizontal));
			JsonObject->SetField(TEXT("ContinuedSpeedHorizontal"), value3);

			FString OutputString;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

			UMODToolBlueprintFunctionLibrary::FileCreate(mod_name.Append("/Character/player_movement"), OutputString);
		}
	}
	
}


void UMODToolEditorUtilityWidgetCPP::AddPrame(EPrameType type, StartAddress s_a, const char* name, const char* var_type, void* aa) {
	prames[type].AddVar(name, var_type, aa);
	int64 byte_count = (int64)(aa) - s_a.main_address;

	int64 max_address = s_a.max_address + byte_count;
	int64 min_address = s_a.min_address + byte_count;

	max_prames[type].AddVar(name, var_type, (void*)max_address);
	min_prames[type].AddVar(name, var_type, (void*)min_address);

}

void UMODToolEditorUtilityWidgetCPP::AddPlayerPrame(const char* name, const char* type, void* aa) {
	player_param.search.AddVar(name, type, aa);
	int64 byte_count = (int64)(aa) - (int64)(&player_param.start);

	int64 max_address = (int64)(&player_param_max.start) + byte_count;
	int64 min_address = (int64)(&player_param_min.start) + byte_count;

	player_param_max.search.AddVar(name, type, (void*)max_address);
	player_param_min.search.AddVar(name, type, (void*)min_address);
}

void UMODToolEditorUtilityWidgetCPP::AddWeaponPrame(const char* name, const char* type, void* aa) {
	weapon_param.search.AddVar(name, type, aa);
	int64 byte_count = (int64)(aa)-(int64)(&weapon_param.start);

	int64 max_address = (int64)(&weapon_param_max.start) + byte_count;
	int64 min_address = (int64)(&weapon_param_min.start) + byte_count;

	weapon_param_max.search.AddVar(name, type, (void*)max_address);
	weapon_param_min.search.AddVar(name, type, (void*)min_address);
}

void UMODToolEditorUtilityWidgetCPP::AddMapPrame(const char* name, const char* type, void* aa) {
	map_param.search.AddVar(name, type, aa);
	int64 byte_count = (int64)(aa)-(int64)(&map_param.start);

	int64 max_address = (int64)(&map_param_max.start) + byte_count;
	int64 min_address = (int64)(&map_param_min.start) + byte_count;

	map_param_max.search.AddVar(name, type, (void*)max_address);
	map_param_min.search.AddVar(name, type, (void*)min_address);
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
	map_wave_param.Add(FMapWaveParam());
	int32 index_num = map_wave_param.Num() - 1;
	map_wave_param[index_num].enemy.Init(FEnemyParam(),6);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < map_wave_param_addres.Num(); j++) {
			int64 address = (int64)(&map_wave_param[index_num].enemy[i].start) + map_wave_param_addres[j].byte_count;
			map_wave_param[index_num].enemy[i].search.AddVar(
				TCHAR_TO_ANSI(*map_wave_param_addres[j].name),
				TCHAR_TO_ANSI(*map_wave_param_addres[j].type),
				(void*)address
				);
		}
	}

}

void UMODToolEditorUtilityWidgetCPP::InsertWave(int32 index) {
	int32 set_index = map_wave_param.Insert(FMapWaveParam(), index - 1);
	map_wave_param[set_index].enemy.Init(FEnemyParam(), 6);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < map_wave_param_addres.Num(); j++) {
			int64 address = (int64)(&map_wave_param[set_index].enemy[i].start) + map_wave_param_addres[j].byte_count;
			map_wave_param[set_index].enemy[i].search.AddVar(
				TCHAR_TO_ANSI(*map_wave_param_addres[j].name),
				TCHAR_TO_ANSI(*map_wave_param_addres[j].type),
				(void*)address
			);
		}
	}
}

void UMODToolEditorUtilityWidgetCPP::RemoveWave(int32 index) {
	if (index < 1 || index > map_wave_param.Num() + 1) {
		return;
	}
	map_wave_param.RemoveAt(index - 1);
}