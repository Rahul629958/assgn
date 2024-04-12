map<float, map<float,float>> secArea;

void getSectionArea(map<float,map<float,float>> offset)
{
    for(auto p: offset)
    {
        float x_values = p.first;
        vector<pointYZ> secPoint;
        for(auto v: p.second)
        {
            pointYZ temp = pointYZ(v.second,v.first);
            secPoint.push_back(temp);
        }

        for(int limit = 0;limit<=90;limit++)
        {
            float zVal = (float)limit/10.0;
            secArea[x_values][zVal]= 2*trapezoidalIntegration(secPoint,zVal);
        }
    }
}