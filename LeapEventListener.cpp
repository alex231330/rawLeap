#include <iostream>
#include "include/Leap.h"

using namespace Leap;

class LeapEventListener : public Listener {
  public:
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onFrame(const Controller&);
};
