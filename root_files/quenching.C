void quenching(){

TFile *f_el = TFile::Open("../Resultats/output_gamma.root");
TFile *f_alph = TFile::Open("../Resultats/output_alpha.root");
TTree *Optical_tree_el = (TTree*)f_el->Get("Optical");
TTree *Optical_tree_alph = (TTree*)f_alph->Get("Optical");

TCanvas *c1 = new TCanvas("c1", "LY");
TCanvas *c2 = new TCanvas("c2", "light/heat");

TH1* h1 = new TH1I("h1", "e- Yield [kev/MeV]", 100.0, 0.0, 0.0);
TH1* h2 = new TH1I("h2", "alpha Yield [kev/MeV]", 100.0, 0.0, 0.0);
TGraph* g1el = new TGraph();
TGraph* g2el = new TGraph();
TGraph* g1alph = new TGraph();
TGraph* g2alph = new TGraph();

int scintillated_el;
float E_dep_event_LMO_el;
float E_dep_eV_el;
int detected_el;
vector<float>* detected_wavelength_LD1_el = nullptr;

int scintillated_alph;
float E_dep_event_LMO_alph;
float E_dep_eV_alph;
int detected_alph;
vector<float>* detected_wavelength_LD1_alph = nullptr;


Optical_tree_el->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO_el);
Optical_tree_el->SetBranchAddress("detected_wavelength_LD1", &detected_wavelength_LD1_el);
Optical_tree_el->SetBranchAddress("scintillation_LMO", &scintillated_el);
Optical_tree_el->SetBranchAddress("detected_LD1", &detected_el);
Optical_tree_alph->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO_alph);
Optical_tree_alph->SetBranchAddress("detected_wavelength_LD1", &detected_wavelength_LD1_alph);
Optical_tree_alph->SetBranchAddress("scintillation_LMO", &scintillated_alph);
Optical_tree_alph->SetBranchAddress("detected_LD1", &detected_alph);


// electron
for (int i = 0; i < Optical_tree_el->GetEntries(); i++)
{
    Optical_tree_el->GetEntry(i);
    if (detected_wavelength_LD1_el->size() != 0){
        E_dep_eV_el = 0;


        for(int j=0;j<(detected_wavelength_LD1_el->size());j++)
        {
            E_dep_eV_el += (1240 / detected_wavelength_LD1_el->at(j));
        }

        h1->Fill(E_dep_eV_el/E_dep_event_LMO_el);
    }
    if (E_dep_event_LMO_el>50){
        g1el->AddPoint(E_dep_event_LMO_el, detected_el);
        g2el->AddPoint(E_dep_event_LMO_el, E_dep_eV_el/E_dep_event_LMO_el);
    }
}

// alpha

for (int i = 0; i < Optical_tree_alph->GetEntries(); i++)
{
    Optical_tree_alph->GetEntry(i);
    if (detected_wavelength_LD1_alph->size() != 0){
        E_dep_eV_alph = 0;


        for(int j=0;j<(detected_wavelength_LD1_alph->size());j++)
        {
            E_dep_eV_alph += (1240 / detected_wavelength_LD1_alph->at(j));
        }

        h2->Fill(E_dep_eV_alph/E_dep_event_LMO_alph);
    }
    if (E_dep_event_LMO_alph>50){
        g1alph->AddPoint(E_dep_event_LMO_alph, detected_alph);
        g2alph->AddPoint(E_dep_event_LMO_alph, E_dep_eV_alph/E_dep_event_LMO_alph);
    }
}

c1->DivideSquare(2);
c1->SetWindowSize(950, 450);
c1->cd(1);
h1->Draw();

c1->cd(2);
h2->Draw();

c2->DivideSquare(2);
c2->SetWindowPosition(0,505);
c2->SetWindowSize(950, 450);
c2->cd(1);
g1el->SetMarkerStyle(20);
g1alph->SetMarkerStyle(20);
TMultiGraph *mg1 = new TMultiGraph();
mg1->Add(g1el);
mg1->Add(g1alph);
mg1->GetYaxis()->SetTitle("Photons detected");
mg1->GetXaxis()->SetTitle("Energy [keV]");
mg1->Draw("APPMC");
c2->cd(2);
g2el->SetMarkerStyle(20);
g2alph->SetMarkerStyle(20);
TMultiGraph *mg2 = new TMultiGraph();
mg2->Add(g2el);
mg2->Add(g2alph);
mg2->GetYaxis()->SetTitle("LY [keV/MeV]");
mg2->GetXaxis()->SetTitle("Energy [keV]");
mg2->Draw("APPMC");

}