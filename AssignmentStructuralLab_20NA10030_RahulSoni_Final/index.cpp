#include<algorithm>
#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;

#include "helper/Point2D.cpp"
#include "helper/MathHelper.cpp"
#include "helper/ReadInputFile.cpp"
#include "helper/GraphAreaCalculator.cpp"
#include "helper/DataFormatter.cpp"
#include "helper/SectionArea.cpp"
#include "helper/Volume.cpp"
#include "helper/WaterPlaneArea.cpp"
#include "helper/EquilibriumCondition.cpp"
#include "helper/CurvesBuoyancy.cpp"
#include "helper/printData.cpp"
#include "helper/sinWave.cpp"
#include "helper/ReadTankInput.cpp"
#include "helper/TankCalculation.cpp"


/*
----------IMPORTANT VARIABLES---------------------------------------

-> secArea --(x->{z->sectionArea})
-> volumeTill --(z->volume ) (0-9, 0.1 increment)
-> lcb_Till --(z->LCB) (0-9, 0.1 increment)
-> massTill --(z->mass) (0-9, 0.1 increment)
-> WPA --(z-> water plane area) (0-9, 0.1 increment)
-> LCF --(z-> lcf )(0-9, 0.1 increment)
-> buoyancyCurve -- (x->secArea*rho till equilibrium z for each x)
- > weightCurve
- > loadCurve
- > shearForceCurve
- > BendingMomentCurve

----------IMPORTANT FUNCTIONS-----------------------------------------
->  pair<float,float> getVolumeFromTrim(AftTrim, forwardTrim)  (return type: {Volume, LCB})
-> pair<float,float> getEquilibriumCondition(lightWeight,LCG)  (return type: {aftTrim, forwardTrim})

*/



int main()
{
    map<float,vector<pointYZ>> data;//x->{y,z};
    //Reading data from secLine.dat file
    ReadFile(data);
    //formatting the data in usable format, for futher usage
    map<float,map<float,float>> offset = makeOffset(data);//x->{z->y};

    //getting section Area For Each section Each Draft
    getSectionArea(offset);//values will be stored on secArea --variable
    getVolume();//getting Values for Volume,mass  & LCB, values will be stores on volumeTill, massTill and lcb_Till (for each draft)
    getWPA(offset);// getting values for waterplane Area & LCF, values will be stored on WPA, LCF (for each draft)
    

    float lightWeight = 2973.15;//given as ship data
    float LCG = 47.515;//given as ship data
    pair<float,float> trimCase = getEquilibriumCondition(lightWeight,LCG);//{aftTrim,forwardTrim} // implemented in helper/EquilibriumCondition.cpp
    //trim case I get: aftTrim -> 3.83, forwardTrim -> 0.63

    float aftTrim = trimCase.first;//after equilibrium calculations
    float forwardTrim = trimCase.second; //after equilibrium calculations

    //all these functions below are implemented in helper/curvesBuoyancy.cpp file
    getBuoyancyCurve(aftTrim,forwardTrim); //generate buoyancy curve from equilibrium trim condition
    getWeightCurve();//read weight file and generate weight curve (from given ship data)
    getLoadCurve(); //weight curve- buoyancy curve
    getShearForceCurve();//integration of load curve
    getBendingMomentCurve();//integration of shear force curve



//----------------------FOR PRINTING VARIOUS DATA----------------------------------------------------------------------------------------------
//all functions are implemented in 'helper/printData.cpp' file


    //print hydrostatic table (will print , draft, volume, mass, lcb, wpa, lcf)
    //printHydrostaticTable(); 
    
    //print different curves (will print buoyancy curve data, load curve data, shear force data, bending moment data)
    //printCurveData();

    //print volume lcb for a particular trim value (input -- draft at Aft, draft at Forward perpendicular)
    //printDataForTrim(3.83,0.63);

    //print volume, mass and lcb for a particular draft (input -- draft)
    //printDataForDraft(2.5);


    getSinWave(113,6);
    ReadLoadingCaseFile();

    for(auto tankName: TankNameAndFillPercent)
    {
        ReadTankInfo(tankName.first);
        getAreaTankCurve(tankName.first);
        getRequiredLevel(tankName.first,tankName.second);
    }

    getLoadEachStation();
    getWeightWithTankLoad();

    getLoadCurveWithTank();
    getShearForceCurveWithTank();
    getBendingMomentCurveWithTank();

    printCurveDataTank();
    

    
}