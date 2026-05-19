/**
 * @file SCOPSimGeometryConstruction.cc
 * @brief Implements the detector geometry and magnetic field setup for the
 * Optical simulation.
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 *
 * This file contains the method definitions for the
 * `SCOPSimGeometryConstruction` class declared in
 * `SCOPSimGeometryConstruction.hh`. It manages:
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
 *  - `G4ThreadLocal` instances of `SCOPSimMagneticField` and
 * `G4FieldManager`
 *
 * Visualization colors for logical volumes:
 *  - "invis", "black", "white", "gray", "red", "orange", "yellow", "green",
 * "cyan", "blue", "magenta"
 *
 */

#include "SCOPSimGeometryConstruction.hh"

using namespace CLHEP;

//! Mutex to synchronize access to the magnetic field manager in multithreaded
//! mode
const G4String SCOPSimGeometryConstruction::path =
    "../simulation_input_files/";
std::mutex geometryMutex;
std::mutex fileAccessMutex;

/**
 * @brief Constructor for SCOPSimGeometryConstruction.
 *
 * Initializes the base geometry and attaches the geometry messenger
 * for interactive user control via macro commands.
 */
SCOPSimGeometryConstruction::SCOPSimGeometryConstruction()
    : G4VUserDetectorConstruction() {
    Geom = std::make_unique<Geometry>();
    fGeometryMessenger =
        std::make_unique<SCOPSimGeometryMessenger>(this);
}

/**
 * @brief Destructor for SCOPSimGeometryConstruction.
 */
SCOPSimGeometryConstruction::
    ~SCOPSimGeometryConstruction() = default;

/**
 * @brief Print a summary of the current geometry setup.
 */
void SCOPSimGeometryConstruction::Print() {
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
void SCOPSimGeometryConstruction::SetLogicalVolumeColor(
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
    gray->SetForceSolid(true);
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

    G4double alpha = 0.2;

    blueAlpha = new G4VisAttributes(G4Colour(0, 0, 1, alpha));
    blueAlpha->SetForceSolid(true);
    blueAlpha->SetVisibility(true);
    yellowAlpha = new G4VisAttributes(G4Colour(1, 1, 0, alpha));
    yellowAlpha->SetForceSolid(true);
    yellowAlpha->SetVisibility(true);
    orangeAlpha = new G4VisAttributes(G4Colour(1, 0.5, 0, alpha));
    orangeAlpha->SetForceSolid(true);
    orangeAlpha->SetVisibility(true);
    grayAlpha = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, alpha));
    grayAlpha->SetForceSolid(true);
    grayAlpha->SetVisibility(true);

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
    } else if (Color == "blueAlpha") {
        LogicalVolume->SetVisAttributes(blueAlpha);
    } else if (Color == "yellowAlpha") {
        LogicalVolume->SetVisAttributes(yellowAlpha);
    } else if (Color == "orangeAlpha") {
        LogicalVolume->SetVisAttributes(orangeAlpha);
    } else if (Color == "grayAlpha") {
        LogicalVolume->SetVisAttributes(grayAlpha);
    }
}

/**
 * @brief Create the world and holder volumes.
 *
 * Defines the simulation world as a large vacuum box and
 * places a holder volume inside it for containing components.
 */
