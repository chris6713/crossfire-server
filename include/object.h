/*
 * static char *rcsid_object_h =
 *   "$Id$";
 */

/*
    CrossFire, A Multiplayer game for X-windows

    Copyright (C) 1992 Frank Tore Johansen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    The author can be reached via e-mail to mark@pyramid.com.
*/

#ifndef OBJECT_H
#define OBJECT_H

typedef struct obj {
/* These variables are not changed by copy_object(): */
  struct pl *contr;    /* Pointer to the player which control this object */
  struct obj *next;    /* Pointer to the next object in the free/used list */
  struct obj *prev;    /* Pointer to the previous object in the free/used list*/
  struct obj *active_next;	/* Next & previous object in the 'active' */
  struct obj *active_prev;	/* List.  This is used in process_events */
				/* so that the entire object list does not */
				/* need to be gone through. */
  struct obj *below;   /* Pointer to the object stacked below this one */
  struct obj *above;   /* Pointer to the object stacked above this one */
	         /* Note: stacked in the *same* environment*/
  struct obj *inv;     /* Pointer to the first object in the inventory */
  struct obj *container; /* Current container being used.  I think this
			  * is only used by the player right now.
			  */
  struct obj *env;     /* Pointer to the object which is the environment.
			* This is typically the container that the object is in.
			*/
  struct obj *more;    /* Pointer to the rest of a large body of objects */
  struct obj *head;    /* Points to the main object of a large body */
  struct mapdef *map;  /* Pointer to the map in which this object is present */

  uint32	count;         /* Which nr. of object created this is. */
  uint16	refcount;	/* How many objects points to this object */
  struct oblnk *sk_list;	/* Pointer to linked list of skill objects for this ob*/

/* These get an extra add_refcount(), after having been copied by memcpy() */
  char *name;			/* The name of the object, obviously... */
  char *title;			/* Of foo, etc */
  char *race;			/* human, goblin, dragon, etc */
  char *slaying;		/* Which race to do double damage to */
  char *msg;			/* If this is a book/sign/magic mouth/etc */
				/* If this is an exit, this is the filename */
/* These variables are copied by memcpy() in copy_object(): */
  sint16 x,y;			/* Position in the map for this object */
  sint16 ox,oy;			/* For debugging: Where it was last inserted */
  float speed;                  /* The overall speed of this object */
  float speed_left;             /* How much speed is left to spend this round */
  uint32	nrof;		/* How many of the objects */
  New_Face *face;		/* Face with colors */
  sint8		direction;	/* Means the object is moving that way. */
  sint8 facing;			/* Object is oriented/facing that way. */
  uint8 type; 		        /* PLAYER, BULLET, etc.  See define.h */
  /* The next 6 variables actually only really use 24 bits each */
  uint32	immune;		/* Attacks which the object is immune against */
  uint32	protected;	/* Attacks which does half damage */
  uint32	attacktype;	/* Same bitmask as immune/protected */
  uint32	vulnerable;	/* Attacks which does double damage */
  uint32	path_attuned;	/* Paths the object is attuned to */
  uint32	path_repelled;	/* Paths the object is repelled from */
  uint32	path_denied; 	/* Paths the object is denied access to */
  uint16	material;      	/* What materials this object consist of */
  sint8		magic;		/* Any magical bonuses to this item */
  sint8		thrownthaco;	/* How precise the throw is */
  uint8		state;          /* How the object was last drawn (animation) */
  sint32	value;		/* How much money it is worth (or contains) */
  signed short level;
  sint32 last_heal;       /* Last healed. Depends on constitution */
  sint32 last_sp;         /* As last_heal, but for spell points */
  signed short last_grace;      /* as last_sp, except for grace */
  signed short last_eat;	/* How long since we last ate */
  signed short invisible;	/* How much longer the object will be invis */
  sint8		armour;		/* How many % is subtracted from phys. damage */
  unsigned char pick_up;        /* See crossfire.doc */
  struct obj *owner;  /* Pointer to the object which controls this one */
                      /* Owner should not be referred to directly - */
                      /* get_owner should be used instead. */
  struct obj *enemy;   /* Monster/player to follow even if not closest */
  struct archt *arch;           /* Pointer to archetype */
  struct archt *other_arch;	/* Pointer used for various things */
  signed long weight;           /* Attributes of the object */
  signed long carrying;         /* How much weight this object contains */
  uint32 flags[4];		/* various flags */
  uint32 ownercount;		/* What count the owner had (in case owner */
				/* has been freed) */
  struct treasureliststruct *randomitems; /* Items to be generated */
#if 0
  unsigned short thrown;        /* How much further the object will fly */
#endif
/* Some debug variables: */
  unsigned short run_away;	/* Monster runs away if it's hp goes below \
				   this percentage. */
 
/* Not commented out by ALLOW_SKILLS - to many pieces of code want this
 * information
 */
  struct obj *chosen_skill;	/* the skill chosen to use */
  struct obj *exp_obj;		/* the exp. obj (category) assoc. w/ this object */
  uint32 hide;			/* The object is hidden, not invisible */

/* lighting code uses these - b.t. */
  struct oblnk *lights;   	/* list of lights the object carries */
  signed short glow_radius;	/* indicates the glow radius of the object */

/* changes made by kholland@sunlab.cit.cornell.edu */
/* allows different movement patterns for attackers */
  signed long move_status;      /* What stage in attack mode */
  unsigned short move_type;     /* What kind of attack movement */

  signed long weight_limit;     /* Weight-limit of object */
  unsigned char can_apply;      /* See crossfire.doc */
  unsigned char will_apply;     /* See crossfire.doc */
    uint16 animation_id;    /* An index into the animation array */
    uint8 anim_speed, last_anim; /* ticks between animation-frames */
  living stats;

#ifdef CASTING_TIME
  signed short casting;         /* time left before spell goes off */
  unsigned short spell_state;
  unsigned short start_holding;
  struct spell_struct *spell;
  unsigned int spelltype;
  char *spellarg;
#endif

  struct obj *spellitem;

/* This modification will allow variable experience requirements 
   for advancement (eanders@cmu.edu) */
  double expmul;        /* needed experience = (calc_exp*expmul) */
} object;

typedef struct oblnk { /* Used to link together several objects */
  object *ob;
  struct oblnk *next;
  int id;
} objectlink;

typedef struct oblinkpt { /* Used to link together several object links */
  struct oblnk *link;
  long value;		/* Used as connected value in buttons/gates */
  struct oblinkpt *next;
} oblinkpt;


/*
 * The archetype structure is a set of rules on how to generate and manipulate
 * objects which point to archetypes.
 * This probably belongs in arch.h, but there really doesn't appear to
 * be much left in the archetype - all it really is is a holder for the
 * object and pointers.  This structure should get removed, and just replaced
 * by the object structure
 */

typedef struct archt {
    char *name;		    /* More definite name, like "generate_kobold" */
    struct archt *next;	    /* Next archetype in a linked list */
    struct archt *head;	    /* The main part of a linked object */
    struct archt *more;	    /* Next part of a linked object */
    object clone;	    /* An object from which to do copy_object() */
    unsigned long editable; /* editable flags (mainly for editor) */
} archetype;


extern object *objects;
extern object *active_objects;
extern object *free_objects;
extern object objarray[STARTMAX];

extern int nrofallocobjects;
extern int nroffreeobjects;

/* This returns TRUE if the object is somethign that
 * should be displayed in the look window
 */
#define LOOK_OBJ(ob) (!ob->invisible && ob->type!=PLAYER)

#endif
