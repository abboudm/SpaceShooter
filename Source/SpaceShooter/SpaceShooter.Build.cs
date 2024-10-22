// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SpaceShooter : ModuleRules
{
	public SpaceShooter(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule","GameplayTasks"});

        //PublicIncludePaths.AddRange(new string[] { "DialogueSystem/Public", "DialogueSystem/Classes" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
