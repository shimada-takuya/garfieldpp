#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

// ROOT
#include <TApplication.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>

// Garifeld++
#include <MediumMagboltz.hh>
#include <ComponentElmer.hh>
#include <GarfieldConstants.hh>
#include <Random.hh>
#include <Sensor.hh>
#include <AvalancheMicroscopic.hh>
#include <AvalancheMC.hh>
#include <ViewField.hh>
#include <ViewFEMesh.hh>
#include <Plotting.hh>

using namespace Garfield;

int main(int argc, char *argv[]){
  TApplication *app = new TApplication("app", &argc, argv);

  const double lem_th = 0.04;          // LEM thickness in cm
  const double lem_cpth = 0.0035;      // Copper thickness
  const double lem_pitch = 0.07;       // LEM pitch in cm
  const double axis_x = 0.1;
  const double axis_y = 0.1;
  const double axis_z = 0.25 + lem_th/2 + lem_cpth;
  // Set the electron start parameters.
  const double zi = lem_th/2 + lem_cpth + 0.1;
  double ri = (lem_pitch/2)*RndmUniform();
  double thetai = RndmUniform()*TwoPi;
  double xi = ri*cos(thetai);
  double yi = ri*sin(thetai);

  MediumMagboltz *gas = new MediumMagboltz();
  gas->SetComposition("ar", 90.,
                      "c2h6", 10.);
  gas->SetTemperature(293.15);        // [K]
  gas->SetPressure(760.);             // [Torr]
  gas->EnablePenningTransfer(0.31, 0, "ar");
  gas->SetMaxElectronEnergy(200.);    // [eV]
  gas->EnableDrift();
  gas->Initialise(true);
  gas->LoadIonMobility("/usr/local/Garfield/Data/IonMobility_Ar+_Ar.txt");

  ComponentElmer *elm 
    = new ComponentElmer("gemcell/mesh.header",
                         "gemcell/mesh.elements",
                         "gemcell/mesh.nodes",
                         "gemcell/dielectrics.dat",
                         "gemcell/gemcell.result",
                         "cm");
  elm->SetWeightingField("gemcell/gemcell_WTlel.result", "wtlel");
  elm->EnablePeriodicityX();
  elm->EnableMirrorPeriodicityY();
  elm->SetMedium(0, gas);

  double tEnd = 500.0;
  int nsBins = 500;
  Sensor *sensor = new Sensor();
  sensor->AddComponent(elm);
  sensor->SetArea(-axis_x,-axis_y,-axis_z,axis_x,axis_y,axis_z);
  sensor->AddElectrode(elm, "wtlel");
  sensor->SetTimeWindow(0., tEnd/nsBins, nsBins);

  AvalancheMicroscopic *aval = new AvalancheMicroscopic();
  aval->SetSensor(sensor);
  aval->EnableSignalCalculation();
  
  AvalancheMC *ion = new AvalancheMC();
  ion->SetSensor(sensor);
  ion->SetDistanceSteps(2.e-4);
  ion->EnableSignalCalculation();

  sensor->ClearSignal();
  aval->AvalancheElectron(xi, yi, zi, 0, 0, 0);
  for(int i=0; i<nsBins; i++){
    std::cout << (i * tEnd/nsBins) << '\t'
	      << sensor->GetSignal("wtlel", i) << '\t' 
	      << sensor->GetElectronSignal("wtlel", i) << '\t'
	      << sensor->GetIonSignal("wtlel", i) << std::endl;
  }
}

