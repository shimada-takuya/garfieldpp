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

  MediumMagboltz *gas = new MediumMagboltz();
  gas->SetComposition("ar", 90.,
                      "c2h6", 10.);
  gas->SetTemperature(293.15);        // [K]
  gas->SetPressure(760.);             // [Torr]
  gas->EnablePenningTransfer(0.31, 0, "ar");
  gas->SetMaxElectronEnergy(200.);    // [eV]
  gas->EnableDrift();
  gas->Initialise(true);

  double vx, vy, vz;
  double dl, dt;
  double alpha, eta, tof;
  double vxe, vye, vze, dle, dte, ale, ete;
  double Eval = 400;
  
  gas->RunMagboltz(Eval, 0, 0, 10, true,
		   vx, vy, vz, dl, dt, alpha, eta,
		   vxe, vye, vze, dle, dte, ale, ete,
		   tof);
  std::cout << " E [V/cm] : " << Eval << std::endl;
  std::cout << " Drift V [cm/ns] : " 
	    << '\t' << vz << " " << vze << "%" << std::endl;
  std::cout << " Diff. L [cm^0.5]: " 
	    << '\t' << dl << " " << dle << "%" << std::endl;
  std::cout << " Diff. T [cm^0.5]: " 
	    << '\t' << dt << " " << dte << "%" << std::endl;
}
