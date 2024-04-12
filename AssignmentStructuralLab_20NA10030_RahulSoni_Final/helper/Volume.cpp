map<float,float> volumeTill;
map<float,float> lcb_Till;
map<float,float> massTill;


void getVolume()
{
  for(int i=0;i<=90;i++)
  {
    float volume = 0.0;
    float moment = 0.0;

    float zVal = (float)i/10.0;
    for(int s=0;s<stations.size()-1;s++)
    {
        float a1 = secArea[stations[s]][zVal];
        float a2 = secArea[stations[s+1]][zVal];

        float m1 = a1*stations[s];
        float m2 = a2*stations[s+1];

        float dist = stations[s+1]-stations[s];

        float avgArea = (a1 + a2)/2.0;
        float avgMoment = (m1 + m2)/2.0;

        volume+= (avgArea*dist);
        moment+= (avgMoment*dist);
        
    }
    volumeTill[zVal]=volume;
    lcb_Till[zVal]=moment/volume;
    massTill[zVal]=volume*1.025;
  }
  return;
}



pair<float,float> getVolumeFromTrim(float trimAtAft, float trimAtForward)
{
  float slope = (trimAtForward-trimAtAft)/110.0;
  float AreaSum = 0.0;
  float momentTrimmed = 0.0;
  for(int i=0;i<stations.size()+1;i++)
  {
    float zVal1 = trimAtAft + (slope*stations[i]);
    float zVal2 = trimAtAft + (slope*stations[i+1]);
    zVal1 = roundTillOne(zVal1);
    zVal2 = roundTillOne(zVal2);

    float a1 = secArea[stations[i]][zVal1];
    float a2 = secArea[stations[i+1]][zVal2];

    float m1 = a1*stations[i];
    float m2 = a2*stations[i+1];
    
    float avgArea = (a1+a2)/2.0;
    float avgMoment = (m1+m2)/2.0;

    float dist = stations[i+1]-stations[i];

    AreaSum+=avgArea*dist;
    momentTrimmed += avgMoment*dist;

  }
  momentTrimmed/=AreaSum;
  return {AreaSum, momentTrimmed};
}