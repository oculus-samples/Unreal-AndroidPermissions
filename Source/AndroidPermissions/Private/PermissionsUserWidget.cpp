/*
Copyright (c) Meta Platforms, Inc. and affiliates.
All rights reserved.

This source code is licensed under the license found in the
LICENSE file in the root directory of this source tree.
*/
#include "PermissionsUserWidget.h"
#include "AndroidPermissionFunctionLibrary.h"
#include "AndroidPermissionCallbackProxy.h"
#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(AndroidPermissions, Log, All);
DEFINE_LOG_CATEGORY(AndroidPermissions);

void UPermissionsUserWidget::OnPermissionsGranted(const TArray<FString>& Permissions, const TArray<bool>& GrantResults)
{
#if PLATFORM_ANDROID
	if (GrantResults.Num() == 0)
	{
		UE_LOG(AndroidPermissions, Error, TEXT("No grant results were returned."));
		return;
	}
	// Technically, we don't need to loop through the returned permissions as we only request a unique permission at a time.
	// However, this demonstrates how one would handle multiple permission requests.
	for (int32 i = 0; i < Permissions.Num(); ++i)
	{
		UE_LOG(AndroidPermissions, Log, TEXT("In Permissions array %s has been granted: %s"), *Permissions[i], GrantResults[i] ? TEXT("true") : TEXT("false"))
		if (TEXT("android.permission.RECORD_AUDIO") == Permissions[i])
		{
			HasMicPermission = GrantResults[i];
		}
		else if (TEXT("android.permission.INTERNET") == Permissions[i])
		{
			HasInternetPermission = GrantResults[i];
		}
		else if (TEXT("android.permission.WRITE_EXTERNAL_STORAGE") == Permissions[i])
		{
			HasWriteExternalStoragePermission = GrantResults[i];
		}
	}
#endif
}

void UPermissionsUserWidget::NativeConstruct()
{
	// Check if we have the related permissions enabled.
	HasMicPermission = HasPermission(TEXT("android.permission.RECORD_AUDIO"));
	HasInternetPermission = HasPermission(TEXT("android.permission.INTERNET"));
	HasWriteExternalStoragePermission = HasPermission(TEXT("android.permission.WRITE_EXTERNAL_STORAGE"));
	UAndroidPermissionCallbackProxy::GetInstance()->OnPermissionsGrantedDynamicDelegate.AddDynamic(this, &UPermissionsUserWidget::OnPermissionsGranted);
}

void UPermissionsUserWidget::NativeDestruct()
{
	// Remove the dynamic delegate to prevent memory leaks.
	UAndroidPermissionCallbackProxy::GetInstance()->OnPermissionsGrantedDynamicDelegate.RemoveDynamic(this, &UPermissionsUserWidget::OnPermissionsGranted);
}

bool UPermissionsUserWidget::HasPermission(const FString& PermissionStr)
{
#if PLATFORM_ANDROID
	return UAndroidPermissionFunctionLibrary::CheckPermission(PermissionStr);
#else
	UE_LOG(AndroidPermissions, Warning, TEXT("Permissions are only available on Android."));
	return true;
#endif
}

void UPermissionsUserWidget::RequestPermission(const FString& PermissionStr)
{
#if PLATFORM_ANDROID
	UE_LOG(AndroidPermissions, Log, TEXT("Requesting permission: %s"), *PermissionStr);
	bool HasBeenGranted = HasPermission(PermissionStr);
	if (HasBeenGranted)
	{
		UE_LOG(AndroidPermissions, Log, TEXT("Permission already granted: %s"), *PermissionStr);
		return;
	}

	// As a demonstration, we only request for a unique permission at a time.
	TArray<FString> PermsToEnable;
	PermsToEnable.Add(PermissionStr);
	UAndroidPermissionFunctionLibrary::AcquirePermissions(PermsToEnable);
#endif
}

void UPermissionsUserWidget::RequestMicPermission()
{
	RequestPermission(TEXT("android.permission.RECORD_AUDIO"));
}

void UPermissionsUserWidget::RequestInternetPermission()
{
	RequestPermission(TEXT("android.permission.INTERNET"));
}

void UPermissionsUserWidget::RequestWriteExternalStoragePermission()
{
	RequestPermission(TEXT("android.permission.WRITE_EXTERNAL_STORAGE"));
}
