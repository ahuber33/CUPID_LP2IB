#ifndef OpSimGeometryMessenger_H
#define OpSimGeometryMessenger_H

/**
 * @class OpSimGeometryMessenger
 * @brief UI messenger for the Geometry construction in optical simulation
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 *
 * Provides UI commands to setup detector and readout geometry (prior to
 * initialization). Length, distance, gradients and display can be changed.
 */

#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh" // for G4UIcmdWithADoubleAndUnit
#include "G4UIcmdWithAnInteger.hh"      // for G4UIcmdWithAnInteger
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"   // for G4UIcmdWithoutParameter
#include "G4UIdirectory.hh"             // for G4UIdirectory
#include "OpSimGeometryConstruction.hh" // for OpSimGeometryConstruction

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithoutParameter;
class G4UIdirectory;
class OpSimGeometryConstruction;

class OpSimGeometryMessenger : public G4UImessenger {
  public:
    OpSimGeometryMessenger(OpSimGeometryConstruction *);
    ~OpSimGeometryMessenger();

    /// Invokes appropriate methods based on the typed command
    virtual void SetNewValue(G4UIcommand *, G4String) final;
    /// Retrieves the current settings
    virtual G4String GetCurrentValue(G4UIcommand *) final;

  private:
    /// Detector construction to setup
    OpSimGeometryConstruction *fGeometry = nullptr;
    /// Command to set the directory common to all messengers in this example
    /// /Par04
    G4UIdirectory *fExampleDir = nullptr;
    /// Command to set the directory for detector settings
    /// /OpSim/geometry
    G4UIdirectory *fGeometryDir = nullptr;
    /// /OpSim/materials
    G4UIdirectory *fMaterialsDir = nullptr;
    /// Command printing current settings
    G4UIcmdWithoutParameter *fPrintCmd;

    /// GEOMETRY
    /// Command to set the Scintillator Length
    G4UIcmdWithADoubleAndUnit *fGeometryLMOLengthCmd = nullptr;
    /// Command to set the Scintillator Width
    G4UIcmdWithADoubleAndUnit *fGeometryLMOWidthCmd = nullptr;
    /// Command to set the Scintillator Thickness
    G4UIcmdWithADoubleAndUnit *fGeometryLMOThicknessCmd = nullptr;
    /// Command to set the Detector Distance
    G4UIcmdWithADoubleAndUnit *fGeometryDetectorDistanceCmd = nullptr;
    /// Command to set the LMO Surface Model
    G4UIcmdWithAString *fGeometryLMOModelCmd = nullptr;
    /// Command to set the LMO Surface Polish
    G4UIcmdWithADouble *fGeometryLMOPolishCmd = nullptr;
    /// Command to set the LMO Surface Type
    G4UIcmdWithAString *fGeometryLMOTypeCmd = nullptr;
    /// Command to set the LMO Surface Finish
    G4UIcmdWithAString *fGeometryLMOFinishCmd = nullptr;
    /// Command to set the LMO Surface SigmaAlpha
    G4UIcmdWithADouble *fGeometryLMOSigmaAlphaCmd = nullptr;

    /// MATERIALS
    ///  Command to set the LMO LY
    G4UIcmdWithADouble *fGeometryLMOLYCmd = nullptr;
};

#endif
