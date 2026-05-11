#ifndef OpSimGeometryConstruction_h
#define OpSimGeometryConstruction_h 1

/**
 * @class OpSimGeometryConstruction
 * @brief Defines the detector geometry for the OpSim
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
#include "OpSimGeometryMessenger.hh"
#include "OpSimMaterials.hh"
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

class Geometry;
class G4FieldManager;
class OpSimGeometryMessenger;
class OpSimMagneticField;

class OpSimGeometryConstruction final
    : public G4VUserDetectorConstruction {
  public:
    /** @brief Default constructor. */
    OpSimGeometryConstruction();

    /** @brief Destructor. */
    ~OpSimGeometryConstruction() override;

    /** @name Geometry Construction */
    ///@{
    /** @brief Set color for a given logical volume. */
    void SetLogicalVolumeColor(G4LogicalVolume *LogicalVolume, G4String color);

    /** @brief Create world and base holder. */
    void CreateWorldAndHolder();

    /** @brief Construct PTFE Part. */
    void ConstructPTFE();

    /** @brief Construct PTFE Part. */
    /* void ConstructPEN(); */
    
    /** @brief Construct Copper Frame. */
    void ConstructCopperFrame();

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
    void SetLMOThickness(const G4double Thickness) {fLMOThickness = Thickness;};

    // LMO Surface
    void SetLMOSurfaceModel(const G4String Model) {fLMOSurfaceModel = Model;};
    void SetLMOSurfacePolish(const G4double Polish) {fLMOSurfacePolish = Polish;};
    void SetLMOSurfaceType(const G4String Type) {fLMOSurfaceType = Type;};
    void SetLMOSurfaceFinish(const G4String Finish) {fLMOSurfaceFinish = Finish;};
    void SetLMOSurfaceSigmaAlpha(const G4double SigmaAlpha) {fLMOSurfaceSigmaAlpha = SigmaAlpha;};

    // LD
    void SetLDMaterial(const G4String LDMaterial) {fLDMaterial = LDMaterial;};
    void SetLDCoatingRINDEX(const G4double LDCoatingRINDEX) {fLDCoatingRINDEX = LDCoatingRINDEX;};
    void SetLDCoatingThickness(const G4double LDCoatingThickness) {fLDCoatingThickness = LDCoatingThickness;};

    void SetDetectorDistance(const G4double Distance) {fDetectorDistance = Distance;};

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

    G4int    NFloors;
            G4double CrystalL;
            G4double CrystalOffset;
            G4double LightDetT;
	    G4double LightDetCoatingT;

            std::vector<G4TwoVector> LightDetPolygon;
            std::vector<G4ThreeVector> LightDetSolidPos;
	    std::vector<G4ThreeVector> LightDetCoatingSolidPos;
            std::vector<G4ThreeVector> CrystalSolidPos;


            G4double CuFrameX;
            G4double CuFrameY;
            G4double CuFrameH;

            std::vector<G4double> CuFrameHoleX;
            std::vector<G4double> CuFrameHoleY;
            std::vector<G4double> CuFrameHoleH;
            std::vector<G4ThreeVector> CuFrameHolePos;

            G4double CuBandX;
            G4double CuBandY;
            G4double CuBandH;
            G4double CuBandHoleX;
            G4double CuBandHoleH;
            G4double CuBandTopHoleH;
            G4double CuMidBandX;
            G4double CuMidBandY;
            G4double CuMidBandH;
            G4double CuLatBandX;
            G4double CuLatBandY;
            G4double CuLatBandH;
            G4double CuLatBandHole1X;
            G4double CuLatBandHole1Y;
            G4double CuLatBandHole1H;
            G4double CuLatBandHole2X;
            G4double CuLatBandHole2Y;
            G4double CuLatBandHole2H;



            std::vector<G4ThreeVector> CuBandHolePos;
            G4ThreeVector CuBandTopHolePos;
            std::vector<G4ThreeVector> CuLatBandHole1Pos;
            std::vector<G4ThreeVector> CuLatBandHole2Pos;
            G4double CuLatBandT;
            G4double CuBandLittleHoleR;
            std::vector<G4RotationMatrix*> CuBandLittleHoleRot;
            std::vector<G4ThreeVector> CuBandLittleHolePos;

            std::vector<G4RotationMatrix>  CuBandRot;
            std::vector<G4ThreeVector>     CuBandPos;
            std::vector<G4Transform3D*>    CuBandTrans;
            std::vector<G4RotationMatrix>  CuMidBandRot;
            std::vector<G4ThreeVector>     CuMidBandPos;
            std::vector<G4Transform3D*>    CuMidBandTrans;
            std::vector<G4RotationMatrix>  CuLatBandRot;
            std::vector<G4ThreeVector>     CuLatBandPos;
            std::vector<G4Transform3D*>    CuLatBandTrans;
            std::vector<G4RotationMatrix>  CuLeftLatBandRot;
            std::vector<G4ThreeVector>     CuLeftLatBandPos;
            std::vector<G4Transform3D*>    CuLeftLatBandTrans;
            std::vector<G4RotationMatrix>  CuRightLatBandRot;
            std::vector<G4ThreeVector>     CuRightLatBandPos;
            std::vector<G4Transform3D*>    CuRightLatBandTrans;

            G4double          CuBottomX;
            G4double          CuBottomY;
            G4double          CuBottomH;
            G4ThreeVector     CuBottomPos;
            G4RotationMatrix  CuBottomRot;
            G4Transform3D*    CuBottomTrans;

            std::vector<G4double>      CuBottomHoleX;
            std::vector<G4double>      CuBottomHoleY;
            std::vector<G4ThreeVector> CuBottomHolePos;

            G4double          CuTopX;
            G4double          CuTopY;
            G4double          CuTopH;
            G4ThreeVector     CuTopPos;
            G4RotationMatrix  CuTopRot;
            G4Transform3D*    CuTopTrans;

            G4double          CuTopTopX;
            G4double          CuTopTopY;
            G4double          CuTopTopH;
            G4ThreeVector     CuTopTopPos;
            G4RotationMatrix  CuTopTopRot;
            G4Transform3D*    CuTopTopTrans;
            std::vector<G4double>      CuTopTopHoleX;
            std::vector<G4double>      CuTopTopHoleY;
            std::vector<G4ThreeVector> CuTopTopHolePos;
            std::vector<G4double>      CuTopTopRadHoleR;
            std::vector<G4ThreeVector> CuTopTopRadHolePos;

            std::vector<G4RotationMatrix>  CuHorizontalFrameRot;
            std::vector<G4ThreeVector>     CuHorizontalFramePos;
            std::vector<G4Transform3D*>    CuHorizontalFrameTrans;

            G4double CuBandZ;
            G4double CuFrameZ;

            G4double ClearanceX;
            G4double ClearanceY;

            G4ThreeVector CuFramePos;
            G4ThreeVector CuFrameSourcePos;

            // PEN parts
            G4double PENBandX;
            G4double PENBandY;
            G4double PENBandH;
            G4double PENBandHole1X;
            G4double PENBandHole1Y;
            G4double PENBandHole1H;
            G4double PENBandHole2X;
            G4double PENBandHole2Y;
            G4double PENBandHole2H;
            G4double PENBandHole3X;
            G4double PENBandHole3Y;
            G4double PENBandHole3H;
            G4double PENBandZ;

            std::vector<G4ThreeVector> PENBandHole1Pos;
            std::vector<G4ThreeVector> PENBandHole2Pos;
            std::vector<G4ThreeVector> PENBandHole3Pos;

            G4double                       PENBandLittleHoleR;
            std::vector<G4RotationMatrix*> PENBandLittleHoleRot;
            std::vector<G4ThreeVector>     PENBandLittleHolePos;

            std::vector<G4RotationMatrix>  PENBandRot;
            std::vector<G4ThreeVector>     PENBandPos;
            std::vector<G4Transform3D*>    PENBandTrans;


            G4double PENFlapX;
            G4double PENFlapY;
            G4double PENFlapH;
            G4double PENFlapT;
            std::vector<G4RotationMatrix> PENFlapRot;
            std::vector<G4ThreeVector>    PENFlapPos;
            std::vector<G4Transform3D*>   PENFlapTrans;


            G4double PENZ;
            G4ThreeVector PENPos;
            G4ThreeVector PENSourcePos;


            G4double PTFECornerX;
            G4double PTFECornerY;
            G4double PTFECornerH;
            G4double PTFECornerDiagHoleX;
            G4RotationMatrix* PTFECornerDiagHoleRot;
            G4ThreeVector     PTFECornerDiagHolePos;
            G4double PTFECornerTopHoleX;
            G4double PTFECornerTopHoleH;
            std::vector<G4RotationMatrix*> PTFECornerTopHoleRot;
            std::vector<G4ThreeVector>     PTFECornerTopHolePos;
            G4double PTFECornerXHoleX;
            G4double PTFECornerXHoleY;
            G4double PTFECornerXHoleH;
            G4RotationMatrix* PTFECornerXHoleRot;
            G4ThreeVector     PTFECornerXHolePos;
            G4double PTFECornerYHoleX;
            G4double PTFECornerYHoleY;
            G4double PTFECornerYHoleH;
            G4RotationMatrix* PTFECornerYHoleRot;
            G4ThreeVector     PTFECornerYHolePos;
            G4double PTFEMiddleH;
            std::vector<G4RotationMatrix> PTFECornerRot;
            std::vector<G4ThreeVector>    PTFECornerPos;
            std::vector<G4Transform3D*>   PTFECornerTrans;

            G4double PTFEButterflyBottomR;
            G4double PTFEButterflyBottomH;
            G4double PTFEButterflyTopR;
            G4double PTFEButterflyTopH;
            G4double PTFEButterflyFlapX;
            G4double PTFEButterflyFlapY;
            G4double PTFEButterflyFlapH;
            G4double PTFEButterflyFlapDZ;

            std::vector<G4RotationMatrix> PTFEButterflyBottomRot;
            std::vector<G4ThreeVector>    PTFEButterflyBottomPos;
            std::vector<G4Transform3D*>   PTFEButterflyBottomTrans;
            std::vector<G4RotationMatrix> PTFEButterflyTopRot;
            std::vector<G4ThreeVector>    PTFEButterflyTopPos;
            std::vector<G4Transform3D*>   PTFEButterflyTopTrans;
            std::vector<G4RotationMatrix> PTFEButterflyFlapRot;
            std::vector<G4ThreeVector>    PTFEButterflyFlapPos;
            std::vector<G4Transform3D*>   PTFEButterflyFlapTrans;

            G4double PTFELargeCapR;
            G4double PTFESmallCapR;
            G4double PTFELargeCapH;
            G4double PTFESmallCapH;

            std::vector<G4RotationMatrix> PTFECapRot;
            std::vector<G4ThreeVector>    PTFELargeCapPos;
            std::vector<G4ThreeVector>    PTFESmallCapPos;
            std::vector<G4Transform3D*>   PTFELargeCapTrans;
            std::vector<G4Transform3D*>   PTFESmallCapTrans;

            G4double      PTFEZ;
            G4ThreeVector PTFEPos;
            G4ThreeVector PTFESourcePos;


            std::vector<G4ThreeVector> TowerPos;
            G4int NTowers;

            G4double LightDetZ;
            G4ThreeVector LightDetPos;
            G4ThreeVector LightDetSourcePos;

	    G4double LightDetCoatingZ;
            G4ThreeVector LightDetCoatingPos;
            G4ThreeVector LightDetCoatingSourcePos;

            G4double CrystalZ;
            G4ThreeVector CrystalPos;
            G4ThreeVector CrystalSourcePos;

  private:
    static const G4String path;

    /** @brief Geometry handler. */
    std::unique_ptr<Geometry> Geom;

    /** @brief UI messenger for runtime commands. */
    std::unique_ptr<OpSimGeometryMessenger> fGeometryMessenger;

    /** @brief Default materials. */
    G4Material *Vacuum;
    G4Material *Material;

    /** @brief Default magnetic and geometry values. */
    G4double fLMOLength = 45 * CLHEP::mm;
    G4double fLMOWidth = 45 * CLHEP::mm;
    G4double fLMOThickness = 45 * CLHEP::mm;
    G4double fLMOx = 0 * CLHEP::mm;
    G4double fLMOy = 0 * CLHEP::mm;
    G4double fLMOz = 0 * CLHEP::mm;
    G4double fDistanceLMOtoLD1 = 0.5 * CLHEP::mm;
    G4double fDistanceLMOtoLD2 = 3 * CLHEP::mm;
    G4double fDetectorDistance = 100 * CLHEP::mm;
    G4String fLMOSurfaceModel = "unified";
    G4double fLMOSurfacePolish = -1.;
    G4String fLMOSurfaceType = "dielectric_dielectric";
    G4String fLMOSurfaceFinish = "ground";
    G4double fLMOSurfaceSigmaAlpha = -1.;
    G4double fLMOLY = 1000 / MeV;

    /** @brief Default LD values. */
    G4String fLDMaterial = "Germanium";
    G4double fLDCoatingRINDEX = 2.48;
    G4double fLDCoatingThickness = 60;

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
    G4LogicalVolume *LogicalPTFE = nullptr;
    G4LogicalVolume *LogicalCuFrame = nullptr;
    G4LogicalVolume *LogicalLMOsec1 = nullptr;
    G4LogicalVolume *LogicalLMOsec2 = nullptr;
    G4LogicalVolume *LogicalLMOsec3 = nullptr;
    G4LogicalVolume *LogicalLMOsec4 = nullptr;
    G4LogicalVolume *LogicalLMOsec5 = nullptr;
    G4LogicalVolume *LogicalLMOsec6 = nullptr;
    G4LogicalVolume *LogicalLMOsec7 = nullptr;
    G4LogicalVolume *LogicalLMOsec8 = nullptr;
    G4LogicalVolume *LogicalLMOSurf1 = nullptr;
    G4LogicalVolume *LogicalLMOSurf2 = nullptr;
    G4LogicalVolume *LogicalLMOSurf3 = nullptr;
    G4LogicalVolume *LogicalLMOSurf4 = nullptr;
    G4LogicalVolume *LogicalLMOSurf5 = nullptr;
    G4LogicalVolume *LogicalLMOSurf6 = nullptr;

    

    G4VSolid *SolidPTFE = nullptr;
    G4VSolid *SolidCuFrame = nullptr;
    

    /** @brief Physical volumes (placements in space). */
    G4VPhysicalVolume *PhysicalWorld = nullptr;
    G4VPhysicalVolume *PhysicalHolder = nullptr;
    G4VPhysicalVolume *PhysicalLD1 = nullptr;
    G4VPhysicalVolume *PhysicalLD2 = nullptr;
    //G4VPhysicalVolume *PhysicalLDCoating = nullptr;
    G4VPhysicalVolume *PhysicalLMO = nullptr;
    G4VPhysicalVolume *PhysicalPTFE = nullptr;
    G4VPhysicalVolume *PhysicalCuFrame = nullptr;
    G4VPhysicalVolume *PhysicalLMOsec1 = nullptr;
    G4VPhysicalVolume *PhysicalLMOsec2 = nullptr;
    G4VPhysicalVolume *PhysicalLMOsec3 = nullptr;
    G4VPhysicalVolume *PhysicalLMOsec4 = nullptr;
    G4VPhysicalVolume *PhysicalLMOsec5 = nullptr;
    G4VPhysicalVolume *PhysicalLMOsec6 = nullptr;
    G4VPhysicalVolume *PhysicalLMOsec7 = nullptr;
    G4VPhysicalVolume *PhysicalLMOsec8 = nullptr;
    G4VPhysicalVolume *PhysicalLMOSurf1 = nullptr;
    G4VPhysicalVolume *PhysicalLMOSurf2 = nullptr;
    G4VPhysicalVolume *PhysicalLMOSurf3 = nullptr;
    G4VPhysicalVolume *PhysicalLMOSurf4 = nullptr;
    G4VPhysicalVolume *PhysicalLMOSurf5 = nullptr;
    G4VPhysicalVolume *PhysicalLMOSurf6 = nullptr;

    /** @brief Rotation matrices for component orientation. */
    G4RotationMatrix DontRotate;
    G4RotationMatrix Flip;
    G4RotationMatrix *RotationMatrix;


    // AGATA

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
