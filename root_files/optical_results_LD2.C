void optical_results_LD2(){

    

TFile *f = TFile::Open("../Resultats/output.root");
TTree *Optical_tree = (TTree*)f->Get("Optical");

TCanvas *c1 = new TCanvas("c1", "Wavelength spectrum");
TCanvas *c1b = new TCanvas("c1b", "Energy spectrum");
TCanvas *c2 = new TCanvas("c2", "Optical photons");
TCanvas *c3 = new TCanvas("c3", "Energy deposit");
TCanvas *c4 = new TCanvas("c4", "Yield [kev/MeV]");
TCanvas *c4b = new TCanvas("c4b", "Yield [photons/MeV]");
TCanvas *c5 = new TCanvas("c5", "Scintillation");

TH1* h1 = new TH1F("h1", "birth_wavelength", 100.0, 200.0, 1000);
TH1* h2 = new TH1F("h2", "detected_wavelength_LD2", 100.0, 200.0, 1000);

TH1* h1b = new TH1F("h1b", "birth_energy", 100.0, 1240/200.0, 1240/1000);
TH1* h2b = new TH1F("h2b", "detected_energy", 100.0, 1240/200.0, 1240/1000);

TH1* h3 = new TH1I("h3", "scintillated", 100.0, 0.0, 1500);
TH1* h4 = new TH1I("h4", "detected", 100.0, 0.0, 1500);
TH1* h5 = new TH1I("h5", "escaped", 100.0, 0.0, 1500);
TH1* h6 = new TH1I("h6", "absorbed", 100.0, 0.0, 1500);
TH1* h7 = new TH1I("h7", "reemitted", 100.0, 0.0, 1500);

TH1* h8 = new TH1I("h8", "E_dep_LD", 100.0, 0.0, 1100);
TH1* h9 = new TH1I("h9", "E_dep_LMO", 100.0, 0.0, 1100);

TH1* h10 = new TH1I("h10", "Yield [kev/MeV]", 100.0, 0.0, 0.0);
TH1* h10b = new TH1I("h10b", "Yield [photons/MeV]", 50.0, 0.0, 0.0);

int scintillated;
float E_dep_event_LMO;
float E_dep_eV;
float yield;
int detected;
int escaped;
int absorbed;
int reemitted;
vector<float>* birth_wavelength = nullptr;
vector<float>* detected_wavelength_LD2 = nullptr;
double xmin;
double xmax;


Optical_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO);
Optical_tree->SetBranchAddress("birth_wavelength", &birth_wavelength);
Optical_tree->SetBranchAddress("detected_wavelength_LD2", &detected_wavelength_LD2);
Optical_tree->SetBranchAddress("scintillation_LMO", &scintillated);
Optical_tree->SetBranchAddress("detected_LD2", &detected);
Optical_tree->SetBranchAddress("escaped", &escaped);
Optical_tree->SetBranchAddress("bulk_abs_LMO", &absorbed);
Optical_tree->SetBranchAddress("reemission_LMO", &reemitted);

for (int i = 0; i < Optical_tree->GetEntries(); i++)
{
    Optical_tree->GetEntry(i);
    E_dep_eV = 0;
    xmin = birth_wavelength->at(0);
    xmax = birth_wavelength->at(0);

    for(int j=0;j<(birth_wavelength->size());j++)
    {
        h1->Fill(birth_wavelength->at(j));
        h1b->Fill(1240/birth_wavelength->at(j));
        if (birth_wavelength->at(j) < xmin){
            xmin = birth_wavelength->at(j);
        }
        if (birth_wavelength->at(j) > xmax){
            xmax = birth_wavelength->at(j);
        }
    }

    for(int j=0;j<(detected_wavelength_LD2->size());j++)
    {
        E_dep_eV += (1240 / detected_wavelength_LD2->at(j));
        h2->Fill(detected_wavelength_LD2->at(j));
        h2b->Fill(1240/detected_wavelength_LD2->at(j));
        if (detected_wavelength_LD2->at(j) < xmin){
            xmin = birth_wavelength->at(j);
        }
        if (detected_wavelength_LD2->at(j) > xmax){
            xmax = birth_wavelength->at(j);
        }
    }

    h3->Fill(scintillated);
    h4->Fill(detected);
    h5->Fill(escaped);
    h6->Fill(absorbed);
    h7->Fill(reemitted);

    h8->Fill(E_dep_eV);
    h9->Fill(E_dep_event_LMO);

    h10->Fill(E_dep_eV/E_dep_event_LMO);
    h10b->Fill(detected/(E_dep_event_LMO/1000));
    

}

c1->cd();

