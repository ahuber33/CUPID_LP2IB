/**
 * @file OpticalSimulationGeometryConstruction.cc
 * @brief Implements the detector geometry and magnetic field setup for the
 * Optical simulation.
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 *
 * This file contains the method definitions for the
 * `OpticalSimulationGeometryConstruction` class declared in
 * `OpticalSimulationGeometryConstruction.hh`. It manages:
 *  - Construction of the full and simplified detector geometry
 *  - Loading of GDML models for realistic component shapes
 *  - Definition of visualization attributes for logical volumes
 *  - Creation of world and holder volumes
 *  - Assignment of materials to all volumes
 *  - Optional multithread-safe handling of magnetic field instances
 *
 * The geometry construction workflow:
 *  - **Construct()**:
 *      - Cleans any existing geometry to prevent duplication
 *      - Defines rotation matrices for volume placement
 *      - Calls `CreateWorldAndHolder()` to create the world and main holder
 * volume
 *
 * Thread safety is ensured via:
 *  - `G4Mutex fieldManagerMutex` for synchronized access to the magnetic field
 * manager
 *  - `G4ThreadLocal` instances of `OpticalSimulationMagneticField` and
 * `G4FieldManager`
 *
 * Visualization colors for logical volumes:
 *  - "invis", "black", "white", "gray", "red", "orange", "yellow", "green",
 * "cyan", "blue", "magenta"
 *
 */

#include "OpticalSimulationGeometryConstruction.hh"

using namespace CLHEP;

//! Mutex to synchronize access to the magnetic field manager in multithreaded
//! mode
const G4String OpticalSimulationGeometryConstruction::path =
    "../simulation_input_files/";
std::mutex geometryMutex;
std::mutex fileAccessMutex;

/**
 * @brief Constructor for OpticalSimulationGeometryConstruction.
 *
 * Initializes the base geometry and attaches the geometry messenger
 * for interactive user control via macro commands.
 */
OpticalSimulationGeometryConstruction::OpticalSimulationGeometryConstruction()
    : G4VUserDetectorConstruction() {
    Geom = std::make_unique<Geometry>();
    fGeometryMessenger =
        std::make_unique<OpticalSimulationGeometryMessenger>(this);
}

/**
 * @brief Destructor for OpticalSimulationGeometryConstruction.
 */
OpticalSimulationGeometryConstruction::
    ~OpticalSimulationGeometryConstruction() = default;

/**
 * @brief Print a summary of the current geometry setup.
 */
void OpticalSimulationGeometryConstruction::Print() {
    G4cout << "\n------------------------------------------------------"
           << G4endl;
    G4cout << "-----------------------------------------------------" << G4endl;
}

/**
 * @brief Assign a visualization color to a logical volume.
 *
 * Predefined colors can be applied to logical volumes for debugging or
 * visualization.
 *
 * @param LogicalVolume Pointer to the logical volume to colorize.
 * @param Color Name of the color (e.g. "red", "green", "gray").
 */
