// Fill out your copyright notice in the Description page of Project Settings.
#include "MODToolEditorUtilityWidgetCPP.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "IPlatformFilePak.h"


#include <typeinfo>

UMODToolEditorUtilityWidgetCPP::UMODToolEditorUtilityWidgetCPP() {
	player_param.AddVar(TO_STRING(Health), typeid(player_param.Health).name());
	player_param.AddVar(TO_STRING(Attack), typeid(player_param.Attack).name());
	player_param.AddVar(TO_STRING(Defense), typeid(player_param.Defense).name());
	player_param.AddVar(TO_STRING(Speed), typeid(player_param.Speed).name());
	player_param.AddVar(TO_STRING(test4), typeid(player_param.test4).name());
	player_param.AddVar(TO_STRING(test5), typeid(player_param.test5).name());
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

void UMODToolEditorUtilityWidgetCPP::GetPlayerPrame(int32 index, FString& var_type, int32& out1, float& out2, FString& out3) {
	if (player_param.var_name.Num() > index && index >= 0) {
		FString type = player_param.var_Type[index];

		//prame.AddVar(TO_STRING(Damage), typeid(prame.Damage).name());	//const char* kata = typeid(a).name();

		//FString kata = typeid(a).name();
		if (type == "int") {
			out1 = *(&player_param.start_var + 1 + index);
			var_type = type;
		}
		else if (type == "float") {
			out2 = *((float*)player_param.begin() + 1 + index);
			var_type = type;
		}
		else if (type == "class FString") {
			out3 = *((FString*)player_param.begin() + 1 + index);
			var_type = type;
		}

		var_type = type;
	}
}

void UMODToolEditorUtilityWidgetCPP::SetPlayerPrame(int32 index, int32 in1, float in2, FString in3) {
	if (player_param.var_name.Num() > index && index >= 0) {
		FString type = player_param.var_Type[index];

		//prame.AddVar(TO_STRING(Damage), typeid(prame.Damage).name());	//const char* kata = typeid(a).name();

		//FString kata = typeid(a).name();
		if (type == "int") {
			*((int32*)player_param.begin() + 1 + index) = in1;
		}
		else if (type == "float") {
			*((float*)player_param.begin() + 1 + index) = in2;
		}
		else if (type == "class FString") {
			*((FString*)player_param.begin() + 1 + index) = in3;
		}
	}
}