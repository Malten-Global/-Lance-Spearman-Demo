#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SpearmanHUD.generated.h"

UCLASS()
class LANCESPEARMAN_API ASpearmanHUD : public AHUD
{
 GENERATED_BODY()
public:
 virtual void DrawHUD() override;
};
