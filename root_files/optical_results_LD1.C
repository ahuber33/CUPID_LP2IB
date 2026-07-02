void optical_results_LD1(){

    

TFile *f = TFile::Open("../Resultats/output.root");
TTree *Optical_tree = (TTree*)f->Get("Optical");

TCanvas *c1 = new TCanvas("c1", "Wavelength spectrum");
TCanvas *c1b = new TCanvas("c1b", "Energy spectrum");
TCanvas *c2 = new TCanvas("c2", "Optical photons");
TCanvas *c3 = new TCanvas("c3", "Energy deposit");
TCanvas *c4 = new TCanvas("c4", "Yield [kev/MeV]");
TCanvas *c4b = new TCanvas("c4b", "Yield [photons/MeV]");
TCanvas *c5 = new TCanvas("c5", "Scintillation");
TCanvas *c6 = new TCanvas("c6", "Total Yield [kev/MeV]");

TH1* h1 = new TH1F("h1", "birth_wavelength", 100.0, 200.0, 1000);
TH1* h2 = new TH1F("h2", "detected_wavelength_LD1", 100.0, 200.0, 1000);

TH1* h1b = new TH1F("h1b", "birth_energy", 100.0, 1240/200.0, 1240/1000);
TH1* h2b = new TH1F("h2b", "detected_energy", 100.0, 1240/200.0, 1240/1000);

TH1* h3 = new TH1I("h3", "scintillated", 100.0, 0.0, 1500);
TH1* h3b = new TH1I("h3b", "cerenkov", 100.0, 0.0, 1500);
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

TH1* h16 = new TH1I("h16", "LY Total", 100.0, 0.0, 0.0);

TH1* htot = new TH1I("htot", "detectedTOT", 100.0, 0.0, 1500);

int scintillated;
int cerenkov;
float E_dep_event_LMO;
float E_dep_eV_LD1;
float E_dep_eV_tot;
float yield;
int detected_LD1;
int detected_LD2;
int escaped;
int absorbed;
int reemitted;
int reflected_LMO_topbot;
int reflected_LMO_sides;
vector<float>* birth_wavelength = nullptr;
vector<float>* detected_wavelength_LD1 = nullptr;
vector<float>* detected_wavelength_LD2 = nullptr;
vector<float>* detected_track_length_LD1 = nullptr;
vector<float>* absorbed_track_length = nullptr;
double xmin;
double xmax;


Optical_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO);
Optical_tree->SetBranchAddress("birth_wavelength", &birth_wavelength);
Optical_tree->SetBranchAddress("detected_wavelength_LD1", &detected_wavelength_LD1);
Optical_tree->SetBranchAddress("detected_track_length_LD1", &detected_track_length_LD1);
Optical_tree->SetBranchAddress("detected_wavelength_LD2", &detected_wavelength_LD2);
Optical_tree->SetBranchAddress("absorbed_track_length", &absorbed_track_length);
Optical_tree->SetBranchAddress("scintillation_LMO", &scintillated);
Optical_tree->SetBranchAddress("cerenkov_LMO", &cerenkov);
Optical_tree->SetBranchAddress("detected_LD1", &detected_LD1);
Optical_tree->SetBranchAddress("detected_LD2", &detected_LD2);
Optical_tree->SetBranchAddress("reflected_LMO_topbot", &reflected_LMO_topbot);
Optical_tree->SetBranchAddress("reflected_LMO_sides", &reflected_LMO_sides);
Optical_tree->SetBranchAddress("escaped", &escaped);
Optical_tree->SetBranchAddress("bulk_abs_LMO", &absorbed);
Optical_tree->SetBranchAddress("reemission_LMO", &reemitted);