void OpticalSimulationGeometryConstruction::SetLogicalVolumeColor(
    G4LogicalVolume *LogicalVolume, G4String Color) {
    // ***********************
    // Visualization Colors
    // ***********************
    invis = new G4VisAttributes(G4Colour(255 / 255., 255 / 255., 255 / 255.));
    invis->SetVisibility(false);

    black = new G4VisAttributes(G4Colour(0, 0, 0, 0.9));
    black->SetForceSolid(true);
    black->SetVisibility(true);

    white = new G4VisAttributes(G4Colour(1, 1, 1, 1.));
    white->SetForceSolid(true);
    white->SetVisibility(true);

    gray = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.5));
    gray->SetVisibility(true);

    red = new G4VisAttributes(G4Colour(1, 0, 0, 0.3));
    red->SetForceSolid(true);
    red->SetVisibility(true);

    orange = new G4VisAttributes(G4Colour(1, 0.5, 0, 0.3));
    orange->SetForceSolid(true);
    orange->SetVisibility(true);

    yellow = new G4VisAttributes(G4Colour(1, 1, 0, 0.5));
    yellow->SetForceSolid(true);
    yellow->SetVisibility(true);

    green = new G4VisAttributes(G4Colour(0, 1, 0, 0.3));
    green->SetForceSolid(true);
    green->SetVisibility(true);

    cyan = new G4VisAttributes(G4Colour(0, 1, 1, 0.3));
    cyan->SetForceSolid(true);
    cyan->SetVisibility(true);

    blue = new G4VisAttributes(G4Colour(0, 0, 1, 0.5));
    blue->SetForceSolid(true);
    blue->SetVisibility(true);

    magenta = new G4VisAttributes(G4Colour(1, 0, 1, 0.3));
    magenta->SetVisibility(true);

    // Apply selected color
    if (Color == "invis") {
        LogicalVolume->SetVisAttributes(invis);
    } else if (Color == "black") {
        LogicalVolume->SetVisAttributes(black);
    } else if (Color == "white") {
        LogicalVolume->SetVisAttributes(white);
    } else if (Color == "gray") {
        LogicalVolume->SetVisAttributes(gray);
    } else if (Color == "red") {
        LogicalVolume->SetVisAttributes(red);
    } else if (Color == "orange") {
        LogicalVolume->SetVisAttributes(orange);
    } else if (Color == "yellow") {
        LogicalVolume->SetVisAttributes(yellow);
    } else if (Color == "green") {
        LogicalVolume->SetVisAttributes(green);
    } else if (Color == "cyan") {
        LogicalVolume->SetVisAttributes(cyan);
    } else if (Color == "blue") {
        LogicalVolume->SetVisAttributes(blue);
    } else if (Color == "magenta") {
        LogicalVolume->SetVisAttributes(magenta);
    }
}

/**
 * @brief Create the world and holder volumes.
 *
 * Defines the simulation world as a large vacuum box and
 * places a holder volume inside it for containing components.
 */
void OpticalSimulationGeometryConstruction::CreateWorldAndHolder() {
    auto VacuumWorld =
        OpticalSimulationMaterials::getInstance()->getMaterial("VacuumWorld");
    auto Vacuum =
        OpticalSimulationMaterials::getInstance()->getMaterial("Vacuum");

    G4Box *SolidWorld = new G4Box("SolidWorld", 2.1 * m, 15.1 * m, 2.1 * m);
    LogicalWorld = new G4LogicalVolume(SolidWorld, VacuumWorld, "LogicalWorld");
    SetLogicalVolumeColor(LogicalWorld, "invis");

    G4Box *SolidHolder =
        new G4Box("SolidHolder", 2.05 * m, 15.05 * m, 2.05 * m);
    LogicalHolder = new G4LogicalVolume(SolidHolder, Vacuum, "LogicalHolder");
    SetLogicalVolumeColor(LogicalHolder, "invis");

    PhysicalWorld =
        new G4PVPlacement(G4Transform3D(DontRotate, G4ThreeVector(0, 0, 0)),
                          "World", LogicalWorld, NULL, false, 0);

    PhysicalHolder =
        new G4PVPlacement(G4Transform3D(DontRotate, G4ThreeVector(0, 0, 0)),
                          LogicalHolder, "Holder", LogicalWorld, false, 0);
}

/**
 * @brief Construct the Copper Frame.
 */
