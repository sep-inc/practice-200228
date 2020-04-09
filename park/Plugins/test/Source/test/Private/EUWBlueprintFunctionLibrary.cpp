// Fill out your copyright notice in the Description page of Project Settings.


#include "EUWBlueprintFunctionLibrary.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Editor/LevelEditor/Public/LevelEditor.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Editor/Blutility/Public/IBlutilityModule.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "UObject/Package.h"
#include "IPlatformFilePak.h"
#include "HAL/PlatformFilemanager.h"

//void UEUWBlueprintFunctionLibrary::RunEditorUtilityWidget(UWidgetBlueprint* Blueprint)
//{
//	if (Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
//	{
//		const UEditorUtilityWidget* CDO = (UEditorUtilityWidget*)Blueprint->GeneratedClass->GetDefaultObject();
//		if (CDO->ShouldAutoRunDefaultAction())
//		{
//			// This is an instant-run blueprint, just execute it
//			UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(GetTransientPackage(), Blueprint->GeneratedClass);
//			Instance->ExecuteDefaultAction();
//		}
//		else
//		{
//			FName RegistrationName = FName(*(Blueprint->GetPathName() + TEXT("_ActiveTab")));
//			FText DisplayName = FText::FromString(Blueprint->GetName());
//			FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
//			TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
//
//			////この部分を入れるとエラーが起きたので、とりあえず省いた。
//			//if (!LevelEditorTabManager->CanSpawnTab(RegistrationName))
//			//{
//			//	IBlutilityModule* BlutilityModule = FModuleManager::GetModulePtr<IBlutilityModule>("Blutility");
//			//	UEditorUtilityWidgetBlueprint* WidgetBlueprint = Cast<UEditorUtilityWidgetBlueprint>(Blueprint);
//			//	
//			//	WidgetBlueprint->SetRegistrationName(RegistrationName);
//			//	LevelEditorTabManager->RegisterTabSpawner(RegistrationName, FOnSpawnTab::CreateUObject(WidgetBlueprint, &UEditorUtilityWidgetBlueprint::SpawnEditorUITab))
//			//		.SetDisplayName(DisplayName)
//			//		.SetGroup(BlutilityModule->GetMenuGroup().ToSharedRef());
//			//	BlutilityModule->AddLoadedScriptUI(WidgetBlueprint);
//			//}
//
//			TSharedRef<SDockTab> NewDockTab = LevelEditorTabManager->InvokeTab(RegistrationName);
//
//		}
//	}
//
//}


//TSharedRef<SDockTab> SpawnEditorUITab(const FSpawnTabArgs& SpawnTabArgst, UWidgetBlueprint* Blueprint) {
//	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab);
//	TSubclassOf<UEditorUtilityWidget> WidgetClass = Blueprint->GeneratedClass;
//	UWorld* World = GEditor->GetEditorWorldContext().World();
//	check(World);
//	UEditorUtilityWidget* CreatedUMGWidget = CreateWidget<UEditorUtilityWidget>(World, WidgetClass);
//	if (CreatedUMGWidget)
//	{
//		TSharedRef<SWidget> CreatedSlateWidget = CreatedUMGWidget->TakeWidget();
//		SpawnedTab->SetContent(CreatedSlateWidget);
//	}
//
//	return SpawnedTab;
//}

//
////EUW生成
//void UEUWBlueprintFunctionLibrary::RunWidget(UWidgetBlueprint* Blueprint)
//{
//	if (Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
//	{
//		const UEditorUtilityWidget* CDO = Blueprint->GeneratedClass->GetDefaultObject<UEditorUtilityWidget>();
//		if (CDO->ShouldAutoRunDefaultAction())
//		{
//			// This is an instant-run blueprint, just execute it
//			UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(GetTransientPackage(), Blueprint->GeneratedClass);
//			Instance->ExecuteDefaultAction();
//		}
//		else
//		{
//			FName RegistrationName = FName(*(Blueprint->GetPathName() + TEXT("_ActiveTab")));
//			FText DisplayName = FText::FromString(Blueprint->GetName());
//			FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
//			TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
//			if (!LevelEditorTabManager->CanSpawnTab(RegistrationName))
//			{
//				LevelEditorTabManager->RegisterTabSpawner(RegistrationName, FOnSpawnTab::CreateStatic(&SpawnEditorUITab, Blueprint))
//					.SetDisplayName(DisplayName)
//					.SetMenuType(ETabSpawnerMenuType::Hidden);
//			}
//
//			TSharedRef<SDockTab> NewDockTab = LevelEditorTabManager->InvokeTab(RegistrationName);
//		}
//	}
//}

FString UEUWBlueprintFunctionLibrary::FileCreate(FString file_name, FString in) {

	if (FFileHelper::SaveStringToFile(in, *(FPaths::GameContentDir() + FString("Mod/") + file_name + FString(".json")))) {
		return (FString)FPaths::GameDir() + FString("Mod/") + file_name + FString(".json");

	}
	return FString("null");
}

TSharedPtr<FJsonObject> UEUWBlueprintFunctionLibrary::LoadJsonObject(FString file_name) {
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

int UEUWBlueprintFunctionLibrary::GetJsonValueinteger(FString file_name, FString field_name) {

	const TSharedPtr<FJsonObject> JsonObject = LoadJsonObject(file_name);
	if (JsonObject.IsValid() == false)
	{
		return false;
	}

	return JsonObject->GetIntegerField(field_name);
}

void UEUWBlueprintFunctionLibrary::CreatePackage2(UObject* obj, FString file_name) {

	FString name = FString("/Game/Mod/") + file_name;


	//パッケージ化(.uasset)
	//UPackage* prk = CreatePackage(NULL, *name);
	//prk->FullyLoad();
	//prk->SetFolderName("aaa");
	//
	//
	//FString PackageFileName = FPackageName::LongPackageNameToFilename(name, FPackageName::GetAssetPackageExtension());
	//UPackage::SavePackage(prk, UPackage::EditorPackage, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName);
	//UPackage::SavePackage(prk, obj, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName);

	//const int32 PakOrder = 0;
	//FString inname = FPaths::GameContentDir() + FString("Game/Mod/trstdrt.pak");
	//const FString outname = FPaths::GameContentDir() + FString("Game/Mod/test");
	//FPakPlatformFile* PakPlatform = new FPakPlatformFile();

	//IPlatformFile* LocalPlatformFile = &FPlatformFileManager::Get().GetPlatformFile();

	//if (LocalPlatformFile != nullptr)

	//{

	//	IPlatformFile* PakPlatformFile = FPlatformFileManager::Get().GetPlatformFile(TEXT("PakFile"));

	//	//if (PakPlatformFile != nullptr) bSuccessfulInitialization = true;

	//}

	//pakファイル作成(動かない)
	//FPakFile pakFile(LocalPlatformFile, *inname, false);

	/*IPlatformFile* InnerPlatform = LocalPlatformFile;
	const TCHAR* cmdLine = TEXT("");
	PakPlatform->Initialize(InnerPlatform, cmdLine);
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatform);*/
	//PakPlatform->CreateDirectory(TEXT("asdgfds"));
	
	//PakPlatform->Mount(*outname, PakOrder,*inname);
	

	
	//delete(PakPlatform);
	
}


FString UEUWBlueprintFunctionLibrary::PackageFolder()

{

	FString FileDir = FPaths::GamePersistentDownloadDir() + "/DownPaks/";

	FPaths::NormalizeDirectoryName(FileDir);

	return FString(FPaths::ConvertRelativePathToFull(FileDir));

}

