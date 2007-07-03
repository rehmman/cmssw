#include "DQM/EcalPreshowerMonitorModule/interface/ESPedestalCMCTTask.h"

#include <iostream>

using namespace cms;
using namespace edm;
using namespace std;

ESPedestalCMCTTask::ESPedestalCMCTTask(const ParameterSet& ps) {

  label_        = ps.getUntrackedParameter<string>("Label");
  instanceName_ = ps.getUntrackedParameter<string>("InstanceES");
  pedestalFile_ = ps.getUntrackedParameter<string>("PedestalFile");
  sta_          = ps.getUntrackedParameter<bool>("RunStandalone", false);

  init_ = false;

  ped_ = new TFile(pedestalFile_.c_str());  //Root file with ped histos
  Char_t tmp[300];  

  for (int i=0; i<2; ++i){ 
    for (int j=0; j<6; ++j){
      for (int k=0; k<2; ++k){        
	for (int m=0; m<5; ++m){
	  meSensorCM_[i][j][k][m]=0;
	  
	  int zside = (i==0)?1:-1;
	  sprintf(tmp,"DQMData/ES/QT/PedestalCT/ES Pedestal Fit Mean RMS Z %d P %1d Row %02d Col %02d",zside,j+1,k+1,m+1);
	  hist_[i][j][k][m] = (TH1F*) ped_->Get(tmp);

	  for (int n=0; n<32; ++n){
	    mePedestalCM_[i][j][k][m][n] = 0; 
          }
        }
      }
    }
  }

  dbe_ = Service<DaqMonitorBEInterface>().operator->();
}

ESPedestalCMCTTask::~ESPedestalCMCTTask(){

  delete ped_;

}

void ESPedestalCMCTTask::beginJob(const EventSetup& c) {
  
  ievt_ = 0;
  
  if ( dbe_ ) {
    dbe_->setCurrentFolder("ES/ESPedestalCMCTTask");
    dbe_->rmdir("ES/ESPedestalCMCTTask");
  }

}

void ESPedestalCMCTTask::setup(void){
  
  init_ = true;
  
  Char_t hist[200];
  
  if ( dbe_ ) {   
    dbe_->setCurrentFolder("ES/ESPedestalCMCTTask");
    for (int i=0; i<2; ++i) {       
      for (int j=0; j<6; ++j) {
	for (int k=0; k<2; ++k) {
	  for (int m=0; m<5; ++m) {
            int zside = (i==0)?1:-1;
	    sprintf(hist, "ES Sensor CM Z %d P %d Row %02d Col %02d", zside, j+1, k+1, m+1);
            meSensorCM_[i][j][k][m] = dbe_->book1D(hist, hist, 200, -100, 100);;
	    for (int n=0; n<32; ++n) {
	      sprintf(hist, "ES Pedestal Z %d P %d Row %02d Col %02d Str %02d", zside, j+1, k+1, m+1, n+1);      
	      mePedestalCM_[i][j][k][m][n] = dbe_->book1D(hist, hist, 5000, -200, 4800);
	    }
	  }
	}
      }
    }
  }

}

void ESPedestalCMCTTask::cleanup(void){

  if (sta_) return;

  if ( dbe_ ) {
    dbe_->setCurrentFolder("ES/ESPedestalCMCTTask");
    for (int i=0; i<2; ++i) {
      for (int j=0; j<6; ++j) {
	for (int k=0; k<2; ++k) {
	  for (int m=0; m<5; ++m) {
            if ( meSensorCM_[i][j][k][m] ) dbe_->removeElement( meSensorCM_[i][j][k][m]->getName() );
            meSensorCM_[i][j][k][m] = 0;
	    for (int n=0; n<32; ++n) {
	      if ( mePedestalCM_[i][j][k][m][n] ) dbe_->removeElement( mePedestalCM_[i][j][k][m][n]->getName() );
	      mePedestalCM_[i][j][k][m][n] = 0;
	    }
	  }
	}
      }
    } 

  }

  init_ = false;

}

void ESPedestalCMCTTask::endJob(void) {

  LogInfo("ESPedestalCMCTTask") << "analyzed " << ievt_ << " events";

  if ( init_ ) this->cleanup();

}


