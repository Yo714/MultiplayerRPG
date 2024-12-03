// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_EnemyHealthyBar.h"
#include <Components/ProgressBar.h>

// Sets the health percent on the enemy health bar
void UUI_EnemyHealthyBar::SetHealthPercent(float InPercent)
{
	// Update the progress bar with the provided health percentage
	HealthyBar->SetPercent(InPercent);
}