for (int i = 0; i < Optical_tree->GetEntries(); i++)
{
    Optical_tree->GetEntry(i);
    E_dep_eV_tot = 0;
    //std::cout<<"i = "<<i<<" | "<<detected_wavelength_LD1->size()<<" | "<<birth_wavelength->size()<<std::endl;
    if (detected_wavelength_LD1->size() != 0){
        E_dep_eV_LD1 = 0;

        for(int j=0;j<(birth_wavelength->size());j++)
        {
            h1->Fill(birth_wavelength->at(j));
            h1b->Fill(1240/birth_wavelength->at(j));
        }

        for(int j=0;j<(detected_wavelength_LD1->size());j++)
        {
            E_dep_eV_LD1 += (1240 / detected_wavelength_LD1->at(j));
            E_dep_eV_tot += (1240 / detected_wavelength_LD1->at(j));
            h2->Fill(detected_wavelength_LD1->at(j));
            h2b->Fill(1240/detected_wavelength_LD1->at(j));
            h11->Fill(detected_track_length_LD1->at(j));
            h13->Fill(detected_track_length_LD1->at(j));
        }

        for(int j=0;j<(absorbed_track_length->size());j++)
        {
            h12->Fill(absorbed_track_length->at(j));
            h13->Fill(absorbed_track_length->at(j));
        }

        h3->Fill(scintillated);
        h3b->Fill(cerenkov);
        h4->Fill(detected_LD1);
        h5->Fill(escaped);
        h6->Fill(absorbed);
        h7->Fill(reemitted);
        h14->Fill(reflected_LMO_topbot);
        h15->Fill(reflected_LMO_sides);

        h8->Fill(E_dep_eV_LD1);
        h9->Fill(E_dep_event_LMO);

        h10->Fill(E_dep_eV_LD1/E_dep_event_LMO);
        h10b->Fill(detected_LD1/(E_dep_event_LMO/1000));

        if (detected_wavelength_LD2->size() != 0){
            htot->Fill(detected_LD1+detected_LD2);
        }
    }
    if (detected_wavelength_LD2->size() != 0){
        for(int j=0;j<(detected_wavelength_LD2->size());j++)
        {
            E_dep_eV_tot += (1240 / detected_wavelength_LD2->at(j));
        }
    }
    
    if (E_dep_eV_tot>0 && E_dep_event_LMO>0){
        h16->Fill(E_dep_eV_tot/E_dep_event_LMO);
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
TF1 *f3 = new TF1 ("f3", "gaus", h3->GetMean(1)-200,h3->GetMean(1)+200);
TF1 *f3b = new TF1 ("f3b", "gaus", h3b->GetMean(1)-200,h3b->GetMean(1)+200);
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

h3b->Fit("f3b");
TF1 *ftot = new TF1 ("ftot", "gaus", 0., 0.);
htot->Fit("ftot");

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

c6->cd();
h16->Draw();


double Nscint = f3->GetParameter(1);
double Ncerenkov = f3b->GetParameter(1);
double NdetLD1 = f4->GetParameter(1);
double NdetTOT= ftot->GetParameter(1);
double Nescaped = f5->GetParameter(1);
double Nabsorbed = f6->GetParameter(1);
double Nscint_err = f3->GetParError(1);
double Ncerenkov_err = f3b->GetParError(1);
double NdetLD1_err = f4->GetParError(1);
double NdetTOT_err = ftot->GetParError(1);
double Nescaped_err = f5->GetParError(1);
double Nabsorbed_err = f6->GetParError(1);

double RdetLD1 = 100*(NdetLD1/(Nscint+Ncerenkov));
double RdetTOT = 100*(NdetTOT/(Nscint+Ncerenkov));
double Rescaped  = 100*(Nescaped /(Nscint+Ncerenkov));
double Rabsorbed = 100*(Nabsorbed/(Nscint+Ncerenkov));
double RdetLD1_err = RdetLD1*sqrt( pow((NdetLD1_err/NdetLD1), 2) + pow((Nscint_err/Nscint), 2) );
double RdetTOT_err = RdetTOT*sqrt( pow((NdetTOT_err/NdetTOT), 2) + pow((Nscint_err/Nscint), 2) );
double Rescaped_err  = Rescaped*sqrt( pow((Nescaped_err/Nescaped), 2) + pow((Nscint_err/Nscint), 2) );
double Rabsorbed_err = Rabsorbed*sqrt( pow((Nabsorbed_err/Nabsorbed), 2) + pow((Nscint_err/Nscint), 2) );

std::cout<<"AAAAAAAAA  "<<NdetTOT<<std::endl;


std::cout<<"--------------------------------------------"<<std::endl;
std::cout<<"----------------- S1 STATS -----------------"<<std::endl;
std::cout<<"--------------------------------------------"<<std::endl;
//std::cout<<"Ndetected: "<<h4->GetMean(1)<<" +- "<<h4->GetMeanError(1)<<" photons"<<std::endl;
std::cout<<"LY: "<<h10->GetMean(1)<<" +- "<<h10->GetMeanError(1)<<" keV/MeV"<<std::endl;
std::cout<<"Detected S1: "<<RdetLD1<<" +- "<<RdetLD1_err<<" %"<<std::endl;

std::cout<<"--------------------------------------------"<<std::endl;
std::cout<<"----------------- S1+S2 STATS --------------"<<std::endl;
std::cout<<"--------------------------------------------"<<std::endl;
std::cout<<"LY: "<<h16->GetMean(1)<<" +- "<<h16->GetMeanError(1)<<" keV/MeV"<<std::endl;
std::cout<<"Scintillated: "<<Nscint<<" +- "<<Nscint_err<<" photons"<<std::endl;
std::cout<<"Detected S1+S2: "<<RdetTOT<<" +- "<<RdetTOT_err<<" %"<<std::endl;
std::cout<<"Escaped: "<<Rescaped<<" +- "<<Rescaped_err<<" %"<<std::endl;
std::cout<<"Absorbed: "<<Rabsorbed<<" +- "<<Rabsorbed_err<<" %"<<std::endl;
std::cout<<"<Lph>det: "<<h11->GetMean(1)<<" +- "<<h11->GetMeanError(1)<<" mm"<<std::endl;
std::cout<<"<Lph>abs: "<<h12->GetMean(1)<<" +- "<<h12->GetMeanError(1)<<" mm"<<std::endl;
std::cout<<"<Lph>all: "<<h13->GetMean(1)<<" +- "<<h13->GetMeanError(1)<<" mm"<<std::endl;
std::cout<<"<Nreflect>top/bot: "<<h14->GetMean(1)<<" +- "<<h14->GetMeanError(1)<<" reflections"<<std::endl;
std::cout<<"<Nreflect>sides: "<<h15->GetMean(1)<<" +- "<<h15->GetMeanError(1)<<" reflections"<<std::endl;
}