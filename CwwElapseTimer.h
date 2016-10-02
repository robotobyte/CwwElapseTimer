// *****************************************************************************
//
// Elapse Timer Class
// ------------------
// Code by W. Witt; V1.00-beta-01; July 2016
//
// *****************************************************************************

#ifndef CwwElapseTimer_h
#define CwwElapseTimer_h

// *****************************************************************************

#include <Arduino.h>

// =============================================================================

class CwwElapseTimer {

  public:

    // Public Types:

    // Public Constants:

    // Public Variables:

    // Public Functions:

             CwwElapseTimer ( unsigned long duration = 1000 );
    virtual ~CwwElapseTimer ();

    void          setDuration     ( unsigned long duration );
    unsigned long valueOfDuration (); 

    void          start   ();
    void          stop    ();
    void          restart ();

    unsigned long elapsedTime ();
    boolean       hasElapsed  ();

    unsigned long remainingTime ();  // will stop at zero; will not go negative

  private:

    // Private Constants:

    // Private Variables:

    unsigned long duration;
    unsigned long lastStartTime;
    boolean       isRunning;

    // Private Functions:

};

// *****************************************************************************

#endif

// *****************************************************************************
