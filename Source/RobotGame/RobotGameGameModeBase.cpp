#include "RobotGameGameModeBase.h"
#include "RobotCharacter.h"

ARobotGameGameModeBase::ARobotGameGameModeBase()
{
    DefaultPawnClass = ARobotCharacter::StaticClass();
}

