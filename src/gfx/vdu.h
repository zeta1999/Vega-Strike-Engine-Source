#ifndef _GFX_VDU_H_
#define _GFX_VDU_H_

#include "cockpit_generic.h"
#include "sprite.h"
#include <string>
#include <vector>

class Unit;
class TextPlane;


/**
 * Holds information for dedicated computer output
 * on a fighter craft. Can print out target info, local damage info
 * Local weapon info or Nav info.
 */
class VDU: public Sprite {
 private:
  class Animation * comm_ani;
  VIEWSTYLE viewStyle;
  unsigned short * StartArmor;
  float *maxhull;
  ///Holds a pointer to the font used to render text in the vdu
  TextPlane *tp;
  ///potential modes this computer is equipped for
  unsigned int posmodes;
  ///The current mode (VDU_MODE) that this unit is in is in back of this vector
  std::vector <unsigned int> thismode;
  
  ///Rows and columns of text this VDU can display
  short rows,cols;

  int DrawVDUObjective (void * obj, int offset);//obj is of type Mission::Objective
  void DrawVDUObjectives(Unit * parent);
  ///Draws a shield display in the VDU
  void DrawVDUShield (Unit * parent);
  ///Draws the target display of Unit *target (only call with nonNULL)
  void DrawTarget(Unit * parent, Unit *target);
  ///Draws a list of cargo contents
  void DrawManifest (Unit * parent, Unit * target);
  ///Draws the message from the messagecenter
  void DrawMessages(Unit *target);
  ///Draws the nav point this unit is heading to
  void DrawNav(const Vector &navPoint);
  ///Draws the comm screen this unit can use to communicate
  void DrawComm();
  ///Draws the damage this unit has sustained
  void DrawDamage(Unit * parent);
  ///Draws the weapons activated on current unit
  void DrawWeapon(Unit *parent);
  ///Draws the sprite representing the current starship. Returns proper location and size for future use (with weaps and damage display)
  void DrawTargetSpr(Sprite * s,float percent, float &x, float &y, float &w, float &h);
  ///draws the target camera
void  DrawStarSystemAgain (float x,float y,float w,float h, VIEWSTYLE viewStyle,Unit *parent,Unit *target);
public:
 unsigned int getMode() {return thismode.back();}
  int scrolloffset;
  ///Alert! To add a mode must change const array on the bottom. VIEW must remain LAST
  enum VDU_MODE {TARGET=0x1,NAV=0x2,OBJECTIVES=0x4, COMM=0x8, WEAPON=0x10, DAMAGE=0x20, SHIELD=0x40,  MANIFEST=0x80, TARGETMANIFEST=0x100, VIEW=0x200, MSG=0x400};
  VDU(const char *file, TextPlane *textp,unsigned short modes, short rows, short cols, unsigned short *MaxArmor, float * maxhull);
  ///Draws the entire VDU, all data, etc
  void Draw(Unit * parent, const GFXColor & c);
  ///Changes the mode of the current VDU to another legal mode
  void SwitchMode();
  void SetViewingStyle (VIEWSTYLE vm);
  void Scroll (int howmuch);
  bool SetCommAnimation (Animation *ani);
};

int parse_vdu_type (const char * s);

#endif
