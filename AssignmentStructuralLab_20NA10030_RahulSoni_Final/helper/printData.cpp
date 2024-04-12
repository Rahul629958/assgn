#include<string>
string fts(float val)
{
      string s = to_string(val).substr(0,8);
      return s;
}


void printHydrostaticTable()
{
    fstream file;
    file.open("outputFiles/hydrostaticTableData.txt", ios::out);
    if (!file)
    {
        cout << "\nTry Again, system compatibility issue.\n";
    }
    else
    {
        cout<<"--------------------------------------------------------------------------------------------"<<endl;
        cout << "HYDROSTATIC_DATA FILE GENERATED SUCCESSFULLY, check at outputFiles/hydrostaticTableData.txt"<<endl;
        cout<<"--------------------------------------------------------------------------------------------"<<endl;
        //-----------------------------------------------------------------------------------------------

        string s = string(13,' ');
        file<<"Draft"<<s<<"Vol"<<s<<"mass"<<s<<"LCB"<<s<<"WPA"<<s<<"LCF"<<endl;
        file<<endl;
        s = string(8,' ');
        for(auto p: volumeTill)
        {
            float d = p.first;
            string ds = fts(p.first);
            string vol = fts(p.second);
            string mass = fts(massTill[d]);
            string lcbVal = fts(lcb_Till[d]);
            string wpaVal = fts(WPA[d]);
            string lcfVal = fts(LCF[d]);

            file<<ds<<s<<vol<<s<<mass<<s<<lcbVal<<s<<wpaVal<<s<<lcfVal<<endl;
        }
        
        //-------------------------------------------------------------------------------------------------
        file.close();
    }
}

// print different curves (will print buoyancy curve data, load curve data, shear force data, bending moment data)
void printCurveData()
{
    fstream file;
    file.open("outputFiles/curveData.txt", ios::out);
    if (!file)
    {
        cout << "\nTry Again, system compatibility issue.\n";
    }
    else
    {
        cout<<"--------------------------------------------------------------------------------------------"<<endl;
        cout << "CURVE_DATA FILE GENERATED SUCCESSFULLY, check at outputFiles/curveData.txt"<< endl;
        cout<<"(For checking Graph plot, you can visit outputFiles/OutputExcelFile.xlsx)"<<endl;
        cout<<"--------------------------------------------------------------------------------------------"<<endl;
        //-----------------------------------------------------------------------------------------------

        string s = string(8,' ');
        file<<"Station"<<s<<"Buoyancy_curve"<<s<<"Load_Curve"<<s<<"Shear_Force"<<s<<"Bending_Moment"<<endl;
        file<<endl;
        s = string(10,' ');
        for(auto p: buoyancyCurve)
        {
            float st = p.first;
            string sts = fts(p.first);
            string b = fts(p.second);
            string l = fts(loadCurve[st]);
            string sF = fts(shearForceCurve[st]);
            string bm = fts(BendingMomentCurve[st]);



            file<<sts<<s<<b<<s<<l<<s<<sF<<s<<bm<<endl;

        }

        //-------------------------------------------------------------------------------------------------
        file.close();
    }
}

void printDataForTrim(float aftTrim, float forwardTrim)
{
    cout << endl;
    cout << "----------------------------" << endl;
    pair<float, float> volLCB = getVolumeFromTrim(aftTrim, forwardTrim);
    cout << "---Trim draft--- " << endl;
    cout << "Aft Draft: " << aftTrim << endl;
    cout << "Forward Draft: " << forwardTrim << endl<<endl;
    cout << "Volume for this trimLine: " << round2(volLCB.first) << endl;
    cout<< "Mass for this trimLine: "<<round2(volLCB.first*1.025)<<endl;
    cout << "LCB for this trimLine: " << round2(volLCB.second) << endl;
    cout << "----------------------------" << endl;
    cout << endl;
}

void printDataForDraft(float draft)
{
    cout << endl;
    cout << "----------------------------" << endl;
    float vol = volumeTill[roundTillOne(draft)];
    float lcb = lcb_Till[roundTillOne(draft)];

    cout << "Draft: " << draft << endl;
    cout << "Volume for this draft: " << vol << endl;
    cout << "LCB for this draft: " << lcb << endl;
    cout << "----------------------------" << endl;
    cout << endl;
}





