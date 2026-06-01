void PlotDecay(){

TFile *f = TFile::Open("../Resultats/RadDecayOutput.root");
TTree *tree = (TTree*)f->Get("Result_tree");

TCanvas *c1 = new TCanvas("c1", "Light Yield");
TGraph* g2 = new TGraph();

vector<float>* E_dep_LMO = nullptr;
vector<float>* E_dep_LD1 = nullptr;

tree->SetBranchAddress("E_dep_LMO",&E_dep_LMO);
tree->SetBranchAddress("E_dep_LD1",&E_dep_LD1);

for (int i = 0; i < tree->GetEntries(); i++)
{
    tree->GetEntry(i);
    for (int j = 0; j < E_dep_LD1->size(); j++)
    {
        if (E_dep_LD1->at(j)/E_dep_LMO->at(j) < 0.5)
        {
            g2->AddPoint(E_dep_LMO->at(j), E_dep_LD1->at(j)/E_dep_LMO->at(j));
        }
    }
}


c1->cd();
g2->SetMarkerStyle(15);
g2->GetYaxis()->SetTitle("LY [keV/MeV]");
g2->GetXaxis()->SetTitle("Energy [keV]");
g2->Draw("APPMC"); 
}