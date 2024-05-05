# Chapter 2



Chapter 2: Writing C++ Code and Integrating with Java

Now that we have set up the Android Studio environment for JNI development with C++ and CMake, it's time to start writing some C++ code and integrate it with our Java code using the JNI.

### Writing C++ Code

In this section, we'll write a simple C++ function that performs some arithmetic operations and returns the result.

Open the `native-lib.cpp` file located in the `app/src/main/cpp/` directory and replace its content with the following code:

```cpp
#include <jni.h>

extern "C" JNIEXPORT jint JNICALL
Java_com_safeai_webrtcapp_MainActivity_calculateSum(JNIEnv *env, jobject /* this */, jint a, jint b) {
    return a + b;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_safeai_webrtcapp_MainActivity_calculateDifference(JNIEnv *env, jobject /* this */, jint a, jint b) {
    return a - b;
}
```

In this code, we have defined two C++ functions:

1. `calculateSum`: This function takes two integers (`a` and `b`) as arguments and returns their sum.
2. `calculateDifference`: This function takes two integers (`a` and `b`) as arguments and returns their difference.

Both functions are marked with the `extern "C"` specifier, which is required for C++ functions to be callable from other languages like Java.

The function names follow the JNI naming convention: `Java_com_safeai_webrtcapp_MainActivity_functionName`, where `com_safeai_webrtcapp_MainActivity` is the fully qualified name of the Java class containing the corresponding native method declarations.

### Declaring Native Methods in Java

Next, we need to declare the native methods in our Java code so that we can call them from our MainActivity.

Open the `MainActivity.java` file located in the `app/src/main/java/com/safeai/webrtcapp/` directory and add the following method declarations:

```java
public native int calculateSum(int a, int b);
public native int calculateDifference(int a, int b);
```

These method declarations should be placed inside the `MainActivity` class.

### Calling Native Methods from Java

Now, we can call our native methods from Java. Update the `onCreate` method in `MainActivity.java` with the following code:

```java
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    binding = ActivityMainBinding.inflate(getLayoutInflater());
    setContentView(binding.getRoot());

    // Call native methods
    int sum = calculateSum(10, 5);
    int difference = calculateDifference(10, 5);

    TextView tv = binding.sampleText;
    tv.setText("Sum: " + sum + ", Difference: " + difference);
}
```

In this code, we call the `calculateSum` and `calculateDifference` native methods with the arguments `10` and `5`, respectively. We then set the result to a `TextView` for display.

### Building and Running the Project

To build and run the project, follow these steps:

1. Connect an Android device to your development machine or start an Android emulator.

2. In Android Studio, click the "Make Project" button (usually a green hammer icon) to build the project.

3. If there are no errors, you can run the app on your connected device or emulator by clicking the "Run" button (usually a green play icon).

You should see the text "Sum: 15, Difference: 5" displayed in the `TextView`.

Congratulations! You have successfully written C++ code, integrated it with your Java code using the JNI, and called native methods from your Java code.

In the next chapter, we'll explore more advanced topics, such as passing complex data structures between Java and C++, and using third-party C++ libraries in your Android project.