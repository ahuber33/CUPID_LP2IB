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

TH1* h11 = new TH1I("h11", "Detected Track length [mm]", 100.0, 0.0, 0.0);
TH1* h12 = new TH1I("h12", "Absorbed Track length [mm]", 100.0, 0.0, 0.0);
TH1* h13 = new TH1I("h13", "All Track length [mm]", 100.0, 0.0, 0.0);

TH1* h14 = new TH1I("h14", "LMO Reflections Top/Bot", 100.0, 0.0, 0.0);
TH1* h15 = new TH1I("h15", "LMO Reflections Sides", 100.0, 0.0, 0.0);

int scintillated;
float E_dep_event_LMO;
float E_dep_eV;
float yield;
int detected;
int escaped;
int absorbed;
int reemitted;
int reflected_LMO_topbot;
int reflected_LMO_sides;
vector<float>* birth_wavelength = nullptr;
vector<float>* detected_wavelength_LD2 = nullptr;
vector<float>* detected_track_length_LD2 = nullptr;
vector<float>* absorbed_track_length = nullptr;
double xmin;
double xmax;


Optical_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO);
Optical_tree->SetBranchAddress("birth_wavelength", &birth_wavelength);
Optical_tree->SetBranchAddress("detected_wavelength_LD2", &detected_wavelength_LD2);
Optical_tree->SetBranchAddress("detected_track_length_LD2", &detected_track_length_LD2);
Optical_tree->SetBranchAddress("absorbed_track_length", &absorbed_track_length);
Optical_tree->SetBranchAddress("scintillation_LMO", &scintillated);
Optical_tree->SetBranchAddress("detected_LD2", &detected);
Optical_tree->SetBranchAddress("reflected_LMO_topbot", &reflected_LMO_topbot);
Optical_tree->SetBranchAddress("reflected_LMO_sides", &reflected_LMO_sides);
Optical_tree->SetBranchAddress("escaped", &escaped);
Optical_tree->SetBranchAddress("bulk_abs_LMO", &absorbed);
Optical_tree->SetBranchAddress("reemission_LMO", &reemitted);

for (int i = 0; i < Optical_tree->GetEntries(); i++)
{
    Optical_tree->GetEntry(i);
    //std::cout<<"i = "<<i<<" | "<<detected_wavelength_LD2->size()<<" | "<<birth_wavelength->size()<<std::endl;
    if (detected_wavelength_LD2->size() != 0){
        E_dep_eV = 0;

        for(int j=0;j<(birth_wavelength->size());j++)
        {
            h1->Fill(birth_wavelength->at(j));
            h1b->Fill(1240/birth_wavelength->at(j));
        }

        for(int j=0;j<(detected_wavelength_LD2->size());j++)
        {
            E_dep_eV += (1240 / detected_wavelength_LD2->at(j));
            h2->Fill(detected_wavelength_LD2->at(j));
            h2b->Fill(1240/detected_wavelength_LD2->at(j));
            h11->Fill(detected_track_length_LD2->at(j));
            h13->Fill(detected_track_length_LD2->at(j));
        }

        for(int j=0;j<(absorbed_track_length->size());j++)
        {
            h12->Fill(absorbed_track_length->at(j));
            h13->Fill(absorbed_track_length->at(j));
        }

        h3->Fill(scintillated);
        h4->Fill(detected);
        h5->Fill(escaped);
        h6->Fill(absorbed);
        h7->Fill(reemitted);
        h14->Fill(reflected_LMO_topbot);
        h15->Fill(reflected_LMO_sides);

        h8->Fill(E_dep_eV);
        h9->Fill(E_dep_event_LMO);

        h10->Fill(E_dep_eV/E_dep_event_LMO);
        h10b->Fill(detected/(E_dep_event_LMO/1000));
    }
    

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


auto legend1 = new TLegend(0.1,0.7,0.28,0.9);
legend1->AddEntry(h1, "birth");
legend1->AddEntry(h2, "detected");
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
h3->Fit("f3", "QR");
h4->Fit("f4", "QR+");
h5->Fit("f5", "QR+");
h6->Fit("f6", "QR+");
h7->Fit("f7", "QR+");
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
h10->Fit("f10", "QR");
h10->GetXaxis()->SetTitle("yield [keV/MeV]");
h10->GetYaxis()->SetTitle("event");

c4b->cd();
h10b->Draw();
TF1 *f10b = new TF1 ("f10b", "gaus", 0., 0.);
h10b->Fit("f10b", "QR");
h10b->GetXaxis()->SetTitle("yield [photons/MeV]");
h10b->GetYaxis()->SetTitle("event");

c5->cd();
h3->SetLineColor(kBlack);
h3->GetXaxis()->SetTitle("photons");
h3->GetYaxis()->SetTitle("event");
h3->Draw();

double Nscint = f3->GetParameter(1);
double NdetLD2 = f4->GetParameter(1);
double Nescaped = f5->GetParameter(1);
double Nabsorbed = f6->GetParameter(1);
double Nscint_err = f3->GetParameter(2);
double NdetLD2_err = f4->GetParameter(2);
double Nescaped_err = f5->GetParameter(2);
double Nabsorbed_err = f6->GetParameter(2);

double RdetLD2 = 100*(NdetLD2/Nscint);
double Rescaped  = 100*(Nescaped /Nscint);
double Rabsorbed = 100*(Nabsorbed/Nscint);
double RdetLD2_err = RdetLD2*sqrt( pow((NdetLD2_err/NdetLD2), 2) + pow((Nscint_err/Nscint), 2) );
double Rescaped_err  = Rescaped*sqrt( pow((Nescaped_err/Nescaped), 2) + pow((Nscint_err/Nscint), 2) );
double Rabsorbed_err = Rabsorbed*sqrt( pow((Nabsorbed_err/Nabsorbed), 2) + pow((Nscint_err/Nscint), 2) );


std::cout<<"--------------------------------------------"<<std::endl;
std::cout<<"----------------- S1 STATS -----------------"<<std::endl;
std::cout<<"--------------------------------------------"<<std::endl;
//std::cout<<"Ndetected: "<<h4->GetMean(1)<<" +- "<<h4->GetMeanError(1)<<" photons"<<std::endl;
std::cout<<"LY: "<<h10->GetMean(1)<<" +- "<<h10->GetMeanError(1)<<" keV/MeV"<<std::endl;
std::cout<<"Detected S1: "<<RdetLD2<<" +- "<<RdetLD2_err<<" %"<<std::endl;
std::cout<<"Escaped: "<<Rescaped<<" +- "<<Rescaped_err<<" %"<<std::endl;
std::cout<<"Absorbed: "<<Rabsorbed<<" +- "<<Rabsorbed_err<<" %"<<std::endl;
std::cout<<"<Lph>det: "<<h11->GetMean(1)<<" +- "<<h11->GetMeanError(1)<<" mm"<<std::endl;
std::cout<<"<Lph>abs: "<<h12->GetMean(1)<<" +- "<<h12->GetMeanError(1)<<" mm"<<std::endl;
std::cout<<"<Lph>all: "<<h13->GetMean(1)<<" +- "<<h13->GetMeanError(1)<<" mm"<<std::endl;
std::cout<<"<Nreflect>top/bot: "<<h14->GetMean(1)<<" +- "<<h14->GetMeanError(1)<<" reflections"<<std::endl;
std::cout<<"<Nreflect>sides: "<<h15->GetMean(1)<<" +- "<<h15->GetMeanError(1)<<" reflections"<<std::endl;
std::cout<<"--------------------------------------------"<<std::endl;
}