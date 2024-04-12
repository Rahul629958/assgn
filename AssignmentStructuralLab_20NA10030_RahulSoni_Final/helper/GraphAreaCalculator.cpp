


void getAreaCurve(map<float,float> data, map<float,float> &result)
{
    float areaSum = 0.0;
    result[stations[0]]=0.0;
  for(int i=0;i<stations.size()-1;i++)
  {
    float st1 = stations[i];
    float st2 = stations[i+1];

    float y1 = data[st1];
    float y2 = data[st2];

    float avgY = (y1 + y2)/2.0;
    float dist = (st2-st1);
    
    areaSum+= (avgY*dist);
    result[st2]=areaSum;
  }
  return;
}