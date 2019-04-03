package keithwang.jnisignature;

import android.content.Context;

public class Jni {

    public static native String getSignatureKey(Context mContext);

    public static native boolean isSameKey(Context mContext);
}
