#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpearmanCharacter.generated.h"
class USceneComponent;
class USpringArmComponent; class UCameraComponent;
UCLASS()
class LANCESPEARMAN_API ASpearmanCharacter : public ACharacter {
 GENERATED_BODY()
public:
 ASpearmanCharacter();
 virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
 void MoveForward(float Value); void MoveRight(float Value);
 void StartSprint(); void StopSprint(); void Interact();
 void RestartMission();
 virtual void Tick(float DeltaSeconds) override;
protected:
 UPROPERTY(VisibleAnywhere) USpringArmComponent* CameraBoom;
 UPROPERTY(VisibleAnywhere) UCameraComponent* FollowCamera;
private:
 UPROPERTY() USceneComponent* LeftHip;
 UPROPERTY() USceneComponent* RightHip;
 UPROPERTY() USceneComponent* LeftShoulder;
 UPROPERTY() USceneComponent* RightShoulder;
 float StridePhase = 0.f;
 float SwingDegrees = 0.f;
};