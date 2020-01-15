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
#include <ViewField.hh>
#include <ViewFEMesh.hh>

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

  TH2F *E_hist = new TH2F("E_hist", "", 
			  300, -axis_x, axis_x,
			  300, -axis_z, axis_z);
  TH2F *V_hist = new TH2F("V_hist", "", 
			  300, -axis_x, axis_x,
			  300, -axis_z, axis_z);
  Medium *med;
  for(int i=0; i<300; i++){
    double x = E_hist->GetXaxis()->GetBinCenter(i+1);

    for(int j=0; j<300; j++){
      double z = E_hist->GetYaxis()->GetBinCenter(j+1);
      
      double ex, ey, ez, v;
      int stat;
      elm->ElectricField(0, x, z, ex, ey, ez, v, med, stat);
      
      double e_val = TMath::Sqrt(ex*ex + ey*ey + ez*ez);
      E_hist->Fill(x, z, e_val);
      V_hist->Fill(x, z, v);
    }
  }

  TFile OutFile("e_field.root", "recreate");
  E_hist->Write();
  V_hist->Write();
  OutFile.Close();
}