/* 
void OpticalSimulationGeometryConstruction::ConstructCopperFrame() {

    // -------------------------------------
    // Pile detector tower (Gio, 29.04.20).
    // Copper horizontal frames.
    // Horizontal octagonal light detectors.
    // -------------------------------------

    //                          111
    //      <--------------------------------------->
    //    ^ * * * * * * * * * * * * * * * * * * * * *
    //    | * * * * * * * * * * * * * * * * * * * * *
    //    | * * *       ^     * * * *           * * *
    //    | * *         |       * *               * *
    //    | * *         |       * *               * *
    //  59| * *       45|       * *               * *
    //    | * *<--------|------>* *               * *
    //    | * *         |       * *       35      * *
    //    | * * *       v     * * * * <-------> * * *
    //    | * * * * * * * * * * * * * * * * * * * * *
    //    v * * * * * * * * * * * * * * * * * * * * *
    //      <->                 <->
    //       7                   7


    NFloors         = 13;
    CrystalL        = 45.  * mm;
    LightDetL       = 49.  * mm;
    LightDetDiagL   = 40. * sqrt(2.) * mm;
    LightDetT       = 0.3  * mm;

    CuFrameX        = 111. * mm;
    CuFrameY        = 59.  * mm;
    CuFrameH        = 2.   * mm;
    CuTopFrameH     = 12.  * mm;
    CuBottomFrameH  = 12.  * mm;
    CuFrameHoleL    = 45.  * mm;
    CuFrameDT       = 7.   * mm;// Lateral thickness

    PTFEFrameX      = 7.  * mm;
    PTFEFrameY      = 7.  * mm;
    PTFEFrameH      = 7.  * mm;
    PTFEFrameHoleL  = 5.   * mm;
    PTFEFrameHoleL2 = 0.5 * PTFEFrameHoleL * sqrt(2.);
    PTFEFrameHoleT  = 3.   * mm;
    PTFEFrameHoleH  = 7.   * mm;
    PTFEFrameT      = 2.   * mm;

    CuBandX        = 8. * mm;
    CuBandY        = 2. * mm;
    CuBandH        = fDetTopCuPlate.Z
        - 0.5 * fDetTopCuPlate.H
        - 0.5 * fDetBottomCuPlate.H
        - fDetBottomCuPlate.Z
        - 30. * mm;
    PENBandX = CuBandX;
    PENBandY = 0.5 * mm; // 5 bands of ~100 um thickness each
    PENBandH = CuBandH;
    PENCoverT = 1. * mm;
    PENCoverX = CuBandX + 2. * PENCoverT;
    PENCoverY = 0.5 * mm + PENCoverT; //
    PENCoverH = CuBandH;

    ReflectorT = 70. * um;
    ReflectorL = CrystalL
        + 2. * PTFEFrameT;
    ReflectorH = CrystalL
        + 2. * PTFEFrameT;

    // Cu band positions
    CuBandPos.push_back( G4ThreeVector( -0.25 * CuFrameX   - 0.5 * CuFrameDT,
                -0.5 * CuFrameY    + 0.5 * CuBandY,
                +0.5 * CuTopFrameH - 0.5 * CuBandH ) );
    CuBandPos.push_back( G4ThreeVector( +0.25 * CuFrameX   + 0.5 * CuFrameDT,
                -0.5 * CuFrameY    + 0.5 * CuBandY,
                +0.5 * CuTopFrameH - 0.5 * CuBandH ) );
    CuBandPos.push_back( G4ThreeVector( -0.25 * CuFrameX   - 0.5 * CuFrameDT,
                +0.5 * CuFrameY    - 0.5 * CuBandY,
                +0.5 * CuTopFrameH - 0.5 * CuBandH ) );
    CuBandPos.push_back( G4ThreeVector( +0.25 * CuFrameX   + 0.5 * CuFrameDT,
                +0.5 * CuFrameY    - 0.5 * CuBandY,
                +0.5 * CuTopFrameH - 0.5 * CuBandH ) );

    // PEN band positions
    PENBandTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( -0.25 * CuFrameX   - 0.5 * CuFrameDT,
                    -0.5 * CuFrameY    - 0.5 * PENBandY,
                    +0.5 * CuTopFrameH - 0.5 * PENBandH ) ) );
    PENBandTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( +0.25 * CuFrameX   + 0.5 * CuFrameDT,
                    -0.5 * CuFrameY    - 0.5 * PENBandY,
                    +0.5 * CuTopFrameH - 0.5 * PENBandH ) ) );
    PENBandTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( -0.25 * CuFrameX   - 0.5 * CuFrameDT,
                    +0.5 * CuFrameY    + 0.5 * PENBandY,
                    +0.5 * CuTopFrameH - 0.5 * PENBandH ) ) );
    PENBandTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( +0.25 * CuFrameX   + 0.5 * CuFrameDT,
                    +0.5 * CuFrameY    + 0.5 * PENBandY,
                    +0.5 * CuTopFrameH - 0.5 * PENBandH ) ) );

    // PEN cover positions
    G4RotationMatrix rotcover = G4RotationMatrix();
    rotcover.rotateZ( 180. * deg );
    PENCoverTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( -0.25 * CuFrameX   - 0.5 * CuFrameDT,
                    -0.5 * CuFrameY    - 0.5 * PENCoverY,
                    +0.5 * CuTopFrameH - 0.5 * PENCoverH ) ) );
    PENCoverTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( +0.25 * CuFrameX   + 0.5 * CuFrameDT,
                    -0.5 * CuFrameY    - 0.5 * PENCoverY,
                    +0.5 * CuTopFrameH - 0.5 * PENCoverH ) ) );
    PENCoverTrans.push_back( new G4Transform3D( rotcover,
                G4ThreeVector( -0.25 * CuFrameX   - 0.5 * CuFrameDT,
                    +0.5 * CuFrameY    + 0.5 * PENCoverY,
                    +0.5 * CuTopFrameH - 0.5 * PENCoverH ) ) );
    PENCoverTrans.push_back( new G4Transform3D( rotcover,
                G4ThreeVector( +0.25 * CuFrameX   + 0.5 * CuFrameDT,
                    +0.5 * CuFrameY    + 0.5 * PENCoverY,
                    +0.5 * CuTopFrameH - 0.5 * PENCoverH ) ) );


    G4TwoVector offA(0,0), offB(0,0);
    G4double scaleA = 1, scaleB = 1;

    // Central vertical bands
    G4VSolid* CuBand = new G4Box( "CuBand",
				  0.5 * det.CuBandX,
				  0.5 * det.CuBandY,
				  0.5 * det.CuBandH );

    G4VSolid* CuBandHole = new G4Box( "CuBandHole",
				      0.5 * det.CuBandHoleX,
				      det.CuBandY,
				      0.5 * det.CuBandHoleH );

    G4VSolid* CuBandTopHole = new G4Box( "CuBandTopHole",
					 0.5 * det.CuBandHoleX,
					 det.CuBandY,
					 0.5 * det.CuBandTopHoleH );
}
 */

