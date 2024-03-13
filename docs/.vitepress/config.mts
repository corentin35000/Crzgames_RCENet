import { defineConfig } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  base: "/", // The base URL your site will be deployed at. You will need to set this if you plan to deploy your site under a sub path, for example GitHub pages.
  srcDir: './src' , // The directory where VitePress will resolve your markdown files from.
  lastUpdated: true,
  sitemap: { // Generate a sitemap for better SEO
    hostname: 'https://librcenet.crzcommon2.com'
  },
  title: "RCENet",
  locales: {
    // Config for Language = EN (default language)
    root: {
      description: "A fork of ENet",
      label: 'English',
      lang: 'en',
      themeConfig: {
        nav: [
          { text: 'Home', link: '/' },
          { text: 'Guides', link: '/guides/getting-started/prerequisites' },
          { text: 'API', link: '/api/rcenet' },
          { text: 'Release Notes', link: 'https://github.com/corentin35000/Crzgames_RCENet/releases' },
        ],
        sidebar: {
          '/api/': [
            {
              text: 'RCENet API Reference',
              items: [
                { text: 'rcenet', link: '/api/rcenet' },
              ]
            },
          ],
          '/guides/': [
            {
              text: 'Guides',
              items: [
                { 
                  text: 'Getting Started', 
                  items: [
                    { text: 'Prerequisites', link: '/guides/getting-started/prerequisites' },
                    { text: 'Quick Start', link: '/guides/getting-started/quick-start' }
                  ] 
                },
                { text: 'Distribution', link: '/guides/distribution' },
              ]
            },
          ],
        }
      }
    },



    // Config for Language = FR
    fr: {
      description: "Un fork de ENet",
      label: 'Français',
      lang: 'fr',
      link: '/fr/',
      themeConfig: {
        nav: [
          { text: 'Accueil', link: '/fr/' },
          { text: 'Guides', link: '/fr/guides/getting-started/prerequisites' },
          { text: 'API', link: '/fr/api/rcenet' },
          { text: 'Notes de version', link: 'https://github.com/corentin35000/Crzgames_RCENet/releases' },
        ],
        sidebar: {
          '/fr/api/': [
            {
              text: 'Référence de l\'API RCENet',
              items: [
                { text: 'rcenet', link: '/fr/api/rcenet' },
              ]
            },
          ],
          '/fr/guides/': [
            {
              text: 'Guides',
              items: [
                { 
                  text: 'Commencer', 
                  items: [
                    { text: 'Conditions préalables', link: '/fr/guides/getting-started/prerequisites' },
                    { text: 'Démarrage rapide', link: '/fr/guides/getting-started/quick-start' }
                  ] 
                },
                { text: 'Distribution', link: '/fr/guides/distribution' },
              ]
            },
          ],
        }
      }
    },
  },


  
  // Config for ALL LANGUAGES
  themeConfig: {
    search: {
      provider: 'local'
    },
    socialLinks: [
      { icon: 'github', link: 'https://github.com/corentin35000/Crzgames_RCENet' }
    ],
    footer: {
      copyright: 'Copyright © 2024, Crzgames'
    }
  }
})