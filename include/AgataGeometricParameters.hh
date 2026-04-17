// Author: Giovanni Benato
// Contact: giovanni.benato@lngs.infn.it
//
// Variable naming logic:
// L = length (e.g. for G4Box)
// R = radius
// H = height
// T = thickness
// P = position

#ifndef AgataGeometricParameters_h
#define AgataGeometricParameters_h 1

#include <vector>

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Types.hh"
#include "G4TwoVector.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

using namespace CLHEP;

class AgataGeometricParameters
{
    public:

        // ---------
        // Muon veto
        // ---------

        struct MuonVeto
        {
            G4double LateralExtL;
            G4double LateralIntL;
            G4double LateralH;
            G4double LateralZ;
            G4double BottomLateralX;
            G4double BottomLateralY;
            G4double BottomLateralT;
            G4double BottomLateralH;
            G4double BottomLateralZ;
            G4double BottomX;
            G4double BottomY;
            G4double BottomT;
            G4double BottomZ;
            G4ThreeVector LateralPos;
            G4ThreeVector LateralSourcePos;
            G4ThreeVector BottomLateralPos;
            G4ThreeVector BottomLateralSourcePos;
            G4ThreeVector BottomPos;
            G4ThreeVector BottomSourcePos;
        };

        struct RealisticMuonVeto
        {
          G4int nPanels;
          G4int nRings;
          std::vector<G4double> LateralRadius;
          std::vector<G4double> LateralWidth;
          G4double LateralHeight;
          G4double LateralThickness;
         	G4double LateralH;
         	G4double LateralZ;
         	G4double BottomLateralX;
         	G4double BottomLateralY;
         	G4double BottomLateralT;
         	G4double BottomLateralH;
         	G4double BottomLateralZ;
         	G4double BottomX;
         	G4double BottomY;
         	G4double BottomT;
         	G4double BottomZ;
        	G4double TopX;
        	G4double TopY;
        	G4double TopT;
        	G4double TopZ;
         	G4ThreeVector LateralPos;
         	G4ThreeVector LateralSourcePos;
         	G4ThreeVector BottomLateralPos;
         	G4ThreeVector BottomLateralSourcePos;
         	G4ThreeVector BottomPos;
         	G4ThreeVector BottomSourcePos;
         	G4ThreeVector TopPos;
         	G4ThreeVector TopSourcePos;
        };



        // ----------------
        // External shield
        // ----------------
        struct Polyethylene
        {
            G4double ExtL;
            G4double IntL;
            G4double H;
            G4double BottomH;
            G4double Z;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
        };

        struct BoricAcid
        {
            G4double ExtL;
            G4double IntL;
            G4double H;
            G4double Z;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
        };

        struct ExternalLead
        {
            G4double ExtL;
            G4double IntL;
            G4double H;
            G4double BottomH;
            G4double Z;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
        };
        struct CalibrationSource
        {
            G4int nVertices;
            G4double arrayRadius;
            G4double CylR;
            G4double CylH;
            G4double CylLocationX;
            G4double CylLocationY;
            G4double CylLocationZ;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
        };

        // --------
        // Cryostat
        // --------

        // 1st radiation shield (300 K)
        struct FirstRadiationShield
        {
            G4double FlangeR;
            G4double FlangeH;
            G4double R;
            G4double H;
            G4double TotH;
            G4double T;
            G4double BottomT;
            G4double BottomCylT;
            G4double SphereR;
            G4double Theta;
            G4double BottomH;
            G4double SteelT;
            G4double SteelR;
            G4double SteelH;
            G4double RingR;
            G4double RingH;
            G4double RingT;
            G4double DistFromPETop;
            G4double Z;
            G4double SteelZ;
            G4double FlangeZ;
            G4ThreeVector SteelPos;
            G4ThreeVector SteelSourcePos;
            G4ThreeVector CuPos;
            G4ThreeVector CuSourcePos;
            G4ThreeVector FlangePos;
            G4ThreeVector FlangeSourcePos;

        };

        // Vacuum inside 1st radiation shield
        struct Vacuum
        {
            G4double Z;
            G4double R;
            G4double H;
            G4double TotH;
            G4double BottomT;
            G4double SphereR;
            G4double Theta;
            G4double BottomH;
            G4ThreeVector Pos;
        };

        // 2nd radiation shield (40 K)
        struct SecondRadiationShield
        {
            G4double DistFromRS1;
            G4double Z;
            G4double FlangeZ;
            G4double FlangeR;
            G4double FlangeH;
            G4double T;
            G4double H;
            G4double TotH;
            G4double R;
            G4double RingR;
            G4double RingH;
            G4double RingT;
            G4double SphereR;
            G4double Theta;
            G4double TorusR;
            G4double BottomR;
            G4double BottomH;
            G4double BottomT;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
            G4ThreeVector FlangePos;
            G4ThreeVector FlangeSourcePos;
        };