void SCOPSimGeometryConstruction::CreateWorldAndHolder() {
    auto VacuumWorld =
        SCOPSimMaterials::getInstance()->getMaterial("VacuumWorld");
    auto Vacuum =
        SCOPSimMaterials::getInstance()->getMaterial("Vacuum");

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

void SCOPSimGeometryConstruction::ConstructCopperFrame(G4ThreeVector  moduleCoords,
                                                    G4String CuName,
                                                    G4String CuColor,
                                                    G4LogicalVolume* motherLogical) {
    auto Copper = SCOPSimMaterials::getInstance()->getMaterial("Copper");

    NFloors         = 1;

    double epsilon = 100. * um;
    // Copper frames
    CuFrameX        = 108. * mm;

    CuFrameY        =  65. * mm;
    CuFrameH        =   7. * mm;

    for( double sx=-1.; sx<=1.; sx+=2. )
	{
	    CuFrameHoleX.push_back( 45. * mm );
	    CuFrameHoleY.push_back( 45. * mm );
	    CuFrameHoleH.push_back( 14. * mm );
	    CuFrameHolePos.push_back( G4ThreeVector( sx * 26.5 * mm, 0, 0 ) );
	}

    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		CuFrameHoleX.push_back(  6.  * mm );
		CuFrameHoleY.push_back( 16.5 * mm );
		CuFrameHoleH.push_back( 14.  * mm );
		CuFrameHolePos.push_back( G4ThreeVector( sx * 47. * mm, sy * 17.25 * mm, 0 ) );
	    }
    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		CuFrameHoleX.push_back(  6.  * mm );
		CuFrameHoleY.push_back( 16.5 * mm );
		CuFrameHoleH.push_back( 14.  * mm );
		CuFrameHolePos.push_back( G4ThreeVector( sx * 6. * mm, sy * 17.25 * mm, 0 ) );
	    }
    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		CuFrameHoleX.push_back(  3.6 * mm );
		CuFrameHoleY.push_back( 11.2 * mm );
		CuFrameHoleH.push_back( 14.  * mm );
		CuFrameHolePos.push_back( G4ThreeVector( sx * 16. * mm, sy * 22.5 * mm, 0 ) );
	    }
    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		CuFrameHoleX.push_back( 27.5 * mm );
		CuFrameHoleY.push_back(  6.  * mm );
		CuFrameHoleH.push_back( 14.  * mm );
		CuFrameHolePos.push_back( G4ThreeVector( sx * 54. * mm, sy * 32.5 * mm, 0 ) );
	    }
    for( double sy=-1.; sy<=1.; sy+=2. )
	{
	    CuFrameHoleX.push_back( 69.5 * mm );
	    CuFrameHoleY.push_back(  2.  * mm );
	    CuFrameHoleH.push_back( 14.  * mm );
	    CuFrameHolePos.push_back( G4ThreeVector( 0, sy * 32.5 * mm, 0 ) );
	}
    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		CuFrameHoleX.push_back( 15.75 * mm );
		CuFrameHoleY.push_back(  6.   * mm );
		CuFrameHoleH.push_back( 14.   * mm );
		CuFrameHolePos.push_back( G4ThreeVector( sx * 26.875 * mm, sy * 32.5 * mm, 0 ) );
	    }
    CuFrameHoleX.push_back( 110. * mm );
    CuFrameHoleY.push_back(  61. * mm );
    CuFrameHoleH.push_back(  10. * mm );
    CuFrameHolePos.push_back( G4ThreeVector( 0, 0, - 0.5 * CuFrameH ) );

    

    CuBandX           =  43. * mm;
    CuBandY           =   1. * mm;
    CuBandH           =  53. * mm;   //739. * mm;
    CuBandHoleX       =  37. * mm;
    CuBandHoleH       =  45. * mm;
    CuBandTopHoleH    =  27. * mm;

    for( int f=0; f<14; f++ )
    {
        double z = -0.5 * CuBandH + 16. * mm
            + ( 0.5 + f ) * CuBandHoleH
            + 4. * mm * f;
        CuBandHolePos.push_back( G4ThreeVector( 0., 0., z ) );
    }
    CuBandTopHolePos = G4ThreeVector( 0., 0., 0.5 * CuBandH - 10. * mm - 0.5 * CuBandTopHoleH );
    
    CuMidBandX        =   1. * mm;
    CuMidBandY        =   3. * mm;
    CuMidBandH        =  53. * mm;   //739. * mm;
    
    CuLatBandX        =  13.9  * mm;
    CuLatBandY        =   1.   * mm;
    CuLatBandH        =    53. * mm;   //739. * mm;
    CuLatBandHole1X   =   5.4  * mm;
    CuLatBandHole1Y   =   1.   * mm;
    CuLatBandHole1H   =  20.25 * mm;
    CuLatBandHole2X   =   5.4  * mm;
    CuLatBandHole2Y   =   1.   * mm;
    CuLatBandHole2H   =  16.25 * mm;
    
    for( int f=0; f<NFloors; f++ )

	{
	    double x = -0.5 * CuLatBandX;
	    double z = -0.5 * CuLatBandH + 16.*mm
		+ 0.5 * CuLatBandHole1H
		+ 49. * mm * f;
	    CuLatBandHole1Pos.push_back( G4ThreeVector( x, 0., z ) );
	    
	    z = - 0.5 * CuLatBandH + 16.*mm + 24.75*mm
		+ 0.5 * CuLatBandHole2H
		+ 49. * mm * f;
	    CuLatBandHole2Pos.push_back( G4ThreeVector( x, 0., z ) );
	}

    CuBandLittleHoleR = 1.1 * mm;
    for( int f=0; f<NFloors; f++ )
	{
	    CuBandLittleHoleRot.push_back( new G4RotationMatrix() );
	    CuBandLittleHoleRot.back()->rotateX( 90. * deg );
	    double x = 1.75 * mm;
	    double y = 0.;
	    double z = -0.5 * CuBandH + 38.5 * mm + f * 49. * mm;
	    CuBandLittleHolePos.push_back( G4ThreeVector( x, y, z ) );
	}


    for( double sy=-1.; sy<=1.; sy+=2. )
	{
	    CuBandRot.push_back( G4RotationMatrix() );
	    CuBandPos.push_back( G4ThreeVector( 0, sy * ( 34.0*mm + 3. * epsilon ), 0. ) );
	}
    for( unsigned int i=0; i<CuBandPos.size(); i++ )
	CuBandTrans.push_back( new G4Transform3D( CuBandRot[i],
								CuBandPos[i] ) );

    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	{
	    CuMidBandPos.push_back( G4ThreeVector( sx * 21.*mm, sy * ( 32.*mm + 2. * epsilon ), 0. ) );
	    CuMidBandRot.push_back( G4RotationMatrix() );
	}
    for( unsigned int i=0; i<CuMidBandPos.size(); i++ )
	CuMidBandTrans.push_back( new G4Transform3D( CuMidBandRot[i],
								   CuMidBandPos[i] ) );



    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		double x = sx * 27.45*mm;
		double y = sy * ( 30*mm + epsilon );
		double z = 0.;
		CuLatBandPos.push_back( G4ThreeVector( x, y, z ) );
		CuLatBandRot.push_back( G4RotationMatrix() );
		if( sx == 1. )
		    CuLatBandRot.back().rotateZ( 180. * deg );
	    }
    for( unsigned int i=0; i<CuLatBandPos.size(); i++ )
	CuLatBandTrans.push_back( new G4Transform3D( CuLatBandRot[i],
								   CuLatBandPos[i] ) );
    
    for( unsigned int f=0; f<=NFloors; f++ )
	{
	    double z = -0.5 * CuBandH + 15. * mm + f * 49. * mm - 2.5 * mm;
	    CuHorizontalFramePos.push_back( G4ThreeVector( 0, 0, z ) );
	    CuHorizontalFrameRot.push_back( G4RotationMatrix() );
	    CuHorizontalFrameTrans.push_back( new G4Transform3D( CuHorizontalFrameRot[f],
									       CuHorizontalFramePos[f]) );
	} 


    CuBandZ         = 0;
    CuFrameZ = CuBandZ;

    CuFramePos         = G4ThreeVector( 0, 0, CuFrameZ );
    CuFrameSourcePos   = G4ThreeVector( 0, 0, CuFrameZ );


    // ------------
    // Copper parts
    // ------------

    G4TwoVector offA(0,0), offB(0,0);
    G4double scaleA = 1, scaleB = 1;

    // Central vertical bands
    G4VSolid* CuBand = new G4Box( "CuBand",
				  0.5 * CuBandX,
				  0.5 * CuBandY,
				  0.5 * CuBandH );

    G4VSolid* CuBandHole = new G4Box( "CuBandHole",
				      0.5 * CuBandHoleX,
				      CuBandY,
				      0.5 * CuBandHoleH );

    G4VSolid* CuBandTopHole = new G4Box( "CuBandTopHole",
					 0.5 * CuBandHoleX,
					 CuBandY,
					 0.5 * CuBandTopHoleH );

    for( unsigned int f=0; f<CuBandHolePos.size(); f++ )
	CuBand = new G4SubtractionSolid( "CuFrame",
					 CuBand,
					 CuBandHole,
					 0,
					 CuBandHolePos[f] );

    CuBand = new G4SubtractionSolid( "CuFrame",
				     CuBand,
				     CuBandTopHole,
				     0,
				     CuBandTopHolePos );

    // Vertical mid band
    G4VSolid* CuMidBand = new G4Box( "CuMidBand",
				     0.5 * CuMidBandX,
				     0.5 * CuMidBandY,
				     0.5 * CuMidBandH );

    // Vertical lateral band
    G4VSolid* CuLatBand = new G4Box( "CuLatBand",
				     0.5 * CuLatBandX,
				     0.5 * CuLatBandY,
				     0.5 * CuLatBandH );

    G4VSolid* CuLatBandHole1 = new G4Box( "CuLatBandHole1",
					  CuLatBandHole1X,
					  CuLatBandHole1Y,
					  0.5 * CuLatBandHole1H );

    G4VSolid* CuLatBandHole2 = new G4Box( "CuLatBandHole2",
					  CuLatBandHole2X,
					  CuLatBandHole2Y,
					  0.5 * CuLatBandHole2H );

    for( unsigned int f=0; f<CuLatBandHole1Pos.size(); f++ )
	CuLatBand = new G4SubtractionSolid( "CuLatBand",
					    CuLatBand,
					    CuLatBandHole1,
					    0,
					    CuLatBandHole1Pos[f] );

    for( unsigned int f=0; f<CuLatBandHole2Pos.size(); f++ )
	CuLatBand = new G4SubtractionSolid( "CuLatBand",
					    CuLatBand,
					    CuLatBandHole2,
					    0,
					    CuLatBandHole2Pos[f] );

    G4Tubs* CuBandLittleHole = new G4Tubs( "CuBandLittleHole",
					   0.,
					   CuBandLittleHoleR,
					   CuLatBandY,
					   0.,
					   360. * deg );

    for( unsigned int f=0; f<CuBandLittleHolePos.size(); f++ )
	CuLatBand = new G4SubtractionSolid( "CuFrame",
					    CuLatBand,
					    CuBandLittleHole,
					    CuBandLittleHoleRot[f],
					    CuBandLittleHolePos[f] );

    // Middle frames
    G4VSolid* CuHorizontalFrame = new G4Box( "CuHorizontalFrame",
					     0.5 * CuFrameX,
					     0.5 * CuFrameY,
					     0.5 * CuFrameH );
    std::vector<G4VSolid*> CuHorizontalFrameHole;

    G4cout<<"FLAG 10 = "<<CuFrameHolePos.size()<<G4endl;

	CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[0], 0.5 * CuFrameHoleY[0], 0.5 * CuFrameHoleH[0] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[0] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[1], 0.5 * CuFrameHoleY[1], 0.5 * CuFrameHoleH[1] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[1] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[2], 0.5 * CuFrameHoleY[2], 0.5 * CuFrameHoleH[2] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[2] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[3], 0.5 * CuFrameHoleY[3], 0.5 * CuFrameHoleH[3] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[3] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[4], 0.5 * CuFrameHoleY[4], 0.5 * CuFrameHoleH[4] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[4] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[5], 0.5 * CuFrameHoleY[5], 0.5 * CuFrameHoleH[5] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[5] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[6], 0.5 * CuFrameHoleY[6], 0.5 * CuFrameHoleH[6] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[6] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[7], 0.5 * CuFrameHoleY[7], 0.5 * CuFrameHoleH[7] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[7] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[8], 0.5 * CuFrameHoleY[8], 0.5 * CuFrameHoleH[8] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[8] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[9], 0.5 * CuFrameHoleY[9], 0.5 * CuFrameHoleH[9] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[9] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[10], 0.5 * CuFrameHoleY[10], 0.5 * CuFrameHoleH[10] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[10] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[11], 0.5 * CuFrameHoleY[11], 0.5 * CuFrameHoleH[11] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[11] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[12], 0.5 * CuFrameHoleY[12], 0.5 * CuFrameHoleH[12] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[12] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[13], 0.5 * CuFrameHoleY[13], 0.5 * CuFrameHoleH[13] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[13] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[14], 0.5 * CuFrameHoleY[14], 0.5 * CuFrameHoleH[14] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[14] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[15], 0.5 * CuFrameHoleY[15], 0.5 * CuFrameHoleH[15] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[15] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[16], 0.5 * CuFrameHoleY[16], 0.5 * CuFrameHoleH[16] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[16] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[17], 0.5 * CuFrameHoleY[17], 0.5 * CuFrameHoleH[17] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[17] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[18], 0.5 * CuFrameHoleY[18], 0.5 * CuFrameHoleH[18] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[18] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[19], 0.5 * CuFrameHoleY[19], 0.5 * CuFrameHoleH[19] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[19] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[20], 0.5 * CuFrameHoleY[20], 0.5 * CuFrameHoleH[20] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[20] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[21], 0.5 * CuFrameHoleY[21], 0.5 * CuFrameHoleH[21] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[21] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[22], 0.5 * CuFrameHoleY[22], 0.5 * CuFrameHoleH[22] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[22] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[23], 0.5 * CuFrameHoleY[23], 0.5 * CuFrameHoleH[23] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[23] );
    CuHorizontalFrameHole.push_back( new G4Box( "CuFrameHole", 0.5 * CuFrameHoleX[24], 0.5 * CuFrameHoleY[24], 0.5 * CuFrameHoleH[24] ) );
    CuHorizontalFrame = new G4SubtractionSolid( "CuHorizontalFrame", CuHorizontalFrame,CuHorizontalFrameHole.back(), 0, CuFrameHolePos[24] );


    // Put everything together
    
    G4MultiUnion* CuFrame = new G4MultiUnion( CuName );

    /* for( unsigned int i=0; i<CuHorizontalFrameTrans.size(); i++ )
    	CuFrame->AddNode( *CuHorizontalFrame, *CuHorizontalFrameTrans[i] );
    for( unsigned int i=0; i<CuBandTrans.size(); i++ )
    	CuFrame->AddNode( *CuBand, *CuBandTrans[i] );
    for( unsigned int i=0; i<CuMidBandTrans.size(); i++ )
    	CuFrame->AddNode( *CuMidBand, *CuMidBandTrans[i] );
    for( unsigned int i=0; i<CuLatBandTrans.size(); i++ )
    	CuFrame->AddNode( *CuLatBand, *CuLatBandTrans[i] ); */

    G4cout<<CuHorizontalFrameTrans.size()<<G4endl;
    G4cout<<CuBandTrans.size()<<G4endl;
    G4cout<<CuMidBandTrans.size()<<G4endl;
    G4cout<<CuLatBandTrans.size()<<G4endl;

    CuFrame->AddNode( *CuHorizontalFrame, *CuHorizontalFrameTrans[0] );
    CuFrame->AddNode( *CuHorizontalFrame, *CuHorizontalFrameTrans[1] );

    CuFrame->AddNode( *CuBand, *CuBandTrans[0] );
    CuFrame->AddNode( *CuBand, *CuBandTrans[1] );

    CuFrame->AddNode( *CuMidBand, *CuMidBandTrans[0] );
    CuFrame->AddNode( *CuMidBand, *CuMidBandTrans[1] );
    CuFrame->AddNode( *CuMidBand, *CuMidBandTrans[2] );
    CuFrame->AddNode( *CuMidBand, *CuMidBandTrans[3] );

    /* CuFrame->AddNode( *CuLatBand, *CuLatBandTrans[0] );
    CuFrame->AddNode( *CuLatBand, *CuLatBandTrans[1] );      // NE FONCTIONNE PAS ??????
    CuFrame->AddNode( *CuLatBand, *CuLatBandTrans[2] );      //
    CuFrame->AddNode( *CuLatBand, *CuLatBandTrans[3] ); */

    CuFrame->Voxelize();

    SolidCuFrame = CuFrame;
    LogicalCuFrame    = new G4LogicalVolume( SolidCuFrame,    Copper,    CuName,    0, 0, 0 );

    SetLogicalVolumeColor(LogicalCuFrame, CuColor);

    PhysicalCuFrame = new G4PVPlacement(
        G4Transform3D(DontRotate, moduleCoords+G4ThreeVector(26.5 * mm, 0 * mm, -13 * mm)),
        LogicalCuFrame, CuName, motherLogical, false, 0);
}


