// Copyright Fireteam Interactive

using UnrealBuildTool;

public class Aura : ModuleRules
{
	public Aura(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayAbilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayTags",
			"GameplayTasks",
			"NavigationSystem",
			"Niagara"
		});

		PublicIncludePaths.AddRange(new string[]
		{
			"Aura/Public/AbilitySystem",
			"Aura/Public/AbilitySystem/ModMagCalc",
			"Aura/Public/Actor",
			"Aura/Public/Character",
			"Aura/Public/Game",
			"Aura/Public/Interaction",
			"Aura/Public/Player",
			"Aura/Public/UI",
			"Aura/Public/UI/HUD",
			"Aura/Public/UI/Widget",
			"Aura/Public/UI/WidgetController"
		});
	}
}