#include "MovingObject.h"
ClassImp(MovingObject);


//contructors    
MovingObject::MovingObject()
  : fVx(0), fVy(0), fVz(0){}

MovingObject::MovingObject(Double_t vx, Double_t vy, Double_t vz) 
     : fVx(vx), fVy(vy), fVz(vz){}

MovingObject::~MovingObject(){}

void MovingObject::SetVelocity(Double_t vx, Double_t vy, Double_t vz){
    fVx=vx;
    fVy=vy;
    fVz=vz;    
}

Double_t MovingObject::Vx()const {
    return fVx;
}

Double_t MovingObject::Vy()const{
    return fVy;
}

Double_t MovingObject::Vz()const{
    return fVz;
}

Double_t MovingObject::Speed() const
{
    return TMath::Sqrt(
        TMath::Power(fVx, 2) +
        TMath::Power(fVy, 2) +
        TMath::Power(fVz, 2)
    );
}

Double_t MovingObject::HorizontalSpeed() const
{
    return TMath::Sqrt(
        TMath::Power(fVx, 2) +
        TMath::Power(fVy, 2)
    );
}


