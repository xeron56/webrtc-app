# Chapter 7


Chapter 7: Testing and Debugging JNI Code

Testing and debugging are crucial aspects of software development, and JNI code is no exception. In this chapter, we'll explore various techniques and tools for testing and debugging JNI code effectively.

### Unit Testing JNI Code

Unit testing is an essential practice for ensuring the correctness and reliability of your code, and it's equally important for JNI code. While testing JNI code can be more challenging than testing pure Java or C++ code, there are several approaches you can take.

#### Testing C++ Code

For testing your C++ code that interacts with the JNI, you can use standard C++ unit testing frameworks like Google Test or Catch2. These frameworks allow you to write and run tests for your C++ functions and classes, independent of the Java code.

Here's an example of a simple test using Google Test:

```cpp
#include <gtest/gtest.h>

extern "C" JNIEXPORT jint JNICALL
Java_com_safeai_webrtcapp_MainActivity_calculateSum(JNIEnv *env, jobject /* this */, jint a, jint b) {
    return a + b;
}

TEST(NativeMethods, CalculateSum) {
    EXPECT_EQ(Java_com_safeai_webrtcapp_MainActivity_calculateSum(nullptr, nullptr, 2, 3), 5);
    EXPECT_EQ(Java_com_safeai_webrtcapp_MainActivity_calculateSum(nullptr, nullptr, -1, 10), 9);
}
```

In this example, we define a test case `CalculateSum` that tests the `calculateSum` native method with different input values and verifies the expected output using `EXPECT_EQ`.

To run the tests, you'll need to set up a separate test project or build target in your development environment and link against the Google Test library.

#### Testing Java Code Interacting with JNI

To test Java code that interacts with JNI, you can use standard Java unit testing frameworks like JUnit or Android Test. However, testing Java code that calls native methods can be challenging because you need to ensure that the native code behaves as expected.

One approach is to use mocking libraries like Mockito to mock the native method calls and verify the expected behavior based on the mocked return values or side effects.

Here's an example of a JUnit test using Mockito:

```java
import org.junit.Test;
import org.mockito.Mockito;

public class MainActivityTest {

    @Test
    public void testCalculateSum() {
        MainActivity activity = Mockito.mock(MainActivity.class);
        Mockito.when(activity.calculateSum(2, 3)).thenReturn(5);
        Mockito.when(activity.calculateSum(-1, 10)).thenReturn(9);

        int sum1 = activity.calculateSum(2, 3);
        int sum2 = activity.calculateSum(-1, 10);

        assertEquals(5, sum1);
        assertEquals(9, sum2);
    }
}
```

In this example, we create a mock instance of the `MainActivity` class using Mockito's `mock` method. We then define the expected behavior of the `calculateSum` native method using `when` and `thenReturn`. Finally, we call the `calculateSum` method on the mock instance and verify the expected output using JUnit's `assertEquals`.

While mocking can be a useful technique for testing Java code that interacts with JNI, it has limitations. For example, it may not accurately simulate the behavior of the native code, especially in cases where the native code interacts with external resources or has side effects.

#### Integration Testing

Another approach to testing JNI code is to perform integration testing, where you test the Java and C++ code together as a single unit. This can be done by writing test cases that exercise the JNI interface and verify the expected behavior of the combined Java and C++ code.

Integration testing can be more complex and time-consuming than unit testing, but it can provide a higher level of confidence in the correctness of your JNI code by testing the actual integration between Java and C++.

### Debugging JNI Code

Debugging JNI code can be challenging due to the complexity of interacting between Java and C++ code. However, there are several tools and techniques available to help you debug your JNI code effectively.

#### Android Studio Debugging

Android Studio provides built-in support for debugging both Java and C++ code, including JNI code. You can set breakpoints in your Java and C++ code, step through the execution, and inspect variables and data structures.

To debug JNI code in Android Studio, follow these steps:

1. Set breakpoints in your Java and C++ code where you want to pause execution.
2. Start the debugging session by clicking the "Debug" button in Android Studio.
3. When the breakpoint is hit, you can step through the code, inspect variables, and evaluate expressions in both Java and C++ code.

Android Studio also supports advanced debugging features like memory profiling and CPU profiling, which can be useful for diagnosing performance issues in your JNI code.

#### Logging and Print Statements

While not as powerful as a full-fledged debugger, logging and print statements can be valuable tools for debugging JNI code, especially in scenarios where using a debugger is not practical or possible (e.g., on production devices).

In Java code, you can use the standard `Log` class or third-party logging libraries like Timber to log messages and debug information.

In C++ code, you can use the `__android_log_print` function provided by the Android NDK to log messages to the Android logcat:

```cpp
#include <android/log.h>

#define LOG_TAG "NativeCode"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT jint JNICALL
Java_com_safeai_webrtcapp_MainActivity_calculateSum(JNIEnv *env, jobject /* this */, jint a, jint b) {
    LOGD("Calculating sum of %d and %d", a, b);
    int sum = a + b;
    LOGD("Sum: %d", sum);
    return sum;
}
```

In this example, we define a logging macro `LOGD` that uses `__android_log_print` to log debug messages with the tag "NativeCode". We then use this macro to log the input values and the calculated sum in the `calculateSum` native method.

You can view the logged messages in the Android logcat, which can be accessed through Android Studio or the `adb logcat` command.

#### Native Debugging Tools

In addition to the debugging tools provided by Android Studio, there are several other tools available for debugging native code, including JNI code.

One popular tool is `gdb`, the GNU Debugger, which can be used to debug C++ code, including code that interacts with the JNI. `gdb` provides powerful debugging features like breakpoints, watchpoints, and expression evaluation.

Another useful tool is `addr2line`, which can be used to map memory addresses to source code lines in C++ code. This can be particularly helpful when debugging crashes or memory corruption issues in JNI code.

Additionally, there are various profiling tools available for native code, such as `perf` (for CPU profiling), `valgrind` (for memory profiling), and `gperftools` (for CPU and heap profiling). These tools can help you identify performance bottlenecks and memory leaks in your JNI code.

### Testing and Debugging Best Practices

When testing and debugging JNI code, it's important to follow best practices to ensure the reliability and maintainability of your code. Here are some recommended best practices:

1. **Write Unit Tests**: Develop a comprehensive suite of unit tests for your JNI code, covering both the Java and C++ sides of the interface. Unit tests can help catch issues early in the development process and ensure that your code behaves as expected.

2. **Leverage Logging and Print Statements**: While not a substitute for a full-fledged debugger, logging and print statements can be invaluable for debugging JNI code, especially in scenarios where using a debugger is not practical or possible.

3. **Use Code Analysis Tools**: Utilize static code analysis tools like clang-tidy, cppcheck, or SonarQube to identify potential issues, code smells, and areas for improvement in your JNI code.

4. **Document Test Cases and Debugging Scenarios**: Maintain detailed documentation for your test cases and debugging scenarios, including the purpose, expected behavior, and any special considerations or prerequisites.

5. **Continuously Test and Debug**: Testing