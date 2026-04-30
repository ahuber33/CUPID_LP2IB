#include "OpSimGeometryMessenger.hh"

/**
 * @file OpSimGeometryMessenger.cc
 * @brief Implementation of the GeometryMessenger class for the
 * OpSim.
 *
 * This file defines the OpSimGeometryMessenger class, which
 * inherits from G4UImessenger. It provides an interface for the Geant4 UI to
 * control geometry and field parameters for the OpSim simulation.
 *
 * Responsibilities include:
 *  - Creating UI directories and commands for geometry, and materials
 *  - Setting geometry parameters such as LMO & Scintillator dimensions
 *  - Passing user-specified values to the OpSimGeometryConstruction
 * class.
 *
 * Each UI command is linked to a setter function in the geometry construction
 * to update the simulation configuration dynamically.
 *
 * The messenger also provides functions to:
 *  - Retrieve current command values for UI display.
 *  - Delete all UI commands upon destruction to free memory.
 *
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/**
 * @brief Constructor
 * @param aDetector Pointer to the OpSim geometry construction class
 *
 * This constructor initializes all UI commands and directories for geometry,
 * display, and field control.
 */
OpSimGeometryMessenger::OpSimGeometryMessenger(
    OpSimGeometryConstruction *aDetector)
    : G4UImessenger(), fGeometry(aDetector) {
    // Create a main directory for all UI commands related to OpSim
    fExampleDir = new G4UIdirectory("/OpSim/");
    fExampleDir->SetGuidance("UI commands specific to this example");

    // Create sub-directory for geometry-related commands
    fGeometryDir = new G4UIdirectory("/OpSim/geometry/");
    fGeometryDir->SetGuidance("Geometry construction UI commands");

    // Create sub-directory for materials-related commands
    fMaterialsDir = new G4UIdirectory("/OpSim/materials/");
    fMaterialsDir->SetGuidance("Materials construction UI commands");

    // Create sub-directory for surface finish commands
    fMaterialsDir = new G4UIdirectory("/OpSim/geometry/");
    fMaterialsDir->SetGuidance("Surface finish UI commands");

    // Command to print current geometry and field settings
    fPrintCmd = new G4UIcmdWithoutParameter("/OpSim/print", this);
    fPrintCmd->SetGuidance("Print current settings.");

    //=====================================
    // Geometry Commands
    //=====================================

    /**
     * @brief Command to set the LMO Length.
     *
     * Parameter: LMOLength (double) unit
     */
    fGeometryLMOLengthCmd = new G4UIcmdWithADoubleAndUnit(
        "/OpSim/geometry/setLMOLength", this);
    fGeometryLMOLengthCmd->SetGuidance("Set LMO Length");
    fGeometryLMOLengthCmd->SetParameterName("LMOLength", false);
    fGeometryLMOLengthCmd->SetRange("LMOLength>0.");
    fGeometryLMOLengthCmd->SetUnitCategory("Length");
    fGeometryLMOLengthCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fGeometryLMOLengthCmd->SetToBeBroadcasted(false);

    /**
     * @brief Command to set the LMO Width.
     *
     * Parameter: LMOWidth (double) unit
     */
    fGeometryLMOWidthCmd = new G4UIcmdWithADoubleAndUnit(
        "/OpSim/geometry/setLMOWidth", this);
    fGeometryLMOWidthCmd->SetGuidance("Set LMO Width");
    fGeometryLMOWidthCmd->SetParameterName("LMOWidth", false);
    fGeometryLMOWidthCmd->SetRange("LMOWidth>0.");
    fGeometryLMOWidthCmd->SetUnitCategory("Length");
    fGeometryLMOWidthCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fGeometryLMOWidthCmd->SetToBeBroadcasted(false);

    /**
     * @brief Command to set the LMO Thickness.
     *
     * Parameter: LMOThickness (double) unit
     */
    fGeometryLMOThicknessCmd = new G4UIcmdWithADoubleAndUnit(
        "/OpSim/geometry/setLMOThickness", this);
    fGeometryLMOThicknessCmd->SetGuidance("Set LMO Thickness");
    fGeometryLMOThicknessCmd->SetParameterName("LMOThickness", false);
    fGeometryLMOThicknessCmd->SetRange("LMOThickness>0.");
    fGeometryLMOThicknessCmd->SetUnitCategory("Length");
    fGeometryLMOThicknessCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    fGeometryLMOThicknessCmd->SetToBeBroadcasted(false);

    /**
     * @brief Command to set the LMO Surface Finish Model.
     *
     * Parameter: LMO Surface Finish Model
     */
    fGeometryLMOModelCmd = new G4UIcmdWithAString(
        "/OpSim/geometry/setLMOSurfaceModel", this);
    fGeometryLMOModelCmd->SetParameterName("LMOSurfaceModel", false);

    /**
     * @brief Command to set the LMO Surface Finish Polish.
     *
     * Parameter: LMO Surface Finish Polish
     */
    fGeometryLMOPolishCmd = new G4UIcmdWithADouble(
        "/OpSim/geometry/setLMOSurfacePolish", this);
    fGeometryLMOPolishCmd->SetParameterName("LMOSurfacePolish", false);

    /**
     * @brief Command to set the LMO Surface Finish Type.
     *
     * Parameter: LMO Surface Finish Type
     */
    fGeometryLMOTypeCmd = new G4UIcmdWithAString(
        "/OpSim/geometry/setLMOSurfaceType", this);
    fGeometryLMOTypeCmd->SetParameterName("LMOSurfaceType", false);

    /**
     * @brief Command to set the LMO Surface Finish Type.
     *
     * Parameter: LMO Surface Finish Type
     */
    fGeometryLMOFinishCmd = new G4UIcmdWithAString(
        "/OpSim/geometry/setLMOSurfaceFinish", this);
    fGeometryLMOFinishCmd->SetParameterName("LMOSurfaceFinish", false);

    /**
     * @brief Command to set the LMO Surface Finish SigmaAlpha.
     *
     * Parameter: LMO Surface Finish SigmaAlpha
     */
    fGeometryLMOSigmaAlphaCmd = new G4UIcmdWithADouble(
        "/OpSim/geometry/setLMOSurfaceSigmaAlpha", this);
    fGeometryLMOSigmaAlphaCmd->SetParameterName("LMOSurfaceSigmaAlpha", false);

    /**
     * @brief Command to set the Detector Distance.
     *
     * Parameter: DetectorDistance (double) unit
     */
    fGeometryDetectorDistanceCmd = new G4UIcmdWithADoubleAndUnit(
        "/OpSim/geometry/setDetectorDistance", this);
    fGeometryDetectorDistanceCmd->SetGuidance("Set Detector Distance");
    fGeometryDetectorDistanceCmd->SetParameterName("DetectorDistance", false);
    fGeometryDetectorDistanceCmd->SetRange("DetectorDistance>0.");
    fGeometryDetectorDistanceCmd->SetUnitCategory("Length");
    fGeometryDetectorDistanceCmd->AvailableForStates(G4State_PreInit,
                                                     G4State_Idle);
    fGeometryDetectorDistanceCmd->SetToBeBroadcasted(false);

    //=====================================
    // Materials Commands
    //=====================================

    /**
     * @brief Command to set the LMO:Ag LY.
     *
     * Parameter: Lightyield LMO:Ag (double)
     */
    fGeometryLMOLYCmd =
        new G4UIcmdWithADouble("/OpSim/materials/setLMOLY", this);
    fGeometryLMOLYCmd->SetGuidance("Set Scintillator LMO (photons/MeV)");
    fGeometryLMOLYCmd->SetParameterName("LMOLY", false);
    fGeometryLMOLYCmd->SetRange("LMOLY>0.");
    fGeometryLMOLYCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/**
 * @brief Destructor.
 *
 * Deletes all UI commands to free memory.
 */
OpSimGeometryMessenger::~OpSimGeometryMessenger() {
    delete fPrintCmd;
    delete fGeometryLMOLengthCmd;
    delete fGeometryLMOWidthCmd;
    delete fGeometryLMOThicknessCmd;
    delete fGeometryDetectorDistanceCmd;
    delete fGeometryLMOLYCmd;
    delete fGeometryLMOModelCmd;
    delete fGeometryLMOPolishCmd;
    delete fGeometryLMOTypeCmd;
    delete fGeometryLMOFinishCmd;
    delete fGeometryLMOSigmaAlphaCmd;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/**
 * @brief Apply a new value from the UI command.
 * @param aCommand Pointer to the UI command used.
 * @param aNewValue New value as string from the UI.
 *
 * Converts the string to the appropriate type and sets it in the
 * geometry construction.
 */
void OpSimGeometryMessenger::SetNewValue(G4UIcommand *aCommand,
                                                     G4String aNewValue) {
    if (aCommand == fPrintCmd) {
        fGeometry->Print();
    } else if (aCommand == fGeometryLMOLengthCmd) {
        fGeometry->SetLMOLength(
            fGeometryLMOLengthCmd->GetNewDoubleValue(aNewValue));
    } else if (aCommand == fGeometryLMOWidthCmd) {
        fGeometry->SetLMOWidth(
            fGeometryLMOWidthCmd->GetNewDoubleValue(aNewValue));
    } else if (aCommand == fGeometryLMOThicknessCmd) {
        fGeometry->SetLMOThickness(
            fGeometryLMOThicknessCmd->GetNewDoubleValue(aNewValue));
    } else if (aCommand == fGeometryDetectorDistanceCmd) {
        fGeometry->SetDetectorDistance(
            fGeometryDetectorDistanceCmd->GetNewDoubleValue(aNewValue));
    } else if (aCommand == fGeometryLMOLYCmd) {
        fGeometry->SetLMOLY(fGeometryLMOLYCmd->GetNewDoubleValue(aNewValue));
    } else if (aCommand == fGeometryLMOModelCmd) {
        fGeometry->SetLMOSurfaceModel(aNewValue);
    } else if (aCommand == fGeometryLMOPolishCmd) {
        fGeometry->SetLMOSurfacePolish(fGeometryLMOPolishCmd->GetNewDoubleValue(aNewValue));
    } else if (aCommand == fGeometryLMOTypeCmd) {
        fGeometry->SetLMOSurfaceType(aNewValue);
    } else if (aCommand == fGeometryLMOFinishCmd) {
        fGeometry->SetLMOSurfaceFinish(aNewValue);
    } else if (aCommand == fGeometryLMOSigmaAlphaCmd) {
        fGeometry->SetLMOSurfaceSigmaAlpha(fGeometryLMOSigmaAlphaCmd->GetNewDoubleValue(aNewValue));
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/**
 * @brief Get the current value of a UI command.
 * @param aCommand Pointer to the UI command.
 * @return Current value of the command as a string.
 *
 * Retrieves the current value from the geometry construction and
 * converts it to a string for display in the UI.
 */
G4String
OpSimGeometryMessenger::GetCurrentValue(G4UIcommand *aCommand) {
    G4String cv;

    if (aCommand == fGeometryLMOLengthCmd) {
        cv = fGeometryLMOLengthCmd->ConvertToString(fGeometry->GetLMOLength(),
                                                    "m");
    } else if (aCommand == fGeometryLMOWidthCmd) {
        cv = fGeometryLMOWidthCmd->ConvertToString(fGeometry->GetLMOWidth(),
                                                   "m");
    } else if (aCommand == fGeometryLMOThicknessCmd) {
        cv = fGeometryLMOThicknessCmd->ConvertToString(
            fGeometry->GetLMOThickness(), "m");
    } else if (aCommand == fGeometryDetectorDistanceCmd) {
        cv = fGeometryDetectorDistanceCmd->ConvertToString(
            fGeometry->GetDetectorDistance(), "m");
    } else if (aCommand == fGeometryLMOLYCmd) {
        cv = fGeometryLMOLYCmd->ConvertToString(fGeometry->GetLMOLY());
    }
    return cv;
}
