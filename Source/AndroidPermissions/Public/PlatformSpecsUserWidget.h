/*
Copyright (c) Meta Platforms, Inc. and affiliates.
All rights reserved.

This source code is licensed under the license found in the
LICENSE file in the root directory of this source tree.
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlatformSpecsUserWidget.generated.h"

/**
 * A derived user widget to handle the querying of platform specific states and specs.
 */
UCLASS()
class ANDROIDPERMISSIONS_API UPlatformSpecsUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// At every tick, we update the dynamic states.
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Following are BP functions to acquire platform specs.
	UFUNCTION(BlueprintCallable, Category = "BPPlatformSpecsFuncs")
	FString GetAndroidVersion();

	UFUNCTION(BlueprintCallable, Category = "BPPlatformSpecsFuncs")
	FString GetDeviceMake();

	UFUNCTION(BlueprintCallable, Category = "BPPlatformSpecsFuncs")
	FString GetDeviceModel();

	// Dynamic states that get checked every tick.  These are binded to UMG widgets.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPPlatformSpecsStates")
	bool BatteryIsCharging;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPPlatformSpecsStates")
	int32 BatteryLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPPlatformSpecsStates")
	float BatteryTemp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPPlatformSpecsStates")
	int32 CurVolume;
};
