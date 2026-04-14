void plot_LY(){

TFile *f = TFile::Open("../Resultats");
TTree *Input_tree = (TTree*)f->Get("Input");
TTree *LMO_tree = (TTree*)f->Get("LMO");
TTree *Optical_tree = (TTree*)f->Get("Optical");

TCanvas *c1 = new TCanvas();
TCanvas *c2 = new TCanvas();
TCanvas *c3 = new TCanvas();
TCanvas *c4 = new TCanvas();

TH1* h1 = new TH1I("h1", "scintillation_LMO", 100.0, 0.0, 15000);
TH1* h3 = new TH1I("h3", "E_dep_event_LMO", 100.0, 0.0, 1200);
TH1* h5 = new TH1I("h5", "LY_LMO", 100.0, 0.0, 15000);
TH1* h6 = new TH1I("h6", "birth_wavelength", 100.0, 0.0, 1000);

int scintillation_LMO;
float E_dep_event_LMO;
vector<double>* birth_wavelength = nullptr;


Optical_tree->SetBranchAddress("scintillation_LMO", &scintillation_LMO);
LMO_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO);
Optical_tree->SetBranchAddress("birth_wavelength", &birth_wavelength);

for (int i = 0; i < Optical_tree->GetEntries(); i++)
{
    Optical_tree->GetEntry(i);
    LMO_tree->GetEntry(i);
    //std::cout<<scintillation_LMO<<endl;
    h1->Fill(scintillation_LMO);
    h3->Fill(E_dep_event_LMO);
    //std::cout<<"PHOTONS SC = "<<scintillation_Sc<<" ||| E_DEP_EVENT = "<<E_dep_event_Sc<<" keV ||| LY = "<<scintillation_Sc/(E_dep_event_Sc/1000)<<endl;
    if (E_dep_event_LMO>0 && scintillation_LMO>0)
    {
        h5->Fill(scintillation_LMO/(E_dep_event_LMO/1000));
    }
    for(int j=0;j<(birth_wavelength->size());j++)
    {
        h6->Fill(birth_wavelength->at(j));
    }
}

c1->cd();

h1->SetFillColor(kBlue);
h1->GetXaxis()->SetTitle("nombre de photons");
h1->GetYaxis()->SetTitle("event");
h1->Draw();

auto legend1 = new TLegend(0.1,0.7,0.28,0.9);
legend1->AddEntry(h1, "scintillation_LMO");
legend1->Draw();

c2->cd();

h3->SetFillColor(kBlue);
h3->GetXaxis()->SetTitle("energy deposit [keV]");
h3->GetYaxis()->SetTitle("event");
h3->Draw();

auto legend2 = new TLegend(0.1,0.7,0.28,0.9);
legend2->AddEntry(h3, "E_dep_event_LMO");
legend2->Draw();

c3->cd();
h6->Draw();

c4->cd();
h5->SetFillColor(kBlue);
h5->GetXaxis()->SetTitle("LY [photons/MeV]");
h5->Draw();

auto legend3 = new TLegend(0.1,0.7,0.28,0.9);
legend3->AddEntry(h5, "E_dep_event_LMO");
legend3->Draw();

}