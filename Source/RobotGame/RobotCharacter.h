#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RobotCharacter.generated.h"

class UCameraComponent;
class ARobotProjectile;

UCLASS()
class ROBOTGAME_API ARobotCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ARobotCharacter();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FirstPersonCamera;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);

    void Fire();

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<ARobotProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float MuzzleOffset;
};
