# Quick Start
 
This guide will help you set up a basic project structure. This is the minimum starter for the RC2D engine so you can start creating your game !

## 🛠 Tech Stack
- C++ (Language)
- A C++17 compiler (Visual C++ 2017, GCC 8.0, Clang 5, or newer)
- doctest (Unit tests)
- CI / CD (Github actions)
- CMake (Build script)
- Compiler (GCC, CL, Clang, Ninja, NDK)

<br /><br />


## 📂 Global Project Structure

Voici une représentation de l'arborescence du projet :

::: details Click me to view
```
├─ .github/                        # Dossier qui contient les fichiers de CI/CD pour GitHub Actions
│  ├─ build_deploy_production.yml/ # CI/CD : Environment Production (branch: main)
│  ├─ build_deploy_staging.yml/    # CI/CD : Environment staging (branch: staging)
│  ├─ test_deploy-release.yml/     # CI/CD : Deploy new version Release Notes in Github and tag new version for before run production (branch: main)
├─ android-project/                # Projet du jeu pour Android via un projet Android Studio (doit être versionner!)
│  ├─ app/
│  │  ├─ jni/CMakeLists.txt        # Dans le dossier jni contient le fichier CMakeLists.txt dédié au projet Android
│  │  ├─ jni/SDL/                  # Le dossier 'SDL' qui sont les sources complète de SDL pour la contrainte du wrapper de SDL pour Java JNI
│  │  ├─ src/main/assets/          # Placer les assets original ici (automatiser via RC2D)
│  │  ├─ src/main/AndroidManifest  # Ajouter de nouvelle permission si besoin
│  │  ├─ build.gradle              # Configuration du projet android pour : Version app android, SDK version, NDK version, name package android..etc ainsi que la signature pour la production pour le .apk / .aab
│  │  ├─ ...
│  ├─ distribution/whatsnews/ 
│  │  ├─ whatsnew-en-US            # Release Note for PlayStore to language EN
│  │  ├─ whatsnew-fr-FR            # Release Note for PlayStore to language FR
│  │  ├─ ...
├─ assets/                         # Assets original pour le jeu (exclu du versioning)
├─ build-scripts/                  # Le dossier qui contient tout les scripts de build
│  ├─ android/
│  │  ├─ update-app-version.sh     # This script is feature for changes "versionCode" and "versionName" relative to last tag fetch in github actions CI
│  ├─ assets/
│  │  ├─ build-assets-rres.sh      # Script pour convertir les assets original situé dans le dossier 'assets' vers le format de fichier : .rres
│  ├─ generate-project-production/
│  │  ├─ android.sh                # Bundle .apk / .aab and Sign
│  │  ├─ ios.sh                    # Bundle .ipa and Sign
│  │  ├─ linux.sh                  # Bundle .AppImage
│  │  ├─ macos.sh                  # Bundle .app and Sign
│  │  ├─ windows.sh                # Bundle .exe and Sign
│  ├─ generate-project/
│  │  ├─ ios.sh                    # Generate project xCode with CMake for game project
│  │  ├─ linux.sh                  # Generate project Makefile with CMake for game project
│  │  ├─ macos.sh                  # Generate project xCode with CMake for game project
│  │  ├─ windows.sh                # Generate project VS2022 with CMake for game project
│  ├─ icons/
│  │  ├─ generate-icons.sh         # Script pour générer les icônes
│  ├─ run-project-development/
│  │  ├─ android.sh                # Install .apk in real device connected and run application and start logcat in terminal 
│  │  ├─ ios.sh                    # Install .ipa in real device connected and run application and start log in terminal
│  │  ├─ linux.sh                  # Run project en mode Debug
│  │  ├─ macos.sh                  # Run project en mode Debug
│  │  ├─ windows.sh                # Run project en mode Debug
├─ dependencies/                   # Submodules pour les librairies pour chaque plateformes.
├─ dist/                           # Builds du jeu pour chaque plateforme (exclu du versioning)
├─ icons/                          # Dossier qui contient les icones pour toute les plateformes
│  ├─ android/                     # mimap-*.png
│  ├─ linux/                       # .png
│  ├─ macos-ios/                   # .icns
│  ├─ windows/                     # .ico and .o
│  ├─ app-icon-default.png/        # Icone de base à modifier la premiere fois pour mettre sont icone a la place
├─ include/                        # Dossier include pour les fichiers include du jeu
│  ├─ game.h                       # Fichier .h des prototype pour la logique de votre jeu
│  ├─ unit-tests.h                 # (Facultatif) Fichier .h du prototype pour la fonction pour lancer les tests unitaires
├─ rres/                           # Dossier qui contient les fichiers .rres générer lors du build des assets pour le jeu (exclu du versioning)
├─ rrespacker/                     # Dossier qui contient l'outils rrespacker pour les distribution Desktop
│  ├─ linux-x86_64/
│  │  ├─ rrespacker                # Binaire tool rrespacker for Linux
│  ├─ macos-x86_64-arm64/
│  │  ├─ rrespacker.app            # Binaire tool rrespacker for macOS
│  ├─ windows-x64/
│  │  ├─ rrespacker.exe            # Binaire tool rrespacker for Windows
│  ├─ v1.5.0                       # Info version rrespacker
├─ src/                            # Dossier des fichiers source du jeu
│  ├─ game.cpp                     # Fichier d'implémentation pour la logique de votre jeu
│  ├─ main.cpp                     # Le point d'entrée de votre application
│  ├─ unit-tests.cpp               # (Facultatif) Pour les tests unitaires avec Doctest
├─ .gitignore                      # Permet d'éviter de versionner certains fichiers
├─ .gitmodules                     # Contient les path vers les dependencies (submodules)
├─ CHANGELOG.md                    # Journal des modifications des diffèrente versions
├─ CMakeLists.txt                  # Script de construction cross-plateformes
├─ README.md                       # Documentation de votre projet à personnaliser
├─ appimage.cmake                  # Fichier .cmake utiliser par CMakeLists.txt pour le bundle d'un .AppImage (Linux)
├─ version.txt                     # Fichier de version du jeu
```
:::

