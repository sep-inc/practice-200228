// Fill out your copyright notice in the Description page of Project Settings.

#include "MODToolBlueprintFunctionLibrary.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "IPlatformFilePak.h"

//#include "PakFileUtilities.h"
#include "PakFileUtilities/Public/PakFileUtilities.h"

#include "HAL/PlatformFilemanager.h"
#include "Async/ParallelFor.h"
#include "Async/AsyncWork.h"
#include "Modules/ModuleManager.h"
#include "DerivedDataCacheInterface.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "Misc/Compression.h"
#include "Math/NumericLimits.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/FileManager.h"
#include "HAL/FileManagerGeneric.h"
#include <typeinfo>
#include <string>






FString UMODToolBlueprintFunctionLibrary::FileCreate(FString file_name, FString in) {

	if (FFileHelper::SaveStringToFile(in, *(FPaths::ProjectPluginsDir() + FString("MODToolbuttonContent/Content/EUW/Package/") + file_name + FString(".json")))) {
		return (FString)FPaths::GameDir() + FString("Mod/") + file_name + FString(".json");

	}
	return FString("null");
}

TSharedPtr<FJsonObject> UMODToolBlueprintFunctionLibrary::LoadJsonObject(FString file_name) {
	//フルパス生成
	const FString JsonFullPath = FPaths::ProjectPluginsDir().Append("MODToolbuttonContent/Content/EUW/Package/").Append(file_name).Append(TEXT(".json"));

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


TArray<int32> UMODToolBlueprintFunctionLibrary::StringSort_OutNum(TArray<FString> in, bool ascending_worder) {
	TArray<FString> inst = in;

	if (ascending_worder) {
		inst.Sort([](const FString& A, const FString& B) {
			return A > B;
			}
		);
	}
	else {
		inst.Sort([](const FString& A, const FString& B) {
			return A < B;
			}
		);

	}

	TArray<int32> num;

	for (int i = 0; i < in.Num(); i++) {
		for (int j = 0; j < inst.Num(); j++) {
			if (in[i] == inst[j] && inst[j] != "") {
				inst[j] = "";
				num.Add(j);
				break;
			}
		}
	}
	return num;
}

void UMODToolBlueprintFunctionLibrary::CreateModPackage(bool& ErrorFrag) {
	ErrorFrag = false;
	FString PakFromPath = FPaths::EngineDir().Append("Binaries/Win64/ModPackage.pak");
	FString PakToPath = FPaths::ProjectPluginsDir().Append("MODToolbuttonContent/Content/EUW/Package/ModPackage.pak");

	FString cmd = FString("ModPackage.pak = ").Append(FPaths::ProjectPluginsDir()).Append("MODToolbuttonContent/Content/EUW/Asset/");
	ExecuteUnrealPak(*cmd);


	if (!FFileManagerGeneric::Get().Move(*PakToPath, *PakFromPath)) {
		UE_LOG(LogTemp, Error, TEXT("Could not be packaged."));
		ErrorFrag = true;
		return;
	}

	FPakFile file(&FPlatformFileManager::Get().GetPlatformFile(), *PakToPath,false);
	if (!file.Check()) {
		UE_LOG(LogTemp, Error, TEXT("ERROR"));
		ErrorFrag = true;
		return;
	}

}

void UMODToolBlueprintFunctionLibrary::GetPackageFolderNames(TArray<FString>& out) {
	FString PakPath = FPaths::ProjectPluginsDir().Append("MODToolbuttonContent/Content/EUW/Package/ModPackage.pak");

	FPakFile file(&FPlatformFileManager::Get().GetPlatformFile(), *PakPath, false);
	if (!file.Check()) {
		UE_LOG(LogTemp, Error, TEXT("ERROR"));
	}

	file.GetFilenames(out);
}

void UMODToolBlueprintFunctionLibrary::SetJsonFieldVal_Num(TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, double InNumber) {
	TSharedPtr<FJsonValueNumber> value = MakeShareable(new FJsonValueNumber(InNumber));
	JsonObject->SetField(FieldName, value);

}

void UMODToolBlueprintFunctionLibrary::SetJsonFieldVal_String(TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, const FString& InString) {
	TSharedPtr<FJsonValueString> value = MakeShareable(new FJsonValueString(InString));
	JsonObject->SetField(FieldName, value);
}

void UMODToolBlueprintFunctionLibrary::SetJsonFieldVal_Bool(TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, bool InBool) {
	TSharedPtr<FJsonValueBoolean> value = MakeShareable(new FJsonValueBoolean(InBool));
	JsonObject->SetField(FieldName, value);
}





