package keithwang.jnisignature;

import android.content.Context;

public class Jni {

    public static native String getSignatureKey(Context mContext);

    public static native boolean isSameKey(Context mContext);

    public static native String stringFromJNI();

    public static native String encode(Context mContext, String str);

    public static native String decode(Context mContext, String str);
}