/**
 * @brief Construct the LMO part.
 */
void OpticalSimulationGeometryConstruction::ConstructPTFE() {
    auto Vacuum= OpticalSimulationMaterials::getInstance()->getMaterial("Vacuum");

    const AgataGeometricParameters::BDPTDetector& det = fGeomPars->GetBDPTDetector();

    // ----------
    // PTFE parts
    // ----------
    G4VSolid* PTFECorner = new G4Box( "PTFECorner",
				      0.5 * det.PTFECornerX,
				      0.5 * det.PTFECornerY,
				      0.5 * det.PTFECornerH );
    G4VSolid* PTFECornerDiagHole = new G4Box( "PTFECornerDiagHole",
					      0.5 * det.PTFECornerDiagHoleX,
					      0.5 * det.PTFECornerDiagHoleX,
					      det.PTFECornerH );

    PTFECorner = new G4SubtractionSolid( "PTFECorner",
					 PTFECorner,
					 PTFECornerDiagHole,
					 det.PTFECornerDiagHoleRot,
					 det.PTFECornerDiagHolePos );

    G4VSolid* PTFECornerTopHole = new G4Box( "PTFECornerTopHole",
					     det.PTFECornerTopHoleX,
					     det.PTFECornerTopHoleX,
					     det.PTFECornerTopHoleH );

    for( unsigned int i=0; i<det.PTFECornerTopHolePos.size(); i++ )
	PTFECorner = new G4SubtractionSolid( "PTFECorner",
					     PTFECorner,
					     PTFECornerTopHole,
					     det.PTFECornerTopHoleRot[i],
					     det.PTFECornerTopHolePos[i] );

    G4VSolid* PTFECornerXHole = new G4Box( "PTFECornerXHole",
					   det.PTFECornerXHoleX,
					   det.PTFECornerXHoleY,
					   0.5 * det.PTFECornerXHoleH );

    PTFECorner = new G4SubtractionSolid( "PTFECorner",
					 PTFECorner,
					 PTFECornerXHole,
					 det.PTFECornerXHoleRot,
					 det.PTFECornerXHolePos );

    G4VSolid* PTFECornerYHole = new G4Box( "PTFECornerYHole",
					   det.PTFECornerYHoleX,
					   det.PTFECornerYHoleY,
					   0.5 * det.PTFECornerYHoleH );

    PTFECorner = new G4SubtractionSolid( "PTFECorner",
					 PTFECorner,
					 PTFECornerYHole,
					 det.PTFECornerYHoleRot,
					 det.PTFECornerYHolePos );

    G4Tubs* PTFEButterflyBottom = new G4Tubs( "PTFE",
					      0.,
					      det.PTFEButterflyBottomR,
					      0.5 * det.PTFEButterflyBottomH,
					      0.,
					      360. * deg );

    G4Tubs* PTFEButterflyTop = new G4Tubs( "PTFE",
					   0.,
					   det.PTFEButterflyTopR,
					   0.5 * det.PTFEButterflyTopH,
					   0.,
					   360. * deg );

    G4VSolid* PTFEButterflyFlap = new G4Box( "PTFEButterflyFlap",
					     0.5 * det.PTFEButterflyFlapX,
					     0.5 * det.PTFEButterflyFlapY,
					     0.5 * det.PTFEButterflyFlapH );

    G4Tubs* PTFESmallCap = new G4Tubs( "PTFE",
				       0.,
				       det.PTFESmallCapR,
				       0.5 * det.PTFESmallCapH,
				       0.,
				       360. * deg );

    G4Tubs* PTFELargeCap = new G4Tubs( "PTFE",
				       0.,
				       det.PTFELargeCapR,
				       0.5 * det.PTFELargeCapH,
				       0.,
				       360. * deg );

    G4UnionSolid* PTFECap = new G4UnionSolid( "PTFE",
					      PTFELargeCap,
					      PTFESmallCap,
					      0,
					      G4ThreeVector( 0., 0., 0.5 * ( det.PTFELargeCapH + det.PTFESmallCapH ) ) );

    G4MultiUnion* PTFE = new G4MultiUnion( "PTFE" );
    for( unsigned int i=0; i<det.PTFECornerTrans.size(); i++ )
    	PTFE->AddNode( *PTFECorner, *det.PTFECornerTrans[i] );
    for( unsigned int i=0; i<det.PTFEButterflyTopTrans.size(); i++ )
    	PTFE->AddNode( *PTFEButterflyTop, *det.PTFEButterflyTopTrans[i] );
    for( unsigned int i=0; i<det.PTFEButterflyBottomTrans.size(); i++ )
    	PTFE->AddNode( *PTFEButterflyBottom, *det.PTFEButterflyBottomTrans[i] );
    for( unsigned int i=0; i<det.PTFEButterflyFlapTrans.size(); i++ )
    	PTFE->AddNode( *PTFEButterflyFlap, *det.PTFEButterflyFlapTrans[i] );
    for( unsigned int i=0; i<det.PTFELargeCapTrans.size(); i++ )
    	PTFE->AddNode( *PTFELargeCap, *det.PTFELargeCapTrans[i] );
    for( unsigned int i=0; i<det.PTFESmallCapTrans.size(); i++ )
    	PTFE->AddNode( *PTFESmallCap, *det.PTFESmallCapTrans[i] );
    PTFE->Voxelize();

    fPTFESolid = PTFE;

    // LOGICAL

    fPTFELogical       = new G4LogicalVolume( fPTFESolid,      Vacuum,    "PTFELogical",       0, 0, 0 );

    fPTFEPhysical = AgataAbstractGeometry::CreatePhysicalVolume( fPTFESolid,
						  fPTFELogical,
						  PhysicalHolder,
						  det.PTFEPos + det.TowerPos[0],
						  det.PTFESourcePos + det.TowerPos[0],
						  AgataAbstractGeometry::GetColor(Color::kWhite),
						  true,
						  0 );

}

