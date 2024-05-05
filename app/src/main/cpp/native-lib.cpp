#include <jni.h>
#include <string>
#include <vector>


extern "C"
JNIEXPORT jint JNICALL
Java_com_safeai_webrtcapp_MainActivity_calculateSum(JNIEnv *env, jobject thiz, jint a, jint b) {
    // TODO: implement calculateSum()
    return a + b;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_safeai_webrtcapp_MainActivity_calculateDifference(JNIEnv *env, jobject thiz, jint a,
                                                           jint b) {
    // TODO: implement calculateDifference()
    return a - b;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_safeai_webrtcapp_MainActivity_CalculateArrySum(JNIEnv *env, jobject thiz,
                                                        jintArray array) {
    // TODO: implement CalculateArrySum()
    jint *elements = env->GetIntArrayElements(array, nullptr);
    jint length = env->GetArrayLength(array);
    jint sum = 0;

    for (int i=0; i<length;i++ ){
        sum = sum + elements[i];
    }

    env->ReleaseIntArrayElements(array, elements,JNI_ABORT);
    return sum;

}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_safeai_webrtcapp_MainActivity_ReversesString(JNIEnv *env, jobject thiz, jstring input) {

    const char *inputChars = env->GetStringUTFChars(input, nullptr);
    std::string inputStr(inputChars);
    std::reverse(inputStr.begin(), inputStr.end());
    env->ReleaseStringUTFChars(input, inputChars);
    return env->NewStringUTF(inputStr.c_str());

}
// C++ struct to represent the Person class
struct Person {
    std::string name;
    int age;
};

extern "C"
JNIEXPORT jobject JNICALL
Java_com_safeai_webrtcapp_MainActivity_swapPersonAttributes(JNIEnv *env, jobject thiz,
                                                            jobject person) {
    // TODO: implement swapPersonAttributes()
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