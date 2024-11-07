void analysis() {

TFile* myFile = TFile::Open("histos_progetto.root", "READ");

TH1F* h1 = ( TH1F*)myFile->Get("h_Particle_Type");
TH1F* h2 = ( TH1F*)myFile->Get("h_Phi");
TH1F* h3 = ( TH1F*)myFile->Get("h_Theta");
TH1F* h4 = ( TH1F*)myFile->Get("h_Impulse");
TH1F* h5 = ( TH1F*)myFile->Get("h_Trasverse_Impulse");
TH1F* h6 = ( TH1F*)myFile->Get("h_Energy");
TH1F* h7 = ( TH1F*)myFile->Get("h_Invariant_mass_same_sign_pi_k");
TH1F* h8 = ( TH1F*)myFile->Get("h_Invariant_mass_opp_sign_pi_k");
TH1F* h9 = ( TH1F*)myFile->Get("h_Invariant_mass_same_sign");
TH1F* h10 = ( TH1F*)myFile->Get("h_Invariant_mass_opp_sign");
TH1F* h11 = ( TH1F*)myFile->Get("h_Benchmark");

//TH1F h_opp_same =

}