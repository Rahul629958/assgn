

pair<float,float> getEquilibriumCondition(float weight, float lcg)
{
   float mean_draft = interpolate(massTill[2.2],2.2, massTill[2.3],2.3, weight);
   float lcb = interpolate(2.2,lcb_Till[2.2],2.3, lcb_Till[2.3],mean_draft);
   float volume = interpolate(2.2,volumeTill[2.2],2.3, volumeTill[2.3],mean_draft);
   float displacement = 1.025*volume;
   float current_draft = mean_draft;
   bool isDone = false;

   float aftTrim = mean_draft;
   float forwardTrim = mean_draft;
   float max_draft = 12.3;
   

   float epsilon1 = 0.01;
   float epsilon2 = 0.0055;

   if(abs((lcg-lcb)/lcg)<epsilon1)
   {
    return {mean_draft,mean_draft};
   }

   while(!isDone )
   {
    if(abs(lcg-lcb)/lcg<epsilon1)
    {
      if(abs(weight-displacement)/weight<=epsilon2)
      {
        return {aftTrim,forwardTrim};
        isDone = true;
      }else{
         float smallDraftChange = 0.0125;
         if(weight<displacement)
         {
           smallDraftChange*=(-1.0);
         }

         aftTrim+=smallDraftChange;
         forwardTrim+=smallDraftChange;
        pair<float,float> vl = getVolumeFromTrim(aftTrim,forwardTrim);
        volume = vl.first;
        displacement = 1.025*volume;
        lcb = vl.second;

      }
    }else
    {
        float smallTrim = 0.1;
        aftTrim+= smallTrim;
        forwardTrim-=smallTrim;
        pair<float,float> vl = getVolumeFromTrim(aftTrim,forwardTrim);
        volume = vl.first;
        displacement = 1.025*volume;
        lcb = vl.second;
    }
   }
   
 


}