void ESPedestalCMCTTask::DoCommonMode(float det_data[], float *cm1, float *cm2)
{

   int current_min1 = 4095;
   int current_strip_val1 = 0;
   int current_sum1 = 0;
   int threshold1=0;
   int n1=0;
   int check_bit1_10;
   int corrected_sum1;

   int current_min2 = 4095;
   int current_strip_val2 = 0;
   int current_sum2 = 0;
   int threshold2=0;
   int n2=0;
   int check_bit2_10;
   int corrected_sum2;


   int treshold_const = 24;  //+-3sigma?
   int myltip_factor[]={2048, 1024, 683, 512, 410, 341, 293, 256, 228, 205,
                        186, 171, 158, 146, 137, 128};


   // Common mode for strips 0-15
   
   for(int i=0; i<16; ++i){                    //Evaluate min value strip 0-15
     current_strip_val1 = (int) det_data[i];
     if(current_min1 > current_strip_val1) {
       current_min1 = current_strip_val1;
     }
   } 
   threshold1 = current_min1 + treshold_const;

   for(int i=0; i<16; ++i){                    //Sum all noisy strips 0-15
     current_strip_val1 = (int) det_data[i];
     if(current_strip_val1 <= threshold1) {
       n1++;
       current_sum1 += current_strip_val1;
     }
   } 
   corrected_sum1 = current_sum1*myltip_factor[n1-1];   // multiply sum by factor
   corrected_sum1 = corrected_sum1 >> 10;               //shilft right 10 bits [9:0]
   check_bit1_10 = corrected_sum1 & 1;                  //check bit [10]
   corrected_sum1 = corrected_sum1 >> 1;                //shilft right 1 more bit [10]
   if(check_bit1_10 == 1) corrected_sum1++;             //increase by 1 if bit [10] was one

   *cm1=(float)corrected_sum1;

   // Common mode for strips 16-31
   
   for(int i=16; i<32; ++i){                    //Evaluate min value strip 16-31
     current_strip_val2 = (int) det_data[i];
     if(current_min2 > current_strip_val2) {
       current_min2 = current_strip_val2;
     }
   } 
   threshold2 = current_min2 + treshold_const;

   for(int i=16; i<32; ++i){                    //Sum all noisy strips 16-31
     current_strip_val2 = (int) det_data[i];
     if(current_strip_val2 <= threshold2) {
       n2++;
       current_sum2 += current_strip_val2;
     }
   } 
   corrected_sum2 = current_sum2*myltip_factor[n2-1];   // multiply sum by factor
   corrected_sum2 = corrected_sum2 >> 10;               //shilft right 10 bits [9:0]
   check_bit2_10 = corrected_sum2 & 1;                  //check bit [10]
   corrected_sum2 = corrected_sum2 >> 1;                //shilft right 1 more bit [10]
   if(check_bit2_10 == 1) corrected_sum2++;             //increase by 1 if bit [10] was one

   *cm2=(float)corrected_sum2;

}

