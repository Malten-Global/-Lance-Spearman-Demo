#include "SpearmanCharacter.h"
#include "SpearmanObjective.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
ASpearmanCharacter::ASpearmanCharacter() {
 PrimaryActorTick.bCanEverTick = true;
 // A jointed stand-in makes the playable silhouette visible using packaged engine content.
 static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
 auto AddPart = [&](FName Name, USceneComponent* Parent, FVector Position, FVector Scale)
 {
  auto* Part = CreateDefaultSubobject<UStaticMeshComponent>(Name);
  Part->SetupAttachment(Parent);
  Part->SetRelativeLocation(Position);
  Part->SetRelativeScale3D(Scale);
  Part->SetStaticMesh(Sphere.Object);
  Part->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  Part->SetGenerateOverlapEvents(false);
  Part->SetCanEverAffectNavigation(false);
 };
 auto AddJoint = [&](FName Name, FVector Position)
 {
  auto* Joint = CreateDefaultSubobject<USceneComponent>(Name);
  Joint->SetupAttachment(RootComponent);
  Joint->SetRelativeLocation(Position);
  return Joint;
 };
 AddPart(TEXT("Jacket"), RootComponent, FVector(0,0,15), FVector(.32,.47,.67));
 AddPart(TEXT("Head"), RootComponent, FVector(0,0,61), FVector(.22,.22,.29));
 AddPart(TEXT("HatBrim"), RootComponent, FVector(2,0,71), FVector(.32,.31,.04));
 AddPart(TEXT("HatCrown"), RootComponent, FVector(0,0,75), FVector(.23,.23,.12));
 LeftHip = AddJoint(TEXT("LeftHip"), FVector(0,-11,-13));
 RightHip = AddJoint(TEXT("RightHip"), FVector(0,11,-13));
 LeftShoulder = AddJoint(TEXT("LeftShoulder"), FVector(0,-24,36));
 RightShoulder = AddJoint(TEXT("RightShoulder"), FVector(0,24,36));
 AddPart(TEXT("LeftLeg"), LeftHip, FVector(0,0,-35), FVector(.17,.18,.72));
 AddPart(TEXT("RightLeg"), RightHip, FVector(0,0,-35), FVector(.17,.18,.72));
 AddPart(TEXT("LeftArm"), LeftShoulder, FVector(0,0,-25), FVector(.14,.14,.54));
 AddPart(TEXT("RightArm"), RightShoulder, FVector(0,0,-25), FVector(.14,.14,.54));
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
 Input->BindAction("RestartMission", IE_Pressed, this, &ASpearmanCharacter::RestartMission);
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
void ASpearmanCharacter::RestartMission()
{
 // Reload the configured game map so the contact, guards and player start reset together.
 UGameplayStatics::OpenLevel(this, FName(TEXT("/Engine/Maps/Entry")));
}

void ASpearmanCharacter::Tick(float DeltaSeconds)
{
 Super::Tick(DeltaSeconds);
 const float GroundSpeed = GetCharacterMovement()->IsMovingOnGround() ? GetVelocity().Size2D() : 0.f;
 StridePhase = FMath::Fmod(StridePhase + GroundSpeed * DeltaSeconds * .03f, 2.f * PI);
 const float DesiredSwing = 32.f * FMath::Clamp(GroundSpeed / 650.f, 0.f, 1.f);
 SwingDegrees = FMath::FInterpTo(SwingDegrees, DesiredSwing, DeltaSeconds, 10.f);
 const float Pitch = FMath::Sin(StridePhase) * SwingDegrees;
 LeftHip->SetRelativeRotation(FRotator(Pitch, 0, 0));
 RightHip->SetRelativeRotation(FRotator(-Pitch, 0, 0));
 LeftShoulder->SetRelativeRotation(FRotator(-Pitch, 0, 0));
 RightShoulder->SetRelativeRotation(FRotator(Pitch, 0, 0));
}
