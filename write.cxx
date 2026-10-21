#include "MovingObject.h"
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>

void write(){
    // Initialize your object e.g. as a pointer
    MovingObject *object{nullptr};
    object= new MovingObject();

    // Create your root file here

    TFile *f1 = new TFile("tree_file.root", "RECREATE");
    f1->cd();

    // Create your TTree here

    TTree *T = new TTree("tree", "data tree");


    // And the associated branches underneath
    // for example a branch with your personal object type
     Double_t v;
     Double_t v_horiz; 
     T->Branch("object", &object);

    // Now we create our loop for filling the tree with some random data
    const Int_t nMeasurements=10000;
    gRandom->SetSeed(12345);
    // For loop here
    for (Int_t i{0}; i<nMeasurements; i++){ // define how many events you want
        // Initialize your new object below

        Double_t vx = gRandom->Gaus(0.0, 0.30);
        Double_t vy = gRandom->Gaus(0.0, 0.30);
        Double_t vz = gRandom->Gaus(0.0, 0.30);
        object->SetVelocity(vx, vy, vz);


        // Now fill tree
    
        T->Fill();


        // Remember to delete it again otherwise you will have memory leak!
    }
// save the tree/file
T->Write();
f1->Close();
delete object;
delete f1;

}