        // Superinsulation of 2nd radiation shield (40 K)
        struct SuperInsulation2ndShield
        {
            G4double FlangeR;
            G4double FlangeH;
            G4double T;
            G4double H;
            G4double TotH;
            G4double R;
            G4double BottomT;
            G4double BottomH;
            G4double SphereR;
            G4double Theta;
            G4double Z;
            G4double FlangeZ;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
            G4ThreeVector FlangePos;
            G4ThreeVector FlangeSourcePos;
        };

        // 3rd radiation shield (4 K)
        struct ThirdRadiationShield
        {
            G4double DistFromRS2;
            G4double FlangeR;
            G4double FlangeH;
            G4double T;
            G4double BottomT;
            G4double BottomH;
            G4double H;
            G4double TotH;
            G4double R;
            G4double RingR;
            G4double RingH;
            G4double RingT;
            G4double Theta;
            G4double SphereR;
            G4double Z;
            G4double FlangeZ;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
            G4ThreeVector FlangePos;
            G4ThreeVector FlangeSourcePos;
        };

        // Superinsulation of 3rd radiation shield (4 K)
        struct SuperInsulation3rdShield
        {
            G4double FlangeR;
            G4double FlangeH;
            G4double T;
            G4double H;
            G4double TotH;
            G4double R;
            G4double SphereR;
            G4double Theta;
            G4double BottomT;
            G4double BottomH;
            G4double Z;
            G4double FlangeZ;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
            G4ThreeVector FlangePos;
            G4ThreeVector FlangeSourcePos;
        };

        // 4th radiation shield (600 mK)
        struct FourthRadiationShield
        {
            G4double DistFromRS3;
            G4double R;
            G4double H;
            G4double TotH;
            G4double T;
            G4double FlangeR;
            G4double FlangeH;
            G4double RingR;
            G4double RingT;
            G4double RingH;
            G4double TorusR;
            G4double SphereR;
            G4double ThetaMin;
            G4double ThetaMax;
            G4double BottomR;

            G4double LTPhase;
            G4double LTWidth;
            G4double LTDepth;
            G4double LTAperture;
            std::vector<G4RotationMatrix*> LTRot;

            G4double SSPhase;// Phase of CuBe holders
            G4double SSWidth;// Width of CuBe holes in vessel
            G4double SSAperture;// Aperture of CuBe holes in vessel
            G4double SSH;// Height of CuBe holes in vessel
            G4double SSD;// Distance from center of CuBe holes in flange
            G4double SSR;// Distance from center of CuBe holes in flange
            std::vector<G4double> SSAngle;
            std::vector<G4ThreeVector> SSHoleP;
            std::vector<G4RotationMatrix*> SSRot;
            std::vector<G4ThreeVector> SSFlangeHoleP;

            G4double Z;
            G4double FlangeZ;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
            G4ThreeVector FlangePos;
            G4ThreeVector FlangeSourcePos;
        };

        // Roman lead around 600 mK shield
        struct RomanLead
        {
            //** PbRom Lateral Cylinder  **
            G4double H;
            G4double R;
            G4double T;
            G4double RodsHoleD;
            G4double RodsHoleR;
            G4double RodsFlangeHoleR;
            G4double RodsPhase;
            std::vector<G4ThreeVector> RodsHoleP;
            G4double TopCuRingR;
            G4double TopCuRingH;
            G4double TopCuRingT;
            G4double BottomCuRingR;
            G4double BottomCuRingH;
            G4double BottomCuRingT;
            G4double CuCradleR;
            G4double CuCradleH;
            G4double BottomPbR;
            G4double BottomPbH;
            G4double DistFromRS4Flange;
            G4double Z;
            G4double TopCuRingZ;
            G4double BottomCuRingZ;
            G4double BottomPbZ;

            std::vector<G4double> Angle;
            G4ThreeVector PbPos;
            G4ThreeVector PbSourcePos;
            G4ThreeVector TopCuRingPos;
            G4ThreeVector TopCuRingSourcePos;
            G4ThreeVector BottomCuRingPos;
            G4ThreeVector BottomCuRingSourcePos;
            G4ThreeVector BottomPbPos;
            G4ThreeVector BottomPbSourcePos;
        };

        // Steel rods
        struct SteelRods
        {
            G4double R;
            G4double H;
            G4double TopR;
            G4double TopH;
            G4double HatR;
            G4double HatH;
            G4double Z;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;

            std::vector<G4ThreeVector> HoleP;
            std::vector<G4ThreeVector> ACHoleP;
        };

        // 5th radiation shield (50 mK)
        struct FifthRadiationShield
        {
            G4double R;
            G4double H;
            G4double TotH;
            G4double T;
            G4double FlangeR;
            G4double FlangeH;
            G4double RingR;
            G4double RingH;
            G4double RingT;
            G4double TorusR;
            G4double SphereR;
            G4double ThetaMin;
            G4double ThetaMax;
            G4double BottomR;

