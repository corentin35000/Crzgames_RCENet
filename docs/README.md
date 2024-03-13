## Crzgames - RCENet Documentation


## <span style="color: green;">🛠 Tech Stack</span>
- Vitepress (Framework)
- NodeJS (Environment)
- CI / CD (Github Actions)

<br /><br /><br /><br />


## <span style="color: green;">📚 Documentation Project</span>
- Ajouter les images, favicon, robot.txt que vous avez besoin dans le dossier : ./docs/src/public
- Pour chaque langue un dossier nommé : 'fr', 'us'..etc dans le dossier : ./docs/src/
- Fichier de configuration du site dans : ./docs/.vitepress/config.mts

<br /><br /><br /><br />


## <span style="color: green;"> ⚙️ Setup Environment</span>
1. Download and Install NodeJS >= 18
2. Install dependencies :
```bash
   cd ./docs
   npm install
```


<br /><br /><br /><br />


## <span style="color: green;"> 🔄 Cycle Development</span>
1. Run command :
```bash
   cd ./docs
   npm run dev
```

<br /><br /><br /><br />


## <span style="color: green;">Production</span>
### ✋ Manual :
1. Build documentation to website static for production :
```bash
   cd ./docs
   npm install
   npm run build
   npm run preview # test if success
```
