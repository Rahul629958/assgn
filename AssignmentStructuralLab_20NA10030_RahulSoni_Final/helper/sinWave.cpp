map<float,float> sinWaveData;


void getSinWave(int halflength, int height)
{
 for(auto s: stations)
 {
    sinWaveData[s]=height*(sin(pi*(s/halflength)));
 }
}