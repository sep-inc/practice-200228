// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "test.h"
#include "testStyle.h"
#include "testCommands.h"
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"
#include "Misc/MessageDialog.h"
#include "Editor/Blutility/Public/EditorUtilityLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"
#include "Editor/Blutility/Public/IBlutilityModule.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Runtime/Engine/Classes/Kismet/BlueprintFunctionLibrary.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"

//#include "park/StartEuwCPP.h"

#include "LevelEditor.h"

static const FName testTabName("test");

class UWidgetBlueprint;

#define LOCTEXT_NAMESPACE "FtestModule"

//FtestModule::FtestModule() {
//	static ConstructorHelpers::FObjectFinder<UWidgetBlueprint> buildingMesh(TEXT("EditorUtilityWidgetBlueprint'/Game/TestEUW.TestEUW'"));
//}

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
	//// Put your "OnButtonClicked" stuff here
	//FText DialogText = FText::Format(
	//						LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
	//						FText::FromString(TEXT("FtestModule::PluginButtonClicked()")),
	//						FText::FromString(TEXT("aaaaaaaaaaaatest.cpp"))
	//				   );
	//FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	
	
	//TSharedRef<SWidget> testwi = SNew();

	/*TSharedRef<SWindow> cbw = SNew(SWindow)
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
			.Text(FText::FromString(TEXT("Hello(^o^)/")))
		]
		];
	
	*/

	FString path = "EditorUtilityWidgetBlueprint'/Game/oifidf.oifidf'"; 
	UWidgetBlueprint* sc = TSoftObjectPtr<UWidgetBlueprint>(FSoftObjectPath(*path)).LoadSynchronous(); // ����UEditorUtilityWidgetBlueprint���󂯎�邱�Ƃ͏o���Ȃ����ۂ�

	//FString path = "Blueprint'/Game/StartEuw.StartEuw'"; // /Content �ȉ��̃p�X�� /Game �ȉ��̃p�X�ɒu�������A�R���e���g�u���E�U�[�Ŗ��O�� test �Ȃ� test.test_C ���w�肷��B
	//AStartEuwCPP* sc = TSoftObjectPtr<AStartEuwCPP>(FSoftObjectPath(*path)).LoadSynchronous(); // ��L�Őݒ肵���p�X�ɊY������N���X���擾
	
	/*if (sc) {
		sc->StartEUW();
	}*/
	//UEditorUtilityWidgetBlueprint* EUWB = FindObject<UEditorUtilityWidgetBlueprint>(ANY_PACKAGE,TEXT("EditorUtilityWidgetBlueprint'/Game/TestEUW.TestEUW'"),false);


	//if (sc) {
	//	UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(GetTransientPackage(),sc->GeneratedClass);
	//	Instance->ExecuteDefaultAction();
	//	printf("aaa");
	//	//UEditorUtilityWidget* CDO = EUWB->GeneratedClass->GetDefaultObject();
	//}
	//
	
	//�T�u�V�X�e���ŌĂяo���Ȃ��ƍċN�����ɉ����f��Ȃ��Ȃ�
	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	UEditorUtilityWidgetBlueprint* euwb = (UEditorUtilityWidgetBlueprint*)sc;
	EditorUtilitySubsystem->SpawnAndRegisterTab(euwb);



	//const UEditorUtilityWidget* CDO = (UEditorUtilityWidget*)sc->GeneratedClass->GetDefaultObject();
	//if (CDO->ShouldAutoRunDefaultAction())
	//{
	//	//���ؒ�
	//	//// Put your "OnButtonClicked" stuff here
	//	FText DialogText = FText::Format(
	//							LOCTEXT("PluginButtonDialogText", "Set AutoRunDefaultAction to false"),
	//							FText::FromString(TEXT("FtestModule::PluginButtonClicked()")),
	//							FText::FromString(TEXT("test.cpp"))
	//					   );
	//	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	//	//// ����
	//	//UEditorUtilityWidget* Instance = NewObject<UEditorUtilityWidget>(GetTransientPackage(),sc->GeneratedClass);
	//	//BP�̃C�x���g���Ă�
	//	////Instance->Run();
	//	//
	//	//Instance->BeginDestroy();
	//	////Destro
	//	//Instance->ExecuteDefaultAction();
	//}
	//else
	//{
	//	

	//	/*FName RegistrationName = FName(*(sc->GetPathName() + TEXT("_ActiveTab")));
	//	FText DisplayName = FText::FromString(sc->GetName());
	//	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	//	TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
	//	if (!LevelEditorTabManager->CanSpawnTab(RegistrationName))
	//	{
	//		LevelEditorTabManager->RegisterTabSpawner(RegistrationName, FOnSpawnTab::CreateStatic(&SpawnEditorUITab, sc))
	//			.SetDisplayName(DisplayName)
	//			.SetMenuType(ETabSpawnerMenuType::Hidden);
	//	}

	//	TSharedRef<SDockTab> NewDockTab = LevelEditorTabManager->InvokeTab(RegistrationName);*/
	//	////�����炭����Ȃ�
	//	//FName RegistrationName = FName(*(sc->GetPathName() + TEXT("_ActiveTab")));
	//	//FText DisplayName = FText::FromString(sc->GetName());
	//	//FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	//	//TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
	//	//TSharedRef<SDockTab> NewDockTab = LevelEditorTabManager->InvokeTab(RegistrationName);
	//}



	//if (BluePrintFile.Object) {
	//	//BP_Var = (UClass*)BluePrintFile.Object->GeneratedClass;
	//}
	
	//GetTransientPackage();
	



	/*IMainFrameModule& MF = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
	
	if (MF.GetParentWindow().IsValid()) {
		FSlateApplication::Get().AddWindowAsNativeChild(cbw, MF.GetParentWindow().ToSharedRef());

	}
	else {
		FSlateApplication::Get().AddWindow(cbw);
	}*/
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