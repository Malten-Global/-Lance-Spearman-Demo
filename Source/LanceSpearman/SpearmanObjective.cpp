#include "SpearmanObjective.h"
#include "SpearmanCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
ASpearmanObjective::ASpearmanObjective(){
 PrimaryActorTick.bCanEverTick=false;
 Marker=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContactMarker"));RootComponent=Marker;
 static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
 if(Mesh.Succeeded())Marker->SetStaticMesh(Mesh.Object);
 Marker->SetMobility(EComponentMobility::Movable);
 Marker->SetWorldScale3D(FVector(.8f));Marker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
bool ASpearmanObjective::CanInteract(const AActor* Player) const
{
 if (bComplete || !IsValid(Player) || !GetWorld()) return false;
 if (FVector::DistSquared(GetActorLocation(), Player->GetActorLocation()) >= FMath::Square(240.f)) return false;

 // Trace from the character's upper body so a nearby wall or stall blocks pickup.
 FCollisionQueryParams Query(SCENE_QUERY_STAT(CourierInteraction), false, Player);
 Query.AddIgnoredActor(this);
 FHitResult Hit;
 const FVector Start = Player->GetActorLocation() + FVector(0.f, 0.f, 50.f);
 return !GetWorld()->LineTraceSingleByChannel(Hit, Start, GetActorLocation(), ECC_Visibility, Query);
}

void ASpearmanObjective::Activate(ASpearmanCharacter* Player){
 if (!CanInteract(Player)) return;
 if (!bActivated) {
  bActivated = true;
  SetActorLocation(FVector(1200.f, -550.f, 140.f));
  if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Yellow,
   TEXT("Package secured. Cross the market to the extraction marker and press E."));
  return;
 }
 if(GEngine)GEngine->AddOnScreenDebugMessage(-1,12.f,FColor::Green,TEXT("LEVEL 1 COMPLETE: Encrypted package extracted. Press R or controller Menu to replay."));
 bComplete = true;
 Marker->SetVisibility(false);
}