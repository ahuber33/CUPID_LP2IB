void LD1_multimodels(){

    const char *models[] = {"unified"};
    int i, j;
    for (i = 0; i < 1; i++) {
        for (j = 0; j <= 10; j++) {
            char filename[50];
            double polish = j * 0.1;
            snprintf(filename, sizeof(filename), "output_%s_dielectric_dielectric_ground_%.1f", models[i], polish);
            //std::cout<<"------------------------------------------------------------------"<<std::endl;
            //std::cout<<"opening file "<<filename<<std::endl;

            TString filepath = "../Resultats/";
            filepath += filename;
            filepath += ".root";
            TFile *f = TFile::Open(filepath);
            TTree *Input_tree = (TTree*)f->Get("Input");
            TTree *Optical_tree = (TTree*)f->Get("Optical");
            
            TH1* h1 = new TH1I("h1", "Yield [photons/MeV]", 50.0, 0.0, 0.0);
            TH1* h2 = new TH1I("h2", "Yield [keV/MeV]", 50.0, 0.0, 0.0);

            float E_dep_event_LMO;
            float E_dep_eV;
            int detected;
            vector<float>* detected_wavelength_LD1 = nullptr;

            Optical_tree->SetBranchAddress("deposited_energy_event", &E_dep_event_LMO);
            Optical_tree->SetBranchAddress("detected_LD1", &detected);
            Optical_tree->SetBranchAddress("detected_wavelength_LD1", &detected_wavelength_LD1);

            for (int i = 0; i < Optical_tree->GetEntries(); i++)
            {
                Optical_tree->GetEntry(i);
                E_dep_eV = 0;
                h1->Fill(detected/(E_dep_event_LMO/1000));
                for(int j=0;j<(detected_wavelength_LD1->size());j++)
                {
                    E_dep_eV += (1240 / detected_wavelength_LD1->at(j));
                }

                h2->Fill(E_dep_eV/E_dep_event_LMO);
            }

            // Redirect std::cout to suppress the output
            std::ofstream null_stream("/dev/null");  // For Linux/Mac
            // std::ofstream null_stream("nul");  // For Windows
            std::streambuf* original_cout = std::cout.rdbuf();
            std::cout.rdbuf(null_stream.rdbuf());
            TF1 *f1 = new TF1 ("f1", "gaus", 0., 0.);
            h1->Fit("f1", "R");
            TF1 *f2 = new TF1 ("f2", "gaus", 0., 0.);
            h2->Fit("f2", "R");
            std::cout.rdbuf(original_cout);

            double mean_gauss = f2->GetParameter(1);
            double mean_gauss_error = f2->GetParError(1);

            std::cout<<models[i]<<" polish="<<polish<<" | MEAN GAUSS = "<<mean_gauss<<" +- "<<mean_gauss_error<<
            " | MEAN = "<<h2->GetMean(1)<<" +- "<<h2->GetMeanError(1)<<std::endl;

       }
    }
}