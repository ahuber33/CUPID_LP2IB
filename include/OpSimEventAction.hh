#ifndef OpSimEventAction_h
#define OpSimEventAction_h 1

/**
 * @class OpSimEventAction
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 * @brief Header file for event-level actions in OpSim, including
 * per-event statistics structures.
 */

#include "G4String.hh"
#include "G4Types.hh"
#include "G4UserEventAction.hh"
#include <TBranch.h>
#include <TTree.h>
#include <vector>

class G4Event;

/**
 * @brief Structure to store per-event input particle data
 *
 * Holds position, direction, and energy information for the particle at the
 * start of the event.
 */
struct RunTallyInput {
    float x = 0.0;
    float xp = 0.0;
    float y = 0.0;
    float yp = 0.0;
    float z = 0.0;
    float zp = 0.0;
    float energy = 0.0;
};

// This struct carries statistics OPTICAL part
struct RunTallyOptical {
    float IncidentE;
    float DepositTotal;
    float DepositLMO;
    G4int GeneratedTotal;
    G4int GeneratedLMO;
    G4int ScintillationLMO;
    G4int CerenkovLMO;
    G4int ReemissionLMO;
    G4int BulkAbsTotal;
    G4int BulkAbsLMO;
    G4int Absorbed;
    G4int Escaped;
    G4int Failed;
    G4int Killed;
    G4int DetectedLD1;
    G4int DetectedLD2;
    G4int DetectedTotal;
    G4int ReflectedLMOTopBot;
    G4int ReflectedLMOSides;
    std::vector<float> ExitLightPositionX;
    std::vector<float> ExitLightPositionY;
    std::vector<float> ExitLightPositionZ;
    std::vector<float> DetectorPositionX;
    std::vector<float> DetectorPositionY;
    std::vector<float> DetectorPositionZ;
    std::vector<float> BirthWavelength;
    std::vector<float> DetectedWavelengthLD1;
    std::vector<float> DetectedWavelengthLD2;
    std::vector<float> DetectedTrackLengthLD1;
    std::vector<float> DetectedTrackLengthLD2;
    std::vector<float> AbsorbedTrackLength;
    std::vector<float> IncidentAngleSurfx;
    std::vector<float> IncidentAngleSurfy;
    std::vector<float> IncidentAngleSurfz;
    std::vector<float> Time;
    std::vector<int> Rayleigh;
    std::vector<int> Total_Reflections;
    std::vector<int> Wrap_Reflections;
    std::vector<float> TotalLength;
    std::vector<float> Angle_creation;
    std::vector<float> Angle_detection;
    std::vector<int> FinalState;

    inline G4int operator==(const RunTallyOptical &right) const {
        return (this == &right);
    }
};

/**
 * @brief Structure for YAG detector statistics
 *
 * Tracks exit coordinates, particle IDs, energies, deposited energy, and flags.
 */
struct RunTallySc {
    std::vector<float> x_entrance;
    std::vector<float> y_entrance;
    std::vector<float> z_entrance;
    std::vector<int> parentID;
    std::vector<int> particleID;
    std::vector<float> energy;
    float deposited_energy = 0.0;
    float deposited_energy_event = 0.0;
    std::vector<float> total_deposited_energy;
    G4bool flag = false;

    // Methods to add data
    void AddXEntrance(float d) { x_entrance.push_back(d); }
    void AddYEntrance(float d) { y_entrance.push_back(d); }
    void AddZEntrance(float d) { z_entrance.push_back(d); }
    void AddParentID(int d) { parentID.push_back(d); }
    void AddParticleID(int d) { particleID.push_back(d); }
    void AddEnergy(float d) { energy.push_back(d); }
    void AddDepositedEnergyEvent(float d) { deposited_energy_event += d; }
    void AddDepositedEnergy(float d) { deposited_energy += d; }
    void AddTotalDepositedEnergy(float d) {
        total_deposited_energy.push_back(d);
    }

    // Size accessors
    size_t XEntranceSize() const { return x_entrance.size(); }
    size_t YEntranceSize() const { return y_entrance.size(); }
    size_t ZEntranceSize() const { return z_entrance.size(); }
    size_t ParentIDSize() const { return parentID.size(); }
    size_t ParticleIDSize() const { return particleID.size(); }
    size_t EnergySize() const { return energy.size(); }
    size_t TotalDepositedEnergySize() const {
        return total_deposited_energy.size();
    }

