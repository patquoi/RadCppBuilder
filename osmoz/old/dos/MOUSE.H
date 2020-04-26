#include <dos.h>

typedef unsigned Matrix[32];

class mouse
 {
  struct REGPACK r;
  public:
  unsigned Buttons;
  unsigned NumCurs;
  mouse();
  void CursorOn();
  void CursorOff();
  void GetMouse(unsigned *, unsigned *, unsigned *, unsigned *, unsigned *);
  int CursorCond(unsigned, unsigned, unsigned, unsigned);
  int ButtonPressed();
  void RepeatUntilNoPress();
  void GetButtons(unsigned *,unsigned *,unsigned *);
  void MoveMouse(unsigned, unsigned);
  void WinMouse(unsigned, unsigned, unsigned, unsigned);
  void SetMouseCursor(unsigned, unsigned, int);
 };
