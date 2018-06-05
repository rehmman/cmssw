import FWCore.ParameterSet.Config as cms

#HGCAL reconstruction
from RecoLocalCalo.HGCalRecProducers.HGCalUncalibRecHit_cfi import *
from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import *
from RecoLocalCalo.HGCalRecProducers.hgcalLayerClusters_cfi import *
from RecoLocalCalo.HGCalRecProducers.hgcalMultiClusters_cfi import *


HGCalLocalRecoSequence = cms.Sequence(HGCalUncalibRecHit*HGCalRecHit*hgcalLayerClusters*hgcalMultiClusters)
