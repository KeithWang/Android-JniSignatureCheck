package keithwang.jnisignature;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {


    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.show_text);
        String str = "Key:" + Jni.getSignatureKey(this) +
                "\nkey check:" + Jni.isSameKey(this) +
                "\nGet Key" + Jni.stringFromJNI();
        tv.setText(str);
        String code = "1234567890";
        code = Jni.encode(this, code);
        Log.d("JniTest Encoed:", code);
        Log.d("JniTest Decoed:", Jni.decode(this, code));
    }
}
