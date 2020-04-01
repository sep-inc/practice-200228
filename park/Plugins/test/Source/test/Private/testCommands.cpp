// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "testCommands.h"

#define LOCTEXT_NAMESPACE "FtestModule"

void FtestCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "test", "Execute test action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
