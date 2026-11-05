// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class tp_8djv104_tp3 : ModuleRules
{
	public tp_8djv104_tp3(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"tp_8djv104_tp3",
			"tp_8djv104_tp3/Variant_Platforming",
			"tp_8djv104_tp3/Variant_Platforming/Animation",
			"tp_8djv104_tp3/Variant_Combat",
			"tp_8djv104_tp3/Variant_Combat/AI",
			"tp_8djv104_tp3/Variant_Combat/Animation",
			"tp_8djv104_tp3/Variant_Combat/Gameplay",
			"tp_8djv104_tp3/Variant_Combat/Interfaces",
			"tp_8djv104_tp3/Variant_Combat/UI",
			"tp_8djv104_tp3/Variant_SideScrolling",
			"tp_8djv104_tp3/Variant_SideScrolling/AI",
			"tp_8djv104_tp3/Variant_SideScrolling/Gameplay",
			"tp_8djv104_tp3/Variant_SideScrolling/Interfaces",
			"tp_8djv104_tp3/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
