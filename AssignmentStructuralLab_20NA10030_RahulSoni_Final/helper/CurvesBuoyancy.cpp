

map<float,float> buoyancyCurve;
map<float,float> weightCurve;
map<float,float> loadCurve;
map<float,float> shearForceCurve;
map<float,float> BendingMomentCurve;


float getAccurateSecArea(float st, float z)
{
    float roundOff = roundTillOne(z);
    float a1 = secArea[st][roundOff];
    float a2 = secArea[st][roundOff+0.1];

    float area = interpolate(roundOff,a1,roundOff+0.1, a2, z);
    return area;
}

void getBuoyancyCurve(float aftTrim, float forwardTrim)
{
    float slope = (forwardTrim-aftTrim)/110.0;
    for(int i=0;i<stations.size();i++)
    {
        float zVal = aftTrim + (slope*(stations[i]));      
        float a = getAccurateSecArea(stations[i],zVal);
        
        buoyancyCurve[stations[i]] = a*1.025;
    }
}


void getWeightCurve()
{
    ReadWeightFile(weightCurve);
}

void getLoadCurve()
{
  for(int i=0;i<stations.size();i++)
  {
    float x = stations[i];
    loadCurve[x]=weightCurve[x]-buoyancyCurve[x];
  }
}

void getShearForceCurve()
{
  getAreaCurve(loadCurve,shearForceCurve);
}

void getBendingMomentCurve()
{
  getAreaCurve(shearForceCurve,BendingMomentCurve);
}



