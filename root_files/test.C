void test(){

    TFile *f = TFile::Open("../Resultats");
    TTree *Optical_tree = (TTree*)f->Get("Optical");


    int detected_LD1;
    int detected_LD2;
    vector<float>* x_entrance = nullptr;
    vector<float>* z_entrance = nullptr;

    Optical_tree->SetBranchAddress("detected_LD1", &detected_LD1);
    Optical_tree->SetBranchAddress("detected_LD2", &detected_LD2);
    Optical_tree->SetBranchAddress("x_entrance", &x_entrance);
    Optical_tree->SetBranchAddress("z_entrance", &z_entrance);

    TCanvas *c1 = new TCanvas("c1", "Light Yield / position");


    //The number of x-y counts (ignores s)
    int nbins = 20;
   TH2D *hEntries = new TH2D("hEntries","hEntries", nbins,-25,25,nbins,-25,25);
   //The mean value of s for each x-y bin.
   TH2D *hMean1 = (TH2D*) hEntries->Clone("hMean1");
   TH2D *hMean2 = (TH2D*) hEntries->Clone("hMean2");
   hMean1->SetTitle("S1 Light Yield");
   hMean2->SetTitle("S2 Light Yield");

   for (int i=0;i<Optical_tree->GetEntries();i++) {

    Optical_tree->GetEntry(i);
    float x;
    float z;
    
    x = x_entrance->at(0);
    z = z_entrance->at(0);

      //Find the correct bin
      int bin = hEntries->FindBin(x, z);

      //First add another count to the entries histogram.
      hEntries->Fill(x, z);
      int numBinEntries = hEntries->GetBinContent(bin);

      //Compute the new mean
      double prevMean1 = hMean1->GetBinContent(bin);
      double newMean1 = prevMean1 + (detected_LD1 - prevMean1) / numBinEntries;
      double prevMean2 = hMean2->GetBinContent(bin);
      double newMean2 = prevMean2 + (detected_LD2 - prevMean2) / numBinEntries;

      hMean1->SetBinContent(bin, newMean1);
      hMean2->SetBinContent(bin, newMean2);
   }

   c1->DivideSquare(2);
   c1->cd(1);

   hMean1->SetStats(0);
   hMean1->Draw("COLZ");
   hMean1->GetXaxis()->SetTitle("x [mm]");
    hMean1->GetYaxis()->SetTitle("z [mm]");

    c1->cd(2);

   hMean2->SetStats(0);
   hMean2->Draw("COLZ");
   hMean2->GetXaxis()->SetTitle("x [mm]");
    hMean2->GetYaxis()->SetTitle("z [mm]");
}