/** \class CSCCathodeLCTAnalyzer
 *
 * Class for Monte Carlo studies of cathode LCTs.  Returns a vector of up
 * to six (one per layer) CSCCathodeLayerInfo objects for a given CLCT.
 * They contain the list of comparator digis used to build a given CLCT, and
 * the list of associated (closest) SimHits.
 *
 * \author Slava Valuev  26 May 2004.
 * Porting from ORCA by S. Valuev in September 2006.
 *
 * $Date: 2006/09/12 09:00:29 $
 * $Revision: 1.1 $
 *
 */

#ifndef CSCTriggerPrimitives_CSCCathodeLCTAnalyzer_H
#define CSCTriggerPrimitives_CSCCathodeLCTAnalyzer_H

#include <DataFormats/CSCDigi/interface/CSCComparatorDigiCollection.h>
#include <DataFormats/CSCDigi/interface/CSCCLCTDigiCollection.h>
#include <SimDataFormats/TrackingHit/interface/PSimHitContainer.h>
#include <L1Trigger/CSCTriggerPrimitives/test/CSCLayerInfo.h>

typedef CSCLayerInfo<CSCComparatorDigi> CSCCathodeLayerInfo;

class CSCCathodeLCTAnalyzer
{
 public:
  /** Default constructor. */
  CSCCathodeLCTAnalyzer() {};

  /** Constructs vector of CSCCathodeLayerInfo objects for CLCT. */
  std::vector<CSCCathodeLayerInfo> getSimInfo(const CSCCLCTDigi& clct,
       const CSCDetId& clctId, const CSCComparatorDigiCollection* compdc,
       const edm::PSimHitContainer* allSimHits);

  /** Finds half-strip, phi and eta of the nearest SimHit for comparison
      to the reconstructed values. */
  int nearestHS(const std::vector<CSCCathodeLayerInfo>& allLayerInfo,
		double& closestPhi, double& closestEta);

  /** Cache pointer to geometry for current event. */
  void setGeometry(const CSCGeometry* geom);

  /** Returns phi position of a given strip. */
  double getStripPhi(const CSCDetId& layerId, const float strip);

  /** Turns on the debug flag for this class. */
  static void setDebug() {debug = true;}

  /** Turns off the debug flag for this class (default). */
  static void setNoDebug() {debug = false;}

 private:
  static bool debug;

  /* Cache geometry for current event. */
  const CSCGeometry* geom_;

  /* Find the list of ComparatorDigis belonging to this CLCT. */
  std::vector<CSCCathodeLayerInfo> lctDigis(const CSCCLCTDigi& clct,
       const CSCDetId& clctId, const CSCComparatorDigiCollection* compdc);

  /* Find SimHits closest to each ComparatorDigi on CLCT. */
  void digiSimHitAssociator(CSCCathodeLayerInfo& info,
			    const edm::PSimHitContainer* allSimHits);
};
#endif
