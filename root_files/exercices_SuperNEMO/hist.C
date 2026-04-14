void hist(){

TFile *f = TFile::Open("test.root"); 
TTree *tree = (TTree*)f->Get("Result_tree");

double energy_per_event;
int event_number;

tree->SetBranchAddress("E_deposit", &energy_per_event);
tree->SetBranchAddress("event_number", &event_number);

TCanvas *c1 = new TCanvas();

TH1* h1 = new TH1I("h1", "Energy deposit / Event", 100.0, 0.0, 2.5);
TH1* h2 = new TH1I("h1", "Energy deposit / Event", 100.0, 0.0, 2.5);

for (int i = 0; i < tree->GetEntries(); i++)
{
    tree->GetEntry(i);
    std::cout<<event_number<<" | "<<energy_per_event<<endl;
    h1->Fill(energy_per_event);
}
TF1 *f1 = new TF1 ("f1", "gaus", 0.8, 1.2);
TF1 *f2 = new TF1 ("f2", "gaus", 0.3, 0.7);
h1->Fit("f1", "R");
h1->Fit("f2", "R+");
h1->Draw();
}