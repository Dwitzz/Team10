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


h10->Add(h9, -1);
h8->Add(h8, h7, 1, -1);


TCanvas *c1 = new TCanvas("c1", "Canvas", 800, 800);
h10->Draw("H");
TCanvas *c2 = new TCanvas("c2", "Canvas", 800, 800);
h8->Draw("H");
TCanvas *c3 = new TCanvas("c3", "Canvas", 800, 800);
h11->Draw("H");
/*TCanvas *c2 = new TCanvas("c2", "2x2 Canvas", 800, 800);
  c2->Divide(2, 2);
  c2->cd(1);
  h7->Draw("H");
  c2->cd(2);
  h8->Draw("H");
  c2->cd(3);
  h9->Draw("H");
  c2->cd(4);
  h10->Draw("H");
  c2->Update();*/


}