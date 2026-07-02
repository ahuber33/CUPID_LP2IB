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
        if (cerenkov_LMO>0){
            g3->AddPoint(incident_E, cerenkov_LMO);
        }
    }
}

c1->cd();
gStyle->SetLabelSize(0.05, "XY");
gStyle->SetTitleSize(0.05, "XY");

g2->AddPoint(1,132);
g2->AddPoint(2,354);
g2->AddPoint(3,556);
g2->SetMarkerStyle(23);
g2->SetMarkerColor(96);
g2->SetMarkerSize(2);
g2->SetLineColor(1);
g2->SetLineWidth(2);

g1->SetMarkerStyle(15);
g1->SetMarkerColor(1);
TMultiGraph *mg1 = new TMultiGraph();
mg1->Add(g1);
mg1->Add(g2);
mg1->GetYaxis()->SetTitle("cerenkov photons");
mg1->GetXaxis()->SetTitle("particle energy [MeV]");
mg1->GetXaxis()->SetTitleOffset(1);
mg1->Draw("AP");

auto legend = new TLegend(0.9,0.2,0.8,0.4);
legend->AddEntry(g1, "simulation", "P");
legend->AddEntry(g2, "theory", "P");
legend->Draw();

c2->cd();
gStyle->SetLabelSize(0.08, "XY");

TLine* tl = new TLine(0.121, 0, 0.121, 10);

g3->SetMarkerStyle(20);
g3->SetMarkerSize(1);
g3->SetMarkerColor(1);
g3->SetMaximum(10);
g3->SetMinimum(0);
g3->GetXaxis()->SetLimits(0,0.35);
g3->Draw("AP");

tl->SetLineColor(kRed);
tl->Draw("same");

}