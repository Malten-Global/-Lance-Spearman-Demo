#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpearmanGuard.generated.h"
class UStaticMeshComponent;
UCLASS()
class LANCESPEARMAN_API ASpearmanGuard : public AActor {
 GENERATED_BODY()
public:
 ASpearmanGuard();
 virtual void BeginPlay() override;
 virtual void Tick(float DeltaSeconds) override;
protected:
 UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Body;
 UPROPERTY(EditAnywhere,Category="Patrol") float PatrolDistance=500.f;
 UPROPERTY(EditAnywhere,Category="Patrol") float WalkSpeed=120.f;
 UPROPERTY(EditAnywhere,Category="Detection") float DetectionRadius=420.f;
private:
 FVector Origin;
 bool bGoingOut=true;
 float AlertCooldown=0.f;
};