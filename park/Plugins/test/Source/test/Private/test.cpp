// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "test.h"
#include "testStyle.h"
#include "testCommands.h"
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"
#include "Misc/MessageDialog.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Editor/Blutility/Public/EditorUtilityLibrary.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprintFactory.h"

#include "LevelEditor.h"

static const FName testTabName("test");

#define LOCTEXT_NAMESPACE "FtestModule"

void FtestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FtestStyle::Initialize();
	FtestStyle::ReloadTextures();

	FtestCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FtestCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FtestModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FtestModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FtestModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FtestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FtestStyle::Shutdown();

	FtestCommands::Unregister();
}

void FtestModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FtestModule::PluginButtonClicked()")),
							FText::FromString(TEXT("aaaaaaaaaaaatest.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	
	

	TSharedRef<SWindow> cbw = SNew(SWindow)
		.Title(FText::FromString(TEXT("Test")))
		.ClientSize(FVector2D(800.400))
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Hello")))
		]
		];
	UEditorUtilityWidget* euw;
	
	IMainFrameModule& MF = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
	
	if (MF.GetParentWindow().IsValid()) {
		FSlateApplication::Get().AddWindowAsNativeChild(cbw, MF.GetParentWindow().ToSharedRef());
		
	}
	else {
		FSlateApplication::Get().AddWindow(cbw);
	}
}

void FtestModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FtestCommands::Get().PluginAction);
}

void FtestModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FtestCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FtestModule, test)