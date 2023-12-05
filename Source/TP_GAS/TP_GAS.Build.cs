

using UnrealBuildTool;

public class TP_GAS : ModuleRules
{
	public TP_GAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {  });

		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayAbilities","GameplayTags","GameplayTasks" });

		
	}
}
