#include "AgataAbstractGeometry.hh"
#include "AgataGeometricParameters.hh"
#include "AgataVolume.hh"
#include "AgataVolumeMap.hh"
#include "AgataConfigurator.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4VSolid.hh"
#include "DistributedSource.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"

#ifndef theVolumeMap
#define theVolumeMap AgataVolumeMap::GetInstance()
#endif

AgataAbstractGeometry::AgataAbstractGeometry()
{
    ;
}

AgataAbstractGeometry::~AgataAbstractGeometry()
{
    ;
}

void AgataAbstractGeometry::Initialize(
					G4VPhysicalVolume*                 mother,
					std::map<std::string, G4Material*> materialMap,
					std::vector<G4int>                 deactivatedVolumes,
					std::vector<G4int>                 onlyDrawVolumes,
					std::vector<G4int>                 doNotDrawVolumes,
					G4bool                             checkOverlaps,
					G4int                              overlapVolume,
					G4int                              nOverlapTests,
					G4String                           sourceElementName,
					std::vector<DistributedSource*>* source,
					G4double                           maxAngle )
{

    fMother             = mother;
    fMaterialMap        = materialMap;
    fDeactivatedVolumes = deactivatedVolumes;
    fOnlyDrawVolumes    = onlyDrawVolumes;
    fDoNotDrawVolumes   = doNotDrawVolumes;
    fCheckOverlaps      = checkOverlaps;
    fOverlapVolume      = overlapVolume;
    fNOverlapTests      = nOverlapTests;
    fSourceElementName  = sourceElementName;
    fSource             = source;
    fMaxAngle           = maxAngle * deg;
}

G4VisAttributes* AgataAbstractGeometry::GetColor( Color color )
{

    if( color == Color::kTransparent )
        return new G4VisAttributes(false);
    else if( color == Color::kWhite )
        return new G4VisAttributes( G4Colour( 1.0, 1.0, 1.0 ) );
    else if( color == Color::kBlack )
        return new G4VisAttributes( G4Colour( 0.0, 0.0, 0.0 ) );
    else if( color == Color::kRed )
        return new G4VisAttributes( G4Colour( 1.0, 0.0, 0.0 ) );
    else if( color == Color::kBlue )
        return new G4VisAttributes( G4Colour( 0.0, 0.0, 1.0 ) );
    else if( color == Color::kLightBlue )
        return new G4VisAttributes( G4Colour( 0.8, 0.9, 1.0 ) );
    else if( color == Color::kGreen )
        return new G4VisAttributes( G4Colour( 0.0, 1.0, 0.0 ) );
    else if( color == Color::kYellow )
        return new G4VisAttributes( G4Colour( 1.0, 1.0, 0.0 ) );
    else if( color == Color::kOrange )
        return new G4VisAttributes( G4Colour( 1.0, 0.4, 0.0 ) );
    else if( color == Color::kBrown )
        return new G4VisAttributes( G4Colour( 0.6, 0.3, 0.0 ) );
    else if( color == Color::kPink )
        return new G4VisAttributes( G4Colour( 1.0, 0.8, 0.9 ) );
    else if( color == Color::kMagenta )
        return new G4VisAttributes( G4Colour( 1.0, 0.4, 1.0 ) );
    else if( color == Color::kGray )
        return new G4VisAttributes( G4Colour( 0.9, 0.9, 0.9 ) );
    else if( color == Color::kDarkGray )
        return new G4VisAttributes( G4Colour( 0.4, 0.4, 0.4 ) );

    return 0;
}

void AgataAbstractGeometry::SetColor( G4LogicalVolume* volume,
				      Color color )
{
    volume->SetVisAttributes( GetColor( color ) );

    return;
}


void AgataAbstractGeometry::AddVolumeToMap( std::string name )
{

    G4int index = theVolumeMap.GetIndex( name, true );
    if( index != -1 )
	{
	    G4cout << "WARNING - AgataAbstractGeometry::AddVolumeToMap(): Volume "
		   << name << " added already." << G4endl;
	    return;
	}

    theVolumeMap.AddVolume( AgataVolume() );

    return;
}