/**
 * @brief Construct the LMO part.
 */
void SCOPSimGeometryConstruction::ConstructPTFE(G4ThreeVector  moduleCoords,
                                                G4String PTFEName,
                                                G4String PTFEColor,
                                                G4LogicalVolume* motherLogical) {
    auto Teflon = SCOPSimMaterials::getInstance()->getMaterial("Teflon");

    NFloors = 1;

    PTFECornerX = 9. * mm;
    PTFECornerY = 10. * mm;
    PTFECornerH = 8. * mm;
    PTFECornerDiagHoleX = 7.4 * mm;
    PTFECornerDiagHoleRot = new G4RotationMatrix();
    PTFECornerDiagHoleRot->rotateZ( 45. * deg );
    PTFECornerDiagHolePos = G4ThreeVector( 0.5 * PTFECornerX, 0.5 * PTFECornerY, 0 );
    PTFECornerTopHoleX = 5.2 * mm;
    PTFECornerTopHoleH = 2. * mm;
    for( double sign=-1; sign<=2.; sign+=2. )
	{
	    PTFECornerTopHoleRot.push_back( new G4RotationMatrix() );
	    PTFECornerTopHolePos.push_back( G4ThreeVector( 0.5 * PTFECornerX,
									 0.5 * PTFECornerY,
									 sign * 0.5 * PTFECornerH ) );
	}
    PTFECornerXHoleX = 3. * mm;
    PTFECornerXHoleY = 10. * mm;
    PTFECornerXHoleH = 2. * mm;
    PTFECornerXHoleRot = new G4RotationMatrix();
    PTFECornerXHolePos = G4ThreeVector( -0.5 * PTFECornerX, 0, 0 );
    PTFECornerYHoleX = 9. * mm;
    PTFECornerYHoleY = 2. * mm;
    PTFECornerYHoleH = 2. * mm;
    PTFECornerYHoleRot = new G4RotationMatrix();
    PTFECornerYHolePos = G4ThreeVector( 0, -0.5 * PTFECornerY, 0 );
    

    PTFECornerPos.push_back( G4ThreeVector( -48.5*mm, -22.5*mm, 0. ) );
    PTFECornerRot.push_back( G4RotationMatrix() );

    PTFECornerPos.push_back( G4ThreeVector( -48.5*mm, +22.5*mm, 0. ) );
    PTFECornerRot.push_back( G4RotationMatrix() );
    PTFECornerRot.back().rotateX( 180. * deg );

    PTFECornerPos.push_back( G4ThreeVector( +48.5*mm, -22.5*mm, 0. ) );
    PTFECornerRot.push_back( G4RotationMatrix() );
    PTFECornerRot.back().rotateY( 180. * deg );

    PTFECornerPos.push_back( G4ThreeVector( +48.5*mm, +22.5*mm, 0. ) );
    PTFECornerRot.push_back( G4RotationMatrix() );
    PTFECornerRot.back().rotateX( 180. * deg );
    PTFECornerRot.back().rotateY( 180. * deg );

    PTFECornerPos.push_back( G4ThreeVector( +4.5*mm, -22.5*mm, 0. ) );
    PTFECornerRot.push_back( G4RotationMatrix() );

    PTFECornerPos.push_back( G4ThreeVector( +4.5*mm, +22.5*mm, 0. ) );
    PTFECornerRot.push_back( G4RotationMatrix() );
    PTFECornerRot.back().rotateX( 180. * deg );

    PTFECornerPos.push_back( G4ThreeVector( -4.5*mm, -22.5*mm, 0. ) );
    PTFECornerRot.push_back( G4RotationMatrix() );
    PTFECornerRot.back().rotateY( 180. * deg );

    PTFECornerPos.push_back( G4ThreeVector( -4.5*mm, +22.5*mm, 0. ) );
    PTFECornerRot.push_back( G4RotationMatrix() );
    PTFECornerRot.back().rotateX( 180. * deg );
    PTFECornerRot.back().rotateY( 180. * deg );

    for( unsigned int f=0; f<=NFloors; f++ )

	for( unsigned int i=0; i<PTFECornerPos.size(); i++ )
	    {
		double z = -0.5 * CuBandH + 15. * mm + f * 49. * mm
		    -0.5 * CuFrameH;

		PTFECornerTrans.push_back( new G4Transform3D( PTFECornerRot[i],
									    PTFECornerPos[i] + G4ThreeVector( 0, 0, z ) ) );
	    }

    PTFEButterflyBottomR = 2.75 * mm;
    PTFEButterflyBottomH = 2.   * mm;
    PTFEButterflyTopR    = 1.5  * mm;
    PTFEButterflyTopH    = 6.   * mm;
    PTFEButterflyFlapX   = 7.   * mm;
    PTFEButterflyFlapY   = 2.85 * mm;
    PTFEButterflyFlapH   = 2.   * mm;
    PTFEButterflyFlapDZ  = 2.5 * mm;

    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		PTFEButterflyFlapPos.push_back( G4ThreeVector( sx * 16. * mm, sy * 24.125 * mm, 0. ) );
		PTFEButterflyFlapRot.push_back( G4RotationMatrix() );
		
		PTFEButterflyTopPos.push_back( G4ThreeVector( sx * 16. * mm, sy * 26.5 * mm, 0. ) );
		PTFEButterflyTopRot.push_back( G4RotationMatrix() );
		
		PTFEButterflyBottomPos.push_back( G4ThreeVector( sx * 16. * mm, sy * 26.5 * mm, 0. ) );
		PTFEButterflyBottomRot.push_back( G4RotationMatrix() );
	    }
    
    for( unsigned int f=0; f<=NFloors; f++ )
	for( unsigned int i=0; i<PTFEButterflyTopPos.size(); i++ )
	    {
		double z = -0.5 * CuBandH -0.5 * CuFrameH + 15. * mm + f * 49. * mm
		    - PTFEButterflyBottomH;
		PTFEButterflyBottomTrans.push_back( new G4Transform3D( PTFEButterflyBottomRot[i],
										     PTFEButterflyBottomPos[i] + G4ThreeVector( 0, 0, z ) ) );
		
		z = -0.5 * CuBandH -0.5 * CuFrameH + 15. * mm + f * 49. * mm
		    - 0.5 * PTFEButterflyBottomH
		    + 0.5 * PTFEButterflyTopH;
		PTFEButterflyTopTrans.push_back( new G4Transform3D( PTFEButterflyTopRot[i],
										  PTFEButterflyTopPos[i] + G4ThreeVector( 0, 0, z ) ) );
		
		z = -0.5 * CuBandH -0.5 * CuFrameH + 15. * mm + f * 49. * mm
		    - 0.5 * PTFEButterflyBottomH
		    + PTFEButterflyFlapDZ
		    + 0.5 * PTFEButterflyFlapH;
		PTFEButterflyFlapTrans.push_back( new G4Transform3D( PTFEButterflyFlapRot[i],
										   PTFEButterflyFlapPos[i] + G4ThreeVector( 0, 0, z ) ) );
		
	    }

    PTFELargeCapR = 3.  * mm;
    PTFESmallCapR = 1.  * mm;
    PTFELargeCapH = 1.5 * mm;
    PTFESmallCapH = 6.4 * mm;

    G4cout<<NFloors<<G4endl;

    for( int f=0; f<NFloors; f++ ){

        for( double sx=-1; sx<=1; sx+=2 )
            for( double sy=-1; sy<=1; sy+=2 )
            {
                PTFECapRot.push_back( G4RotationMatrix() );
                PTFECapRot.back().rotateX( sy * 90. * deg );
                double x = sx * 25.7 * mm;
                double y = sy * 32. * mm;
                double z = -0.5 * CuBandH + 37.5 * mm + f * 49. * mm - 2.5 * mm;
                PTFELargeCapPos.push_back( G4ThreeVector( x, y, z ) );
                PTFELargeCapTrans.push_back( new G4Transform3D( PTFECapRot.back(),
                                            PTFELargeCapPos.back() ) );
                y = sy * (  32. * mm - 0.5 * PTFELargeCapH - 0.5 * PTFESmallCapH );
                PTFESmallCapPos.push_back( G4ThreeVector( x, y, z ) );
                PTFESmallCapTrans.push_back( new G4Transform3D( PTFECapRot.back(),
                                            PTFESmallCapPos.back() ) );
            }
    }

    PTFEZ           = CuFrameZ - 0.5 * ( PTFEMiddleH - CuFrameH );
    G4cout<<"PTFEZ = "<<PTFEZ<<G4endl;
    PTFEPos         = G4ThreeVector( 0, 0, PTFEZ );
    PTFESourcePos   = G4ThreeVector( 0, 0, PTFEZ );

    // ----------
    // PTFE parts
    // ----------
    G4VSolid* PTFECorner = new G4Box( "PTFECorner",
				      0.5 * PTFECornerX,
				      0.5 * PTFECornerY,
				      0.5 * PTFECornerH );
    G4VSolid* PTFECornerDiagHole = new G4Box( "PTFECornerDiagHole",
					      0.5 * PTFECornerDiagHoleX,
					      0.5 * PTFECornerDiagHoleX,
					      PTFECornerH );

    PTFECorner = new G4SubtractionSolid( "PTFECorner",
					 PTFECorner,
					 PTFECornerDiagHole,
					 PTFECornerDiagHoleRot,
					 PTFECornerDiagHolePos );

    G4VSolid* PTFECornerTopHole = new G4Box( "PTFECornerTopHole",
					     PTFECornerTopHoleX,
					     PTFECornerTopHoleX,
					     PTFECornerTopHoleH );

    for( unsigned int i=0; i<PTFECornerTopHolePos.size(); i++ ){
        PTFECorner = new G4SubtractionSolid( "PTFECorner",
                            PTFECorner,
                            PTFECornerTopHole,
                            PTFECornerTopHoleRot[i],
                            PTFECornerTopHolePos[i] );
    }

    G4VSolid* PTFECornerXHole = new G4Box( "PTFECornerXHole",
					   PTFECornerXHoleX,
					   PTFECornerXHoleY,
					   0.5 * PTFECornerXHoleH );

    PTFECorner = new G4SubtractionSolid( "PTFECorner",
					 PTFECorner,
					 PTFECornerXHole,
					 PTFECornerXHoleRot,
					 PTFECornerXHolePos );

    G4VSolid* PTFECornerYHole = new G4Box( "PTFECornerYHole",
					   PTFECornerYHoleX,
					   PTFECornerYHoleY,
					   0.5 * PTFECornerYHoleH );

    PTFECorner = new G4SubtractionSolid( "PTFECorner",
					 PTFECorner,
					 PTFECornerYHole,
					 PTFECornerYHoleRot,
					 PTFECornerYHolePos );

    G4Tubs* PTFEButterflyBottom = new G4Tubs( "PTFE",
					      0.,
					      PTFEButterflyBottomR,
					      0.5 * PTFEButterflyBottomH,
					      0.,
					      360. * deg );

    G4Tubs* PTFEButterflyTop = new G4Tubs( "PTFE",
					   0.,
					   PTFEButterflyTopR,
					   0.5 * PTFEButterflyTopH,
					   0.,
					   360. * deg );

    G4VSolid* PTFEButterflyFlap = new G4Box( "PTFEButterflyFlap",
					     0.5 * PTFEButterflyFlapX,
					     0.5 * PTFEButterflyFlapY,
					     0.5 * PTFEButterflyFlapH );

    G4Tubs* PTFESmallCap = new G4Tubs( "PTFE",
				       0.,
				       PTFESmallCapR,
				       0.5 * PTFESmallCapH,
				       0.,
				       360. * deg );

    G4Tubs* PTFELargeCap = new G4Tubs( "PTFE",
				       0.,
				       PTFELargeCapR,
				       0.5 * PTFELargeCapH,
				       0.,
				       360. * deg );

    G4UnionSolid* PTFECap = new G4UnionSolid( "PTFE",
					      PTFELargeCap,
					      PTFESmallCap,
					      0,
					      G4ThreeVector( 0., 0., 0.5 * ( PTFELargeCapH + PTFESmallCapH ) ) );

    G4MultiUnion* PTFE = new G4MultiUnion( PTFEName );
    /* for( unsigned int i=0; i<PTFECornerTrans.size(); i++ )
    	PTFE->AddNode( *PTFECorner, *PTFECornerTrans[i] );
    for( unsigned int i=0; i<PTFEButterflyTopTrans.size(); i++ )
    	PTFE->AddNode( *PTFEButterflyTop, *PTFEButterflyTopTrans[i] );
    for( unsigned int i=0; i<PTFEButterflyBottomTrans.size(); i++ )
    	PTFE->AddNode( *PTFEButterflyBottom, *PTFEButterflyBottomTrans[i] );
    for( unsigned int i=0; i<PTFEButterflyFlapTrans.size(); i++ )
    	PTFE->AddNode( *PTFEButterflyFlap, *PTFEButterflyFlapTrans[i] );
    for( unsigned int i=0; i<PTFELargeCapTrans.size(); i++ )
    	PTFE->AddNode( *PTFELargeCap, *PTFELargeCapTrans[i] );
    for( unsigned int i=0; i<PTFESmallCapTrans.size(); i++ )
    	PTFE->AddNode( *PTFESmallCap, *PTFESmallCapTrans[i] ); */
        
    G4cout<<"FLAG = "<<PTFEButterflyTopTrans.size()<<G4endl;
    

    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[0] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[1] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[2] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[3] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[4] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[5] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[6] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[7] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[8] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[9] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[10] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[11] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[12] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[13] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[14] );
    PTFE->AddNode( *PTFECorner, *PTFECornerTrans[15] );

    PTFE->AddNode( *PTFEButterflyTop, *PTFEButterflyTopTrans[0] );
    PTFE->AddNode( *PTFEButterflyTop, *PTFEButterflyTopTrans[1] );
    PTFE->AddNode( *PTFEButterflyTop, *PTFEButterflyTopTrans[2] );
    PTFE->AddNode( *PTFEButterflyTop, *PTFEButterflyTopTrans[3] );
    PTFE->AddNode( *PTFEButterflyTop, *PTFEButterflyTopTrans[4] );
    PTFE->AddNode( *PTFEButterflyTop, *PTFEButterflyTopTrans[5] );
    //PTFE->AddNode( *PTFEButterflyTop, *PTFEButterflyTopTrans[6] );  // Ne marche pas pourquoi ??????????????????????
    //PTFE->AddNode( *PTFEButterflyTop, *PTFEButterflyTopTrans[7] );  //

    PTFE->AddNode( *PTFEButterflyBottom, *PTFEButterflyBottomTrans[0] );
    PTFE->AddNode( *PTFEButterflyBottom, *PTFEButterflyBottomTrans[1] );
    PTFE->AddNode( *PTFEButterflyBottom, *PTFEButterflyBottomTrans[2] );
    PTFE->AddNode( *PTFEButterflyBottom, *PTFEButterflyBottomTrans[3] );
    PTFE->AddNode( *PTFEButterflyBottom, *PTFEButterflyBottomTrans[4] );
    PTFE->AddNode( *PTFEButterflyBottom, *PTFEButterflyBottomTrans[5] );
    PTFE->AddNode( *PTFEButterflyBottom, *PTFEButterflyBottomTrans[6] );
    PTFE->AddNode( *PTFEButterflyBottom, *PTFEButterflyBottomTrans[7] );

    PTFE->AddNode( *PTFEButterflyFlap, *PTFEButterflyFlapTrans[0] );
    PTFE->AddNode( *PTFEButterflyFlap, *PTFEButterflyFlapTrans[1] );
    PTFE->AddNode( *PTFEButterflyFlap, *PTFEButterflyFlapTrans[2] );
    PTFE->AddNode( *PTFEButterflyFlap, *PTFEButterflyFlapTrans[3] );
    PTFE->AddNode( *PTFEButterflyFlap, *PTFEButterflyFlapTrans[4] );
    PTFE->AddNode( *PTFEButterflyFlap, *PTFEButterflyFlapTrans[5] );
    PTFE->AddNode( *PTFEButterflyFlap, *PTFEButterflyFlapTrans[6] );
    PTFE->AddNode( *PTFEButterflyFlap, *PTFEButterflyFlapTrans[7] );


    PTFE->Voxelize();

    SolidPTFE = PTFE;

    LogicalPTFE = new G4LogicalVolume( SolidPTFE,      Teflon,    PTFEName,       0, 0, 0 );
    SetLogicalVolumeColor(LogicalPTFE, PTFEColor);

    PhysicalPTFE = new G4PVPlacement(
        G4Transform3D(DontRotate, moduleCoords+G4ThreeVector(26.5 * mm, 0 * mm, -49 * mm + 9.5 * mm)),
        LogicalPTFE, PTFEName, motherLogical, false, 0);
}

