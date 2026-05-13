/**
 * @file Geometry.cc
 * @brief Implementation of the Geometry class for the SCOPSim.
 *
 * This file implements the methods defined in Geometry.hh to construct and
 * retrieve Geant4 geometry volumes used in the optical simulation framework.
 * It provides functions to:
 *   - Load GDML-defined volumes and assign materials.
 *   - Create simplified box/tubs volumes.
 *   - Create specific 5" PMT from SuperNEMO
 *
 * The Geometry class acts as a utility for building and managing
 * logical volumes in Geant4 simulations, facilitating the definition
 * of both realistic and simplified detector components.
 *
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 */

#include "Geometry.hh"

// ***********************
// Constructor
// ***********************

/**
 * @brief Default constructor.
 *
 * Initializes internal pointers and sets up the geometry environment.
 */
Geometry::Geometry() {}

// ***********************
// Destructor
// ***********************

/**
 * @brief Destructor.
 *
 * Cleans up any allocated resources associated with the geometry.
 */
Geometry::~Geometry() {}

/**
 * @brief Load and retrieve a GDML-defined volume.
 *
 * This method uses a GDML parser to read a geometry description from a GDML
 * file, retrieve the specified volume, and assign it the provided material.
 *
 * @param path Path to the GDML file.
 * @param VName Name of the volume inside the GDML file.
 * @param material Material to assign to the retrieved logical volume.
 * @return Pointer to the created G4LogicalVolume.
 */
G4LogicalVolume *Geometry::GetGDMLVolume(const char *path, const char *VName,
                                         G4Material *material) {
    G4GDMLParser *parser = new G4GDMLParser();
    // Create tessellated volume of the requested component
    parser->Clear();
    parser->Read(G4String(path), false);
    LogicalVolume = parser->GetVolume(G4String(VName));
    LogicalVolume->SetMaterial(material);

    return LogicalVolume;
}

/**
 * @brief Create a Box volume.
 *
 * Constructs a simple box volume with the given dimensions and assigns it a
 * given material.
 *
 * @param name Name of the quadrupole logical volume.
 * @param material G4Material defined
 * @param dx Size of the box along the X-axis [mm].
 * @param dy Size of the box along the Y-axis [mm].
 * @param dz Size of the box along the Z-axis [mm].
 * @return Pointer to the created G4LogicalVolume.
 */
G4LogicalVolume *Geometry::GetBoxVolume(G4String name, G4Material *material,
                                        G4double dx, G4double dy, G4double dz) {
    Box = new G4Box(name, dx / 2 * CLHEP::mm, dy / 2 * CLHEP::mm,
                    dz / 2 * CLHEP::mm);

    LogicalVolume = new G4LogicalVolume(Box, material, name, 0, 0, 0);

    return LogicalVolume;
}

/**
 * @brief Create LD volume.
 *
 *
 * @param name Name of the quadrupole logical volume.
 * @param material G4Material defined
 * @param dx Size of the box along the X-axis [mm].
 * @param dy Size of the box along the Y-axis [mm].
 * @param dz Size of the box along the Z-axis [mm].
 * @return Pointer to the created G4LogicalVolume.
 */
G4LogicalVolume *Geometry::GetOctogonalVolume(G4String name, G4Material *material, std::vector<G4TwoVector> LDpolygon, G4double LDthickness) {


    G4TwoVector offA(0,0);
    G4TwoVector offB(0,0);
    G4double scaleA = 1;
    G4double scaleB = 1;

    Octogon = new G4ExtrudedSolid(name,
					  LDpolygon,
					  0.5 * LDthickness,
					  offA,
					  scaleA,
					  offB,
					  scaleB );

    LogicalVolume = new G4LogicalVolume(Octogon, material, name, 0, 0, 0);

    return LogicalVolume;
}

/**
 * @brief Create a Tubs volume.
 *
 * Constructs a simple tubs volume with the given dimensions and assigns it a
 * given material.
 * @param name Name of the Box volume.
 * @param material G4Material defined
 * @param rint internal radius.
 * @param rext external radius.
 * @param dz dz length.
 * @return Pointer to the created G4LogicalVolume.
 */
G4LogicalVolume *Geometry::GetTubsVolume(G4String name, G4Material *material,
                                         G4double rint, G4double rext,
                                         G4double dz) {
    G4Tubs *Tubs = new G4Tubs(name, rint, rext, dz, 0, 360 * deg);

    LogicalVolume = new G4LogicalVolume(Tubs, material, name, 0, 0, 0);

    return LogicalVolume;
}
