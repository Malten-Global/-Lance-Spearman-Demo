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
 Marker->SetWorldScale3D(FVector(.8f));Marker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ASpearmanObjective::Activate(ASpearmanCharacter* Player){
 if(bActivated||!IsValid(Player))return;
 if(FVector::Dist(GetActorLocation(),Player->GetActorLocation())>240.f)return;
 bActivated=true;
 if(GEngine)GEngine->AddOnScreenDebugMessage(-1,12.f,FColor::Green,TEXT("LEVEL 1 COMPLETE: Contact located. Courier conspiracy uncovered!"));
 Destroy();
}