/**
 * @brief Construct the PEN Flaps.
 */
/* void SCOPSimGeometryConstruction::ConstructPEN() {

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

    // ---------
    // PEN parts
    // ---------

    G4VSolid* PENBand = new G4Box( "PENBand",
				   0.5 * PENBandX,
				   0.5 * PENBandY,
				   0.5 * PENBandH );


    G4VSolid* PENBandHole1 = new G4Box( "PENBandHole1",
					PENBandHole1X,
					PENBandHole1Y,
					0.5 * PENBandHole1H );

    G4VSolid* PENBandHole2 = new G4Box( "PENBandHole2",
					PENBandHole2X,
					PENBandHole2Y,
					0.5 * PENBandHole2H );

    G4VSolid* PENBandHole3 = new G4Box( "PENBandHole3",
					PENBandHole3X,
					PENBandHole3Y,
					0.5 * PENBandHole3H );

    for( unsigned int f=0; f<PENBandHole1Pos.size(); f++ )
	PENBand = new G4SubtractionSolid( "PENBand",
					  PENBand,
					  PENBandHole1,
					  0,
					  PENBandHole1Pos[f] );

    for( unsigned int f=0; f<PENBandHole2Pos.size(); f++ )
	PENBand = new G4SubtractionSolid( "PENBand",
					  PENBand,
					  PENBandHole2,
					  0,
					  PENBandHole2Pos[f] );

    for( unsigned int f=0; f<PENBandHole3Pos.size(); f++ )
	PENBand = new G4SubtractionSolid( "PENBand",
					  PENBand,
					  PENBandHole3,
					  0,
					  PENBandHole3Pos[f] );

    G4VSolid* PENBandLittleHole = new G4Tubs( "PENBandLittleHole",
					      0.,
					      PENBandLittleHoleR,
					      2. * PENBandY,
					      0.,
					      360. * deg );

    for( unsigned int f=0; f<PENBandLittleHolePos.size(); f++ )
	PENBand = new G4SubtractionSolid( "PENLatBand",
					  PENBand,
					  PENBandLittleHole,
					  PENBandLittleHoleRot[f],
					  PENBandLittleHolePos[f] );

    G4VSolid* PENFlap = new G4Box( "PENFlap",
				   0.5 * PENFlapX,
				   0.5 * PENFlapY + 0.5 * PENFlapT,
				   0.5 * PENFlapH + 0.5 * PENFlapT );

    G4VSolid* PENFlapHole = new G4Box( "PENFlapHole",
				       PENFlapX,
				       PENFlapY,
				       PENFlapH );

    PENFlap = new G4SubtractionSolid( "PENFlap",
				      PENFlap,
				      PENFlapHole,
				      0,
				      G4ThreeVector( 0.,
						     0.5 * ( PENFlapY + PENFlapT ),
						     -0.5 * ( PENFlapH + PENFlapT ) ) );


    G4MultiUnion* PEN = new G4MultiUnion( "PEN" );
    for( unsigned int i=0; i<PENBandTrans.size(); i++ )
    	PEN->AddNode( *PENBand, *PENBandTrans[i] );
    for( unsigned int i=0; i<PENFlapTrans.size(); i++ )
    	PEN->AddNode( *PENFlap, *PENFlapTrans[i] );

    PEN->Voxelize();

    fPENSolid = PEN;
}
 */