void ESPedestalCMCTTask::analyze(const Event& e, const EventSetup& c){

  if ( ! init_ ) this->setup();
  ievt_++;
  
  Handle<ESDigiCollection> digis;
  try {
    e.getByLabel(label_, instanceName_, digis);
  } catch ( cms::Exception &e ) {
    LogDebug("") << "ESPedestal : Error! can't get collection !" << std::endl;
  } 

  //Need for storing original data 
  int data[2][6][2][5][32];
  for (int i=0; i<2; ++i) 
    for (int j=0; j<6; ++j)
      for (int k=0; k<2; ++k)        
	for (int m=0; m<5; ++m)
	  for (int n=0; n<32; ++n)
	    data[i][j][k][m][n] = 0;

  //Need for storing data after CM correction 
  int dataCM[2][6][2][5][32];
  for (int i=0; i<2; ++i) 
    for (int j=0; j<6; ++j)
      for (int k=0; k<2; ++k)        
	for (int m=0; m<5; ++m)
	  for (int n=0; n<32; ++n)
	    dataCM[i][j][k][m][n] = 0;


  for (ESDigiCollection::const_iterator digiItr = digis->begin(); digiItr != digis->end(); ++digiItr ) {

    ESDataFrame dataframe = (*digiItr);
    ESDetId id = dataframe.id();

    //int zside = id.zside();
    //int plane = id.plane();
    int ix    = id.six();
    int iy    = id.siy();
    int strip = id.strip();
    int mean_strip_pedestal = 0;

    
    int j = (ix-1)/2; 
    int i;
    if (j<=5) i = 0;
    else i = 1;
    if (j>5) j=j-6;    
    int k = (ix-1)%2;


    for (int i=0; i<dataframe.size(); ++i) {
      //printf("zside=%d plane=%d ix=%d iy=%d strip=%d dataframe=%d\n",zside,plane,ix,iy,strip,dataframe.sample(i).adc());    
      mean_strip_pedestal+=dataframe.sample(i).adc();
    }
     mean_strip_pedestal=mean_strip_pedestal/3;
     //printf("i=%d j=%d k=%d iy-1=%d strip-1=%d\n",i,j,k,iy-1,strip-1);
     //printf("mean_strip_pedestal=%d \n",mean_strip_pedestal);
     data[i][j][k][iy-1][strip-1]=mean_strip_pedestal;    //storing data per event
  }

  //TDirectory *d = (TDirectory*)ped_->Get("DQMData/ES/QT/PedestalCT");
  //TH1F *hist;

  float sensor_data[32];
  float com_mode1;
  float com_mode2;
  //char tmp[100];
  
  for (int i=0; i<2; ++i){ 
    for (int j=0; j<6; ++j){
      for (int k=0; k<2; ++k){        
	for (int m=0; m<5; ++m){
	  for (int n=0; n<32; ++n){
	    sensor_data[n]=data[i][j][k][m][n];  //Read sensor data
	  }
	  
	  //printf("******************************************\n"); 
	  //for(int kk=0; kk<32; ++kk){printf("%6.0f",sensor_data[kk]);}
	  //printf("\n");
	  
	  //Read pedestals from Ming Here and correct sensor_data
	  //if(i==1){
	  //sprintf(tmp,"ES Pedestal Fit Mean RMS Z -1 P %1d Row %02d Col %02d;1",j+1,k+1,m+1);
	  //}
	  //if(i==0){
	  //sprintf(tmp,"ES Pedestal Fit Mean RMS Z 1 P %1d Row %02d Col %02d;1",j+1,k+1,m+1);
	  //}
	  
	  //printf(tmp);
	  //printf("\n");
	  //hist =(TH1F*)d->Get(tmp);  //Get histo
	  if (hist_[i][j][k][m]->GetEntries() == 0) continue;
	  
	  for(int kk=0; kk<32; ++kk){
	    float pedestal=hist_[i][j][k][m]->GetBinContent(kk+1);
	    //printf("GaussMean=%f\n",pedestal);
	    
	    sensor_data[kk]=sensor_data[kk]-pedestal;   //Pedestal subtraction
	  }
	  
	  
	  //for(int kk=0; kk<32; ++kk){printf("%6.0f",sensor_data[kk]);}
	  //printf("\n");
	  
	  
	  // correct for common mode
	  DoCommonMode(sensor_data, &com_mode1,&com_mode2);  //Common mode calculation
	  //printf("cm1=%f cm2=%f\n",com_mode1,com_mode2);
	  meSensorCM_[i][j][k][m]->Fill(com_mode1);  //Fill CM histos per sensor
	  meSensorCM_[i][j][k][m]->Fill(com_mode2);
	  for(int kk=0; kk<16; ++kk){
	    sensor_data[kk]    -= com_mode1;  //Common mode correction 0:15
	    sensor_data[kk+16] -= com_mode2;  //Common mode correction 16:31
	  }
	  
	  for(int kk=0; kk<32; ++kk){
	    dataCM[i][j][k][m][kk]=(int)sensor_data[kk];  //Storing corrected data
	  }
	  
	}
      }
    }
  }
  
  
  for (int i=0; i<2; ++i){ 
    for (int j=0; j<6; ++j){
      for (int k=0; k<2; ++k){        
	for (int m=0; m<5; ++m){
	  for (int n=0; n<32; ++n){
	    mePedestalCM_[i][j][k][m][n]->Fill(dataCM[i][j][k][m][n]);  //Filling histos with corrected data
	  }
	}
      }
    }
  }
  
}
