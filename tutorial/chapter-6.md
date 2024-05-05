# Chapter 6



Chapter 6: Advanced JNI Techniques and Best Practices

In the previous chapters, we covered the fundamentals of JNI development and explored some advanced topics like exception handling, multithreading, performance optimization, and native code security. In this chapter, we'll dive into some additional advanced techniques and best practices that can help you write more robust, efficient, and maintainable JNI code.

### JNI Local and Global References

When working with Java objects in C++ code, you need to manage references to those objects carefully to prevent memory leaks and ensure correct behavior. The JNI provides two types of references: local references and global references.

#### Local References

Local references are temporary references to Java objects that are automatically managed by the JNI. They are valid only within the scope of a single JNI function call or a single thread. When the function returns or the thread detaches from the JVM, all local references become invalid.

Here's an example of using local references:

```cpp
extern "C" JNIEXPORT void JNICALL
Java_com_safeai_webrtcapp_MainActivity_someNativeMethod(JNIEnv *env, jobject /* this */, jobject javaObject) {
    jclass objectClass = env->GetObjectClass(javaObject);
    // Use objectClass and perform operations on javaObject
    // ...

    // No need to explicitly delete local references
}
```

In this example, `javaObject` is a local reference to a Java object passed as an argument to the native method. We obtain the class of `javaObject` using `GetObjectClass`, which also returns a local reference. Local references are automatically managed by the JNI and do not need to be explicitly deleted.

#### Global References

Global references are permanent references to Java objects that remain valid until they are explicitly deleted or until the object is garbage-collected. Global references can be safely used across multiple threads and function calls, but they must be manually managed to avoid memory leaks.

Here's an example of using global references:

```cpp
extern "C" JNIEXPORT jobject JNICALL
Java_com_safeai_webrtcapp_MainActivity_createGlobalObject(JNIEnv *env, jobject /* this */) {
    jclass objectClass = env->FindClass("java/lang/Object");
    jmethodID constructor = env->GetMethodID(objectClass, "<init>", "()V");
    jobject newObject = env->NewObject(objectClass, constructor);

    // Create a global reference
    jobject globalRef = env->NewGlobalRef(newObject);

    // Delete the local reference to avoid memory leaks
    env->DeleteLocalRef(newObject);

    return globalRef;
}
```

In this example, we create a new Java object using `FindClass`, `GetMethodID`, and `NewObject`. We then create a global reference to the object using `NewGlobalRef`. It's important to delete the local reference to the object using `DeleteLocalRef` to avoid memory leaks.

When you're done using a global reference, you should delete it using `DeleteGlobalRef` to free the associated memory:

```cpp
extern "C" JNIEXPORT void JNICALL
Java_com_safeai_webrtcapp_MainActivity_deleteGlobalObject(JNIEnv *env, jobject /* this */, jobject globalRef) {
    env->DeleteGlobalRef(globalRef);
}
```

Global references can be useful when you need to retain a reference to a Java object across multiple JNI function calls or threads, but they should be used judiciously as they can lead to memory leaks if not managed properly.

### Weak Global References

Weak global references are a special type of global reference that does not prevent the associated Java object from being garbage-collected. They provide a way to maintain a reference to an object without preventing its garbage collection, which can be useful in certain scenarios where you need to handle the case of the object being collected.

Here's an example of using weak global references:

```cpp
extern "C" JNIEXPORT void JNICALL
Java_com_safeai_webrtcapp_MainActivity_useWeakGlobalRef(JNIEnv *env, jobject /* this */, jobject javaObject) {
    // Create a weak global reference
    jobject weakRef = env->NewWeakGlobalRef(javaObject);

    // Use the weak global reference
    // ...

    // Check if the object has been garbage-collected
    jobject referredObject = env->NewLocalRef(weakRef);
    if (referredObject == nullptr) {
        // The object has been garbage-collected
        // Handle the case accordingly
    } else {
        // The object still exists
        // Perform operations on referredObject
        // ...

        // Delete the local reference
        env->DeleteLocalRef(referredObject);
    }

    // Delete the weak global reference
    env->DeleteWeakGlobalRef(weakRef);
}
```

In this example, we create a weak global reference to a Java object using `NewWeakGlobalRef`. To use the weak global reference, we first obtain a local reference to the referred object using `NewLocalRef`. If the referred object has been garbage-collected, `NewLocalRef` will return `nullptr`.

After using the local reference, we delete it using `DeleteLocalRef`. Finally, we delete the weak global reference using `DeleteWeakGlobalRef`.

Weak global references can be useful in scenarios where you need to maintain a reference to an object for a specific purpose (e.g., caching, event handling), but you don't want to prevent the object from being garbage-collected if it's no longer needed elsewhere in the application.

### JNI Critical References

JNI critical references provide a way to temporarily "pin" Java objects in memory, preventing them from being moved or relocated by the garbage collector. This can be useful when you need to access the internal fields or data of a Java object directly from C++ code, as moving the object could invalidate the pointers you're using.

Here's an example of using critical references:

```cpp
extern "C" JNIEXPORT void JNICALL
Java_com_safeai_webrtcapp_MainActivity_accessObjectData(JNIEnv *env, jobject /* this */, jobject javaObject) {
    // Get the class and field ID
    jclass objectClass = env->GetObjectClass(javaObject);
    jfieldID dataField = env->GetFieldID(objectClass, "data", "I");

    // Get a critical reference to the object
    jint *data = static_cast<jint *>(env->GetPrimitiveArrayCritical(javaObject, nullptr));

    // Access and modify the object data
    *data = 42;

    // Release the critical reference
    env->ReleasePrimitiveArrayCritical(javaObject, data, JNI_COMMIT);
}
```

In this example, we obtain a critical reference to a Java object using `GetPrimitiveArrayCritical`. This function returns a pointer to the internal data of the object, which we can use to directly access and modify the object's fields.

After performing the necessary operations on the object's data, we release the critical reference using `ReleasePrimitiveArrayCritical`. The `JNI_COMMIT` flag indicates that any changes made to the object's data should be committed back to the Java object.

Critical references should be used with caution, as they can have a significant performance impact and can lead to deadlocks or other concurrency issues if not used correctly. They should be held for the shortest possible time and should not be used in performance-critical code paths.

### JNI Best Practices

In addition to the advanced techniques covered above, there are several best practices that you should follow when developing JNI code:

1. **Minimize JNI Calls**: As mentioned in the performance optimization section, JNI calls can be expensive due to the overhead of marshaling and unmarshaling data between Java and C++. Try to minimize the number of JNI calls by performing as much work as possible in the native code and passing larger data structures or batches of data between Java and C++.

2. **Use Defensive Programming Techniques**: JNI code is prone to errors and vulnerabilities if not written carefully. Always validate and sanitize input data, perform bounds checking, and handle exceptions and error conditions gracefully.

3. **Document Your JNI Code**: JNI code can be complex and difficult to understand, especially when dealing with advanced techniques like critical references or custom data structures. Document your code thoroughly, including the purpose, usage, and any assumptions or limitations.

4. **Follow Coding Standards and Style Guides**: Consistent coding standards and style guides can make your JNI code more readable and maintainable. Follow established coding standards and style guides