/**
 * @brief Construct the LMO part.
 */
void SCOPSimGeometryConstruction::ConstructLMO(G4ThreeVector  moduleCoords,
                                            G4String LMO1Name,
                                            G4String LMO2Name,
                                            G4String LMO1Color,
                                            G4String LMO2Color,
                                            G4LogicalVolume* motherLogical,
                                            G4bool buildTwoLMOs = true) {
    auto Vacuum = SCOPSimMaterials::getInstance()->getMaterial("Vacuum");
    auto Li2MoO4 = SCOPSimMaterials::getInstance()->getMaterial("Li2MoO4");
    G4MaterialPropertiesTable *mpt = Li2MoO4->GetMaterialPropertiesTable();

    LogicalLMO1 = Geom->GetBoxVolume(LMO1Name, Li2MoO4, fLMOLength, fLMOWidth, fLMOThickness);

    SetLogicalVolumeColor(LogicalLMO1, LMO1Color);

    PhysicalLMO1 = new G4PVPlacement(G4Transform3D(DontRotate,
        moduleCoords+G4ThreeVector(fLMOx, fLMOy, fLMOz)),
        LogicalLMO1, LMO1Name, motherLogical, false, 0);
    
    if (buildTwoLMOs){ // build the second LMO of the module
        LogicalLMO2 = Geom->GetBoxVolume(LMO2Name, Li2MoO4, fLMOLength, fLMOWidth, fLMOThickness);
        SetLogicalVolumeColor(LogicalLMO2, LMO2Color);
        PhysicalLMO2 = new G4PVPlacement(G4Transform3D(DontRotate,
            fOffsetBetweenLMO+moduleCoords+G4ThreeVector(fLMOx, fLMOy, fLMOz)),
            LogicalLMO2, LMO2Name, motherLogical, false, 0);
    }


    // Surface properties

    auto opLMOSurface = new G4OpticalSurface("LMOSurface");

    if (!diffLMOsurfaces){

        if (fLMOSurfaceType=="dielectric_dielectric"){opLMOSurface->SetType(dielectric_dielectric);}
        if (fLMOSurfaceFinish=="ground"){opLMOSurface->SetFinish(ground);}
        if (fLMOSurfaceFinish=="polished"){opLMOSurface->SetFinish(polished);}
        if (fLMOSurfaceModel=="unified"){opLMOSurface->SetModel(unified);}
        if (fLMOSurfaceModel=="glisur"){opLMOSurface->SetModel(glisur);}

        if (fLMOSurfacePolish >= 0.){
            opLMOSurface->SetPolish(fLMOSurfacePolish);
        }

        if (fLMOSurfaceSigmaAlpha >= 0.){
            opLMOSurface->SetSigmaAlpha(fLMOSurfaceSigmaAlpha);
        }

        auto LMOSurface1 = new G4LogicalSkinSurface("LMOSurface", LogicalLMO1, opLMOSurface);
        if (buildTwoLMOs){
            auto LMOSurface2 = new G4LogicalSkinSurface("LMO2Surface", LogicalLMO2, opLMOSurface);
        }
    }

    // Differents surface finishes

    else {
        G4double LMOSurfWidth = 0.1 * mm;

        G4VSolid* SolidLMOSurf1 = new G4Box("LMOSurf1", fLMOLength/2, fLMOWidth/2, LMOSurfWidth/2);
        G4VSolid* SolidLMOSurf2 = new G4Box("LMOSurf2", fLMOLength/2, fLMOWidth/2, LMOSurfWidth/2);
        G4VSolid* SolidLMOSurf3 = new G4Box("LMOSurf3", fLMOLength/2, LMOSurfWidth/2, fLMOThickness/2);
        G4VSolid* SolidLMOSurf4 = new G4Box("LMOSurf4", fLMOLength/2, LMOSurfWidth/2, fLMOThickness/2);
        G4VSolid* SolidLMOSurf5 = new G4Box("LMOSurf5", LMOSurfWidth/2, fLMOWidth/2, fLMOThickness/2);
        G4VSolid* SolidLMOSurf6 = new G4Box("LMOSurf6", LMOSurfWidth/2, fLMOWidth/2, fLMOThickness/2);
        LogicalLMOSurf1 = new G4LogicalVolume(SolidLMOSurf1, Vacuum, "LMOSurf1", 0, 0, 0);
        LogicalLMOSurf2 = new G4LogicalVolume(SolidLMOSurf2, Vacuum, "LMOSurf2", 0, 0, 0);
        LogicalLMOSurf3 = new G4LogicalVolume(SolidLMOSurf3, Vacuum, "LMOSurf3", 0, 0, 0);
        LogicalLMOSurf4 = new G4LogicalVolume(SolidLMOSurf4, Vacuum, "LMOSurf4", 0, 0, 0);
        LogicalLMOSurf5 = new G4LogicalVolume(SolidLMOSurf5, Vacuum, "LMOSurf5", 0, 0, 0);
        LogicalLMOSurf6 = new G4LogicalVolume(SolidLMOSurf6, Vacuum, "LMOSurf6", 0, 0, 0);
        SetLogicalVolumeColor(LogicalLMOSurf1, "green");
        SetLogicalVolumeColor(LogicalLMOSurf2, "green");
        SetLogicalVolumeColor(LogicalLMOSurf3, "red");
        SetLogicalVolumeColor(LogicalLMOSurf4, "red");
        SetLogicalVolumeColor(LogicalLMOSurf5, "red");
        SetLogicalVolumeColor(LogicalLMOSurf6, "red");
        
        PhysicalLMOSurf1 = new G4PVPlacement(G4Transform3D(DontRotate, moduleCoords +
            G4ThreeVector(fLMOx, fLMOy, fLMOz + fLMOThickness/2 + LMOSurfWidth/2)),LogicalLMOSurf1, "LMOSurf1", LogicalHolder, false, 0);
        PhysicalLMOSurf2 = new G4PVPlacement(G4Transform3D(DontRotate, moduleCoords +
            G4ThreeVector(fLMOx, fLMOy, fLMOz - fLMOThickness/2 - LMOSurfWidth/2)),LogicalLMOSurf2, "LMOSurf2", LogicalHolder, false, 0);
        PhysicalLMOSurf3 = new G4PVPlacement(G4Transform3D(DontRotate, moduleCoords +
            G4ThreeVector(fLMOx, fLMOy + fLMOWidth/2 + LMOSurfWidth/2, fLMOz)),LogicalLMOSurf3, "LMOSurf3", LogicalHolder, false, 0);
        PhysicalLMOSurf4 = new G4PVPlacement(G4Transform3D(DontRotate, moduleCoords +
            G4ThreeVector(fLMOx, fLMOy - fLMOWidth/2 - LMOSurfWidth/2, fLMOz)),LogicalLMOSurf4, "LMOSurf4", LogicalHolder, false, 0);
        PhysicalLMOSurf5 = new G4PVPlacement(G4Transform3D(DontRotate, moduleCoords +
            G4ThreeVector(fLMOx + fLMOLength/2 + LMOSurfWidth/2, fLMOy, fLMOz)),LogicalLMOSurf5, "LMOSurf5", LogicalHolder, false, 0);
        PhysicalLMOSurf6 = new G4PVPlacement(G4Transform3D(DontRotate, moduleCoords +
            G4ThreeVector(fLMOx - fLMOLength/2 - LMOSurfWidth/2, fLMOy, fLMOz)),LogicalLMOSurf6, "LMOSurf6", LogicalHolder, false, 0);
    
        auto opLMOSurfaceRough = new G4OpticalSurface("LMOSurfaceRough");
        auto opLMOSurfacePolished = new G4OpticalSurface("LMOSurfacePolished");

        opLMOSurfaceRough->SetType(dielectric_dielectric);
        opLMOSurfaceRough->SetModel(unified);
        opLMOSurfaceRough->SetFinish(ground);
        opLMOSurfacePolished->SetType(dielectric_dielectric);
        opLMOSurfacePolished->SetModel(unified);
        opLMOSurfacePolished->SetFinish(polished);

        auto LMO1SurfBorder1 = new G4LogicalBorderSurface("LMOSurfBorder1", PhysicalLMO1, PhysicalLMOSurf1, opLMOSurfaceRough);
        auto LMO1SurfBorder2 = new G4LogicalBorderSurface("LMOSurfBorder2", PhysicalLMO1, PhysicalLMOSurf2, opLMOSurfaceRough);
        auto LMO1SurfBorder3 = new G4LogicalBorderSurface("LMOSurfBorder3", PhysicalLMO1, PhysicalLMOSurf3, opLMOSurfacePolished);
        auto LMO1SurfBorder4 = new G4LogicalBorderSurface("LMOSurfBorder4", PhysicalLMO1, PhysicalLMOSurf4, opLMOSurfacePolished);
        auto LMO1SurfBorder5 = new G4LogicalBorderSurface("LMOSurfBorder5", PhysicalLMO1, PhysicalLMOSurf5, opLMOSurfacePolished);
        auto LMO1SurfBorder6 = new G4LogicalBorderSurface("LMOSurfBorder6", PhysicalLMO1, PhysicalLMOSurf6, opLMOSurfacePolished);
        auto SurfLMO1Border1 = new G4LogicalBorderSurface("SurfLMOBorder1", PhysicalLMOSurf1, PhysicalLMO1, opLMOSurfaceRough);
        auto SurfLMO1Border2 = new G4LogicalBorderSurface("SurfLMOBorder2", PhysicalLMOSurf2, PhysicalLMO1, opLMOSurfaceRough);
        auto SurfLMO1Border3 = new G4LogicalBorderSurface("SurfLMOBorder3", PhysicalLMOSurf3, PhysicalLMO1, opLMOSurfacePolished);
        auto SurfLMO1Border4 = new G4LogicalBorderSurface("SurfLMOBorder4", PhysicalLMOSurf4, PhysicalLMO1, opLMOSurfacePolished);
        auto SurfLMO1Border5 = new G4LogicalBorderSurface("SurfLMOBorder5", PhysicalLMOSurf5, PhysicalLMO1, opLMOSurfacePolished);
        auto SurfLMO1Border6 = new G4LogicalBorderSurface("SurfLMOBorder6", PhysicalLMOSurf6, PhysicalLMO1, opLMOSurfacePolished);
    }
}