            // Rounded slits for CuBe holders (SS1, SS2 and SS3 in drawings)
            G4double SSPhase;// Phase of CuBe holders
            G4double SSD;// Distance from center of CuBe holes in flange
            G4double SSR;// Distance from center of CuBe holes in flange
            std::vector<G4double> SSAngle;
            std::vector<G4ThreeVector> SSHoleP;
            std::vector<G4ThreeVector> SSFlangeHoleP;

            // Unknown slits (S1, S2, S3 and S4 in drawings)
            G4double SWidth;
            G4double SDepth;
            G4double SAperture;
            G4double SFlangeDepth;
            G4double SFlangeAperture;
            G4int    NSSlits;
            std::vector<G4double> SPhase;
            std::vector<G4ThreeVector> SHoleP;
            std::vector<G4RotationMatrix*> SRot;

            G4double DistBotCuRS4BotCuRS5;
            G4double DistFromRS4;
            G4double Z;
            G4double FlangeZ;

            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
            G4ThreeVector FlangePos;
            G4ThreeVector FlangeSourcePos;
        };

        // Cu-Be joints
        struct CuBeJoints
        {
            G4double H;
            G4double R;
            G4double HoleR;
            G4double Z;
            G4int    NumGiuntiCuBe;
            std::vector<G4ThreeVector> GiuntiCuBePos;
        };

        // 6th radiation shield (10 mK)
        struct SixthRadiationShield
        {
            G4double R;
            G4double H;
            G4double T;
            G4double FlangeR;
            G4double FlangeH;
            G4double RingR;
            G4double RingH;
            G4double RingT;
            std::vector<G4ThreeVector> RingPos;// Position of ring relative to main cylinder
            std::vector<bool> IsDoubleRing;
            G4int    NRings;
            G4double BottomR;
            G4double BottomH;
            G4double TilesR;// Tiles are approximated with a cylinder
            G4double TilesH;
            G4double TilesT;

            G4double DistFromRS5;
            G4double Z;
            G4double FlangeZ;
            G4double TilesZ;

            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
            G4ThreeVector FlangePos;
            G4ThreeVector FlangeSourcePos;
            G4ThreeVector TilesPos;
            G4ThreeVector TilesSourcePos;

            G4double CuRS6RingDouble1ZRelToRing0;
            G4double CuRS6RingDouble2ZRelToRing0;
            G4double CuRS6RingDouble3ZRelToRing0;
            G4double CuRS6RingDouble4ZRelToRing0;
            G4double CuRS6Ring5ZRelToRing0;

        };

        // Cu plate above top internal lead shielding
        struct InternalTopPb
        {
            G4double TopCuR;
            G4double TopCuH;
            G4double TopCuDistFromRS6;
            G4double TopCuZ;
            G4double R;
            G4double H;
            G4double Z;
            G4double BottomCuR;
            G4double BottomCuH;
            G4double BottomCuZ;

            G4ThreeVector TopCuPos;
            G4ThreeVector TopCuSourcePos;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
            G4ThreeVector BottomCuPos;
            G4ThreeVector BottomCuSourcePos;
        };

        // Tower Support Plate (TSP)
        struct TSP
        {
            G4double R;
            G4double H;
            G4double DistFromIntTopPb;
            G4double SuspensionR;
            G4double SuspensionT;
            G4double Suspensionr;
            G4double SuspensionH;

            G4double Z;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
            std::vector<G4ThreeVector>     SuspensionPos;
            std::vector<G4ThreeVector>     SuspensionSourcePos;
            std::vector<G4RotationMatrix*> SuspensionRot;
        };

        // Cu detector top plate (tiles attached to TSP bottom)
        struct DetTopCuPlate
        {
            G4double R;
            G4double H;
            G4double Z;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
        };

        // Cu detector bottom plate
        struct DetBottomCuPlate
        {
            G4double R;
            G4double H;
            G4double DistFromTopCuPlate;
            G4double Z;
            G4ThreeVector Pos;
            G4ThreeVector SourcePos;
        };

        // ---------------------------
        // Detector: frames + crystals
        // ---------------------------

        // Frame
        struct Frame
        {
            G4int SpacerN;
            G4int PlaneN;
            G4double LaterDist;
            G4double FrontDist;
            G4double DetectorR;
            G4double DetectorH;
            G4double LDetectorR;
            G4double LDetectorH;
            G4double ReflectorSpes;
            G4double ReflectorR1;
            G4double ReflectorR2;
            G4double ReflectorH;
            G4double ReflectorHS;
            G4double RingSpes;
            G4double RingR1;
            G4double RingR2;
            G4double RingH;
            G4double SpacerR;
            G4double SpacerH;
            G4double SpacerRAG;
            G4double TowerR;
            G4double TowerH;
            G4double DistCuDetUpPlateTowersTop;
            G4double TowersCenterZ;
        };

