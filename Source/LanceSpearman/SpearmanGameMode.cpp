#include "SpearmanGameMode.h"
#include "SpearmanCharacter.h"
#include "SpearmanGuard.h"
#include "SpearmanObjective.h"
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerStart.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "UObject/ConstructorHelpers.h"
ASpearmanGameMode::ASpearmanGameMode(){DefaultPawnClass=ASpearmanCharacter::StaticClass();}
void ASpearmanGameMode::SpawnBlock(const FVector& Position,const FVector& Scale){
 AStaticMeshActor* A=GetWorld()->SpawnActor<AStaticMeshActor>(Position,FRotator::ZeroRotator);
 if(!A)return;
 UStaticMesh* Cube=LoadObject<UStaticMesh>(nullptr,TEXT("/Engine/BasicShapes/Cube.Cube"));
 if(Cube){A->GetStaticMeshComponent()->SetStaticMesh(Cube);A->SetActorScale3D(Scale);A->GetStaticMeshComponent()->SetMobility(EComponentMobility::Static);}
}
void ASpearmanGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage){
 Super::InitGame(MapName, Options, ErrorMessage);
 // Spawn a predictable playable start, rather than relying on the empty Entry map.\n GetWorld()->SpawnActor<APlayerStart>(FVector(-1700.f,-450.f,130.f),FRotator(0.f,0.f,0.f));\n // Engine cube is 100cm per axis. Large floor, roadside shops and market stalls.
 SpawnBlock(FVector(0,0,-70),FVector(42,42,1));
 for(int32 I=-3;I<=3;++I){
  if(I==0)continue;
  SpawnBlock(FVector(I*550.f,-1050.f,230.f),FVector(4,3,6));
  SpawnBlock(FVector(I*550.f,1050.f,230.f),FVector(4,3,6));
 }
 for(int32 I=0;I<9;++I){
  float X=-1500.f+I*370.f;
  SpawnBlock(FVector(X,300.f,50.f),FVector(2.1f,1.1f,1.f));
  SpawnBlock(FVector(X,300.f,150.f),FVector(.12f,.12f,2.f));
 }
 GetWorld()->SpawnActor<ASpearmanObjective>(FVector(-1000.f,300.f,140.f),FRotator::ZeroRotator);
 // Primitive patrol stand-ins; replace with skeletal-mesh AI after Windows build verification.
 GetWorld()->SpawnActor<ASpearmanGuard>(FVector(-450.f,-220.f,100.f),FRotator::ZeroRotator);
 GetWorld()->SpawnActor<ASpearmanGuard>(FVector(850.f,200.f,100.f),FRotator::ZeroRotator);
 if(GEngine)GEngine->AddOnScreenDebugMessage(-1,20.f,FColor::Yellow,TEXT("CHAPTER 1 / LEVEL 1: Arrival at the Market | Find the contact marker and press E | WASD move, Shift sprint"));
}