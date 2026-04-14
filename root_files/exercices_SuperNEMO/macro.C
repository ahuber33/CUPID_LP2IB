void macro(){
TFile *f = TFile::Open("extracted_data.root"); //ouvre le fichier
TTree *tree = (TTree*)f->Get("Event"); //recupere le TTree
TFile file("test.root", "RECREATE");
TTree Result_tree("Result_tree","");

int event_number;
double energy_deposed_sum;
vector<double>* energy_deposed = nullptr;
vector<string>* particle_name = nullptr;
string particle = "e-";

Result_tree.Branch("event_number",&event_number);
Result_tree.Branch("E_deposit",&energy_deposed_sum);

tree->SetBranchAddress("event_number", &event_number); //recupere la branch event_number
tree->SetBranchAddress("energy", &energy_deposed); 
tree->SetBranchAddress("particle_name,", &particle_name); 

for (int i = 0; i < tree->GetEntries(); i++)
{
    tree->GetEntry(i); //accede à l'entree i
    energy_deposed_sum = 0;
    for(int j=0;j<energy_deposed->size();j++)
    {
        double energy_temp = energy_deposed->at(j);
        if(particle_name->at(j)==particle)
        {
            energy_deposed_sum += energy_temp;
        }

    }
    
    if(energy_deposed_sum >=0)
    {
        std::cout<<"EVENT: "<<event_number<<" | PARTICLE: "<<particle<<" | TOTAL ENERGY DEPOSIT: "<<energy_deposed_sum<<endl;
    } 

    Result_tree.Fill();
}
std::cout<<"La taille du vecteur energie depose est = "<<energy_deposed->size()<<endl;

Result_tree.Write();
file.Close();
}