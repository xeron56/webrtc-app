package com.safeai.webrtcapp;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import com.safeai.webrtcapp.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'webrtcapp' library on application startup.
    static {
        System.loadLibrary("webrtcapp");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Call native methods
        int sum = calculateSum(10, 5);
        int difference = calculateDifference(10, 5);

        int array[] = {1, 2, 3, 4, 5};
        int arrysum = CalculateArrySum(array);

        String originalString = "Hello from Java";
        String reversedString = ReversesString(originalString);

        TextView tv = binding.sampleText;
        tv.setText("Sum: " + sum + ", Difference: " + difference + ", Array Sum: " + arrysum + ", Reversed String: " + reversedString);
    }

    /**
     * Native methods declared here
     */
    public native int calculateSum(int a, int b);
    public native int calculateDifference(int a, int b);

    public native int CalculateArrySum (int[] array);

    public native String ReversesString(String input);

    public native  Person swapPersonAttributes(Person person);
}