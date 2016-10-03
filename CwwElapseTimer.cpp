// ****************************************************************************
//
// Elapse Timer Class
// -------------------
// Code by W. Witt; V1.00-beta-03; August 2016
//
// ****************************************************************************

#include <limits.h>
#include <Arduino.h>

#include <CwwElapseTimer.h>

// ============================================================================
// Private Macros:
// ============================================================================

#define CWW_ELAPSE_TIMER_IS_IDLE    0x00
#define CWW_ELAPSE_TIMER_IS_RUNNING 0x01
#define CWW_ELAPSE_TIMER_IS_PAUSED  0x02

// ============================================================================
// Constructors, Destructor
// ============================================================================

CwwElapseTimer::CwwElapseTimer (
  unsigned long duration
) {

  this->duration = duration;

  lastStartTime = 0;
  status        = CWW_ELAPSE_TIMER_IS_IDLE;

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

void CwwElapseTimer::start ( unsigned long duration ) {

  setDuration ( duration );
  start ();

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void CwwElapseTimer::start () {

  lastStartTime = millis ();
  
  status = CWW_ELAPSE_TIMER_IS_RUNNING;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

boolean CwwElapseTimer::stop () {

  lastStartTime = elapsedTime ();
  
  if ( hasElapsed() ) {
    status = CWW_ELAPSE_TIMER_IS_IDLE;
    return false;
  }
  else {
    status = CWW_ELAPSE_TIMER_IS_PAUSED;
    return true;
  }

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

boolean CwwElapseTimer::resume () {

  unsigned long currentTime;

  currentTime = millis ();

  if ( currentTime < lastStartTime ) {
    lastStartTime = ULONG_MAX - ( lastStartTime - currentTime );
  }
  else {
    lastStartTime = currentTime - lastStartTime;
  }

  if ( hasElapsed() ) {
    status = CWW_ELAPSE_TIMER_IS_IDLE;
    return false;
  }
  else {
    status = CWW_ELAPSE_TIMER_IS_RUNNING;
    return true;
  }

}

// ----------------------------------------------------------------------------

boolean CwwElapseTimer::isRunning () {

  return status & CWW_ELAPSE_TIMER_IS_RUNNING;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

boolean CwwElapseTimer::isPaused () {

  return status & CWW_ELAPSE_TIMER_IS_PAUSED;

}

// ----------------------------------------------------------------------------

unsigned long CwwElapseTimer::elapsedTime () {

  unsigned long currentTime;
  unsigned long elapsedTime;

  if ( isRunning() ) {

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
