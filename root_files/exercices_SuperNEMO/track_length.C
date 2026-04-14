void track_length(){
TFile *f = TFile::Open("extracted_data_sorted.root"); //ouvre le fichier
TTree *tree = (TTree*)f->Get("Event"); //recupere le TTree

int event_number;
double energy_deposed_sum;
double x_in;
double y_in;
double z_in;
double t_in;
double x_out;
double y_out;
double z_out;
double t_out;
double distance;
double temps_de_vol;
vector<double>* energy_deposed = nullptr;
vector<double>* time = nullptr;
vector<double>* x = nullptr;
vector<double>* y = nullptr;
vector<double>* z = nullptr;
vector<string>* material = nullptr;
vector<string>* particle_name = nullptr;
string particle = "e-";

tree->SetBranchAddress("event_number", &event_number); //recupere la branch event_number
tree->SetBranchAddress("energy", &energy_deposed); 
tree->SetBranchAddress("time", &time); 
tree->SetBranchAddress("x", &x); 
tree->SetBranchAddress("y", &y); 
tree->SetBranchAddress("z", &z); 
tree->SetBranchAddress("particle_name", &particle_name); 
tree->SetBranchAddress("material", &material); 

TH1* h1 = new TH1I("h1", "Temps de vol", 100.0, 0.0, 3000);

for (int i = 0; i < tree->GetEntries(); i++)
{
    tree->GetEntry(i); //accede à l'entree i

    if (x->size()>3)
    {
        for(int j=1;j<(x->size()-1);j++)
        {
            if(particle_name->at(j)==particle && material->at(j)=="tracking_gas" && material->at(j-1)=="basic::mylar")
            {
                std::cout<<"[EVENT "<<event_number<<"] E- IN | TIME: "<<time->at(j)<<" | X: "<<x->at(j)<<" | Y: "<<y->at(j)<<" | Z: "<<z->at(j)<<endl;
                x_in = x->at(j);
                y_in = y->at(j);
                z_in = z->at(j);
                t_in = time->at(j);
            }
        

            else if(particle_name->at(j)==particle && material->at(j)=="tracking_gas" && material->at(j+1)=="basic::mylar")
            {
                std::cout<<"[EVENT "<<event_number<<"] E- OUT | TIME: "<<time->at(j)<<" | X: "<<x->at(j)<<" | Y: "<<y->at(j)<<" | Z: "<<z->at(j)<<endl;
                x_out = x->at(j);
                y_out = y->at(j);
                z_out = z->at(j);
                t_out = time->at(j);
            }



        }
        if (x_in!=0 && y_in!=0 && z_in!=0 && x_out!=0 && y_out!=0 && z_out!=0 && x_in!=x_out && y_in!=y_out && z_in!=z_out)
        {
        distance = sqrt(pow(x_in-x_out,2)+pow(y_in-y_out,2)+pow(z_in-z_out,2));
        temps_de_vol = t_out - t_in;
        h1->Fill(distance);
        x_out = 0;
        y_out = 0;
        z_out = 0;
        x_in = 0;
        y_in = 0;
        z_in = 0;
        }
    }

}
h1->Draw();
}