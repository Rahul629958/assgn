map<float,float> WPA;
map<float,float> LCF;


void getWPA(map<float,map<float,float>> offset)
{
  for(int i=0;i<=90;i++)
  {
    float zVal = (float)i/10.0;
    float AreaSum = 0.0;
    float moment = 0.0;
    for(int s=0;s<stations.size()-1;s++)
    {
        float y1 = offset[stations[s]][zVal];
        float y2 = offset[stations[s+1]][zVal];
        
        float m1 = y1*stations[s];
        float m2 = y2*stations[s+1];

        float avgY = (y1 + y2)/2.0;
        float avgM = (m1 + m2)/2.0;

        float dist = stations[s+1]-stations[s];

        AreaSum += 2*avgY*dist;
        moment += 2*avgM*dist;
    }
    WPA[zVal]=AreaSum;
    LCF[zVal]=moment/AreaSum;
  }
}