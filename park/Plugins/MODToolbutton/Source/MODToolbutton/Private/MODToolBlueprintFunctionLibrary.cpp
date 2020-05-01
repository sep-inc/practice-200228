// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "IPlatformFilePak.h"

#include "Math/NumericLimits.h"
#include <typeinfo>
#include <string>
#include "MODToolBlueprintFunctionLibrary.h"

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

	int64 max_size = 0;
	int32 digit = 0;
	bool minus;
	FString a;

	if (in[0] == TCHAR('-')) {
		max_size = INT64_MIN;
		digit = 20;
		a = in.RightChop(1);
		minus = true;
	}
	else {
		max_size = INT64_MAX;
		digit = 19;
		a = in;
		minus = false;
	}

	char* var = TCHAR_TO_ANSI(*a);

	//桁数チェック
	if (in.Len() < digit) {
		return minus ? -(std::stoll(var)) : std::stoll(var);
	}

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
		return minus ? -(std::stoll(var)) : std::stoll(var);
	}
	else {
		return max_size;
	}


}

FString UMODToolBlueprintFunctionLibrary::int64ToString(int64 in) {
	char a[1000];
	sprintf(a, "%lld", in);
	FString out = a;
	return out;
}


//