/**
 * @brief Construct the LMO part.
 */
void OpticalSimulationGeometryConstruction::ConstructLMO() {
    auto Li2MoO4 = OpticalSimulationMaterials::getInstance()->getMaterial("Li2MoO4");
    /* auto Li2MoO4 = OpticalSimulationMaterials::getInstance()->getMaterial("EJ212"); */
    G4MaterialPropertiesTable *mpt = Li2MoO4->GetMaterialPropertiesTable();

    LogicalLMO =
        Geom->GetBoxVolume("Li2MoO4", Li2MoO4, fLMOLength, fLMOWidth, fLMOThickness);

    // Assign colors
    SetLogicalVolumeColor(LogicalLMO, "blue");

    PhysicalLMO = new G4PVPlacement(
        G4Transform3D(DontRotate, G4ThreeVector(0. * mm, 0 * mm, 0 * mm)),
        LogicalLMO, "LMO", LogicalHolder, false, 0);

    // Surface properties

    std::string optical_model = "unified";

    auto opLMOSurface = new G4OpticalSurface("LMOSurface");

    if (optical_model == "unified"){
        opLMOSurface->SetType(dielectric_dielectric);//dielectric_dielectric dielectric_LUTDAVIS
        opLMOSurface->SetFinish(polished);// ground polished Rough_LUT Polished_LUT
        opLMOSurface->SetModel(unified);//glisur unified DAVIS
    }

    if (optical_model == "glisur"){
        opLMOSurface->SetType(dielectric_dielectric);//dielectric_dielectric dielectric_LUTDAVIS
        opLMOSurface->SetFinish(Polished_LUT);// ground polished Rough_LUT Polished_LUT
        opLMOSurface->SetModel(glisur);//glisur unified DAVIS
        opLMOSurface->SetPolish(0.1);
    }

    if (optical_model == "DAVIS"){
        opLMOSurface->SetType(dielectric_LUTDAVIS);//dielectric_dielectric dielectric_LUTDAVIS
        opLMOSurface->SetFinish(Rough_LUT);// ground polished Rough_LUT Polished_LUT
        opLMOSurface->SetModel(glisur);//glisur unified DAVIS
    }

    auto LMOSurface = new G4LogicalSkinSurface("LMOSurface", LogicalLMO, opLMOSurface);

    auto opticalSurface = dynamic_cast<G4OpticalSurface*>(LMOSurface->GetSurface(LogicalLMO)->GetSurfaceProperty());
    if (opticalSurface) opticalSurface->DumpInfo();
}

