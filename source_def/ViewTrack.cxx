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
  elm->EnablePeriodicityX();
  elm->EnableMirrorPeriodicityY();
  elm->SetMedium(0, gas);

  Sensor *sensor = new Sensor();
  sensor->AddComponent(elm);
  sensor->SetArea(-axis_x,-axis_y,-axis_z,axis_x,axis_y,axis_z);

  ViewDrift *viewDrift = new ViewDrift();
  viewDrift->SetArea(-axis_x, -axis_y, -axis_z,
		     axis_x, axis_y, axis_z);

  TCanvas *ViewWin = new TCanvas("ViewWin", "", 0, 0, 800, 800);
  ViewWin->SetFillColor(0);
  ViewWin->SetFrameFillColor(0);

  ViewFEMesh *vFE = new ViewFEMesh();
  vFE->SetCanvas(ViewWin);
  vFE->SetComponent(elm);
  vFE->SetPlane(0, 1, 0, 0, 0, 0);
  vFE->SetFillMesh(true);
  vFE->SetColor(1, kOrange);
  vFE->SetColor(2, kGreen);
  vFE->SetColor(3, kGreen);

  AvalancheMicroscopic *aval = new AvalancheMicroscopic();
  aval->SetSensor(sensor);
  aval->EnablePlotting(viewDrift);
  
  AvalancheMC *ion = new AvalancheMC();
  ion->SetSensor(sensor);
  ion->SetDistanceSteps(2.e-4);
  ion->EnablePlotting(viewDrift);

  aval->AvalancheElectron(xi, yi, zi, 0, 0, 0);
  Int_t nd = aval->GetNumberOfElectronEndpoints();
  for(int i=0; i<nd; i++){
    Int_t Stat;
    double x0, y0, z0, t0, e0;
    double x1, y1, z1, t1, e1;
    aval->GetElectronEndpoint(i,
			      x0, y0, z0, t0, e0,
			      x1, y1, z1, t1, e1,
			      Stat);
    ion->DriftIon(x0, y0, z0, t0);
  }
  ViewWin->cd();
  vFE->SetArea(-axis_x,-axis_z,0.,axis_x,axis_z,0.);
  vFE->EnableAxes();
  vFE->SetViewDrift(viewDrift);
  vFE->SetXaxisTitle("[cm]");
  vFE->SetYaxisTitle("[cm]");
  vFE->Plot();
  ViewWin->Update();
  ViewWin->Print("track.png");

  app->Run();
}

