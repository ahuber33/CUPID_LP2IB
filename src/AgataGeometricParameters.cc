#include "AgataGeometricParameters.hh"

// Static stuff
AgataGeometricParameters* AgataGeometricParameters::fInstance = 0;

AgataGeometricParameters::AgataGeometricParameters()
{
}

AgataGeometricParameters::~AgataGeometricParameters()
{
    ;
}

AgataGeometricParameters* AgataGeometricParameters::GetInstance()
{
    if( !fInstance )
    {
        fInstance = new AgataGeometricParameters();
        fInstance->Initialize();
    }

    return fInstance;
}

void AgataGeometricParameters::Initialize()
{

    // Gio, 13.03.20
    // Important note on positioning of all volumes:
    // the zero in the Z direction corresponds to the bottom
    // of the polyethylene (PE) shielding. The external shielding,
    // the 1st radiation shield and the vacuum (OVC) volume
    // are daughters of the main hall, and their Z position is defined
    // relative to the PE shielding. Everything inside the OVC
    // (starting from the 2nd radiation shield) are OVC daughters,
    // so they are positioned relatively to it.
    // In principle, changing the position of PE shielding should move
    // everything accordingly.

    // --------------------------------------------
    // Muon veto. Last modification: 26.06.20 (Gio)
    // --------------------------------------------
    // The muon veto is made of 3 components:
    // - an octagonal part outside the polyethylene shielding
    // - a rectangular vertical part outside the platform holding the outer shielding
    // - a rectangular horizontal panel below the platform holding the outershielding
    // All parts have a 50 mm thickness.
    fMuonVeto.LateralExtL            = 2700. * mm;
    fMuonVeto.LateralIntL            = 2600. * mm;
    fMuonVeto.LateralH               = 3480. * mm;
    fMuonVeto.BottomLateralX         = 3640. * mm;
    fMuonVeto.BottomLateralY         = 3225. * mm;
    fMuonVeto.BottomLateralT         = 50.   * mm;
    fMuonVeto.BottomLateralH         = 1000  * mm;
    fMuonVeto.BottomX                = 3740. * mm;
    fMuonVeto.BottomY                = 3325. * mm;
    fMuonVeto.BottomT                = 50.   * mm;
    fMuonVeto.LateralZ               = +0.5 * fMuonVeto.LateralH; // Bottom of lateral muon veto is at z=0.
    fMuonVeto.BottomLateralZ         = -0.5 * fMuonVeto.BottomLateralH;
    fMuonVeto.BottomZ                = -fMuonVeto.BottomLateralH - 0.5 * fMuonVeto.BottomT;
    fMuonVeto.LateralPos             = G4ThreeVector( 0., 0., fMuonVeto.LateralZ       );
    fMuonVeto.LateralSourcePos       = G4ThreeVector( 0., 0., fMuonVeto.LateralZ       );
    fMuonVeto.BottomLateralPos       = G4ThreeVector( 0., 0., fMuonVeto.BottomLateralZ );
    fMuonVeto.BottomLateralSourcePos = G4ThreeVector( 0., 0., fMuonVeto.BottomLateralZ );
    fMuonVeto.BottomPos              = G4ThreeVector( 0., 0., fMuonVeto.BottomZ        );
    fMuonVeto.BottomSourcePos        = G4ThreeVector( 0., 0., fMuonVeto.BottomZ        );

    fRealisticMuonVeto.nPanels				  = 4;
    fRealisticMuonVeto.nRings				  = 2;
    fRealisticMuonVeto.LateralRadius	  	  = {1318.*mm, 1363.*mm};
    fRealisticMuonVeto.LateralWidth   	      = {1600.*mm, 850.*mm};
    fRealisticMuonVeto.LateralHeight          = 3400. * mm;
    fRealisticMuonVeto.LateralThickness       = 25.4 * mm;
    fRealisticMuonVeto.LateralH               = 3480. * mm;
    fRealisticMuonVeto.BottomLateralX         = 3640. * mm;
    fRealisticMuonVeto.BottomLateralY         = 3225. * mm;
    fRealisticMuonVeto.BottomLateralT         = 50.   * mm;
    fRealisticMuonVeto.BottomLateralH         = 1200  * mm;
    fRealisticMuonVeto.BottomX                = 2900. * mm;
    fRealisticMuonVeto.BottomY                = 2900. * mm;
    fRealisticMuonVeto.BottomT                = 25.4  * mm;
    fRealisticMuonVeto.TopX                	  = 7000. * mm;
    fRealisticMuonVeto.TopY                	  = 7000. * mm;
    fRealisticMuonVeto.TopT                	  = 25.4  * mm;
    fRealisticMuonVeto.TopZ                	  = 8300. * mm;
    fRealisticMuonVeto.LateralZ               = +0.5 * fRealisticMuonVeto.LateralH; // Bottom of lateral muon veto is at z=0.
    fRealisticMuonVeto.BottomLateralZ         = -0.5 * fRealisticMuonVeto.BottomLateralH;
    fRealisticMuonVeto.BottomZ                = -fRealisticMuonVeto.BottomLateralH - 0.5 * fRealisticMuonVeto.BottomT;
    fRealisticMuonVeto.LateralPos             = G4ThreeVector( 0., 0., fRealisticMuonVeto.LateralZ       );
    fRealisticMuonVeto.LateralSourcePos       = G4ThreeVector( 0., 0., fRealisticMuonVeto.LateralZ       );
    fRealisticMuonVeto.BottomLateralPos       = G4ThreeVector( 0., 0., fRealisticMuonVeto.BottomLateralZ );
    fRealisticMuonVeto.BottomLateralSourcePos = G4ThreeVector( 0., 0., fRealisticMuonVeto.BottomLateralZ );
    fRealisticMuonVeto.BottomPos              = G4ThreeVector( 0., 0., fRealisticMuonVeto.BottomZ        );
    fRealisticMuonVeto.BottomSourcePos        = G4ThreeVector( 0., 0., fRealisticMuonVeto.BottomZ        );
    fRealisticMuonVeto.TopPos                 = G4ThreeVector( 0., 0., fRealisticMuonVeto.TopZ        );
    fRealisticMuonVeto.TopSourcePos           = G4ThreeVector( 0., 0., fRealisticMuonVeto.TopZ        );

    // ------------------------------------------------------
    // Bottom polyethylene. Last modification: 13.03.20 (Gio)
    // ------------------------------------------------------
    fPolyethylene.ExtL      = 2600. * mm;
    fPolyethylene.IntL      = 2240. * mm;
    fPolyethylene.H         = 3480. * mm;
    fPolyethylene.BottomH   = 200.  * mm;// thickness of bottom PE part
    fPolyethylene.Z         = fMuonVeto.LateralZ;//0.5 * fPolyethylene.H;// Bottom of PE is at z=0.
    fPolyethylene.Pos       = G4ThreeVector( 0., 0., fPolyethylene.Z );
    fPolyethylene.SourcePos = G4ThreeVector( 0., 0., fPolyethylene.Z );

    // ---------------------------------------------
    // Boric acid. Last modification: 13.03.20 (Gio)
    // ---------------------------------------------
    fBoricAcid.ExtL      = 2240. * mm;
    fBoricAcid.IntL      = 2200. * mm;
    fBoricAcid.H         = 3280. * mm;
    fBoricAcid.Z         = fPolyethylene.Z + 0.5 * fPolyethylene.H - 0.5 * fBoricAcid.H;
    fBoricAcid.Pos       = G4ThreeVector( 0., 0., fBoricAcid.Z );
    fBoricAcid.SourcePos = G4ThreeVector( 0., 0., fBoricAcid.Z );

    // --------------------------------------------------
    // External shield. Last modification: 13.03.20 (Gio)
    // --------------------------------------------------
    fExternalLead.ExtL    = 2200. * mm;
    fExternalLead.IntL    = 1700. * mm;
    fExternalLead.H       = 3280. * mm;
    fExternalLead.BottomH = 250.  * mm;// bottom thickness
    fExternalLead.Z       = fPolyethylene.Z + 0.5 * fPolyethylene.H - 0.5 * fExternalLead.H;
    fExternalLead.Pos       = G4ThreeVector( 0., 0., fExternalLead.Z );
    fExternalLead.SourcePos = G4ThreeVector( 0., 0., fExternalLead.Z );

    // ------------------------------------------------------
    // Calibration source volume. Last modification: 14.02.22 (Penny)
    // ------------------------------------------------------
    fCalibrationSource.nVertices		=    8;
    fCalibrationSource.arrayRadius		=    0.95 * fExternalLead.IntL/2.;
    fCalibrationSource.CylR				=	 5. * mm;
    fCalibrationSource.CylH				=	 200. * mm;
    fCalibrationSource.CylLocationX		= 	 0. * mm;
    fCalibrationSource.CylLocationY		= 	 0. * mm;
    fCalibrationSource.CylLocationZ 	=    1500. * mm;
    fCalibrationSource.Pos				= G4ThreeVector( fCalibrationSource.CylLocationX, fCalibrationSource.CylLocationY, fCalibrationSource.CylLocationZ );
    fCalibrationSource.SourcePos		= G4ThreeVector( fCalibrationSource.CylLocationX, fCalibrationSource.CylLocationY, fCalibrationSource.CylLocationZ );

    // -------------------------------------------------------
    // 1st radiation shield. Last modification: 13.03.20 (Gio)
    // -------------------------------------------------------
    fFirstRadiationShield.FlangeR       = 1030. * mm;
    fFirstRadiationShield.FlangeH       = 62.   * mm;// Gio: Used to be 64 mm, but the drawing says 62
    fFirstRadiationShield.R             = 813.5 * mm;
    fFirstRadiationShield.H             = 2245. * mm;// Gio: Used to be 2248 mm, but the drawing says 2245
    fFirstRadiationShield.TotH          = 2620. * mm;// Total height of copper part
    fFirstRadiationShield.T             = 12.   * mm;
    fFirstRadiationShield.BottomT       = 15.   * mm;
    fFirstRadiationShield.SphereR       = 1615. * mm;

    // The bottom cylinder has to be thicker than BottomT (the thickness of the bottom spherical cap).
    // BottomR is the radius, w.r.t. the Z axis, of the inner face of the spherical cap when it 
    // joins to the bottom cylinder
    G4double BottomR = sqrt( 
            pow(fFirstRadiationShield.R,2) 
            + pow(fFirstRadiationShield.BottomT,2) 
            - 2*fFirstRadiationShield.SphereR*fFirstRadiationShield.BottomT );
    fFirstRadiationShield.BottomCylT    = fFirstRadiationShield.R - BottomR;

    fFirstRadiationShield.Theta         = asin( fFirstRadiationShield.R / fFirstRadiationShield.SphereR );
    fFirstRadiationShield.BottomH       = fFirstRadiationShield.TotH
        - fFirstRadiationShield.H
        - fFirstRadiationShield.R * tan( 0.5 * fFirstRadiationShield.Theta );
    fFirstRadiationShield.SteelT        = 12.   * mm;
    fFirstRadiationShield.SteelR        = 813.5 * mm;
    fFirstRadiationShield.SteelH        = 410.  * mm;// Gio: Used to be 400 mm, but the drawing says 410
    fFirstRadiationShield.RingR         = 856.5 * mm;
    fFirstRadiationShield.RingH         = 65.   * mm;
    fFirstRadiationShield.RingT         = 43.   * mm;
    fFirstRadiationShield.DistFromPETop = -65.  * mm; // The RS1 flange is 65 mm above the top of the external shield
    fFirstRadiationShield.SteelZ        = fPolyethylene.H
        - fFirstRadiationShield.DistFromPETop
        - 0.5 * fFirstRadiationShield.SteelH;
    fFirstRadiationShield.Z             = fPolyethylene.H
        - fFirstRadiationShield.DistFromPETop
        - fFirstRadiationShield.SteelH
        - 0.5 * fFirstRadiationShield.H;
    fFirstRadiationShield.FlangeZ = fPolyethylene.H
        - fFirstRadiationShield.DistFromPETop
        + 0.5 * fFirstRadiationShield.FlangeH;

    fFirstRadiationShield.SteelPos        = G4ThreeVector( 0., 0., fFirstRadiationShield.SteelZ  );
    fFirstRadiationShield.SteelSourcePos  = G4ThreeVector( 0., 0., fFirstRadiationShield.SteelZ  );
    fFirstRadiationShield.CuPos           = G4ThreeVector( 0., 0., fFirstRadiationShield.Z       );
    fFirstRadiationShield.CuSourcePos     = G4ThreeVector( 0., 0., fFirstRadiationShield.Z       );
    fFirstRadiationShield.FlangePos       = G4ThreeVector( 0., 0., fFirstRadiationShield.FlangeZ );
    fFirstRadiationShield.FlangeSourcePos = G4ThreeVector( 0., 0., fFirstRadiationShield.FlangeZ );

    // ----------------------------------
    // Vacuum inside 1st radiation shield
    // ----------------------------------
    fVacuum.R       = fFirstRadiationShield.R       - fFirstRadiationShield.T;
    fVacuum.H       = fFirstRadiationShield.H       + fFirstRadiationShield.SteelH;
    fVacuum.TotH    = fFirstRadiationShield.TotH    + fFirstRadiationShield.SteelH - fFirstRadiationShield.BottomT;
    fVacuum.BottomT = fFirstRadiationShield.BottomCylT - fFirstRadiationShield.T;
    fVacuum.SphereR = fFirstRadiationShield.SphereR - fFirstRadiationShield.BottomT;

    //fVacuum.Theta   = asin( fVacuum.R / fVacuum.SphereR );
    fVacuum.Theta = asin( (fFirstRadiationShield.R - fFirstRadiationShield.BottomCylT) / fVacuum.SphereR );
    
    fVacuum.BottomH = fVacuum.TotH - fVacuum.H - (fFirstRadiationShield.R - fFirstRadiationShield.BottomCylT) * tan( 0.5 * fVacuum.Theta );
    fVacuum.Z       = fFirstRadiationShield.Z       + 0.5 * fFirstRadiationShield.SteelH;
    fVacuum.Pos     = G4ThreeVector( 0., 0., fVacuum.Z );

    // --------------------------------------------------------------
    // 2nd radiation shield (40 K). Last modification: 06.03.20 (Gio)
    // --------------------------------------------------------------
    fSecondRadiationShield.DistFromRS1  = 215.  * mm;
    fSecondRadiationShield.FlangeR      = 786.5 * mm;
    fSecondRadiationShield.FlangeH      = 20.   * mm;
    fSecondRadiationShield.T            = 5.0   * mm;
    fSecondRadiationShield.H            = 2439  * mm;// Includes also top ring
    fSecondRadiationShield.TotH         = 2765. * mm;
    fSecondRadiationShield.R            = 756.5 * mm;
    fSecondRadiationShield.RingR        = 786.5 * mm;// Equal to FlangeH
    fSecondRadiationShield.RingH        = 35.   * mm;
    fSecondRadiationShield.RingT        = 30.   * mm;
    fSecondRadiationShield.SphereR      = 1505. * mm;// External radius of bottom spherical part
    fSecondRadiationShield.BottomT      = 5.    * mm;// Same as lateral thickness
    fSecondRadiationShield.Theta        = asin( fSecondRadiationShield.R / fSecondRadiationShield.SphereR );
    fSecondRadiationShield.BottomH      = fSecondRadiationShield.TotH - fSecondRadiationShield.H - fSecondRadiationShield.R * tan( 0.5 * fSecondRadiationShield.Theta );
    fSecondRadiationShield.Z            = fFirstRadiationShield.Z
        + fFirstRadiationShield.SteelH
        + 0.5 * fFirstRadiationShield.H
        - 0.5 * fSecondRadiationShield.H
        - fSecondRadiationShield.DistFromRS1
        - fVacuum.Z;
    fSecondRadiationShield.FlangeZ = fSecondRadiationShield.Z
        + 0.5 * fSecondRadiationShield.H
        + 0.5 * fSecondRadiationShield.FlangeH;

    fSecondRadiationShield.Pos             = G4ThreeVector( 0., 0., fSecondRadiationShield.Z       );
    fSecondRadiationShield.SourcePos       = G4ThreeVector( 0., 0., fSecondRadiationShield.Z       ) + fVacuum.Pos;
    fSecondRadiationShield.FlangePos       = G4ThreeVector( 0., 0., fSecondRadiationShield.FlangeZ );
    fSecondRadiationShield.FlangeSourcePos = G4ThreeVector( 0., 0., fSecondRadiationShield.FlangeZ ) + fVacuum.Pos;

    // -------------------------------------------------------------------------------
    // Super insulation around 2nd radiation shield. Last modification: 06.03.20 (Gio)
    // -------------------------------------------------------------------------------
    fSuperInsulation2ndShield.FlangeR  = fSecondRadiationShield.FlangeR;
    fSuperInsulation2ndShield.FlangeH  = 0.0228 * cm;
    fSuperInsulation2ndShield.T        = 0.0684 * cm;
    fSuperInsulation2ndShield.H        = fSecondRadiationShield.H - fSecondRadiationShield.RingH;
    fSuperInsulation2ndShield.TotH     = fSecondRadiationShield.TotH - fSecondRadiationShield.RingH + fSuperInsulation2ndShield.T;
    fSuperInsulation2ndShield.R        = fSecondRadiationShield.R + fSuperInsulation2ndShield.T;
    fSuperInsulation2ndShield.SphereR  = fSecondRadiationShield.SphereR + fSuperInsulation2ndShield.T;
    fSuperInsulation2ndShield.BottomT  = fSuperInsulation2ndShield.T;
    fSuperInsulation2ndShield.Theta    = fSecondRadiationShield.Theta;
    fSuperInsulation2ndShield.BottomH  = fSecondRadiationShield.BottomH;
    fSuperInsulation2ndShield.Z        = fSecondRadiationShield.Z
        - 0.5 * fSecondRadiationShield.RingH
        - 0.5 * fSuperInsulation2ndShield.T;
    fSuperInsulation2ndShield.FlangeZ  = fSecondRadiationShield.Z
        + 0.5 * fSecondRadiationShield.H
        + fSecondRadiationShield.FlangeH
        + 0.5 * fSuperInsulation2ndShield.FlangeH;
    fSuperInsulation2ndShield.Pos             = G4ThreeVector( 0., 0., fSuperInsulation2ndShield.Z       );
    fSuperInsulation2ndShield.SourcePos       = G4ThreeVector( 0., 0., fSuperInsulation2ndShield.Z       ) + fVacuum.Pos;
    fSuperInsulation2ndShield.FlangePos       = G4ThreeVector( 0., 0., fSuperInsulation2ndShield.FlangeZ );
    fSuperInsulation2ndShield.FlangeSourcePos = G4ThreeVector( 0., 0., fSuperInsulation2ndShield.FlangeZ ) + fVacuum.Pos;

    // ------------------------------------------------------------
    // 3rd radiation shield (4K). Last modification: 09.03.20 (Gio)
    // ------------------------------------------------------------
    fThirdRadiationShield.FlangeR    = 736.5  * mm;
    fThirdRadiationShield.FlangeH    = 60.    * mm;
    fThirdRadiationShield.T          = 10.    * mm;
    fThirdRadiationShield.BottomT    = 12.    * mm;
    fThirdRadiationShield.H           = 2137.4 * mm;
    fThirdRadiationShield.TotH        = 2471.4 * mm;
    fThirdRadiationShield.R           = 691.5  * mm;
    fThirdRadiationShield.SphereR     = 1260.  * mm;
    fThirdRadiationShield.Theta       = asin( fThirdRadiationShield.R / fThirdRadiationShield.SphereR );
    fThirdRadiationShield.BottomH     = fThirdRadiationShield.TotH - fThirdRadiationShield.H - fThirdRadiationShield.R * tan( 0.5 * fThirdRadiationShield.Theta );
    fThirdRadiationShield.RingR       = 736.5  * mm;
    fThirdRadiationShield.RingH       = 60.    * mm;
    fThirdRadiationShield.RingT       = 45.    * mm;
    fThirdRadiationShield.DistFromRS2 = 258.   * mm;
    fThirdRadiationShield.Z           = fSecondRadiationShield.Z
        + 0.5 * fSecondRadiationShield.H
        - 0.5 * fThirdRadiationShield.H
        - fThirdRadiationShield.DistFromRS2;
    fThirdRadiationShield.FlangeZ     = fThirdRadiationShield.Z
        + 0.5 * fThirdRadiationShield.H
        + 0.5 * fThirdRadiationShield.FlangeH;
    fThirdRadiationShield.Pos             = G4ThreeVector( 0., 0., fThirdRadiationShield.Z       );
    fThirdRadiationShield.SourcePos       = G4ThreeVector( 0., 0., fThirdRadiationShield.Z       ) + fVacuum.Pos;
    fThirdRadiationShield.FlangePos       = G4ThreeVector( 0., 0., fThirdRadiationShield.FlangeZ );
    fThirdRadiationShield.FlangeSourcePos = G4ThreeVector( 0., 0., fThirdRadiationShield.FlangeZ ) + fVacuum.Pos;

    // ---------------------------------------------------------------------
    // Super insulation around 3rd shield. Last modification: 09.03.20 (Gio)
    // ---------------------------------------------------------------------
    fSuperInsulation3rdShield.FlangeR  = fThirdRadiationShield.FlangeR;
    fSuperInsulation3rdShield.FlangeH  = 0.228 * mm;
    fSuperInsulation3rdShield.T        = 0.228 * mm;
    fSuperInsulation3rdShield.H        = fThirdRadiationShield.H - fThirdRadiationShield.RingH;
    fSuperInsulation3rdShield.TotH     = fThirdRadiationShield.TotH - fThirdRadiationShield.RingH + fSuperInsulation3rdShield.T;
    fSuperInsulation3rdShield.R        = fThirdRadiationShield.R + fSuperInsulation3rdShield.T;
    fSuperInsulation3rdShield.SphereR  = fThirdRadiationShield.SphereR + fSuperInsulation3rdShield.T;
    fSuperInsulation3rdShield.BottomT  = fSuperInsulation3rdShield.T;
    fSuperInsulation3rdShield.Theta    = fThirdRadiationShield.Theta;
    fSuperInsulation3rdShield.BottomH  = fThirdRadiationShield.BottomH;
    fSuperInsulation3rdShield.Z        = fThirdRadiationShield.Z - 0.5 * fThirdRadiationShield.RingH - 0.5 * fSuperInsulation3rdShield.T;
    fSuperInsulation3rdShield.FlangeZ  = fThirdRadiationShield.Z
        + 0.5 * fThirdRadiationShield.H
        + fThirdRadiationShield.FlangeH
        + 0.5 * fSuperInsulation3rdShield.FlangeH;
    fSuperInsulation3rdShield.Pos             = G4ThreeVector( 0., 0., fSuperInsulation3rdShield.Z       );
    fSuperInsulation3rdShield.SourcePos       = G4ThreeVector( 0., 0., fSuperInsulation3rdShield.Z       ) + fVacuum.Pos;
    fSuperInsulation3rdShield.FlangePos       = G4ThreeVector( 0., 0., fSuperInsulation3rdShield.FlangeZ );
    fSuperInsulation3rdShield.FlangeSourcePos = G4ThreeVector( 0., 0., fSuperInsulation3rdShield.FlangeZ ) + fVacuum.Pos;

    // ----------------------------------------------------------------
    // 4th radiation shield (600 mK). Last modification: 06.02.20 (Gio)
    // ----------------------------------------------------------------
    fFourthRadiationShield.R           = 560.  * mm;
    fFourthRadiationShield.TorusR      = 155.  * mm;
    fFourthRadiationShield.TotH        = 1850. * mm;// Total height: 1695 (lateral) + 155 (bottom torus) = 1850 mm
    G4double a                         = fFourthRadiationShield.TorusR * ( sqrt(2.) - 1. );
    fFourthRadiationShield.SphereR     = fFourthRadiationShield.R * sqrt(2.) - a;
    G4double delta                     = acos( fFourthRadiationShield.R / fFourthRadiationShield.SphereR );
    fFourthRadiationShield.ThetaMin    = 90.  * deg + delta;
    fFourthRadiationShield.ThetaMax    = 180. * deg - delta;
    G4double e                         = fFourthRadiationShield.R - fFourthRadiationShield.SphereR * sin(delta);
    fFourthRadiationShield.H           = fFourthRadiationShield.TotH - e;
    fFourthRadiationShield.T           = 5.    * mm;
    fFourthRadiationShield.FlangeR     = 666.5 * mm;
    fFourthRadiationShield.FlangeH     = 43.   * mm;
    fFourthRadiationShield.BottomR     = fFourthRadiationShield.SphereR * sin( fFourthRadiationShield.ThetaMax );
    fFourthRadiationShield.RingR       = 580.  * mm;
    fFourthRadiationShield.RingT       = 20.   * mm;
    fFourthRadiationShield.RingH       = 29.5  * mm;

    fFourthRadiationShield.LTPhase     = 45.   * deg;
    fFourthRadiationShield.LTWidth     = 70.   * mm;
    fFourthRadiationShield.LTDepth     = 76.5  * mm;
    fFourthRadiationShield.LTAperture  = 2. * asin( 0.5 * fFourthRadiationShield.LTWidth / fFourthRadiationShield.FlangeR );
    for( G4int i=0; i<3; i++ )// Angle of LT slits
    {
        G4double angle = 120. * deg * i + fFourthRadiationShield.LTPhase;
        fFourthRadiationShield.LTRot.push_back( new G4RotationMatrix() );
        fFourthRadiationShield.LTRot.back()->rotateZ( -angle );
    }

    fFourthRadiationShield.SSPhase     = 105.  * deg;// Phase of CuBe holders
    fFourthRadiationShield.SSWidth     = 120.  * mm;
    fFourthRadiationShield.SSAperture  = 2. * asin( 0.5 * fFourthRadiationShield.SSWidth / fFourthRadiationShield.R );
    fFourthRadiationShield.SSH         = 170.  * mm;
    fFourthRadiationShield.SSD         = 590.  * mm;// Distance from center of CuBe holders
    fFourthRadiationShield.SSR         = 20.   * mm;// Radius of CuBe holders holes
    for( G4int i=0; i<3; i++ )// Angle of SS holes for CuBe holders
    {
        G4double angle = 120. * deg * i + fFourthRadiationShield.SSPhase;
        fFourthRadiationShield.SSAngle.push_back( angle );
        fFourthRadiationShield.SSHoleP.push_back( G4ThreeVector( 0,
                    0,
                    0.5 * fFourthRadiationShield.H ) );
        fFourthRadiationShield.SSRot.push_back( new G4RotationMatrix() );
        fFourthRadiationShield.SSRot.back()->rotateZ( -angle );
        fFourthRadiationShield.SSFlangeHoleP.push_back( G4ThreeVector( cos(angle) * fFourthRadiationShield.SSD,
                    sin(angle) * fFourthRadiationShield.SSD,
                    0 ) );
    }

    fFourthRadiationShield.DistFromRS3 = 330.  * mm;
    fFourthRadiationShield.Z           = fThirdRadiationShield.Z
        + 0.5 * fThirdRadiationShield.H
        - 0.5 * fFourthRadiationShield.H
        - fFourthRadiationShield.DistFromRS3;
    fFourthRadiationShield.FlangeZ     = fFourthRadiationShield.Z
        + 0.5 * fFourthRadiationShield.H
        + 0.5 * fFourthRadiationShield.FlangeH;
    fFourthRadiationShield.Pos             = G4ThreeVector( 0., 0., fFourthRadiationShield.Z       );
    fFourthRadiationShield.SourcePos       = G4ThreeVector( 0., 0., fFourthRadiationShield.Z       ) + fVacuum.Pos;
    fFourthRadiationShield.FlangePos       = G4ThreeVector( 0., 0., fFourthRadiationShield.FlangeZ );
    fFourthRadiationShield.FlangeSourcePos = G4ThreeVector( 0., 0., fFourthRadiationShield.FlangeZ ) + fVacuum.Pos;

    // ---------------------------------------------
    // Roman lead. Last modification: 13.03.20 (Gio)
    // ---------------------------------------------
    fRomanLead.R                 = 638.5  * mm;
    fRomanLead.T                 = 59.74  * mm;
    fRomanLead.H                 = 1567.5 * mm;
    fRomanLead.RodsHoleD         = 610.   * mm;// Distance of rod holes from center
    fRomanLead.RodsHoleR         = 10.5   * mm;// Rod hole radius
    fRomanLead.RodsFlangeHoleR   = 20.    * mm;// Radius of rod holes in 4th rad. shield flange
    fRomanLead.RodsPhase         = 72.5   * deg;
    for( G4int i=0; i<3; i++ )// Drill holes for steel rods
    {
        G4double angle = 120. * deg * i + fRomanLead.RodsPhase;
        fRomanLead.Angle.push_back( angle );
        fRomanLead.RodsHoleP.push_back( G4ThreeVector( cos(angle) * fRomanLead.RodsHoleD,
                    sin(angle) * fRomanLead.RodsHoleD,
                    0. ) );
    }
    fRomanLead.TopCuRingR        = 666.5 * mm;
    fRomanLead.TopCuRingH        = 80.   * mm;
    fRomanLead.TopCuRingT        = 88.   * mm;
    fRomanLead.BottomCuRingR     = 638.5 * mm;// Radius of bottom cradle ring
    fRomanLead.BottomCuRingH     = 95.   * mm;
    fRomanLead.BottomCuRingT     = 98.5  * mm;
    fRomanLead.CuCradleR         = 575.  * mm;// Diameter of cradle bottom plate
    fRomanLead.CuCradleH         = 35.   * mm;// Height of cradle bottom plate
    fRomanLead.BottomPbR         = 540.  * mm;
    fRomanLead.BottomPbH         = 60.   * mm;
    fRomanLead.DistFromRS4Flange = 230. * mm - fFourthRadiationShield.FlangeH;// Distance between RS4 flange and top Cu ring. Used to be 187mm, but who knows what quantity that was!
    fRomanLead.Z                 = fFourthRadiationShield.FlangeZ
        - 0.5 * fFourthRadiationShield.FlangeH
        - fRomanLead.DistFromRS4Flange
        - fRomanLead.TopCuRingH
        - 0.5 * fRomanLead.H;
    fRomanLead.TopCuRingZ        = fRomanLead.Z
        + 0.5 * fRomanLead.H
        + 0.5 * fRomanLead.TopCuRingH;
    fRomanLead.BottomCuRingZ     = fRomanLead.Z
        - 0.5 * fRomanLead.H
        - 0.5 * fRomanLead.BottomCuRingH;
    fRomanLead.BottomPbZ = fRomanLead.BottomCuRingZ
        - 0.5 * fRomanLead.BottomCuRingH
        + 0.5 * fRomanLead.BottomPbH;

    fRomanLead.PbPos                 = G4ThreeVector( 0., 0., fRomanLead.Z             );
    fRomanLead.PbSourcePos           = G4ThreeVector( 0., 0., fRomanLead.Z             ) + fVacuum.Pos;
    fRomanLead.TopCuRingPos          = G4ThreeVector( 0., 0., fRomanLead.TopCuRingZ    );
    fRomanLead.TopCuRingSourcePos    = G4ThreeVector( 0., 0., fRomanLead.TopCuRingZ    ) + fVacuum.Pos;
    fRomanLead.BottomCuRingPos       = G4ThreeVector( 0., 0., fRomanLead.BottomCuRingZ );
    fRomanLead.BottomCuRingSourcePos = G4ThreeVector( 0., 0., fRomanLead.BottomCuRingZ ) + fVacuum.Pos;
    fRomanLead.BottomPbPos           = G4ThreeVector( 0., 0., fRomanLead.BottomPbZ     );
    fRomanLead.BottomPbSourcePos     = G4ThreeVector( 0., 0., fRomanLead.BottomPbZ     ) + fVacuum.Pos;

    // ---------------------------------------------
    // Steel rods. Last modification: 13.03.20 (Gio)
    // ---------------------------------------------
    fSteelRods.R    = 9.   * mm;
    fSteelRods.H = fRomanLead.BottomCuRingH
        + fRomanLead.H
        + fRomanLead.TopCuRingH;
    fSteelRods.TopR = 20.  * mm;
    fSteelRods.TopH = 230. * mm;
    fSteelRods.HatR = 35.  * mm;
    fSteelRods.HatH = 20.  * mm;
    fSteelRods.Z = fRomanLead.Z
        + 0.5 * fRomanLead.H
        + fRomanLead.TopCuRingH
        - 0.5 * fSteelRods.H;
    fSteelRods.Pos       = G4ThreeVector( 0., 0., fSteelRods.Z );
    fSteelRods.SourcePos = G4ThreeVector( 0., 0., fSteelRods.Z ) + fVacuum.Pos;

    // -----------------------------------------------
    // Cu-Be joints. Last modification: 13.03.20 (Gio)
    // -----------------------------------------------
    fCuBeJoints.H     = 129.6 * mm;
    fCuBeJoints.R     = 54.   * mm;
    fCuBeJoints.HoleR = 590.  * mm;// Gio: Why the hell do we define this variable if then we position the volume at a different radius?!?
    fCuBeJoints.Z     = fFourthRadiationShield.FlangeZ - fCuBeJoints.H;

    //G4double tmpZ = fCuBeJoints.Z + 0.5 * fCuBeJoints.H;
    //fCuBeJoints.GiuntiCuBePos.push_back( G4ThreeVector( tmpR,
    //							0.,
    //							tmpZ ) );
    //fCuBeJoints.GiuntiCuBePos.push_back( G4ThreeVector( -0.5 * tmpR,
    //							0.866 * tmpR,
    //							tmpZ ) );
    //fCuBeJoints.GiuntiCuBePos.push_back( G4ThreeVector( -0.5 * tmpR,
    //							-0.866 * tmpR,
    //							tmpZ ) );
    fCuBeJoints.NumGiuntiCuBe = fCuBeJoints.GiuntiCuBePos.size();


    // ----------------------------
    // 5th radiation shield (50 mK)
    // ----------------------------

    fFifthRadiationShield.R           = 515.  * mm;
    fFifthRadiationShield.TorusR      = 60.   * mm;
    fFifthRadiationShield.TotH        = 1650. * mm;
    a                                 = fFifthRadiationShield.TorusR * ( sqrt(2.) - 1. );
    fFifthRadiationShield.SphereR     = fFifthRadiationShield.R * sqrt(2.) - a;
    delta                             = acos( fFifthRadiationShield.R / fFifthRadiationShield.SphereR );
    fFifthRadiationShield.ThetaMin    = 90.  * deg + delta;
    fFifthRadiationShield.ThetaMax    = 180. * deg - delta;
    e                                 = fFifthRadiationShield.R - fFifthRadiationShield.SphereR * sin(delta);
    fFifthRadiationShield.H           = fFifthRadiationShield.TotH - e;// Used to be 1590 mm
    fFifthRadiationShield.BottomR     = fFifthRadiationShield.SphereR * sin( fFifthRadiationShield.ThetaMax );
    fFifthRadiationShield.T           = 5.    * mm;
    fFifthRadiationShield.FlangeR     = 535.  * mm;
    fFifthRadiationShield.FlangeH     = 28.   * mm;
    fFifthRadiationShield.RingR       = 535.  * mm;
    fFifthRadiationShield.RingH       = 29.5  * mm;
    fFifthRadiationShield.RingT       = 20.   * mm;

    // CuBe holder slits
    fFifthRadiationShield.SSPhase     = 105.  * deg;// Phase of CuBe holders
    fFifthRadiationShield.SSD         = 590.  * mm;// Distance from center of CuBe holders
    fFifthRadiationShield.SSR         = 69.   * mm;// Radius of CuBe holders holes
    for( G4int i=0; i<3; i++ )// Angle of SS holes for CuBe holders
    {
        G4double angle = 120. * deg * i + fFifthRadiationShield.SSPhase;
        fFifthRadiationShield.SSAngle.push_back( angle );
        fFifthRadiationShield.SSHoleP.push_back( G4ThreeVector( cos(angle) * fFifthRadiationShield.SSD,
                    sin(angle) * fFifthRadiationShield.SSD,
                    0.5 * fFifthRadiationShield.H - 0.5 * fFifthRadiationShield.RingH ) );
        fFifthRadiationShield.SSFlangeHoleP.push_back( G4ThreeVector( cos(angle) * fFifthRadiationShield.SSD,
                    sin(angle) * fFifthRadiationShield.SSD,
                    0. ) );
    }

    // Unknown slits
    fFifthRadiationShield.SWidth          = 115.   * mm;
    fFifthRadiationShield.SDepth          = fFifthRadiationShield.RingT;
    fFifthRadiationShield.SAperture       = 2. * asin( 0.5 * fFifthRadiationShield.SWidth / fFifthRadiationShield.RingR );
    fFifthRadiationShield.SFlangeDepth    = 125. * mm;
    fFifthRadiationShield.SFlangeAperture = 5.   * deg;
    fFifthRadiationShield.SPhase.push_back( 15.  * deg );// S2
    fFifthRadiationShield.SPhase.push_back( 86.  * deg );// S1
    fFifthRadiationShield.SPhase.push_back( 195. * deg );// S4
    fFifthRadiationShield.SPhase.push_back( 256. * deg );// S3
    fFifthRadiationShield.NSSlits = fFifthRadiationShield.SPhase.size();
    for( G4int i=0; i<fFifthRadiationShield.NSSlits; i++ )
    {
        G4double angle = 120. * deg * i + fFifthRadiationShield.SPhase[i];
        fFifthRadiationShield.SHoleP.push_back( G4ThreeVector( 0.,
                    0.,
                    0.5 * fFifthRadiationShield.H - 0.5 * fFifthRadiationShield.RingH ) );
        fFifthRadiationShield.SRot.push_back( new G4RotationMatrix() );
        fFifthRadiationShield.SRot.back()->rotateZ( -angle );
    }

    // Position
    fFifthRadiationShield.DistFromRS4 = 112.  * mm;
    fFifthRadiationShield.Z           = fFourthRadiationShield.Z
        + 0.5 * fFourthRadiationShield.H
        - 0.5 * fFifthRadiationShield.H
        - fFifthRadiationShield.DistFromRS4;
    fFifthRadiationShield.FlangeZ     = fFifthRadiationShield.Z
        + 0.5 * fFifthRadiationShield.H
        + 0.5 * fFifthRadiationShield.FlangeH;

    fFifthRadiationShield.Pos             = G4ThreeVector( 0., 0., fFifthRadiationShield.Z       );
    fFifthRadiationShield.SourcePos       = G4ThreeVector( 0., 0., fFifthRadiationShield.Z       ) + fVacuum.Pos;
    fFifthRadiationShield.FlangePos       = G4ThreeVector( 0., 0., fFifthRadiationShield.FlangeZ );
    fFifthRadiationShield.FlangeSourcePos = G4ThreeVector( 0., 0., fFifthRadiationShield.FlangeZ ) + fVacuum.Pos;

    // ----------------------------
    // 6th radiation shield (10 mK)
    // ----------------------------

    fSixthRadiationShield.R                    = 475.   * mm;
    fSixthRadiationShield.H                    = 1365.  * mm;
    fSixthRadiationShield.T                    = 5.     * mm;
    fSixthRadiationShield.FlangeR              = 490.   * mm;
    fSixthRadiationShield.FlangeH              = 18.    * mm;
    fSixthRadiationShield.RingR                = 490.   * mm;
    fSixthRadiationShield.RingH                = 28.    * mm;
    fSixthRadiationShield.RingT                = 15.    * mm;
    fSixthRadiationShield.BottomR              = 490.   * mm;
    fSixthRadiationShield.BottomH              = 5.     * mm;
    fSixthRadiationShield.TilesR               = fSixthRadiationShield.R - fSixthRadiationShield.T;
    fSixthRadiationShield.TilesH               = 965    * mm;// Used to be 979 mm, but it doesn't match with installation pics
    fSixthRadiationShield.TilesT               = 0.5    * mm;

    fSixthRadiationShield.RingPos.push_back( G4ThreeVector( 0, 0, -0.5 * fSixthRadiationShield.H + 0.5 * fSixthRadiationShield.RingH + fSixthRadiationShield.BottomH ) );
    fSixthRadiationShield.RingPos.push_back( G4ThreeVector( 0, 0, -0.5 * fSixthRadiationShield.H + 240. * mm ) );
    fSixthRadiationShield.RingPos.push_back( G4ThreeVector( 0, 0, -0.5 * fSixthRadiationShield.H + 480. * mm ) );
    fSixthRadiationShield.RingPos.push_back( G4ThreeVector( 0, 0, -0.5 * fSixthRadiationShield.H + 720. * mm ) );
    fSixthRadiationShield.RingPos.push_back( G4ThreeVector( 0, 0, -0.5 * fSixthRadiationShield.H + 965. * mm ) );
    fSixthRadiationShield.RingPos.push_back( G4ThreeVector( 0, 0,  0.5 * fSixthRadiationShield.H - 0.5 * fSixthRadiationShield.RingH ) );
    fSixthRadiationShield.IsDoubleRing.push_back( false );
    fSixthRadiationShield.IsDoubleRing.push_back( true );
    fSixthRadiationShield.IsDoubleRing.push_back( true );
    fSixthRadiationShield.IsDoubleRing.push_back( true );
    fSixthRadiationShield.IsDoubleRing.push_back( true );
    fSixthRadiationShield.IsDoubleRing.push_back( false );

    fSixthRadiationShield.NRings = fSixthRadiationShield.RingPos.size();

    // Position
    fSixthRadiationShield.DistFromRS5 = 202. * mm;
    fSixthRadiationShield.Z           = fFifthRadiationShield.Z
        + 0.5 * fFifthRadiationShield.H
        - 0.5 * fSixthRadiationShield.H
        - fSixthRadiationShield.DistFromRS5;
    fSixthRadiationShield.FlangeZ     = fSixthRadiationShield.Z
        + 0.5 * fSixthRadiationShield.H
        + 0.5 * fSixthRadiationShield.FlangeH;
    fSixthRadiationShield.TilesZ      = fSixthRadiationShield.Z
        - 0.5 * fSixthRadiationShield.H
        + fSixthRadiationShield.BottomH
        + 0.5 * fSixthRadiationShield.TilesH;

    fSixthRadiationShield.Pos             = G4ThreeVector( 0., 0., fSixthRadiationShield.Z       );
    fSixthRadiationShield.SourcePos       = G4ThreeVector( 0., 0., fSixthRadiationShield.Z       ) + fVacuum.Pos;
    fSixthRadiationShield.FlangePos       = G4ThreeVector( 0., 0., fSixthRadiationShield.FlangeZ );
    fSixthRadiationShield.FlangeSourcePos = G4ThreeVector( 0., 0., fSixthRadiationShield.FlangeZ ) + fVacuum.Pos;
    fSixthRadiationShield.TilesPos        = G4ThreeVector( 0., 0., fSixthRadiationShield.TilesZ  );
    fSixthRadiationShield.TilesSourcePos  = G4ThreeVector( 0., 0., fSixthRadiationShield.TilesZ  ) + fVacuum.Pos;


    fSixthRadiationShield.CuRS6RingDouble1ZRelToRing0 = -35.8  * cm;//22.01.13
    fSixthRadiationShield.CuRS6RingDouble2ZRelToRing0 = -60.3  * cm;//22.01.13
    fSixthRadiationShield.CuRS6RingDouble3ZRelToRing0 = -84.3  * cm;//22.01.13
    fSixthRadiationShield.CuRS6RingDouble4ZRelToRing0 = -108.3 * cm;//22.01.13
    fSixthRadiationShield.CuRS6Ring5ZRelToRing0       = -133.7 * cm;//21.01.13

    //fSixthRadiationShield.CuRS6FlanZ                  = fSixthRadiationShield.CuRS6Z
    //	+ fSixthRadiationShield.CuRS6BotAlt
    //	+ fSixthRadiationShield.CuRS6Alt;//22.01.13 Ovvero 238.7cm: 101.7+0.5+136.5
    //
    //fSixthRadiationShield.DistBotCuRS5BotCuRS6        = 6.0    * cm;//24.01.13
    //fSixthRadiationShield.CuRS6Z                      = fFifthRadiationShield.Z
    //	+ fSixthRadiationShield.DistBotCuRS5BotCuRS6;//24.01.13 Da 101.7cm a 238.7 cm (bottom della CuRS6Flan): 101.7+0.5(CuRS6BotAlt)+136.5(CuRS6Alt)

    // ------------------------------------------
    // Cu plate above top internal lead shielding
    // ------------------------------------------
    fInternalTopPb.TopCuR           = 450. * mm;
    fInternalTopPb.TopCuH           = 18.  * mm;
    fInternalTopPb.R                = 450. * mm;
    fInternalTopPb.H                = 300. * mm;
    fInternalTopPb.BottomCuR        = 450. * mm;
    fInternalTopPb.BottomCuH        = 46.  * mm;
    fInternalTopPb.TopCuDistFromRS6 = 60.  * mm;

    fInternalTopPb.TopCuZ           = fSixthRadiationShield.Z
        + 0.5 * fSixthRadiationShield.H
        - 0.5 * fInternalTopPb.TopCuH
        - fInternalTopPb.TopCuDistFromRS6;
    fInternalTopPb.Z                = fInternalTopPb.TopCuZ
        - 0.5 * fInternalTopPb.TopCuH
        - 0.5 * fInternalTopPb.H;
    fInternalTopPb.BottomCuZ        = fInternalTopPb.Z
        - 0.5 * fInternalTopPb.H
        - 0.5 * fInternalTopPb.BottomCuH;

    fInternalTopPb.TopCuPos          = G4ThreeVector( 0., 0., fInternalTopPb.TopCuZ    );
    fInternalTopPb.TopCuSourcePos    = G4ThreeVector( 0., 0., fInternalTopPb.TopCuZ    ) + fVacuum.Pos;
    fInternalTopPb.Pos               = G4ThreeVector( 0., 0., fInternalTopPb.Z         );
    fInternalTopPb.SourcePos         = G4ThreeVector( 0., 0., fInternalTopPb.Z         ) + fVacuum.Pos;
    fInternalTopPb.BottomCuPos       = G4ThreeVector( 0., 0., fInternalTopPb.BottomCuZ );
    fInternalTopPb.BottomCuSourcePos = G4ThreeVector( 0., 0., fInternalTopPb.BottomCuZ ) + fVacuum.Pos;

    // -------------------------
    // Tower Support Plate (TSP)
    // -------------------------
    fTSP.R                = 450. * mm;
    fTSP.H                = 48.  * mm;
    fTSP.DistFromIntTopPb = 76.8 * mm;
    // Dimensions of fake solid used only at development stage
    // to leave the space for the TSP suspensions free.
    fTSP.SuspensionR      = 425. * mm;
    fTSP.SuspensionT      = 24.  * mm;
    fTSP.Suspensionr      = 36.  * mm;
    fTSP.SuspensionH      = 20.  * mm;
    // Position
    fTSP.Z                = fInternalTopPb.BottomCuZ
        - 0.5 * fInternalTopPb.BottomCuH
        - 0.8 * fTSP.H
        - fTSP.DistFromIntTopPb;
    fTSP.Pos       = G4ThreeVector( 0., 0., fTSP.Z );
    fTSP.SourcePos = G4ThreeVector( 0., 0., fTSP.Z ) + fVacuum.Pos;
    for( G4double angle=90.; angle<360.+90.; angle+=120. )
    {
        G4double x = fTSP.SuspensionR * cos( angle * deg );
        G4double y = fTSP.SuspensionR * sin( angle * deg );
        G4double z = fTSP.Z
            - 0.5 * fTSP.H
            - 0.5 * fTSP.SuspensionH;

        fTSP.SuspensionPos.push_back( G4ThreeVector( x, y, z ) );
        fTSP.SuspensionSourcePos.push_back( G4ThreeVector( x, y, z ) + fVacuum.Pos );
        fTSP.SuspensionRot.push_back( new G4RotationMatrix );
        fTSP.SuspensionRot.back()->rotateZ( -angle * deg );
    }

    // ----------------------------------------------------
    // Cu detector top plate (tiles attached to TSP bottom)
    // ----------------------------------------------------
    fDetTopCuPlate.R  = 460. * mm;
    fDetTopCuPlate.H  = 1.   * mm;
    fDetTopCuPlate.Z  = fTSP.Z
        - 0.5 * fTSP.H
        - 0.5 * fDetTopCuPlate.H;

    fDetTopCuPlate.Pos       = G4ThreeVector( 0., 0., fDetTopCuPlate.Z );
    fDetTopCuPlate.SourcePos = G4ThreeVector( 0., 0., fDetTopCuPlate.Z ) + fVacuum.Pos;

    // ------------------------
    // Cu detector bottom plate
    // ------------------------
    fDetBottomCuPlate.R                  = 460. * mm;
    fDetBottomCuPlate.H                  = 1.   * mm;
    fDetBottomCuPlate.DistFromTopCuPlate = 791. * mm;
    fDetBottomCuPlate.Z                  = fDetTopCuPlate.Z
        - 0.5 * fDetTopCuPlate.H
        - 0.5 * fDetBottomCuPlate.H
        - fDetBottomCuPlate.DistFromTopCuPlate;

    fDetBottomCuPlate.Pos       = G4ThreeVector( 0., 0., fDetBottomCuPlate.Z );
    fDetBottomCuPlate.SourcePos = G4ThreeVector( 0., 0., fDetBottomCuPlate.Z ) + fVacuum.Pos;

    // ---------------------------
    // Detector: frames + crystals
    // ---------------------------
    // Frame
    fFrame.SpacerN                   = 3;
    fFrame.PlaneN                    = 13;
    fFrame.LaterDist                 = 0.2 * cm;
    fFrame.FrontDist                 = 0.2 * cm;
    fFrame.DetectorR                 = 2.5 * cm;
    fFrame.DetectorH                 = 5.0 * cm;
    fFrame.LDetectorR                = fFrame.DetectorR
        + 0.5 * fFrame.LaterDist;
    fFrame.LDetectorH                = 0.017 * cm;
    fFrame.ReflectorSpes             = 0.007 * cm;
    fFrame.ReflectorR1               = fFrame.DetectorR
        + fFrame.LaterDist;
    fFrame.ReflectorR2               = fFrame.ReflectorR1
        + fFrame.ReflectorSpes;
    fFrame.ReflectorH                = fFrame.DetectorH 
        + 2. * fFrame.FrontDist
        + fFrame.LDetectorH;
    fFrame.ReflectorHS               = -0.1 * cm
        + fFrame.ReflectorH;
    fFrame.RingSpes                  = 0.5 * cm;
    fFrame.RingR1                    = fFrame.ReflectorR2
        + fFrame.LaterDist;
    fFrame.RingR2                    = fFrame.RingR1
        + fFrame.RingSpes;
    fFrame.RingH                     = 0.5  * cm;
    fFrame.SpacerR                   = 0.25 * cm;
    fFrame.SpacerH                   = fFrame.ReflectorH * fFrame.PlaneN
        + fFrame.RingH;
    fFrame.SpacerRAG                 = fFrame.RingR2;
    fFrame.TowerR                    = fFrame.SpacerRAG
        + fFrame.SpacerR;
    fFrame.TowerH                    = fFrame.SpacerH;
    fFrame.DistCuDetUpPlateTowersTop = 1.4 * cm;
    fFrame.TowersCenterZ             = fDetTopCuPlate.Z
        - fFrame.DistCuDetUpPlateTowersTop
        - 0.5 * fFrame.TowerH;

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


    fPileDetector.NFloors         = 13;
    fPileDetector.CrystalL        = 45.  * mm;
    fPileDetector.LightDetL       = 49.  * mm;
    fPileDetector.LightDetDiagL   = 40. * sqrt(2.) * mm;
    fPileDetector.LightDetT       = 0.3  * mm;

    fPileDetector.CuFrameX        = 111. * mm;
    fPileDetector.CuFrameY        = 59.  * mm;
    fPileDetector.CuFrameH        = 2.   * mm;
    fPileDetector.CuTopFrameH     = 12.  * mm;
    fPileDetector.CuBottomFrameH  = 12.  * mm;
    fPileDetector.CuFrameHoleL    = 45.  * mm;
    fPileDetector.CuFrameDT       = 7.   * mm;// Lateral thickness

    fPileDetector.PTFEFrameX      = 7.  * mm;
    fPileDetector.PTFEFrameY      = 7.  * mm;
    fPileDetector.PTFEFrameH      = 7.  * mm;
    fPileDetector.PTFEFrameHoleL  = 5.   * mm;
    fPileDetector.PTFEFrameHoleL2 = 0.5 * fPileDetector.PTFEFrameHoleL * sqrt(2.);
    fPileDetector.PTFEFrameHoleT  = 3.   * mm;
    fPileDetector.PTFEFrameHoleH  = 7.   * mm;
    fPileDetector.PTFEFrameT      = 2.   * mm;

    fPileDetector.CuBandX        = 8. * mm;
    fPileDetector.CuBandY        = 2. * mm;
    fPileDetector.CuBandH        = fDetTopCuPlate.Z
        - 0.5 * fDetTopCuPlate.H
        - 0.5 * fDetBottomCuPlate.H
        - fDetBottomCuPlate.Z
        - 30. * mm;
    fPileDetector.PENBandX = fPileDetector.CuBandX;
    fPileDetector.PENBandY = 0.5 * mm; // 5 bands of ~100 um thickness each
    fPileDetector.PENBandH = fPileDetector.CuBandH;
    fPileDetector.PENCoverT = 1. * mm;
    fPileDetector.PENCoverX = fPileDetector.CuBandX + 2. * fPileDetector.PENCoverT;
    fPileDetector.PENCoverY = 0.5 * mm + fPileDetector.PENCoverT; //
    fPileDetector.PENCoverH = fPileDetector.CuBandH;

    fPileDetector.ReflectorT = 70. * um;
    fPileDetector.ReflectorL = fPileDetector.CrystalL
        + 2. * fPileDetector.PTFEFrameT;
    fPileDetector.ReflectorH = fPileDetector.CrystalL
        + 2. * fPileDetector.PTFEFrameT;

    // Cu band positions
    fPileDetector.CuBandPos.push_back( G4ThreeVector( -0.25 * fPileDetector.CuFrameX   - 0.5 * fPileDetector.CuFrameDT,
                -0.5 * fPileDetector.CuFrameY    + 0.5 * fPileDetector.CuBandY,
                +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.CuBandH ) );
    fPileDetector.CuBandPos.push_back( G4ThreeVector( +0.25 * fPileDetector.CuFrameX   + 0.5 * fPileDetector.CuFrameDT,
                -0.5 * fPileDetector.CuFrameY    + 0.5 * fPileDetector.CuBandY,
                +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.CuBandH ) );
    fPileDetector.CuBandPos.push_back( G4ThreeVector( -0.25 * fPileDetector.CuFrameX   - 0.5 * fPileDetector.CuFrameDT,
                +0.5 * fPileDetector.CuFrameY    - 0.5 * fPileDetector.CuBandY,
                +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.CuBandH ) );
    fPileDetector.CuBandPos.push_back( G4ThreeVector( +0.25 * fPileDetector.CuFrameX   + 0.5 * fPileDetector.CuFrameDT,
                +0.5 * fPileDetector.CuFrameY    - 0.5 * fPileDetector.CuBandY,
                +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.CuBandH ) );

    // PEN band positions
    fPileDetector.PENBandTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( -0.25 * fPileDetector.CuFrameX   - 0.5 * fPileDetector.CuFrameDT,
                    -0.5 * fPileDetector.CuFrameY    - 0.5 * fPileDetector.PENBandY,
                    +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.PENBandH ) ) );
    fPileDetector.PENBandTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( +0.25 * fPileDetector.CuFrameX   + 0.5 * fPileDetector.CuFrameDT,
                    -0.5 * fPileDetector.CuFrameY    - 0.5 * fPileDetector.PENBandY,
                    +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.PENBandH ) ) );
    fPileDetector.PENBandTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( -0.25 * fPileDetector.CuFrameX   - 0.5 * fPileDetector.CuFrameDT,
                    +0.5 * fPileDetector.CuFrameY    + 0.5 * fPileDetector.PENBandY,
                    +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.PENBandH ) ) );
    fPileDetector.PENBandTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( +0.25 * fPileDetector.CuFrameX   + 0.5 * fPileDetector.CuFrameDT,
                    +0.5 * fPileDetector.CuFrameY    + 0.5 * fPileDetector.PENBandY,
                    +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.PENBandH ) ) );

    // PEN cover positions
    G4RotationMatrix rotcover = G4RotationMatrix();
    rotcover.rotateZ( 180. * deg );
    fPileDetector.PENCoverTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( -0.25 * fPileDetector.CuFrameX   - 0.5 * fPileDetector.CuFrameDT,
                    -0.5 * fPileDetector.CuFrameY    - 0.5 * fPileDetector.PENCoverY,
                    +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.PENCoverH ) ) );
    fPileDetector.PENCoverTrans.push_back( new G4Transform3D( G4RotationMatrix(),
                G4ThreeVector( +0.25 * fPileDetector.CuFrameX   + 0.5 * fPileDetector.CuFrameDT,
                    -0.5 * fPileDetector.CuFrameY    - 0.5 * fPileDetector.PENCoverY,
                    +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.PENCoverH ) ) );
    fPileDetector.PENCoverTrans.push_back( new G4Transform3D( rotcover,
                G4ThreeVector( -0.25 * fPileDetector.CuFrameX   - 0.5 * fPileDetector.CuFrameDT,
                    +0.5 * fPileDetector.CuFrameY    + 0.5 * fPileDetector.PENCoverY,
                    +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.PENCoverH ) ) );
    fPileDetector.PENCoverTrans.push_back( new G4Transform3D( rotcover,
                G4ThreeVector( +0.25 * fPileDetector.CuFrameX   + 0.5 * fPileDetector.CuFrameDT,
                    +0.5 * fPileDetector.CuFrameY    + 0.5 * fPileDetector.PENCoverY,
                    +0.5 * fPileDetector.CuTopFrameH - 0.5 * fPileDetector.PENCoverH ) ) );

    // Bottom PTFE holder positions
    for( G4int f=0; f<fPileDetector.NFloors; f++ )
    {
        for( G4double mainSign=-1; mainSign<=1; mainSign+=2 )// left-right side of the holder
        {
            G4double center = mainSign * 0.5 * ( fPileDetector.CuFrameDT + fPileDetector.CuFrameHoleL );

            for( G4double signX=-1; signX<=1; signX+=2 )
                for( G4double signY=-1; signY<=1; signY+=2 )
                {

                    G4double x = center + signX * ( +0.5 * fPileDetector.CuFrameHoleL
                            -0.5 * fPileDetector.PTFEFrameX
                            +fPileDetector.PTFEFrameT );
                    G4double y = signY * ( +0.5 * fPileDetector.CuFrameHoleL
                            -0.5 * fPileDetector.PTFEFrameX
                            +fPileDetector.PTFEFrameT );
                    G4double z = 0.5 * fPileDetector.PTFEFrameH
                        + ( fPileDetector.CrystalL + fPileDetector.CuFrameH + 2. * fPileDetector.PTFEFrameT ) * f;

                    G4ThreeVector    pos = G4ThreeVector( x, y, z );
                    G4RotationMatrix rot = G4RotationMatrix();
                    if( signX > 0 && signY > 0 )
                        rot.rotateZ( 180. * deg );
                    else if( signX < 0 && signY > 0 )
                        rot.rotateZ( 270. * deg );
                    else if( signX > 0 && signY < 0 )
                        rot.rotateZ( 90. * deg );

                    fPileDetector.BottomPTFETrans.push_back( new G4Transform3D( rot, pos ) );

                }
        }
    }

    // Top PTFE holder positions
    for( G4int f=0; f<fPileDetector.NFloors; f++ )
    {
        for( G4double mainSign=-1; mainSign<=1; mainSign+=2 )// left-right side of the holder
        {
            G4double center = mainSign * 0.5 * ( fPileDetector.CuFrameDT + fPileDetector.CuFrameHoleL );

            for( G4double signX=-1; signX<=1; signX+=2 )
                for( G4double signY=-1; signY<=1; signY+=2 )
                {

                    G4double x = center + signX * ( +0.5 * fPileDetector.CuFrameHoleL
                            -0.5 * fPileDetector.PTFEFrameX
                            +fPileDetector.PTFEFrameT );
                    G4double y = signY * ( +0.5 * fPileDetector.CuFrameHoleL
                            -0.5 * fPileDetector.PTFEFrameX
                            +fPileDetector.PTFEFrameT );
                    G4double z = -0.5 * fPileDetector.PTFEFrameH
                        + fPileDetector.CrystalL * ( f + 1 )
                        + fPileDetector.CuFrameH * f
                        + 2. * fPileDetector.PTFEFrameT * ( f + 1 );

                    G4ThreeVector    pos = G4ThreeVector( x, y, z );
                    G4RotationMatrix rot = G4RotationMatrix();
                    if( signX > 0 && signY > 0 )
                        rot.rotateZ( 180. * deg );
                    else if( signX < 0 && signY > 0 )
                        rot.rotateZ( 270. * deg );
                    else if( signX > 0 && signY < 0 )
                        rot.rotateZ( 90. * deg );

                    fPileDetector.TopPTFETrans.push_back( new G4Transform3D( rot, pos ) );

                }
        }
    }

    // Crystal and light detector positions
    for( G4int f=0; f<=fPileDetector.NFloors; f++ )
    {
        for( G4double sign=-1; sign<=1; sign+=2 )// left-right side of the holder
        {
            G4double x = sign * 0.5 * ( fPileDetector.CuFrameDT + fPileDetector.CuFrameHoleL );
            G4double y = 0.;
            G4double z = ( fPileDetector.CrystalL + fPileDetector.CuFrameH + 2. * fPileDetector.PTFEFrameT ) * f;
            fPileDetector.LightDetSolidPos.push_back( G4ThreeVector( x, y, z ) );

            if( f == fPileDetector.NFloors )
                continue;

            fPileDetector.CrystalSolidPos.push_back( G4ThreeVector( x, y, z ) );
        }
    }

    // Reflector foil position
    for( G4int f=0; f<fPileDetector.NFloors; f++ )
    {

        G4double z = ( fPileDetector.CrystalL + fPileDetector.CuFrameH + 2. * fPileDetector.PTFEFrameT ) * f;

        // reflectors along x
        for( G4double signX=-1; signX<=1; signX+=2 )// left-right side of the holder
            for( G4double signY=-1; signY<=1; signY+=2 )
            {
                G4double x = signX * 0.5 * ( fPileDetector.CuFrameDT + fPileDetector.CuFrameHoleL );
                G4double y = signY * ( 0.5 * fPileDetector.CrystalL + fPileDetector.PTFEFrameT + 0.5 * fPileDetector.ReflectorT );
                G4ThreeVector    pos = G4ThreeVector( x, y, z );
                G4RotationMatrix rot = G4RotationMatrix();

                fPileDetector.ReflectorTrans.push_back( new G4Transform3D( rot, pos ) );
            }

        // reflectors along y
        for( G4int signX=-1; signX<=1; signX+=2 )
            for( G4int signX2=-1; signX2<=1; signX2+=2 )
            {
                G4double x = signX * 0.5 * (fPileDetector.CuFrameDT + fPileDetector.CuFrameHoleL )
                    + signX2 * ( 0.5 * ( fPileDetector.CuFrameHoleL + fPileDetector.ReflectorT ) + fPileDetector.PTFEFrameT );
                G4double y = 0.;

                G4ThreeVector    pos = G4ThreeVector( x, y, z );
                G4RotationMatrix rot = G4RotationMatrix();
                rot.rotateZ( 90. * deg );

                fPileDetector.ReflectorTrans.push_back( new G4Transform3D( rot, pos ) );
            }
    }

    fPileDetector.CuFrameZ = fDetTopCuPlate.Z
        - 0.5 * fDetTopCuPlate.H
        - 0.5 * fDetBottomCuPlate.DistFromTopCuPlate
        + 0.5 * fPileDetector.CuBandH;
    fPileDetector.CuFramePos         = G4ThreeVector( 0, 0, fPileDetector.CuFrameZ );
    fPileDetector.CuFrameSourcePos   = G4ThreeVector( 0, 0, fPileDetector.CuFrameZ ) + fVacuum.Pos;

    fPileDetector.PENBandZ         = fPileDetector.CuFrameZ;
    fPileDetector.PENBandPos       = G4ThreeVector( 0, 0, fPileDetector.PENBandZ );
    fPileDetector.PENBandSourcePos = G4ThreeVector( 0, 0, fPileDetector.PENBandZ ) + fVacuum.Pos;

    fPileDetector.PENCoverZ         = fPileDetector.CuFrameZ;
    fPileDetector.PENCoverPos       = G4ThreeVector( 0, 0, fPileDetector.PENCoverZ );
    fPileDetector.PENCoverSourcePos = G4ThreeVector( 0, 0, fPileDetector.PENCoverZ ) + fVacuum.Pos;

    fPileDetector.PTFEFrameZ = fPileDetector.CuFrameZ
        + 0.5 * fPileDetector.CuTopFrameH
        - fPileDetector.CuBandH
        + fPileDetector.CuBottomFrameH;
    fPileDetector.PTFEFramePos         = G4ThreeVector( 0, 0, fPileDetector.PTFEFrameZ );
    fPileDetector.PTFEFrameSourcePos   = G4ThreeVector( 0, 0, fPileDetector.PTFEFrameZ ) + fVacuum.Pos;

    fPileDetector.CrystalZ = fPileDetector.CuFrameZ
        + 0.5 * fPileDetector.CuTopFrameH
        - fPileDetector.CuBandH
        + fPileDetector.CuBottomFrameH
        + fPileDetector.PTFEFrameT
        + 0.5 * fPileDetector.CrystalL;
    fPileDetector.CrystalPos         = G4ThreeVector( 0, 0, fPileDetector.CrystalZ );
    fPileDetector.CrystalSourcePos   = G4ThreeVector( 0, 0, fPileDetector.CrystalZ ) + fVacuum.Pos;

    fPileDetector.LightDetZ = fPileDetector.CuFrameZ
        + 0.5 * fPileDetector.CuTopFrameH
        - fPileDetector.CuBandH
        + fPileDetector.CuBottomFrameH
        + 0.5 * fPileDetector.LightDetT;
    fPileDetector.LightDetPos         = G4ThreeVector( 0, 0, fPileDetector.LightDetZ );
    fPileDetector.LightDetSourcePos   = G4ThreeVector( 0, 0, fPileDetector.LightDetZ ) + fVacuum.Pos;

    fPileDetector.ReflectorZ = fPileDetector.CrystalZ;
    fPileDetector.ReflectorPos       = G4ThreeVector( 0, 0, fPileDetector.ReflectorZ );
    fPileDetector.ReflectorSourcePos = G4ThreeVector( 0, 0, fPileDetector.ReflectorZ ) + fVacuum.Pos;

    // Tower positions
    fPileDetector.ClearanceX     = 10.  * mm;
    fPileDetector.ClearanceY     = 15.  * mm;

    for( G4int row=-3; row<=3; row++ )
        for( G4int col=0; col<4; col++ )
        {
            G4double x = ( fPileDetector.CuFrameX + fPileDetector.ClearanceX ) * row;
            G4double y = ( fPileDetector.CuFrameY + fPileDetector.ClearanceY ) * ( -1.5 + col );
            fPileDetector.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
        }

    for( G4int row=-2; row<=2; row++ )
        for( G4int col=0; col<8; col++ )
        {
            if( col>=2 && col<=5 ) continue;
            G4double x = ( fPileDetector.CuFrameX + fPileDetector.ClearanceX ) * row;
            G4double y = ( fPileDetector.CuFrameY + fPileDetector.ClearanceY ) * ( -3.5 + col );
            fPileDetector.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
        }

    for( G4int row=0; row<4; row++ )
        for( G4int col=0; col<10; col++ )
        {
            if( col>=1 && col<=8 ) continue;
            G4double x = ( fPileDetector.CuFrameX + fPileDetector.ClearanceX ) * ( -1.5 + row );
            G4double y = ( fPileDetector.CuFrameY + fPileDetector.ClearanceY ) * ( -4.5 + col );
            fPileDetector.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
        }
    for( G4int row=0; row<2; row++ )
    {
        G4double x = ( fPileDetector.CuFrameX + fPileDetector.ClearanceX ) * ( -0.5 + row );
        G4double y = ( fPileDetector.CuFrameY + fPileDetector.ClearanceY ) * -5.5;
        fPileDetector.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
    }

    fPileDetector.NTowers = fPileDetector.TowerPos.size();

    // -----------------------------------------------------------
    // Baseline Detector Prototoype Tower (BDPT (Gio, 11.05.2022).
    // Copper horizontal frames.
    // Horizontal octagonal light detectors.
    //
    // Note (Gio, 25.20.2022): I re-implemented the entire geometry
    // without using G4ExtrudedSolid and G4UnionSolid objects
    // because they conflicted with G4MultiUnion causing a bunch
    // of annoying G4Exceptions. 
    //
    // -----------------------------------------------------------

    fBDPTDetector.NFloors         = 14;

    double epsilon = 100. * um;
    // Copper frames
    fBDPTDetector.CuFrameX        = 108. * mm;

    fBDPTDetector.CuFrameY        =  65. * mm;
    fBDPTDetector.CuFrameH        =   7. * mm;

    for( double sx=-1.; sx<=1.; sx+=2. )
	{
	    fBDPTDetector.CuFrameHoleX.push_back( 45. * mm );
	    fBDPTDetector.CuFrameHoleY.push_back( 45. * mm );
	    fBDPTDetector.CuFrameHoleH.push_back( 14. * mm );
	    fBDPTDetector.CuFrameHolePos.push_back( G4ThreeVector( sx * 26.5 * mm, 0, 0 ) );
	}

    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		fBDPTDetector.CuFrameHoleX.push_back(  6.  * mm );
		fBDPTDetector.CuFrameHoleY.push_back( 16.5 * mm );
		fBDPTDetector.CuFrameHoleH.push_back( 14.  * mm );
		fBDPTDetector.CuFrameHolePos.push_back( G4ThreeVector( sx * 47. * mm, sy * 17.25 * mm, 0 ) );
	    }
    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		fBDPTDetector.CuFrameHoleX.push_back(  6.  * mm );
		fBDPTDetector.CuFrameHoleY.push_back( 16.5 * mm );
		fBDPTDetector.CuFrameHoleH.push_back( 14.  * mm );
		fBDPTDetector.CuFrameHolePos.push_back( G4ThreeVector( sx * 6. * mm, sy * 17.25 * mm, 0 ) );
	    }
    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		fBDPTDetector.CuFrameHoleX.push_back(  3.6 * mm );
		fBDPTDetector.CuFrameHoleY.push_back( 11.2 * mm );
		fBDPTDetector.CuFrameHoleH.push_back( 14.  * mm );
		fBDPTDetector.CuFrameHolePos.push_back( G4ThreeVector( sx * 16. * mm, sy * 22.5 * mm, 0 ) );
	    }
    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		fBDPTDetector.CuFrameHoleX.push_back( 27.5 * mm );
		fBDPTDetector.CuFrameHoleY.push_back(  6.  * mm );
		fBDPTDetector.CuFrameHoleH.push_back( 14.  * mm );
		fBDPTDetector.CuFrameHolePos.push_back( G4ThreeVector( sx * 54. * mm, sy * 32.5 * mm, 0 ) );
	    }
    for( double sy=-1.; sy<=1.; sy+=2. )
	{
	    fBDPTDetector.CuFrameHoleX.push_back( 69.5 * mm );
	    fBDPTDetector.CuFrameHoleY.push_back(  2.  * mm );
	    fBDPTDetector.CuFrameHoleH.push_back( 14.  * mm );
	    fBDPTDetector.CuFrameHolePos.push_back( G4ThreeVector( 0, sy * 32.5 * mm, 0 ) );
	}
    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		fBDPTDetector.CuFrameHoleX.push_back( 15.75 * mm );
		fBDPTDetector.CuFrameHoleY.push_back(  6.   * mm );
		fBDPTDetector.CuFrameHoleH.push_back( 14.   * mm );
		fBDPTDetector.CuFrameHolePos.push_back( G4ThreeVector( sx * 26.875 * mm, sy * 32.5 * mm, 0 ) );
	    }
    fBDPTDetector.CuFrameHoleX.push_back( 110. * mm );
    fBDPTDetector.CuFrameHoleY.push_back(  61. * mm );
    fBDPTDetector.CuFrameHoleH.push_back(  10. * mm );
    fBDPTDetector.CuFrameHolePos.push_back( G4ThreeVector( 0, 0, - 0.5 * fBDPTDetector.CuFrameH ) );

    

    fBDPTDetector.CuBandX           =  43. * mm;
    fBDPTDetector.CuBandY           =   1. * mm;
    fBDPTDetector.CuBandH           = 739. * mm;
    fBDPTDetector.CuBandHoleX       =  37. * mm;
    fBDPTDetector.CuBandHoleH       =  45. * mm;
    fBDPTDetector.CuBandTopHoleH    =  27. * mm;

    for( int f=0; f<14; f++ )
    {
        double z = -0.5 * fBDPTDetector.CuBandH + 16. * mm
            + ( 0.5 + f ) * fBDPTDetector.CuBandHoleH
            + 4. * mm * f;
        fBDPTDetector.CuBandHolePos.push_back( G4ThreeVector( 0., 0., z ) );
    }
    fBDPTDetector.CuBandTopHolePos = G4ThreeVector( 0., 0., 0.5 * fBDPTDetector.CuBandH - 10. * mm - 0.5 * fBDPTDetector.CuBandTopHoleH );
    
    fBDPTDetector.CuMidBandX        =   1. * mm;
    fBDPTDetector.CuMidBandY        =   3. * mm;
    fBDPTDetector.CuMidBandH        = 739. * mm;
    
    fBDPTDetector.CuLatBandX        =  13.9  * mm;
    fBDPTDetector.CuLatBandY        =   1.   * mm;
    fBDPTDetector.CuLatBandH        = 739.   * mm;
    fBDPTDetector.CuLatBandHole1X   =   5.4  * mm;
    fBDPTDetector.CuLatBandHole1Y   =   1.   * mm;
    fBDPTDetector.CuLatBandHole1H   =  20.25 * mm;
    fBDPTDetector.CuLatBandHole2X   =   5.4  * mm;
    fBDPTDetector.CuLatBandHole2Y   =   1.   * mm;
    fBDPTDetector.CuLatBandHole2H   =  16.25 * mm;
    
    for( int f=0; f<fBDPTDetector.NFloors; f++ )

	{
	    double x = -0.5 * fBDPTDetector.CuLatBandX;
	    double z = -0.5 * fBDPTDetector.CuLatBandH + 16.*mm
		+ 0.5 * fBDPTDetector.CuLatBandHole1H
		+ 49. * mm * f;
	    fBDPTDetector.CuLatBandHole1Pos.push_back( G4ThreeVector( x, 0., z ) );
	    
	    z = - 0.5 * fBDPTDetector.CuLatBandH + 16.*mm + 24.75*mm
		+ 0.5 * fBDPTDetector.CuLatBandHole2H
		+ 49. * mm * f;
	    fBDPTDetector.CuLatBandHole2Pos.push_back( G4ThreeVector( x, 0., z ) );
	}

    fBDPTDetector.CuBandLittleHoleR = 1.1 * mm;
    for( int f=0; f<fBDPTDetector.NFloors; f++ )
	{
	    fBDPTDetector.CuBandLittleHoleRot.push_back( new G4RotationMatrix() );
	    fBDPTDetector.CuBandLittleHoleRot.back()->rotateX( 90. * deg );
	    double x = 1.75 * mm;
	    double y = 0.;
	    double z = -0.5 * fBDPTDetector.CuBandH + 38.5 * mm + f * 49. * mm;
	    fBDPTDetector.CuBandLittleHolePos.push_back( G4ThreeVector( x, y, z ) );
	}


    for( double sy=-1.; sy<=1.; sy+=2. )
	{
	    fBDPTDetector.CuBandRot.push_back( G4RotationMatrix() );
	    fBDPTDetector.CuBandPos.push_back( G4ThreeVector( 0, sy * ( 34.0*mm + 3. * epsilon ), 0. ) );
	}
    for( unsigned int i=0; i<fBDPTDetector.CuBandPos.size(); i++ )
	fBDPTDetector.CuBandTrans.push_back( new G4Transform3D( fBDPTDetector.CuBandRot[i],
								fBDPTDetector.CuBandPos[i] ) );

    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	{
	    fBDPTDetector.CuMidBandPos.push_back( G4ThreeVector( sx * 21.*mm, sy * ( 32.*mm + 2. * epsilon ), 0. ) );
	    fBDPTDetector.CuMidBandRot.push_back( G4RotationMatrix() );
	}
    for( unsigned int i=0; i<fBDPTDetector.CuMidBandPos.size(); i++ )
	fBDPTDetector.CuMidBandTrans.push_back( new G4Transform3D( fBDPTDetector.CuMidBandRot[i],
								   fBDPTDetector.CuMidBandPos[i] ) );



    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		double x = sx * 27.45*mm;
		double y = sy * ( 30*mm + epsilon );
		double z = 0.;
		fBDPTDetector.CuLatBandPos.push_back( G4ThreeVector( x, y, z ) );
		fBDPTDetector.CuLatBandRot.push_back( G4RotationMatrix() );
		if( sx == 1. )
		    fBDPTDetector.CuLatBandRot.back().rotateZ( 180. * deg );
	    }
    for( unsigned int i=0; i<fBDPTDetector.CuLatBandPos.size(); i++ )
	fBDPTDetector.CuLatBandTrans.push_back( new G4Transform3D( fBDPTDetector.CuLatBandRot[i],
								   fBDPTDetector.CuLatBandPos[i] ) );
    
    for( unsigned int f=0; f<=fBDPTDetector.NFloors; f++ )
	{
	    double z = -0.5 * fBDPTDetector.CuBandH + 15. * mm + f * 49. * mm - 2.5 * mm;
	    fBDPTDetector.CuHorizontalFramePos.push_back( G4ThreeVector( 0, 0, z ) );
	    fBDPTDetector.CuHorizontalFrameRot.push_back( G4RotationMatrix() );
	    fBDPTDetector.CuHorizontalFrameTrans.push_back( new G4Transform3D( fBDPTDetector.CuHorizontalFrameRot[f],
									       fBDPTDetector.CuHorizontalFramePos[f]) );
	}

    // Bottom frame
    fBDPTDetector.CuBottomX = 108. * mm;
    fBDPTDetector.CuBottomY =  59. * mm;
    fBDPTDetector.CuBottomH =  10. * mm;

    fBDPTDetector.CuBottomPos = G4ThreeVector( 0, 0, -0.5 * fBDPTDetector.CuBandH + 0.5 * fBDPTDetector.CuBottomH );
    fBDPTDetector.CuBottomRot = G4RotationMatrix();
    fBDPTDetector.CuBottomTrans = new G4Transform3D( fBDPTDetector.CuBottomRot,
						     fBDPTDetector.CuBottomPos );

    for( double sx=-1; sx<=+1; sx+=2 )
        for( double sy=-1; sy<=+1; sy+=2 )
        {
            fBDPTDetector.CuBottomHoleX.push_back( 15.5 * mm );
            fBDPTDetector.CuBottomHoleY.push_back(  8.5 * mm );
            fBDPTDetector.CuBottomHolePos.push_back( G4ThreeVector( sx * 44.25 * mm, sy * 23.25 * mm, 0 ) );
        }
    for( double sy=-1; sy<=+1; sy+=2 )
    {
        fBDPTDetector.CuBottomHoleX.push_back( 45.  * mm );
        fBDPTDetector.CuBottomHoleY.push_back(  8.5 * mm );
        fBDPTDetector.CuBottomHolePos.push_back( G4ThreeVector( 0, sy * 23.5 * mm, 0 ) );
    }
    for( double sx=-1; sx<=+1; sx+=2 )
    {
        fBDPTDetector.CuBottomHoleX.push_back( 32. * mm );
        fBDPTDetector.CuBottomHoleY.push_back( 34. * mm );
        fBDPTDetector.CuBottomHolePos.push_back( G4ThreeVector( sx * 36. * mm, 0, 0 ) );
    }
    fBDPTDetector.CuBottomHoleX.push_back( 36. * mm );
    fBDPTDetector.CuBottomHoleY.push_back( 34. * mm );
    fBDPTDetector.CuBottomHolePos.push_back( G4ThreeVector( 0, 0, 0 ) );

    // Top frame
    fBDPTDetector.CuTopX = 108. * mm;
    fBDPTDetector.CuTopY = 59. * mm;
    fBDPTDetector.CuTopH =  2. * mm;

    fBDPTDetector.CuTopPos   = G4ThreeVector( 0, 0, 0.5 * fBDPTDetector.CuBandH - 30.5*mm - 0.5 * fBDPTDetector.CuTopH );
    fBDPTDetector.CuTopRot   = G4RotationMatrix();
    fBDPTDetector.CuTopTrans = new G4Transform3D( fBDPTDetector.CuTopRot,
						  fBDPTDetector.CuTopPos );

    // Top top frame
    fBDPTDetector.CuTopTopX = 73. * mm;
    fBDPTDetector.CuTopTopY = 59. * mm;
    fBDPTDetector.CuTopTopH = 10. * mm;

    fBDPTDetector.CuTopTopPos   = G4ThreeVector( 0, 0, 0.5 * fBDPTDetector.CuBandH - 0.5 * fBDPTDetector.CuTopTopH );
    fBDPTDetector.CuTopTopRot   = G4RotationMatrix();
    fBDPTDetector.CuTopTopTrans = new G4Transform3D( fBDPTDetector.CuTopTopRot,
						     fBDPTDetector.CuTopTopPos );

    for( double sx=-1; sx<=+1; sx+=2 )
        for( double sy=-1; sy<=+1; sy+=2 )
        {
            fBDPTDetector.CuTopTopHoleX.push_back( 16.  * mm );
            fBDPTDetector.CuTopTopHoleY.push_back( 17.5 * mm );
            fBDPTDetector.CuTopTopHolePos.push_back( G4ThreeVector( sx * 26.5 * mm, sy * 14.75 * mm, 0 ) );
        }
    for( double sy=-1; sy<=+1; sy+=2 )
    {
        fBDPTDetector.CuTopTopHoleX.push_back( 33.  * mm );
        fBDPTDetector.CuTopTopHoleY.push_back( 21.5 * mm );
        fBDPTDetector.CuTopTopHolePos.push_back( G4ThreeVector( 0, sy * 16.75 * mm, 0 ) );
    }
    for( double sx=-1; sx<=+1; sx+=2 )
    {
        fBDPTDetector.CuTopTopHoleX.push_back( 10.5 * mm );
        fBDPTDetector.CuTopTopHoleY.push_back(  8.  * mm );
        fBDPTDetector.CuTopTopHolePos.push_back( G4ThreeVector( sx * 10. * mm, 0, 0 ) );
    }

    for( double sx=-1; sx<=+1; sx+=2 )
    {
        fBDPTDetector.CuTopTopRadHoleR.push_back( 4.9 * mm );
        fBDPTDetector.CuTopTopRadHolePos.push_back( G4ThreeVector( sx * 26.5 * mm, 0, 0 ) );
    }
    fBDPTDetector.CuTopTopRadHoleR.push_back( 6.65 * mm );
    fBDPTDetector.CuTopTopRadHolePos.push_back( G4ThreeVector( 0, 0, 0 ) );

    fBDPTDetector.CuBandZ         = fDetTopCuPlate.Z
        - 0.5 * fDetTopCuPlate.H
        - 0.5 * fBDPTDetector.CuBandH
        - 30. * mm;
    fBDPTDetector.CuFrameZ = fBDPTDetector.CuBandZ;

    fBDPTDetector.CuFramePos         = G4ThreeVector( 0, 0, fBDPTDetector.CuFrameZ );
    fBDPTDetector.CuFrameSourcePos   = G4ThreeVector( 0, 0, fBDPTDetector.CuFrameZ ) + fVacuum.Pos;

    // PEN parts
    fBDPTDetector.PENBandX      =  11.5  * mm;
    fBDPTDetector.PENBandY      =   0.5  * mm;
    fBDPTDetector.PENBandH      = 716.   * mm;
    fBDPTDetector.PENBandHole1X =   5.5  * mm;
    fBDPTDetector.PENBandHole1Y =   0.5  * mm;
    fBDPTDetector.PENBandHole1H =  22.25 * mm;
    fBDPTDetector.PENBandHole2X =   5.5  * mm;
    fBDPTDetector.PENBandHole2Y =   0.5  * mm;
    fBDPTDetector.PENBandHole2H =  16.25 * mm;
    fBDPTDetector.PENBandHole3X =   5.5  * mm;
    fBDPTDetector.PENBandHole3Y =   0.5  * mm;
    fBDPTDetector.PENBandHole3H =  12.   * mm;

    for( int f=0; f<fBDPTDetector.NFloors; f++ )

	{
	    double x = -0.5 * fBDPTDetector.PENBandX;
	    double z = -0.5 * fBDPTDetector.PENBandH + 6.*mm
		+ 0.5 * fBDPTDetector.PENBandHole1H
		+ 49. * mm * f;
	    fBDPTDetector.PENBandHole1Pos.push_back( G4ThreeVector( x, 0., z ) );
	    
	    z = - 0.5 * fBDPTDetector.PENBandH + 6.*mm + 26.75*mm
		+ 0.5 * fBDPTDetector.PENBandHole2H
		+ 49. * mm * f;
	    fBDPTDetector.PENBandHole2Pos.push_back( G4ThreeVector( x, 0., z ) );
	}

    fBDPTDetector.PENBandHole2Pos.push_back( G4ThreeVector( -0.5 * fBDPTDetector.PENBandX,
							    0.,
							    0.5 * fBDPTDetector.PENBandH - 12.*mm - 0.5*fBDPTDetector.PENBandHole3H ) );
    
    fBDPTDetector.PENBandLittleHoleR = 1.6 * mm;
    for( int f=0; f<fBDPTDetector.NFloors; f++ )
	{
	    fBDPTDetector.PENBandLittleHoleRot.push_back( new G4RotationMatrix() );
	    fBDPTDetector.PENBandLittleHoleRot.back()->rotateX( 90. * deg );
	    double x = 2.55 * mm;
	    double y = 0.;
	    double z = -0.5 * fBDPTDetector.PENBandH + 30.5 * mm + f * 49. * mm;
	    fBDPTDetector.PENBandLittleHolePos.push_back( G4ThreeVector( x, y, z ) );
	}
    
    for( double sx=-1; sx<=1; sx+=2 )
	for( double sy=-1; sy<=1; sy+=2 )
	    {
		double x = sx * 28.25 * mm;
		double y = sy * ( 30.75 *mm + 2. * epsilon );
		double z = 0;//fBDPTDetector.PENBandZ;

		fBDPTDetector.PENBandRot.push_back( G4RotationMatrix() );
		if( sx == 1. )
		    fBDPTDetector.PENBandRot.back().rotateZ( 180. * deg );
		fBDPTDetector.PENBandPos.push_back( G4ThreeVector( x, y, z ) );
	    }
    
    for( unsigned int i=0; i<fBDPTDetector.PENBandPos.size(); i++ )
	fBDPTDetector.PENBandTrans.push_back( new G4Transform3D( fBDPTDetector.PENBandRot[i],
								 fBDPTDetector.PENBandPos[i] ) );


    fBDPTDetector.PENFlapX = 5.5 * mm;
    fBDPTDetector.PENFlapY = 5.8 * mm;
    fBDPTDetector.PENFlapH = 7.  * mm;
    fBDPTDetector.PENFlapT     = 0.2 * mm;

    for( int f=0; f<=fBDPTDetector.NFloors; f++ )

	for( double sx=-1; sx<=1; sx+=2 )
	    for( double sy=-1; sy<=1; sy+=2 )
		{
		    double x = sx * 37.5 * mm;
		    double y = sy * 29.8 * mm;
		    double z = -0.5 * fBDPTDetector.CuBandH + 15. * mm + f * 49. * mm -2.5 * mm
			+ 0.5 * fBDPTDetector.PENFlapH + 0.5 * fBDPTDetector.PENFlapT + epsilon;
		    fBDPTDetector.PENFlapPos.push_back( G4ThreeVector( x, y, z ) );
		    fBDPTDetector.PENFlapRot.push_back( G4RotationMatrix() );
		    if( sy == 1 ) fBDPTDetector.PENFlapRot.back().rotateZ( 180. * deg );
		    fBDPTDetector.PENFlapTrans.push_back( new G4Transform3D( fBDPTDetector.PENFlapRot.back(),
									     fBDPTDetector.PENFlapPos.back() ) );
		}

    fBDPTDetector.PENZ           = fBDPTDetector.CuFrameZ
	- 0.5 * fBDPTDetector.CuBandH + 0.5 * fBDPTDetector.PENBandH + 8.*mm;
    fBDPTDetector.PENPos         = G4ThreeVector( 0, 0, fBDPTDetector.PENZ );
    fBDPTDetector.PENSourcePos   = G4ThreeVector( 0, 0, fBDPTDetector.PENZ ) + fVacuum.Pos;

    // PTFE parts (slightly approximated, e.g. with no edge roundings)

    fBDPTDetector.PTFECornerX = 9. * mm;
    fBDPTDetector.PTFECornerY = 10. * mm;
    fBDPTDetector.PTFECornerH = 8. * mm;
    fBDPTDetector.PTFECornerDiagHoleX = 7.4 * mm;
    fBDPTDetector.PTFECornerDiagHoleRot = new G4RotationMatrix();
    fBDPTDetector.PTFECornerDiagHoleRot->rotateZ( 45. * deg );
    fBDPTDetector.PTFECornerDiagHolePos = G4ThreeVector( 0.5 * fBDPTDetector.PTFECornerX, 0.5 * fBDPTDetector.PTFECornerY, 0 );
    fBDPTDetector.PTFECornerTopHoleX = 5.2 * mm;
    fBDPTDetector.PTFECornerTopHoleH = 2. * mm;
    for( double sign=-1; sign<=2.; sign+=2. )
	{
	    fBDPTDetector.PTFECornerTopHoleRot.push_back( new G4RotationMatrix() );
	    fBDPTDetector.PTFECornerTopHolePos.push_back( G4ThreeVector( 0.5 * fBDPTDetector.PTFECornerX,
									 0.5 * fBDPTDetector.PTFECornerY,
									 sign * 0.5 * fBDPTDetector.PTFECornerH ) );
	}
    fBDPTDetector.PTFECornerXHoleX = 3. * mm;
    fBDPTDetector.PTFECornerXHoleY = 10. * mm;
    fBDPTDetector.PTFECornerXHoleH = 2. * mm;
    fBDPTDetector.PTFECornerXHoleRot = new G4RotationMatrix();
    fBDPTDetector.PTFECornerXHolePos = G4ThreeVector( -0.5 * fBDPTDetector.PTFECornerX, 0, 0 );
    fBDPTDetector.PTFECornerYHoleX = 9. * mm;
    fBDPTDetector.PTFECornerYHoleY = 2. * mm;
    fBDPTDetector.PTFECornerYHoleH = 2. * mm;
    fBDPTDetector.PTFECornerYHoleRot = new G4RotationMatrix();
    fBDPTDetector.PTFECornerYHolePos = G4ThreeVector( 0, -0.5 * fBDPTDetector.PTFECornerY, 0 );
    

    fBDPTDetector.PTFECornerPos.push_back( G4ThreeVector( -48.5*mm, -22.5*mm, 0. ) );
    fBDPTDetector.PTFECornerRot.push_back( G4RotationMatrix() );

    fBDPTDetector.PTFECornerPos.push_back( G4ThreeVector( -48.5*mm, +22.5*mm, 0. ) );
    fBDPTDetector.PTFECornerRot.push_back( G4RotationMatrix() );
    fBDPTDetector.PTFECornerRot.back().rotateX( 180. * deg );

    fBDPTDetector.PTFECornerPos.push_back( G4ThreeVector( +48.5*mm, -22.5*mm, 0. ) );
    fBDPTDetector.PTFECornerRot.push_back( G4RotationMatrix() );
    fBDPTDetector.PTFECornerRot.back().rotateY( 180. * deg );

    fBDPTDetector.PTFECornerPos.push_back( G4ThreeVector( +48.5*mm, +22.5*mm, 0. ) );
    fBDPTDetector.PTFECornerRot.push_back( G4RotationMatrix() );
    fBDPTDetector.PTFECornerRot.back().rotateX( 180. * deg );
    fBDPTDetector.PTFECornerRot.back().rotateY( 180. * deg );

    fBDPTDetector.PTFECornerPos.push_back( G4ThreeVector( +4.5*mm, -22.5*mm, 0. ) );
    fBDPTDetector.PTFECornerRot.push_back( G4RotationMatrix() );

    fBDPTDetector.PTFECornerPos.push_back( G4ThreeVector( +4.5*mm, +22.5*mm, 0. ) );
    fBDPTDetector.PTFECornerRot.push_back( G4RotationMatrix() );
    fBDPTDetector.PTFECornerRot.back().rotateX( 180. * deg );

    fBDPTDetector.PTFECornerPos.push_back( G4ThreeVector( -4.5*mm, -22.5*mm, 0. ) );
    fBDPTDetector.PTFECornerRot.push_back( G4RotationMatrix() );
    fBDPTDetector.PTFECornerRot.back().rotateY( 180. * deg );

    fBDPTDetector.PTFECornerPos.push_back( G4ThreeVector( -4.5*mm, +22.5*mm, 0. ) );
    fBDPTDetector.PTFECornerRot.push_back( G4RotationMatrix() );
    fBDPTDetector.PTFECornerRot.back().rotateX( 180. * deg );
    fBDPTDetector.PTFECornerRot.back().rotateY( 180. * deg );

    for( unsigned int f=0; f<=fBDPTDetector.NFloors; f++ )

	for( unsigned int i=0; i<fBDPTDetector.PTFECornerPos.size(); i++ )
	    {
		double z = -0.5 * fBDPTDetector.CuBandH + 15. * mm + f * 49. * mm
		    -0.5 * fBDPTDetector.CuFrameH;

		fBDPTDetector.PTFECornerTrans.push_back( new G4Transform3D( fBDPTDetector.PTFECornerRot[i],
									    fBDPTDetector.PTFECornerPos[i] + G4ThreeVector( 0, 0, z ) ) );
	    }

    fBDPTDetector.PTFEButterflyBottomR = 2.75 * mm;
    fBDPTDetector.PTFEButterflyBottomH = 2.   * mm;
    fBDPTDetector.PTFEButterflyTopR    = 1.5  * mm;
    fBDPTDetector.PTFEButterflyTopH    = 6.   * mm;
    fBDPTDetector.PTFEButterflyFlapX   = 7.   * mm;
    fBDPTDetector.PTFEButterflyFlapY   = 2.85 * mm;
    fBDPTDetector.PTFEButterflyFlapH   = 2.   * mm;
    fBDPTDetector.PTFEButterflyFlapDZ  = 2.5 * mm;

    for( double sx=-1.; sx<=1.; sx+=2. )
	for( double sy=-1.; sy<=1.; sy+=2. )
	    {
		fBDPTDetector.PTFEButterflyFlapPos.push_back( G4ThreeVector( sx * 16. * mm, sy * 24.125 * mm, 0. ) );
		fBDPTDetector.PTFEButterflyFlapRot.push_back( G4RotationMatrix() );
		
		fBDPTDetector.PTFEButterflyTopPos.push_back( G4ThreeVector( sx * 16. * mm, sy * 26.5 * mm, 0. ) );
		fBDPTDetector.PTFEButterflyTopRot.push_back( G4RotationMatrix() );
		
		fBDPTDetector.PTFEButterflyBottomPos.push_back( G4ThreeVector( sx * 16. * mm, sy * 26.5 * mm, 0. ) );
		fBDPTDetector.PTFEButterflyBottomRot.push_back( G4RotationMatrix() );
	    }
    
    for( unsigned int f=0; f<=fBDPTDetector.NFloors; f++ )
	for( unsigned int i=0; i<fBDPTDetector.PTFEButterflyTopPos.size(); i++ )
	    {
		double z = -0.5 * fBDPTDetector.CuBandH -0.5 * fBDPTDetector.CuFrameH + 15. * mm + f * 49. * mm
		    - fBDPTDetector.PTFEButterflyBottomH;
		fBDPTDetector.PTFEButterflyBottomTrans.push_back( new G4Transform3D( fBDPTDetector.PTFEButterflyBottomRot[i],
										     fBDPTDetector.PTFEButterflyBottomPos[i] + G4ThreeVector( 0, 0, z ) ) );
		
		z = -0.5 * fBDPTDetector.CuBandH -0.5 * fBDPTDetector.CuFrameH + 15. * mm + f * 49. * mm
		    - 0.5 * fBDPTDetector.PTFEButterflyBottomH
		    + 0.5 * fBDPTDetector.PTFEButterflyTopH;
		fBDPTDetector.PTFEButterflyTopTrans.push_back( new G4Transform3D( fBDPTDetector.PTFEButterflyTopRot[i],
										  fBDPTDetector.PTFEButterflyTopPos[i] + G4ThreeVector( 0, 0, z ) ) );
		
		z = -0.5 * fBDPTDetector.CuBandH -0.5 * fBDPTDetector.CuFrameH + 15. * mm + f * 49. * mm
		    - 0.5 * fBDPTDetector.PTFEButterflyBottomH
		    + fBDPTDetector.PTFEButterflyFlapDZ
		    + 0.5 * fBDPTDetector.PTFEButterflyFlapH;
		fBDPTDetector.PTFEButterflyFlapTrans.push_back( new G4Transform3D( fBDPTDetector.PTFEButterflyFlapRot[i],
										   fBDPTDetector.PTFEButterflyFlapPos[i] + G4ThreeVector( 0, 0, z ) ) );
		
	    }

    fBDPTDetector.PTFELargeCapR = 3.  * mm;
    fBDPTDetector.PTFESmallCapR = 1.  * mm;
    fBDPTDetector.PTFELargeCapH = 1.5 * mm;
    fBDPTDetector.PTFESmallCapH = 6.4 * mm;

    for( int f=0; f<fBDPTDetector.NFloors; f++ )

	for( double sx=-1; sx<=1; sx+=2 )
	    for( double sy=-1; sy<=1; sy+=2 )
		{
		    fBDPTDetector.PTFECapRot.push_back( G4RotationMatrix() );
		    fBDPTDetector.PTFECapRot.back().rotateX( sy * 90. * deg );
		    double x = sx * 25.7 * mm;
		    double y = sy * 32. * mm;
		    double z = -0.5 * fBDPTDetector.CuBandH + 37.5 * mm + f * 49. * mm - 2.5 * mm;
		    fBDPTDetector.PTFELargeCapPos.push_back( G4ThreeVector( x, y, z ) );
		    fBDPTDetector.PTFELargeCapTrans.push_back( new G4Transform3D( fBDPTDetector.PTFECapRot.back(),
										  fBDPTDetector.PTFELargeCapPos.back() ) );
		    y = sy * (  32. * mm - 0.5 * fBDPTDetector.PTFELargeCapH - 0.5 * fBDPTDetector.PTFESmallCapH );
		    fBDPTDetector.PTFESmallCapPos.push_back( G4ThreeVector( x, y, z ) );
		    fBDPTDetector.PTFESmallCapTrans.push_back( new G4Transform3D( fBDPTDetector.PTFECapRot.back(),
										  fBDPTDetector.PTFESmallCapPos.back() ) );
		}

    fBDPTDetector.PTFEZ           = fBDPTDetector.CuFrameZ - 0.5 * ( fBDPTDetector.PTFEMiddleH - fBDPTDetector.CuFrameH );
    fBDPTDetector.PTFEPos         = G4ThreeVector( 0, 0, fBDPTDetector.PTFEZ );
    fBDPTDetector.PTFESourcePos   = G4ThreeVector( 0, 0, fBDPTDetector.PTFEZ ) + fVacuum.Pos;
    // Light detectors
    fBDPTDetector.LightDetPolygon.push_back( G4TwoVector( -15.7 * mm, -24.3 * mm ) );
    fBDPTDetector.LightDetPolygon.push_back( G4TwoVector( +15.7 * mm, -24.3 * mm ) );
    fBDPTDetector.LightDetPolygon.push_back( G4TwoVector( +24.3 * mm, -15.7 * mm ) );
    fBDPTDetector.LightDetPolygon.push_back( G4TwoVector( +24.3 * mm, +15.7 * mm ) );
    fBDPTDetector.LightDetPolygon.push_back( G4TwoVector( +15.7 * mm, +24.3 * mm ) );
    fBDPTDetector.LightDetPolygon.push_back( G4TwoVector( -15.7 * mm, +24.3 * mm ) );
    fBDPTDetector.LightDetPolygon.push_back( G4TwoVector( -24.3 * mm, +15.7 * mm ) );
    fBDPTDetector.LightDetPolygon.push_back( G4TwoVector( -24.3 * mm, -15.7 * mm ) );

    fBDPTDetector.LightDetT = 0.5 * mm;

    for( unsigned int f=0; f<=fBDPTDetector.NFloors; f++ )

	{
	    double z = -0.5 * fBDPTDetector.CuBandH + 15. * mm + f * 49. * mm - 2.5 * mm
		+ 0.5 * fBDPTDetector.CuFrameH
		+ 0.5 * fBDPTDetector.LightDetT;
	    fBDPTDetector.LightDetSolidPos.push_back( G4ThreeVector( -26.5 * mm, 0, z ) );
	    fBDPTDetector.LightDetSolidPos.push_back( G4ThreeVector( +26.5 * mm, 0, z ) );
	}

    fBDPTDetector.LightDetZ = fBDPTDetector.CuFrameZ;
    fBDPTDetector.LightDetPos       = G4ThreeVector( 0, 0, fBDPTDetector.LightDetZ );
    fBDPTDetector.LightDetSourcePos = G4ThreeVector( 0, 0, fBDPTDetector.LightDetZ ) + fVacuum.Pos;

    // Light detector coating
    
    fBDPTDetector.LightDetCoatingT = 70 * nm;

    for( unsigned int f=0; f<=fBDPTDetector.NFloors; f++ )

        {
            double z = -0.5 * fBDPTDetector.CuBandH + 15. * mm + f * 49. * mm - 2.5 * mm
                + 0.5 * fBDPTDetector.CuFrameH
                + 0.5 * fBDPTDetector.LightDetT
		+ 0.5 * fBDPTDetector.LightDetT
		- 0.5 * fBDPTDetector.LightDetCoatingT;
            fBDPTDetector.LightDetCoatingSolidPos.push_back( G4ThreeVector( -26.5 * mm, 0, z ) );
            fBDPTDetector.LightDetCoatingSolidPos.push_back( G4ThreeVector( +26.5 * mm, 0, z ) );

	    double z2 = -0.5 * fBDPTDetector.CuBandH + 15. * mm + f * 49. * mm - 2.5 * mm
                + 0.5 * fBDPTDetector.CuFrameH
                + 0.5 * fBDPTDetector.LightDetT
                - 0.5 * fBDPTDetector.LightDetT
                + 0.5 * fBDPTDetector.LightDetCoatingT;

	    fBDPTDetector.LightDetCoatingSolidPos.push_back( G4ThreeVector( -26.5 * mm, 0, z2 ) );
            fBDPTDetector.LightDetCoatingSolidPos.push_back( G4ThreeVector( +26.5 * mm, 0, z2 ) );
        }

    fBDPTDetector.LightDetCoatingZ = fBDPTDetector.LightDetZ;
    fBDPTDetector.LightDetCoatingPos       = G4ThreeVector( 0, 0, fBDPTDetector.LightDetCoatingZ );
    fBDPTDetector.LightDetCoatingSourcePos = G4ThreeVector( 0, 0, fBDPTDetector.LightDetCoatingZ ) + fVacuum.Pos;
    


    // Crystals
    fBDPTDetector.CrystalL        = 45.    * mm;
    fBDPTDetector.CrystalOffset   = 0.5 * fBDPTDetector.CrystalL + 4. * mm;

    for( unsigned int f=0; f<fBDPTDetector.NFloors; f++ )
    {
        double z = -0.5 * fBDPTDetector.CuBandH + 17. * mm + f * 49. * mm;
        fBDPTDetector.CrystalSolidPos.push_back( G4ThreeVector( -26.5 * mm, 0, z ) );
        fBDPTDetector.CrystalSolidPos.push_back( G4ThreeVector( +26.5 * mm, 0, z ) );
    }

    fBDPTDetector.CrystalZ = fBDPTDetector.CuFrameZ

	+ 0.5 * fBDPTDetector.CrystalL;
    G4cout << fBDPTDetector.CrystalZ << G4endl;
    G4cout << fVacuum.Pos << G4endl;
    fBDPTDetector.CrystalPos       = G4ThreeVector( 0, 0, fBDPTDetector.CrystalZ );
    fBDPTDetector.CrystalSourcePos = G4ThreeVector( 0, 0, fBDPTDetector.CrystalZ ) + fVacuum.Pos;

    // Tower positions
    fBDPTDetector.ClearanceX = 112. * mm;
    fBDPTDetector.ClearanceY = 80. * mm;
    /*    
    for( G4int row=0; row<=0; row++ )
    	for( G4int col=0; col<=0; col++ )
	    {
		G4double x = fBDPTDetector.ClearanceX * row;
		G4double y = fBDPTDetector.ClearanceY * col;
		fBDPTDetector.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
	    }
    */
    for( G4int row=-3; row<=3; row++ )
        for( G4int col=-2; col<=2; col++ )
        {
            G4double x = fBDPTDetector.ClearanceX * row;
            G4double y = fBDPTDetector.ClearanceY * col;
            fBDPTDetector.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
        }
    for( G4int row=-3; row<=2; row++ )
        for( G4int col=-3; col<=3; col+=6 )
        {
            G4double x = fBDPTDetector.ClearanceX * ( 0.5 + row );
            G4double y = fBDPTDetector.ClearanceY * col;
            fBDPTDetector.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
        }
    for( G4int row=-1; row<=1; row+=1 )
        for( G4int col=-4; col<=4; col+=8 )
        {
            G4double x = fBDPTDetector.ClearanceX * row;
            G4double y = fBDPTDetector.ClearanceY * col;
            fBDPTDetector.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
        }
    for( G4int row=-1; row<=0; row++ )

	for( G4int col=-5; col<=5; col+=10 )
	    {
		G4double x = fBDPTDetector.ClearanceX * ( 0.5 + row );
		G4double y = fBDPTDetector.ClearanceY * col;
		fBDPTDetector.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
	    }

    fBDPTDetector.NTowers = fBDPTDetector.TowerPos.size();


    // -----------------------------------------
    // Cuore-like detector tower (Gio, 06.04.20)
    // Horizontal light detector
    // -----------------------------------------

    fCuoreLikeDetector.NFloors          = 2;
    fCuoreLikeDetector.CrystalL         = 45.  * mm;
    fCuoreLikeDetector.LightDetL        = 45.  * mm;
    fCuoreLikeDetector.LightDetT        = 0.5  * mm;
    fCuoreLikeDetector.CuFrameX         = 112. * mm;
    fCuoreLikeDetector.CuFrameY         = fCuoreLikeDetector.CuFrameX;
    fCuoreLikeDetector.CuFrameH         = 12.  * mm;
    fCuoreLikeDetector.CuTopFrameH      = 9.  * mm;
    fCuoreLikeDetector.CuBottomFrameH   = 9.  * mm;
    fCuoreLikeDetector.CuFrameDT        = 4.   * mm;// Lateral thickness
    fCuoreLikeDetector.CuFrameHoleL     = 0.5 * ( fCuoreLikeDetector.CuFrameX - 3. * fCuoreLikeDetector.CuFrameDT );
    fCuoreLikeDetector.CuFrameHoleL2    = 33.7 * mm;// 2 of the central frame beams are cut by this amount
    fCuoreLikeDetector.CuFrameThinningL = 33.2 * mm;
    fCuoreLikeDetector.CuFrameThinningH = 3.   * mm;

    double tmpD = 0.5 * fCuoreLikeDetector.CuFrameDT// X-Y Position of frame hole
        + 0.5 * fCuoreLikeDetector.CuFrameHoleL;

    // Holes for detectors
    fCuoreLikeDetector.CuHolePos.push_back( G4ThreeVector( +tmpD, +tmpD, 0 ) );
    fCuoreLikeDetector.CuHolePos.push_back( G4ThreeVector( -tmpD, +tmpD, 0 ) );
    fCuoreLikeDetector.CuHolePos.push_back( G4ThreeVector( -tmpD, -tmpD, 0 ) );
    fCuoreLikeDetector.CuHolePos.push_back( G4ThreeVector( +tmpD, -tmpD, 0 ) );

    // Holes in central frame beams
    fCuoreLikeDetector.CuHolePos2.push_back( G4ThreeVector( +tmpD, 0, 0 ) );
    fCuoreLikeDetector.CuHolePos2.push_back( G4ThreeVector( -tmpD, 0, 0 ) );

    // Frame thinnings
    double tmpD2 = 0.5 * fCuoreLikeDetector.CuFrameX
        - 0.5 * fCuoreLikeDetector.CuFrameDT;
    double tmpH = 0.5 * fCuoreLikeDetector.CuFrameH;

    for( double sign=-1.; sign<=1.; sign+=2. )
    {
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( +tmpD,  +tmpD2, sign * tmpH ) );
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( +tmpD,  -tmpD2, sign * tmpH ) );
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( -tmpD,  +tmpD2, sign * tmpH ) );
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( -tmpD,  -tmpD2, sign * tmpH ) );
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( +tmpD2, +tmpD,  sign * tmpH ) );
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( +tmpD2, -tmpD,  sign * tmpH ) );
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( -tmpD2, +tmpD,  sign * tmpH ) );
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( -tmpD2, -tmpD,  sign * tmpH ) );
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( 0,      +tmpD,  sign * tmpH ) );
        fCuoreLikeDetector.CuFrameThinningPos.push_back( G4ThreeVector( 0,      -tmpD,  sign * tmpH ) );
        // Thinnings along x
        for( int i=0; i<4; i++ )
            fCuoreLikeDetector.CuFrameThinningRot.push_back( new G4RotationMatrix() );
        // Thinnings along y
        for( int i=0; i<6; i++ )
        {
            fCuoreLikeDetector.CuFrameThinningRot.push_back( new G4RotationMatrix() );
            fCuoreLikeDetector.CuFrameThinningRot.back()->rotateZ( 90. * deg );
        }
    }

    tmpH = -0.5 * fCuoreLikeDetector.CuTopFrameH;
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( +tmpD,  +tmpD2, tmpH ) );
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( +tmpD,  -tmpD2, tmpH ) );
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( -tmpD,  +tmpD2, tmpH ) );
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( -tmpD,  -tmpD2, tmpH ) );
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( +tmpD2, +tmpD,  tmpH ) );
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( +tmpD2, -tmpD,  tmpH ) );
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( -tmpD2, +tmpD,  tmpH ) );
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( -tmpD2, -tmpD,  tmpH ) );
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( 0,      +tmpD,  tmpH ) );
    fCuoreLikeDetector.CuTopFrameThinningPos.push_back( G4ThreeVector( 0,      -tmpD,  tmpH ) );

    tmpH = 0.5 * fCuoreLikeDetector.CuBottomFrameH;
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( +tmpD,  +tmpD2, tmpH ) );
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( +tmpD,  -tmpD2, tmpH ) );
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( -tmpD,  +tmpD2, tmpH ) );
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( -tmpD,  -tmpD2, tmpH ) );
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( +tmpD2, +tmpD,  tmpH ) );
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( +tmpD2, -tmpD,  tmpH ) );
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( -tmpD2, +tmpD,  tmpH ) );
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( -tmpD2, -tmpD,  tmpH ) );
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( 0,      +tmpD,  tmpH ) );
    fCuoreLikeDetector.CuBottomFrameThinningPos.push_back( G4ThreeVector( 0,      -tmpD,  tmpH ) );

    // Copper columns
    fCuoreLikeDetector.CuColumnR = 0.5 * fCuoreLikeDetector.CuFrameDT;
    fCuoreLikeDetector.CuColumnH = 41. * mm;
    tmpD = 0.5 * fCuoreLikeDetector.CuFrameX - fCuoreLikeDetector.CuColumnR;
    fCuoreLikeDetector.CuColumnPos.push_back( G4ThreeVector( +tmpD, 0., 0. ) );
    fCuoreLikeDetector.CuColumnPos.push_back( G4ThreeVector( -tmpD, 0., 0. ) );
    fCuoreLikeDetector.CuColumnPos.push_back( G4ThreeVector( 0., +tmpD, 0. ) );
    fCuoreLikeDetector.CuColumnPos.push_back( G4ThreeVector( 0., -tmpD, 0. ) );

    fCuoreLikeDetector.TowerH = fCuoreLikeDetector.CuTopFrameH
        + fCuoreLikeDetector.CuBottomFrameH
        + fCuoreLikeDetector.CuFrameH * ( fCuoreLikeDetector.NFloors - 1 )
        + fCuoreLikeDetector.CuColumnH * fCuoreLikeDetector.NFloors;

    // PTFE dimensions (see drawing in AgataCuoreLikeDetector.cc)
    fCuoreLikeDetector.t1x = 6.  * mm;
    fCuoreLikeDetector.t1y = 20. * mm;
    fCuoreLikeDetector.t1z = 7.  * mm;
    fCuoreLikeDetector.t2x = 8. * sqrt(2.) * mm;
    fCuoreLikeDetector.t2y = 8. * sqrt(2.) * mm;
    fCuoreLikeDetector.t2z = 8.  * mm;
    fCuoreLikeDetector.t2t = 10. * mm;

    fCuoreLikeDetector.b1x = 20. * mm;
    fCuoreLikeDetector.b1y = 20. * mm;
    fCuoreLikeDetector.b1z = 5.  * mm;
    fCuoreLikeDetector.b2x = 10. * sqrt(2.) * mm;
    fCuoreLikeDetector.b2y = 10. * sqrt(2.) * mm;
    fCuoreLikeDetector.b2z = 12. * mm;
    fCuoreLikeDetector.b1t = 10. * mm;
    fCuoreLikeDetector.b2t = -3. * mm;

    fCuoreLikeDetector.b3x = 18.  * mm;
    fCuoreLikeDetector.b3y = 18.  * mm;
    fCuoreLikeDetector.b3z = 10.  * mm;
    fCuoreLikeDetector.b3t = -10. * mm;

    // Clearance between towers
    fCuoreLikeDetector.ClearanceX     = 15.  * mm;
    fCuoreLikeDetector.ClearanceY     = 15.  * mm;

    fCuoreLikeDetector.CuBandX        = 12.  * mm;
    fCuoreLikeDetector.CuBandY        = 2.   * mm;
    fCuoreLikeDetector.CuBandH        = 730. * mm;

    // Physical volume positions
    G4double tmpShiftZ = 10. * mm;
    fCuoreLikeDetector.CuFrameZ = fDetTopCuPlate.Z
        - 0.5 * fDetTopCuPlate.H
        - 0.5 * tmpShiftZ
        - 0.5 * fCuoreLikeDetector.CuTopFrameH;

    fCuoreLikeDetector.CuFramePos         = G4ThreeVector( 0, 0, fCuoreLikeDetector.CuFrameZ );
    fCuoreLikeDetector.CuFrameSourcePos   = G4ThreeVector( 0, 0, fCuoreLikeDetector.CuFrameZ ) + fVacuum.Pos;
    fCuoreLikeDetector.CrystalPos         = G4ThreeVector();// Crystal pos assigned via CrystalSolidPos
    fCuoreLikeDetector.CrystalSourcePos   = G4ThreeVector() + fVacuum.Pos;
    fCuoreLikeDetector.LightDetPos         = G4ThreeVector();// LightDet pos assigned via LightDetSolidPos
    fCuoreLikeDetector.LightDetSourcePos   = G4ThreeVector() + fVacuum.Pos;
    fCuoreLikeDetector.PTFEFramePos         = G4ThreeVector();// PTFEFrame pos assigned via PTFEPos
    fCuoreLikeDetector.PTFEFrameSourcePos   = G4ThreeVector() + fVacuum.Pos;

    for( G4int i=0; i<fCuoreLikeDetector.NFloors; i++ )
    {
        for( G4int quarter=1; quarter<=4; quarter++ )
        {
            G4double mainSignX = +1.;
            G4double mainSignY = +1.;

            if( quarter == 2 || quarter == 3 )
                mainSignX  = -1.;
            if( quarter > 2 )
                mainSignY = -1;

            G4double x = mainSignX * 0.5 * ( fCuoreLikeDetector.CuFrameDT + fCuoreLikeDetector.CuFrameHoleL );
            G4double y = mainSignY * 0.5 * ( fCuoreLikeDetector.CuFrameDT + fCuoreLikeDetector.CuFrameHoleL );

            // Crystal positions
            G4double z = fCuoreLikeDetector.CuFrameZ
                - 0.5 * fCuoreLikeDetector.CuTopFrameH
                - ( 0.5 + i ) * fCuoreLikeDetector.CuColumnH
                - fCuoreLikeDetector.CuFrameH * i;
            fCuoreLikeDetector.CrystalSolidPos.push_back( G4ThreeVector( x, y, z ) );

            // Light detector positions
            z = fCuoreLikeDetector.CuFrameZ
                - 0.5 * fCuoreLikeDetector.CuTopFrameH
                - fCuoreLikeDetector.CuColumnH * i
                - fCuoreLikeDetector.CuFrameH * i
                + fCuoreLikeDetector.b1z
                + 0.5 * fCuoreLikeDetector.LightDetT;
            fCuoreLikeDetector.LightDetSolidPos.push_back( G4ThreeVector( x, y, z ) );

            // PTFE holders
            for( G4double angle=45.; angle<360.; angle+=90. )
            {
                G4double signX = 1.;
                G4double signY = 1.;
                if( angle > 90. && angle <= 270. ) signY = -1.;
                if( angle > 180. ) signX = -1.;

                G4double shift = 0.5 * fCuoreLikeDetector.CuFrameHoleL;
                G4double thisX = x + signX * shift;
                G4double thisY = y + signY * shift;

                // PTFE holders on top of the crystals
                z = fCuoreLikeDetector.CuFrameZ
                    - 0.5 * fCuoreLikeDetector.CuTopFrameH
                    - fCuoreLikeDetector.CuColumnH * i
                    - fCuoreLikeDetector.CuFrameH * i
                    - 0.5 * fCuoreLikeDetector.t1z
                    + fCuoreLikeDetector.b1z;

                fCuoreLikeDetector.PTFEPos.push_back( G4ThreeVector( thisX, thisY, z ) );
                fCuoreLikeDetector.PTFERot.push_back( new G4RotationMatrix() );
                fCuoreLikeDetector.PTFERot.back()->rotateZ( angle * deg );
                fCuoreLikeDetector.PTFERot.back()->rotateX( 180. * deg );

                // PTFE holders on bottom of the crystals
                z = fCuoreLikeDetector.CuFrameZ
                    - 0.5 * fCuoreLikeDetector.CuTopFrameH
                    - fCuoreLikeDetector.CuColumnH * ( i + 1 )
                    - fCuoreLikeDetector.CuFrameH * i
                    + 0.5 * fCuoreLikeDetector.t1z
                    - fCuoreLikeDetector.b1z;

                fCuoreLikeDetector.PTFEPos.push_back( G4ThreeVector( thisX, thisY, z ) );
                fCuoreLikeDetector.PTFERot.push_back( new G4RotationMatrix() );
                fCuoreLikeDetector.PTFERot.back()->rotateZ( ( 180. + angle ) * deg );

            }
        }

    }

    //fCuoreLikeDetector.TowerPos.push_back( G4ThreeVector( 0, 0, 0 ) );

    // Tower positions
    for( G4int row=-3; row<=3; row++ )
        for( G4int col=0; col<2; col++ )
        {
            G4double tmpX = ( fCuoreLikeDetector.CuFrameX + fCuoreLikeDetector.ClearanceX ) * row;
            G4double tmpY = ( fCuoreLikeDetector.CuFrameY + fCuoreLikeDetector.ClearanceY ) * ( -0.5 + col );
            fCuoreLikeDetector.TowerPos.push_back( G4ThreeVector( tmpX, tmpY, 0 ) );
        }

    for( G4int row=0; row<6; row++ )
        for( G4int col=0; col<2; col++ )
        {
            G4double tmpX = ( fCuoreLikeDetector.CuFrameX + fCuoreLikeDetector.ClearanceX ) * ( -2.5 + row );
            G4double tmpY = ( fCuoreLikeDetector.CuFrameY + fCuoreLikeDetector.ClearanceY ) * ( -1.5 + col * 3 );
            fCuoreLikeDetector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
        }
    for( G4int row=0; row<4; row++ )
        for( G4int col=0; col<2; col++ )
        {
            G4double tmpX = ( fCuoreLikeDetector.CuFrameX + fCuoreLikeDetector.ClearanceX ) * ( -1.5 + row );
            G4double tmpY = ( fCuoreLikeDetector.CuFrameY + fCuoreLikeDetector.ClearanceY ) * ( -2.5 + col * 5 );
            fCuoreLikeDetector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
        }


    fCuoreLikeDetector.NTowers = fCuoreLikeDetector.TowerPos.size();




    // -----------------------------------------
    // Canfranc-like detector tower (Gio, 15.04.20)
    // Horizontal light detector
    // -----------------------------------------

    fCanfrancLikeDetector.NFloors          = 13;
    fCanfrancLikeDetector.CrystalL         = 45.   * mm;
    fCanfrancLikeDetector.LightDetL        = 45.   * mm;
    fCanfrancLikeDetector.LightDetT        = 0.5   * mm;
    fCanfrancLikeDetector.CuFrameX         = 113.5 * mm;
    fCanfrancLikeDetector.CuFrameY         = fCanfrancLikeDetector.CuFrameX;
    fCanfrancLikeDetector.CuFrameH         = 5.    * mm;
    fCanfrancLikeDetector.CuFrameLateralT  = 5.    * mm;
    fCanfrancLikeDetector.CuFrameCentralT  = 7.    * mm;
    fCanfrancLikeDetector.CuFrameHoleL     = 48.25 * mm;
    fCanfrancLikeDetector.CuFrameShortGap  = 4.    * mm;// Gap around light detector
    fCanfrancLikeDetector.CuFrameLongGap   = 44.   * mm;// Gap around crystal
    fCanfrancLikeDetector.CuColumnR        = 3.    * mm;
    fCanfrancLikeDetector.CuColumnOffset   = 5.    * mm;
    fCanfrancLikeDetector.CuColumnDistance = 110.5 * mm;// Distance between column centers
    fCanfrancLikeDetector.CuColumnH = fCanfrancLikeDetector.CuFrameLongGap * fCanfrancLikeDetector.NFloors
        + fCanfrancLikeDetector.CuFrameShortGap * ( fCanfrancLikeDetector.NFloors + 1 )
        + fCanfrancLikeDetector.CuFrameH * 2. * ( fCanfrancLikeDetector.NFloors + 1. )
        + 2. * fCanfrancLikeDetector.CuColumnOffset;

    // Hole position
    tmpD = 0.5 * fCanfrancLikeDetector.CuFrameCentralT
        + 0.5 * fCanfrancLikeDetector.CuFrameHoleL;
    fCanfrancLikeDetector.CuHolePos.push_back( G4ThreeVector( +tmpD, +tmpD, 0 ) );
    fCanfrancLikeDetector.CuHolePos.push_back( G4ThreeVector( -tmpD, +tmpD, 0 ) );
    fCanfrancLikeDetector.CuHolePos.push_back( G4ThreeVector( -tmpD, -tmpD, 0 ) );
    fCanfrancLikeDetector.CuHolePos.push_back( G4ThreeVector( +tmpD, -tmpD, 0 ) );

    // Column position
    tmpD = 0.5 * fCanfrancLikeDetector.CuColumnDistance;
    G4double columnZ = 0.5 * fCanfrancLikeDetector.CuFrameH
        - 0.5 * fCanfrancLikeDetector.CuColumnH
        + fCanfrancLikeDetector.CuColumnOffset;
    fCanfrancLikeDetector.CuColumnPos.push_back( G4ThreeVector( 0,     0,     columnZ ) );
    fCanfrancLikeDetector.CuColumnPos.push_back( G4ThreeVector( +tmpD, +tmpD, columnZ ) );
    fCanfrancLikeDetector.CuColumnPos.push_back( G4ThreeVector( -tmpD, +tmpD, columnZ ) );
    fCanfrancLikeDetector.CuColumnPos.push_back( G4ThreeVector( -tmpD, -tmpD, columnZ ) );
    fCanfrancLikeDetector.CuColumnPos.push_back( G4ThreeVector( +tmpD, -tmpD, columnZ ) );

    // Frame position
    G4double dh = fCanfrancLikeDetector.CuFrameShortGap + fCanfrancLikeDetector.CuFrameH;
    G4double DH = fCanfrancLikeDetector.CuFrameShortGap
        + fCanfrancLikeDetector.CuFrameLongGap
        + 2. * fCanfrancLikeDetector.CuFrameH;
    fCanfrancLikeDetector.CuMainFramePos.push_back( G4ThreeVector( 0, 0, -dh ) );
    for( G4int f=1; f<=fCanfrancLikeDetector.NFloors; f++ )
    {
        double z = -DH * f;
        fCanfrancLikeDetector.CuMainFramePos.push_back( G4ThreeVector( 0, 0, z ) );
        z = -DH * f - dh;
        fCanfrancLikeDetector.CuMainFramePos.push_back( G4ThreeVector( 0, 0, z ) );
    }

    // Physical volume frame positions
    tmpShiftZ = 10. * mm;
    fCanfrancLikeDetector.CuFrameZ = fDetTopCuPlate.Z
        - 0.5 * fDetTopCuPlate.H
        - tmpShiftZ
        - 0.5 * fCanfrancLikeDetector.CuFrameH;

    fCanfrancLikeDetector.CuFramePos         = G4ThreeVector( 0, 0, fCanfrancLikeDetector.CuFrameZ );
    fCanfrancLikeDetector.CuFrameSourcePos   = G4ThreeVector( 0, 0, fCanfrancLikeDetector.CuFrameZ ) + fVacuum.Pos;

    // PTFE parts
    fCanfrancLikeDetector.LateralPTFEX           = 9.   * mm;
    fCanfrancLikeDetector.LateralPTFEY           = 5.   * mm;
    fCanfrancLikeDetector.LateralPTFEH           = 4.   * mm;
    fCanfrancLikeDetector.LateralPTFETopHoleX    = 2.85 * mm;
    fCanfrancLikeDetector.LateralPTFETopHoleH    = 2.5  * mm;
    fCanfrancLikeDetector.LateralPTFEBottomHoleX = fCanfrancLikeDetector.CuFrameLateralT;
    fCanfrancLikeDetector.LateralPTFEBottomHoleH = 2.   * mm;

    fCanfrancLikeDetector.CentralPTFEX           = 15.   * mm;
    fCanfrancLikeDetector.CentralPTFEY           = 5.   * mm;
    fCanfrancLikeDetector.CentralPTFEH           = 4.   * mm;
    fCanfrancLikeDetector.CentralPTFETopHoleX    = 2.85 * mm;
    fCanfrancLikeDetector.CentralPTFETopHoleH    = 2.5  * mm;
    fCanfrancLikeDetector.CentralPTFEBottomHoleX = fCanfrancLikeDetector.CuFrameCentralT;
    fCanfrancLikeDetector.CentralPTFEBottomHoleH = 2.   * mm;

    fCanfrancLikeDetector.LateralLDPTFEX = 8.  * mm;
    fCanfrancLikeDetector.LateralLDPTFEY = 9.  * mm;
    fCanfrancLikeDetector.LateralLDPTFEH = 4.  * mm;
    fCanfrancLikeDetector.CentralLDPTFEX = 8.  * mm;
    fCanfrancLikeDetector.CentralLDPTFEY = 15. * mm;
    fCanfrancLikeDetector.CentralLDPTFEH = 4.  * mm;
    fCanfrancLikeDetector.LDPTFEHoleX    = 4.  * mm;
    fCanfrancLikeDetector.LDPTFEHoleY    = 6.4 * mm;
    fCanfrancLikeDetector.LDPTFEHoleH    = 5.  * mm;
    fCanfrancLikeDetector.LDPTFESlitX    = 9.  * mm;
    fCanfrancLikeDetector.LDPTFESlitY    = 9.  * mm;
    fCanfrancLikeDetector.LDPTFESlitH    = 0.3 * mm;

    tmpD = 0.5 * fCanfrancLikeDetector.CuFrameCentralT
        + 0.5 * fCanfrancLikeDetector.CuFrameHoleL;
    tmpD2 = 0.5 * fCanfrancLikeDetector.CuFrameX
        - 0.5 * fCanfrancLikeDetector.LateralPTFEX;

    // Central frames
    for( G4int f=0; f<=fCanfrancLikeDetector.NFloors; f++ )
        for( G4double sign=-1.; sign<=1.; sign+=2. )
        {

            // Light detector PTFE holders
            double z = - DH * f
                + fCanfrancLikeDetector.CuFrameH
                + 0.5 * fCanfrancLikeDetector.CentralLDPTFEH;

            G4RotationMatrix rot  = G4RotationMatrix();
            G4ThreeVector pos = G4ThreeVector( sign * tmpD, 0., z );
            fCanfrancLikeDetector.CentralLDPTFETrans.push_back( new G4Transform3D( rot, pos ) );

            rot  = G4RotationMatrix();
            rot.rotateZ( 90.  * deg );
            pos = G4ThreeVector( 0., sign * tmpD, z );
            fCanfrancLikeDetector.CentralLDPTFETrans.push_back( new G4Transform3D( rot, pos ) );

            if( f == fCanfrancLikeDetector.NFloors )
                continue;

            // PTFE frames on top of crystals
            z = - DH * f;

            rot  = G4RotationMatrix();
            rot.rotateZ( 90.  * deg );
            rot.rotateX( 180. * deg );
            pos = G4ThreeVector( sign * tmpD, 0., z );
            fCanfrancLikeDetector.CentralPTFETrans.push_back( new G4Transform3D( rot, pos ) );

            rot = G4RotationMatrix();
            rot.rotateX( 180. * deg );
            pos = G4ThreeVector( 0., sign * tmpD, z );
            fCanfrancLikeDetector.CentralPTFETrans.push_back( new G4Transform3D( rot, pos ) );

            // PTFE frames on bottom of crystals
            z = - DH * f - fCanfrancLikeDetector.CuFrameLongGap;

            rot  = G4RotationMatrix();
            rot.rotateZ( 90.  * deg );
            pos = G4ThreeVector( sign * tmpD, 0., z );
            fCanfrancLikeDetector.CentralPTFETrans.push_back( new G4Transform3D( rot, pos ) );

            rot = G4RotationMatrix();
            pos = G4ThreeVector( 0., sign * tmpD, z );
            fCanfrancLikeDetector.CentralPTFETrans.push_back( new G4Transform3D( rot, pos ) );

        }

    // Lateral frames
    for( G4int f=0; f<=fCanfrancLikeDetector.NFloors; f++ )
        for( G4double signX=-1.; signX<=1.; signX+=2. )
            for( G4double signY=-1.; signY<=1.; signY+=2. )
            {	
                // Light detector PTFE holders
                double z = - DH * f
                    + fCanfrancLikeDetector.CuFrameH
                    + 0.5 * fCanfrancLikeDetector.CentralLDPTFEH;

                G4RotationMatrix rot  = G4RotationMatrix();
                if( signY == +1. )
                    rot.rotateZ( 180.  * deg );
                G4ThreeVector pos = G4ThreeVector( signX * tmpD, signY * tmpD2 , z );
                fCanfrancLikeDetector.LateralLDPTFETrans.push_back( new G4Transform3D( rot, pos ) );

                rot  = G4RotationMatrix();
                if( signX == +1. )
                    rot.rotateZ( +90.  * deg );
                else
                    rot.rotateZ( -90.  * deg );
                pos = G4ThreeVector( signX * tmpD2, signY * tmpD , z );
                fCanfrancLikeDetector.LateralLDPTFETrans.push_back( new G4Transform3D( rot, pos ) );

                if( f == fCanfrancLikeDetector.NFloors )
                    continue;

                // PTFE frames on top of crystals
                z = - DH * f;
                rot  = G4RotationMatrix();
                if( signY == +1. )
                    rot.rotateZ( 90.  * deg );
                else
                    rot.rotateZ( -90.  * deg );
                rot.rotateX( 180. * deg );
                pos = G4ThreeVector( signX * tmpD, signY * tmpD2 , z );
                fCanfrancLikeDetector.LateralPTFETrans.push_back( new G4Transform3D( rot, pos ) );

                rot  = G4RotationMatrix();
                if( signX == +1. )
                    rot.rotateZ( 180.  * deg );
                rot.rotateX( 180. * deg );
                pos = G4ThreeVector( signX * tmpD2, signY * tmpD , z );
                fCanfrancLikeDetector.LateralPTFETrans.push_back( new G4Transform3D( rot, pos ) );

                // PTFE frames on bottom of crystals
                z = - DH * f - fCanfrancLikeDetector.CuFrameLongGap;

                rot  = G4RotationMatrix();
                if( signY == -1. )
                    rot.rotateZ( 90.  * deg );
                else
                    rot.rotateZ( -90.  * deg );
                pos = G4ThreeVector( signX * tmpD, signY * tmpD2 , z );
                fCanfrancLikeDetector.LateralPTFETrans.push_back( new G4Transform3D( rot, pos ) );

                rot  = G4RotationMatrix();
                if( signX == +1. )
                    rot.rotateZ( 180.  * deg );
                pos = G4ThreeVector( signX * tmpD2, signY * tmpD , z );
                fCanfrancLikeDetector.LateralPTFETrans.push_back( new G4Transform3D( rot, pos ) );

            }

    fCanfrancLikeDetector.PTFEFrameZ = fCanfrancLikeDetector.CuFrameZ
        - fCanfrancLikeDetector.CuFrameShortGap
        - 1.5 * fCanfrancLikeDetector.CuFrameH;
    fCanfrancLikeDetector.PTFEFramePos       = G4ThreeVector( 0, 0, fCanfrancLikeDetector.PTFEFrameZ );
    fCanfrancLikeDetector.PTFEFrameSourcePos = G4ThreeVector( 0, 0, fCanfrancLikeDetector.PTFEFrameZ ) + fVacuum.Pos;


    // Crystal and LD position
    tmpD = 0.5 * fCanfrancLikeDetector.CuFrameCentralT
        + 0.5 * fCanfrancLikeDetector.CuFrameHoleL;

    for( G4int f=0; f<=fCanfrancLikeDetector.NFloors; f++ )
        for( G4double signX=-1.; signX<=1.; signX+=2. )
            for( G4double signY=-1.; signY<=1.; signY+=2. )
            {

                G4double x = signX * tmpD;
                G4double y = signY * tmpD;

                double z = - DH * f
                    + fCanfrancLikeDetector.CuFrameH
                    + 0.5 * fCanfrancLikeDetector.CentralLDPTFEH;
                fCanfrancLikeDetector.LightDetSolidPos.push_back( G4ThreeVector( x, y, z ) );

                if( f == fCanfrancLikeDetector.NFloors )
                    continue;

                z = - DH * f
                    - 0.5 * fCanfrancLikeDetector.CuFrameLongGap;
                fCanfrancLikeDetector.CrystalSolidPos.push_back( G4ThreeVector( x, y, z ) );

            }

    fCanfrancLikeDetector.CrystalZ = fCanfrancLikeDetector.PTFEFrameZ;
    fCanfrancLikeDetector.CrystalPos       = G4ThreeVector( 0, 0, fCanfrancLikeDetector.CrystalZ );
    fCanfrancLikeDetector.CrystalSourcePos = G4ThreeVector( 0, 0, fCanfrancLikeDetector.CrystalZ ) + fVacuum.Pos;

    fCanfrancLikeDetector.LightDetZ = fCanfrancLikeDetector.PTFEFrameZ;
    fCanfrancLikeDetector.LightDetPos       = G4ThreeVector( 0, 0, fCanfrancLikeDetector.LightDetZ );
    fCanfrancLikeDetector.LightDetSourcePos = G4ThreeVector( 0, 0, fCanfrancLikeDetector.LightDetZ ) + fVacuum.Pos;

    fCanfrancLikeDetector.ClearanceX = 15.  * mm;
    fCanfrancLikeDetector.ClearanceY = 15.  * mm;

    // Tower positions
    for( G4int row=-3; row<=3; row++ )
        for( G4int col=0; col<2; col++ )
        {
            G4double tmpX = ( fCanfrancLikeDetector.CuFrameX + fCanfrancLikeDetector.ClearanceX ) * row;
            G4double tmpY = ( fCanfrancLikeDetector.CuFrameY + fCanfrancLikeDetector.ClearanceY ) * ( -0.5 + col );
            fCanfrancLikeDetector.TowerPos.push_back( G4ThreeVector( tmpX, tmpY, 0 ) );
        }

    for( G4int row=0; row<6; row++ )
        for( G4int col=0; col<2; col++ )
        {
            G4double tmpX = ( fCanfrancLikeDetector.CuFrameX + fCanfrancLikeDetector.ClearanceX ) * ( -2.5 + row );
            G4double tmpY = ( fCanfrancLikeDetector.CuFrameY + fCanfrancLikeDetector.ClearanceY ) * ( -1.5 + col * 3 );
            fCanfrancLikeDetector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
        }
    for( G4int row=0; row<4; row++ )
        for( G4int col=0; col<2; col++ )
        {
            G4double tmpX = ( fCanfrancLikeDetector.CuFrameX + fCanfrancLikeDetector.ClearanceX ) * ( -1.5 + row );
            G4double tmpY = ( fCanfrancLikeDetector.CuFrameY + fCanfrancLikeDetector.ClearanceY ) * ( -2.5 + col * 5 );
            fCanfrancLikeDetector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
        }

    fCanfrancLikeDetector.NTowers = fCanfrancLikeDetector.TowerPos.size();












    // -------------------------------------------------------------------
    // Cuore-like detector tower with 2 crystals per floor (Gio, 06.04.20)
    // Horizontal light detector
    // -------------------------------------------------------------------

    fCuore1x2Detector.NFloors          = 13;
    fCuore1x2Detector.CrystalL         = 45.  * mm;
    fCuore1x2Detector.LightDetL        = 45.  * mm;
    fCuore1x2Detector.LightDetT        = 0.5  * mm;
    fCuore1x2Detector.CuFrameX         = 112. * mm;
    fCuore1x2Detector.CuFrameY         = 58.  * mm;
    fCuore1x2Detector.CuFrameH         = 12.  * mm;
    fCuore1x2Detector.CuTopFrameH      = 9.  * mm;
    fCuore1x2Detector.CuBottomFrameH   = 9.  * mm;
    fCuore1x2Detector.CuFrameDT        = 4.   * mm;// Lateral thickness
    fCuore1x2Detector.CuFrameHoleL     = 0.5 * ( fCuore1x2Detector.CuFrameX - 3. * fCuore1x2Detector.CuFrameDT );
    fCuore1x2Detector.CuFrameHoleL2    = 33.7 * mm;// 2 of the central frame beams are cut by this amount
    fCuore1x2Detector.CuFrameThinningL = 33.2 * mm;
    fCuore1x2Detector.CuFrameThinningH = 3.   * mm;

    tmpD = 0.5 * fCuore1x2Detector.CuFrameDT// X-Y Position of frame hole
        + 0.5 * fCuore1x2Detector.CuFrameHoleL;

    // Holes for detectors
    fCuore1x2Detector.CuHolePos.push_back( G4ThreeVector( +tmpD, 0, 0 ) );
    fCuore1x2Detector.CuHolePos.push_back( G4ThreeVector( -tmpD, 0, 0 ) );

    // Holes in central frame beams
    fCuore1x2Detector.CuHolePos2.push_back( G4ThreeVector( 0, 0, 0 ) );

    // Frame thinnings
    tmpD2 = 0.5 * fCuore1x2Detector.CuFrameX
        - 0.5 * fCuore1x2Detector.CuFrameDT;
    tmpH = 0.5 * fCuore1x2Detector.CuFrameH;

    for( double sign=-1.; sign<=1.; sign+=2. )
    {
        fCuore1x2Detector.CuFrameThinningPos.push_back( G4ThreeVector( +tmpD,  +tmpD, sign * tmpH ) );
        fCuore1x2Detector.CuFrameThinningPos.push_back( G4ThreeVector( +tmpD,  -tmpD, sign * tmpH ) );
        fCuore1x2Detector.CuFrameThinningPos.push_back( G4ThreeVector( -tmpD,  +tmpD, sign * tmpH ) );
        fCuore1x2Detector.CuFrameThinningPos.push_back( G4ThreeVector( -tmpD,  -tmpD, sign * tmpH ) );
        fCuore1x2Detector.CuFrameThinningPos.push_back( G4ThreeVector( +tmpD2, 0,     sign * tmpH ) );
        fCuore1x2Detector.CuFrameThinningPos.push_back( G4ThreeVector( -tmpD2, 0,     sign * tmpH ) );
        // Thinnings along x
        for( int i=0; i<4; i++ )
            fCuore1x2Detector.CuFrameThinningRot.push_back( new G4RotationMatrix() );
        // Thinnings along y
        for( int i=0; i<2; i++ )
        {
            fCuore1x2Detector.CuFrameThinningRot.push_back( new G4RotationMatrix() );
            fCuore1x2Detector.CuFrameThinningRot.back()->rotateZ( 90. * deg );
        }
    }

    tmpH = -0.5 * fCuore1x2Detector.CuTopFrameH;
    fCuore1x2Detector.CuTopFrameThinningPos.push_back( G4ThreeVector( +tmpD,  +tmpD, tmpH ) );
    fCuore1x2Detector.CuTopFrameThinningPos.push_back( G4ThreeVector( +tmpD,  -tmpD, tmpH ) );
    fCuore1x2Detector.CuTopFrameThinningPos.push_back( G4ThreeVector( -tmpD,  +tmpD, tmpH ) );
    fCuore1x2Detector.CuTopFrameThinningPos.push_back( G4ThreeVector( -tmpD,  -tmpD, tmpH ) );
    fCuore1x2Detector.CuTopFrameThinningPos.push_back( G4ThreeVector( +tmpD2, 0,     tmpH ) );
    fCuore1x2Detector.CuTopFrameThinningPos.push_back( G4ThreeVector( -tmpD2, 0,     tmpH ) );

    tmpH = +0.5 * fCuore1x2Detector.CuBottomFrameH;
    fCuore1x2Detector.CuBottomFrameThinningPos.push_back( G4ThreeVector( +tmpD,  +tmpD, tmpH ) );
    fCuore1x2Detector.CuBottomFrameThinningPos.push_back( G4ThreeVector( +tmpD,  -tmpD, tmpH ) );
    fCuore1x2Detector.CuBottomFrameThinningPos.push_back( G4ThreeVector( -tmpD,  +tmpD, tmpH ) );
    fCuore1x2Detector.CuBottomFrameThinningPos.push_back( G4ThreeVector( -tmpD,  -tmpD, tmpH ) );
    fCuore1x2Detector.CuBottomFrameThinningPos.push_back( G4ThreeVector( +tmpD2, 0,     tmpH ) );
    fCuore1x2Detector.CuBottomFrameThinningPos.push_back( G4ThreeVector( -tmpD2, 0,     tmpH ) );

    // Copper columns
    fCuore1x2Detector.CuColumnR = 0.5 * fCuore1x2Detector.CuFrameDT;
    fCuore1x2Detector.CuColumnH = 41. * mm;
    tmpD = 0.5 * fCuore1x2Detector.CuFrameY - fCuore1x2Detector.CuColumnR;
    fCuore1x2Detector.CuColumnPos.push_back( G4ThreeVector( -tmpD2, -tmpD, 0. ) );
    fCuore1x2Detector.CuColumnPos.push_back( G4ThreeVector( -tmpD2, +tmpD, 0. ) );
    fCuore1x2Detector.CuColumnPos.push_back( G4ThreeVector( +tmpD2, -tmpD, 0. ) );
    fCuore1x2Detector.CuColumnPos.push_back( G4ThreeVector( +tmpD2, +tmpD, 0. ) );

    fCuore1x2Detector.TowerH = fCuore1x2Detector.CuTopFrameH
        + fCuore1x2Detector.CuBottomFrameH
        + fCuore1x2Detector.CuFrameH * ( fCuore1x2Detector.NFloors - 1 )
        + fCuore1x2Detector.CuColumnH * fCuore1x2Detector.NFloors;

    // PTFE dimensions (see drawing in Agatacuore1x2Detector.cc)
    fCuore1x2Detector.t1x = 6.  * mm;
    fCuore1x2Detector.t1y = 20. * mm;
    fCuore1x2Detector.t1z = 7.  * mm;
    fCuore1x2Detector.t2x = 8. * sqrt(2.) * mm;
    fCuore1x2Detector.t2y = 8. * sqrt(2.) * mm;
    fCuore1x2Detector.t2z = 8.  * mm;
    fCuore1x2Detector.t2t = 10. * mm;

    fCuore1x2Detector.b1x = 20. * mm;
    fCuore1x2Detector.b1y = 20. * mm;
    fCuore1x2Detector.b1z = 5.  * mm;
    fCuore1x2Detector.b2x = 10. * sqrt(2.) * mm;
    fCuore1x2Detector.b2y = 10. * sqrt(2.) * mm;
    fCuore1x2Detector.b2z = 12. * mm;
    fCuore1x2Detector.b1t = 10. * mm;
    fCuore1x2Detector.b2t = -3. * mm;

    fCuore1x2Detector.b3x = 18.  * mm;
    fCuore1x2Detector.b3y = 18.  * mm;
    fCuore1x2Detector.b3z = 10.  * mm;
    fCuore1x2Detector.b3t = -10. * mm;

    // Clearance between towers
    fCuore1x2Detector.ClearanceX     = 10.  * mm;
    fCuore1x2Detector.ClearanceY     = 30.  * mm;

    fCuore1x2Detector.CuBandX        = 12.  * mm;
    fCuore1x2Detector.CuBandY        = 2.   * mm;
    fCuore1x2Detector.CuBandH        = 730. * mm;

    // Physical volume positions
    tmpShiftZ = 10. * mm;
    fCuore1x2Detector.CuFrameZ = fDetTopCuPlate.Z
        - 0.5 * fDetTopCuPlate.H
        - 0.5 * tmpShiftZ
        - 0.5 * fCuore1x2Detector.CuTopFrameH;

    fCuore1x2Detector.CuFramePos         = G4ThreeVector( 0, 0, fCuore1x2Detector.CuFrameZ );
    fCuore1x2Detector.CuFrameSourcePos   = G4ThreeVector( 0, 0, fCuore1x2Detector.CuFrameZ ) + fVacuum.Pos;

    for( G4int i=0; i<=fCuore1x2Detector.NFloors; i++ )
    {
        for( G4int mainSign=-1; mainSign<=1; mainSign+=2 )
        {

            G4double x = mainSign * 0.5 * ( fCuore1x2Detector.CuFrameDT + fCuore1x2Detector.CuFrameHoleL );
            G4double y = 0.;//mainSign * 0.5 * ( fCuore1x2Detector.CuFrameDT + fCuore1x2Detector.CuFrameHoleL );

            // Light detector positions
            G4double z = fCuore1x2Detector.CuFrameZ
                - 0.5 * fCuore1x2Detector.CuTopFrameH
                - fCuore1x2Detector.CuColumnH * i
                - fCuore1x2Detector.CuFrameH * i
                + fCuore1x2Detector.b1z
                + 0.5 * fCuore1x2Detector.LightDetT;
            fCuore1x2Detector.LightDetSolidPos.push_back( G4ThreeVector( x, y, z ) );

            if( i == fCuore1x2Detector.NFloors )
                continue;

            // Crystal positions
            z = fCuore1x2Detector.CuFrameZ
                - 0.5 * fCuore1x2Detector.CuTopFrameH
                - ( 0.5 + i ) * fCuore1x2Detector.CuColumnH
                - fCuore1x2Detector.CuFrameH * i;
            fCuore1x2Detector.CrystalSolidPos.push_back( G4ThreeVector( x, y, z ) );


            // PTFE holders
            for( G4double angle=45.; angle<360.; angle+=90. )
            {
                G4double signX = 1.;
                G4double signY = 1.;
                if( angle > 90. && angle <= 270. ) signY = -1.;
                if( angle > 180. ) signX = -1.;

                G4double shift = 0.5 * fCuore1x2Detector.CuFrameHoleL;
                G4double thisX = x + signX * shift;
                G4double thisY = y + signY * shift;

                // PTFE holders on top of the crystals
                z = fCuore1x2Detector.CuFrameZ
                    - 0.5 * fCuore1x2Detector.CuTopFrameH
                    - fCuore1x2Detector.CuColumnH * i
                    - fCuore1x2Detector.CuFrameH * i
                    - 0.5 * fCuore1x2Detector.t1z
                    + fCuore1x2Detector.b1z;

                fCuore1x2Detector.PTFEPos.push_back( G4ThreeVector( thisX, thisY, z ) );
                fCuore1x2Detector.PTFERot.push_back( new G4RotationMatrix() );
                fCuore1x2Detector.PTFERot.back()->rotateZ( angle * deg );
                fCuore1x2Detector.PTFERot.back()->rotateX( 180. * deg );

                // PTFE holders on bottom of the crystals
                z = fCuore1x2Detector.CuFrameZ
                    - 0.5 * fCuore1x2Detector.CuTopFrameH
                    - fCuore1x2Detector.CuColumnH * ( i + 1 )
                    - fCuore1x2Detector.CuFrameH * i
                    + 0.5 * fCuore1x2Detector.t1z
                    - fCuore1x2Detector.b1z;

                fCuore1x2Detector.PTFEPos.push_back( G4ThreeVector( thisX, thisY, z ) );
                fCuore1x2Detector.PTFERot.push_back( new G4RotationMatrix() );
                fCuore1x2Detector.PTFERot.back()->rotateZ( ( 180. + angle ) * deg );

            }
        }

    }

    fCuore1x2Detector.CrystalPos         = G4ThreeVector();// Crystal pos assigned via CrystalSolidPos
    fCuore1x2Detector.CrystalSourcePos   = G4ThreeVector() + fVacuum.Pos;
    fCuore1x2Detector.LightDetPos         = G4ThreeVector();// LightDet pos assigned via LightDetSolidPos
    fCuore1x2Detector.LightDetSourcePos   = G4ThreeVector() + fVacuum.Pos;
    fCuore1x2Detector.PTFEFramePos         = G4ThreeVector();// PTFEFrame pos assigned via PTFEPos
    fCuore1x2Detector.PTFEFrameSourcePos   = G4ThreeVector() + fVacuum.Pos;

    //fCuore1x2Detector.TowerPos.push_back( G4ThreeVector( 0, 0, 0 ) );

    // Tower positions
    for( G4int row=-3; row<=3; row++ )
        for( G4int col=-1; col<=1; col++ )
        {
            G4double tmpX = ( fCuore1x2Detector.CuFrameX + fCuore1x2Detector.ClearanceX ) * row;
            G4double tmpY = ( fCuore1x2Detector.CuFrameY + fCuore1x2Detector.ClearanceY ) * col;
            fCuore1x2Detector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
        }
    for( G4int row=0; row<6; row++ )
        for( G4int col=2; col<=2; col++ )
        {
            G4double tmpX = ( fCuore1x2Detector.CuFrameX + fCuore1x2Detector.ClearanceX ) * ( -2.5 + row );
            G4double tmpY = ( fCuore1x2Detector.CuFrameY + fCuore1x2Detector.ClearanceY ) * col;
            fCuore1x2Detector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
        }
    for( G4int row=-2; row<=2; row++ )
        for( G4int col=-3; col<=3; col++ )
        {
            if( col >= -1 && col <= 2 )
                continue;

            G4double tmpX = ( fCuore1x2Detector.CuFrameX + fCuore1x2Detector.ClearanceX ) * row;
            G4double tmpY = ( fCuore1x2Detector.CuFrameY + fCuore1x2Detector.ClearanceY ) * col;
            fCuore1x2Detector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
        }

    for( G4int row=-1; row<=1; row++ )
        for( G4int col=-4; col<=4; col+=8 )
        {
            G4double tmpX = ( fCuore1x2Detector.CuFrameX + fCuore1x2Detector.ClearanceX ) * row;
            G4double tmpY = ( fCuore1x2Detector.CuFrameY + fCuore1x2Detector.ClearanceY ) * col;
            fCuore1x2Detector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
        }

    /*
       for( G4int row=0; row<6; row++ )
       for( G4int col=-3; col<=3; col++ )
       {
       G4double tmpX = ( fCuore1x2Detector.CuFrameX + fCuore1x2Detector.ClearanceX ) * ( -2.5 + row );
       G4double tmpY = ( fCuore1x2Detector.CuFrameY + fCuore1x2Detector.ClearanceY ) * col;
       fCuore1x2Detector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
       }

       for( G4int row=-2; row<=2; row++ )
       for( G4int sign=-1; sign<=1; sign+=2 )
       for( G4int col=4; col<=4; col++ )
       {
       G4double tmpX = ( fCuore1x2Detector.CuFrameX + fCuore1x2Detector.ClearanceX ) * row;
       G4double tmpY = ( fCuore1x2Detector.CuFrameY + fCuore1x2Detector.ClearanceY ) * sign * col;
       fCuore1x2Detector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
       }
       for( G4int row=0; row<=2; row++ )
       for( G4int sign=-1; sign<=1; sign+=2 )
       for( G4int col=5; col<=5; col++ )
       {
       G4double tmpX = ( fCuore1x2Detector.CuFrameX + fCuore1x2Detector.ClearanceX ) * ( -0.5 + row );
       G4double tmpY = ( fCuore1x2Detector.CuFrameY + fCuore1x2Detector.ClearanceY ) * sign * col;
       fCuore1x2Detector.TowerPos.push_back( G4ThreeVector( tmpX, +tmpY, 0 ) );
       }
       */
    fCuore1x2Detector.NTowers = fCuore1x2Detector.TowerPos.size();

    /*
     *  ======================================================================
     *      CUORE detector
     *  ======================================================================
     */ 

    // -- DCS tubes
    fCuoreDetector.DCSTubeR = 4.0 * mm;
    fCuoreDetector.DCSTubeT = 1.0 * mm;
    // Height: distance between top and bottom plate
    fCuoreDetector.DCSTubeH = fDetTopCuPlate.Z - fDetBottomCuPlate.Z - 0.5*fDetTopCuPlate.H - 0.5*fDetBottomCuPlate.H;
    // Z : mid point between top and bottom plate
    fCuoreDetector.DCSTubeZ = 0.5 * (fDetTopCuPlate.Z + fDetBottomCuPlate.Z);

    // -- Frames
    fCuoreDetector.FrameL = 12.2 * cm;
    fCuoreDetector.FrameH = 1.2 * cm;
    fCuoreDetector.EdgeFrameH = 0.9 * cm;
    fCuoreDetector.FrameW = 0.4 * cm;

    // Crystal holes
    fCuoreDetector.FrameHoleL = 0.5 * (fCuoreDetector.FrameL - 3 * fCuoreDetector.FrameW);
    fCuoreDetector.FrameHoleC = 0.5 * (fCuoreDetector.FrameW + fCuoreDetector.FrameHoleL);

    // Notches on sides of the frame
    fCuoreDetector.FrameNotchL = 3.82 * cm;
    fCuoreDetector.FrameNotchH = 0.3 * cm;
    fCuoreDetector.FrameCentralNotchL = 3.87 * cm;

    // -- Columns
    fCuoreDetector.PlaneH = 5.8 * cm;   // Distance between the base of a frame and the base of the next frame
    fCuoreDetector.ColumnR = 0.15 * cm;
    fCuoreDetector.ColumnH = fCuoreDetector.PlaneH - fCuoreDetector.FrameH;

    // -- Wire trays
    fCuoreDetector.NFloors = 13;
    fCuoreDetector.TowerH = 
        fCuoreDetector.PlaneH * fCuoreDetector.NFloors 
        + fCuoreDetector.EdgeFrameH;
    fCuoreDetector.WireTrayW = 1 * mm;
    fCuoreDetector.WireTrayL = 2.0 * cm;

    fCuoreDetector.WireTrayVL = 4. * mm;
    fCuoreDetector.WireTrayVW = 1. * mm;
    fCuoreDetector.WireTrayVH = 6. * mm;
    fCuoreDetector.WireTrayArmW = 1. * mm;
    fCuoreDetector.WireTrayArmL = 16. * mm;
    fCuoreDetector.WireTrayArmH = 6. * mm;

    // -- PEN tape
    fCuoreDetector.PENTapeW = 0.8 * mm;
    fCuoreDetector.PENTapeL = 16. * mm;

    fCuoreDetector.PENTapeArmL = 9. * mm;
    fCuoreDetector.PENTapeArmH = 6. * mm;

    fCuoreDetector.PENTapeOffset = -6 * mm;

    // -- Wire pad
    fCuoreDetector.WirePadW = 0.1 * mm;
    fCuoreDetector.WirePadL = 11. * mm;
    fCuoreDetector.WirePadH = 5. * mm;

    // -- NTD
    fCuoreDetector.NTDW = 1. * mm;
    fCuoreDetector.NTDL = 2.9 * mm;
    fCuoreDetector.NTDH = 3. * mm;
    fCuoreDetector.NTDOffset = 1.5 * cm;

    // -- PTFE
    fCuoreDetector.PTFEW = 0.6 * cm;
    fCuoreDetector.PTFEL = 1.6 * cm;
    fCuoreDetector.PTFEH = 0.65 * cm;

    fCuoreDetector.PTFEFrameDist = 0.17 * cm;

    fCuoreDetector.PTFENotchW = 2.0 * cm;
    fCuoreDetector.PTFENotchL = 2.0 * cm;
    fCuoreDetector.PTFENotchH = 1.0 * cm;
    fCuoreDetector.PTFENotchYOffset = sqrt(2) * cm;
    fCuoreDetector.PTFENotchZOffset = 0.45 * cm;

    fCuoreDetector.PTFEBlock1W = 2.0 * cm;
    fCuoreDetector.PTFEBlock1L = 2.0 * cm;
    fCuoreDetector.PTFEBlock1H = 1.0 * cm;
    fCuoreDetector.PTFEBlock2W = 1.5 * cm;
    fCuoreDetector.PTFEBlock2L = 1.5 * cm;
    fCuoreDetector.PTFEBlock2H = 1.2 * cm;
    fCuoreDetector.PTFEBlockOffset = 1.06 * cm;

    fCuoreDetector.PTFESub1YOffset = -0.2 * cm;
    fCuoreDetector.PTFESub1ZOffset = -0.3 * cm;
    fCuoreDetector.PTFESub2YOffset = -0.5 * cm;
    fCuoreDetector.PTFESub3YOffset = -1.1 * cm;

    // -- Crystals
    fCuoreDetector.NCrystalsPerFloor = 4;
    fCuoreDetector.CrystalL = 5. * cm;

    /*
     * Position
     */
    fCuoreDetector.NTowers = 19;

    // DCS tubes - Internal
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( 147., 80., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( 147., -80., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( -147., 80., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( -147., -80., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( 0., 214., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( 0., -214., fCuoreDetector.DCSTubeZ) );

    // DCS tubes - External
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( 458.99, 265., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( 458.99, -265., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( -458.99, 265., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( -458.99, -265., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( 0., 530., fCuoreDetector.DCSTubeZ) );
    fCuoreDetector.DCSTubePos.push_back( G4ThreeVector( 0., -530., fCuoreDetector.DCSTubeZ) );

    for(unsigned int i = 0; i < fCuoreDetector.DCSTubePos.size(); i++)
    {
        fCuoreDetector.DCSTubeSourcePos.push_back( 
                fCuoreDetector.DCSTubePos.at(i) + fVacuum.Pos );
    }

    // Frame position
    for( G4int f = 0; f <= fCuoreDetector.NFloors; f++)
    {
        double z = f * fCuoreDetector.PlaneH + 0.5 * fCuoreDetector.EdgeFrameH - 0.5 * fCuoreDetector.TowerH;
        double angle = ((f+1)%2) * 90. * deg;

        // Alternate orientation of frames on the XY plane
        fCuoreDetector.FrameZ.push_back( G4ThreeVector(0, 0, z) );
        G4RotationMatrix rotation = G4RotationMatrix();
        rotation.rotateZ(angle);

        // Bottom frame: upside down
        if( f == 0 )
            rotation.rotateX(180. * deg);

        fCuoreDetector.FrameTrans.push_back( new G4Transform3D(
                    rotation, fCuoreDetector.FrameZ.back()));
    }

    // Column position
    for( G4int f = 0; f < fCuoreDetector.NFloors; f++)
    {
        double z = 0.5 * fCuoreDetector.PlaneH;
        double p = fCuoreDetector.FrameL - fCuoreDetector.FrameW;

        fCuoreDetector.ColumnTrans.push_back( 
                new G4Transform3D(
                    G4RotationMatrix(),
                    fCuoreDetector.FrameZ.at(f) + G4ThreeVector( 0.5 * p, 0, z )));
        fCuoreDetector.ColumnTrans.push_back( 
                new G4Transform3D(
                    G4RotationMatrix(),
                    fCuoreDetector.FrameZ.at(f) + G4ThreeVector( 0, 0.5 * p, z )));
        fCuoreDetector.ColumnTrans.push_back( 
                new G4Transform3D(
                    G4RotationMatrix(),
                    fCuoreDetector.FrameZ.at(f) + G4ThreeVector( -0.5 * p, 0, z )));
        fCuoreDetector.ColumnTrans.push_back( 
                new G4Transform3D(
                    G4RotationMatrix(),
                    fCuoreDetector.FrameZ.at(f) + G4ThreeVector( 0, -0.5 * p, z )));
    }

    // Wire trays
    G4int centralFrame = fCuoreDetector.FrameZ.size() / 2;

    G4RotationMatrix wireTrayRot = G4RotationMatrix();
    G4ThreeVector wireTrayPos = fCuoreDetector.FrameZ.at(centralFrame) + 
        G4ThreeVector(
            0.5 * (fCuoreDetector.FrameL + fCuoreDetector.WireTrayW), 
            0.,
            - 0.5 * fCuoreDetector.PlaneH);

    fCuoreDetector.WireTrayTrans.push_back(
            new G4Transform3D( wireTrayRot, wireTrayPos ));

    wireTrayRot.rotateZ(180. * deg);
    wireTrayPos = fCuoreDetector.FrameZ.at(centralFrame) + 
        G4ThreeVector(
            -0.5 * (fCuoreDetector.FrameL + fCuoreDetector.WireTrayW), 
            0.,
            - 0.5 * fCuoreDetector.PlaneH);

    fCuoreDetector.WireTrayTrans.push_back(
            new G4Transform3D( wireTrayRot, wireTrayPos ));


    // Wire pads
    for( G4int f = 0; f < fCuoreDetector.NFloors; f++)
    {
        double x = 0.5 * (fCuoreDetector.FrameL + fCuoreDetector.WirePadW);
        double y = 1.2 * fCuoreDetector.NTDOffset;

        fCuoreDetector.WirePadTrans.push_back( 
                new G4Transform3D(
                    G4RotationMatrix(),
                    fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-x, -y, 0)));
        fCuoreDetector.WirePadTrans.push_back( 
                new G4Transform3D(
                    G4RotationMatrix(),
                    fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+x, -y, 0)));
        fCuoreDetector.WirePadTrans.push_back( 
                new G4Transform3D(
                    G4RotationMatrix(),
                    fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-x, +y, 0)));
        fCuoreDetector.WirePadTrans.push_back( 
                new G4Transform3D(
                    G4RotationMatrix(),
                    fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+x, +y, 0)));
    }

    // PEN tape
    G4RotationMatrix PENTapeRot = G4RotationMatrix();

    G4ThreeVector PENTapePos = 
        fCuoreDetector.FrameZ.at(centralFrame) + 
        G4ThreeVector(
                0.5 * (fCuoreDetector.FrameL + fCuoreDetector.PENTapeW) + fCuoreDetector.WireTrayW,
                0.,
                -0.5 * fCuoreDetector.PlaneH);
    fCuoreDetector.PENTapeTrans.push_back( new G4Transform3D( PENTapeRot, PENTapePos ));

    PENTapePos = 
        fCuoreDetector.FrameZ.at(centralFrame) + 
        G4ThreeVector(
                -0.5 * (fCuoreDetector.FrameL + fCuoreDetector.PENTapeW) - fCuoreDetector.WireTrayW,
                0.,
                -0.5 * fCuoreDetector.PlaneH);
    fCuoreDetector.PENTapeTrans.push_back( new G4Transform3D( PENTapeRot, PENTapePos ));

    // PTFE holders
    fCuoreDetector.PTFEX0 = 0.5 * fCuoreDetector.FrameW + fCuoreDetector.PTFEFrameDist;
    fCuoreDetector.PTFEX1 = 0.5 * fCuoreDetector.FrameL - fCuoreDetector.FrameW - fCuoreDetector.PTFEFrameDist;
    fCuoreDetector.PTFEZ = 0.4 * cm;

    for( G4int f = 0; f < fCuoreDetector.NFloors; f++ )
    {
        /*
         * Location of the 4 PTFE holders in the frame hole
         *  _________
         *  |D     C|
         *  |       |
         *  |       |
         *  |A     B|
         *  ---------
         *
         *  Rotations: 
         *      A = -45 deg
         *      B = +45 deg
         *      C = 135 deg
         *      D = -135 deg
         */

        G4ThreeVector position;
        G4RotationMatrix rotation;

        /*
         *  PTFE A
         */

        rotation = G4RotationMatrix();
        rotation.rotateZ(-45. * deg);

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-fCuoreDetector.PTFEX1, -fCuoreDetector.PTFEX1, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-fCuoreDetector.PTFEX1, +fCuoreDetector.PTFEX0, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+fCuoreDetector.PTFEX0, +fCuoreDetector.PTFEX0, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+fCuoreDetector.PTFEX0, -fCuoreDetector.PTFEX1, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        /*
         *  PTFE B
         */

        rotation = G4RotationMatrix();
        rotation.rotateZ(45. * deg);

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-fCuoreDetector.PTFEX0, -fCuoreDetector.PTFEX1, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-fCuoreDetector.PTFEX0, +fCuoreDetector.PTFEX0, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+fCuoreDetector.PTFEX1, +fCuoreDetector.PTFEX0, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+fCuoreDetector.PTFEX1, -fCuoreDetector.PTFEX1, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        /*
         *  PTFE C
         */

        rotation = G4RotationMatrix();
        rotation.rotateZ(135. * deg);

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-fCuoreDetector.PTFEX0, -fCuoreDetector.PTFEX0, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-fCuoreDetector.PTFEX0, +fCuoreDetector.PTFEX1, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+fCuoreDetector.PTFEX1, +fCuoreDetector.PTFEX1, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+fCuoreDetector.PTFEX1, -fCuoreDetector.PTFEX0, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        /*
         *  PTFE D
         */

        rotation = G4RotationMatrix();
        rotation.rotateZ(-135. * deg);

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-fCuoreDetector.PTFEX1, -fCuoreDetector.PTFEX0, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(-fCuoreDetector.PTFEX1, +fCuoreDetector.PTFEX1, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+fCuoreDetector.PTFEX0, +fCuoreDetector.PTFEX1, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );

        position =  fCuoreDetector.FrameZ.at(f) + G4ThreeVector(+fCuoreDetector.PTFEX0, -fCuoreDetector.PTFEX0, fCuoreDetector.PTFEZ);
        fCuoreDetector.PTFETrans.push_back( new G4Transform3D(rotation, position) );
    }

    // PTFE - Top
    for( unsigned int i = 0; i < fCuoreDetector.PTFETrans.size(); i++ )
    {
        G4ThreeVector position = fCuoreDetector.PTFETrans.at(i)->getTranslation();
        G4RotationMatrix rotation = fCuoreDetector.PTFETrans.at(i)->getRotation();

        rotation.rotateX(180. * deg);
        // PTFE A
        if( i % 16 < 4 )     
            rotation.rotateZ(90. * deg);
        // PTFE B
        else if( i % 16 >= 4 && i % 16 < 8 )
            rotation.rotateZ(-90. * deg);
        // PTFE C
        else if( i % 16 >= 8 && i % 16 < 12 )
            rotation.rotateZ(90. * deg);
        // PTFE D
        else if( i % 16 >= 12 )
            rotation.rotateZ(-90. * deg);

        position += G4ThreeVector(0, 0, fCuoreDetector.CrystalL);
        fCuoreDetector.PTFETransBottom.push_back(new G4Transform3D(rotation, position));
    }

    // Crystal position
    for( G4int f = 0; f < fCuoreDetector.NFloors; f++)
    {
        double z = 0.5 * fCuoreDetector.PlaneH;

        for( G4int c = 0; c < fCuoreDetector.NCrystalsPerFloor; c++ )
        {
            double x = (2*(c%2)-1) * fCuoreDetector.FrameHoleC;
            double y = (2*(c/2)-1) * fCuoreDetector.FrameHoleC;
            
            G4ThreeVector pos = fCuoreDetector.FrameZ.at(f) + G4ThreeVector(x, y, z);
            
            fCuoreDetector.CrystalPos.push_back(pos);
        }
    }
    
    // NTD position
    for( G4int f = 0; f < fCuoreDetector.NFloors; f++)
    {
        for( G4int c = 0; c < fCuoreDetector.NCrystalsPerFloor; c++ )
        {
            // Crystal position
            double x = (2*(c%2)-1) * fCuoreDetector.FrameHoleC;
            double y = (2*(c/2)-1) * fCuoreDetector.FrameHoleC;

            // Vertical offset
            double z = 0.5 * fCuoreDetector.PlaneH;

            // NTD offset
            x += (2*(c%2)-1) * 0.5 * (fCuoreDetector.CrystalL + fCuoreDetector.NTDW);
            y += - (2*(c/2)-1) * fCuoreDetector.NTDOffset;
            z += - (2*(f%2)-1) * fCuoreDetector.NTDOffset;

            G4RotationMatrix rot = G4RotationMatrix();
            G4ThreeVector pos = fCuoreDetector.FrameZ.at(f) + G4ThreeVector(x, y, z);
            fCuoreDetector.NTDTrans.push_back(
                    new G4Transform3D(rot, pos));
        }
    }

    // Tower position
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(0, 0, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(147, 0, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(-147, 0, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(294, 0, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(-294, 0, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(73.5, 147, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(-73.5, 147, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(220.5, 147, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(-220.5, 147, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(73.5, -147, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(-73.5, -147, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(220.5, -147, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(-220.5, -147, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(0, 294, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(147, 294, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(-147, 294, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(0, -294, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(147, -294, 0));
    fCuoreDetector.TowerPos.push_back( G4ThreeVector(-147, -294, 0));

    // Absolute vertical position
    fCuoreDetector.FramePos = 
        G4ThreeVector(0, 0, 
                fDetTopCuPlate.Z
                -0.5 * fDetTopCuPlate.H
                -0.5 * fCuoreDetector.TowerH
                -2. * cm);

    fCuoreDetector.PENTapePos = fCuoreDetector.FramePos;
    fCuoreDetector.PTFEPos = fCuoreDetector.FramePos;
    fCuoreDetector.NTDPos = fCuoreDetector.FramePos;
    fCuoreDetector.CrystalOffset = fCuoreDetector.FramePos;

    fCuoreDetector.FrameSourcePos = fCuoreDetector.FramePos + fVacuum.Pos;
    fCuoreDetector.PENTapeSourcePos = fCuoreDetector.PENTapePos + fVacuum.Pos;
    fCuoreDetector.PTFESourcePos = fCuoreDetector.PTFEPos + fVacuum.Pos;
    fCuoreDetector.NTDSourcePos = fCuoreDetector.NTDPos + fVacuum.Pos;
    fCuoreDetector.CrystalSourceOffset = fCuoreDetector.CrystalOffset + fVacuum.Pos;

    // Dummy flat cylinder around top part of Roman lead
    fLateralDummy.DummyLatZ    = 231.5  * cm;
    fLateralDummy.DummyLatAlt  = 47.5   * cm;
    fLateralDummy.DummyLatRag  = fSuperInsulation3rdShield.R
        - fSuperInsulation3rdShield.T;
    fLateralDummy.DummyLatSpes = 0.0001 * cm;

    // Dummy flat partial disk at top of Roman lead
    fTopDummy.DummyTopZ    = 279    * cm;
    fTopDummy.DummyTopAlt  = 0.0001 * cm;
    fTopDummy.DummyTopRag  = 67.95  * cm;
    fTopDummy.DummyTopSpes = 50.76  * cm;

    // Gaps in 4th radiation shield
    fGaps.ScassiRS4Pos.push_back( G4ThreeVector( fCuBeJoints.HoleR,
                0.,
                0.5 * ( fFourthRadiationShield.H - fCuBeJoints.H ) ) );
    fGaps.ScassiRS4Pos.push_back( G4ThreeVector( -0.5 * fCuBeJoints.HoleR,
                0.866 * fCuBeJoints.HoleR,
                0.5 * ( fFourthRadiationShield.H - fCuBeJoints.H ) ) );
    fGaps.ScassiRS4Pos.push_back( G4ThreeVector( -0.5 * fCuBeJoints.HoleR,
                -0.866 * fCuBeJoints.HoleR,
                0.5 * ( fFourthRadiationShield.H - fCuBeJoints.H ) ) );
    fGaps.NumScassiRS4 = fGaps.ScassiRS4Pos.size();



    
    
    /* 
    -----------------------------------------
    -----------------------------------------
    Phase-I structure (berettam, 05.20.24)
    Adding the configurator for the phased approach
    this structure has fewer fields, because in the geometrical object BDPT and CUORE structures will be mixed
    ----------------------------------------- 
    ----------------------------------------- 
    */
    //first: adding the tower position for the inner core (BDPT geometry) 
    //in the current prototype the core consists of 15 towers
    // organized as follows:
    /*
                x
          x   x   x
      x   x   x   x
      x   x   x   x  
      x   x   x   x
          x   x   x
                x             
    */
    // 4 rows (x) for 3 columns (y) (not symmetrical)
    // 3 rows (x) for 2 columns (y) 
    // 1 rows (x) for 2 columns (y) shifted (0.5+row)*clearancex 
    
    //4x3 
    for( G4int row=-2; row<=1; row++ ){
      for( G4int col=-1; col<=1; col+=1 ){
        G4double x = fBDPTDetector.ClearanceX * row;
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
      }
    }
    //3*2
    for( G4int row=-1; row<=1; row++ ){
      for( G4int col=-2; col<=2; col+=4 ){
        G4double x = fBDPTDetector.ClearanceX * row;
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
      }
    }
    //1*2
    G4int row=0;
      for( G4int col=-3; col<=3; col+=6 ){
        G4double x = fBDPTDetector.ClearanceX * (0.5+row);
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
      }
    

    fBDPTDetector_PhaseI.NTowers = fBDPTDetector_PhaseI.TowerPos.size();
    
    //now the outer shield, using the CUORE detector parameters
    //the outer CUORE rim is composed of 13 towers
    // towers are placed right (most positive x value) to left
    // so placed by blocks of constant x value
    G4double DeltaX = 73.5; // half a tower shift
    G4double DeltaY = 73.5; // half a tower shift
    
    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(294, 147, 0));
    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(294, 0, 0));
    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(294, -147, 0));

    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(147+DeltaX/2, 294, 0));
    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(147+DeltaX/2, -294, 0));

    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(DeltaX/2, 294+DeltaY, 0));
    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(DeltaX/2, -294-DeltaY, 0));

    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(-147+DeltaX/2, 294, 0));
    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(-147+DeltaX/2, -294, 0));

    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(-147-DeltaX*1.25, 294-DeltaY*1.5, 0));
    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(-147-DeltaX*1.25, -294+DeltaY*1.5, 0));

    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(-294-DeltaX, 147-DeltaY, 0));
    fBDPTDetector_PhaseI.TowerPos_Shield.push_back( G4ThreeVector(-294-DeltaX, -147+DeltaY, 0));

    fBDPTDetector_PhaseI.NTowers_Shield = fBDPTDetector_PhaseI.TowerPos_Shield.size();



  
    
    /* 
    -----------------------------------------
    -----------------------------------------
    Phase-I structure with TeO2 in BDPT geometry (berettam, 05.21.24)
    Adding the configurator for the phased approach - one of the alternatives
    this structure has fewer fields, because in the geometrical object BDPT stores all info    ----------------------------------------- 
    ----------------------------------------- 
    */
    //first: adding the tower position for the inner core (LMOs) 
    //in the current prototype the core consists of 19 towers
    // organized as follows:
    /*
        x   x
      x   x   x
      x   x   x
      x   x   x  
      x   x   x
      x   x   x
        x   x             
    */
    // 3 rows (x) for 5 columns (y)
    // 2 rows (x) for 2 columns (y)
    
    //3x5  
    for( G4int row=-1; row<=1; row++ ){
      for( G4int col=-2; col<=2; col+=1 ){
        G4double x = fBDPTDetector.ClearanceX * row;
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI_SameTowers.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
      }
    }
    //2*2
    for( G4int row=-1; row<=0; row++ ){
      for( G4int col=-3; col<=3; col+=6 ){
        G4double x = fBDPTDetector.ClearanceX *( 0.5 + row);
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI_SameTowers.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
      }
    }

    fBDPTDetector_PhaseI_SameTowers.NTowers = fBDPTDetector_PhaseI_SameTowers.TowerPos.size();
    
    //now the outer shield, using the BDPT parameters
    // here the configuration is stranger
    
    /*
        x   x   x
      x           x
    x               x
    x               x
    x               x
    x               x
    x               x   
      x           x  
        x   x   x
    */
   // 3 rows for 3 cols
   // 2 rows (more internal) for 2 columns
   // 2 rows (external) for 5 columns

   //3x2 
    for( G4int row=-1; row<=1; row++ ){
      for( G4int col=-4; col<=4; col+=8 ){
        G4double x = fBDPTDetector.ClearanceX * row;
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI_SameTowers.TowerPos_Shield.push_back( G4ThreeVector( x, y, 0 ) );
      }
    }
    // 2x2 -- internal
    for( G4int row=-2; row<=1; row+=3 ){
      for( G4int col=-3; col<=3; col+=6 ){
        G4double x = fBDPTDetector.ClearanceX *( 0.5 + row);
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI_SameTowers.TowerPos_Shield.push_back( G4ThreeVector( x, y, 0 ) );
      }
    }
    // 2x5 
    for( G4int row=-2; row<=2; row+=4 ){
      for( G4int col=-2; col<=2; col+=1 ){
        G4double x = fBDPTDetector.ClearanceX * row;
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI_SameTowers.TowerPos_Shield.push_back( G4ThreeVector( x, y, 0 ) );
      }
    }
    
    fBDPTDetector_PhaseI_SameTowers.NTowers_Shield = fBDPTDetector_PhaseI_SameTowers.TowerPos_Shield.size();


    
    
    /* 
    -----------------------------------------
    -----------------------------------------
    Phase-I structure with passive shield (berettam, 05.22.24)
    Adding the configurator for the phased approach
    this structure has fewer fields, because in will use the BDPTstructure 
    ----------------------------------------- 
    ----------------------------------------- 
    */
    //adding the tower position for the inner core (BDPT geometry) 
    //in the current prototype the core consists of 19 towers
    // organized as follows:
    /*
        x   x
      x   x   x
      x   x   x
      x   x   x   
      x   x   x
      x   x   x
        x   x             
    */
    // 3 rows (x) for 5 columns (y) 
    // 2 rows (x) for 2 columns (y) shifted (0.5+row)*clearancex 
    
    
    //3x5 --> the ol done 19 ths
    for( G4int row=-1; row<=1; row++ ){
      for( G4int col=-2; col<=2; col+=1 ){
        G4double x = fBDPTDetector.ClearanceX * row;
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI_PassiveShield.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
      }
    } 

    //MORELIGHT GEOMETRY -- used one just for plotting
    // //5x3  adding the morelight towers side by side at the center
    // for( G4int row=-2; row<=2; row++ ){
    //   for( G4int col=-1; col<=1; col+=1 ){
    //     G4double x = fBDPTDetector.ClearanceX * row;
    //     G4double y = fBDPTDetector.ClearanceY * col;
    //     fBDPTDetector_PhaseI_PassiveShield.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
    //   }
    // }

    // // now the two lines with only 3 rows
    // for( G4int row=-1; row<=1; row++ ){
    //   for( G4int col=-2; col<=2; col+=4 ){
    //     G4double x = fBDPTDetector.ClearanceX * row;
    //     G4double y = fBDPTDetector.ClearanceY * col;
    //     fBDPTDetector_PhaseI_PassiveShield.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
    //   }
    // }


    //2x2
    for( G4int row=-1; row<=0; row++ ){
      for( G4int col=-3; col<=3; col+=6 ){
        G4double x = fBDPTDetector.ClearanceX * (0.5+row);
        G4double y = fBDPTDetector.ClearanceY * col;
        fBDPTDetector_PhaseI_PassiveShield.TowerPos.push_back( G4ThreeVector( x, y, 0 ) );
      }
    }

    fBDPTDetector_PhaseI_PassiveShield.NTowers = fBDPTDetector_PhaseI_PassiveShield.TowerPos.size();

    //now deciding the shield parameters
    fBDPTDetector_PhaseI_PassiveShield.Shield_Thickness_mm = 45 * mm;
    fBDPTDetector_PhaseI_PassiveShield.Shield_OuterRadius_mm = 355 * mm ;
    fBDPTDetector_PhaseI_PassiveShield.Shield_InnerRadius_mm = fBDPTDetector_PhaseI_PassiveShield.Shield_OuterRadius_mm-fBDPTDetector_PhaseI_PassiveShield.Shield_Thickness_mm;
    //Getting the heigt as a difference from the other cryostat parameters
    fBDPTDetector_PhaseI_PassiveShield.Shield_Height = fCuoreDetector.DCSTubeH;
    fBDPTDetector_PhaseI_PassiveShield.Shield_Z =  0.5 * (fDetTopCuPlate.Z + fDetBottomCuPlate.Z);
    fBDPTDetector_PhaseI_PassiveShield.Shield_Pos = G4ThreeVector( 0., 0., fBDPTDetector_PhaseI_PassiveShield.Shield_Z );
    fBDPTDetector_PhaseI_PassiveShield.Shield_SourcePos = G4ThreeVector( 0., 0., fBDPTDetector_PhaseI_PassiveShield.Shield_Z ) + fVacuum.Pos;
    return;
}

