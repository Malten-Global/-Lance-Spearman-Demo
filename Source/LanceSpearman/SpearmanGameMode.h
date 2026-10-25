#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpearmanGameMode.generated.h"
UCLASS()
class LANCESPEARMAN_API ASpearmanGameMode : public AGameModeBase {
 GENERATED_BODY()
public:
 ASpearmanGameMode();
 virtual void BeginPlay() override;
private:
 void SpawnBlock(const FVector& Position,const FVector& Scale);
};