// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.entrypointinfrastructure;

import android.app.Activity;
import android.content.res.AssetManager;
import android.view.Surface;

public class NativeJniCalls
{
    public static native long createNativeCode(Activity activity, AssetManager assetManager, float dpi, int density, String versionName, int versionCode);
    public static native void destroyNativeCode();
    public static native void pauseNativeCode();
    public static native void resumeNativeCode();
    public static native void setNativeSurface(Surface surface);
    public static native void updateNativeCode(float deltaTimeSeconds);
    public static native void updateUiViewCode(float deltaTimeSeconds);
    public static native void stopUpdatingNativeCode();
    public static native void revealApplicationUi(long nativePointer);
    public static native void handleApplicationUiCreatedOnNativeThread(long nativePointer);
    public static native void destroyApplicationUi();
}
