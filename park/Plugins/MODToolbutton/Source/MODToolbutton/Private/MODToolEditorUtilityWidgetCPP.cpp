// Fill out your copyright notice in the Description page of Project Settings.
#include "MODToolEditorUtilityWidgetCPP.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "IPlatformFilePak.h"


#include <typeinfo>



UMODToolEditorUtilityWidgetCPP::UMODToolEditorUtilityWidgetCPP() {
	AddPlayerPrame(TO_STRING(Health), typeid(player_param.Health).name(), &player_param.Health);
	AddPlayerPrame(TO_STRING(Attack), typeid(player_param.Attack).name(), &player_param.Attack);
	AddPlayerPrame(TO_STRING(Defense), typeid(player_param.Defense).name(), &player_param.Defense);
	AddPlayerPrame(TO_STRING(Speed), typeid(player_param.Speed).name(), &player_param.Speed);
	AddPlayerPrame(TO_STRING(int32_var), typeid(player_param.int32_var).name(), &player_param.int32_var);
	AddPlayerPrame(TO_STRING(float_var), typeid(player_param.float_var).name(), &player_param.float_var);
	AddPlayerPrame(TO_STRING(string_var), typeid(player_param.string_var).name(), &player_param.string_var);
	AddPlayerPrame(TO_STRING(int64_var), typeid(player_param.int64_var).name(), &player_param.int64_var);

	AddWeaponPrame(TO_STRING(Durability), typeid(weapon_param.Durability).name(), &weapon_param.Durability);
	AddWeaponPrame(TO_STRING(Attack), typeid(weapon_param.Attack).name(), &weapon_param.Attack);
	AddWeaponPrame(TO_STRING(Defense), typeid(weapon_param.Defense).name(), &weapon_param.Defense);
	AddWeaponPrame(TO_STRING(Weight), typeid(weapon_param.Weight).name(), &weapon_param.Weight);

	AddMapPrame(TO_STRING(Health), typeid(map_param.Health).name(), &map_param.Health);
	AddMapPrame(TO_STRING(Attack), typeid(map_param.Attack).name(), &map_param.Attack);
	AddMapPrame(TO_STRING(Defense), typeid(map_param.Defense).name(), &map_param.Defense);
	AddMapPrame(TO_STRING(Speed), typeid(map_param.Speed).name(), &map_param.Speed);
	AddMapPrame(TO_STRING(test4), typeid(map_param.test4).name(), &map_param.test4);
	AddMapPrame(TO_STRING(test5), typeid(map_param.test5).name(), &map_param.test5);

	//AddEnemyPrame(TO_STRING(id), typeid(enemy_param_measurement.id).name(), &enemy_param_measurement.id);
	AddEnemyPrame(TO_STRING(param1), typeid(enemy_param_measurement.param1).name(), &enemy_param_measurement.param1);
	AddEnemyPrame(TO_STRING(param2), typeid(enemy_param_measurement.param2).name(), &enemy_param_measurement.param2);
	AddEnemyPrame(TO_STRING(param3), typeid(enemy_param_measurement.param3).name(), &enemy_param_measurement.param3);
}

void UMODToolEditorUtilityWidgetCPP::AddPlayerPrame(const char* name, const char* type, void* aa) {
	player_param.AddVar(name, type, aa);
	int64 byte_count = (int64)(aa) - (int64)(&player_param.start);

	int64 max_address = (int64)(&player_param_max.start) + byte_count;
	int64 min_address = (int64)(&player_param_min.start) + byte_count;

	player_param_max.AddVar(name, type, (void*)max_address);
	player_param_min.AddVar(name, type, (void*)min_address);
}

void UMODToolEditorUtilityWidgetCPP::AddWeaponPrame(const char* name, const char* type, void* aa) {
	weapon_param.AddVar(name, type, aa);
	int64 byte_count = (int64)(aa)-(int64)(&weapon_param.start);

	int64 max_address = (int64)(&weapon_param_max.start) + byte_count;
	int64 min_address = (int64)(&weapon_param_min.start) + byte_count;

	weapon_param_max.AddVar(name, type, (void*)max_address);
	weapon_param_min.AddVar(name, type, (void*)min_address);
}

void UMODToolEditorUtilityWidgetCPP::AddMapPrame(const char* name, const char* type, void* aa) {
	map_param.AddVar(name, type, aa);
	int64 byte_count = (int64)(aa)-(int64)(&map_param.start);

	int64 max_address = (int64)(&map_param_max.start) + byte_count;
	int64 min_address = (int64)(&map_param_min.start) + byte_count;

	map_param_max.AddVar(name, type, (void*)max_address);
	map_param_min.AddVar(name, type, (void*)min_address);
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

	enemy_param_max.AddVar(name, type, (void*)max_address);
	enemy_param_min.AddVar(name, type, (void*)min_address);
}

void UMODToolEditorUtilityWidgetCPP::AddWave() {
	map_wave_param.Add(FMapWaveParam());
	int32 index_num = map_wave_param.Num() - 1;
	map_wave_param[index_num].enemy.Init(FEnemyParam(),6);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < map_wave_param_addres.Num(); j++) {
			int64 address = (int64)(&map_wave_param[index_num].enemy[i].start) + map_wave_param_addres[j].byte_count;
			map_wave_param[index_num].enemy[i].AddVar(
				TCHAR_TO_ANSI(*map_wave_param_addres[j].name),
				TCHAR_TO_ANSI(*map_wave_param_addres[j].type),
				(void*)address
				);
		}
	}

}