        struct PileDetector
        {
            G4int    NFloors;
            G4double CrystalL;
            G4double LightDetL;
            G4double LightDetDiagL;
            G4double LightDetT;

            G4double CuFrameX;
            G4double CuFrameY;
            G4double CuFrameH;
            G4double CuTopFrameH;
            G4double CuBottomFrameH;
            G4double CuFrameHoleL;
            G4double CuFrameDT;

            G4double PTFEFrameX;
            G4double PTFEFrameY;
            G4double PTFEFrameH;
            G4double PTFEFrameHoleL;
            G4double PTFEFrameHoleL2;
            G4double PTFEFrameHoleT;
            G4double PTFEFrameHoleH;
            G4double PTFEFrameT;
            G4double PinL;
            G4double PinT;
            G4double CuBandX;
            G4double CuBandY;
            G4double CuBandH;
            G4double PENBandX;
            G4double PENBandY;
            G4double PENBandH;
            G4double PENCoverT;
            G4double PENCoverX;
            G4double PENCoverY;
            G4double PENCoverH;
            G4double ClearanceX;
            G4double ClearanceY;

            G4double ReflectorL;
            G4double ReflectorH;
            G4double ReflectorT;

            std::vector<G4ThreeVector> CuBandPos;
            std::vector<G4Transform3D*> PENBandTrans;
            std::vector<G4Transform3D*> PENCoverTrans;
            std::vector<G4ThreeVector> PTFEPos;
            std::vector<G4RotationMatrix*> PTFERot;
            std::vector<G4Transform3D*> BottomPTFETrans;
            std::vector<G4Transform3D*> TopPTFETrans;
            std::vector<G4Transform3D*> ReflectorTrans;

            std::vector<G4ThreeVector> TopPinPos;
            std::vector<G4ThreeVector> BottomPinPos;
            std::vector<G4RotationMatrix*> PinRot;
            std::vector<G4ThreeVector> CrystalSolidPos;
            std::vector<G4ThreeVector> LightDetSolidPos;

            G4double CrystalZ;
            G4ThreeVector CrystalPos;
            G4ThreeVector CrystalSourcePos;
            G4double CuFrameZ;
            G4ThreeVector CuFramePos;
            G4ThreeVector CuFrameSourcePos;
            G4double PENBandZ;
            G4ThreeVector PENBandPos;
            G4ThreeVector PENBandSourcePos;
            G4double PENCoverZ;
            G4ThreeVector PENCoverPos;
            G4ThreeVector PENCoverSourcePos;
            G4double PTFEFrameZ;
            G4ThreeVector PTFEFramePos;
            G4ThreeVector PTFEFrameSourcePos;
            G4double LightDetZ;
            G4ThreeVector LightDetPos;
            G4ThreeVector LightDetSourcePos;
            G4double ReflectorZ;
            G4ThreeVector ReflectorPos;
            G4ThreeVector ReflectorSourcePos;

            std::vector<G4ThreeVector> TowerPos;
            G4int NTowers;
        };


        struct BDPTDetector
        {
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
        };


        struct BDPTDetector_PhaseI
        {
            /*
            berettam - 05/20/20204
            This struct will be used to merge BDPT-like and CUORE-like structures
            The two will be split into a set of shield detectors (outer rim) and detectors(inner core)
            Only the core will have LDs
            */

            std::vector<G4ThreeVector> TowerPos;
            G4int NTowers;
            std::vector<G4ThreeVector> TowerPos_Shield;
            G4int NTowers_Shield;

            G4double LightDetZ;
            G4ThreeVector LightDetPos;
            G4ThreeVector LightDetSourcePos;

            G4double CrystalZ;
            G4ThreeVector CrystalPos;
            G4ThreeVector CrystalSourcePos;

            
            G4double CrystalShieldZ;
            G4ThreeVector CrystalShieldPos;
            G4ThreeVector CrystalShieldSourcePos;
        };

        
        struct BDPTDetector_PhaseI_SameTowers
        {
            /*
            berettam - 05/21/20204
            This struct will be used to insert TeO2 in the BDPT geometry
            TeO2 will be shield detectors (outer rim) and LMOs will be actual physics detectors (inner core)
            */

            std::vector<G4ThreeVector> TowerPos;
            G4int NTowers;
            std::vector<G4ThreeVector> TowerPos_Shield;
            G4int NTowers_Shield;

            G4double LightDetZ;
            G4ThreeVector LightDetPos;
            G4ThreeVector LightDetSourcePos;

