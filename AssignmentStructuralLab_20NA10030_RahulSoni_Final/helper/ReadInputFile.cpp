

vector<float> stations;
map<float,bool> checkStation;

bool isStationNumber(string line)
{
    for(auto c: line)
    {
        if(c=='e')
        {
            return true;
        }
    }
    return false;
}


pair<float,float> getElementValue(string line, bool checkSecond)
{
  string first="";
  string second = "";
  float firstNum=0.0;
  float secondNum = 0.0;
  int n = line.size();
  int i=0;
  for(;i<n;i++)
  {
    if(line[i]==',')
    {
        break;
    }else{
        first+=line[i];
    }
  }
  i++;
  firstNum = stof(first);
  if(checkSecond)
  {
    for(;i<n;i++)
    {
        if(line[i]==',')
        {
            break;
        }else{
            second+=line[i];
        }
    }
    secondNum=stof(second);
  }
  return {firstNum,secondNum};
}



void ReadFile(map<float,vector<pointYZ>> &points)
{
  fstream file;
  file.open("inputFiles/SecLine.dat", ios::in);
  string line="";
  float stationNumber = 0.0;
  while(getline(file,line))
  {
    if(line.size()>2 && isStationNumber(line))
    {
        stationNumber = getElementValue(line,false).first;
        if(checkStation[round2(stationNumber)]==false){
        stations.push_back(round2(stationNumber));
        checkStation[round2(stationNumber)]=true;}
    }else if(line.size()>2)
    {
        pair<float,float> yz = getElementValue(line, true);
        pointYZ p = pointYZ(round2(yz.first), round2(yz.second));
        points[round2(stationNumber)].push_back(p);
    }
  }
  file.close();

}



void ReadWeightFile(map<float,float> &weightData)
{
  fstream file;
  vector<float> temp;
  file.open("inputFiles/WeightData.txt", ios::in);
  string line = "";
  while(getline(file,line))
  {
    if(line.size()>0){
    temp.push_back(stof(line));
    }
  }

  for(int i=0;i<stations.size();i++)
  {
    weightData[stations[i]]=temp[i];
  }
  return;
}






