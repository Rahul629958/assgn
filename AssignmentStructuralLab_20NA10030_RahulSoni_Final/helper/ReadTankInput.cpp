
map<string,float> TankNameAndFillPercent;
map<string,map<float,vector<pair<float,float>>>> tankInfo;

void ReadLoadingCaseFile()
{
  fstream file;
  file.open("inputFiles/Tanks/loading1.txt", ios::in);
  string line = "";
  string name = "";
  while(getline(file,line))
  {
    
    if(line.size()>0){
        if(line[0]=='$')
        {
            break;
        }
        if(line[0]>='0' && line[0]<='9')
        {
            TankNameAndFillPercent[name] = stof(line);
        }else{
            name=line;
        }
    }
  }


  return;
}

bool isX_Cordinate(string line)
{
    for(auto c:line)
    {
        if(c==',')
        {
            return false;
        }
    }
    return true;
}

pair<float,float> getYZ_tanks(string line)
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
  
  return {round2(firstNum),round2(secondNum)};
}


void ReadTankInfo(string tankFileName)
{
  fstream file;
  file.open("inputFiles/Tanks/"+tankFileName + ".txt", ios::in);
  string line = "";
  float x = 0.0;
  while(getline(file,line))
  {
    if(line.size()>0){
     if(isX_Cordinate(line))
     {
       x=round2(stof(line));
     }else{
        pair<float,float> yz = getYZ_tanks(line);
        tankInfo[tankFileName][x].push_back(yz);
     }
    }
  }


  return;
}



