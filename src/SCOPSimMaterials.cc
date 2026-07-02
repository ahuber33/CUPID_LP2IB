/**
 * @file SCOPSimMaterials.cc
 * @brief Implementation of the Materials class for the Optical
 * simulation.
 *
 * [TO DO]
 *
 * @author Arnaud HUBER <huber@lp2ib.in2p3.fr>
 * @date 2026
 */

#include "SCOPSimMaterials.hh"
#include "G4OpticalParameters.hh"

using namespace CLHEP;

const G4String SCOPSimMaterials::path = "../optical_input/";

SCOPSimMaterials::SCOPSimMaterials() : fMaterialsList{} {

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
    G4Element* elSe = new G4Element( "Selenium",   "Se", 34., 78.96      * g/mole );
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

    G4Material* Vacuum   = new G4Material("Vacuum", 1., 1.01*g/mole, universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal );
    G4Material* VacuumWorld = new G4Material("VacuumWorld", 1., 1. * g/mole, 1.e-20 * g/cm3, kStateGas, 0.1 * kelvin, 1.e-20 * bar);
    G4Material* Germanium = new G4Material( elGe->GetName(), elGe->GetZ(), elGe->GetAtomicMassAmu() * g/mole, 5.323  * g/cm3 );
    G4Material* Silicon   = new G4Material( elSi->GetName(), elSi->GetZ(), elSi->GetAtomicMassAmu() * g/mole, 2.3290 * g/cm3 );
    G4Material* Copper = new G4Material( elCu->GetName(), elCu->GetZ(), elCu->GetAtomicMassAmu() * g/mole, 8.935  * g/cm3 );
    G4Material* Teflon = G4NistManager::Instance()->FindOrBuildMaterial("G4_TEFLON");
    Teflon->SetName("Teflon");
    G4Material* Mylar = G4NistManager::Instance()->FindOrBuildMaterial("G4_MYLAR");
    Mylar->SetName("Mylar");

    // ------------------
    // Compound materials
    // ------------------

    // Li2MoO4 //
    auto Li2MoO4 = new G4Material("Li2MoO4", 3.07*g/cm3, 3);
    Li2MoO4->AddElement( elLi, 2);
    Li2MoO4->AddElement( elMo, 1);
    Li2MoO4->AddElement( elO, 4);

    // SiO //
    auto SiO = new G4Material( "SiO", 2.13*g/cm3, 2 );
    SiO->AddElement( elSi, 1);
    SiO->AddElement( elO,  1);

    // ------------------
    // Optical parameters
    // ------------------

    G4bool scintByParticleType = false;

    G4OpticalParameters::Instance()->SetScintByParticleType(scintByParticleType); // different scintillation for each interacting particle

    // Vacuum //
    std::vector<G4double> energy_vacuum = {1.5 * eV, 5.0 * eV};
    std::vector<G4double> refractive_index_vacuum = {1.0, 1.0};
    std::vector<G4double> absorption_vacuum = {100000. *m, 100000. *m};

    auto mptVacuum = new G4MaterialPropertiesTable();
    mptVacuum->AddProperty("RINDEX", energy_vacuum, refractive_index_vacuum);
    mptVacuum->AddProperty("ABSLENGTH", energy_vacuum, absorption_vacuum);
    Vacuum->SetMaterialPropertiesTable(mptVacuum);

    // LMO //
    SetProperty("EMISSION", "LMO_EMISSION_eV.txt");
    SetProperty("ABSORPTION", "LMO_ABSORPTION_eV_mm.txt");
    SetProperty("RINDEX", "LMO_RINDEX_eV.txt");
    SetProperty("ELECTRONLY", "LMO_ELECTRONLY_eV_photon.txt");
    SetProperty("ALPHALY", "LMO_ALPHALY_eV_photon.txt");

    auto mptLi2MoO4 = new G4MaterialPropertiesTable();
    mptLi2MoO4->AddProperty("RINDEX", RINDEX_energy, RINDEX_var);
    mptLi2MoO4->AddProperty("ABSLENGTH", ABSORPTION_energy, ABSORPTION_var);
    if (scintByParticleType){
        mptLi2MoO4->AddProperty("ELECTRONSCINTILLATIONYIELD", ELECTRONLY_energy, ELECTRONLY_var, 2);
        mptLi2MoO4->AddProperty("ALPHASCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2); // quenching
        mptLi2MoO4->AddProperty("TRITONSCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2);
        mptLi2MoO4->AddProperty("IONSCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2);
        mptLi2MoO4->AddProperty("PROTONSCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2);
        mptLi2MoO4->AddProperty("DEUTERONSCINTILLATIONYIELD", ALPHALY_energy, ALPHALY_var, 2);
    }
    else {
        mptLi2MoO4->AddConstProperty("SCINTILLATIONYIELD", 1050 / MeV);
        Li2MoO4->GetIonisation()->SetBirksConstant(0.0016 * cm / MeV);
    }

    mptLi2MoO4->AddProperty("SCINTILLATIONCOMPONENT1", EMISSION_energy, EMISSION_var);
    mptLi2MoO4->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptLi2MoO4->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    mptLi2MoO4->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 84.5 * us); // https://doi.org/10.1140/epjc/s10052-019-7242-1
    Li2MoO4->SetMaterialPropertiesTable(mptLi2MoO4);

    // Germanium //
    SetProperty("ABSORPTION", "Ge_ABSORPTION_eV_mm.txt");
    SetProperty("RINDEX", "Ge_RINDEX_eV.txt");

    auto mptGermanium = new G4MaterialPropertiesTable();
    mptGermanium->AddProperty("RINDEX", RINDEX_energy, RINDEX_var);
    mptGermanium->AddProperty("ABSLENGTH", ABSORPTION_energy, ABSORPTION_var);
    Germanium->SetMaterialPropertiesTable(mptGermanium);

    // Silicon //
    SetProperty("ABSORPTION", "Si_ABSORPTION_eV_mm.txt");
    SetProperty("RINDEX", "Si_RINDEX_eV.txt");

    auto mptSilicon = new G4MaterialPropertiesTable();
    mptSilicon->AddProperty("RINDEX", RINDEX_energy, RINDEX_var);
    mptSilicon->AddProperty("ABSLENGTH", ABSORPTION_energy, ABSORPTION_var);
    Silicon->SetMaterialPropertiesTable(mptSilicon);

    // Copper //
    SetProperty("ABSORPTION", "Cu_ABSORPTION_eV_mm.txt");
    SetProperty("RINDEX", "Cu_RINDEX_eV.txt");

    auto mptCopper = new G4MaterialPropertiesTable();
    mptCopper->AddProperty("RINDEX", RINDEX_energy, RINDEX_var);
    mptCopper->AddProperty("ABSLENGTH", ABSORPTION_energy, ABSORPTION_var);
    Copper->SetMaterialPropertiesTable(mptCopper);

    // Teflon //
    SetProperty("RINDEX", "PTFE_RINDEX_eV.txt");

    auto mptTeflon= new G4MaterialPropertiesTable();
    /* double multiplier = 1.1;

    for (auto &element : RINDEX_var) {
        element *= multiplier;
    } */
    mptTeflon->AddProperty("RINDEX", RINDEX_energy, RINDEX_var);
    Teflon->SetMaterialPropertiesTable(mptTeflon);

    // Add to Material List
    fMaterialsList.push_back(Vacuum);
    fMaterialsList.push_back(VacuumWorld);
    fMaterialsList.push_back(Li2MoO4);
    fMaterialsList.push_back(Germanium);
    fMaterialsList.push_back(Silicon);
    fMaterialsList.push_back(Copper);
    fMaterialsList.push_back(Teflon);
    fMaterialsList.push_back(Mylar);
}

SCOPSimMaterials::~SCOPSimMaterials() {}

void SCOPSimMaterials::SetProperty(const G4String propName, const G4String propFile) {

    if (propName=="EMISSION"){ // READ EMISSION SPECTRUM
        file = path + propFile;

        ReadEMISSION.clear();
        EMISSION_energy.clear();
        EMISSION_var.clear();

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
    }
    if (propName=="ABSORPTION"){ // READ ABSORPTION SPECTRUM
        file = path + propFile;

        ReadABSORPTION.clear();
        ABSORPTION_energy.clear();
        ABSORPTION_var.clear();

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
    }
    if (propName=="RINDEX"){ // READ RINDEX
        file = path + propFile;

        ReadRINDEX.clear();
        RINDEX_energy.clear();
        RINDEX_var.clear();

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
    if (propName=="ELECTRONLY"){ // READ ELECTRONLY
        file = path + propFile;

        ReadELECTRONLY.clear();
        ELECTRONLY_energy.clear();
        ELECTRONLY_var.clear();

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
    }
    if (propName=="ALPHALY"){ // READ ALPHALY
        file = path + propFile;

        ReadALPHALY.clear();
        ALPHALY_energy.clear();
        ALPHALY_var.clear();

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

}

G4Material *SCOPSimMaterials::getMaterial(const char *materialId) {
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

void SCOPSimMaterials::printMaterialProperties(G4Material *material) {
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

void SCOPSimMaterials::printMaterialProperties(
    const char *materialId) {
    G4Material *material = getMaterial(materialId);
    if (material == NULL)
        return;
    printMaterialProperties(material);
}

SCOPSimMaterials *SCOPSimMaterials::getInstance() {
    static G4ThreadLocal SCOPSimMaterials* instance = nullptr;
    if (!instance) {
        instance = new SCOPSimMaterials();
    }
    return instance;
}

G4double SCOPSimMaterials::wavelengthNmToEnergy(G4double wavelength) {
    G4double hc = 1239.84193;
    return hc / wavelength * eV; // E (eV) = 1239.8 / l (nm)
}