    // Index accessors
    float GetXEntrance(size_t i) const { return x_entrance.at(i); }
    float GetYEntrance(size_t i) const { return y_entrance.at(i); }
    float GetZEntrance(size_t i) const { return z_entrance.at(i); }
    int GetParentID(size_t i) const { return parentID.at(i); }
    int GetParticleID(size_t i) const { return particleID.at(i); }
    float GetEnergy(size_t i) const { return energy.at(i); }
    float GetTotalDepositedEnergy(size_t i) const {
        return total_deposited_energy.at(i);
    }
    float GetTotalDepositedEnergyEvent() const {
        return deposited_energy_event;
    }

    // Flags
    void ActivateFlag() { flag = true; }
    void ResetFlag() { flag = false; }
    G4bool ReturnFlag() const { return flag; }

    void ResetDepositedEnergy() { deposited_energy = 0; }
    float GetDepositedEnergy() const { return deposited_energy; }
};

/**
 * @brief Event action class for OpSim
 *
 * Implements G4UserEventAction interface to handle per-event statistics,
 * including input particle, collimator, quadrupole, and detector data.
 */
class OpSimEventAction : public G4UserEventAction {
  public:
    /** Constructor */
    OpSimEventAction(const char *);

    /** Destructor */
    ~OpSimEventAction();

    /** Called at the beginning of each event */
    void BeginOfEventAction(const G4Event *);

    /** Called at the end of each event */
    void EndOfEventAction(const G4Event *);

    /** Setters for input particle data */
    void SetXStart(G4float d) { StatsInput.x = d; }
    void SetXpStart(G4float d) { StatsInput.xp = d; }
    void SetYStart(G4float d) { StatsInput.y = d; }
    void SetYpStart(G4float d) { StatsInput.yp = d; }
    void SetZStart(G4float d) { StatsInput.z = d; }
    void SetZpStart(G4float d) { StatsInput.zp = d; }
    void SetEnergyStart(G4float d) { StatsInput.energy = d; }

    // ░█████╗░██████╗░████████╗██╗░█████╗░░█████╗░██╗░░░░░
    // ██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗██╔══██╗██║░░░░░
    // ██║░░██║██████╔╝░░░██║░░░██║██║░░╚═╝███████║██║░░░░░
    // ██║░░██║██╔═══╝░░░░██║░░░██║██║░░██╗██╔══██║██║░░░░░
    // ╚█████╔╝██║░░░░░░░░██║░░░██║╚█████╔╝██║░░██║███████╗
    // ░╚════╝░╚═╝░░░░░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚═╝╚══════╝

