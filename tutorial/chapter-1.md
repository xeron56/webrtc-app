# Chapter 1



Chapter 1: Setting up the Android Studio Environment

In this chapter, we'll go through the steps to set up the Android Studio environment for JNI development with C++ and CMake.

### Prerequisites

Before we begin, make sure you have the following installed on your system:

1. **Android Studio**: The official IDE for Android app development. You can download it from the official Android Studio website: [https://developer.android.com/studio](https://developer.android.com/studio)

2. **Android NDK (Native Development Kit)**: The NDK is a toolset that allows you to build performance-critical portions of your app in native code (C and C++). Android Studio typically installs the NDK automatically, but you can also download it separately from the Android NDK website: [https://developer.android.com/ndk](https://developer.android.com/ndk)

3. **CMake**: CMake is an open-source, cross-platform family of tools designed to build, test, and package software. Android Studio includes CMake out-of-the-box, but you can also download it separately from the official CMake website: [https://cmake.org/download/](https://cmake.org/download/)

### Setting up a New Android Project

1. Open Android Studio and create a new project by selecting "Start a new Android Studio project" from the welcome screen or by going to "File > New > New Project" in the menu bar.

2. In the "New Project" wizard, select the appropriate options for your project, such as the project name, package name, programming language (Java or Kotlin), and minimum SDK level.

3. When prompted to select the project template, choose "Native C++" from the list of available templates.

4. Android Studio will automatically configure the project to include the necessary files and settings for JNI development with C++ and CMake.

### Project Structure

After creating the project, you should see the following important files and directories:

- `app/src/main/cpp/native-lib.cpp`: This file contains the C++ source code for your native library.
- `app/src/main/java/com/safeai/webrtcapp/MainActivity.java`: This file contains the Java source code for your MainActivity, including the JNI method declaration.
- `app/src/main/cpp/CMakeLists.txt`: This file is the CMake build script that defines how to build your native library.
- `app/build.gradle`: This file is the Gradle build script for your Android app project.

### Sample Code

Let's take a look at the sample code provided by Android Studio:

**MainActivity.java**

```java
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

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'webrtcapp' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
```

This code loads the `webrtcapp` native library when the application starts, sets the `ActivityMainBinding`, and calls the `stringFromJNI()` native method to set the text of a `TextView`.

**CMakeLists.txt**

```cmake
cmake_minimum_required(VERSION 3.22.1)
project("webrtcapp")

add_library(${CMAKE_PROJECT_NAME} SHARED
    # List C/C++ source files with relative paths to this CMakeLists.txt.
    native-lib.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
    # List libraries link to the target library
    android
    log)
```

This `CMakeLists.txt` file specifies the minimum required CMake version, sets the project name, adds the `native-lib.cpp` file to the library, and links the library with the Android and log libraries.

**native-lib.cpp**

```cpp
#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_safeai_webrtcapp_MainActivity_stringFromJNI(
    JNIEnv* env,
    jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
```

This `native-lib.cpp` file contains the implementation of the `stringFromJNI()` method, which returns a string "Hello from C++" to the Java layer.

### Building and Running the Project

To build and run the project, follow these steps:

1. Connect an Android device to your development machine or start an Android emulator.

2. In Android Studio, click the "Make Project" button (usually a green hammer icon) to build the project.

3. If there are no errors, you can run the app on your connected device or emulator by clicking the "Run" button (usually a green play icon).

Congratulations! You've successfully set up the Android Studio environment for JNI development with C++ and CMake. In the next chapter, we'll explore how to write more complex C++ code and integrate it with your Java code using the JNI.