            G4double CrystalZ;
            G4ThreeVector CrystalPos;
            G4ThreeVector CrystalSourcePos;

            
            G4double CrystalShieldZ;
            G4ThreeVector CrystalShieldPos;
            G4ThreeVector CrystalShieldSourcePos;
        };

        
        struct BDPTDetector_PhaseI_PassiveShield
        {
            /*
            berettam - 05/22/20204
            This struct will get a partial number of towers from BDPT-like (inner core)
            and surround them with a shield
            */

            std::vector<G4ThreeVector> TowerPos;
            G4int NTowers;
            G4double Shield_InnerRadius_mm;
            G4double Shield_OuterRadius_mm;
            G4double Shield_Height;
            G4double Shield_Thickness_mm;
            G4double Shield_Z;
            G4ThreeVector Shield_Pos;
            G4ThreeVector Shield_SourcePos;
        };



        struct CuoreLikeDetector
        {
            G4int    NFloors;
            G4double CrystalL;
            G4double LightDetL;
            G4double LightDetT;
            G4double CuFrameX;
            G4double CuFrameY;
            G4double CuFrameH;
            G4double CuTopFrameH;
            G4double CuBottomFrameH;
            G4double CuFrameHoleL;
            G4double CuFrameHoleL2;
            G4double CuFrameDT;
            G4double CuFrameThinningL;
            G4double CuFrameThinningH;
            std::vector<G4ThreeVector> CuHolePos;
            std::vector<G4ThreeVector> CuHolePos2;
            std::vector<G4ThreeVector> CuFrameThinningPos;
            std::vector<G4ThreeVector> CuTopFrameThinningPos;
            std::vector<G4ThreeVector> CuBottomFrameThinningPos;
            std::vector<G4RotationMatrix*> CuFrameThinningRot;
            G4double CuColumnR;
            G4double CuColumnH;
            std::vector<G4ThreeVector> CuColumnPos;
            G4double TowerH;

            G4double t1x;
            G4double t1y;
            G4double t1z;
            G4double t2x;
            G4double t2y;
            G4double t2z;
            G4double t2t;
            G4double b1x;
            G4double b1y;
            G4double b1z;
            G4double b2x;
            G4double b2y;
            G4double b2z;
            G4double b1t;
            G4double b2t;
            G4double b3x;
            G4double b3y;
            G4double b3z;
            G4double b3t;

            std::vector<G4ThreeVector> PTFEPos;
            std::vector<G4RotationMatrix*> PTFERot;

            G4double CuBandX;
            G4double CuBandY;
            G4double CuBandH;
            G4double ClearanceX;
            G4double ClearanceY;
            std::vector<G4ThreeVector> CuBandPos;
            std::vector<G4ThreeVector> TopPinPos;
            std::vector<G4ThreeVector> BottomPinPos;
            std::vector<G4RotationMatrix*> PinRot;
            std::vector<G4ThreeVector> CrystalSolidPos;
            std::vector<G4ThreeVector> LightDetSolidPos;

            G4double CrystalZ;
            G4ThreeVector CrystalPos;
            G4ThreeVector CrystalSourcePos;
            G4double CuFrameZ;
            G4ThreeVector CuFramePos;
            G4ThreeVector CuFrameSourcePos;
            G4double PTFEFrameZ;
            G4ThreeVector PTFEFramePos;
            G4ThreeVector PTFEFrameSourcePos;
            G4double LightDetZ;
            G4ThreeVector LightDetPos;
            G4ThreeVector LightDetSourcePos;

            std::vector<G4ThreeVector> TowerPos;
            G4int NTowers;
        };

        struct Cuore1x2Detector
        {
            G4int    NFloors;
            G4double CrystalL;
            G4double LightDetL;
            G4double LightDetT;
            G4double CuFrameX;
            G4double CuFrameY;
            G4double CuFrameH;
            G4double CuTopFrameH;
            G4double CuBottomFrameH;
            G4double CuFrameHoleL;
            G4double CuFrameHoleL2;
            G4double CuFrameDT;
            G4double CuFrameThinningL;
            G4double CuFrameThinningH;
            std::vector<G4ThreeVector> CuHolePos;
            std::vector<G4ThreeVector> CuHolePos2;
            std::vector<G4ThreeVector> CuFrameThinningPos;
            std::vector<G4ThreeVector> CuTopFrameThinningPos;
            std::vector<G4ThreeVector> CuBottomFrameThinningPos;
            std::vector<G4RotationMatrix*> CuFrameThinningRot;
            G4double CuColumnR;
            G4double CuColumnH;
            std::vector<G4ThreeVector> CuColumnPos;
            G4double TowerH;

            G4double t1x;
            G4double t1y;
            G4double t1z;
            G4double t2x;
            G4double t2y;
            G4double t2z;
            G4double t2t;
            G4double b1x;
            G4double b1y;
            G4double b1z;
            G4double b2x;
            G4double b2y;
            G4double b2z;
            G4double b1t;
            G4double b2t;
            G4double b3x;
            G4double b3y;
            G4double b3z;
            G4double b3t;