    // Functions for Optical Tree
    void CountCerenkovLMO() { StatsOptical.CerenkovLMO++; }
    void CountScintillationLMO() { StatsOptical.ScintillationLMO++; }
    void CountReemissionLMO() { StatsOptical.ReemissionLMO++; }
    void CountKilled() { StatsOptical.Killed++; }
    int GetKilled() { return StatsOptical.Killed; }
    void CountDetectedLD1() { StatsOptical.DetectedLD1++; StatsOptical.DetectedTotal++;}
    void CountDetectedLD2() { StatsOptical.DetectedLD2++; StatsOptical.DetectedTotal++;}
    int GetDetected() { return StatsOptical.DetectedTotal; }
    // void CountWLS(){StatsOptical.WLS++;}
    void CountAbsorbed() { StatsOptical.Absorbed++; }
    int GetAbsorbed() { return StatsOptical.Absorbed; }
    void CountBulkAbsLMO() { StatsOptical.BulkAbsLMO++; }
    int GetBulkAbsLMO() { return StatsOptical.BulkAbsLMO; }
    void CountEscaped() { StatsOptical.Escaped++; }
    int GetEscaped() { return StatsOptical.Escaped; }
    void CountFailed() { StatsOptical.Failed++; }
    void CountReflectedLMOTopBot() { StatsOptical.ReflectedLMOTopBot++; }
    void CountReflectedLMOSides() { StatsOptical.ReflectedLMOSides++; }
    int GetFailed() { return StatsOptical.Failed; }
    void FillPhotonExitLightPositionX(float e) {
        StatsOptical.ExitLightPositionX.push_back(e);
    }
    void FillPhotonExitLightPositionY(float e) {
        StatsOptical.ExitLightPositionY.push_back(e);
    }
    void FillPhotonExitLightPositionZ(float e) {
        StatsOptical.ExitLightPositionZ.push_back(e);
    }
    void FillPhotonDetectorPositionX(float e) {
        StatsOptical.DetectorPositionX.push_back(e);
    }
    void FillPhotonDetectorPositionY(float e) {
        StatsOptical.DetectorPositionY.push_back(e);
    }
    void FillPhotonDetectorPositionZ(float e) {
        StatsOptical.DetectorPositionZ.push_back(e);
    }
    void FillPhotonFinalState(G4int e) { StatsOptical.FinalState.push_back(e); }
    void FillBirthWavelength(float e) {
        StatsOptical.BirthWavelength.push_back(e);
    }
    void FillDetectedWavelengthLD1(float e) {
        StatsOptical.DetectedWavelengthLD1.push_back(e);
    }
    void FillDetectedWavelengthLD2(float e) {
        StatsOptical.DetectedWavelengthLD2.push_back(e);
    }
    void FillDetectedTrackLengthLD1(float e) {
        StatsOptical.DetectedTrackLengthLD1.push_back(e);
    }
    void FillDetectedTrackLengthLD2(float e) {
        StatsOptical.DetectedTrackLengthLD2.push_back(e);
    }
    void FillAbsorbedTrackLength(float e) {
        StatsOptical.AbsorbedTrackLength.push_back(e);
    }
    void FillIncidentAngleSurfx(float e) {
        StatsOptical.IncidentAngleSurfx.push_back(e);
    }
    void FillIncidentAngleSurfy(float e) {
        StatsOptical.IncidentAngleSurfy.push_back(e);
    }
    void FillIncidentAngleSurfz(float e) {
        StatsOptical.IncidentAngleSurfz.push_back(e);
    }
    void FillPhotonTime(float e) { StatsOptical.Time.push_back(e); }
    void FillRayleigh(int e) { StatsOptical.Rayleigh.push_back(e); }
    void FillTotalReflections(int e) {
        StatsOptical.Total_Reflections.push_back(e);
    }
    void FillWrapReflecions(int e) {
        StatsOptical.Wrap_Reflections.push_back(e);
    }
    void FillPhotonTotalLength(float e) {
        StatsOptical.TotalLength.push_back(e);
    }
    void FillFiberAngleCreation(float e) {
        StatsOptical.Angle_creation.push_back(e);
    }

    void FillFiberAngleDetection(float e) {
        StatsOptical.Angle_detection.push_back(e);
    }
    void SetAirIndex(float a) { Air_Index = a; }
    float GetAirIndex() { return Air_Index; }

    void AddEnergyDepositLMO(float d){energy_deposit_electron_LMO += d; }

    /** Accessors for generic detector statistics */
    RunTallySc &GetLMO() { return StatsLMO; }

  private:
    TTree *EventTree;         ///< ROOT tree for per-event data
    TBranch *EventBranch;     ///< ROOT branch for event tree
    RunTallyInput StatsInput; ///< Input particle statistics
    RunTallySc StatsLMO;      ///< Beam Stop LMO detector statistics
    G4String suffixe;      ///< Suffix for output naming
    RunTallyOptical StatsOptical;
    float Photon_creation_angle = 0.0;
    float Photon_creation_lambda = 0.0;
    float Air_Index = 0.0;
    float Absfrac = 0.0;
    float BulkfracLMO = 0.0;
    float Escfrac = 0.0;
    float Failfrac = 0.0;
    float efficiency = 0.0;
    G4int GeneratedLMO = 0;
    G4int Generated = 0;
    G4int Scintillation = 0;
    G4int Cerenkov = 0;
    float Deposit = 0.0;
    G4bool VerbosityResults = false;
    float energy_deposit_LD_event = 0.0;
    float energy_deposit_electron_LMO  = 0.0;
};

#endif
