void optical(){

    

TFile *f = TFile::Open("../Resultats/output_cerenkov.root");
TTree *Optical_tree = (TTree*)f->Get("Optical");

TCanvas *c1 = new TCanvas("c1", "Wavelength spectrum");
TCanvas *c2 = new TCanvas("c2", "Waaum");

TGraph* g1 = new TGraph();
TGraph* g2 = new TGraph();
TGraph* g3 = new TGraph();

int cerenkov_LMO;
float incident_E;
float deposited_energy_event;

Optical_tree->SetBranchAddress("cerenkov_LMO", &cerenkov_LMO);
Optical_tree->SetBranchAddress("incident_E", &incident_E);
Optical_tree->SetBranchAddress("deposited_energy_event", &deposited_energy_event);

for (int i = 0; i < Optical_tree->GetEntries(); i++)
{
    Optical_tree->GetEntry(i);
    if (incident_E<0.001+deposited_energy_event/1000)
    {
        g1->AddPoint(incident_E, cerenkov_LMO);
        g3->AddPoint(incident_E, cerenkov_LMO);
    }
}

c1->cd();

g2->AddPoint(1,147);
g2->AddPoint(2,304);
g2->SetMarkerStyle(106);
g2->SetMarkerColor(96);
g2->SetMarkerSize(2);

g1->SetMarkerStyle(15);
g1->SetMarkerColor(1);
TMultiGraph *mg1 = new TMultiGraph();
mg1->Add(g1);
mg1->Add(g2);
mg1->GetYaxis()->SetTitle("cerenkov photons");
mg1->GetXaxis()->SetTitle("particle energy [MeV]");
mg1->Draw("AP");

c2->cd();
gStyle->SetLabelSize(0.06, "XY");

g3->SetMarkerStyle(20);
g3->SetMarkerSize(1);
g3->SetMarkerColor(1);
g3->SetMaximum(30);
g3->GetXaxis()->SetLimits(0,0.5);
g3->Draw("AP");
}