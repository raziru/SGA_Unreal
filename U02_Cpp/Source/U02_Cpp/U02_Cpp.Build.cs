// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U02_Cpp : ModuleRules
{
	public U02_Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