/**
 * @brief Construct the Light Detector part.
 */
void OpticalSimulationGeometryConstruction::ConstructLD() {
    auto Germanium = OpticalSimulationMaterials::getInstance()->getMaterial("Germanium");

    G4MaterialPropertiesTable *mptLD = Germanium->GetMaterialPropertiesTable();

    // Octogonal Germanium LD dimensions

    G4double LDThickness;
    std::vector<G4TwoVector> LDPolygon; // LD octogonal shape vector

    LDPolygon.push_back( G4TwoVector( -15.7 * mm, -24.3 * mm ) );
    LDPolygon.push_back( G4TwoVector( +15.7 * mm, -24.3 * mm ) );
    LDPolygon.push_back( G4TwoVector( +24.3 * mm, -15.7 * mm ) );
    LDPolygon.push_back( G4TwoVector( +24.3 * mm, +15.7 * mm ) );
    LDPolygon.push_back( G4TwoVector( +15.7 * mm, +24.3 * mm ) );
    LDPolygon.push_back( G4TwoVector( -15.7 * mm, +24.3 * mm ) );
    LDPolygon.push_back( G4TwoVector( -24.3 * mm, +15.7 * mm ) );
    LDPolygon.push_back( G4TwoVector( -24.3 * mm, -15.7 * mm ) );
    LDThickness = 0.5 * mm;

    LogicalLD1 = Geom->GetOctogonalVolume("LD1", Germanium, LDPolygon, LDThickness);
    LogicalLD2 = Geom->GetOctogonalVolume("LD2", Germanium, LDPolygon, LDThickness);

    // Assign colors
    SetLogicalVolumeColor(LogicalLD1, "yellow");
    SetLogicalVolumeColor(LogicalLD2, "yellow");

    PhysicalLD1 = new G4PVPlacement(
        G4Transform3D(DontRotate, G4ThreeVector(0. * mm, 0 * mm, -fLMOThickness/2 - fDistanceLMOtoLD1 - LDThickness/2 )),
        LogicalLD1, "LD1", LogicalHolder, false, 0);

    PhysicalLD2 = new G4PVPlacement(
        G4Transform3D(DontRotate, G4ThreeVector(0. * mm, 0 * mm, fLMOThickness/2 + fDistanceLMOtoLD2 + LDThickness/2 )),
        LogicalLD2, "LD2", LogicalHolder, false, 0);
    
    //G4cout<<"LMO Thickness="<<fLMOThickness<<" | DistanceLMOtoLD="<<fDistanceLMOtoLD<<" | LDThickness="<<
    //LDThickness<<" | fLMOThickness/2 + fDistanceLMOtoLD + LDThickness/2 = "<<(fLMOThickness/2 + fDistanceLMOtoLD + LDThickness/2)<<G4endl;

    // Surface
    // https://eom.umicore.com/en/germanium-solutions/products/germanium-substrates/
    // Roughness: Polished side < 1 nm RMS
    // How the coating affects the polishing?

   /*  auto opLDSurface = new G4OpticalSurface("LDSurface");
    opLDSurface->SetType(dielectric_dielectric);
    opLDSurface->SetFinish(polished);
    opLDSurface->SetModel(unified);


    G4PhysicalVolumeStore* store = G4PhysicalVolumeStore::GetInstance();
    G4VPhysicalVolume* VacuumPhysical = store->GetVolume("Holder");

    auto LDSurface = new G4LogicalBorderSurface("LDSurface", PhysicalLD, VacuumPhysical, opLDSurface);
    auto opticalSurfaceLD = dynamic_cast<G4OpticalSurface*>(LDSurface->GetSurface(PhysicalLD,VacuumPhysical)->GetSurfaceProperty());
    
    if (opticalSurfaceLD) opticalSurfaceLD->DumpInfo(); */

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////// SiO coating
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    
   /*  auto SiO = OpticalSimulationMaterials::getInstance()->getMaterial("SiO");
    G4MaterialPropertiesTable *mptLDCoating = SiO->GetMaterialPropertiesTable();

    G4double LDCoatingThickness;
    LDCoatingThickness = 60 * nm;

    LogicalLDCoating = Geom->GetOctogonalVolume("LDCoating", SiO, LDPolygon, LDCoatingThickness);
    
    // Assign colors
    SetLogicalVolumeColor(LogicalLDCoating, "red");

    PhysicalLDCoating = new G4PVPlacement(
        G4Transform3D(DontRotate, G4ThreeVector(0. * mm, 0 * mm, fLMOThickness/2 + fDistanceLMOtoLD - LDCoatingThickness/2 )),
        LogicalLDCoating, "LDCoating", LogicalHolder, false, 0);
    
 */
}


