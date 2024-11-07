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

for(int i = 1; i <= 7; i++) {
      std::cout<< "Particle Type Bin " << i << " content: " << 
      h_Particle_Type->GetBinContent(i) << '\n' << "With error: " <<
      h_Particle_Type->GetBinError(i) << '\n';
    }

TF1 *Uniform_Phi = new TF1("Uniform_Phi", "[0]/(2 * TMath::Pi())",
                           0., 2 * TMath::Pi());
Uniform_Phi->SetParameters(0, 1E5);
h_Phi->Fit("Uniform_Phi", "Q");
std::cout<< "Phi fit parameter: " << Uniform_Phi->GetParameters(0)
    << ", Chi^2/NDF: " << Uniform_Phi->GetChiSquare()/Uniform_Phi->GetNDF()
    << ", fit probability: " << Uniform_Phi->GetProb() << '\n';

TF1 *Uniform_Theta = new TF1("Uniform_Theta", "[0]/(TMath::Pi())",
                             0., TMath::Pi());
Uniform_Theta->SetParameters(0, 1E5);
h_Theta->Fit("Uniform_Theta", "Q");
std::cout<< "Theta fit parameter: " << Uniform_Theta->GetParameters(0)
    << ", Chi^2/NDF: " << Uniform_Theta->GetChiSquare()/Uniform_Theta->GetNDF()
    << ", fit probability: " << Uniform_Theta->GetProb() << '\n';

TF1 *Expo_Impulse = new TF1("Expo_Impulse", "[0] * exp(-[1] * x)", 0., 7.);
Expo_Impulse->SetParameters(0, 7E5);
Expo_Impulse->SetParameters(1, 1.);
h_Impulse->Fit("Expo_Impulse", "Q");
std::cout<< "Impulse fit parameter: " << Expo_Impulse->GetParameters(0)
    << ", Chi^2/NDF: " << Expo_Impulse->GetChiSquare()/Expo_Impulse->GetNDF()
    << ", fit probability: " << Expo_Impulse->GetProb() << '\n';

}