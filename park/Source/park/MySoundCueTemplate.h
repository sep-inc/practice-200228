// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCueTemplate.h"

#include "Misc/Attribute.h"
#include "Sound/SoundCueTemplate.h"
#include "UObject/ObjectMacros.h"

#if WITH_EDITOR
#include "IDetailCustomization.h"
#include "Layout/Visibility.h"
#include "PropertyHandle.h"
#endif // WITH_EDITOR

#include "MySoundCueTemplate.generated.h"

// ========================================================================
// UMySoundCueTemplate
// UMySoundCueTemplate which implements USoundCueTemplate.
//
// Simple example showing how to expose or hide template
// parameters in the editor such as the looping and soundwave
// fields of a USoundNodeWavePlayer.
//
// In order for proper data hiding to occur for inherited properties,
// Customization Detail's 'Register' must be called in during initialization
// (eg. in module's StartupModule()) like so:
// #include "MySoundCueTemplate.h"
// ...
//#if WITH_EDITOR
// FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
// FMySoundCueTemplateDetailCustomization::Register(PropertyModule);
//#endif // WITH_EDITOR
// ========================================================================


UCLASS(hidecategories = object, BlueprintType)
class PARK_API UMySoundCueTemplate : public USoundCueTemplate
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITORONLY_DATA
public:
	UPROPERTY(EditAnywhere, Category = "Waves")
	bool bLooping;

	UPROPERTY(EditAnywhere, Category = "Waves")
	USoundWave* SoundWave;
#endif // WITH_EDITORONLY_DATA

#if WITH_EDITOR
	/** Whitelisted categories, which allows hiding default
	  * categories from the editor on the inherited SoundCue
	  * as desired.
	  */
	static TSet<FName>& GetWhitelistedCategories();

	/** Overload with logic to rebuild the node graph when
	  * user-facing properties are changed
	  */
	virtual void OnRebuildGraph(USoundCue& SoundCue) const override;
#endif // WITH_EDITOR
};

#if WITH_EDITOR
class FMySoundCueTemplateDetailCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	static void Register(FPropertyEditorModule& PropertyModule);
	static void Unregister(FPropertyEditorModule& PropertyModule);
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;
};
#endif // WITH_EDITOR
