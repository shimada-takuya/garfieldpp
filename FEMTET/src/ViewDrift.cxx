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
#include <TTree.h>

// Garifeld++
#include <MediumMagboltz.hh>
#include <ComponentElmer.hh>
#include <ComponentVoxel.hh>
#include <GarfieldConstants.hh>
#include <Random.hh>
#include <Sensor.hh>
#include <AvalancheMicroscopic.hh>
#include <AvalancheMC.hh>
#include <ViewField.hh>
#include <ViewFEMesh.hh>
#include <Plotting.hh>

using namespace Garfield;

int main(){

	const double axis_x = 15;
	const double axis_y = 15;	
	const double axis_z = 13;

	//Set the electron start parameters
  
  /* muon simulation
	double zi[33] =  {5.1,5.1,5.1,5.1,5.1,5.1,5.1,5.1,5.1,5.1,5.1,
                    6.1,6.4,6.7,7.0,7.3,7.6,7.9,8.2,8.5,8.8,9.1,
                    8.1,7.5,6.9,6.3,5.7,5.1,4.5,3.9,3.3,2.7,2.1};
  double xi[33] =  {-5,-4,-3,-2,-1,0,1,2,3,4,5,
                    -5,-4,-3,-2,-1,0,1,2,3,4,5,
                    -5,-4,-3,-2,-1,0,1,2,3,4,5};
  double yi[33] =  {-5,-4,-3,-2,-1,0,1,2,3,4,5,
                    -5,-4,-3,-2,-1,0,1,2,3,4,5,
                    -5,-4,-3,-2,-1,0,1,2,3,4,5};
  */
  
  /* diffusion & z-endpoint
  double zi[54] = {1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1,
    1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1,
    1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1,
    1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1,
    1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1,
    1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1};
  double xi[54] = {0,0,0,0,0,0,0,0,0,
    3,3,3,3,3,3,3,3,3,
    5,5,5,5,5,5,5,5,5,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0};
  double yi[54] = {0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    3,3,3,3,3,3,3,3,3,
    5,5,5,5,5,5,5,5,5};
  */

  /* symmetry
  double zi[21] = {9.1,9.1,9.1,9.1,
  9.1,9.1,9.1,9.1,
  9.1,9.1,9.1,9.1,
  9.1,9.1,9.1,9.1,
  9.1,9.1,9.1,9.1,9.1};
  double xi[21] = {5,-5,5,-5,
  4,-4,4,-4,
  3,-3,3,-3,
  2,-2,2,-2,
  1,-1,1,-1,0};
  double yi[21] = {5,5,-5,-5,
  4,4,-4,-4,
  3,3,-3,-3,
  2,2,-2,-2,
  1,1,-1,-1,0};
  
  */
  /* same point error
  double zi[90] = {9.1,9.1,9.1,9.1,9.1,9.1,9.1,9.1,9.1,9.1,
    8.1,8.1,8.1,8.1,8.1,8.1,8.1,8.1,8.1,8.1,
    7.1,7.1,7.1,7.1,7.1,7.1,7.1,7.1,7.1,7.1,
    6.1,6.1,6.1,6.1,6.1,6.1,6.1,6.1,6.1,6.1,
    5.1,5.1,5.1,5.1,5.1,5.1,5.1,5.1,5.1,5.1,
    4.1,4.1,4.1,4.1,4.1,4.1,4.1,4.1,4.1,4.1,
    3.1,3.1,3.1,3.1,3.1,3.1,3.1,3.1,3.1,3.1,
    2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,
    1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1};
  double xi[90];
  for(int i=0;i<90;i++)xi[i]=0;
  double yi[90];
  for(int i=0;i<90;i++)yi[i]=0;
  */
  
  //double zi = 9.5;
  //double xi = 5;
  //double yi = 5;
	double zi[9] = {1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1};
	
  double xi[40] = {1,-1,-1,1,
                  2,-2,-2,2,
                  3,-3,-3,3,
                  4,-4,-4,4,
                  5,-5,-5,5,

                  1,0,-1,0,
                  2,0,-2,0,
                  3,0,-3,0,
                  4,0,-4,0,
                  5,0,-5,0
                  };
	
  double yi[40] = {1,1,-1,-1,
                  2,2,-2,-2,
                  3,3,-3,-3,
                  4,4,-4,-4,
                  5,5,-5,-5,

                  0,1,0,-1,
                  0,2,0,-2,
                  0,3,0,-3,
                  0,4,0,-4,
                  0,5,0,-5
                  };


  

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
  vox->EnableMirrorPeriodicityY();
  vox->SetMedium(0, gas);
  //vox->PrintRegions();
  vox->EnableInterpolation();

  Sensor *sensor = new Sensor();
  //sensor->AddComponent(elm);
  sensor->AddComponent(vox);
  sensor->SetArea(-axis_x,-axis_y,0,axis_x,axis_y,axis_z);

  ViewDrift *viewDrift = new ViewDrift();
  viewDrift->SetArea(-axis_x,-axis_y,-1,axis_x,axis_y,axis_z);

  TCanvas *win = new TCanvas("win","",0,0,800,400);
  win->SetFillColor(0);
  win->SetFrameFillColor(0);

  ViewFEMesh *FE = new ViewFEMesh();
  FE->SetCanvas(win);
  //FE->SetComponent(vox);
  FE->SetPlane(0,-1,0,0,0,0);
  FE->SetFillMesh(true);
  FE->SetColor(0, kOrange);
  FE->SetColor(1, kGreen);
  FE->SetColor(2, kGreen);
  FE->SetColor(3, kGreen);

  AvalancheMicroscopic *aval = new AvalancheMicroscopic();
  aval->SetSensor(sensor);
  aval->EnablePlotting(viewDrift);

  /*
     AvalancheMC *ion = new AvalancheMC();
     ion->SetSensor(sensor);
     ion->SetDistanceSteps(1.e-1);
     ion->EnablePlotting(viewDrift);
     */

  TFile *fout = new TFile("endpoint.root","recreate");
  //std::ofstream ofs("endpoint.dat");

  double end_x, end_y, end_t;
  TTree *tree = new TTree("tree","endpoint");
  tree->Branch("end_x", &end_x, "end_x/F");
  tree->Branch("end_y", &end_y, "end_y/F");
  tree->Branch("end_t", &end_t, "end_t/F");

  TH2D *hist_2D = new TH2D("hist_2D","EndPoints",100,-1,1,100,-1,1);

  char name[100];

  //double t[10];
  for(int n=0;n<40;n++){        
    for(int k=0;k<9;k++){
      sprintf(name,"EndPointM/symme/end%d_z%d.dat",n,k);
      std::ofstream ofs(name);
      for(int j=0;j<1000;j++){
        end_t = 0;
        //aval->DriftElectron(xi, yi, zi, 0, 0, 0);
        aval->DriftElectron(xi[n], yi[n], zi[k], 0, 0, 0);
        Int_t nd = aval->GetNumberOfElectronEndpoints();
        //std::cout << "nd = " << nd <<std::endl;
        double x1, y1, z1, e1;
        double t1 = 0;
        Int_t Stat; 
        for(int i=0; i<nd; i++){
          double x0, y0, z0, e0;
          double t0 = 0;
          aval->GetElectronEndpoint(i,
              x0, y0, z0, t0, e0,
              x1, y1, z1, t1, e1,
              Stat);
          //ion->DriftIon(x0, y0, z0, t0);
          //std::cout << "step time = " << t1 << " - " << t0 << " = " << t1-t0 << " [ns]" <<std::endl;
          //std::cout << "End Energy = " << e1 << " - " << e0 << " = " << e1-e0 << " [eV]" <<std::endl;
          std::cout << "Stat = " << Stat <<std::endl;

        }
        end_x = x1;
        end_y = y1;
        end_t = t1;
        std::cout << "RUN Number [ " << n+1 << ", " << k+1 << " ] ..." <<std::endl;
        std::cout << "Event Number [ " << j+1 << " ] ..." <<std::endl;
        std::cout << "x = " << x1 << ", y = " << y1 << ", z = " << z1 << ", time = " << t1 << ", E = " << e1 <<std::endl;
        ofs << x1 << " " << y1 << " " << z1 << " " << end_t << " " << e1 << " " << Stat << "\n";
        tree->Fill();
        hist_2D->Fill(end_x,end_y);
      }
      ofs.close();
    }
  }


  tree->Write();
  hist_2D->Write();
  fout->Close();

  win->cd();
  FE->SetArea(-15, -1, 0, 15, 15, 0);
  FE->EnableAxes();
  FE->SetViewDrift(viewDrift);
  FE->SetXaxisTitle("[mm]");
  FE->SetYaxisTitle("[mm]");
  FE->Plot();
  win->Update();
  win->Print("ele_track.png");

}

























