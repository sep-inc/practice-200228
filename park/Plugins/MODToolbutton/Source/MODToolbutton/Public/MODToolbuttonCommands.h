// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MODToolbuttonStyle.h"

class FMODToolbuttonCommands : public TCommands<FMODToolbuttonCommands>
{
public:

	FMODToolbuttonCommands()
		: TCommands<FMODToolbuttonCommands>(TEXT("MODToolbutton"), NSLOCTEXT("Contexts", "MODToolbutton", "MODToolbutton Plugin"), NAME_None, FMODToolbuttonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
