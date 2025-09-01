#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RobotProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ROBOTGAME_API ARobotProjectile : public AActor
{
    GENERATED_BODY()

public:
    ARobotProjectile();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
    USphereComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta=(AllowPrivateAccess="true"))
    UProjectileMovementComponent* ProjectileMovement;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
