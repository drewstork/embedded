/*******************************************************************
 *
 * C code framework for ESOS user-interface (UI) service
 *
 *    requires the EMBEDDED SYSTEMS target rev. F14
 *
 * ****************************************************************/
# include esos_f14ui.h;

// PRIVATE FUNCTIONS
inline void _esos_uiF14_setRPGCounter (uint16_t newValue) {
    _st_esos_uiF14Data.u16_RPGCounter = newValue;
    return;
}

inline void _esos_uiF14_setLastRPGCounter (uint16_t newValue) {
    _st_esos_uiF14Data.u16_lastRPGCounter = newValue;
    return;
}

// ------------------------
// PUBLIC SWITCH FUNCTIONS
// ------------------------

// Switch 1
inline BOOL esos_uiF14_getSW1Pressed (void) {
    return (_st_esos_uiF14Data.b_SW1Pressed==TRUE);
}

inline BOOL esos_uiF14_getSW1Released (void) {
    return (_st_esos_uiF14Data.b_SW1Pressed==FALSE);
}

inline BOOL esos_uiF14_getSW1DoublePressed (void) {
    return (_st_esos_uiF14Data.b_SW1DoublePressed==TRUE);
}

// Switch 2
inline BOOL esos_uiF14_getSW2Pressed (void) {
    return (_st_esos_uiF14Data.b_SW2Pressed==TRUE);
}

inline BOOL esos_uiF14_getSW2Released (void) {
    return (_st_esos_uiF14Data.b_SW2Pressed==FALSE);
}

inline BOOL esos_uiF14_getSW2DoublePressed (void) {
    return (_st_esos_uiF14Data.b_SW2DoublePressed==TRUE);
}

// Switch 3
inline BOOL esos_uiF14_getSW3Pressed (void) {
    return (_st_esos_uiF14Data.b_SW3Pressed==TRUE);
}

inline BOOL esos_uiF14_getSW3Released (void) {
    return (_st_esos_uiF14Data.b_SW3Pressed==FALSE);
}

inline BOOL esos_uiF14_getSW3DoublePressed (void) {
    return (_st_esos_uiF14Data.b_SW3DoublePressed==TRUE);
}


// --------------------
// PUBLIC LED FUNCTIONS
// --------------------

inline BOOL esos_uiF14_isLED1On (void) {
    return (_st_esos_uiF14Data.b_LED1On==TRUE);
}

inline BOOL esos_uiF14_isLED1Off (void) {
    return (_st_esos_uiF14Data.b_LED1On==FALSE);
}

inline void esos_uiF14_turnLED1On (void) {
    _st_esos_uiF14Data.b_LED1On = TRUE;
    return;
}

inline void esos_uiF14_turnLED1Off (void) {
    _st_esos_uiF14Data.b_LED1On = FALSE;
    return;
}

inline void esos_uiF14_toggleLED1 (void) {
    _st_esos_uiF14Data.b_LED1On ^= 1;
    return;
}

inline void esos_uiF14_flashLED1( uint16_t u16_period) {
    _st_esos_uiF14Data.u16_LED1FlashPeriod = u16_period;
    return
}

/****** LED2 and LED3 will need similar.  ********/
/****** RED, GREEN, and YELLOW functions need to be created *******/

// PUBLIC RPG FUNCTIONS

//gets data from the encoder
inline uint16_t esos_uiF14_getRpgValue_u16 ( void ) {
    return _st_esos_uiF14Data.u16_RPGCounter;
}

//determines whether or not the encoder is turning
inline BOOL esos_uiF14_isRpgTurning ( void ) {
  //if it's turning, velocity is not 0
    return (esos_uiF14_getRpgVelocity_i16() != 0);
}

//is the new-old delta between 1 and 10?
inline BOOL esos_uiF14_isRpgTurningSlow( void ) {
  static char sz_reportSlow[64];
  sz_reportSlow = "Turning slow";
  //TODO: use getRpgVelocity for this (ditto on medium and fast)
  //code for determining slow goes here
  // this is the code for console output --carol
  ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
  ESOS_TASK_WAIT_ON_SEND_STRING(sz_reportSlow);
  ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
}

//is the new-old delta between 11 and 24?
inline BOOL esos_uiF14_isRpgTurningMedium( void ) {
  static char sz_reportMed[64];
  sz_reportMed = "Turning medium";
  // code for determining medium goes here
  //code for console output
  ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
  ESOS_TASK_WAIT_ON_SEND_STRING(sz_reportMed);
  ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
}

//is the new-old delta above 25?
inline BOOL esos_uiF14_isRpgTurningFast( void ) {
  static char sz_reportFast[64];
  sz_reportFast = "Turning fast";
  // code for determining speedy boi goes here
  //code for console output
  ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
  ESOS_TASK_WAIT_ON_SEND_STRING(sz_reportFast);
  ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
}

//determines if the encoder turning clockwise
inline BOOL esos_uiF14_isRpgTurningCW( void ) {
  static char sz_reportCW[64];
  sz_reportCW = "Turning clockwise";
  // code for determining CW goes here
  //code for console output
  ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
  ESOS_TASK_WAIT_ON_SEND_STRING(sz_reportCW);
  ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
}

//is the encoder turning counterclockwise
inline BOOL esos_uiF14_isRpgTurningCCW( void ) {
  static char sz_reportCCW[64];
  sz_reportCCW = "Turning counterclockwise";
  // code for determining ccw goes here
  //code for console output
  ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
  ESOS_TASK_WAIT_ON_SEND_STRING(sz_reportCCW);
  ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
}

//obtains the velocity of the encoder
int16_t esos_uiF14_getRpgVelocity_i16( void ) {
  // not yet implemented
}

// UIF14 INITIALIZATION FUNCTION

void config_esos_uiF14() {
  // setup your UI implementation
  esos_RegisterTask( __uiF14_task );
}


// UIF14 task to manage user-interface
ESOS_USER_TASK( __esos_uiF14_task ){

  ESOS_TASK_BEGIN();
  while(TRUE) {
    // do your UI stuff here
    ESOS_TASK_WAIT_TICKS( __ESOS_UIF14_UI_PERIOD );
  }
  ESOS_TASK_END();
}

void user_init(void){


}
