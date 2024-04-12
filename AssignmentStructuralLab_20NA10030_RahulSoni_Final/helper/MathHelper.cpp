float pi = 3.14159265359;

float interpolate(float x1, float f1, float x2, float f2, float x3)
    {
       float ans = ((f2-f1)/(x2-x1))*(x3-x1) + f1;
       return ans;
    }

float trapezoidalIntegration(vector<pointYZ> dataVal, float limitValue)
{
   float sum=0.0;
   if(dataVal.size()>0 && dataVal[0].z>=limitValue)
   {
      return 0.0;
   }
   for(int i=0;i<dataVal.size()-1;i++)
   {
      if(dataVal[i+1].z>limitValue)
      {
         break;
      }
      float f1 = dataVal[i].y;
      float f2 = dataVal[i+1].y;

      float diff = dataVal[i+1].z - dataVal[i].z;
      sum+= (diff*((f1+f2)/2.0));
   }
   return sum;
}



float round2(float var)
{
    float value = (int)(var * 100 + (var<0.0?(-0.5):(0.5)));
    return (float)value / 100;
}


float roundTillOne(float v)
{
   float value = (int)(v * 10 + (v<0.0?(-0.5):(0.5)));
   return (float)value / 10;
}


float polygonArea(vector<float> Z, vector<float> Y)
{
    // Initialize area
    float area = 0.0;
    int n = Z.size();
 
    // Calculate value of shoelace formula
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (Y[j] + Y[i]) * (Z[j] - Z[i]);
        j = i;  // j is previous vertex to i
    }
 
    // Return absolute value
    return round2(abs(area / 2.0));
}