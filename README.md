# 📊 SCOPSim for Optical Simulation (CUPID experiment)

**Simulation optique des détecteurs de l'expérience CUPID**

**Auteurs**: Arnaud HUBER (huber@lp2ib.in2p3.fr)  
**Auteurs**: Lucas FEDERSPIEL (federspi@lp2ib.in2p3.fr)  
**Affiliation**: LP2IB, IN2P3/CNRS  
**Date**: 2025–2026

---

## 📑 Table des Matières

1. [Aperçu du Projet](#-aperçu-du-projet)
2. [Architecture](#-architecture)
3. [Compilation](#-compilation--setup)
4. [Exécution](#-exécution)
5. [Macros Geant4](#-documentation-des-macros-geant4)
6. [Composants Core](#-composants-core)
7. [Flux de Données](#-flux-de-données--statistiques)
8. [Sortie ROOT](#--sortie-root)
9. [Dépannage](#-dépannage)
10. [Documentation API](#-documentation-api)
11. [Licence](#-licence)

---

## 🎯 Aperçu du Projet

### Objectif
Simuler les processus optiques dans un cristal de LMO, incluant :
- ✅ Génération de lumière par ionisation (scintillation & Cerenkov)
- ✅ Propagation optique
- ✅ Etats de surface
- ✅ Détection par Light Detectors (LD)

---

## 🏗️ Architecture

```
Projet_Instru_Contaminametre_AlphaBeta/
├── SCOPSim.cc              ← Exécutable principal
├── CMakeLists.txt                    ← Configuration build
├── Doxyfile                          ← Documentation Doxygen
│
├── include/                          ← Headers (.hh)
│   ├── SCOPSimGeometryConstruction.hh
│   ├── SCOPSimEventAction.hh
│   ├── SCOPSimSteppingAction.hh
│   ├── SCOPSimRunAction.hh
│   ├── SCOPSimPhysics.hh
│   ├── SCOPSimMaterials.hh
│   ├── Geometry.hh
│   └─�� ...
│
├── src/                              ← Implémentation (.cc)
│   ├── SCOPSimGeometryConstruction.cc
│   ├── SCOPSimEventAction.cc
│   ├── SCOPSimSteppingAction.cc
│   ├── SCOPSimRunAction.cc
│   ├── SCOPSimMaterials.cc
│   ├── Geometry.cc
│   └── ...
│
├── bin/                              ← Exécutables & macros
│   ├── SCOPSim             (généré)
│   ├── vis.mac                       (visualisation interactive)
│   └── vrml.mac                      (batch sans GUI)
│
├── simulation_input_files/           ← Données matériaux
│   ├── QE_ham_GA0154.txt            (PMT quantum efficiency)
│   ├── teflon.dat                    (réflectivité Teflon)
│   ├── mylar.dat                     (réflectivité Mylar)
│   └── ... (150+ fichiers .cfg/.dat)
│
├── gdml_models/                      ← Modèles géométrie GDML
├── XML_schemas/                      ← Schémas XML
└── Resultats/                        ← Output (fichiers ROOT)
```

---

## 🔧 Compilation & Setup

### Prérequis

```bash
# Geant4 >= 11.1 compilé avec GDML
cmake -DGEANT4_USE_GDML=ON  # lors de la compilation de Geant4

# CLHEP (inclus avec Geant4)
# C++17 ou plus
# ROOT (recommandé pour l'analyse)
```

### Étapes de Compilation

```bash
# 1. Cloner le repository
git clone https://github.com/ahuber33/Projet_Instru_Contaminametre_AlphaBeta
cd Projet_Instru_Contaminametre_AlphaBeta

# 2. Créer le répertoire de build
mkdir build && cd build

# 3. Générer les makefiles
cmake -DGeant4_DIR=$G4COMP ../
# $G4COMP pointe vers le répertoire d'installation de Geant4
# Ex: /usr/local/geant4.11.2.1-install

# 4. Compiler avec parallélisation
make -j$(nproc)
# Cette commande utilise tous les cores disponibles
```

**Résultat**: L'exécutable `SCOPSim` est généré dans `bin/`

---

## 🎬 Exécution

### Mode 1: Visualisation Interactive

```bash
cd build
./SCOPSim output
# Exécute bin/vis.mac
# → Ouvre interface OpenGL interactive
# → Permet de visualiser la géométrie et les trajectoires
# → Résultat: Resultats/output.root
```

**Contrôles OpenGL**:
- **Souris gauche + glisser** : Rotation 3D
- **Souris milieu + glisser** : Translation
- **Scroll** : Zoom
- **'s'** : Sauvegarde screenshot
- **Terminal** : Entrer commandes Geant4

### Mode 2: Batch Multi-threading (Production)

```bash
cd build
./SCOPSim output 1000 vrml.mac ON 4
# Paramètres:
# - output          : Nom du fichier ROOT (sans extension)
# - 1000            : Nombre d'événements à simuler
# - vrml.mac        : Macro fichier à exécuter (depuis bin/)
# - ON              : Activation multi-threading
# - 4               : Nombre de threads

# Résultat: Resultats/output.root
# (après fusion des fichiers partiels output_1.root, output_2.root, etc.)
```

### Mode 3: Batch Mono-thread

```bash
./SCOPSim output 100 vrml.mac OFF
# Plus lent mais déterministe (reproductible)
```

---

## 📝 Documentation des Macros Geant4

Les fichiers macro (`.mac`) sont des scripts de commandes qui configurent la simulation. Géant4 les exécute de manière séquentielle.

### 📄 **vis.mac** - Macro de Visualisation Interactive

**Chemin**: `bin/vis.mac`  
**Usage**: Visualisation 3D interactive du détecteur

```bash
# Configuration Visualisation (Lignes 1-13)
/vis/open OGL 600x600-0+0                 # Fenêtre OpenGL 600×600px
/vis/drawVolume                            # Dessine la géométrie
/vis/viewer/set/viewpointThetaPhi 0 0     # Angle caméra (theta, phi en °)
/vis/viewer/set/upVector 1 0 0            # Vecteur "vers le haut"
/vis/viewer/set/viewpointVector -0.99 0 0.01  # Position caméra (x, y, z)
/vis/viewer/zoom 1.                       # Zoom initial: 1x = pas de zoom
/vis/viewer/set/auxiliaryEdge true        # Affiche les arêtes auxiliaires
/vis/viewer/set/hiddenMarker true         # Affiche marqueurs cachés
/vis/scene/endOfEventAction accumulate    # Accumule les trajectoires
/tracking/storeTrajectory 1               # Stocke les trajectoires (0=non, 1=oui)
/vis/scene/add/date                       # Affiche horodatage
/vis/viewer/set/background white          # Couleur de fond
/vis/scene/add/trajectories smooth        # Trajectoires lisses (spline)
```

**Configuration Géométrie** (Lignes 36-49):
```bash
/SCOPSim/geometry/setLMOSurfaceModel glisur                    # Modèle optique pour surface : glisur, unified
/SCOPSim/geometry/setLMOSurfaceType dielectric_dielectric      # Type de surface : dielectric-dielectric, dielectric-metal
/SCOPSim/geometry/setLMOSurfaceFinish ground                   # Finition de surface : ground, polished
/SCOPSim/geometry/setLMOSurfacePolish 1.0                      # Avec le moèle glisur : Définit la proportion de surface polie/dépolie [0 ; 1]
/SCOPSim/geometry/setLMOSurfaceSigmaAlpha 0.1                  # Avec le modèle unified : Définit le RMS de l'angle des microfacettes

# OBLIGATOIRE : Réappliquer la géométrie après modifications
/run/reinitializeGeometry
/run/physicsModified
```

**Suivi Optique** (Lignes 56-60):
```bash
/SCOPSim/step/setVerbose 0              # Verbosité: 0=silence
/SCOPSim/step/setPhotonTrackStatus true # Tracker les photons optiques
/tracking/verbose 0                               # Verbosité Geant4 tracking
/run/verbose 1                                    # Verbosité du run
```

**Générateur de Particules GPS** (Lignes 64-75):
```bash
/gps/number 1                                     # 1 particule par événement
/gps/particle e-                                  # Type: e- (électron)
/gps/pos/type Point                               # Source: Point (ou Volume, Surface)
/gps/pos/centre 0.0 0.0 -100.0 mm                # Position [x, y, z] mm
/gps/direction 0.0 0.0 1.0                       # Direction (vecteur normalisé)
/gps/energy 2. MeV                               # Énergie cinétique [MeV]
#/run/beamOn 1                                    # (Commenté) Lance la simulation
```

---

### 🖥️ **vrml.mac** - Macro Mode Batch (Sans Visualisation)

**Chemin**: `bin/vrml.mac`  
**Usage**: Simulation batch rapide (pas d'interface graphique)

**Contenu** :

```bash
/SCOPSim/geometry/setLMOSurfaceModel glisur                    # Modèle optique pour surface : glisur, unified
/SCOPSim/geometry/setLMOSurfaceType dielectric_dielectric      # Type de surface : dielectric-dielectric, dielectric-metal
/SCOPSim/geometry/setLMOSurfaceFinish ground                   # Finition de surface : ground, polished
/SCOPSim/geometry/setLMOSurfacePolish 1.0                      # Avec le moèle glisur : Définit la proportion de surface polie/dépolie [0 ; 1]
/SCOPSim/geometry/setLMOSurfaceSigmaAlpha 0.1                  # Avec le modèle unified : Définit le RMS de l'angle des microfacettes

/run/reinitializeGeometry
/run/physicsModified

# Photon Tracking (Batch, pas de VIS)
/tracking/storeTrajectory 1
/SCOPSim/step/setVerbose 0
/SCOPSim/step/setPhotonTrackStatus true

/tracking/verbose 0
/run/verbose 1

# GPS - Générateur de Particules
/gps/number 1
/gps/particle e-
/gps/pos/type Point
/gps/pos/centre 0.0 0.0 -100.0 mm
/gps/direction 0.0 0.0 1.0
/gps/energy 2. MeV
```

**Usage**:
```bash
cd build

# Batch automatique (4 threads, 1000 événements)
./SCOPSim output 1000 vrml.mac ON 4
# → Résultat: Resultats/output.root
```

**Avantages**:
- ✅ Pas d'interface graphique → ~10x plus rapide
- ✅ Support multi-threading (4-20x speedup)
- ✅ Sortie ROOT complète avec statistiques
- ✅ Idéal pour production de données

---

### 📋 Commandes Geant4 Courantes

| Commande | Description | Exemple |
|----------|-------------|---------|
| `/run/beamOn N` | Lance N événements | `/run/beamOn 100` |
| `/control/execute file.mac` | Exécute un autre macro | `/control/execute autre.mac` |
| `/gps/particle TYPE` | Type de particule | `/gps/particle proton` |
| `/gps/energy E` | Énergie cinétique | `/gps/energy 5.5 MeV` |
| `/gps/pos/centre x y z` | Position source | `/gps/pos/centre 0 0 -50 mm` |
| `/gps/direction dx dy dz` | Direction (normalisé) | `/gps/direction 0 0 1` |
| `/geometry/test/run` | Test de cohérence géométrie | `/geometry/test/run` |
| `/process/list` | Liste processus physiques | `/process/list` |
| `/tracking/verbose N` | Verbosité tracking (0-2) | `/tracking/verbose 1` |
| `/material/print` | Affiche matériaux | `/material/print` |

### 📊 Types de Particules (GPS)

| Code | Particule | Charge | Masse |
|------|-----------|--------|-------|
| `e-` | Électron | -1 | 0.511 MeV |
| `e+` | Positron | +1 | 0.511 MeV |
| `proton` | Proton | +1 | 938.3 MeV |
| `alpha` | Particule Alpha | +2 | 3728 MeV |
| `gamma` | Photon | 0 | 0 |
| `neutron` | Neutron | 0 | 939.6 MeV |

---

## 🔧 Composants Core

### 1. **SCOPSimGeometryConstruction.cc**  [!!!! TO UPDATE !!!!]

**Responsabilité**: Construire la géométrie complète du détecteur

**Méthodes principales**:

```cpp
G4VPhysicalVolume* Construct()
```
- Nettoie les géométries précédentes
- Crée les volumes monde et conteneur
- Construit les composants détecteur
- Configure les surfaces optiques

```cpp
void CreateWorldAndHolder()
```
- **Monde**: 2.1m × 15.1m × 2.1m (vide)
- **Conteneur**: 2.05m × 15.05m × 2.05m

```cpp
void ConstructZnS()
```
- Crée volume scintillateur ZnS:Ag
- Configure Light Yield (LY) via table de matériaux
- Couleur de visualisation : noir

```cpp
void ConstructScintillator()
```
- Crée volume scintillateur plastique EJ212
- Configure LY et propriétés optiques
- Positionné au-dessus de ZnS avec espacement

```cpp
void ConstructPMTGlass() & CreateDetectionOpticalProperties()
```
- Crée enveloppe PMT (5-inch)
- Charge QE (Quantum Efficiency) depuis `QE_ham_GA0154.txt`
- Configure surface optique: interface diélectrique-métal
- QE effective: `0.64 × QE_fichier × 0.65`

**Disposition géométrique**:
```
   PMT Photocathode
        ↑ (DetectorDistance)
   PMT Glass envelope
        ↑ (optically coupled)
   Scintillator EJ212 (cyan)
        ↑ (optically coupled)
   ZnS:Ag (noir)
```

---

### 2. **SCOPSimEventAction.cc** [!!!! TO UPDATE !!!!]

**Responsabilité**: Agrégation des statistiques par événement

```cpp
void BeginOfEventAction(const G4Event *evt)
```
- Réinitialise les compteurs par événement
- Prépare les tallies (ZnS, Scintillateur, Optique)

```cpp
void EndOfEventAction(const G4Event *evt)
```
- Transfère les données événement → RunAction
- Calcule les efficacités
- Agrège les statistiques de photons
- Affiche résumé événement (optionnel verbose)

**Statistiques suivies**:
- `incident_energy`: Énergie incidente [MeV]
- `deposited_energy_zns`: Énergie dépôt ZnS [keV]
- `deposited_energy_sc`: Énergie dépôt scintillateur [keV]
- `photons_generated`: Photons scintillation + Cerenkov
- `photons_detected`: Photons détectés par PMT
- `photons_absorbed`: Absorption par surface
- `photons_escaped`: Photons quittant la géométrie

---

### 3. **SCOPSimSteppingAction.cc** [!!!! TO UPDATE !!!!]

**Responsabilité**: Suivi détaillé particule à chaque étape

```cpp
void UserSteppingAction(const G4Step *aStep)
```

**Logique principale**:
1. Extrait info étape (positions, énergies, directeurs)
2. Détecte particule incidente (étape 1, primaire)
3. Suivi dépôt d'énergie scintillateurs
4. Gère interactions photons optiques
5. Détecte processus de frontière (réflexions, absorption, détection)
6. Tue particules sortant du monde

**Informations par étape extraites**:
```cpp
particleName          // "proton", "opticalphoton", etc.
particleID            // PDG encoding
stepNo                // Numéro étape dans la trace
energy                // Énergie cinétique pré-étape [MeV]
energy_post           // Énergie post-étape [MeV]
energyDeposited       // Énergie perdue cette étape [keV]
preStep.{x,y,z}       // Position pré-étape [mm]
postStep.{x,y,z}      // Position post-étape [mm]
volumeNamePreStep     // Nom volume courant
volumeNamePostStep    // Nom volume suivant
```

```cpp
void CheckBoundaryStatus(const G4Step *aStep, SCOPSimEventAction *evtac)
```

**Processus optiques trackés**:
- **Detection**: Photon détecté par PMT → `CountDetected()`
- **Absorption**: Absorption surface/frontière → `CountAbsorbed()`
- **OpAbsorption**: Absorption bulk matériau → `CountBulkAbs()`
- **NoRINDEX**: Photon échappe (pas indice réfraction) → `CountEscaped()`
- **Reflections**: Fresnel, Lambertian, TIR

---

### 4. **SCOPSimRunAction.cc** [!!!! TO UPDATE !!!!]

**Responsabilité**: Agrégation statistiques au niveau du run

**Responsabilités**:
- Initialise fichier ROOT et structure arborescence
- Agrège statistiques événement → histogrammes run
- Calcule métriques efficacité
- Écrit fichier ROOT final avec données complètes

---

### 5. **SCOPSimMaterials.cc** [!!!! TO UPDATE !!!!]

**Responsabilité**: Base de données matériaux et propriétés optiques

**Matériaux définis**:
- **Vacuum/VacuumWorld**: Faible densité, pas interactions
- **ZnS:Ag**: Scintillateur zinc sulfide activé argent
- **EJ212**: Scintillateur plastique (BC412 équivalent)
- **bs_glass**: Verre borosilicate (enveloppe PMT)
- **Photocathode**: Matériau virtuel pour surface détection
- **Teflon/Mylar**: Revêtements réflectifs optiques

**Propriétés par matériau**:
- Indice réfraction (dépendant longueur d'onde)
- Longueur absorption
- Light Yield scintillation [photons/MeV]
- Temps décroissance scintillation
- Propriétés surface optique (réflectivité, finition)

---

## 📈 Flux de Données & Statistiques [!!!! TO UPDATE !!!!]

### Flux par Étape

```
┌─────────────────────────────────────────────────────┐
│ SteppingAction (Par étape)                          │
│ - Extrait position, momentum, énergie dépôt         │
│ - Suivi scintillateurs → tally énergie              │
│ - Suivi photons optiques → statut frontière         │
└────────────────┬────────────────────────────────────┘
                 │
                 ↓
┌─────────────────────────────────────────────────────┐
│ EventAction (Fin d'événement)                       │
│ - Agrège données étapes                             │
│ - Calcule totaux & efficacités                      │
│ - Passe au RunAction                                │
└────────────────┬────────────────────────────────────┘
                 │
                 ↓
┌─────────────────────────────────────────────────────┐
│ RunAction (Fin du run)                              │
│ - Accumule événements en arbre ROOT                 │
│ - Remplit histogrammes & branches                   │
│ - Écrit fichier ROOT output                         │
└─────────────────────────────────────────────────────┘
```

### Statistiques Collectées

| Quantité | Source | Unité | Description |
|----------|--------|-------|-------------|
| `incident_energy` | SteppingAction step 1 | MeV | Énergie particule incidente |
| `deposited_energy_total` | EventAction | keV | Somme énergies dépôt |
| `deposited_energy_zns` | ZnS tally | keV | Dépôt ZnS uniquement |
| `deposited_energy_sc` | Scintillateur tally | keV | Dépôt scintillateur EJ212 |
| `photons_generated_total` | SteppingAction scintillation | count | Scintillation + Cerenkov |
| `photons_detected` | CheckBoundaryStatus detection | count | Photons touchant photocathode |
| `photons_absorbed` | CheckBoundaryStatus absorption | count | Absorption surface |
| `photons_escaped` | CheckBoundaryStatus NoRINDEX | count | Photons quittant géométrie |
| `efficiency` | EventAction | % | photons_detected / photons_generated_total |
| ....
| ....

---

## 💾 Sortie ROOT

### Structure Fichier

**Fichier**: `Resultats/output.root`

**Contenu**: Arbre TTree `SCOPSim`

```cpp
// Branches disponibles
Float_t incident_energy;           // [MeV]
Float_t deposited_energy_total;    // [keV]
Float_t deposited_energy_zns;      // [keV]
Float_t deposited_energy_sc;       // [keV]
Int_t photons_generated_total;
Int_t photons_detected;
Int_t photons_absorbed;
Int_t photons_escaped;
Float_t efficiency;                // [%]
```

### Analyse ROOT

```cpp
// Charger et analyser les résultats
root [0] TFile *f = TFile::Open("Resultats/output.root");
root [1] TTree *t = (TTree*)f->Get("SCOPSim");

// Afficher statistiques basiques
root [2] t->Print();

// Histogramme photons détectés
root [3] t->Draw("photons_detected >> h_detected", "", "hist");

// Courbe efficacité vs énergie
root [4] t->Draw("efficiency:incident_energy", "", "scatter");

// Statistiques colonne
root [5] t->GetLeaf("efficiency")->GetBranch()->GetHistogram()->Draw();

// Analyse avancée
root [6] TH2F *h2 = new TH2F("h2", "", 50, 0, 10, 50, 0, 100);
root [7] t->Draw("efficiency:incident_energy>>h2", "", "colz");
```

### Multi-threading Output

Lorsque MT est activé (ON), le processus génère:
```
Resultats/
├── output_1.root           # Thread 1 (par ex. 250 événements)
├── output_2.root           # Thread 2 (250 événements)
├── output_3.root           # Thread 3 (250 événements)
├── output_4.root           # Thread 4 (250 événements)
└── output.root             # Fichier final fusionné (1000 événements)
```

Les fichiers partiels sont automatiquement fusionnés avec `hadd` à la fin.

---

## 🐛 Dépannage

| Problème | Cause | Solution |
|----------|-------|----------|
| "Error opening file" (matériaux) | Fichiers matériaux manquants | Vérifier `simulation_input_files/` exists & accessible |
| Erreur compilation Geant4 | Geant4 compilé sans GDML | Recompiler: `cmake -DGEANT4_USE_GDML=ON` |
| Performance très lente | Suivi photons optiques activé | Batch mode: `/SCOPSim/step/setPhotonTrackStatus false` |
| Aucun photon détecté | QE fichier incorrect | Vérifier `QE_ham_GA0154.txt` path |
| Géométrie ne s'affiche pas | Drivers OpenGL manquants | Installer dépendances: `libgl1-mesa-dev` (Linux) |
| Crash multi-threading | Conflit données partagées | Utiliser mono-thread d'abord pour déboguer |
| ROOT file corrupted | Write error pendant exécution | Vérifier espace disque disponible |

---

## 📚 Documentation API

Documentation Doxygen complète disponible:

**Générer la documentation**:
```bash
doxygen Doxyfile
```

**Accéder à la documentation**:
- Local: `docs/html/index.html`
- Online: [📖 Doxygen Docs](https://ahuber33.github.io/Projet_Instru_Contaminametre_AlphaBeta/)

**Contenu documenté**:
- Classes et fonctions API complètes
- Diagrammes de classe
- Flux de données
- Exemples d'utilisation

---

## 📋 Fichiers Clés

| Fichier | Type | Responsabilité |
|---------|------|-----------------|
| `SCOPSim.cc` | Main | Entrée point, argument parsing, threading |
| `SCOPSimGeometryConstruction.cc` | Geometry | Géométrie détecteur |
| `SCOPSimMaterials.cc` | Materials | Base données matériaux |
| `SCOPSimEventAction.cc` | Action | Agrégation événement |
| `SCOPSimSteppingAction.cc` | Action | Suivi détaillé étape |
| `SCOPSimRunAction.cc` | Action | Agrégation run, sortie ROOT |
| `SCOPSimPhysics.cc` | Physics | Liste processus physiques |
| `Geometry.cc` | Utilities | Utilitaires géométrie |
| `bin/vis.mac` | Macro | Visualisation interactive |
| `bin/vrml.mac` | Macro | Batch sans GUI |

---

## ⚙️ Configuration Recommandée

### Pour Développement
```bash
# Visualisation interactive pour déboguer géométrie
./SCOPSim debug_output vis.mac

# Single-thread pour reproductibilité
./SCOPSim output 100 vrml.mac OFF
```

### Pour Production
```bash
# Multi-threading pour vitesse
./SCOPSim production_run 10000 vrml.mac ON 8

```

### Paramètres Physiques Critiques

**Impactent directement les résultats**:
- **Light Yield (LY)**: Plus élevé → plus de photons
  - ZnS:Ag: 44000 photons/MeV (très élevé)
  - EJ212: 10000 photons/MeV (modéré)
- **DetectorDistance**: Distance PMT-scintillateur
  - Plus grand → plus d'absorption optique
- **Particle Energy**: Énergie particule incidente
  - Détermine ionisation & génération photons

---

## 👥 Contribuer

Pour contribuer:
1. Fork le repository
2. Créer une branche feature
3. Commiter les changements
4. Pousser et créer Pull Request

---

## 📞 Contact & Support

**Auteur**: Arnaud HUBER  
**Auteur**: Lucas FEDERSPIEL  
**Email**: huber@lp2ib.in2p3.fr  
**Email**: federspi@lp2ib.in2p3.fr  
**Institution**: LP2IB, IN2P3/CNRS

---

## 📜 Licence

GEANT4 Collaboration License

Voir le fichier `LICENSE` pour les détails complets.

---

## 🔗 Ressources Externes

- **Geant4**: https://geant4.web.cern.ch/
- **ROOT**: https://root.cern.ch/
- **CLHEP**: https://proj-clhep.web.cern.ch/proj-clhep/

---

**Dernière mise à jour**: 29 Avril 2026  
**Version**: 1.0
