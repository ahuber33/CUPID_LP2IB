void RadDecay(){

TCanvas *c1 = new TCanvas("c1", "Light/heat");
TCanvas *c2 = new TCanvas("c2", "Light/heat with particles");
TCanvas *c3 = new TCanvas("c3", "LY histograms");

TH1* h1 = new TH1I("h1", "#beta / #gamma", 100.0, 0.0, 0.9);
TH1* h2 = new TH1I("h2", "#alpha", 100.0, 0.0, 0.3);
TGraph* g1 = new TGraph();
TGraph* g2 = new TGraph();
TGraph* g2el = new TGraph();
TGraph* g2al = new TGraph();
TGraph* g2ga = new TGraph();


//vector<std::string> filenames = {"../Resultats/decay/output_210Po.root", "../Resultats/decay/output_208Tl.root", "../Resultats/decay/output_238U.root"};*
vector<std::string> filenames = {"../Resultats/output_238Ulong.root"};

for (int n = 0; n < filenames.size(); n++)
{
    TFile *f = TFile::Open(filenames.at(n).c_str());
    TTree *Optical_tree = (TTree*)f->Get("Optical");

    int scintillated;
    vector<float>* Edep = nullptr;
    vector<int>* Edep_ancestorID = nullptr;
    float E_dep_eV;
    float detected_eV;
    int detected;
    std::string ancestorName;
    vector<float>* detected_wavelength_LD1 = nullptr;
    vector<float>* detected_ancestorID_LD1 = nullptr;
    vector<float>* detected_wavelength_LD2 = nullptr;
    vector<float>* detected_ancestorID_LD2 = nullptr;
    vector<int>* list_ancestorID = nullptr;
    vector<std::string>* list_ancestorName = nullptr;
    int ancestorID;
    int detected_photons;

    Optical_tree->SetBranchAddress("particle_deposited_energy", &Edep);
    Optical_tree->SetBranchAddress("particle_deposited_ancestorID", &Edep_ancestorID);
    Optical_tree->SetBranchAddress("detected_wavelength_LD1", &detected_wavelength_LD1);
    Optical_tree->SetBranchAddress("ancestorID_LD1", &detected_ancestorID_LD1);
    Optical_tree->SetBranchAddress("detected_wavelength_LD2", &detected_wavelength_LD2);
    Optical_tree->SetBranchAddress("ancestorID_LD2", &detected_ancestorID_LD2);
    Optical_tree->SetBranchAddress("scintillation_LMO", &scintillated);
    Optical_tree->SetBranchAddress("detected_LD1", &detected);
    Optical_tree->SetBranchAddress("list_ancestorID", &list_ancestorID);
    Optical_tree->SetBranchAddress("list_ancestorName", &list_ancestorName);

    /* 
    for (int i = 0; i < Optical_tree->GetEntries(); i++)
    {
        Optical_tree->GetEntry(i);
        if (detected_wavelength_LD1->size() != 0){
            E_dep_eV = 0;


            for(int j=0;j<(detected_wavelength_LD1->size());j++)
            {
                E_dep_eV += (1240 / detected_wavelength_LD1->at(j));
            }

            h1->Fill(E_dep_eV/E_dep_event_LMO);
        }
        if (E_dep_event_LMO>50){
            g1->AddPoint(E_dep_event_LMO, detected);
            g2->AddPoint(E_dep_event_LMO, E_dep_eV/E_dep_event_LMO);
        }
    } */

    for (int i = 0; i < Optical_tree->GetEntries(); i++)
    {
        Optical_tree->GetEntry(i);

        // get a ancestorID vector withput duplicates
        std::vector<int>* v = new std::vector<int>(*Edep_ancestorID);
        sort(v->begin(), v->end());
        auto it = unique(v->begin(), v->end());
        v->erase(it, v->end());

        for(int j=0;j<(v->size());j++)
            {
                ancestorID = v->at(j);
                
                for (int l=0;l<(list_ancestorID->size());l++){
                    if (ancestorID == list_ancestorID->at(l)){
                        ancestorName = list_ancestorName->at(l);
                    }
                }

                E_dep_eV = 0.;
                detected_photons = 0;
                detected_eV = 0.;

                // get energy deposed by all the particle associated to ancestor
                for(int k=0;k<(Edep->size());k++)
                {
                    if (Edep_ancestorID->at(k)==ancestorID)
                    {
                        E_dep_eV += Edep->at(k);
                    }
                }
                // get detected photons associated with this ancestor
                for(int k=0;k<(detected_wavelength_LD1->size());k++)
                {
                    if (detected_ancestorID_LD1->at(k)==ancestorID)
                    {
                        detected_photons++;
                        detected_eV += (1240 / detected_wavelength_LD1->at(k));
                    }
                }
                for(int k=0;k<(detected_wavelength_LD2->size());k++)
                {
                    if (detected_ancestorID_LD2->at(k)==ancestorID)
                    {
                        detected_photons++;
                        detected_eV += (1240 / detected_wavelength_LD2->at(k));
                    }
                }
                if (detected_photons>0 && E_dep_eV>0)
                {
                    //std::cout<<E_dep_eV<<" | "<<detected_photons<<" | "<<detected_eV<<std::endl;
                    //std::cout<<(detected_eV)/E_dep_eV<<" kev/MeV"<<std::endl;
                    g2->AddPoint(E_dep_eV, (detected_eV)/E_dep_eV);
                    g1->AddPoint(E_dep_eV, detected_photons);
                    if (ancestorName=="e-"){
                        g2el->AddPoint(E_dep_eV, (detected_eV)/E_dep_eV);
                        if (E_dep_eV>1200){
                            h1->Fill((detected_eV)/E_dep_eV);
                        }
                    }
                    else if (ancestorName=="alpha"){
                        g2al->AddPoint(E_dep_eV, (detected_eV)/E_dep_eV);
                        if (E_dep_eV>1200){
                            h2->Fill((detected_eV)/E_dep_eV);
                        }
                    }
                    else if (ancestorName=="gamma"){
                        g2ga->AddPoint(E_dep_eV, (detected_eV)/E_dep_eV);
                        if (E_dep_eV>1200){
                            h1->Fill((detected_eV)/E_dep_eV);
                        }
                    }
                }
            }
    }
}

int xmax = 12000;

gStyle->SetOptFit(1);

c1->DivideSquare(2);
c1->SetWindowSize(950, 450);
c1->cd(2);
g2->SetMarkerStyle(20);
g2->SetMarkerSize(0.5);
g2->SetMaximum(0.9);
g2->GetXaxis()->SetLimits(0,xmax);
g2->Draw("APPMC");
g2->GetYaxis()->SetTitle("LY [keV/MeV]");
g2->GetXaxis()->SetTitle("Energy [keV]");

c1->cd(1);
g1->SetMarkerStyle(20);
g1->SetMarkerSize(0.5);
g1->GetYaxis()->SetTitle("Photons detected");
g1->GetXaxis()->SetTitle("Energy [keV]");
g1->Draw("APPMC");

c2->cd();
c2->SetWindowSize(950, 450);
c2->SetWindowPosition(0,505);

g2el->SetMarkerStyle(20);
g2al->SetMarkerStyle(20);
g2ga->SetMarkerStyle(20);
g2el->SetMarkerSize(0.5);
g2al->SetMarkerSize(0.5);
g2ga->SetMarkerSize(0.5);
g2el->SetMarkerColor(6);
g2al->SetMarkerColor(94);
g2ga->SetMarkerColor(4);
TMultiGraph *mg = new TMultiGraph();
mg->Add(g2el);
mg->Add(g2al);
mg->Add(g2ga);
mg->GetYaxis()->SetTitle("LY [keV/MeV]");
mg->GetXaxis()->SetTitle("Energy [keV]");
mg->GetYaxis()->SetRangeUser(0.,0.9);
mg->GetXaxis()->SetRangeUser(0.,xmax);
mg->Draw("AP");

auto legend = new TLegend(0.9,0.7,0.8,0.9);
legend->AddEntry(g2el, "e-", "P");
legend->AddEntry(g2al, "#alpha", "P");
legend->AddEntry(g2ga, "#gamma", "P");
legend->Draw();

c3->DivideSquare(2);
c3->SetWindowSize(950, 450);
c3->cd(1);
h1->GetXaxis()->SetTitle("LY [keV/MeV]");
h1->Draw();
TF1 *f1 = new TF1 ("f1", "gaus", 0., 0.);
h1->Fit("f1", "QR");

c3->cd(2);
h2->GetXaxis()->SetTitle("LY [keV/MeV]");
h2->Draw();
TF1 *f2 = new TF1 ("f2", "gaus", 0., 0.);
h2->Fit("f2", "QR");

}