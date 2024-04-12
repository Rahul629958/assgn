map<string, map<float, map<float, float>>> tankAreaCurveSectional;
map<string, float> tankRequiredLevel;
map<string, float> tankRequiredArea;
map<float, float> loadAtStation;
map<float, float> weightTankLoad;
map<float, float> loadCurveTank, shearForceCurveTank, BendingMomentCurveTank;

float getAreaTankSecHelper(vector<float> z, vector<float> y, float minY)
{
    z.push_back(z[z.size() - 1]);
    y.push_back(y[minY]);

    return polygonArea(z, y);
}

void getAreaTankCurve(string tankName)
{
    map<float, vector<pair<float, float>>> tank = tankInfo[tankName];
    for (auto p : tank)
    {

        float minY = 10.0;
        float minZ = 20.0;
        vector<float> z, y;
        for (auto v : p.second)
        {
            y.push_back(v.first);
            z.push_back(v.second);
            minY = min(minY, v.first);
            minZ = min(minZ, v.second);
            float areaTillZ = getAreaTankSecHelper(z, y, minY);
            tankAreaCurveSectional[tankName][p.first][v.second] = (minZ == v.second ? 0.0 : areaTillZ);
        }
    }
}

float getLevel(map<float, float> areaCurve, float requiredArea)
{
    float level = 0.0;
    vector<float> fx, x;
    for (auto a : areaCurve)
    {
        fx.push_back(a.first);
        x.push_back(a.second);
    }
    int n = x.size();
    for (int i = 0; i < n - 1; i++)
    {
        float fx1 = fx[i];
        float fx2 = fx[i + 1];
        float x1 = x[i];
        float x2 = x[i + 1];
        if (x2 >= requiredArea && x1 <= requiredArea)
        {
            return round2(interpolate(x1, fx1, x2, fx2, requiredArea));
        }
    }
}

void getRequiredLevel(string tankName, float percentFilling)
{
    float finalLevel = 0.0;
    int count = 0;
    for (auto section : tankAreaCurveSectional[tankName])
    {
        float totalArea = section.second.rbegin()->second;
        float requiredArea = (percentFilling / 100.00) * totalArea;
        tankRequiredArea[tankName] = requiredArea;
        float level = getLevel(section.second, requiredArea);
        finalLevel += level;
        count++;
    }
    finalLevel = finalLevel / (float)count;
    tankRequiredLevel[tankName] = finalLevel;
}

void getLoadEachStation()
{
    vector<float> reqArea, xLoc;
    for (auto ta : tankRequiredArea)
    {
        reqArea.push_back(ta.second);
    }
    for (auto s : tankAreaCurveSectional)
    {
        for (auto p : s.second)
        {
            xLoc.push_back(p.first);
            break;
        }
    }

    for (auto s : stations)
    {
        for (int i = 0; i < xLoc.size() - 1; i++)
        {
            float fx1 = reqArea[i];
            float fx2 = reqArea[i + 1];
            float x1 = xLoc[i];
            float x2 = xLoc[i + 1];
            if (x1 <= s && x2 >= s)
            {
                float area = interpolate(x1, fx1, x2, fx2, s);
                loadAtStation[s] = 1.025 * area;
                break;
            }
        }
    }
}

void getWeightWithTankLoad()
{
    for (auto s : stations)
    {
        weightTankLoad[s] = loadAtStation[s] + weightCurve[s];
    }
}

void getLoadCurveWithTank()
{
    for (int i = 0; i < stations.size(); i++)
    {
        float x = stations[i];
        loadCurveTank[x] = weightTankLoad[x] - buoyancyCurve[x];
    }
}

void getShearForceCurveWithTank()
{

    getAreaCurve(loadCurveTank, shearForceCurveTank);
}
void getBendingMomentCurveWithTank()
{

    getAreaCurve(shearForceCurveTank, BendingMomentCurveTank);
}





void printCurveDataTank()
{
    fstream file;
    file.open("outputFiles/curveDataTank.txt", ios::out);
    if (!file)
    {
        cout << "\nTry Again, system compatibility issue.\n";
    }
    else
    {
        cout<<"--------------------------------------------------------------------------------------------"<<endl;
        cout << "CURVE_DATA_TANK FILE GENERATED SUCCESSFULLY, check at outputFiles/curveDataTank.txt"<< endl;
        // cout<<"(For checking Graph plot, you can visit outputFiles/OutputExcelFile.xlsx)"<<endl;
        cout<<"--------------------------------------------------------------------------------------------"<<endl;
        //-----------------------------------------------------------------------------------------------

        string s = string(8,' ');
        file<<"Station"<<s<<"Buoyancy_curve"<<s<<"Load_Tank"<<s<<"Shear_Tank"<<s<<"Bending_Tank"<<endl;
        file<<endl;
        s = string(10,' ');
        for(auto p: buoyancyCurve)
        {
            float st = p.first;
            string sts = fts(p.first);
            string b = fts(p.second);
            string l = fts(loadCurveTank[st]);
            string sF = fts(shearForceCurveTank[st]);
            string bm = fts(BendingMomentCurveTank[st]);



            file<<sts<<s<<b<<s<<l<<s<<sF<<s<<bm<<endl;

        }

        //-------------------------------------------------------------------------------------------------
        file.close();
    }
}