void plot_results(){

TFile *f = TFile::Open("../Resultats");
TTree *Input_tree = (TTree*)f->Get("Input");
TTree *ZnS_tree = (TTree*)f->Get("ZnS");
TTree *Scintillator_tree = (TTree*)f->Get("Scintillator");
TTree *Optical_tree = (TTree*)f->Get("Optical");

TCanvas *c1 = new TCanvas();
TCanvas *c2 = new TCanvas();
TCanvas *c3 = new TCanvas();

TH1* h1 = new TH1I("h1", "scintillation_ZnS", 100.0, 0.0, 6000);
TH1* h2 = new TH1I("h2", "scintillation_Sc", 100.0, 0.0, 6000);
TH1* h3 = new TH1I("h1", "E_dep_event_ZnS", 100.0, 0.0, 1000);
TH1* h4 = new TH1I("h2", "E_dep_event_Sc", 100.0, 0.0, 1000);
TH1* h5 = new TH1I("h2", "birth_wavelength", 100.0, 300, 800);

int scintillation_ZnS;
int scintillation_Sc;
float E_dep_event_ZnS;
float E_dep_event_Sc;
vector<double>* birth_wavelength = nullptr;


Optical_tree->SetBranchAddress("scintillation_ZnS", &scintillation_ZnS); //recupere la branch event_number
Optical_tree->SetBranchAddress("scintillation_Sc", &scintillation_Sc);
Optical_tree->SetBranchAddress("birth_wavelength", &birth_wavelength);
ZnS_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_ZnS);
Scintillator_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_Sc);

for (int i = 0; i < Optical_tree->GetEntries(); i++)
{
    Optical_tree->GetEntry(i);
    ZnS_tree->GetEntry(i);
    Scintillator_tree->GetEntry(i);
    //std::cout<<scintillation_ZnS<<endl;
    h1->Fill(scintillation_ZnS);
    h2->Fill(scintillation_Sc);
    h3->Fill(E_dep_event_ZnS);
    h4->Fill(E_dep_event_Sc);
    for(int j=0;j<(birth_wavelength->size());j++)
    {
        h5->Fill(birth_wavelength->at(j));
    }
}

c1->cd();

h1->SetFillColor(kBlue);
h1->GetXaxis()->SetTitle("nombre de photons");
h2->SetFillColor(kRed);
h1->GetYaxis()->SetTitle("event");
h1->Draw();
h2->Draw("same");

auto legend1 = new TLegend(0.1,0.7,0.28,0.9);
legend1->AddEntry(h1, "scintillation_ZnS");
legend1->AddEntry(h2, "scintillation_Sc");
legend1->Draw();

c2->cd();

h3->SetFillColor(kBlue);
h3->GetXaxis()->SetTitle("energy deposit [keV]");
h4->SetFillColor(kRed);
h3->GetYaxis()->SetTitle("event");
h3->Draw();
h4->Draw("same");

auto legend2 = new TLegend(0.1,0.7,0.28,0.9);
legend2->AddEntry(h3, "E_dep_event_ZnS");
legend2->AddEntry(h4, "E_dep_event_Sc");
legend2->Draw();

c3->cd();
h5->GetXaxis()->SetTitle("wavelength [nm]");
h5->Draw();

}