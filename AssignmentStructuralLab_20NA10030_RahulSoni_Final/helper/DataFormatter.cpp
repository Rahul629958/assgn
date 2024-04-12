


bool compareFunction(pointYZ p1, pointYZ p2)
{
    return p1.z<p2.z;
}


void getOffsetUtil(map<float,map<float,float>> &res, map<float, vector<pointYZ>> &data)
{
  for(auto p: data)
  {
    float x_value = p.first;
    vector<pointYZ> v = p.second;
    for(auto point: v)
    {
      res[x_value][point.z]=point.y;
    }
  }
  return;
}




map<float,map<float,float>> makeOffset(map<float,vector<pointYZ>> &data)//x->{z->y}
{
    map<float, map<float, float>> res;
    for(auto p: data)
    {
        float x_value = p.first;
       vector<pointYZ> temp = p.second;
      //  vector<float> ans(124,0.0);
      map<float,float> ans;
       std::sort(temp.begin(),temp.end(),compareFunction);

       for(int z10=0;z10<124;z10++)
       {
          float zVal = (float)z10/10.0;
          for(int i=0;i<temp.size()-1;i++)
          {
            float z1 = temp[i].z;
            float z2 = temp[i+1].z;
            if(z1<=zVal && z2>=zVal)
            {
              float new_y = interpolate(z1,temp[i].y, z2, temp[i+1].y, zVal);
              new_y = round2(new_y);
              ans[zVal]=new_y;
              break;
            }

          }
       }

       res[x_value]=ans;
       getOffsetUtil(res,data);
    }
    return res;
}









