#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpearmanCharacter.generated.h"
class USpringArmComponent; class UCameraComponent;
UCLASS()
class LANCESPEARMAN_API ASpearmanCharacter : public ACharacter {
 GENERATED_BODY()
public:
 ASpearmanCharacter();
 virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
 void MoveForward(float Value); void MoveRight(float Value);
 void StartSprint(); void StopSprint(); void Interact();
protected:
 UPROPERTY(VisibleAnywhere) USpringArmComponent* CameraBoom;
 UPROPERTY(VisibleAnywhere) UCameraComponent* FollowCamera;
};