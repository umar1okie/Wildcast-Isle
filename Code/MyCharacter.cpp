#include "MyCharacter.h"
#include "Blueprint/UserWidget.h"

AMyCharacter::AMyCharacter()
{
    
    CurrentXP = 0.0f;
    RequiredXP = 100.0f;
    CurrentLevel = 1;

    MaxHealth = 100.0f;
    CurrentHealth = MaxHealth;

    HungerCap = 100.0f;
    ThirstCap = 100.0f;

    bIsLevelUp = false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

  
    if (HealthWidgetClass)
    {
        HealthWidget = CreateWidget<UUserWidget>(GetWorld(), HealthWidgetClass);
        if (HealthWidget)
        {
            HealthWidget->AddToViewport();
        }
    }
}

void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ThirstCap = FMath::Clamp(ThirstCap - DeltaTime * 0.1f, 0.0f, 100.0f);
    HungerCap = FMath::Clamp(HungerCap - DeltaTime * 0.1f, 0.0f, 100.0f);

    UpdateThirstBar();
    UpdateHungerBar();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::LevelUp()
{
    CurrentLevel++;
    CurrentXP = 0.0f;
    RequiredXP *= 1.5f;

    bIsLevelUp = true;

    CurrentHealth = MaxHealth;
    UE_LOG(LogTemp, Warning, TEXT("Level Up! Current Level: %d"), CurrentLevel);
}


void AMyCharacter::UpdateHungerBar()
{
    if (HungerCap <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character is starving!"));
    }
}

void AMyCharacter::UpdateThirstBar()
{
    if (ThirstCap <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character is dehydrated!"));
    }
}
