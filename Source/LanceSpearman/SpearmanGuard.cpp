#include "SpearmanGuard.h"
#include "SpearmanCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
ASpearmanGuard::ASpearmanGuard(){
 PrimaryActorTick.bCanEverTick=true;
 Body=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GuardBody"));
 SetRootComponent(Body);
 static ConstructorHelpers::FObjectFinder<UStaticMesh> Shape(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
 if(Shape.Succeeded())Body->SetStaticMesh(Shape.Object);
 Body->SetRelativeScale3D(FVector(.45f,.45f,1.8f));
 Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ASpearmanGuard::BeginPlay(){Super::BeginPlay();Origin=GetActorLocation();}
void ASpearmanGuard::Tick(float Dt){
 Super::Tick(Dt);
 const FVector End=Origin+FVector(PatrolDistance,0,0);
 const FVector Goal=bGoingOut?End:Origin;
 const FVector Next=FMath::VInterpConstantTo(GetActorLocation(),Goal,Dt,WalkSpeed);
 SetActorLocation(Next);
 if(FVector::DistSquared2D(Next,Goal)<FMath::Square(15.f))bGoingOut=!bGoingOut;
 AlertCooldown=FMath::Max(0.f,AlertCooldown-Dt);
 ASpearmanCharacter* Player=Cast<ASpearmanCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
 if(!Player||AlertCooldown>0.f||FVector::Dist2D(Player->GetActorLocation(),GetActorLocation())>DetectionRadius)return;
 FHitResult Hit;
 const FVector Eye=GetActorLocation()+FVector(0,0,90);
 const FVector Target=Player->GetActorLocation()+FVector(0,0,60);
 FCollisionQueryParams Params(SCENE_QUERY_STAT(GuardVision),false,this);
 const bool Blocked=GetWorld()->LineTraceSingleByChannel(Hit,Eye,Target,ECC_Visibility,Params) && Hit.GetActor()!=Player;
 if(!Blocked){
  AlertCooldown=5.f;
  if(GEngine)GEngine->AddOnScreenDebugMessage(-1,4.f,FColor::Red,TEXT("GUARD ALERT: You were spotted! Keep your distance and use cover."));
 }
}