using UnrealBuildTool;
using System.Collections.Generic;

public class RobotGameTarget : TargetRules
{
    public RobotGameTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        CppStandard = CppStandardVersion.Cpp20;
        ExtraModuleNames.Add("RobotGame");
    }
}
