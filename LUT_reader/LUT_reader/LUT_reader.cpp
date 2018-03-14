// LUT_reader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <Kinect.h>


int main()
{
	IKinectSensor *sensor = nullptr;
	ICoordinateMapper *coordinateMapper = nullptr;
	HRESULT kinectResult;
	UINT32 tableEntryCount;
	PointF* tableEntries = nullptr;
	kinectResult = GetDefaultKinectSensor(&sensor);
	
	
	if (SUCCEEDED(kinectResult)){
		kinectResult=sensor->Open();
	}
	if (SUCCEEDED(kinectResult)) {
		kinectResult=sensor->get_CoordinateMapper(&coordinateMapper);
	}
	if (SUCCEEDED(kinectResult)) {
		kinectResult= coordinateMapper->GetDepthFrameToCameraSpaceTable(&tableEntryCount, &tableEntries);
	}
	//Look Up Table 
	
	std::ofstream tableSafe;
	tableSafe.open("Lookuptable.txt");
	bool saveDone = false;
	
	if (SUCCEEDED(kinectResult)) {
		while(!saveDone){
			kinectResult = coordinateMapper->GetDepthFrameToCameraSpaceTable(&tableEntryCount, &tableEntries);
			for (int i = 0; i < 217088; i++){
				if (tableEntries[i].X != -INFINITY) {
					saveDone = true;
					tableSafe << tableEntries[i].X << '\n' << tableEntries[i].Y << '\n';
				}
			}
		}
		tableSafe.flush();
		tableSafe.close();
	}
	coordinateMapper->Release();
	sensor->Close();

	
	
	return 0;
}

