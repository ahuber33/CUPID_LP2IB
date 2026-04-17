#ifndef OpticalSimulationGeometryConstruction_h
#define OpticalSimulationGeometryConstruction_h 1

/**
 * @class OpticalSimulationGeometryConstruction
 * @brief Defines the detector geometry for the OpticalSimulation
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 *
 * This class is responsible for:
 *  - Building the world and detector components.
 *  - Setting visualization attributes.
 *  - Providing user control over geometry display.
 */

#include "G4GeometryManager.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4SurfaceProperty.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "Geometry.hh"
#include "OpticalSimulationGeometryMessenger.hh"
#include "OpticalSimulationMaterials.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VSolid.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4MultiUnion.hh"
#include "G4Transform3D.hh"
#include "G4ExtrudedSolid.hh"
#include "G4ThreeVector.hh"

#include "AgataGeometricParameters.hh"
#include "AgataAbstractGeometry.hh"

class Geometry;
class G4FieldManager;
class OpticalSimulationGeometryMessenger;
class OpticalSimulationMagneticField;

class OpticalSimulationGeometryConstruction final
    : public G4VUserDetectorConstruction {
  public:
    /** @brief Default constructor. */
    OpticalSimulationGeometryConstruction();

    /** @brief Destructor. */
    ~OpticalSimulationGeometryConstruction() override;

    /** @name Geometry Construction */
    ///@{
    /** @brief Set color for a given logical volume. */
    void SetLogicalVolumeColor(G4LogicalVolume *LogicalVolume, G4String color);

    /** @brief Create world and base holder. */
    void CreateWorldAndHolder();

    /** @brief Construct PTFE Part. */
    void ConstructPTFE();

    /** @brief Construct LMO Part. */
    void ConstructLMO();

    /** @brief Construct LD Part. */
    void ConstructLD();

    /** @brief Construct DetectionOpticalProperties. */
    void CreateDetectionOpticalProperties();

    /** @brief Construct method required by Geant4 kernel. */
    G4VPhysicalVolume *Construct() override;

    /** @brief Print geometry parameters. */
    static void Print();
    ///@}

    /** @name Geometry Parameters */
    ///@{

    void SetLMOLength(const G4double Length) { fLMOLength = Length; };
    void SetLMOWidth(const G4double Width) { fLMOWidth = Width; };
    void SetLMOThickness(const G4double Thickness) {
        fLMOThickness = Thickness;
    };

    void SetDetectorDistance(const G4double Distance) {
        fDetectorDistance = Distance;
    };

    const float GetLMOLength() const { return fLMOLength; }
    const float GetLMOWidth() const { return fLMOWidth; }
    const float GetLMOThickness() const { return fLMOThickness; }
    const float GetDetectorDistance() const { return fDetectorDistance; }
    ///@}

    /** @name Geometry Parameters */
    ///@{
    void SetLMOLY(const G4double LY) { fLMOLY = LY; };

    const float GetLMOLY() const { return fLMOLY; }
    ///@}

  private:
    static const G4String path;

    /** @brief Geometry handler. */
    std::unique_ptr<Geometry> Geom;

    /** @brief UI messenger for runtime commands. */
    std::unique_ptr<OpticalSimulationGeometryMessenger> fGeometryMessenger;

    /** @brief Default materials. */
    G4Material *Vacuum;
    G4Material *Material;

    /** @brief Default magnetic and geometry values. */
    G4double fLMOLength = 45 * CLHEP::mm;
    G4double fLMOWidth = 45 * CLHEP::mm;
    G4double fLMOThickness = 45 * CLHEP::mm;
    G4double fDistanceLMOtoLD1 = 0.5 * CLHEP::mm;
    G4double fDistanceLMOtoLD2 = 3 * CLHEP::mm;
    G4double fDetectorDistance = 100 * CLHEP::mm;

    /** @brief Default Materials values. */
    G4double fLMOLY = 1000 / MeV;

    /** @brief Visualization attributes (colors). */
    G4VisAttributes *invis = nullptr; // init all the pointers
    G4VisAttributes *white = nullptr;
    G4VisAttributes *gray = nullptr;
    G4VisAttributes *black = nullptr;
    G4VisAttributes *red = nullptr;
    G4VisAttributes *orange = nullptr;
    G4VisAttributes *yellow = nullptr;
    G4VisAttributes *green = nullptr;
    G4VisAttributes *cyan = nullptr;
    G4VisAttributes *blue = nullptr;
    G4VisAttributes *magenta = nullptr;

    /** @brief Logical volumes (geometry definitions). */
    G4LogicalVolume *LogicalWorld = nullptr;
    G4LogicalVolume *LogicalHolder = nullptr;
    G4LogicalVolume *LogicalLD1 = nullptr;
    G4LogicalVolume *LogicalLD2 = nullptr;
    //G4LogicalVolume *LogicalLDCoating = nullptr;
    G4LogicalVolume *LogicalLMO = nullptr;
    

    /** @brief Physical volumes (placements in space). */
    G4VPhysicalVolume *PhysicalWorld = nullptr;
    G4VPhysicalVolume *PhysicalHolder = nullptr;
    G4VPhysicalVolume *PhysicalLD1 = nullptr;
    G4VPhysicalVolume *PhysicalLD2 = nullptr;
    //G4VPhysicalVolume *PhysicalLDCoating = nullptr;
    G4VPhysicalVolume *PhysicalLMO = nullptr;

    /** @brief Rotation matrices for component orientation. */
    G4RotationMatrix DontRotate;
    G4RotationMatrix Flip;
    G4RotationMatrix *RotationMatrix;


    // AGATA

    AgataGeometricParameters* fGeomPars;

    G4bool fSimplifyDrawing;

    G4VSolid* fCuFrameSolid;
    G4VSolid* fPENSolid;
    G4VSolid* fPTFESolid;
    G4VSolid* fLightDetSolid;
    G4VSolid* fLightDetCoatingSolid;
    G4VSolid* fCrystalSolid;

    G4LogicalVolume* fCuFrameLogical;
    G4LogicalVolume* fPENLogical;
    G4LogicalVolume* fPTFELogical;
    G4LogicalVolume* fLightDetLogical;
    G4LogicalVolume* fLightDetCoatingLogical;
    G4LogicalVolume* fCrystalLogical;

    G4VPhysicalVolume* fCuFramePhysical;
    G4VPhysicalVolume* fPENPhysical;
    G4VPhysicalVolume* fPTFEPhysical;
    G4VPhysicalVolume* fLightDetPhysical;
    G4VPhysicalVolume* fLightDetCoatingPhysical;
    G4VPhysicalVolume* fCrystalPhysical;
};
#endif
