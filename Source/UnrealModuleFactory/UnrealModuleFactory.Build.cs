// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealModuleFactory : ModuleRules
{
	public UnrealModuleFactory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate", 
			"StatusModule",
			"BulletCreator",
			"GameplayTags",
			"GameplayTasks",
			"GameplayAbilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"UnrealModuleFactory",
			"UnrealModuleFactory/Variant_Platforming",
			"UnrealModuleFactory/Variant_Platforming/Animation",
			"UnrealModuleFactory/Variant_Combat",
			"UnrealModuleFactory/Variant_Combat/AI",
			"UnrealModuleFactory/Variant_Combat/Animation",
			"UnrealModuleFactory/Variant_Combat/Gameplay",
			"UnrealModuleFactory/Variant_Combat/Interfaces",
			"UnrealModuleFactory/Variant_Combat/UI",
			"UnrealModuleFactory/Variant_SideScrolling",
			"UnrealModuleFactory/Variant_SideScrolling/AI",
			"UnrealModuleFactory/Variant_SideScrolling/Gameplay",
			"UnrealModuleFactory/Variant_SideScrolling/Interfaces",
			"UnrealModuleFactory/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
