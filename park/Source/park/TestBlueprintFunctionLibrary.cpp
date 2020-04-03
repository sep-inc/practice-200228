// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBlueprintFunctionLibrary.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Editor/LevelEditor/Public/LevelEditor.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Editor/Blutility/Public/IBlutilityModule.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"

//AssetTypeActions_EditorUtilityWidgetBlueprint.cpp内にある、ExecuteRun()を移植しただけ。

void UTestBlueprintFunctionLibrary::RunEditorUtilityWidget(UWidgetBlueprint* Blueprint)
{
	if (Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
	{
		const UEditorUtilityWidget* CDO = (UEditorUtilityWidget*)Blueprint->GeneratedClass->GetDefaultObject();
		if (CDO->ShouldAutoRunDefaultAction())
		{
			// This is an instant-run blueprint, just execute it
			UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(GetTransientPackage(), Blueprint->GeneratedClass);
			Instance->ExecuteDefaultAction();
		}
		else
		{
			FName RegistrationName = FName(*(Blueprint->GetPathName() + TEXT("_ActiveTab")));
			FText DisplayName = FText::FromString(Blueprint->GetName());
			FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
			TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();

			////この部分を入れるとエラーが起きたので、とりあえず省いた。
			//if (!LevelEditorTabManager->CanSpawnTab(RegistrationName))
			//{
			//	IBlutilityModule* BlutilityModule = FModuleManager::GetModulePtr<IBlutilityModule>("Blutility");
			//	UEditorUtilityWidgetBlueprint* WidgetBlueprint = Cast<UEditorUtilityWidgetBlueprint>(Blueprint);
			//	
			//	WidgetBlueprint->SetRegistrationName(RegistrationName);
			//	LevelEditorTabManager->RegisterTabSpawner(RegistrationName, FOnSpawnTab::CreateUObject(WidgetBlueprint, &UEditorUtilityWidgetBlueprint::SpawnEditorUITab))
			//		.SetDisplayName(DisplayName)
			//		.SetGroup(BlutilityModule->GetMenuGroup().ToSharedRef());
			//	BlutilityModule->AddLoadedScriptUI(WidgetBlueprint);
			//}
			
			TSharedRef<SDockTab> NewDockTab = LevelEditorTabManager->InvokeTab(RegistrationName);
		}
	}

}


TSharedRef<SDockTab> SpawnEditorUITab(const FSpawnTabArgs& SpawnTabArgst, UWidgetBlueprint* Blueprint) {
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab);
	TSubclassOf<UEditorUtilityWidget> WidgetClass = Blueprint->GeneratedClass;
	UWorld* World = GEditor->GetEditorWorldContext().World();
	check(World);
	UEditorUtilityWidget* CreatedUMGWidget = CreateWidget<UEditorUtilityWidget>(World, WidgetClass);
	if (CreatedUMGWidget)
	{
		TSharedRef<SWidget> CreatedSlateWidget = CreatedUMGWidget->TakeWidget();
		SpawnedTab->SetContent(CreatedSlateWidget);
	}

	return SpawnedTab;
}


//EUW生成
void UTestBlueprintFunctionLibrary::RunWidget(UWidgetBlueprint* Blueprint)
{
	if (Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
	{
		const UEditorUtilityWidget* CDO = Blueprint->GeneratedClass->GetDefaultObject<UEditorUtilityWidget>();
		if (CDO->ShouldAutoRunDefaultAction())
		{
			// This is an instant-run blueprint, just execute it
			UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(GetTransientPackage(), Blueprint->GeneratedClass);
			Instance->ExecuteDefaultAction();
		}
		else
		{
			FName RegistrationName = FName(*(Blueprint->GetPathName() + TEXT("_ActiveTab")));
			FText DisplayName = FText::FromString(Blueprint->GetName());
			FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
			TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			if (!LevelEditorTabManager->CanSpawnTab(RegistrationName))
			{
				LevelEditorTabManager->RegisterTabSpawner(RegistrationName, FOnSpawnTab::CreateStatic(&SpawnEditorUITab, Blueprint))
					.SetDisplayName(DisplayName)
					.SetMenuType(ETabSpawnerMenuType::Hidden);
			}

			TSharedRef<SDockTab> NewDockTab = LevelEditorTabManager->InvokeTab(RegistrationName);
		}
	}
}