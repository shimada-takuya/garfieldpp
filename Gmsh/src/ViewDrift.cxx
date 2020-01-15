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
	const double zi = 8;
	//double ri = (1)/RndmUniform(); 
	//double thetai = RndmUniform()*TwoPi;
	double xi = 5;//ri*cos(thetai);
	double yi = 5;//ri*sin(thetai);

	MediumMagboltz *gas = new MediumMagboltz();
	gas->SetComposition("ar",90,"c2h6",10);
	gas->SetTemperature(293.15);
	gas->SetPressure(760);
	gas->EnablePenningTransfer(0.31,0,"ar");
	gas->SetMaxElectronEnergy(200);
	gas->EnableDrift();
	gas->Initialise(true);
	//gas->LoadIonMobility("filename");

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

	Sensor *sensor = new Sensor();
	sensor->AddComponent(elm);
	sensor->SetArea(-axis_x,-axis_y,-1,axis_x,axis_y,axis_z);

	ViewDrift *viewDrift = new ViewDrift();
	viewDrift->SetArea(-axis_x,-axis_y,-1,axis_x,axis_y,axis_z);

	TCanvas *win = new TCanvas("win","",0,0,800,400);
	win->SetFillColor(0);
	win->SetFrameFillColor(0);

	ViewFEMesh *FE = new ViewFEMesh();
	FE->SetCanvas(win);
	FE->SetComponent(elm);
	FE->SetPlane(0,-1,0,0,0,0);
	FE->SetFillMesh(true);
	FE->SetColor(0, kOrange);
	FE->SetColor(1, kGreen);
	FE->SetColor(2, kGreen);
	FE->SetColor(3, kGreen);

	AvalancheMicroscopic *aval = new AvalancheMicroscopic();
	aval->SetSensor(sensor);
	aval->EnablePlotting(viewDrift);

	AvalancheMC *ion = new AvalancheMC();
	ion->SetSensor(sensor);
	ion->SetDistanceSteps(1.e-1);
	ion->EnablePlotting(viewDrift);

	TFile *fout = new TFile("endpoint.root","recreate");

	double end_x, end_y, end_t;
	TTree *tree = new TTree("tree","endpoint");
	tree->Branch("end_x", &end_x, "end_x/F");
	tree->Branch("end_y", &end_y, "end_y/F");
	tree->Branch("end_t", &end_t, "end_t/F");
	
	TH2D *hist_2D = new TH2D("hist_2D","EndPoints",100,-1,1,100,-1,1);

	std::ofstream ofs("endpoint.dat");
	
	//double t[10];
	for(int j=0;j<1000;j++){
		end_t = 0;
		aval->DriftElectron(xi, yi, zi, 0, 0, 0);
		Int_t nd = aval->GetNumberOfElectronEndpoints();
		//std::cout << "nd = " << nd <<std::endl;
		double x1, y1, z1, e1;
		double t1 = 0;
		for(int i=0; i<nd; i++){
			Int_t Stat; 
			double x0, y0, z0, e0;
			double t0 = 0;
			aval->GetElectronEndpoint(i,
					x0, y0, z0, t0, e0,
					x1, y1, z1, t1, e1,
					Stat);
			ion->DriftIon(x0, y0, z0, t0);
			//std::cout << "step time = " << t1 << " - " << t0 << " = " << t1-t0 << " [ns]" <<std::endl;
			//std::cout << "End Energy = " << e1 << " - " << e0 << " = " << e1-e0 << " [eV]" <<std::endl;
		
		}
		end_x = x1;
		end_y = y1;
		end_t = t1;
		std::cout << "Event Number [ " << j+1 << " ] ..." <<std::endl;
		std::cout << "x = " << x1 << ", y = " << y1 << ", z = " << z1 << ", time = " << t1 << ", E = " << e1 <<std::endl;
		ofs << x1 << " " << y1 << " " << z1 << " " << end_t << " " << e1 <<"\n";
		tree->Fill();
		hist_2D->Fill(end_x,end_y);
	}

	ofs.close();
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

























