# Android NDK build

The interpreter core is Android-compatible and can be built as a static library with the Android NDK. The interactive editline console is disabled automatically on Android; applications should use the C API from `include/brainfuck.h`.

From the repository root, configure with an installed NDK:

```sh
cmake -S . -B build-android \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-24 \
  -DENABLE_CLI=OFF \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build-android
```

The resulting `libbrainfuck.a` can be linked into an Android app or JNI library. Repeat the build with `ANDROID_ABI=armeabi-v7a`, `x86`, or `x86_64` for other supported ABIs.

The library has no Android-specific runtime dependencies.
