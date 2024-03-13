# Prerequisites

Welcome to the RC2D Game Engine! This guide will walk ensuring you have everything you need to get started with game development.

## Tech Stack 🛠
- C++ (Language)
- A C++17 compiler (Visual C++ 2017, GCC 8.0, Clang 5, or newer)
- doctest (Unit tests)
- CI / CD (Github actions)
- CMake (Build script)
- Compiler (GCC, CL, Clang, Ninja, NDK)

<br /><br />


## System Requirements

Below are the minimal system requirements :

| Platform | Architectures | System Version |
|----------|---------------|----------------|
| Windows  | x64 / x86     | Windows Vista+ |
| macOS    | Intel x86_64 / Apple Silicon arm64   | macOS 11.0+ 
| Linux    | x86_64        | glibc 3.25+
| Android  | arm64-v8a / armeabi-v7a / x86_64 / x86       | Android 6.0+
| iOS      | arm64 (iphoneos) - arm64 / x86_64 (iphonesimulator) | iOS 12.0+

<br /><br />


## Setup Environment for RC2D Development

Welcome to the setup guide for the RC2D Game Engine. This guide will walk you through the steps to set up your development environment across various platforms.

### Clone the Project for Game Template

To begin, clone the project repository and initialize all submodules:

```bash
git clone --recurse-submodules git@github.com:corentin35000/Crzgames_GameTemplate.git
```

<br />

### Setup Instructions by Platform

### Windows Setup

#### Requirements
- Windows 10 or higher
- A C++17 compiler (Visual C++ 2017 or newer)

#### Installation Steps
1. **Visual Studio 2022:** Download and install Visual Studio 2022 with MSVC v143 and Windows SDK 10. [Download here](https://visualstudio.microsoft.com/downloads/).
2. **CMake:** Download and install CMake 3.28 or newer and add it to your PATH environment variable. [Download here](https://cmake.org/download/).

<br />

### Linux Setup

#### Requirements
- glibc 3.25 or higher (Ubuntu 22.04+, Debian 12.0+)
- A C++17 compiler (GCC 8.0 or newer)

#### Installation Steps
1. Add your user to the `sudo` group if necessary:
    ```bash
    sudo usermod -aG sudo <username>
    ```
2. **Homebrew:** Install Homebrew for package management.
    ```bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```
3. **Build Essentials and GCC:** Install necessary build tools.
    ```bash
    sudo apt-get install -y build-essential && brew install gcc
    ```
4. **CMake:** Install CMake 3.28 or newer through Homebrew.
    ```bash
    brew install cmake
    ```

<br />

### macOS Setup

#### Requirements
- MacOS 14.0 or higher
- A C++17 compiler (Clang 5 or newer)

#### Installation Steps
1. **Xcode:** Download and install Xcode 15.2.0 or newer.
2. **Command Line Tools:** Install the command-line tools using:
    ```bash
    xcode-select --install
    ```
3. **Homebrew:** Install Homebrew for package management.
    ```bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```
4. **CMake:** Install CMake 3.28 or newer using Homebrew.
    ```bash
    brew install cmake
    ```

<br />

### Android Setup

#### Common Requirements
- Android Studio 2023.1.1 or newer
- Java JDK LTS (Oracle) 17.0.10 or newer
- CMake 3.28 or newer
- A C++17 compiler

#### Installation Steps
- Ensure Android Studio, JDK, and CMake are installed and properly configured with environment variables for `ANDROID_HOME` (Windows) or `ANDROID_NDK_HOME` (Unix).

<br />

### iOS Setup (macOS only)

#### Requirements
- MacOS 14.0 or higher
- A C++17 compiler (Clang 5 or newer)

#### Installation Steps
1. **Xcode:** Download and install Xcode 15.2.0 or newer and ensure iOS SDK 17.0 or newer is installed.
2. **Command Line Tools:** Install the command-line tools using:
    ```bash
    xcode-select --install
    ```
3. **Homebrew:** Install Homebrew for package management.
    ```bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```
4. **CMake:** Install CMake 3.28 or newer using Homebrew.
    ```bash
    brew install cmake
    ```