h1->SetLineColor(kBlue);
h2->SetLineColor(kRed);
h1->Scale( 1./h1->GetMaximum());
h2->Scale( 1./h2->GetMaximum());
h1->GetXaxis()->SetTitle("wavelength [nm]");
h1->GetYaxis()->SetTitle("ratio");
h1->Draw("HIST");
h2->Draw("HIST same");

c1b->cd();

h1b->SetLineColor(kBlue);
h2b->SetLineColor(kRed);
h1b->Scale( 1./h1b->GetMaximum());
h2b->Scale( 1./h2b->GetMaximum());
h1b->GetXaxis()->SetTitle("energy [eV]");
h1b->GetYaxis()->SetTitle("ratio");
h1b->Draw("HIST");
h2b->Draw("HIST same");

// Emission data

vector<double> emission_eV = {1.5, 1.75, 2., 2.15, 2.25, 2.5, 2.75, 3.0};
vector<double> emission_var = {0.1, 0.42, 0.93, 1.0, 0.92, 0.42, 0.1, 0.03};

TGraph *g = new TGraph(emission_eV.size());
for (int i = 0; i < emission_eV.size(); i++) {
    g->SetPoint(i, emission_eV[i], emission_var[i]);
}

g->SetMarkerStyle(47);
g->SetMarkerSize(2);
g->SetMarkerColor(kBlack);

g->Draw("P SAME");


/* 
TF1 *ft = new TF1("ft","-x",(1240/1000),(1240/200));
TGaxis *A1 = new TGaxis(200,h1->GetMaximum()+200,1000,h1->GetMaximum()+200,"ft",510,"-");
A1->SetTitle("[eV]");
A1->Draw();

std::cout<<"XMIN = "<<xmin<<endl;

std::cout<<"XMAX = "<<xmax<<endl;
 */
auto legend1 = new TLegend(0.1,0.7,0.28,0.9);
legend1->AddEntry(h1, "birth");
legend1->AddEntry(h2, "detected");
legend1->AddEntry(g, "input");
legend1->Draw();

c2->cd();
gStyle->SetOptFit(1);
h3->SetLineColor(kBlack);
h4->SetLineColor(kBlue);
h5->SetLineColor(kRed);
h6->SetLineColor(kGreen);
h7->SetLineColor(kOrange);
h4->GetXaxis()->SetTitle("number of photons");
h4->GetYaxis()->SetTitle("event");
TF1 *f3 = new TF1 ("f3", "gaus", 0., 0.);
TF1 *f4 = new TF1 ("f4", "gaus", 0., 0.);
TF1 *f5 = new TF1 ("f5", "gaus", 0., 0.);
TF1 *f6 = new TF1 ("f6", "gaus", 0., 0.);
TF1 *f7 = new TF1 ("f7", "gaus", 0., 0.);
h3->Fit("f3", "R");
h4->Fit("f4", "R+");
h5->Fit("f5", "R+");
h6->Fit("f6", "R+");
h7->Fit("f7", "R+");
h4->Draw();
h5->Draw("same");
h3->Draw("same");
h6->Draw("same");
h7->Draw("same");

c2->SetLogy(1);

auto legend4 = new TLegend(0.1,0.7,0.28,0.9);
legend4->AddEntry(h3, "scintillated");
legend4->AddEntry(h4, "detected");
legend4->AddEntry(h5, "escaped");
legend4->AddEntry(h6, "absorbed");
legend4->AddEntry(h7, "reemitted");
legend4->Draw();

c3->cd();
h8->SetLineColor(kRed);
h9->SetLineColor(kBlue);
h8->GetXaxis()->SetTitle("energy");
h8->GetYaxis()->SetTitle("event");
h9->Draw();
h8->Draw("same");

c3->SetLogy(1);

auto legend3 = new TLegend(0.1,0.7,0.28,0.9);
legend3->AddEntry(h8, "LD [eV]");
legend3->AddEntry(h9, "LMO [keV]");
legend3->Draw();

c4->cd();
h10->Draw();
TF1 *f10 = new TF1 ("f10", "gaus", 0., 1.);
h10->Fit("f10", "R");
h10->GetXaxis()->SetTitle("yield [keV/MeV]");
h10->GetYaxis()->SetTitle("event");

c4b->cd();
h10b->Draw();
TF1 *f10b = new TF1 ("f10b", "gaus", 0., 0.);
h10b->Fit("f10b", "R");
h10b->GetXaxis()->SetTitle("yield [photons/MeV]");
h10b->GetYaxis()->SetTitle("event");

c5->cd();
h3->SetLineColor(kBlack);
h3->GetXaxis()->SetTitle("photons");
h3->GetYaxis()->SetTitle("event");
h3->Draw();
}