            std::vector<G4ThreeVector> PTFEPos;
            std::vector<G4RotationMatrix*> PTFERot;

            G4double CuBandX;
            G4double CuBandY;
            G4double CuBandH;
            G4double ClearanceX;
            G4double ClearanceY;
            std::vector<G4ThreeVector> CuBandPos;
            std::vector<G4ThreeVector> TopPinPos;
            std::vector<G4ThreeVector> BottomPinPos;
            std::vector<G4RotationMatrix*> PinRot;
            std::vector<G4ThreeVector> CrystalSolidPos;
            std::vector<G4ThreeVector> LightDetSolidPos;

            G4double CrystalZ;
            G4ThreeVector CrystalPos;
            G4ThreeVector CrystalSourcePos;
            G4double CuFrameZ;
            G4ThreeVector CuFramePos;
            G4ThreeVector CuFrameSourcePos;
            G4double PTFEFrameZ;
            G4ThreeVector PTFEFramePos;
            G4ThreeVector PTFEFrameSourcePos;
            G4double LightDetZ;
            G4ThreeVector LightDetPos;
            G4ThreeVector LightDetSourcePos;

            std::vector<G4ThreeVector> TowerPos;
            G4int NTowers;
        };

        struct CanfrancLikeDetector
        {
            G4int    NFloors;
            G4double CrystalL;
            G4double LightDetL;
            G4double LightDetT;
            G4double CuFrameX;
            G4double CuFrameY;
            G4double CuFrameH;
            G4double CuFrameLateralT;
            G4double CuFrameCentralT;
            G4double CuFrameHoleL;
            G4double CuFrameShortGap;
            G4double CuFrameLongGap;
            G4double CuColumnR;
            G4double CuColumnH;
            G4double CuColumnOffset;
            G4double CuColumnDistance;
            G4double TowerH;
            std::vector<G4ThreeVector> CuHolePos;
            std::vector<G4ThreeVector> CuColumnPos;
            std::vector<G4ThreeVector> CuMainFramePos;

            G4double LateralPTFEX;
            G4double LateralPTFEY;
            G4double LateralPTFEH;
            G4double LateralPTFETopHoleX;
            G4double LateralPTFETopHoleH;
            G4double LateralPTFEBottomHoleX;
            G4double LateralPTFEBottomHoleH;

            G4double CentralPTFEX;
            G4double CentralPTFEY;
            G4double CentralPTFEH;
            G4double CentralPTFETopHoleX;
            G4double CentralPTFETopHoleH;
            G4double CentralPTFEBottomHoleX;
            G4double CentralPTFEBottomHoleH;

            G4double LateralLDPTFEX;
            G4double LateralLDPTFEY;
            G4double LateralLDPTFEH;
            G4double CentralLDPTFEX;
            G4double CentralLDPTFEY;
            G4double CentralLDPTFEH;
            G4double LDPTFEHoleX;
            G4double LDPTFEHoleY;
            G4double LDPTFEHoleH;
            G4double LDPTFESlitX;
            G4double LDPTFESlitY;
            G4double LDPTFESlitH;

            std::vector<G4Transform3D*> CentralPTFETrans;
            std::vector<G4Transform3D*> LateralPTFETrans;
            std::vector<G4Transform3D*> CentralLDPTFETrans;
            std::vector<G4Transform3D*> LateralLDPTFETrans;


            G4double CuBandX;
            G4double CuBandY;
            G4double CuBandH;
            G4double ClearanceX;
            G4double ClearanceY;
            std::vector<G4ThreeVector> CrystalSolidPos;
            std::vector<G4ThreeVector> LightDetSolidPos;

            G4double CrystalZ;
            G4ThreeVector CrystalPos;
            G4ThreeVector CrystalSourcePos;
            G4double CuFrameZ;
            G4ThreeVector CuFramePos;
            G4ThreeVector CuFrameSourcePos;
            G4double PTFEFrameZ;
            G4ThreeVector PTFEFramePos;
            G4ThreeVector PTFEFrameSourcePos;
            G4double LightDetZ;
            G4ThreeVector LightDetPos;
            G4ThreeVector LightDetSourcePos;

            std::vector<G4ThreeVector> TowerPos;
            G4int NTowers;
        };

        /*
         *  CUORE
         */
        struct CuoreDetector
        {     
            // -- DCS tubes
            G4double DCSTubeR;
            G4double DCSTubeH;
            G4double DCSTubeT;
            G4double DCSTubeZ;
                
            // -- Frames
            G4double FrameL;
            G4double FrameH;
            G4double EdgeFrameH;
            G4double FrameW;

            G4double FrameHoleL;
            G4double FrameHoleC;

            G4double FrameNotchL;
            G4double FrameNotchH;
            G4double FrameCentralNotchL;

