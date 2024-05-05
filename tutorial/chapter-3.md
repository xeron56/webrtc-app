# Chapter 3

Sure, let's move on to Chapter 3.

Chapter 3: Passing Complex Data Structures between Java and C++

In the previous chapter, we learned how to call native C++ methods from Java and pass primitive data types like integers as arguments. However, in real-world scenarios, you often need to work with more complex data structures, such as arrays, strings, and custom objects. In this chapter, we'll explore how to pass complex data structures between Java and C++ using the JNI.

### Passing Arrays

Let's start by learning how to pass arrays between Java and C++. We'll write a C++ function that takes an array of integers as input, calculates the sum of its elements, and returns the result.

#### C++ Code

Open the `native-lib.cpp` file and add the following function:

```cpp
extern "C" JNIEXPORT jint JNICALL
Java_com_safeai_webrtcapp_MainActivity_calculateArraySum(JNIEnv *env, jobject /* this */, jintArray array) {
    jint *elements = env->GetIntArrayElements(array, nullptr);
    jint length = env->GetArrayLength(array);
    jint sum = 0;

    for (int i = 0; i < length; i++) {
        sum += elements[i];
    }

    env->ReleaseIntArrayElements(array, elements, JNI_ABORT);
    return sum;
}
```

In this function:

1. We use the `GetIntArrayElements` method to get a pointer to the array elements.
2. We use the `GetArrayLength` method to get the length of the array.
3. We iterate over the array elements and calculate their sum.
4. We use the `ReleaseIntArrayElements` method to release the array elements and commit any changes (if needed).
5. We return the calculated sum.

#### Java Code

Next, we need to declare the native method in Java and call it from our `MainActivity`.

Open the `MainActivity.java` file and add the following method declaration:

```java
public native int calculateArraySum(int[] array);
```

Then, update the `onCreate` method to call the `calculateArraySum` method:

```java
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    binding = ActivityMainBinding.inflate(getLayoutInflater());
    setContentView(binding.getRoot());

    int[] myArray = {1, 2, 3, 4, 5};
    int arraySum = calculateArraySum(myArray);

    TextView tv = binding.sampleText;
    tv.setText("Array sum: " + arraySum);
}
```

In this code, we create an integer array `myArray`, pass it to the `calculateArraySum` native method, and display the result in a `TextView`.

### Passing Strings

Next, let's learn how to pass strings between Java and C++. We'll write a C++ function that takes a string as input and returns a new string with the characters reversed.

#### C++ Code

Open the `native-lib.cpp` file and add the following function:

```cpp
extern "C" JNIEXPORT jstring JNICALL
Java_com_safeai_webrtcapp_MainActivity_reverseString(JNIEnv *env, jobject /* this */, jstring input) {
    const char *inputChars = env->GetStringUTFChars(input, nullptr);
    std::string inputStr(inputChars);
    std::reverse(inputStr.begin(), inputStr.end());
    env->ReleaseStringUTFChars(input, inputChars);

    return env->NewStringUTF(inputStr.c_str());
}
```

In this function:

1. We use the `GetStringUTFChars` method to get a C-style string from the Java `String` object.
2. We create a `std::string` from the C-style string.
3. We use the `std::reverse` function from the C++ Standard Library to reverse the string.
4. We use the `ReleaseStringUTFChars` method to release the C-style string.
5. We create a new Java `String` object from the reversed C++ string and return it.

#### Java Code

Next, we need to declare the native method in Java and call it from our `MainActivity`.

Open the `MainActivity.java` file and add the following method declaration:

```java
public native String reverseString(String input);
```

Then, update the `onCreate` method to call the `reverseString` method:

```java
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    binding = ActivityMainBinding.inflate(getLayoutInflater());
    setContentView(binding.getRoot());

    String originalString = "Hello, World!";
    String reversedString = reverseString(originalString);

    TextView tv = binding.sampleText;
    tv.setText("Original: " + originalString + "\nReversed: " + reversedString);
}
```

In this code, we create a `String` object `originalString`, pass it to the `reverseString` native method, and display the original and reversed strings in a `TextView`.

### Passing Custom Objects

Finally, let's learn how to pass custom objects between Java and C++. We'll create a simple `Person` class in Java and a corresponding C++ struct. We'll then write a C++ function that takes a `Person` object as input and returns a new `Person` object with the name and age swapped.

