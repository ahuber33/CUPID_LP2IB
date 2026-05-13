void test(){

    TFile *f = TFile::Open("../Resultats/output.root");
    TTree *Optical_tree = (TTree*)f->Get("Optical");


    int detected_LD1;
    int detected_LD2;
    vector<float>* x_entrance = nullptr;
    vector<float>* z_entrance = nullptr;
    float E_dep_event_LMO;

    Optical_tree->SetBranchAddress("detected_LD1", &detected_LD1);
    Optical_tree->SetBranchAddress("detected_LD2", &detected_LD2);
    Optical_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO);
    Optical_tree->SetBranchAddress("x_entrance", &x_entrance);
    Optical_tree->SetBranchAddress("z_entrance", &z_entrance);

    TCanvas *c1 = new TCanvas("c1", "Light Yield / position");
    TCanvas *c2 = new TCanvas("c2", "Light Yield");

    //The number of x-y counts (ignores s)
    int nbins = 20;
    TH2D *hEntries = new TH2D("hEntries","hEntries", nbins,-25,25,nbins,-25,25);
    //The mean value of s for each x-y bin.
    TH2D *hMean1 = (TH2D*) hEntries->Clone("hMean1");
    TH2D *hMean2 = (TH2D*) hEntries->Clone("hMean2");
    TH2D *hMean3 = (TH2D*) hEntries->Clone("hMean3");
    hMean1->SetTitle("S1 LY / position");
    hMean2->SetTitle("S2 LY / position");
    hMean3->SetTitle("S1/S2 LY / position");

    TH1* h1 = new TH1I("h1", "S1 LY [photons/MeV]", 50.0, 0.0, 0.0);
    TH1* h2 = new TH1I("h2", "S2 LY [photons/MeV]", 50.0, 0.0, 0.0);
    TH1* h3 = new TH1I("h3", "S1/S2 LY [photons/MeV]", 50.0, 0.0, 0.0);

    for (int i=0;i<Optical_tree->GetEntries();i++) {

        Optical_tree->GetEntry(i);
        float x;
        float z;
        float LY_S1;
        float LY_S2;

        x = x_entrance->at(0);
        z = z_entrance->at(0);
        LY_S1 = (detected_LD1/(E_dep_event_LMO/1000));
        LY_S2 = (detected_LD2/(E_dep_event_LMO/1000));

        h1->Fill(LY_S1);
        h2->Fill(LY_S2);
        h3->Fill(LY_S1/LY_S2);

        //Find the correct bin
        int bin = hEntries->FindBin(x, z);

        //First add another count to the entries histogram.
        hEntries->Fill(x, z);
        int numBinEntries = hEntries->GetBinContent(bin);

        //Compute the new mean
        double prevMean1 = hMean1->GetBinContent(bin);
        double newMean1 = prevMean1 + (LY_S1 - prevMean1) / numBinEntries;
        double prevMean2 = hMean2->GetBinContent(bin);
        double newMean2 = prevMean2 + (LY_S2 - prevMean2) / numBinEntries;
        double prevMean3 = hMean3->GetBinContent(bin);
        double newMean3 = prevMean3 + ((LY_S1/LY_S2) - prevMean3) / numBinEntries;

        hMean1->SetBinContent(bin, newMean1);
        hMean2->SetBinContent(bin, newMean2);
        hMean3->SetBinContent(bin, newMean3);
   }

    c1->SetWindowSize(950, 450);
    c1->SetWindowPosition(0,0);
    c1->DivideSquare(2);
    c1->GetPad(1)->SetRightMargin(.13);
    c1->GetPad(1)->SetLeftMargin(.13);
    c1->GetPad(2)->SetRightMargin(.13);
    c1->GetPad(2)->SetLeftMargin(.13);
    c1->cd(1);

    hMean1->SetStats(0);
    hMean1->SetMinimum(50);
    hMean1->Draw();
    hMean1->GetXaxis()->SetTitle("x [mm]");
    hMean1->GetYaxis()->SetTitle("z [mm]");

    std::cout<<hMean1->GetMaximum()<<" | "<<hMean1->GetMinimumBin()<<std::endl;

    c1->cd(2);
    hMean2->SetStats(0);
    hMean2->SetMinimum(50);
    hMean2->SetMaximum(hMean1->GetMaximum());
    hMean2->Draw("COLZ");
    hMean2->GetXaxis()->SetTitle("x [mm]");
    hMean2->GetYaxis()->SetTitle("z [mm]");
    hMean2->GetZaxis()->SetTitle("LY [photons/MeV]");

    //c1->cd(3);

    //hMean3->SetStats(0);
    //hMean3->Draw("COLZ");
    //hMean3->GetXaxis()->SetTitle("x [mm]");
    //hMean3->GetYaxis()->SetTitle("z [mm]");

    c2->SetWindowSize(950, 450);
    c2->SetWindowPosition(0,505);
    c2->DivideSquare(2);
    c2->cd(1);

    h1->Draw();
    h1->GetXaxis()->SetTitle("yield [photons/MeV]");
    h1->GetYaxis()->SetTitle("events");

    c2->cd(2);

    h2->Draw();
    h2->GetXaxis()->SetTitle("yield [photons/MeV]");
    h2->GetYaxis()->SetTitle("events");

    //c2->cd(3);

    //h3->Draw();
    //h3->GetXaxis()->SetTitle("yield [photons/MeV]");
    //h3->GetYaxis()->SetTitle("events");
}