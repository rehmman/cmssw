import FWCore.ParameterSet.Config as cms

trackingMaterialAnalyser = cms.EDAnalyzer("TrackingMaterialAnalyser",
    MaterialAccounting      = cms.InputTag("trackingMaterialProducer"),
    SplitMode               = cms.string("NearestLayer"),
    SkipBeforeFirstDetector = cms.bool(False),
    SkipAfterLastDetector   = cms.bool(True),
    SaveSummaryPlot         = cms.bool(True),
    SaveDetailedPlots       = cms.bool(False),
    SaveParameters          = cms.bool(True),
    SaveXML                 = cms.bool(True),
    Groups = cms.vstring(
        'TrackerRecMaterialPixelBarrelLayer0_Z0',
        'TrackerRecMaterialPixelBarrelLayer0_Z20',
        'TrackerRecMaterialPixelBarrelLayer1_Z0',
        'TrackerRecMaterialPixelBarrelLayer1_Z20',
        'TrackerRecMaterialPixelBarrelLayer2_Z0',
        'TrackerRecMaterialPixelBarrelLayer2_Z15',
        'TrackerRecMaterialTIBLayer0_Z0',
        'TrackerRecMaterialTIBLayer0_Z20',
        'TrackerRecMaterialTIBLayer0_Z40',
        'TrackerRecMaterialTIBLayer1_Z0',
        'TrackerRecMaterialTIBLayer1_Z30',
        'TrackerRecMaterialTIBLayer1_Z60',
        'TrackerRecMaterialTIBLayer2_Z0',
        'TrackerRecMaterialTIBLayer2_Z40',
        'TrackerRecMaterialTIBLayer3_Z0',
        'TrackerRecMaterialTIBLayer3_Z50',
        'TrackerRecMaterialTOBLayer0_Z0',
        'TrackerRecMaterialTOBLayer0_Z20',
        'TrackerRecMaterialTOBLayer0_Z70',
        'TrackerRecMaterialTOBLayer0_Z80',
        'TrackerRecMaterialTOBLayer1_Z0',
        'TrackerRecMaterialTOBLayer1_Z20',
        'TrackerRecMaterialTOBLayer1_Z80',
        'TrackerRecMaterialTOBLayer1_Z90',
        'TrackerRecMaterialTOBLayer2_Z0',
        'TrackerRecMaterialTOBLayer2_Z25',
        'TrackerRecMaterialTOBLayer2_Z80',
        'TrackerRecMaterialTOBLayer2_Z90',
        'TrackerRecMaterialTOBLayer3_Z0',
        'TrackerRecMaterialTOBLayer3_Z25',
        'TrackerRecMaterialTOBLayer3_Z80',
        'TrackerRecMaterialTOBLayer3_Z90',
        'TrackerRecMaterialTOBLayer4_Z0',
        'TrackerRecMaterialTOBLayer4_Z25',
        'TrackerRecMaterialTOBLayer4_Z80',
        'TrackerRecMaterialTOBLayer4_Z90',
        'TrackerRecMaterialTOBLayer5_Z0',
        'TrackerRecMaterialTOBLayer5_Z25',
        'TrackerRecMaterialTOBLayer5_Z80',
        'TrackerRecMaterialTOBLayer5_Z90',
        'TrackerRecMaterialPixelEndcapDisk1_R0',
        'TrackerRecMaterialPixelEndcapDisk1_R7',
        'TrackerRecMaterialPixelEndcapDisk1_R11',
        'TrackerRecMaterialPixelEndcapDisk2_R0',
        'TrackerRecMaterialPixelEndcapDisk2_R7',
        'TrackerRecMaterialTIDDisk1_R0',
        'TrackerRecMaterialTIDDisk1_R30',
        'TrackerRecMaterialTIDDisk1_R40',
        'TrackerRecMaterialTIDDisk2_R25',
        'TrackerRecMaterialTIDDisk2_R30',
        'TrackerRecMaterialTIDDisk2_R40',
        'TrackerRecMaterialTIDDisk3_R24',
        'TrackerRecMaterialTIDDisk3_R30',
        'TrackerRecMaterialTIDDisk3_R40',
        'TrackerRecMaterialTECDisk0_R20',
        'TrackerRecMaterialTECDisk0_R40',
        'TrackerRecMaterialTECDisk0_R50',
        'TrackerRecMaterialTECDisk0_R60',
        'TrackerRecMaterialTECDisk0_R90',
        'TrackerRecMaterialTECDisk1_R20',
        'TrackerRecMaterialTECDisk1_Inner',
        'TrackerRecMaterialTECDisk1_Outer',
        'TrackerRecMaterialTECDisk2_Inner',
        'TrackerRecMaterialTECDisk2_Outer',
        'TrackerRecMaterialTECDisk2_R20',
        'TrackerRecMaterialTECDisk3_Inner',
        'TrackerRecMaterialTECDisk3_Outer',
        'TrackerRecMaterialTECDisk3',
        'TrackerRecMaterialTECDisk4_Inner',
        'TrackerRecMaterialTECDisk4_Outer',
        'TrackerRecMaterialTECDisk4_R33',
        'TrackerRecMaterialTECDisk5_Inner',
        'TrackerRecMaterialTECDisk5_Outer',
        'TrackerRecMaterialTECDisk5_R33',
        'TrackerRecMaterialTECDisk6',
        'TrackerRecMaterialTECDisk7_R40',
        'TrackerRecMaterialTECDisk8'
    )
)
