# Distribution

Getting your game into the hands of players is a crucial step in game development. This guide focuses on preparing your RC2D project for distribution across various platforms.

## Executable Distribution

Each platform has its specific bundle format for the game executable. Distributing your game in the appropriate format ensures compatibility and ease of installation for your users.

| Platform | Bundle Format |
|----------|---------------|
| **Windows** | `.exe` |
| **macOS** | `.app` |
| **Linux** | `.AppImage` |
| **Android** | `.apk` / `.aab` |
| **iOS** | `.ipa` |

<br /><br />


## System Requirements

Ensuring that your game runs smoothly requires understanding the minimal system requirements for each platform. Below are the requirements that users need to meet to experience your game without issues.

| Platform | Architectures | System Version |
|----------|---------------|----------------|
| **Windows** | x64 / x86 | Windows Vista+ |
| **macOS** | Intel x86_64 / Apple Silicon arm64 | macOS 11.0+ |
| **Linux** | x86_64 | glibc 3.25+ |
| **Android** | arm64-v8a / armeabi-v7a / x86_64 / x86 | Android 6.0+ |
| **iOS** | arm64 (iphoneos) - arm64 / x86_64 (iphonesimulator) | iOS 12.0+ |

::: warning IMPORTANT
Ensure your development and testing environments meet or exceed these system requirements to offer the best user experience possible.
:::

By adhering to these distribution guidelines and system requirements, you can streamline the deployment of your RC2D game across multiple platforms, ensuring a broad and satisfied audience.

<br /><br />


## Production

### Automatic Distribution Process (CI / CD)

Setting up Continuous Integration and Continuous Deployment (CI/CD) pipelines can automate the distribution process, ensuring that your game is always up-to-date with the latest changes.

::: tip SETUP
CI/CD files are included with the Game Template, streamlining the setup process if it has not been configured previously.
:::

<br /><br />

### Manual Distribution Process

To manually generate the RC2D library for distribution, follow the commands based on your target platform:

#### Linux
```bash
./build-scripts/generate-lib/linux.sh
```

#### macOS
```bash
./build-scripts/generate-lib/macos.sh
```

#### Windows
```bash
sh .\build-scripts\generate-lib\windows.sh
```

#### Android (run in Unix)
```bash
./build-scripts/generate-lib/android.sh
```

#### Android (run in Windows)
```bash
sh .\build-scripts\generate-lib\android.sh
```

#### iOS (run in macOS)
```bash
./build-scripts/generate-lib/ios.sh
```

<br />

### Retrieving the RC2D Library for Distribution

After generating the libraries, here's how you can retrieve them for each system:

### Windows
1. Navigate to `dist/lib/windows/`
2. Choose `Release` or `Debug` directory
3. Retrieve the RC2D library: `rc2d.lib`

### Linux
1. Navigate to `dist/lib/linux/`
2. Choose `Release` or `Debug` directory
3. Retrieve the RC2D library: `librc2d.a`

### macOS
1. Navigate to `dist/lib/macos/`
2. Choose `Release` or `Debug` directory
3. Retrieve the RC2D library: `librc2d.a`

### Android
1. Navigate to `dist/lib/android/`
2. Choose `Release` or `Debug` directory
3. Retrieve the RC2D library: `librc2d.so`

### iOS
1. For iPhoneOS SDK (arm64, arm64e), navigate to `dist/lib/ios/arm64-arm64e/iphoneos/`
2. For iPhoneSimulator SDK (x86_64, arm64), navigate to `dist/lib/ios/x86_64-arm64/iphonesimulator/`
3. Choose `Release` or `Debug` directory
4. Retrieve the RC2D library: `librc2d.a`

::: warning IMPORTANT
Selecting the correct build configuration and platform directory is crucial for the successful distribution of your game.
:::