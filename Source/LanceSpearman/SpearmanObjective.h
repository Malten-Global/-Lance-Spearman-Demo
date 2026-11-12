#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpearmanObjective.generated.h"
class UStaticMeshComponent; class ASpearmanCharacter;
UCLASS()
class LANCESPEARMAN_API ASpearmanObjective : public AActor {
 GENERATED_BODY()
public:
 ASpearmanObjective();
 bool HasPackage() const { return bActivated; }
 bool IsComplete() const { return bComplete; }
 void Activate(ASpearmanCharacter* Player);
protected:
 UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Marker;
 bool bActivated=false;
 bool bComplete=false;
};