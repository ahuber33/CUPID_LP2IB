#ifndef AgataAbstractGeometry_h
#define AgataAbstractGeometry_h 1

#include <map>
#include <vector>

// Prevent compiler from complaining about the use in TString
// of a variable 's' already declared as global by CLHEP
#pragma GCC diagnostic ignored "-Wshadow"

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VisAttributes;
class DistributedSource;

class AgataGeometricParameters;
class AgataVolume;

class AgataAbstractGeometry
{

protected:

    enum Color{ kTransparent, kWhite, kBlack, kRed, kBlue, kLightBlue, kGreen, kYellow, kOrange, kBrown, kPink, kMagenta, kGray, kDarkGray };

    std::map<std::string, G4Material*> fMaterialMap;
    G4VPhysicalVolume*                 fMother;
    G4double                           fMaxAngle;
    G4int                              fNCrystals;
    G4int                              fNLightDetectors;

    void SetColor( G4LogicalVolume* volume,
		   Color color );
    G4VisAttributes* GetColor( Color color );
    void AddVolumeToMap( std::string name );
    void AddVolumeToMap( G4VSolid* solid,
			 G4LogicalVolume* logical,
			 G4VPhysicalVolume* physical,
			 G4bool draw,
			 G4bool issensitive,
			 G4bool issource,
			 G4bool checkoverlapforthis,
			 G4bool istrigger );
    void AddSolidToList( G4VSolid* solid );
    void AddLogicalToList( G4LogicalVolume* logical );
    void AddPhysicalToList( G4VPhysicalVolume* physical );
    G4VPhysicalVolume*  CreatePhysicalVolume( G4VSolid*          solid,
					      G4LogicalVolume*   logical,
					      G4VPhysicalVolume* mother,
					      G4ThreeVector      pos,
					      G4ThreeVector      sourcePos,
					      Color              color,
					      G4bool             issensitive=false,
					      G4int              copyNumber=0,
					      G4RotationMatrix*  rotation=0,
					      G4bool             istrigger=false );

    void Initialize( G4VPhysicalVolume*                 mother,
		     std::map<std::string, G4Material*> materialMap,
		     std::vector<G4int>                 deactivatedVolumes,
		     std::vector<G4int>                 onlyDrawVolumes,
		     std::vector<G4int>                 doNotDrawVolumes,
		     G4bool                             checkOverlaps=false,
		     G4int                              overlapVolume=0,
		     G4int                              nOverlapTests=true,
		     G4String                           sourceElementName="",
		     std::vector<DistributedSource*>* source=0,
		     G4double                           maxAngle=360. );

private:

    std::vector<G4int>                 fDeactivatedVolumes;
    std::vector<G4int>                 fOnlyDrawVolumes;
    std::vector<G4int>                 fDoNotDrawVolumes;
    G4bool                             fCheckOverlaps;
    G4int                              fOverlapVolume;
    G4int                              fNOverlapTests;
    G4String                           fSourceElementName;
    std::vector<DistributedSource*>* fSource;

    std::vector<G4LogicalVolume*>*     fLogicals;

    virtual void CreateSolids() = 0;
    virtual void CreateLogicalVolumes() = 0;
    virtual void CreatePhysicalVolumes() = 0;

public:

    AgataAbstractGeometry();
    ~AgataAbstractGeometry();

    G4int GetNCrystals()      { return fNCrystals;       };
    G4int GetNLightDetectors(){ return fNLightDetectors; };

    virtual void PrintCrystalPosition(std::ostream& oStream);
};

#endif
