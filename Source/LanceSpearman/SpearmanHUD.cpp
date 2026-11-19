#include "SpearmanHUD.h"
#include "SpearmanObjective.h"
#include "SpearmanGuard.h"
#include "Engine/Canvas.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void ASpearmanHUD::DrawHUD()
{
 Super::DrawHUD();
 if (!Canvas || !PlayerOwner) return;
 APawn* Player = PlayerOwner->GetPawn();
 if (!Player) return;

 DrawRect(FLinearColor(0.02f, 0.03f, 0.05f, 0.85f), 16.f, 16.f, 460.f, 176.f);
 DrawText(TEXT("NAIROBI - ARRIVAL AT THE MARKET"), FLinearColor::Yellow, 28.f, 26.f);
 DrawText(TEXT("R / controller Menu: Restart"), FLinearColor::White, 28.f, 110.f);
 DrawText(TEXT("P / controller View: Pause or resume"), FLinearColor::White, 28.f, 136.f);
 DrawText(TEXT("Left mouse / controller B: Punch"), FLinearColor::White, 28.f, 162.f);
 if (UGameplayStatics::IsGamePaused(this)) {
  DrawText(TEXT("MISSION PAUSED"), FLinearColor::Yellow, 28.f, 54.f);
  DrawText(TEXT("Resume here or restart the mission with R / Menu"), FLinearColor::White, 28.f, 82.f);
  return;
 }
 for (TActorIterator<ASpearmanObjective> It(GetWorld()); It; ++It)
 {
  const ASpearmanObjective* Objective = *It;
  if (Objective->IsComplete()) {
   DrawText(TEXT("Package extracted. Mission complete."), FLinearColor::Green, 28.f, 54.f);
   break;
  }
  int32 GuardsRemaining = 0;
  for (TActorIterator<ASpearmanGuard> Guard(GetWorld()); Guard; ++Guard)
   if (!Guard->IsDefeated()) ++GuardsRemaining;
  if (!Objective->HasPackage() && GuardsRemaining > 0) {
   DrawText(FString::Printf(TEXT("Defeat the market guards: %d remaining"), GuardsRemaining),
    FLinearColor::Yellow, 28.f, 54.f);
   DrawText(TEXT("Face a guard and punch at close range."), FLinearColor::White, 28.f, 82.f);
   break;
  }
  const FString Task = Objective->HasPackage()
   ? TEXT("Reach the extraction marker")
   : TEXT("Find the courier contact");
  DrawText(Task, FLinearColor::White, 28.f, 54.f);
  const float Distance = FVector::Dist(Player->GetActorLocation(), Objective->GetActorLocation());
  const FString Prompt = Objective->CanInteract(Player)
   ? TEXT("E / controller X: Interact")
   : Distance < 240.f
    ? TEXT("Move around the obstacle to interact")
    : FString::Printf(TEXT("Objective %.1f m away"), Distance / 100.f);
  DrawText(Prompt, FLinearColor::Yellow, 28.f, 82.f);
  break;
 }
}
