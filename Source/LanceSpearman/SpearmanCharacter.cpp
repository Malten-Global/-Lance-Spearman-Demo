#include "SpearmanCharacter.h"
#include "SpearmanObjective.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "EngineUtils.h"
ASpearmanCharacter::ASpearmanCharacter() {
 PrimaryActorTick.bCanEverTick=false;
 CameraBoom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
 CameraBoom->SetupAttachment(RootComponent); CameraBoom->TargetArmLength=420.f;
 CameraBoom->bUsePawnControlRotation=true;
 FollowCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
 FollowCamera->SetupAttachment(CameraBoom); FollowCamera->bUsePawnControlRotation=false;
 bUseControllerRotationYaw=false; GetCharacterMovement()->bOrientRotationToMovement=true;
 GetCharacterMovement()->RotationRate=FRotator(0,540,0);
 GetCharacterMovement()->MaxWalkSpeed=350.f;
}
void ASpearmanCharacter::SetupPlayerInputComponent(UInputComponent* Input) {
 Super::SetupPlayerInputComponent(Input);
 Input->BindAxis("MoveForward",this,&ASpearmanCharacter::MoveForward);
 Input->BindAxis("MoveRight",this,&ASpearmanCharacter::MoveRight);
 Input->BindAxis("Turn",this,&APawn::AddControllerYawInput);
 Input->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
 Input->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
 Input->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);
 Input->BindAction("Sprint",IE_Pressed,this,&ASpearmanCharacter::StartSprint);
 Input->BindAction("Sprint",IE_Released,this,&ASpearmanCharacter::StopSprint);
 Input->BindAction("Interact",IE_Pressed,this,&ASpearmanCharacter::Interact);
}
void ASpearmanCharacter::MoveForward(float Value) { if(Controller&&Value!=0) AddMovementInput(FRotationMatrix(FRotator(0,Controller->GetControlRotation().Yaw,0)).GetUnitAxis(EAxis::X),Value); }
void ASpearmanCharacter::MoveRight(float Value) { if(Controller&&Value!=0) AddMovementInput(FRotationMatrix(FRotator(0,Controller->GetControlRotation().Yaw,0)).GetUnitAxis(EAxis::Y),Value); }
void ASpearmanCharacter::StartSprint(){GetCharacterMovement()->MaxWalkSpeed=650.f;}
void ASpearmanCharacter::StopSprint(){GetCharacterMovement()->MaxWalkSpeed=350.f;}
void ASpearmanCharacter::Interact(){
 ASpearmanObjective* Closest=nullptr;float Best=240.f;
 for(TActorIterator<ASpearmanObjective> It(GetWorld());It;++It){float D=FVector::Dist(GetActorLocation(),It->GetActorLocation());if(D<Best){Best=D;Closest=*It;}}
 if(Closest)Closest->Activate(this);
}