// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "IPlatformFilePak.h"
#include "MODToolBlueprintFunctionLibrary.h"
#include "Math/NumericLimits.h"
#include <typeinfo>
#include <string>

FString UMODToolBlueprintFunctionLibrary::FileCreate(FString file_name, FString in) {

	if (FFileHelper::SaveStringToFile(in, *(FPaths::GameContentDir() + FString("Mod/") + file_name + FString(".json")))) {
		return (FString)FPaths::GameDir() + FString("Mod/") + file_name + FString(".json");

	}
	return FString("null");
}

TSharedPtr<FJsonObject> UMODToolBlueprintFunctionLibrary::LoadJsonObject(FString file_name) {
	//フルパス生成
	const FString JsonFullPath = FPaths::GameContentDir().Append(TEXT("Mod/")).Append(file_name).Append(TEXT(".json"));

	//エラー処理
	auto LoadError = [&JsonFullPath]()

	{

		UE_LOG(LogTemp, Error, TEXT("Failed LoadJson : %s"), *JsonFullPath);

		return nullptr;

	};


	FString loadFileString;
	if (FFileHelper::LoadFileToString(loadFileString, *JsonFullPath) == false)

	{

		LoadError();

	}

	const auto JsonReader = TJsonReaderFactory<TCHAR>::Create(loadFileString);

	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());



	if (FJsonSerializer::Deserialize(JsonReader, jsonObject) && jsonObject.IsValid())

	{

		return jsonObject;

	}

	return LoadError();
}

int UMODToolBlueprintFunctionLibrary::GetJsonValueinteger(FString file_name, FString field_name) {

	const TSharedPtr<FJsonObject> JsonObject = LoadJsonObject(file_name);
	if (JsonObject.IsValid() == false)
	{
		return false;
	}

	return JsonObject->GetIntegerField(field_name);
}

int64 UMODToolBlueprintFunctionLibrary::StringToInt64(FString in) {
	if (!in.IsNumeric()) {
		return 0;
	}
	
	if (in[0] == TCHAR('-')) {
		if (in.Len() > 1 && in.Len() <= 20) {
			FString a = in.RightChop(1);
			char* var = TCHAR_TO_ANSI(*a);
			if (a.Len() == 19) {
				FString var_max = "9223372036854775807";

				for (int i = 0; i < 19; i++) {
					char* inst = TCHAR_TO_ANSI(*a.Mid(i, 1));
					char* inst2 = TCHAR_TO_ANSI(*var_max.Mid(i, 1));

					int64 c = std::stoll(inst);
					int64 b = std::stoll(inst2);
					if (c == b) {
						continue;
					}
					else if (c > b) {
						return INT64_MIN;
					}
					else {
						break;
					}
				}
			}
			return -(std::stoll(var));

		}
		return INT64_MIN;
	}
	else {
		//char* a = TCHAR_TO_ANSI(*in);
		//return std::stoll(a)
		char* var = TCHAR_TO_ANSI(*in);
		if (in.Len() <= 19) {
			
			if (in.Len() == 19) {
				FString var_max = "9223372036854775807";

				for (int i = 0; i < 19; i++) {
					char* inst = TCHAR_TO_ANSI(*in.Mid(i,1));
					char* inst2 = TCHAR_TO_ANSI(*var_max.Mid(i, 1));
					
					int64 c = std::stoll(inst);
					int64 b = std::stoll(inst2);
					if (c == b) {
						continue;
					}
					else if (c > b) {
						return INT64_MAX;
					}
					else {
						break;
					}
				}
			}
			return std::stoll(var);
		}
		return INT64_MAX;
	}
}

FString UMODToolBlueprintFunctionLibrary::int64ToString(int64 in) {
	char a[1000];
	sprintf(a, "%lld", in);
	FString out = a;
	return out;
}

//
//int UMODToolBlueprintFunctionLibrary::GetPrameItemCount(EPrameType Twpe) {
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
//
//FString UMODToolBlueprintFunctionLibrary::GetPlayerPrame(FPlayerParam prame, int32 index, int32& out1, float& out2, FString& out3) {
//
//	prame.AddVar(TO_STRING(Damage), typeid(prame.Damage).name());
//	const float a = *(&prame.start_var + 1);
//	//const char* kata = typeid(a).name();
//
//	FString kata = typeid(a).name();
//	if (kata == "int") {
//		out1 = a;
//		return kata;
//	}
//	else if (kata == "float") {
//		out2 = a;
//		return kata;
//	}
//	else if (kata == "class FString") {
//		//out3 = FString((char*)a);
//		return kata;
//	}
//
//	return kata;
//}
//
