#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

//ROOT
#include <TApplication.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>

//Garfield++
#include <MediumMagboltz.hh>
#include <ComponentElmer.hh>
#include <ComponentVoxel.hh>
#include <GarfieldConstants.hh>
#include <Random.hh>
#include <Sensor.hh>
#include <AvalancheMicroscopic.hh>
#include <ViewField.hh>
#include <ViewFEMesh.hh>

using namespace Garfield;

int main(){

  //const double mm = 1e-1;
  const double axis_x = 15;
  const double axis_y = 15;
  const double axis_z = 13;
  const double x_bin = 120;
  const double y_bin = 120;
  const double z_bin = 56;

  MediumMagboltz *gas = new MediumMagboltz();
  gas->SetComposition("ar",90,"c2h6",10);
  gas->SetTemperature(293.15);
  gas->SetPressure(760);
  gas->EnablePenningTransfer(0.31,0,"ar");
  gas->SetMaxElectronEnergy(200);
  gas->EnableDrift();
  gas->Initialise(true);
  //gas->LoadIonMobility("filename");

  /*
  ComponentElmer *elm = new ComponentElmer("wire_tpc/mesh.header",
					   "wire_tpc/mesh.elements",
					   "wire_tpc/mesh.nodes",
					   //"wire_tpc/mesh.boundary",
					   "wire_tpc/dielectrics.dat",
					   "wire_tpc/wire.result",
					   "cm");
  elm->EnablePeriodicityX();
  elm->EnableMirrorPeriodicityY();
  elm->SetMedium(0, gas);
  //elm->SetWeightingField("wire_tpc/wire.result")
  */

  ComponentVoxel *vox = new ComponentVoxel();
  vox->SetMesh(120,120,56,-15,15,-15,15,-1,13);
  vox->LoadElectricField("femtetM5_25.dat","XYZ",true,false);
  vox->EnablePeriodicityX();
  vox->SetMedium(0, gas);
  vox->PrintRegions();
  vox->EnableInterpolation();

  Sensor *sensor = new Sensor();
  //sensor->AddComponent(elm);
  sensor->AddComponent(vox);
  sensor->SetArea(-axis_x,-axis_y,-axis_z,
		  axis_x,axis_y,axis_z);
  
  std::string Title = "wire_e_field";

  TH2F *E_hist = new TH2F("E_hist", Title.c_str(), 
			  x_bin, -axis_x, axis_x,
			  z_bin, -1, axis_z);
			  //y_bin, -axis_y, axis_y);
  TH2F *V_hist = new TH2F("V_hist", "", 
			  x_bin, -axis_x, axis_x,
			  z_bin, -1, axis_z);
			  //y_bin, -axis_y, axis_y);
  

  Medium *med;
  for(int i=1;i<x_bin;i++){
    double x = E_hist->GetXaxis()->GetBinCenter(i+1);
     for(int j=1;j<z_bin;j++){
       double z = E_hist->GetYaxis()->GetBinCenter(j+1);
       
       double ex, ey, ez, v;
       int stat;
       vox->ElectricField(x, 5, z, ex, ey, ez, v, med, stat);

       double e_val = TMath::Sqrt(ex*ex + ey*ey + ez*ez);
       E_hist->Fill(x, z, e_val);
       V_hist->Fill(x, z, v);
     }
  }

  std::string filename = "wire_e_field.root";
  TFile OutFile(filename.c_str(), "recreate");
  
  //E_hist->Scale(1e-3);
  E_hist->Write();
  V_hist->Write();
  OutFile.Close();

  std::cout << "owari....<(._.)>" << std::endl;

return 0;
}