#### Java Code

First, create a new Java class called `Person` in the same package as your `MainActivity`:

```java
package com.safeai.webrtcapp;

public class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }
}
```

This class represents a person with a name and age.

Next, open the `MainActivity.java` file and add the following method declaration:

```java
public native Person swapPersonAttributes(Person person);
```

Then, update the `onCreate` method to call the `swapPersonAttributes` method:

```java
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    binding = ActivityMainBinding.inflate(getLayoutInflater());
    setContentView(binding.getRoot());

    Person originalPerson = new Person("John Doe", 30);
    Person swappedPerson = swapPersonAttributes(originalPerson);

    TextView tv = binding.sampleText;
    tv.setText("Original: " + originalPerson.getName() + ", " + originalPerson.getAge() +
               "\nSwapped: " + swappedPerson.getName() + ", " + swappedPerson.getAge());
}
```

In this code, we create a `Person` object `originalPerson`, pass it to the `swapPersonAttributes` native method, and display the original and swapped `Person` objects in a `TextView`.

#### C++ Code

Now, let's implement the `swapPersonAttributes` function in C++.

Open the `native-lib.cpp` file and add the following code:



```cpp
#include <string>

// C++ struct to represent the Person class
struct Person {
    std::string name;
    int age;
};

extern "C" JNIEXPORT jobject JNICALL
Java_com_safeai_webrtcapp_MainActivity_swapPersonAttributes(JNIEnv *env, jobject /* this */, jobject person) {
    // Get the Person class and its fields
    jclass personClass = env->GetObjectClass(person);
    jfieldID nameField = env->GetFieldID(personClass, "name", "Ljava/lang/String;");
    jfieldID ageField = env->GetFieldID(personClass, "age", "I");

    // Get the name and age from the Person object
    jstring nameJString = (jstring) env->GetObjectField(person, nameField);
    const char *nameChars = env->GetStringUTFChars(nameJString, nullptr);
    std::string name(nameChars);
    env->ReleaseStringUTFChars(nameJString, nameChars);
    jint age = env->GetIntField(person, ageField);

    // Swap the name and age
    Person swappedPerson = {std::to_string(age), static_cast<int>(name.length())};

    // Create a new Person object with the swapped attributes
    jmethodID constructor = env->GetMethodID(personClass, "<init>", "(Ljava/lang/String;I)V");
    jstring swappedNameJString = env->NewStringUTF(swappedPerson.name.c_str());
    jobject swappedPersonObject = env->NewObject(personClass, constructor, swappedNameJString, swappedPerson.age);

    return swappedPersonObject;
}
```

Here's what the code does:

1. We define a `Person` struct in C++ to represent the `Person` class in Java.
2. We get the `Person` class and its `name` and `age` fields using the `GetObjectClass` and `GetFieldID` methods.
3. We retrieve the `name` and `age` values from the Java `Person` object using the `GetObjectField` and `GetIntField` methods.
4. We create a new `Person` struct `swappedPerson` with the `name` and `age` swapped (the name becomes the age as a string, and the age becomes the length of the original name).
5. We get the constructor of the `Person` class using the `GetMethodID` method.
6. We create a new Java `String` object from the swapped name using `NewStringUTF`.
7. We create a new Java `Person` object using the constructor and the swapped name and age values.
8. We return the new `Person` object with the swapped attributes.

With this implementation, you can now pass custom objects between Java and C++ using the JNI.

### Building and Running the Project

To build and run the project with the code from Chapter 3, follow these steps:

1. Connect an Android device to your development machine or start an Android emulator.
2. In Android Studio, click the "Make Project" button (usually a green hammer icon) to build the project.
3. If there are no errors, you can run the app on your connected device or emulator by clicking the "Run" button (usually a green play icon).

You should see the following output in the `TextView`:

```
Array sum: 15
Original: Hello, World!
Reversed: !dlroW ,olleH
Original: John Doe, 30
Swapped: 30, 8
```

Congratulations! You have successfully learned how to pass complex data structures like arrays, strings, and custom objects between Java and C++ using the JNI.

In the next chapter, we'll explore how to use third-party C++ libraries in your Android project and integrate them with your Java code.