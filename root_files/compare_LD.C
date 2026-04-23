void compare_LD(){

    

TFile *f = TFile::Open("../Resultats");
TTree *Input_tree = (TTree*)f->Get("Input");
TTree *LMO_tree = (TTree*)f->Get("LMO");
TTree *Optical_tree = (TTree*)f->Get("Optical");

TCanvas *c1 = new TCanvas("c1", "LD1 Yield [photons/MeV]");
TCanvas *c2 = new TCanvas("c2", "LD2 Yield [photons/MeV]");
TCanvas *c3 = new TCanvas("c3", "LD2 Yield / LD1 Yield");

TH1* h1 = new TH1I("h1", "LD1 Yield [photons/MeV]", 50.0, 0.0, 0.0);
TH1* h2 = new TH1I("h2", "LD2 Yield [photons/MeV]", 50.0, 0.0, 0.0);
TH1* h3 = new TH1I("h3", "LD2 Yield / LD1 Yield", 50.0, 0.0, 0.0);

int scintillated;
float E_dep_event_LMO;
float E_dep_eV;
float yield;
int detected_LD1;
int detected_LD2;
int escaped;
int absorbed;
int reemitted;
vector<double>* birth_wavelength = nullptr;
vector<double>* detected_wavelength = nullptr;
vector<double> energy;
double xmin;
double xmax;
double ratio;


LMO_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO);
LMO_tree->SetBranchAddress("energy", &energy);
Optical_tree->SetBranchAddress("birth_wavelength", &birth_wavelength);
Optical_tree->SetBranchAddress("detected_wavelength", &detected_wavelength);
Optical_tree->SetBranchAddress("scintillation_LMO", &scintillated);
Optical_tree->SetBranchAddress("detected_LD1", &detected_LD1);
Optical_tree->SetBranchAddress("detected_LD2", &detected_LD2);
Optical_tree->SetBranchAddress("escaped", &escaped);
Optical_tree->SetBranchAddress("bulk_abs_LMO", &absorbed);
Optical_tree->SetBranchAddress("reemission_LMO", &reemitted);

for (int i = 0; i < Optical_tree->GetEntries(); i++)
{
    Optical_tree->GetEntry(i);

    h1->Fill(detected_LD1);
    h2->Fill(detected_LD2);
    ratio = (float)detected_LD2/(float)detected_LD1;
    h3->Fill(ratio);
    std::cout<<detected_LD1<<" | "<<detected_LD2<<" | "<<ratio<<endl;


}

c1->cd();
h1->Draw();
TF1 *f1 = new TF1 ("f1", "gaus", 0., 0.);
h1->Fit("f1", "R");
h1->GetXaxis()->SetTitle("yield [photons/MeV]");
h1->GetYaxis()->SetTitle("event");

c2->cd();
h2->Draw();
TF1 *f2 = new TF1 ("f2", "gaus", 0., 0.);
h2->Fit("f2", "R");
h2->GetXaxis()->SetTitle("yield [photons/MeV]");
h2->GetYaxis()->SetTitle("event");

c3->cd();
h3->Draw();
TF1 *f3 = new TF1 ("f3", "gaus", 0., 0.);
h3->Fit("f3", "R");
h3->GetXaxis()->SetTitle("LD2/LD1");
h3->GetYaxis()->SetTitle("event");

}