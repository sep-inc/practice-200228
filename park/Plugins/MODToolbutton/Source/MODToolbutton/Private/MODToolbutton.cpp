// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MODToolbutton.h"
#include "MODToolbuttonStyle.h"
#include "MODToolbuttonCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"

#include "LevelEditor.h"

static const FName MODToolbuttonTabName("MODToolbutton");

#define LOCTEXT_NAMESPACE "FMODToolbuttonModule"

void FMODToolbuttonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMODToolbuttonStyle::Initialize();
	FMODToolbuttonStyle::ReloadTextures();

	FMODToolbuttonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMODToolbuttonCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMODToolbuttonModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMODToolbuttonModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMODToolbuttonModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FMODToolbuttonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMODToolbuttonStyle::Shutdown();

	FMODToolbuttonCommands::Unregister();
}

void FMODToolbuttonModule::PluginButtonClicked()
{
	FString path = "EditorUtilityWidgetBlueprint'/MODToolbuttonContent/EUW/ToolEUW.ToolEUW'";
	UWidgetBlueprint* sc = TSoftObjectPtr<UWidgetBlueprint>(FSoftObjectPath(*path)).LoadSynchronous(); // ’¼ÚUEditorUtilityWidgetBlueprint‚ðŽó‚¯Žæ‚é‚±‚Æ‚Ío—ˆ‚È‚¢‚Á‚Û‚¢
	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	UEditorUtilityWidgetBlueprint* euwb = (UEditorUtilityWidgetBlueprint*)sc;
	EditorUtilitySubsystem->SpawnAndRegisterTab(euwb);
}

void FMODToolbuttonModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMODToolbuttonCommands::Get().PluginAction);
}

void FMODToolbuttonModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMODToolbuttonCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMODToolbuttonModule, MODToolbutton)