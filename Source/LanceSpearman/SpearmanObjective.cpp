#include "SpearmanObjective.h"
#include "SpearmanCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
ASpearmanObjective::ASpearmanObjective(){
 PrimaryActorTick.bCanEverTick=false;
 Marker=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContactMarker"));RootComponent=Marker;
 static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
 if(Mesh.Succeeded())Marker->SetStaticMesh(Mesh.Object);
 Marker->SetMobility(EComponentMobility::Movable);
 Marker->SetWorldScale3D(FVector(.8f));Marker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ASpearmanObjective::Activate(ASpearmanCharacter* Player){
 if(!IsValid(Player))return;
 if(FVector::Dist(GetActorLocation(),Player->GetActorLocation())>240.f)return;
 if (!bActivated) {
  bActivated = true;
  SetActorLocation(FVector(1200.f, -550.f, 140.f));
  if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Yellow,
   TEXT("Package secured. Cross the market to the extraction marker and press E."));
  return;
 }
 if(GEngine)GEngine->AddOnScreenDebugMessage(-1,12.f,FColor::Green,TEXT("LEVEL 1 COMPLETE: Encrypted package extracted. Courier mission complete!"));
 Destroy();
}