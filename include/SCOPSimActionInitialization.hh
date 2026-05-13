#ifndef SCOPSimActionInitialization_h
#define SCOPSimActionInitialization_h 1

/**
 * @class SCOPSimActionInitialization
 * @brief Class to initialize user actions in the Optical simulation.
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 *
 * This class inherits from G4VUserActionInitialization and defines
 * actions to be performed at the start of the simulation, including
 * primary particle generation and event/run actions. It supports
 * multithreading and keeps track of simulation parameters such as
 * the number of events and thread index.
 */

#include "G4VUserActionInitialization.hh"
#include "SCOPSimEventAction.hh"
#include "SCOPSimGeometryConstruction.hh"
#include "SCOPSimPrimaryGeneratorAction.hh"
#include "SCOPSimRunAction.hh"
#include "SCOPSimSteppingAction.hh"

class SCOPSimGeometryConstruction;
class SCOPSimPrimaryGeneratorAction;

class SCOPSimActionInitialization
    : public G4VUserActionInitialization {
  public:
    /**
     * @brief Constructor
     * @param name Name identifier for the simulation run
     * @param nEvents Number of events to generate
     * @param nThreads Number of threads for multithreading
     * @param flagMT True if multithreading is enabled
     * @param geometry Pointer to the geometry construction object
     */
    SCOPSimActionInitialization(
        const char *name, size_t nEvents, size_t nThreads, bool flagMT,
        SCOPSimGeometryConstruction *geometry);

    /// @brief Destructor
    virtual ~SCOPSimActionInitialization();

    /**
     * @brief Build actions for master thread (multithreading mode)
     *
     * In Geant4, the master thread only manages run-level actions.
     */
    virtual void BuildForMaster() const override;

    /**
     * @brief Build actions for worker threads or sequential mode
     *
     * This function sets up primary generator actions, run actions,
     * and event actions.
     */
    virtual void Build() const override;

    /// @brief Pointer to the string storing the number of events
    char *NEvents;

    /// @brief Suffix used for file/output identification
    G4String suffixe;

    /// @brief Total number of events generated
    size_t NEventsGenerated;

    /// @brief Number of threads in multithreading
    size_t numThreads;

    /// @brief Flag to indicate multithreading mode
    G4bool flag_MT = false;

  private:
    /// @brief Pointer to the geometry construction object
    SCOPSimGeometryConstruction *fGeometry;
};

#endif