            // -- Columns
            G4double ColumnR;
            G4double ColumnH;
            
            // -- Wire trays
            G4double PlaneH;
            G4double TowerH;
            G4double WireTrayW;
            G4double WireTrayL;

            G4double WireTrayVL;
            G4double WireTrayVW;
            G4double WireTrayVH;

            G4double WireTrayArmW;
            G4double WireTrayArmH;
            G4double WireTrayArmL;

            // -- PEN tape
            G4double PENTapeW;
            G4double PENTapeL;

            G4double PENTapeArmL;
            G4double PENTapeArmH;

            G4double PENTapeOffset;

            // -- Wire pad
            G4double WirePadW;
            G4double WirePadL;
            G4double WirePadH;

            // -- NTD
            G4double NTDW;
            G4double NTDL;
            G4double NTDH;
            G4double NTDOffset;

            // -- PTFE
            G4double PTFEW;
            G4double PTFEL;
            G4double PTFEH;

            G4double PTFENotchW;
            G4double PTFENotchL;
            G4double PTFENotchH;
            G4double PTFENotchYOffset;
            G4double PTFENotchZOffset;

            G4double PTFEBlock1W;
            G4double PTFEBlock1L;
            G4double PTFEBlock1H;
            G4double PTFEBlock2W;
            G4double PTFEBlock2L;
            G4double PTFEBlock2H;
            G4double PTFEBlockOffset;

            G4double PTFESub1YOffset;
            G4double PTFESub1ZOffset;
            G4double PTFESub2YOffset;
            G4double PTFESub3YOffset;

            G4double PTFEFrameDist;
            G4double PTFEX0;
            G4double PTFEX1;
            G4double PTFEZ;

            // -- Crystals
            G4int NCrystalsPerFloor;
            G4double CrystalL;

            // -- Position
            G4int NFloors;
            G4int NTowers;

            std::vector<G4Transform3D*> FrameTrans;
            std::vector<G4Transform3D*> ColumnTrans;
            std::vector<G4Transform3D*> WireTrayTrans;
            std::vector<G4Transform3D*> WireTrayCoverTrans;
            std::vector<G4Transform3D*> WirePadTrans;
            std::vector<G4Transform3D*> PENTapeTrans;
            std::vector<G4Transform3D*> PTFETrans;
            std::vector<G4Transform3D*> PTFETransBottom;
            std::vector<G4Transform3D*> NTDTrans;

            std::vector<G4ThreeVector> DCSTubePos;
            std::vector<G4ThreeVector> DCSTubeSourcePos;
            std::vector<G4ThreeVector> CrystalPos;
            std::vector<G4ThreeVector> TowerPos;
            std::vector<G4ThreeVector> FrameZ;

            G4ThreeVector FramePos;
            G4ThreeVector PENTapePos;
            G4ThreeVector PTFEPos;
            G4ThreeVector NTDPos;
            G4ThreeVector FrameSourcePos;
            G4ThreeVector PENTapeSourcePos;
            G4ThreeVector PTFESourcePos;
            G4ThreeVector NTDSourcePos;

            G4ThreeVector CrystalOffset;
            G4ThreeVector CrystalSourceOffset;
        };

        // --------------
        // Dummy elements --> What do we need them for?
        // --------------

        // Dummy flat cylinder around top part of Roman lead
        struct LateralDummy
        {
            G4double DummyLatZ;
            G4double DummyLatAlt;
            G4double DummyLatRag;
            G4double DummyLatSpes;
        };

        // Dummy flat partial disk at top of Roman lead
        struct TopDummy
        {
            G4double DummyTopZ;
            G4double DummyTopAlt;
            G4double DummyTopRag;
            G4double DummyTopSpes;
        };

        // -------------------------------------------
        // Center coordinates of non-centered elements
        // -------------------------------------------

        // Gaps in 4th radiation shield
        struct Gaps
        {
            G4int NumScassiRS4;
            std::vector<G4ThreeVector> ScassiRS4Pos;
        };


    private:

        static AgataGeometricParameters* fInstance;

        MuonVeto                 fMuonVeto;
        RealisticMuonVeto        fRealisticMuonVeto;
        Polyethylene             fPolyethylene;
        BoricAcid                fBoricAcid;
        ExternalLead             fExternalLead;
        CalibrationSource        fCalibrationSource;
        FirstRadiationShield     fFirstRadiationShield;
        Vacuum                   fVacuum;
        SecondRadiationShield    fSecondRadiationShield;
        SuperInsulation2ndShield fSuperInsulation2ndShield;
        ThirdRadiationShield     fThirdRadiationShield;
        SuperInsulation3rdShield fSuperInsulation3rdShield;
        FourthRadiationShield    fFourthRadiationShield;
        CuBeJoints               fCuBeJoints;
        RomanLead                fRomanLead;
        SteelRods                fSteelRods;
        FifthRadiationShield     fFifthRadiationShield;
        SixthRadiationShield     fSixthRadiationShield;
        InternalTopPb            fInternalTopPb;
        TSP                      fTSP;
        DetTopCuPlate            fDetTopCuPlate;
        DetBottomCuPlate         fDetBottomCuPlate;
        Frame                    fFrame;
        LateralDummy             fLateralDummy;
        TopDummy                 fTopDummy;
        Gaps                     fGaps;