/**
 * @brief Construct the Light Detector part.
 */
void SCOPSimGeometryConstruction::ConstructLD(G4ThreeVector moduleCoords,
                                            G4String LD1Name,
                                            G4String LD2Name,
                                            G4String LD3Name,
                                            G4String LD4Name,
                                            G4String LD1LD2Color,
                                            G4String LD3LD4Color,
                                            G4LogicalVolume* motherLogical,
                                            G4bool buildTwoLDs = true
                                        ) {
    auto matLD = SCOPSimMaterials::getInstance()->getMaterial(fLDMaterial);

    // Octogonal Germanium LD dimensions //

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
    
    // LD1 | LD2 //
    LogicalLD1 = Geom->GetOctogonalVolume(LD1Name, matLD, LDPolygon, LDThickness);
    LogicalLD2 = Geom->GetOctogonalVolume(LD2Name, matLD, LDPolygon, LDThickness);
    SetLogicalVolumeColor(LogicalLD1, LD1LD2Color);
    SetLogicalVolumeColor(LogicalLD2, LD1LD2Color);
    PhysicalLD1 = new G4PVPlacement(
        G4Transform3D(DontRotate, moduleCoords+G4ThreeVector(0. * mm, 0 * mm, -fLMOThickness/2 - fDistanceLMOtoLD1 - LDThickness/2 )),
        LogicalLD1, LD1Name, motherLogical, false, 0);
    PhysicalLD2 = new G4PVPlacement(
        G4Transform3D(DontRotate, moduleCoords+G4ThreeVector(0. * mm, 0 * mm, fLMOThickness/2 + fDistanceLMOtoLD2 + LDThickness/2 )),
        LogicalLD2, LD2Name, motherLogical, false, 0);

    // LD3 | LD4 //
    if (buildTwoLDs){
        LogicalLD3 = Geom->GetOctogonalVolume(LD3Name, matLD, LDPolygon, LDThickness);
        LogicalLD4 = Geom->GetOctogonalVolume(LD4Name, matLD, LDPolygon, LDThickness);
        SetLogicalVolumeColor(LogicalLD3, LD3LD4Color);
        SetLogicalVolumeColor(LogicalLD4, LD3LD4Color);
        PhysicalLD3 = new G4PVPlacement(
            G4Transform3D(DontRotate,moduleCoords+fOffsetBetweenLMO+G4ThreeVector(0. * mm, 0 * mm, -fLMOThickness/2 - fDistanceLMOtoLD1 - LDThickness/2 )),
            LogicalLD3, LD3Name, motherLogical, false, 0);
        PhysicalLD4 = new G4PVPlacement(
            G4Transform3D(DontRotate, moduleCoords+fOffsetBetweenLMO+G4ThreeVector(0. * mm, 0 * mm, fLMOThickness/2 + fDistanceLMOtoLD2 + LDThickness/2 )),
            LogicalLD4, LD4Name, motherLogical, false, 0);
    }

    // SiO coating //
    G4MaterialPropertiesTable *mptLDcoating = new G4MaterialPropertiesTable();
    G4cout<<"fLDCoatingRINDEX = "<<fLDCoatingRINDEX<<G4endl;
    G4cout<<"fLDCoatingThickness = "<<fLDCoatingThickness<<G4endl;
    std::vector<G4double> refractive_index_coating = {fLDCoatingRINDEX, fLDCoatingRINDEX}; // 2.48
    std::vector<G4double> energy_coating = {0.1 * eV, 50 * eV};
    mptLDcoating->AddProperty("COATEDRINDEX", energy_coating, refractive_index_coating);
    mptLDcoating->AddConstProperty("COATEDTHICKNESS", fLDCoatingThickness * nm);
    mptLDcoating->AddConstProperty("COATEDFRUSTRATEDTRANSMISSION", 1);
    
    auto opLDSurface = new G4OpticalSurface("LDSurface");
    opLDSurface->SetType(coated);
    opLDSurface->SetFinish(polished);
    opLDSurface->SetModel(unified);
    opLDSurface->SetMaterialPropertiesTable(mptLDcoating);

    auto LD1Surface = new G4LogicalBorderSurface("VacuumLD", PhysicalHolder, PhysicalLD1, opLDSurface);
    auto LD2Surface = new G4LogicalBorderSurface("VacuumLD", PhysicalHolder, PhysicalLD2, opLDSurface);
    if (buildTwoLDs){
        auto LD3Surface = new G4LogicalBorderSurface("VacuumLD", PhysicalHolder, PhysicalLD3, opLDSurface);
        auto LD4Surface = new G4LogicalBorderSurface("VacuumLD", PhysicalHolder, PhysicalLD4, opLDSurface);
    }
}

