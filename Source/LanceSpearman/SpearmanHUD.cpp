#include "SpearmanHUD.h"
#include "SpearmanObjective.h"
#include "Engine/Canvas.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void ASpearmanHUD::DrawHUD()
{
 Super::DrawHUD();
 if (!Canvas || !PlayerOwner) return;
 APawn* Player = PlayerOwner->GetPawn();
 if (!Player) return;

 DrawRect(FLinearColor(0.02f, 0.03f, 0.05f, 0.85f), 16.f, 16.f, 420.f, 124.f);
 DrawText(TEXT("NAIROBI - ARRIVAL AT THE MARKET"), FLinearColor::Yellow, 28.f, 26.f);
 DrawText(TEXT("R / controller Menu: Restart"), FLinearColor::White, 28.f, 110.f);
 for (TActorIterator<ASpearmanObjective> It(GetWorld()); It; ++It)
 {
  const ASpearmanObjective* Objective = *It;
  if (Objective->IsComplete()) {
   DrawText(TEXT("Package extracted. Mission complete."), FLinearColor::Green, 28.f, 54.f);
   break;
  }
  const FString Task = Objective->HasPackage()
   ? TEXT("Reach the extraction marker")
   : TEXT("Find the courier contact");
  DrawText(Task, FLinearColor::White, 28.f, 54.f);
  const float Distance = FVector::Dist(Player->GetActorLocation(), Objective->GetActorLocation());
  const FString Prompt = Distance < 240.f
   ? TEXT("E / controller X: Interact")
   : FString::Printf(TEXT("Objective %.1f m away"), Distance / 100.f);
  DrawText(Prompt, FLinearColor::Yellow, 28.f, 82.f);
  break;
 }
}