void AgataAbstractGeometry::AddVolumeToMap( G4VSolid* solid,
					    G4LogicalVolume* logical,
					    G4VPhysicalVolume* physical,
					    G4bool draw,
					    G4bool issensitive,
					    G4bool issource,
					    G4bool checkoverlapforthis,
					    G4bool istrigger )
{

    std::string name = solid->GetName();
    if( theVolumeMap.GetIndex( name, true ) != -1 )
	{
	    G4cout << "WARNING - AgataAbstractGeometry::AddVolumeToMap(): Volume "
		   << name << " added already." << G4endl;
	    return;
	}

    theVolumeMap.AddVolume( AgataVolume( solid,
					logical,
					physical,
					draw,
					issensitive,
					issource,
					checkoverlapforthis,
					istrigger ) );

    return;
}

G4VPhysicalVolume*  AgataAbstractGeometry::CreatePhysicalVolume( G4VSolid*          solid,
								 G4LogicalVolume*   logical,
								 G4VPhysicalVolume* mother,
								 G4ThreeVector      pos,
								 G4ThreeVector      sourcePos,
								 Color              color,
								 G4bool             issensitive,
								 G4int              copyNumber,
								 G4RotationMatrix*  rotation,
								 G4bool             istrigger )
{

    // Check if a physical volume was already declared with this index
    // (valid for replicated volumes, e.g. crystals and towers)
    G4int index = theVolumeMap.GetIndex( solid->GetName(), true );
    if( index == -1 )
	index = theVolumeMap.GetSize();// Necessary for drawing

    // Erase elements that the user requires to eliminate (option -F)
    for( unsigned int i=0; i<fDeactivatedVolumes.size(); i++ )
	if( fDeactivatedVolumes[i] == index )
	    return 0;

    // Set color
    bool draw = false;

    if( fDoNotDrawVolumes.size() == 0 &&
	fOnlyDrawVolumes.size() == 0 )
	draw = true;
    else if( fDoNotDrawVolumes.size() > 0 )
	{
	    draw = true;
	    for( unsigned int i=0; i<fDoNotDrawVolumes.size(); i++ )
		if( fDoNotDrawVolumes[i] ==index )
		    draw = false;
	}
    else if( fOnlyDrawVolumes.size() > 0 )
	for( unsigned int i=0; i<fOnlyDrawVolumes.size(); i++ )
	    if( fOnlyDrawVolumes[i] == index )
		draw = true;

    if( draw )
	SetColor( logical, color );
    else
	SetColor( logical, kTransparent );

    // Create physical volume
    bool isMany = false;
    if( copyNumber > 0 ) isMany = true;
    G4VPhysicalVolume* Physical = new G4PVPlacement( rotation,
						     pos,
						     solid->GetName(),
						     logical,
						     mother,
						     isMany,
						     copyNumber );

    // Add this volume to source volume, if required
    G4bool issource = false;
    if( fSourceElementName == solid->GetName() )
	{

	    G4Transform3D transform;
	    if( rotation == 0 )
		transform = G4Transform3D( G4RotationMatrix(),
					   sourcePos );
	    else
		transform = G4Transform3D( *rotation,
					   sourcePos );

	    fSource->push_back( new DistributedSource( solid,
							 transform ) );
	    issource = true;
	}

    // Check overlaps, if required
    G4bool checkoverlapforthis = false;
    if( fCheckOverlaps &&
	( fOverlapVolume == 0  || fOverlapVolume == index ) )
	{
	    Physical->CheckOverlaps( fNOverlapTests );
	    checkoverlapforthis = true;
	}

    if( copyNumber == 0 )
	AddVolumeToMap( solid,
			logical,
			Physical,
			draw,
			issensitive,
			issource,
			checkoverlapforthis,
			istrigger );
    else
	{
	    G4int index = theVolumeMap.GetIndex( solid->GetName(), true );
	    theVolumeMap.AddCopy( index );
	}

    return Physical;
}

void AgataAbstractGeometry::PrintCrystalPosition(std::ostream& oStream) {
  oStream << "PrintCrystalPosition undefined for current geometry" << G4endl;
}
