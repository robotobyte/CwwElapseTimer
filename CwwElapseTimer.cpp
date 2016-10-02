// ****************************************************************************
//
// Elapse Timer Class
// -------------------
// Code by W. Witt; V1.00-beta-01; July 2016
//
// ****************************************************************************

#include <limits.h>
#include <Arduino.h>

#include <CwwElapseTimer.h>

// ============================================================================
// Constructors, Destructor
// ============================================================================

CwwElapseTimer::CwwElapseTimer (
  unsigned long duration
) {

  this->duration = duration;

  lastStartTime = 0;
  isRunning     = false;

}

// ----------------------------------------------------------------------------

CwwElapseTimer::~CwwElapseTimer () {

}

// ============================================================================
// Public Functions
// ============================================================================

void CwwElapseTimer::setDuration ( unsigned long duration ) {

  this->duration = duration;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned long CwwElapseTimer::valueOfDuration () {

  return duration;

}

// ----------------------------------------------------------------------------

void CwwElapseTimer::start () {

  unsigned long currentTime;

  currentTime = millis ();

  if ( currentTime < lastStartTime ) {
    lastStartTime = ULONG_MAX - ( lastStartTime - currentTime );
  }
  else {
    lastStartTime = currentTime - lastStartTime;
  }

  isRunning = true;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void CwwElapseTimer::stop () {

  lastStartTime = elapsedTime ();
  isRunning = false;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void CwwElapseTimer::restart () {

  lastStartTime = millis ();
  isRunning = true;

}

// ----------------------------------------------------------------------------

unsigned long CwwElapseTimer::elapsedTime () {

  unsigned long currentTime;
  unsigned long elapsedTime;

  if ( isRunning ) {

    currentTime = millis ();

    if ( currentTime < lastStartTime ) {
      elapsedTime = ( ULONG_MAX - lastStartTime ) + currentTime;
    }
    else {
      elapsedTime = currentTime - lastStartTime;
    }

    return elapsedTime;

  }
  else {

    return lastStartTime;
  }

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

boolean CwwElapseTimer::hasElapsed () {

  return elapsedTime() >= duration;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned long CwwElapseTimer::remainingTime () {

  unsigned long passedTime;

  passedTime = elapsedTime ();

  if ( passedTime >= duration ) return 0;
  else                          return duration - passedTime;

}

// ============================================================================
// Private Functions
// ============================================================================

// ****************************************************************************
