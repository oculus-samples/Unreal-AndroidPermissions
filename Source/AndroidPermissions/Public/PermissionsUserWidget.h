/*
Copyright (c) Meta Platforms, Inc. and affiliates.
All rights reserved.

This source code is licensed under the license found in the
LICENSE file in the root directory of this source tree.
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PermissionsUserWidget.generated.h"

/**
 * A derived user widget to handle Android permissions.
 */
UCLASS()
class ANDROIDPERMISSIONS_API UPermissionsUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	// On construction, the permissions get checked to see if they are already enabled.
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Utility function to check on a specific permission.
	bool HasPermission(const FString& PermissionStr);

	// Utility function to request for a specific permission.
	void RequestPermission(const FString& PermissionStr);

	// Following BP functions are triggered by UMG button widgets.
	UFUNCTION(BlueprintCallable, Category = "BPPermissionsFuncs")
	void RequestMicPermission();

	UFUNCTION(BlueprintCallable, Category = "BPPermissionsFuncs")
	void RequestInternetPermission();

	UFUNCTION(BlueprintCallable, Category = "BPPermissionsFuncs")
	void RequestWriteExternalStoragePermission();

	UFUNCTION()
	void OnPermissionsGranted(const TArray<FString>& Permissions, const TArray<bool>& GrantResults);

public:
	// Permission states which get binded to UMG widgets.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPPermissionsStates")
	bool HasMicPermission;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPPermissionsStates")
	bool HasInternetPermission;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPPermissionsStates")
	bool HasWriteExternalStoragePermission;
};
