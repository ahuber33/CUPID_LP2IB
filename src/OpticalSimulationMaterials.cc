/**
 * @file OpticalSimulationMaterials.cc
 * @brief Implementation of the Materials class for the Optical
 * simulation.
 *
 * [TO DO]
 *
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 */

#include "OpticalSimulationMaterials.hh"
#include "G4OpticalParameters.hh"

using namespace CLHEP;

const G4String OpticalSimulationMaterials::path = "../simulation_input_files/";
const G4String OpticalSimulationMaterials::path2 = "../optical_input/";

OpticalSimulationMaterials::OpticalSimulationMaterials() : fMaterialsList{} {

    // #######################################################################################################################################
    // #######################################################################################################################################

    // ███████╗░█████╗░██╗░░██╗███████╗  ██╗░░░██╗░█████╗░░█████╗░██╗░░░██╗██╗░░░██╗███╗░░░███╗
    // ██╔════╝██╔══██╗██║░██╔╝██╔════╝  ██║░░░██║██╔══██╗██╔══██╗██║░░░██║██║░░░██║████╗░████║
    // █████╗░░███████║█████═╝░█████╗░░  ╚██╗░██╔╝███████║██║░░╚═╝██║░░░██║██║░░░██║██╔████╔██║
    // ██╔══╝░░██╔══██║██╔═██╗░██╔══╝░░  ░╚████╔╝░██╔══██║██║░░██╗██║░░░██║██║░░░██║██║╚██╔╝██║
    // ██║░░░░░██║░░██║██║░╚██╗███████╗  ░░╚██╔╝░░██║░░██║╚█████╔╝╚██████╔╝╚██████╔╝██║░╚═╝░██║
    // ╚═╝░░░░░╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝  ░░░╚═╝░░░╚═╝░░╚═╝░╚════╝░░╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝

    // Be careful of this vacuum definition.  This is only used to define
    // a refractive index so that the detector boundaries are defined.

    auto VacuumWorld =
        new G4Material("VacuumWorld", 1., 1. * g / mole, 1.e-20 * g / cm3,
                       kStateGas, 0.1 * kelvin, 1.e-20 * bar);

    fMaterialsList.push_back(VacuumWorld);

    // #######################################################################################################################################
    // #######################################################################################################################################

    // ███████╗░░░░░██╗░░░░░░██████╗░░░███╗░░██████╗░
    // ██╔════╝░░░░░██║░░░░░░╚════██╗░████║░░╚════██╗
    // █████╗░░░░░░░██║█████╗░░███╔═╝██╔██║░░░░███╔═╝
    // ██╔══╝░░██╗░░██║╚════╝██╔══╝░░╚═╝██║░░██╔══╝░░
    // ███████╗╚█████╔╝░░░░░░███████╗███████╗███████╗
    // ╚══════╝░╚════╝░░░░░░░╚══════╝╚══════╝╚══════╝

    auto EJ212 =
        new G4Material("EJ212",
                       1.032 * g / cm3, // 1.053
                       2, kStateSolid, 273.15 * kelvin, 1.0 * atmosphere);

    EJ212->AddElement(G4NistManager::Instance()->FindOrBuildElement("H"), 10);
    EJ212->AddElement(G4NistManager::Instance()->FindOrBuildElement("C"), 9);

    {
        Read.clear();
        Readabsorb.clear();
        Readindex.clear();
        Emission_Energy.clear();
        Emission_Ratio.clear();
        Absorption_Energy.clear();
        Absorption_Long.clear();
        Index_Energy.clear();
        Index_Value.clear();

        auto EJ212MPT = new G4MaterialPropertiesTable();

        // Read primary emission spectrum
        file = path + "EJ-212.cfg";

        Read.open(file);
        if (Read.is_open()) {
            while (!Read.eof()) {
                Read >> pWavelength >> filler >> var;
                // G4cout << "Wavelength = " << 1240./pWavelength << " &
                // emission = "<< var << G4endl;
                Emission_Energy.push_back((1240. / pWavelength) *
                                          eV); // convert wavelength to eV
                Emission_Ratio.push_back(var);
            }
        } else {
            G4cout << "Error opening file: " << file << G4endl;
        }
        Read.close();

        // // Read primary bulk absorption

        file = path + "PSTBulkAbsorb_reverse.cfg";

        Readabsorb.open(file);
        if (Readabsorb.is_open()) {
            while (!Readabsorb.eof()) {
                Readabsorb >> pWavelength >> filler >> var;
                //G4cout << "Wavelength = " << pWavelength << " & absorption = "<< var << " & filler = " << filler << "."  <<G4endl;
                Absorption_Energy.push_back((1240. / pWavelength) * eV);
                Absorption_Long.push_back(1. * var * m);
            }
        } else

            G4cout << "Error opening file: " << file << G4endl;

        Readabsorb.close();

        // Read WLS absorption
        //
        // wlsAbEntries = 0;
        // std::ifstream ReadWLSa;
        // G4String WLSabsorb = path+"UPS923.cfg";
        //
        // ReadWLSa.open(WLSabsorb);
        // if (ReadWLSa.is_open()){
        //  while(!ReadWLSa.eof()){
        // 	 G4String filler;
        // 	 ReadWLSa>>pWavelength>>filler>>wlsabsorblength;
        // 	 wlsEnergy[wlsAbEntries] = (1240/pWavelength)*eV;
        //
        //
        // 	 if (wlsAbEntries < 200){
        // wlsAbsorb[wlsAbEntries] = wlsabsorblength*m;
        // 	 }
        // 	 else{
        // wlsAbsorb[wlsAbEntries] = wlsabsorblength*m;
        // 	 }
        //
        // 	 wlsAbEntries++;
        //  }
        // }
        // else
        //  {
        // 	 G4cout << "Error opening file: " << WLSabsorb << G4endl;
        //  }
        //
        // ReadWLSa.close();

        // Read WLS emission
        // wlsEmEntries = 0;
        // std::ifstream ReadWLSe;
        // G4String WLSemit = path+"full_popop_emission.cfg";
        // ReadWLSe.open(WLSemit);
        // if(ReadWLSe.is_open()){
        //  while(!ReadWLSe.eof()){
        // 	 G4String filler;
        // 	 ReadWLSe >> pWavelength >> filler >> wlsEmit[wlsEmEntries];
        // 	 wlsEnergy[wlsEmEntries] = (1240/pWavelength)*eV;
        // 	 wlsEmEntries++;
        //  }
        // }
        // else
        //  G4cout << "Error opening file: " << WLSemit << G4endl;
        // ReadWLSe.close();

        // Read scintillator refractive index

        // G4String ref_index_emit = path+"PST_ref_index.dat";
        file = path + "PS_index_geant_reverse.cfg";

        Readindex.open(file);
        if (Readindex.is_open()) {
            while (!Readindex.eof()) {
                Readindex >> pWavelength >> filler >> var;
                // ref_index_value[ref_index_Entries]=1.59;
                Index_Energy.push_back((1240 / pWavelength) * eV);
                Index_Value.push_back(var);
                // EJ212_Index_Value.push_back(1.59);
            }
        } else
            G4cout << "Error opening file: " << file << G4endl;
        Readindex.close();

        // Now apply the properties table

        // scintMPT->AddProperty("WLSCOMPONENT",wlsEnergy,wlsEmit,wlsEmEntries);
        // scintMPT->AddProperty("WLSABSLENGTH",wlsEnergy,wlsAbsorb,wlsAbEntries);
        // // the WLS absorption spectrum
        // scintMPT->AddConstProperty("WLSTIMECONSTANT",12*ns);
        EJ212MPT->AddProperty("RINDEX", Index_Energy, Index_Value);

        EJ212MPT->AddProperty("ABSLENGTH", Absorption_Energy,
                              Absorption_Long); // the bulk absorption spectrum
        EJ212MPT->AddProperty("SCINTILLATIONCOMPONENT1", Emission_Energy,
                              Emission_Ratio);
        // scintMPT->AddProperty("SCINTILLATIONCOMPONENT1",scintEnergy,scintEmit,scintEntries);
        // scintMPT->AddProperty("SCINTILLATIONCOMPONENT2",scintEnergy,scintEmit,scintEntries);
        // // if slow component

        // G4double efficiency = 1.0;
        // scintMPT->AddConstProperty("EFFICIENCY",efficiency);

        G4double electron[2] = {10000.*1e-6, 10000.*100}; //e- yield factor
        G4double energy_LY[2] = {1. * eV, 100. * MeV};

        EJ212MPT->AddProperty("ELECTRONSCINTILLATIONYIELD", energy_LY, electron, 2);
        // scintMPT->AddConstProperty("ALPHASCINTILLATIONYIELD",0.01*lightyield/MeV);
        Res = 1;
        EJ212MPT->AddConstProperty("RESOLUTIONSCALE", Res);
        Fastconst = 2.1 * ns;
        EJ212MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", Fastconst);
        Slowconst = 10 * ns;
        EJ212MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2",
                                   Slowconst); // if slow component
        EJ212MPT->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
        EJ212MPT->AddConstProperty("SCINTILLATIONYIELD2", 0.0);

        EJ212->SetMaterialPropertiesTable(EJ212MPT);
        // scintillator->GetIonisation()->SetBirksConstant(0.0872*mm/MeV);
        // //0.126->base; 0.0872->article BiPO
        // scintillator->GetIonisation()->SetBirksConstant(0.25*mm/MeV); //
        // Choisi pour validation modÃ¨le avec LY 11737!!!
        // scintillator->GetIonisation()->SetBirksConstant(0.22*mm/MeV);
        // scintillator->GetIonisation()->SetBirksConstant(0.01*mm/MeV); // TEST
        // ELECTRONS !!! => Maxime
    }

    // printMaterialProperties(EJ212);
    fMaterialsList.push_back(EJ212);

    // #######################################################################################################################################
    // #######################################################################################################################################


    /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////// MATERIAL FOR CUPID //////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////

    // --------
    // Elements
    // --------
    //
    // Atomic weights taken from "Atomic weights of the elements 2013 (IUPAC technical report)
    // DOI: https://doi.org/10.1515/pac-2015-0305
    //
    //                                Name         Sym.  Z    Std atomic weight
    G4Element* elH  = new G4Element( "Hydrogen",   "H",  1.,  1.00794    * g/mole );
    G4Element* elHe = new G4Element( "Helium",     "He", 2.,  4.002602   * g/mole );
    G4Element* elLi = new G4Element( "Lithium",    "Li", 3.,  6.94       * g/mole );
    G4Element* elB  = new G4Element( "Boron",      "B",  5.,  10.811     * g/mole );
    G4Element* elBe = new G4Element( "Berillium",  "Be", 4.,  9.012182   * g/mole );
    G4Element* elC  = new G4Element( "Carbon",     "C",  6.,  12.011     * g/mole );
    G4Element* elN  = new G4Element( "Nitrogen",   "N",  7.,  14.01      * g/mole );
    G4Element* elO  = new G4Element( "Oxygen",     "O",  8.,  16.00      * g/mole );
    G4Element* elF  = new G4Element( "Fluorine",   "F",  9.,  18.9984032 * g/mole );
    G4Element* elAl = new G4Element( "Aluminum",   "Al", 13., 26.981539  * g/mole );
    G4Element* elSi = new G4Element( "Silicon",    "Si", 14., 28.085     * g/mole );
    G4Element* elFe = new G4Element( "Iron",       "Fe", 26., 55.847     * g/mole );
    G4Element* elCu = new G4Element( "Copper",     "Cu", 29., 63.55      * g/mole );
    G4Element* elGe = new G4Element( "Germanium",  "Ge", 32., 72.630     * g/mole );
    G4Element* elZn = new G4Element( "Zinc",       "Zn", 30., 65.38      * g/mole );
    G4Element* elSe = new G4Element( "Selenimu",   "Se", 34., 78.96      * g/mole );
    //G4Element* elMo = new G4Element( "Molybdenum", "Mo", 42., 95.96      * g/mole );
    G4Isotope* iso96Mo  = new G4Isotope( "97Mo",  42, 96,  95.91 * g/mole );
    G4Isotope* iso97Mo  = new G4Isotope( "97Mo",  42, 97,  96.91 * g/mole );
    G4Isotope* iso98Mo  = new G4Isotope( "98Mo",  42, 98,  97.91 * g/mole );
    G4Isotope* iso100Mo = new G4Isotope( "100Mo", 42, 100, 99.91 * g/mole );
    G4Element* elMo = new G4Element( "Molybdenum", "Mo", 4 );
    elMo->AddIsotope( iso96Mo,  0.001 );// ------------------------------------------------------
    elMo->AddIsotope( iso97Mo,  0.002 );// WARNING: These values are estimated by educated guess!
    elMo->AddIsotope( iso98Mo,  0.047 );// They will be updated onces ICP-MS data are available.
    elMo->AddIsotope( iso100Mo, 0.950 );// ------------------------------------------------------

    // -------------------
    // Elemental materials
    // -------------------


    G4Material* Vacuum   = new G4Material("Vacuum",
            1.,
            1.01*g/mole,
            universe_mean_density,// From PhyscialConstants.h
            kStateGas,
            2.73*kelvin,
            3.e-18*pascal );
    G4Material* Germanium = new G4Material( elGe->GetName(), elGe->GetZ(), elGe->GetAtomicMassAmu() * g/mole, 5.323  * g/cm3 );
    G4Material* Silicon   = new G4Material( elSi->GetName(), elSi->GetZ(), elSi->GetAtomicMassAmu() * g/mole, 2.3290 * g/cm3 );

    // ------------------
    // Compound materials
    // ------------------

    // Li2MoO4
    auto Li2MoO4 = new G4Material("Li2MoO4", 3.07*g/cm3, 3);
    Li2MoO4->AddElement( elLi, 2);
    Li2MoO4->AddElement( elMo, 1);
    Li2MoO4->AddElement( elO, 4);

    // SiO
    auto SiO = new G4Material( "SiO", 2.13*g/cm3, 2 );
    SiO->AddElement( elSi, 1);
    SiO->AddElement( elO,  1);

    // ------------------
    // Optical parameters
    // ------------------

    G4OpticalParameters::Instance()->SetScintByParticleType(true); //different scintillation for each interacting particle

    // Vacuum

    std::vector<G4double> energy_vacuum = {1.5 * eV, 5.0 * eV};
    std::vector<G4double> refractive_index_vacuum = {1.0, 1.0};
    std::vector<G4double> absorption_vacuum = {100. *m, 100. *m};

    auto mptVacuum = new G4MaterialPropertiesTable();
    mptVacuum->AddProperty("RINDEX", energy_vacuum, refractive_index_vacuum);
    mptVacuum->AddProperty("ABSLENGTH", energy_vacuum, absorption_vacuum);

    Vacuum->SetMaterialPropertiesTable(mptVacuum);

    // LMO

    {
        ReadEMISSION.clear();
        ReadABSORPTION.clear();
        ReadRINDEX.clear();
        ReadELECTRONLY.clear();
        ReadALPHALY.clear();
        EMISSION_energy.clear();
        EMISSION_var.clear();
        ABSORPTION_energy.clear();
        ABSORPTION_var.clear();
        RINDEX_energy.clear();
        RINDEX_var.clear();
        ELECTRONLY_energy.clear();
        ELECTRONLY_var.clear();
        ALPHALY_energy.clear();
        ALPHALY_var.clear();

        // READ EMISSION SPECTRUM
        file = path2 + "LMO_EMISSION_eV.txt";

        ReadEMISSION.open(file);
        if (ReadEMISSION.is_open()) {
            while (!ReadEMISSION.eof()) {
                ReadEMISSION >> energy >> filler >> var;
                EMISSION_energy.push_back(energy * eV);
                EMISSION_var.push_back(var);
            }
        } else {
            G4cout << "Error opening file: " << file << G4endl;
        }
        ReadEMISSION.close();

        // READ ABSORPTION SPECTRUM
        file = path2 + "LMO_ABSORPTION_eV_mm.txt";

        ReadABSORPTION.open(file);
        if (ReadABSORPTION.is_open()) {
            while (!ReadABSORPTION.eof()) {
                ReadABSORPTION >> energy >> filler >> var;
                ABSORPTION_energy.push_back(energy * eV);
                ABSORPTION_var.push_back(var * mm);
            }
        } else {
            G4cout << "Error opening file: " << file << G4endl;
        }
        ReadABSORPTION.close();

        // READ REFRACTIVE INDEX
        file = path2 + "LMO_RINDEX_eV.txt";

        ReadRINDEX.open(file);
        if (ReadRINDEX.is_open()) {
            while (!ReadRINDEX.eof()) {
                ReadRINDEX >> energy >> filler >> var;
                RINDEX_energy.push_back(energy * eV);
                RINDEX_var.push_back(var);
            }
        } else {
            G4cout << "Error opening file: " << file << G4endl;
        }
        ReadRINDEX.close();

        // READ ELECTRON LIGHT YIELD
        file = path2 + "LMO_ELECTRONLY_eV_photon.txt";

        ReadELECTRONLY.open(file);
        if (ReadELECTRONLY.is_open()) {
            while (!ReadELECTRONLY.eof()) {
                ReadELECTRONLY >> energy >> filler >> var;
                ELECTRONLY_energy.push_back(energy * eV);
                ELECTRONLY_var.push_back(var);
            }
        } else {
            G4cout << "Error opening file: " << file << G4endl;
        }
        ReadELECTRONLY.close();

        // READ ALPHA LIGHT YIELD
        file = path2 + "LMO_ALPHALY_eV_photon.txt";

        ReadALPHALY.open(file);
        if (ReadALPHALY.is_open()) {
            while (!ReadALPHALY.eof()) {
                ReadALPHALY >> energy >> filler >> var;
                ALPHALY_energy.push_back(energy * eV);
                ALPHALY_var.push_back(var);
            }
        } else {
            G4cout << "Error opening file: " << file << G4endl;
        }
        ReadALPHALY.close();
    }

    auto mptLi2MoO4 = new G4MaterialPropertiesTable();
    mptLi2MoO4->AddProperty("RINDEX", RINDEX_energy, RINDEX_var);
    mptLi2MoO4->AddProperty("ABSLENGTH", ABSORPTION_energy, ABSORPTION_var);

    mptLi2MoO4->AddProperty("ALPHASCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2);
    mptLi2MoO4->AddProperty("TRITONSCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2);
    mptLi2MoO4->AddProperty("ELECTRONSCINTILLATIONYIELD", ELECTRONLY_energy, ELECTRONLY_var, 2);
    mptLi2MoO4->AddProperty("IONSCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2);
    mptLi2MoO4->AddProperty("PROTONSCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2);
    mptLi2MoO4->AddProperty("DEUTERONSCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2);

    mptLi2MoO4->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptLi2MoO4->AddProperty("SCINTILLATIONCOMPONENT1", EMISSION_energy, EMISSION_var);
    mptLi2MoO4->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    mptLi2MoO4->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 84.5 * us); // https://doi.org/10.1140/epjc/s10052-019-7242-1

    Li2MoO4->SetMaterialPropertiesTable(mptLi2MoO4);


    // Germanium LD

    {
        ReadEMISSION.clear();
        ReadABSORPTION.clear();
        ReadRINDEX.clear();
        ReadELECTRONLY.clear();
        ReadALPHALY.clear();
        EMISSION_energy.clear();
        EMISSION_var.clear();
        ABSORPTION_energy.clear();
        ABSORPTION_var.clear();
        RINDEX_energy.clear();
        RINDEX_var.clear();
        ELECTRONLY_energy.clear();
        ELECTRONLY_var.clear();
        ALPHALY_energy.clear();
        ALPHALY_var.clear();

        // READ ABSORPTION SPECTRUM
        file = path2 + "LD_ABSORPTION_eV_cm.txt";

        ReadABSORPTION.open(file);
        if (ReadABSORPTION.is_open()) {
            while (!ReadABSORPTION.eof()) {
                ReadABSORPTION >> energy >> filler >> var;
                ABSORPTION_energy.push_back(energy * eV);
                ABSORPTION_var.push_back(var * mm);
            }
        } else {
            G4cout << "Error opening file: " << file << G4endl;
        }
        ReadABSORPTION.close();

        // READ REFRACTIVE INDEX
        file = path2 + "LD_RINDEX_eV.txt";

        ReadRINDEX.open(file);
        if (ReadRINDEX.is_open()) {
            while (!ReadRINDEX.eof()) {
                ReadRINDEX >> energy >> filler >> var;
                RINDEX_energy.push_back(energy * eV);
                RINDEX_var.push_back(var);
            }
        } else {
            G4cout << "Error opening file: " << file << G4endl;
        }
        ReadRINDEX.close();
    }

    auto mptGermanium = new G4MaterialPropertiesTable();
    mptGermanium->AddProperty("RINDEX", RINDEX_energy, RINDEX_var);
    mptGermanium->AddProperty("ABSLENGTH", ABSORPTION_energy, ABSORPTION_var);

    Germanium->SetMaterialPropertiesTable(mptGermanium);

    // SiO coating
    // https://doi.org/10.1051/epjconf/20136504003
    // Erin was using 1.94
    
    std::vector<G4double> refractive_index_coating = {2.48, 2.48}; // 2.48
    std::vector<G4double> energy_coating = {1.5 * eV, 5.0 * eV};
    std::vector<G4double> absorption_coating = {10. *cm, 10. *cm}; // IDK IDC?


    auto mptSiO = new G4MaterialPropertiesTable();
    mptSiO->AddProperty("RINDEX", energy_coating, refractive_index_coating);
    mptSiO->AddProperty("ABSLENGTH", energy_coating, absorption_coating);

    SiO->SetMaterialPropertiesTable(mptSiO);


    fMaterialsList.push_back(Vacuum);
    fMaterialsList.push_back(Li2MoO4);
    fMaterialsList.push_back(Germanium);
    fMaterialsList.push_back(SiO);


    // #######################################################################################################################################
    // #######################################################################################################################################
}

OpticalSimulationMaterials::~OpticalSimulationMaterials() {}

G4Material *OpticalSimulationMaterials::getMaterial(const char *materialId) {
    for (int i = 0; i < (int)fMaterialsList.size(); i++) {
        if (fMaterialsList[i]->GetName() == materialId) {
            G4cout << "Material : " << materialId << " found" << G4endl;
            return fMaterialsList[i];
        }
    }
    G4cout << "ERROR: Materials::getMaterial material " << materialId
           << " not found." << G4endl;
    return NULL;
}

void OpticalSimulationMaterials::printMaterialProperties(G4Material *material) {
    std::cout << "\nMaterial name: " << material->GetName() << std::endl;
    G4MaterialPropertiesTable *mpt = material->GetMaterialPropertiesTable();
    if (!mpt)
        return;

    std::vector<G4double> fOpticalPhotonWavelength = {
        360, 400., 440., 480., 520., 560., 600., 640., 680., 720., 760};

    // Print photon wavelengths
    std::cout << std::left << std::setw(TAB_COLUMN_1) << "PHOTON_WAVELEGTH, nm";
    for (G4int i = 0; i < (G4int)fOpticalPhotonWavelength.size(); i++) {
        std::cout << std::left << std::setw(TAB_COLUMN)
                  << fOpticalPhotonWavelength[i];
    }

    std::cout << std::endl;

    // Print photon energy
    std::cout << std::left << std::setw(TAB_COLUMN_1) << "PHOTON_ENERGY, eV";
    for (G4int i = 0; i < (G4int)fOpticalPhotonWavelength.size(); i++) {
        std::cout << std::left << std::setw(TAB_COLUMN)
                  << wavelengthNmToEnergy(fOpticalPhotonWavelength[i]) / eV;
    }
    std::cout << std::endl;

    // Print material properties
    std::vector<G4String> propertyNames = mpt->GetMaterialPropertyNames();

    // Replaced in Geant4 v.11 with const
    // std::vector<G4MaterialPropertyVector*>& GetProperties() const const
    // std::map<G4int, G4MaterialPropertyVector*, std::less<G4int> >* pMapNew =
    // mpt->GetPropertyMap();
    std::vector<G4String> materialPropertiesNames =
        mpt->GetMaterialPropertyNames();

    for (G4String propertyName : materialPropertiesNames) {
        G4MaterialPropertyVector *property = mpt->GetProperty(propertyName);
        if (!property)
            continue;

        // Print property name
        std::cout << std::left << std::setw(TAB_COLUMN_1) << propertyName;
        // Print property values
        for (G4int i = 0; i < (G4int)fOpticalPhotonWavelength.size(); i++) {
            G4bool b;
            G4double value = property->GetValue(
                wavelengthNmToEnergy(fOpticalPhotonWavelength[i]), b);
            std::cout << std::left << std::setw(TAB_COLUMN) << value;
        }

        std::cout << std::endl;
    }

    // Print material constant properties
    std::vector<G4String> constPropertyNames =
        mpt->GetMaterialConstPropertyNames();
    for (G4String constPropertyName : constPropertyNames) {
        if (!mpt->ConstPropertyExists(constPropertyName))
            continue;
        // Print property name and value
        G4double constPropertyValue = mpt->GetConstProperty(constPropertyName);
        std::cout << std::left << std::setw(TAB_COLUMN_1) << constPropertyName
                  << constPropertyValue << std::endl;
    }
}

void OpticalSimulationMaterials::printMaterialProperties(
    const char *materialId) {
    G4Material *material = getMaterial(materialId);
    if (material == NULL)
        return;
    printMaterialProperties(material);
}

OpticalSimulationMaterials *OpticalSimulationMaterials::getInstance() {
    static G4ThreadLocal OpticalSimulationMaterials* instance = nullptr;
    if (!instance) {
        instance = new OpticalSimulationMaterials();
    }
    return instance;
}

G4double OpticalSimulationMaterials::wavelengthNmToEnergy(G4double wavelength) {
    G4double hc = 1239.84193;
    return hc / wavelength * eV; // E (eV) = 1239.8 / l (nm)
}