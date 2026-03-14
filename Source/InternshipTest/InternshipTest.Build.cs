// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InternshipTest : ModuleRules
{
    public InternshipTest(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "HTTP",
            "Json",
            "JsonUtilities",
            "AIModule",
            "StateTreeModule",
            "GameplayStateTreeModule",
            "UMG",
            "Slate"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] {
            "InternshipTest/Public",
            "InternshipTest/Public/Features/JsonShooter",
            "InternshipTest",
            "InternshipTest/Variant_Horror",
            "InternshipTest/Variant_Horror/UI",
            "InternshipTest/Variant_Shooter",
            "InternshipTest/Variant_Shooter/AI",
            "InternshipTest/Variant_Shooter/UI",
            "InternshipTest/Variant_Shooter/Weapons"
        });

        PrivateIncludePaths.AddRange(new string[] {
            "InternshipTest/Private",
            "InternshipTest/Private/Features/JsonShooter"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}