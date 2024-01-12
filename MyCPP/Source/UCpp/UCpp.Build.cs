// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UCpp : ModuleRules
{
	public UCpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "NavigationSystem", "AIModule", "GameplayTasks" });

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