::: warning IMPORTANT
Assurez-vous de bien organiser vos fichiers et répertoires selon cette structure pour faciliter la maintenance et le déploiement de votre projet.
:::

<br /><br />


## 🚀 Main Project Structure

Your project should include at least the following files:

- `main.cpp`: The entry point of your application.
- `game.h`: Header file containing declarations for your game's callback functions.
- `game.cpp`: Implementation file for your game's logic.
- `unit-tests.h`: (Optional) Header file containing declarations for unit testing with Doctest.
- `unit-tests.cpp`: (Optional) For unit testing with Doctest.

<br />

### main.cpp

The `main.cpp` file should include the RC2D header, unit-tests header and your game header.

::: warning IMPORTANT
Ensure the `main` function prototype is exactly `int main(int argc, char* argv[])` for SDL2_main compatibility.
:::

```cpp
#include <rc2d/RC2D.h>
#include "game.h"
#include "unit-tests.h"

int main(int argc, char* argv[])
{
#ifndef DOCTEST_CONFIG_DISABLE
    if (rc2d_tests_runAllTests(argc, argv) != 0) return -1;
#endif

    RC2D_Callbacks myGameCallbacks = {};
    myGameCallbacks.rc2d_unload = rc2d_unload;
    myGameCallbacks.rc2d_load = rc2d_load;
    myGameCallbacks.rc2d_update = rc2d_update;
    myGameCallbacks.rc2d_draw = rc2d_draw;
    // Implement other callbacks...

    rc2d_run(&myGameCallbacks);

    return 0;
}
```

### game.h

Declare your game's callback functions and any other game-specific functionality.

::: details Click me to view the code
```cpp
#ifndef _GAME_H_
#define _GAME_H_

void rc2d_unload(void);
void rc2d_load(void);
void rc2d_update(double dt);
void rc2d_draw(void);

// Implement other callbacks...

#endif // _GAME_H_
```
:::

### game.cpp

Implement your game's logic and callback functions.

::: details Click me to view the code
```cpp
#include "game.h"

RC2D_Image image;

void rc2d_unload(void)
{
    rc2d_graphics_freeImage(image);
}

void rc2d_load(void)
{
    image = rc2d_graphics_newImage("images/test.png");
}

void rc2d_update(double dt)
{

}

void rc2d_draw(void)
{
    rc2d_graphics_draw(image, 300, 200);
}

// Implement other callbacks...
```
:::

### unit-tests.h

(Optional) Header file containing declarations for unit testing with Doctest.

::: details Click me to view the code
```cpp
#ifndef _UNIT_TESTS_H_
#define _UNIT_TESTS_H_

int rc2d_tests_runAllTests(int argc, char* argv[]);

#endif // _UNIT_TESTS_H_
```
:::

### unit-tests.cpp

(Optional) For projects using unit testing with Doctest.

::: details Click me to view the code
```cpp
#include "unit-tests.h"
#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT
#endif
#include <doctest/doctest.h>

// Run all tests with Doctest and return the result
int rc2d_tests_runAllTests(int argc, char* argv[])
{
    doctest::Context context; // Initialisez le contexte
    context.applyCommandLine(argc, argv); // Appliquez les arguments de la ligne de commande
    int test_result = context.run(); // Exécutez les tests

    if(context.shouldExit() || test_result != 0) 
    {
        return test_result; // Termine l'exécution si Doctest demande de quitter ou si les tests échouent
    }

    return 0;
}

TEST_CASE("Example test case") {
    int x = 1;
    CHECK(x == 1); // Test success
    CHECK(x == 2); // Test error
}
```
:::

<br /><br />


## ✨ À propos de RC2D

### 🕹️ RC2DCore
Une bibliothèque écrite en C pur, fournissant l'ensemble des fonctionnalités nécessaires pour développer des jeux vidéo sur les plateformes desktop, console et mobile. Cette librairie constitue le cœur du moteur de jeu RC2D et est conçue pour être extrêmement performante et flexible.

### 📦 RC2DFramework
RC2DFramework, ou le "game template", est construit au-dessus de RC2DCore et offre une structure de projet et des outils pour démarrer rapidement le développement de votre jeu. Il inclut le rrespacker et le format rres, nécessitant que les assets soient placés dans le dossier assets à la racine du repo pour que le rrespacker puisse les traiter correctement. RC2DFramework ajoute quelques librairies en plus comme : base64, nlohmann (json) et doctest (unit tests) par rapport au package RC2DCore, qui oblige RC2DFramework à passé en C++ à cause de ces nouvelles librairies.

<br /><br />


## 🎮 Commencer le Développement
Pour commencer le développement avec RC2D, suivez les étapes décrites dans la section Structure Globale du Projet pour configurer votre environnement de développement, puis utilisez RC2DCore et RC2DFramework comme bases pour développer la logique de votre jeu et gérer vos assets.

Bonne création avec RC2D !