        PileDetector             fPileDetector;
        BDPTDetector             fBDPTDetector;
        BDPTDetector_PhaseI      fBDPTDetector_PhaseI;
        BDPTDetector_PhaseI_SameTowers      fBDPTDetector_PhaseI_SameTowers;
        BDPTDetector_PhaseI_PassiveShield      fBDPTDetector_PhaseI_PassiveShield;
        CuoreLikeDetector        fCuoreLikeDetector;
        Cuore1x2Detector         fCuore1x2Detector;
        CanfrancLikeDetector     fCanfrancLikeDetector;
        CuoreDetector            fCuoreDetector;

        void Initialize();

    protected:
        AgataGeometricParameters();
    public:
        static AgataGeometricParameters* GetInstance();
        ~AgataGeometricParameters();

        const MuonVeto                 GetMuonVeto()const                 { return fMuonVeto;                 };
        const RealisticMuonVeto        GetRealisticMuonVeto()const        { return fRealisticMuonVeto;        };
        const CalibrationSource        GetCalibrationSource()const        { return fCalibrationSource;        };
        const Polyethylene             GetPolyethylene()const             { return fPolyethylene;             };
        const BoricAcid                GetBoricAcid()const                { return fBoricAcid;                };
        const ExternalLead             GetExternalLead()const             { return fExternalLead;             };
        const FirstRadiationShield     Get1stRadiationShield()const       { return fFirstRadiationShield;     };
        const Vacuum                   GetVacuum()const                   { return fVacuum;                   };
        const SecondRadiationShield    Get2ndRadiationShield()const       { return fSecondRadiationShield;    };
        const SuperInsulation2ndShield GetSuperInsulation2ndShield()const { return fSuperInsulation2ndShield; };
        const ThirdRadiationShield     Get3rdRadiationShield()const       { return fThirdRadiationShield;     };
        const SuperInsulation3rdShield GetSuperInsulation3rdShield()const { return fSuperInsulation3rdShield; };
        const FourthRadiationShield    Get4thRadiationShield()const       { return fFourthRadiationShield;    };
        const CuBeJoints               GetCuBeJoints()const               { return fCuBeJoints;               };
        const RomanLead                GetRomanLead()const                { return fRomanLead;                };
        const SteelRods                GetSteelRods()const                { return fSteelRods;                };
        const FifthRadiationShield     Get5thRadiationShield()const       { return fFifthRadiationShield;     };
        const SixthRadiationShield     Get6thRadiationShield()const       { return fSixthRadiationShield;     };
        const InternalTopPb            GetInternalTopPb()const            { return fInternalTopPb;            };
        const TSP                      GetTSP()const                      { return fTSP;                      };
        const DetTopCuPlate            GetDetTopCuPlate()const            { return fDetTopCuPlate;            };
        const DetBottomCuPlate         GetDetBottomCuPlate()const         { return fDetBottomCuPlate;         };
        const Frame                    GetFrame()const                    { return fFrame;                    };
        const LateralDummy             GetLateralDummy()const             { return fLateralDummy;             };
        const TopDummy                 GetTopDummy()const                 { return fTopDummy;                 };
        const Gaps                     GetGaps()const                     { return fGaps;                     };
        const PileDetector             GetPileDetector()const             { return fPileDetector;             };
        const BDPTDetector             GetBDPTDetector()const             { return fBDPTDetector;             };
        const CuoreLikeDetector        GetCuoreLikeDetector()const        { return fCuoreLikeDetector;        };
        const Cuore1x2Detector         GetCuore1x2Detector()const         { return fCuore1x2Detector;         };
        const CanfrancLikeDetector     GetCanfrancLikeDetector()const     { return fCanfrancLikeDetector;     };
        const CuoreDetector            GetCuoreDetector()const            { return fCuoreDetector;            };
        const BDPTDetector_PhaseI      GetBDPTDetector_PhaseI()const      { return fBDPTDetector_PhaseI;      };
        const BDPTDetector_PhaseI_SameTowers      GetBDPTDetector_PhaseI_SameTowers()const      { return fBDPTDetector_PhaseI_SameTowers;      };
        const BDPTDetector_PhaseI_PassiveShield      GetBDPTDetector_PhaseI_PassiveShield()const      { return fBDPTDetector_PhaseI_PassiveShield;      };

};

#endif
