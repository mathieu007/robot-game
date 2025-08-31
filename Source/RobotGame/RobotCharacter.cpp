#include "RobotCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RobotProjectile.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"

ARobotCharacter::ARobotCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Create a CameraComponent
    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
    FirstPersonCamera->bUsePawnControlRotation = true; // Rotate the camera with controller

    // Character turns with controller input
    bUseControllerRotationYaw = true;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    // Let movement orient rotation to movement disabled for FPS
    GetCharacterMovement()->bOrientRotationToMovement = false;

    // Combat defaults
    MuzzleOffset = 120.f;
}

void ARobotCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ARobotCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ARobotCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &ARobotCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ARobotCharacter::LookUp);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARobotCharacter::Fire);
}

void ARobotCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ARobotCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void ARobotCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ARobotCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void ARobotCharacter::Fire()
{
    if (!Controller) return;

    const FRotator SpawnRotation = Controller->GetControlRotation();
    const FVector SpawnLocation = FirstPersonCamera
        ? FirstPersonCamera->GetComponentLocation() + SpawnRotation.Vector() * MuzzleOffset
        : GetActorLocation() + SpawnRotation.Vector() * (MuzzleOffset + 50.f);

    UWorld* World = GetWorld();
    if (World)
    {
        FActorSpawnParameters Params;
        Params.Owner = this;
        Params.Instigator = this;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        TSubclassOf<ARobotProjectile> ClassToSpawn = ProjectileClass ? ProjectileClass : ARobotProjectile::StaticClass();
        World->SpawnActor<ARobotProjectile>(ClassToSpawn, SpawnLocation, SpawnRotation, Params);
    }
}
