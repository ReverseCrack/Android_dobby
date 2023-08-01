package cn.my.dobby_study;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'dobby_study' library on application startup.
    static {
        System.loadLibrary("test_for_hook");
    }

    private TextView showText;

    private final String TAG = "dobby_study";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        showText = findViewById(R.id.textBloardId);
    }

    public void call_native_function(View view) {
        String result = call_test_function();
        showText.setText(result);
    }

    public void dobby_load(View view) {
        Log.d(TAG,"加载动态库");
//        showText.setText(stringFromJNI());
//        Context context = MainActivity.this;
//        File dstSoFile = new File(context.getFilesDir(), "libinject.so");
//        System.load(dstSoFile.getPath());
    }

    /**
     * A native method that is implemented by the 'dobby_study' native library,
     * which is packaged with this application.
     */
    public native String call_test_function();
}