/**
 * @brief Construct the full detector geometry for the simulation.
 *
 * This method initializes and builds all the physical volumes required
 * for the simulation. It cleans up any previously defined geometry,
 * applies common rotation matrices, and constructs the detector
 * components according to display flags.
 *
 * Steps performed:
 * - Clean existing geometry and volume stores to avoid duplication.
 * - Define common rotation matrices used for detector components.
 * - Create the world volume and geometry holder.
 * - Create LMO & Scintillator part
 * - Create PMT Glass part
 * - Create Teflon, Mylar & Detection part
 * - Create Optical Surface
 * - Return the fully initialized world volume.
 *
 * @return Pointer to the top-level physical volume (`PhysicalWorld`)
 *         containing the entire detector setup.
 */
G4VPhysicalVolume *OpticalSimulationGeometryConstruction::Construct() {
    // --- Cleanup of previous geometry ----------------------------------------
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    // --- Define common rotation matrices -------------------------------------
    DontRotate.rotateX(0.0 * deg);
    Flip.rotateZ(0 * deg);
    Flip.rotateX(90 * deg);
    Flip.rotateY(0 * deg);

    // #########################################################################
    //  DEFINE GEOMETRY VOLUMES
    // #########################################################################

    /// Create the world and main holder volume
    CreateWorldAndHolder();
    ConstructLMO();
    ConstructLD();
    ConstructPTFE();

    G4OpticalSurface *surface = new G4OpticalSurface("ScintillatorToHolder");
    surface->SetType(dielectric_dielectric);
    surface->SetFinish(polished);
    surface->SetModel(unified); // modèle plus complet
    /* 
    new G4LogicalBorderSurface("SurfScintHolder", PhysicalScintillator,
                               PhysicalHolder, surface);
    */

    G4cout << "END OF THE DETECTOR CONSTRUCTION" << G4endl;

    // --- Return the fully constructed world volume ---------------------------
    return PhysicalWorld;
}
