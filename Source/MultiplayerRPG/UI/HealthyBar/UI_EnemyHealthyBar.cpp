// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_EnemyHealthyBar.h"
#include <Components/ProgressBar.h>

void UUI_EnemyHealthyBar::SetHealthPercent(float InPercent)
{
	HealthyBar->SetPercent(InPercent);
}
