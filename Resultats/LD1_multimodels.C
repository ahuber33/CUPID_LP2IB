void LD1_multimodels(){

    const char *models[] = {"unified", "glisur"};
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j <= 10; j++) {
            char filename[50];
            double polish = j * 0.1;
            snprintf(filename, sizeof(filename), "output_%s_dielectric_dielectric_ground_%.1f", models[i], polish);
            //std::cout<<"------------------------------------------------------------------"<<std::endl;
            //std::cout<<"opening file "<<filename<<std::endl;

            TString filepath = "../Resultats/n_1/";
            filepath += filename;
            filepath += ".root";
            TFile *f = TFile::Open(filepath);
            TTree *Input_tree = (TTree*)f->Get("Input");
            TTree *Optical_tree = (TTree*)f->Get("Optical");
            
            TH1* h1 = new TH1I("h1", "Yield [photons/MeV]", 50.0, 0.0, 0.0);

            float E_dep_event_LMO;
            int detected;
            Optical_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO);
            Optical_tree->SetBranchAddress("detected_LD1", &detected);

            for (int i = 0; i < Optical_tree->GetEntries(); i++)
            {
                Optical_tree->GetEntry(i);
                h1->Fill(detected/(E_dep_event_LMO/1000));
            }

            // Redirect std::cout to suppress the output
            std::ofstream null_stream("/dev/null");  // For Linux/Mac
            // std::ofstream null_stream("nul");  // For Windows
            std::streambuf* original_cout = std::cout.rdbuf();
            std::cout.rdbuf(null_stream.rdbuf());
            TF1 *f1 = new TF1 ("f1", "gaus", 0., 0.);
            h1->Fit("f1", "R");
            std::cout.rdbuf(original_cout);

            double mean_gauss = f1->GetParameter(1);
            double mean_gauss_error = f1->GetParError(1);

            std::cout<<models[i]<<" polish="<<polish<<" | "<<mean_gauss<<" +- "<<mean_gauss_error<<" | "<<h1->GetMean(1)<<std::endl;

       }
    }
}