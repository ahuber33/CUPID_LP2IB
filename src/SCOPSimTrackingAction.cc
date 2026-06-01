#include "SCOPSimTrackingAction.hh"

#include "G4Track.hh"
#include "G4TrackingManager.hh"

#include "TrackDecayInfo.hh"

SCOPSimTrackingAction::SCOPSimTrackingAction() {}

SCOPSimTrackingAction::~SCOPSimTrackingAction() {}

void SCOPSimTrackingAction::PreUserTrackingAction(const G4Track* track)
{
    // add ancestorID=1 to the primary particle
    if (track->GetParentID() == 0 && !track->GetUserInformation())
    {
        auto info = new TrackDecayInfo(track->GetTrackID());
        const_cast<G4Track*>(track)->SetUserInformation(info);
    }
}

void SCOPSimTrackingAction::PostUserTrackingAction(const G4Track* track)
{
    auto secondaries = fpTrackingManager->GimmeSecondaries();

    if (!secondaries) return;

    auto parentInfo = static_cast<TrackDecayInfo*>(track->GetUserInformation());

    if (!parentInfo) return;

    for (auto sec : *secondaries) {
        sec->SetUserInformation(new TrackDecayInfo(*parentInfo));
    }
}