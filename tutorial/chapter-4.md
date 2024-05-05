# Chapter 4



Chapter 4: Using Third-Party C++ Libraries in Android

In the previous chapters, we learned how to write C++ code and integrate it with Java code using the JNI. However, in many cases, you might want to use existing third-party C++ libraries in your Android app to take advantage of their functionality and save development time.

In this chapter, we'll explore how to use third-party C++ libraries in your Android project and integrate them with your Java code.

### Setting up a Third-Party C++ Library

For this example, we'll use the popular open-source library `rapidjson`, which is a fast JSON parser/generator for C++. You can download the library from the official GitHub repository: [https://github.com/Tencent/rapidjson](https://github.com/Tencent/rapidjson)

Once you have downloaded the library, follow these steps to set it up in your Android project:

1. Create a new directory called `rapidjson` inside the `app/src/main/cpp` directory.
2. Copy the contents of the `rapidjson` library into the `app/src/main/cpp/rapidjson` directory.

Now, we need to update the `CMakeLists.txt` file to include the `rapidjson` library in our project.

Open the `app/src/main/cpp/CMakeLists.txt` file and add the following lines:

```cmake
# Specify the path to the rapidjson library
set(RAPIDJSON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/rapidjson/include)

# Include the rapidjson library
include_directories(${RAPIDJSON_INCLUDE_DIR})
```

This will allow CMake to find the `rapidjson` library and include it in the build process.

### Using the Third-Party Library in C++ Code

Now that we have set up the `rapidjson` library, let's write some C++ code that uses it.

Open the `native-lib.cpp` file and add the following code:

```cpp
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_safeai_webrtcapp_MainActivity_createJsonString(JNIEnv *env, jobject /* this */) {
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Value nameValue("John Doe", document.GetAllocator());
    rapidjson::Value ageValue(30);

    document.AddMember("name", nameValue, document.GetAllocator());
    document.AddMember("age", ageValue, document.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return env->NewStringUTF(buffer.GetString());
}
```

In this code:

1. We include the necessary `rapidjson` headers.
2. We define a C++ function `createJsonString` that creates a JSON string representing a person with a name and age.
3. We use the `rapidjson` API to create a JSON document, add members to it, and serialize it to a string.
4. We return the JSON string as a Java `String` object using the `NewStringUTF` method.

### Calling the C++ Function from Java

Next, we need to declare the native method in Java and call it from our `MainActivity`.

Open the `MainActivity.java` file and add the following method declaration:

```java
public native String createJsonString();
```

Then, update the `onCreate` method to call the `createJsonString` method:

```java
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    binding = ActivityMainBinding.inflate(getLayoutInflater());
    setContentView(binding.getRoot());

    String jsonString = createJsonString();

    TextView tv = binding.sampleText;
    tv.setText(jsonString);
}
```

In this code, we call the `createJsonString` native method and display the resulting JSON string in a `TextView`.

### Building and Running the Project

To build and run the project with the code from Chapter 4, follow these steps:

1. Connect an Android device to your development machine or start an Android emulator.
2. In Android Studio, click the "Make Project" button (usually a green hammer icon) to build the project.
3. If there are no errors, you can run the app on your connected device or emulator by clicking the "Run" button (usually a green play icon).

You should see the following JSON string displayed in the `TextView`:

```
{"name":"John Doe","age":30}
```

Congratulations! You have successfully learned how to use third-party C++ libraries in your Android project and integrate them with your Java code using the JNI.

In the next chapter (if needed), we can explore more advanced topics related to JNI development, such as handling exceptions, working with multithreading, or optimizing performance.
