// Fill out your copyright notice in the Description page of Project Settings.


#include "MySoundCueTemplate.h"


#include "Sound/SoundCue.h"
#include "Sound/SoundCueTemplate.h"
#include "Sound/SoundWave.h"
#include "Sound/SoundNode.h"
#include "Sound/SoundNodeModulator.h"
#include "Sound/SoundNodeWavePlayer.h"

#if WITH_EDITOR
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "Sound/AudioSettings.h"
#include "SoundCueGraph/SoundCueGraphNode.h"
#include "SoundCueGraph/SoundCueGraph.h"
#include "SoundCueGraph/SoundCueGraphNode_Root.h"
#include "SoundCueGraph/SoundCueGraphSchema.h"
#endif // WITH_EDITOR


#define LOCTEXT_NAMESPACE "MySoundCueTemplate"
UMySoundCueTemplate::UMySoundCueTemplate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
// Add editor data initialization here
	bLooping = true;
#endif WITH_EDITOR
}

#if WITH_EDITOR
void UMySoundCueTemplate::OnRebuildGraph(USoundCue& SoundCue) const
{
	const UAudioSettings* AudioSettings = GetDefault<UAudioSettings>();
	if (!AudioSettings)
	{
		return;
	}

	if (!SoundWave)
	{
		return;
	}

	// Add modulator node as first node. Hardcoded values as an example of adding functionality
	// that is hidden from editor/UI.
	USoundNodeModulator& ModulatorNode = ConstructSoundNodeRoot<USoundNodeModulator>(SoundCue);
	ModulatorNode.PitchMin  = 0.80f;
	ModulatorNode.PitchMax  = 1.10f;
	ModulatorNode.VolumeMin = 0.75f;
	ModulatorNode.VolumeMax = 1.00f;

	// ConstructSoundNodeChild (and SetSoundNodePosition) takes a Row and Column, expected to be tracked and
	// updated here as you construct the graph to allow for visually friendly auto-generated SoundCues.
	// Converting to a SoundCue in editor (in context menu of generate SoundCueTemplate instances) is a great
	// way to debug your generated graph.
	int32 Column = 1; // 1 as root is '0', which was added above.
	int32 Row = 0;

	// Add more nodes/branches here to allow for additional functionality between leaf wave players and root modulator.
	// Common practice is to increment generation and increment or reset sibling index depending on branching/looping
	// as you go.

	const int32 InputPinIndex = 0;
	USoundNodeWavePlayer& WavePlayerNode = ConstructSoundNodeChild<USoundNodeWavePlayer>(SoundCue, &ModulatorNode, Column, Row, InputPinIndex);
	WavePlayerNode.SetSoundWave(SoundWave);
	WavePlayerNode.bLooping = bLooping;
}

TSet<FName>& UMySoundCueTemplate::GetWhitelistedCategories()
{
	static TSet<FName> Categories;
	if (Categories.Num() == 0)
	{
		// Add exposed categories here that you'd like to show
		// up in the editor (should match category names properties
		// are assigned to in the header, otherwise the properties
		// will be hidden by default).  If you would like to expose
		// default property categories inherited by USoundCue,
		// add them here as well.
		Categories.Add(FName(TEXT("Waves")));
	}

	return Categories;
}


TSharedRef<IDetailCustomization> FMySoundCueTemplateDetailCustomization::MakeInstance()
{
	return MakeShareable(new FMySoundCueTemplateDetailCustomization);
}

void FMySoundCueTemplateDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	TArray<FName> CategoryNames;
	DetailLayout.GetCategoryNames(CategoryNames);

	const TSet<FName>& Whitelist = UMySoundCueTemplate::GetWhitelistedCategories();
	for (FName CategoryName : CategoryNames)
	{
		if (!Whitelist.Contains(CategoryName))
		{
			DetailLayout.HideCategory(CategoryName);
		}
	}
}

void FMySoundCueTemplateDetailCustomization::Register(FPropertyEditorModule& PropertyModule)
{
	PropertyModule.RegisterCustomClassLayout("MySoundCueTemplate", FOnGetDetailCustomizationInstance::CreateStatic(&FMySoundCueTemplateDetailCustomization::MakeInstance));
}

void FMySoundCueTemplateDetailCustomization::Unregister(FPropertyEditorModule& PropertyModule)
{
	PropertyModule.UnregisterCustomClassLayout("MySoundCueTemplate");
}

#endif // WITH_EDITOR
#undef LOCTEXT_NAMESPACE
