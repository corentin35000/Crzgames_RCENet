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
      description: "An improved fork of ENet",
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
                { text: 'rcenet_address', link: '/api/rcenet_address' },
                { text: 'rcenet_host', link: '/api/rcenet_host' },
                { text: 'rcenet_packet', link: '/api/rcenet_packet' },
                { text: 'rcenet_peer', link: '/api/rcenet_peer' },
                { text: 'rcenet_protocol', link: '/api/rcenet_protocol' },
                { text: 'rcenet_range', link: '/api/rcenet_range' },
                { text: 'rcenet_socket', link: '/api/rcenet_socket' },
                { text: 'rcenet_time', link: '/api/rcenet_time' },
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
                    { text: 'Quick Start', link: '/guides/getting-started/quick-start' },
                    { text: 'Features', link: '/guides/getting-started/features' }
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
      description: "Un fork de ENet améliorer",
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
                { text: 'rcenet_address', link: '/fr/api/rcenet_address' },
                { text: 'rcenet_host', link: '/fr/api/rcenet_host' },
                { text: 'rcenet_packet', link: '/fr/api/rcenet_packet' },
                { text: 'rcenet_peer', link: '/fr/api/rcenet_peer' },
                { text: 'rcenet_protocol', link: '/fr/api/rcenet_protocol' },
                { text: 'rcenet_range', link: '/fr/api/rcenet_range' },
                { text: 'rcenet_socket', link: '/fr/api/rcenet_socket' },
                { text: 'rcenet_time', link: '/fr/api/rcenet_time' },
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
                    { text: 'Démarrage rapide', link: '/fr/guides/getting-started/demarage-rapide' },
                    { text: 'Fonctionnalités', link: '/fr/guides/getting-started/fonctionnalites' },
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