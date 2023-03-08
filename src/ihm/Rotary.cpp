#include "Rotary.h"

const unsigned char Rotary::_tableState[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | R_DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | R_DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};

Rotary::Rotary(InputInterface *inputA, InputInterface *inputB)
{
    _inputA = inputA;
    _inputB = inputB;
    _event = nullptr;
    _lastState = R_START;
}

Rotary::Rotary(InputInterface *inputA, InputInterface *inputB, RotaryEvent *event)
{
    _inputA = inputA;
    _inputB = inputB;
    _event = event;
    _lastState = R_START;
}

void Rotary::loop()
{   
    // Grab state of input pins.
    unsigned char valueA = _inputA->read() ? 0x1 : 0x0;
    unsigned char valueB = _inputB->read() ? 0x1 : 0x0;
    unsigned char rotaryPinsValue = (valueA << 1) | valueB;
    // Determine new state from the pins and state table.
    _lastState = _tableState[_lastState & 0xf][rotaryPinsValue];
    // Return emit bits, ie the generated event.
    unsigned char currentState = _lastState & 0x30;

    if(_event != nullptr) {
        if(currentState == R_DIR_CW) {
            _event->onMove(RotaryEventDirection::INCR);
        } else if(currentState == R_DIR_CCW) {
            _event->onMove(RotaryEventDirection::DECR);
        }
    }
}