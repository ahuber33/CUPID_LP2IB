#ifndef TrackDecayInfo_h
#define TrackDecayInfo_h

#include "G4VUserTrackInformation.hh"

class TrackDecayInfo : public G4VUserTrackInformation {
public:
    TrackDecayInfo(int val = 0) : ancestorID(val) {}
    virtual ~TrackDecayInfo() {}
    int ancestorID;
};

#endif