# include <TFile.h>
# include "MovingObject.h"
#include <iostream>
#include <TTree.h>
# include <TH2D.h>
# include <TCanvas.h>
#include <TAxis.h>
#include <TDirectory.h>


void read(){
auto file =TFile::Open("tree_file.root", "READ");

    if (!file  || file->IsZombie()){
        std::cout<<"The file was not opened."<<std::endl;
        return ;
    }
TTree *tree=static_cast<TTree*>(file->Get("tree"));
if (!tree) {
        std::cout<<"The tree was not found."<<std::endl;
        return ;
    }
MovingObject *object=nullptr;
tree->SetBranchAddress("object", &object);

Long64_t N=tree->GetEntries();
TH2D *h1 = new TH2D(
    "h1",
    "Velocity components;v_{x} (m/s);v_{y} (m/s)",
    100, -1.5, 1.5,
    100, -1.5, 1.5
);
for (Long64_t i=0; i<N; i++){
    tree->GetEntry(i);
    h1->Fill(object->Vx(), object->Vy());
}
TCanvas *c1 = new TCanvas("c1", "Velocity components", 800, 600);
h1->Draw("COLZ");

c1->SaveAs("velocity_components.pdf");
c1->SaveAs("velocity_components.png");



    // Second histogram: selected measurements
    TCanvas *c2 = new TCanvas("c2", "Selected measurements", 800, 600);

    // Draw directly from tree into a temporary histogram
    tree->Draw(
        "sqrt(object.Vx()*object.Vx()+object.Vy()*object.Vy()):object.Vz()>>htemp(500,-1.2,1.2,500, 0 ,1.2)",
        "sqrt(object.Vx()*object.Vx()+object.Vy()*object.Vy()+object.Vz()*object.Vz())>0.50",
        "P"
    );

    // Retrieve the histogram created by TTree::Draw
    TH2D *h2 = (TH2D*)gPad->GetPrimitive("htemp");
    if (h2) {
        h2->SetTitle("Selected measurements;v_{z} (m/s);v_{xy} (m/s)");
        h2->GetXaxis()->SetTitle("Vz (m/s)");
        h2->GetYaxis()->SetTitle("Horizontal speed vxy (m/s)");
        c2->Update();
        c2->SaveAs("selected_measurements.png");
    } else {
        std::cerr << "Error: Could not retrieve histogram from TTree::Draw.\n";
    }

    // Print tree structure
    tree->Print();
file->Close();

}