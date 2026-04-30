/**
 * @file OpSimEventAction.cc
 * @brief Implementation of the EventAction class for the OpSim of
 * an alpha/beta contamineter.
 *
 * This file defines the OpSimEventAction class, which handles
 * per-event actions in the Geant4 simulation of the OpSim setup.
 *
 * The class works in conjunction with:
 *  - OpSimSteppingAction: for per-step updates within an event.
 *  - OpSimRunAction: to accumulate run-level statistics.
 *
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 */

#include "OpSimEventAction.hh" ///< Event action header
#include "OpSimRunAction.hh" ///< Run action header (for statistics accumulation)
#include "OpSimSteppingAction.hh" ///< Stepping action header (per-step updates)

/**
 * @brief Constructor for OpSimEventAction
 * @param suff Suffix used for naming ROOT branches or output files
 *
 * Initializes the event action and stores the provided suffix.
 */
OpSimEventAction::OpSimEventAction(const char *suff)
    : suffixe(suff) {}

/**
 * @brief Destructor for OpSimEventAction
 *
 * Cleans up any resources used by the event action.
 */
OpSimEventAction::~OpSimEventAction() {}

/**
 * @brief Called at the beginning of each event
 * @param evt Pointer to the current G4Event
 *
 * Resets all per-event statistics and counters to initial empty states.
 * This includes:
 * - Input statistics
 * - Optical statistics
 * - LMO Statistics
 * - Scintillator statistics
 */
void OpSimEventAction::BeginOfEventAction(const G4Event *evt) {
    /** Reset input statistics */
    StatsInput = {};
    StatsOptical = {};

    /** Reset Beam Stop (BS) and BSPEC YAG detector statistics */
    StatsLMO = {};
}

/**
 * @brief Called at the end of each event
 * @param evt Pointer to the current G4Event
 *
 * Updates run-level statistics by passing the per-event data to the
 * OpSimRunAction. Only non-empty or relevant data are updated
 * for input, BS YAG, and BSPEC YAG statistics, while quadrupole and
 * collimator statistics are always updated.
 */
void OpSimEventAction::EndOfEventAction(const G4Event *evt) {
    /** Get pointer to current run action */
    OpSimRunAction *runac =
        (OpSimRunAction *)(G4RunManager::GetRunManager()
                                           ->GetUserRunAction());

    //G4cout<<"-/-/-/-/-/-/-/-/-/-/-/- Energy deposit in LD = "<<OpSimEventAction::GetEnergyDepositLD()<<" keV -/-/-/-/-/-/-/-/-/-/-/-"<<G4endl;

    /** Update input energy statistics if valid */
    if (StatsInput.energy > 0)
        runac->UpdateStatisticsInput(StatsInput);

    /** Update Beam Stop YAG statistics if not empty */
    if (!StatsLMO.energy.empty())
        runac->UpdateStatisticsLMO(StatsLMO);

    if (StatsOptical.ScintillationLMO < 0) {
        StatsOptical.IncidentE = StatsInput.energy;
        StatsOptical.DepositLMO = StatsLMO.deposited_energy_event;
        StatsOptical.DepositTotal = StatsLMO.deposited_energy_event;
        StatsOptical.GeneratedLMO = StatsOptical.ScintillationLMO + StatsOptical.CerenkovLMO;
        StatsOptical.GeneratedTotal = StatsOptical.GeneratedLMO;

        StatsOptical.BulkAbsTotal = StatsOptical.BulkAbsLMO;

        float Absfrac =
            100 * StatsOptical.Absorbed / StatsOptical.GeneratedTotal;
        float BulkfracLMO =
            100 * StatsOptical.BulkAbsLMO / StatsOptical.GeneratedTotal;
        float BulkfracTotal = BulkfracLMO;
        float Escfrac =
            100 * StatsOptical.Escaped / StatsOptical.GeneratedTotal;
        float Failfrac =
            100 * StatsOptical.Failed / StatsOptical.GeneratedTotal;
        float Killedfrac =
            100 * StatsOptical.Killed / StatsOptical.GeneratedTotal;

        // Output the results
    }
    runac->UpdateStatisticsOptical(StatsOptical);
}
