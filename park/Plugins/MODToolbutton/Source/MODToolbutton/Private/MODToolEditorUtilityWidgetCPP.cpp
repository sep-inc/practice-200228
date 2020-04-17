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


//int UMODToolEditorUtilityWidgetCPP::GetPrameItemCount(EPrameType Twpe) {
//
//	//switch (Twpe)
//	//{
//	//case EPrameType::Player:
//	//	int size = sizeof(FUnitParam);
//	//	FUnitParam s;
//	//	while (true)
//	//	{
//	//		sizeof(*(&s + 1));
//	//	}
//
//	//	break;
//	//case EPrameType::Weapons:
//	//	break;
//	//case EPrameType::Map:
//	//	break;
//	//}
//	return 0;
//
//
//}

//void UMODToolEditorUtilityWidgetCPP::GetPlayerPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
//	player_param.GetPrame(index, var_type, out1, out2, out3, out4);
//
//	//if (player_param.var_name.Num() > index && index >= 0) {
//	//	FString type = player_param.var_Type[index];
//
//	//	//prame.AddVar(TO_STRING(Damage), typeid(prame.Damage).name());	//const char* kata = typeid(a).name();
//
//	//	//FString kata = typeid(a).name();
//	//	if (type == "int") {
//	//		out1 = *((int32*)player_param.var_address[index]);
//	//		var_type = type;
//	//		return;
//	//	}
//	//	else if (type == "float") {
//	//		out2 = *((float*)player_param.var_address[index]);
//	//		var_type = type;
//	//		return;
//	//	}
//	//	else if (type == "class FString") {
//	//		out3 = *((FString*)player_param.var_address[index]);
//	//		var_type = type;
//	//		return;
//	//	}
//	//	else if (type == "__int64") {
//	//		out4 = *((int64*)player_param.var_address[index]);
//	//		var_type = type;
//	//		return;
//	//	}
//
//	//	var_type = type;
//	//}
//}

//void UMODToolEditorUtilityWidgetCPP::GetWeaponPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
//	weapon_param.GetPrame(index, var_type, out1, out2, out3, out4);
//}

//void UMODToolEditorUtilityWidgetCPP::GetMapPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3, int64& out4) {
//	map_param.GetPrame(index, var_type, out1, out2, out3, out4);
//}

//void UMODToolEditorUtilityWidgetCPP::SetPlayerPrame(int32 index, int32 in1, float in2, FString in3, int64 in4) {
//	player_param.SetPrame(index, in1, in2, in3, in4);
//	//if (player_param.var_name.Num() > index && index >= 0) {
//	//	FString type = player_param.var_Type[index];
//
//	//	//prame.AddVar(TO_STRING(Damage), typeid(prame.Damage).name());	//const char* kata = typeid(a).name();
//
//	//	//FString kata = typeid(a).name();
//	//	if (type == "int") {
//	//		*((int32*)player_param.var_address[index]) = in1;
//	//		return;
//	//	}
//	//	else if (type == "float") {
//	//		*((float*)player_param.var_address[index]) = in2;
//	//		return;
//	//	}
//	//	else if (type == "class FString") {
//	//		*((FString*)player_param.var_address[index]) = in3;
//	//					return;
//	//	}
//	//}
//}

//void UMODToolEditorUtilityWidgetCPP::SetWeaponPrame(int32 index, int32 in1, float in2, FString in3, int64 in4) {
//	weapon_param.SetPrame(index, in1, in2, in3, in4);
//}

//void UMODToolEditorUtilityWidgetCPP::SetMapPrame(int32 index, int32 in1, float in2, FString in3, int64 in4) {
//	map_param.SetPrame(index, in1, in2, in3, in4);
//}