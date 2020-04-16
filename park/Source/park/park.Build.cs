// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class park : ModuleRules
{
	public park(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "DLCTest", "test", "MODToolbutton" });
     //   PrivateDependencyModuleNames.AddRange(
     //   new string[]
     //   {
     //       "CoreUObject",
     //       "Engine",
     //       "Slate",
     //       "SlateCore",
     //       //"UnrealEd",
     //       //"Blutility",
     //       "UMG",
     //       //"UMGEditor",
     //       "Json"
		   // // ... add private dependencies that you statically link with here ...
    	//}
     //   );
    }
}
