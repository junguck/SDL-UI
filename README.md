
lien meet : https://meet.google.com/ujj-ukpx-dhk
---

# SDL3-UI-Framework (C++20)

Une bibliothèque d'interface utilisateur légère et moderne conçue pour **SDL3**. Ce projet exploite les nouvelles fonctionnalités de la version 3 (comme le `SDL_FRect` pour la précision flottante et le nouveau système de propriétés) pour offrir une base solide aux développeurs de jeux et d'outils.

## ✨ Pourquoi SDL3 ?

Ce projet utilise les dernières avancées de SDL3 pour garantir :

* **Précision Sub-pixel** : Utilisation systématique de `SDL_FRect` pour des animations fluides.
* **Gestion Native des Couleurs** : Intégration simplifiée des espaces colorimétriques.
* **Performance** : Optimisation des batchs de rendu via l'API de rendu SDL3.

## 🛠️ Composants Inclus

* **`BaseElement`** : Classe abstraite gérant la hiérarchie parent-enfant et les coordonnées relatives.
* **`Button`** : Supporte les textures, les couleurs dynamiques et les callbacks via `std::function`.
* **`TextInput`** : Intégration native avec le nouveau système de saisie SDL3 (gestion IME améliorée).
* **`Container`** : Un widget de type "Box" gérant le clipping automatique pour ses enfants.
* **`Label`** : Affichage de texte optimisé utilisant les textures de cache.

## 🏗️ Architecture Technique

Le projet suit une structure rigoureuse en **C++20** :

* **Smart Pointers** : Gestion automatique de la mémoire via `std::unique_ptr` pour les éléments de l'UI.
* **Système d'Événements** : Un dispatcher qui filtre les événements SDL3 et ne les transmet qu'aux éléments concernés (Hit-testing).
* **Relative Positioning** : Les enfants sont positionnés par rapport à leur parent, facilitant la création de fenêtres mobiles.



## 📦 Installation & Dépendances

* **SDL3** (dernière version du dépôt GitHub)
* **SDL3_ttf** (pour le rendu de texte)
* **CMake 3.20+**
* Compilateur compatible **C++20** (GCC 10+, Clang 12+, MSVC 19.29+)

---

### Prochaine étape suggérée

Souhaitez-vous que je vous montre comment implémenter la classe de base `BaseElement` en utilisant les **`SDL_FRect`** de SDL3 pour gérer le positionnement relatif ?
