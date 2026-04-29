#ifndef SimOpRunAction_h
#define SimOpRunAction_h 1

/**
 * @class SimOpRunAction
 * @brief Defines the run-level actions and statistics handling for the PALLAS
 * simulation.
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 *
 * This header declares the `SimOpRunAction` class, which inherits
 * from Geant4's `G4UserRunAction` to manage actions at the beginning and end of
 * each run. It handles:
 *  - Collection and storage of run-wide statistics
 *  - ROOT file and tree creation for data output
 *  - Synchronization in multithreaded runs
 *  - Coordination with primary generator and geometry configuration
 *
 *
 * Data recorded here typically includes:
 *  - Initial parameters
 *  - EM Informations for LMO & Scintillator
 *  - Optical Informations for LMO & Scintillator
 *
 * @note This class interacts closely with:
 *       - `SimOpPrimaryGeneratorAction`
 *       - `SimOpGeometryConstruction`
 */

// Include base classes and Geant4 utilities
#include "G4Run.hh" // Run object for event accumulation
#include "G4RunManager.hh"
#include "G4UImanager.hh"     // UI manager (for commands)
#include "G4UserRunAction.hh" // Base class for user-defined run actions
#include "G4VVisManager.hh"   // Visualization manager
#include "SimOpEventAction.hh"
#include "SimOpGeometryConstruction.hh"
#include "SimOpPrimaryGeneratorAction.hh"
#include "TBranch.h"
#include "TFile.h" // ROOT file I/O
#include "TTree.h"
#include <mutex>

// Forward declarations
class SimOpPrimaryGeneratorAction;
class SimOpGeometryConstruction;

/**
 * @class SimOpRunAction
 * @brief Manages run-level actions, statistics, and ROOT output.
 */
class SimOpRunAction : public G4UserRunAction {
  public:
    /**
     * @brief Constructor
     * @param fileName Base name for ROOT output file
     * @param nEventsGenerated Number of events to process
     * @param multithreaded True if running with multithreading
     */
    SimOpRunAction(const char *fileName, size_t nEventsGenerated,
                               G4bool multithreaded);

    /// Destructor
    ~SimOpRunAction();

    /// Called at the start of each run
    void BeginOfRunAction(const G4Run *run) override;

    /// Called at the end of each run
    void EndOfRunAction(const G4Run *run) override;

    /// Generic template to update cumulative statistics in a ROOT tree
    template <typename T>
    static void UpdateStatistics(T &stats, const T &newStats, TTree *tree);

    // --- Specific statistics update methods ---
    void UpdateStatisticsInput(RunTallyInput);
    void UpdateStatisticsLMO(RunTallySc);
    void UpdateStatisticsOptical(RunTallyOptical);

    /// Set the primary generator reference
    void SetPrimaryGenerator(SimOpPrimaryGeneratorAction *gen);

    /// Set the geometry reference
    void SetGeometry(SimOpGeometryConstruction *geom);

  private:
    // --- Output configuration ---
    G4String suffixe;  ///< File suffix for ROOT outputs
    G4String fileName; ///< Base file name for ROOT outputs

    // --- Stored run statistics ---
    RunTallyInput StatsInput;
    RunTallySc StatsLMO;
    RunTallyOptical StatsOptical;

    size_t NEventsGenerated; ///< Number of events generated in the run
    G4bool flag_MT;          ///< Multithreading enabled flag

    // --- ROOT file and trees ---
    TFile *f = nullptr;
    TTree *Tree_Input = nullptr;
    TTree *Tree_LMO = nullptr;
    TTree *Tree_Optical = nullptr;
    TBranch *RunBranch = nullptr;

    time_t start; ///< Start time of the run

    // --- Thread-safety ---
    static std::atomic<int> activeThreads;
    static G4Mutex fileMutex;

  protected:
    SimOpPrimaryGeneratorAction *fPrimaryGenerator =
        nullptr; ///< Primary generator reference
    SimOpGeometryConstruction *fGeometry =
        nullptr; ///< Geometry reference
};

#endif // SimOpRunAction_h