package keithwang.jnisignature;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
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
                "\nkey check:" + Jni.isSameKey(this);
        tv.setText(str);
    }
}