/**
 * @brief Construct one module with 2 LMOs, 4 LDs, CuFrame and PTFE.
 * Input: center coordinates of the module
 */
void SCOPSimGeometryConstruction::ConstructPrimaryModule() {

    ConstructLMO(G4ThreeVector(0*mm, 0*mm, 0*mm), "LMO", "LMOdead", "blue", "blueAlpha", LogicalHolder, buildSecModules);
    ConstructLD(G4ThreeVector(0*mm, 0*mm, 0*mm), "LD1", "LD2", "LD3dead", "LD4dead", "yellow", "yellowAlpha", LogicalHolder, buildSecModules);
    if (buildStructure){
        ConstructPTFE(G4ThreeVector(0*mm, 0*mm, 0*mm), "PTFE", "gray", LogicalHolder);
        ConstructCopperFrame(G4ThreeVector(0*mm, 0*mm, 0*mm), "CuFrame", "orange", LogicalHolder);
    }
}

/**
 * @brief Construct one module with 2 LMOs, 4 LDs, CuFrame and PTFE.
 * Input: center coordinates of the module
 */
void SCOPSimGeometryConstruction::ConstructSecondaryModules() {

    auto Vacuum = SCOPSimMaterials::getInstance()->getMaterial("Vacuum");

    auto SolidModule = new G4Box("Module", 0.5*112*mm, 0.5*80*mm, 0.5*(80)*mm);
    auto LogicalModule = new G4LogicalVolume(SolidModule, Vacuum, "Module");
    ConstructLMO(G4ThreeVector(-28*mm, 0*mm, 0*mm), "secLMO1", "secLMO2", "blueAlpha", "blueAlpha", LogicalModule);
    ConstructLD(G4ThreeVector(-28*mm, 0*mm, 0*mm), "secLD1", "secLD2", "secLD3", "secLD4", "yellowAlpha", "yellowAlpha", LogicalModule);
    if (buildStructure){
        ConstructPTFE(G4ThreeVector(-28*mm, 0*mm, 0*mm), "secPTFE", "grayAlpha", LogicalModule);
        ConstructCopperFrame(G4ThreeVector(-28*mm, 0*mm, 0*mm), "secCuFrame", "orangeAlpha", LogicalModule);
    }
    new G4PVPlacement(nullptr, G4ThreeVector(28*mm, -80*mm, 0*mm), LogicalModule, "Module", LogicalHolder, false, 1);
    new G4PVPlacement(nullptr, G4ThreeVector(28*mm, 80*mm, 0*mm), LogicalModule, "Module", LogicalHolder, false, 2);
    new G4PVPlacement(nullptr, G4ThreeVector(28*mm-112*mm, -80*mm, 0*mm), LogicalModule, "Module", LogicalHolder, false, 3);
    new G4PVPlacement(nullptr, G4ThreeVector(28*mm-112*mm, 0*mm, 0*mm), LogicalModule, "Module", LogicalHolder, false, 4);
    new G4PVPlacement(nullptr, G4ThreeVector(28*mm-112*mm, 80*mm, 0*mm), LogicalModule, "Module", LogicalHolder, false, 5);
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
G4VPhysicalVolume *SCOPSimGeometryConstruction::Construct() {
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

    // --- Geometry conditions -------------------------------------------------
    buildSecModules = false;     // build secondary modules
    buildStructure = true;       // build structure volumes (Copper, PTFE)
    diffLMOsurfaces = false;     // use 6 differents surface states for the LMO

    if (buildStructure){         // ensure that we don't use 6 surfaces for the
        diffLMOsurfaces = false; // LMO when the structure is build, to avoid
    }                            // overlaps between surface volumes and structure


    // --- Construct Volumes ---------------------------------------------------
    CreateWorldAndHolder();          // construct the world and main holder volume
    ConstructPrimaryModule();        // contruct primary module
    if (buildSecModules){
        ConstructSecondaryModules(); // contruct secondary modules
    }

    G4cout << "END OF THE DETECTOR CONSTRUCTION" << G4endl;

    // --- Return the fully constructed world volume ---------------------------
    return PhysicalWorld;
}
