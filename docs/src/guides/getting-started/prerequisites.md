# 📋 Prerequisites

Welcome to the setup guide for the RC2D Framework. This guide will walk you through the steps to set up your development environment across various platforms.

## 🚀 Setup Project

### Create a new GitHub Repository

1. Go to GitHub to create a new repository: [Create New Repository](https://github.com/new)
2. Under 'Repository Template', select: `corentin35000/Crzgames_RC2DFramework`
3. Check : `Include all branches`
4. Choose a name for your GitHub repository.
5. Click the button to create the repository.

<br />

### Clone the Project

To start working with the game template, clone the project repository and initialize all submodules using the following commands:

```bash
git clone --recurse-submodules git@github.com:corentin35000/your_project_name.git
```

Ensure to replace `your_project_name` with the actual name of your project repository.

::: warning IMPORTANT
Make sure you do a recursive clone! The submodules contain the dependencies, if you have already cloned the project without the submodules, use this command
```bash
git submodule update --init --recursive
```
:::

<br /><br />

## ⚙️ Setup Environment by Platform
Follow the instructions below based on your development platform to get everything up and running.

### 🖥 Windows Setup

::: details Click me to view
#### Requirements
- System version : Windows 10 or higher
- System architectures : x64 / x86
- A C++17 compiler (Visual C++ 2017 or newer)

<br />

#### Installation Steps
1. **Visual Studio:** Download and install Visual Studio 2022 with MSVC >= v143 and Windows SDK >= 10. [Download here](https://visualstudio.microsoft.com/downloads/).
2. **CMake:** Ensure CMake 3.28 or newer is installed and added to your PATH. [Download here](https://cmake.org/download/).
3. **WSL2:** Opt for WSL2 installation for better compatibility with build scripts.
:::

---

<br />

### 🐧 Linux Setup

::: details Click me to view
#### Requirements
- System version : glibc 3.25 or higher (Ubuntu 22.04+, Debian 12.0+)
- System architectures : x86_64
- A C++17 compiler (GCC 8.0 or newer)

<br />

#### Installation Steps
1. Add your user to the `sudo` group if necessary :
```bash
sudo usermod -aG sudo <username>
```
2. **Homebrew:** Facilitate package management by installing Homebrew.
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
3. **Build Essentials and GCC:** Install necessary build tools and GCC.
```bash
sudo apt-get update
sudo apt-get install -y build-essential && brew install gcc
```
4. **CMake:** Make sure CMake 3.28 or newer is installed via Homebrew.
```bash
brew install cmake
```
:::

---

<br />

### 🍏 macOS Setup

::: details Click me to view
#### Requirements
- System version : macOS 14.0 or higher
- System architectures : Intel x86_64 / Apple Silicon arm64
- A C++17 compiler (Clang 5 or newer)

<br />

#### Installation Steps
1. **xCode:** Download and install Xcode 15.2.0 or newer.
2. **Command Line Tools:**
```bash
xcode-select --install
```
3. **Homebrew:** Use Homebrew for managing packages.
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
4. **CMake:** Ensure CMake 3.28 or newer is installed through Homebrew.
```bash
brew install cmake
```
:::

---

<br />

### 📱 iOS Setup (macOS only)

::: details Click me to view
#### Requirements
- System version : macOS 14.0 or higher
- System architectures : Intel x86_64 / Apple Silicon arm64
- A C++17 compiler (Clang 5 or newer)

<br />

#### Installation Steps
1. **xCode:** Download and Install xCode 15.2.0 or newer.
2. **SDK iOS:** Download and Install iOS SDK 17.0.0 or newer.
3. **Command Line Tools:**
```bash
xcode-select --install
```
4. **Homebrew:** Install Homebrew for package management.
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
5. **CMake:** CMake 3.28 or newer is installed using Homebrew.
```bash
brew install cmake
```
6. **ios-deploy:** Finally, ensure ios-deploy is installed using Homebrew.
```bash
brew install ios-deploy
```
:::

---

<br />

### 🤖 Android Setup (Windows)

::: details Click me to view
#### Requirements
- Modify the 'android-project' project for your project: [Modification guide](https://librc2d.crzcommon2.com/projects/android.html)
- A C++17 compiler

<br />

#### Installation Steps
1. Download and Install Android Studio 2023.1.1 or newer : https://developer.android.com/studio
2. Add environment variable: ANDROID_HOME for path SDK Android (SDK Manager)
3. Download and Install Java JDK LTS (Oracle) == 17.0.10 : https://www.oracle.com/fr/java/technologies/downloads/#java17
4. Java added to your PATH ENVIRONMENT
5. Download and Install ADB
6. ADB added to your PATH ENVIRONMENT
7. Download and Install CMake 3.22.1 or newer : https://cmake.org/download/
8. CMake added to your PATH ENVIRONMENT
:::

---

<br />

### 🤖 Android Setup (macOS)

::: details Click me to view
#### Requirements
- Modify the 'android-project' project for your project: [Modification guide](https://librc2d.crzcommon2.com/projects/android.html)
- A C++17 compiler

<br />

#### Installation Steps
1. **xCode:** Download and Install xCode 15.2.0 or newer.
2. **Command Line Tools:**
```bash
xcode-select --install
```
3. **Homebrew:** Install Homebrew for package management.
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
4. **CMake:** CMake 3.22.1 or newer is installed using Homebrew.
```bash
brew install cmake
```
5. CMake added to your PATH ENVIRONMENT
6. Download and Install Android Studio 2023.1.1 or newer : https://developer.android.com/studio
7. Add environment variable: ANDROID_HOME for path SDK Android (SDK Manager)
8. Download and Install Java JDK :
```bash
brew install openjdk@17
```
9. Add environment variable: JAVA_HOME for path openjdk@17
10. Download and Install ADB
```bash
brew install adb-enhanced
```
11. ADB added to your PATH ENVIRONMENT
:::

---

<br />

### 🤖 Android Setup (Linux)

::: details Click me to view
#### Requirements
- Modify the 'android-project' project for your project: [Modification guide](https://librc2d.crzcommon2.com/projects/android.html)
- A C++17 compiler

<br />

#### Installation Steps
1. Add your user to the `sudo` group if necessary :
```bash
sudo usermod -aG sudo <username>
```
2. **Homebrew:** Facilitate package management by installing Homebrew.
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
3. **Build Essentials and GCC:** Install necessary build tools and GCC.
```bash
sudo apt-get update
sudo apt-get install -y build-essential && brew install gcc
```
4. Download and Install CMake 3.22.1 or newer
```bash
brew install cmake
```
5. CMake added to your PATH ENVIRONMENT
6. Download and Install Android Studio 2023.1.1 or newer : https://developer.android.com/studio
7. Add environment variable: ANDROID_HOME for path SDK Android (SDK Manager)
8. Download and Install Java JDK :
```bash
brew install openjdk@17
```
9. Add environment variable: JAVA_HOME for path openjdk@17
10. Download and Install ADB
```bash
brew install adb-enhanced
```
11. ADB added to your PATH ENVIRONMENT
:::