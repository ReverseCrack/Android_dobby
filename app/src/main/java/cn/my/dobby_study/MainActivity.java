package cn.my.dobby_study;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.io.File;

import cn.my.dobby_study.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'dobby_study' library on application startup.
    static {
        System.loadLibrary("test_for_hook");
    }

    private TextView showText;

    private final String TAG = "loadsofile";

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        showText = findViewById(R.id.textBloardId);
//        Context context = MainActivity.this;
//        File dstSoFile = new File(context.getFilesDir(), "libinject.so");
//        Log.d(TAG,"dstSoFile ---------> "+dstSoFile.getPath());

//        Context context = MainActivity.this;
//        File dstSoFile = new File(context.getFilesDir(), "libinject.so");
//        System.load(dstSoFile.getPath());
    }

    public void call_native_function(View view) {
        String result = call_test_function();
        showText.setText(result);
    }

    public void call_native_function2(View view) {
//        showText.setText(stringFromJNI());
    }

    public void dobby_load(View view) {
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
//    public native String stringFromJNI();
}