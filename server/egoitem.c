/*
 * static char *rcsid_egoitem_c =
 *   "$Id$";
 */
 

#include <global.h>
#ifndef __CEXTRACT__
#include <sproto.h>
#endif



/*  peterm:  do_power_crystal

  object *op, object *crystal

  This function handles the application of power crystals.
  Power crystals, when applied, either suck power from the applier,
  if he's at full spellpoints, or gives him power, if it's got 
  spellpoins stored.  

*/

int apply_power_crystal(object *op, object *crystal) {
  int available_power;
  int power_space;
  int power_grab;

  available_power =  op->stats.sp - op->stats.maxsp;
  power_space = crystal->stats.maxsp - crystal->stats.sp;
  power_grab = 0;
  if(available_power>=0 && power_space> 0 )  
        power_grab = MIN ( power_space, 0.5 * op->stats.sp );
  if(available_power < 0 && crystal->stats.sp >0 ) 
        power_grab = - MIN( -available_power, crystal->stats.sp);

  op->stats.sp-=power_grab;
  crystal->stats.sp +=power_grab;
  crystal->speed = (float)crystal->stats.sp/(float)crystal->stats.maxsp;
  update_ob_speed(crystal);
  esrv_update_item(UPD_ANIMSPEED, op, crystal);

  return 1;
}

