#ifndef SCOPSimTrackingAction_h
#define SCOPSimTrackingAction_h

#include "G4UserTrackingAction.hh"

class SCOPSimTrackingAction : public G4UserTrackingAction {
public:
    SCOPSimTrackingAction();
    virtual ~SCOPSimTrackingAction();

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);
};

#endif