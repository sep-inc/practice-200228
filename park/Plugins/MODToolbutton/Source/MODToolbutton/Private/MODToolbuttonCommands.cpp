// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MODToolbuttonCommands.h"

#define LOCTEXT_NAMESPACE "FMODToolbuttonModule"

void FMODToolbuttonCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MODToolbutton", "Execute MODToolbutton action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
