/*
 * static char *rcsid_alchemy_c =
 *   "$Id$";
 */

/*
    CrossFire, A Multiplayer game for X-windows

    Copyright (C) 2002 Mark Wedel & Crossfire Development Team
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

    The authors can be reached via e-mail at crossfire-devel@real-time.com
*/

/* March 96 - Laid down original code. -b.t. thomas@astro.psu.edu */

#include <global.h>
#include <object.h>
#ifndef __CEXTRACT__
#include <sproto.h>
#endif
#include <skills.h>
#include <spells.h>

/* define this for some helpful debuging information */
#define ALCHEMY_DEBUG

/* define this for loads of (marginal) debuging information */
#define EXTREME_ALCHEMY_DEBUG

static char *cauldron_effect [] = { 
 "vibrates briefly",
 "produces a cloud of steam",
 "emits bright flames",
 "pours forth heavy black smoke",
 "emits sparks",
 "shoots out small flames",
 "whines painfully",
 "hiccups loudly",
 "wheezes",
 "burps",
 "shakes",
 "rattles",
 "makes chugging sounds",
 "smokes heavily for a while"
}; 


/* cauldron_sound() - returns a random selection from cauldron_effect[] */

char * cauldron_sound ( void ) {
  int size=sizeof(cauldron_effect)/sizeof(char *);

  return cauldron_effect[rndm(0, size-1)]; 
}

/* attempt_do_alchemy() - Main part of the ALCHEMY code. From this we call fctns
 * that take a look at the contents of the 'cauldron' and, using these ingredients, 
 * we construct an integer formula value which is referenced (randomly) against a 
 * formula list (the formula list chosen is based on the # contents of the cauldron).
 *
 * If we get a match between the recipe indicated in cauldron contents and a 
 * randomly chosen one, an item is created and experience awarded. Otherwise 
 * various failure effects are possible (getting worse and worse w/ # cauldron 
 * ingredients). Note that the 'item' to be made can be *anything* listed on 
 * the artifacts list in lib/artifacts which has a recipe listed in lib/formulae.
 *
 * To those wondering why I am using the funky formula index method:
 *   1) I want to match recipe to ingredients regardless of ordering.
 *   2) I want a fast search for the 'right' recipe.
 * 
 * Note: it is just possible that a totally different combination of
 * ingredients will result in a match with a given recipe. This is not a bug!
 * There is no good reason (in my mind) why alchemical processes have to be
 * unique -- such a 'feature' is one reason why players might want to experiment
 * around. :)
 * -b.t.
 */
 
void attempt_do_alchemy(object *caster, object *cauldron) {
    recipelist *fl;
    recipe *rp=NULL;
    float success_chance;
    int numb, ability=1;
    int formula=0;
    float ave_chance;
    object *item, *skop;

    if (caster->type!=PLAYER)
	return; /* only players for now */ 

    /* if no ingredients, no formula! lets forget it */
    if (!(formula=content_recipe_value(cauldron))) return;
 
    numb=numb_ob_inside(cauldron);
    if ((fl=get_formulalist(numb))) {
        if (QUERY_FLAG(caster, FLAG_WIZ)) { 
	    rp=fl->items;
	    while (rp && (formula % rp->index)!=0) {
#ifdef EXTREME_ALCHEMY_DEBUG
		LOG(llevDebug, " found list %d formula: %s of %s (%d)\n", numb,
		    rp->arch_name, rp->title, rp->index);
#endif
	    	rp=rp->next;
	    }
	    if (rp) {
#ifdef ALCHEMY_DEBUG
		if(strcmp(rp->title, "NONE"))
		    LOG(llevDebug, "WIZ got formula: %s of %s\n",
			rp->arch_name, rp->title);
		else 
		    LOG(llevDebug, "WIZ got formula: %s (nbatches:%d)\n",
			rp->arch_name, formula/rp->index);
#endif
		attempt_recipe(caster, cauldron, ability, rp, formula/rp->index);
	    } else LOG(llevDebug, "WIZ couldnt find formula for ingredients.\n"); 
	    return;
	} /* End of WIZ alchemy */

	/* find the recipe */
	for (rp = fl->items;rp!=NULL && (formula % rp->index)!=0;rp=rp->next)
	    ;

	if (rp) { /* if we found a recipe */
	    ave_chance = fl->total_chance/(float)fl->number;
	    /* the caster gets an increase in ability based on thier skill lvl */
	    if (rp->skill != NULL) {
		skop = find_skill_by_name(caster, rp->skill);
		if (!skop) {
		    new_draw_info(NDI_UNIQUE, 0, caster, "You do not have the proper skill for this recipe");
		} else {
		    ability+=skop->level*((4.0 + cauldron->magic)/4.0);
		}
	    } else {
		LOG(llevDebug, "Recipe %s has NULL skill!\n", rp->title);
		return;
	    }

	    if (rp->cauldron == NULL) {
		LOG(llevDebug, "Recipe %s has NULL cauldron!\n", rp->title);
		return;
	    }

	    /* create the object **FIRST**, then decide whether to keep it.	*/
	    if ((item=attempt_recipe(caster, cauldron, ability, rp, formula/rp->index)) != NULL) {
		/*  compute base chance of recipe success */
		success_chance = ((float)ability /
				  (float)(rp->diff * (item->level+2)));
		if (ave_chance == 0)
		    ave_chance = 1;

#ifdef ALCHEMY_DEBUG
		LOG(llevDebug, "percent success chance =  %f ab%d / diff%d*lev%d\n",
		    success_chance, ability, rp->diff, item->level);
#endif

		/* roll the dice */
		if ((float)(random_roll(0, 101, caster, PREFER_LOW)) <= 100.0 * success_chance) {
		    change_exp(caster, rp->exp, rp->skill, SK_EXP_NONE);
		    return;
		}
	    }
	}
    }
    /* if we get here, we failed!! */
    alchemy_failure_effect(caster, cauldron, rp,
	calc_alch_danger(caster, cauldron, rp));
}

/* content_recipe_value()- recipe value of the entire contents of a container.
 * This appears to just generate a hash value, which I guess for now works
 * ok, but the possibility of duplicate hashes is certainly possible - msw
  */

int content_recipe_value (object *op) {
  char name[MAX_BUF];
  object *tmp=op->inv;
  int tval=0, formula=0;

    while(tmp) {
	tval=0;
        strcpy(name, tmp->name);
        if (tmp->title)
	    sprintf(name, "%s %s", tmp->name, tmp->title);
	tval = (strtoint(name) * (tmp->nrof?tmp->nrof:1));
#ifdef ALCHEMY_DEBUG
        LOG(llevDebug,"Got ingredient %d %s(%d)\n", tmp->nrof?tmp->nrof:1,
		name, tval);
#endif   
	formula += tval;
        tmp=tmp->below;
    }   
#ifdef ALCHEMY_DEBUG
    LOG(llevDebug, " Formula value=%d\n", formula);
#endif
    return formula;
}

/* numb_ob_inside() */

int numb_ob_inside (object *op) {
  object *tmp=op->inv;
  int number=0,o_number=0;

    while(tmp) {
        if(tmp->nrof) number += tmp->nrof;
        else number++;
	o_number++;
        tmp=tmp->below;
    }   
#ifdef ALCHEMY_DEBUG
    LOG(llevDebug,"numb_ob_inside(%s): found %d ingredients\n",op->name,o_number);
#endif 
    return o_number;
}
 
/* attempt_recipe() - essentially a wrapper for make_item_from_recipe() and 
 * insert_ob_in_ob. If the caster has some alchemy skill, then they might
 * gain some exp from (successfull) fabrication of the product. 
 * If nbatches==-1, don't give exp for this creation (random generation/
 * failed recipe)
 */ 
 
object * attempt_recipe(object *caster, object *cauldron, int ability, recipe *rp, int nbatches) { 

    object *item=NULL, *skop;
    /* this should be passed to this fctn, not effiecent cpu use this way */
    int batches=abs(nbatches);

    /* is the cauldron the right type? */
    if (strcmp(rp->cauldron, cauldron->arch->name) != 0) {
	new_draw_info(NDI_UNIQUE, 0, caster, "You are not using the proper"
	    " facilities for this formula.");
	return 0;
    }

    skop = find_skill_by_name(caster, rp->skill);
    /* does the caster have the skill? */
    if (!skop)
	return 0;

    /* code required for this recipe, search the caster */
    if(rp->keycode) {
	object *tmp;
	for(tmp=caster->inv; tmp != NULL; tmp=tmp->below) {
	    if(tmp->type==FORCE && tmp->slaying &&
		!strcmp(rp->keycode, tmp->slaying))
		break;
	}
	if(tmp==NULL) { /* failure--no code found */
	    new_draw_info(NDI_UNIQUE, 0, caster, "You know the ingredients,"
		" but not the technique.  Go learn how to do this recipe.");
	    return 0;  
	}
    }

#ifdef EXTREME_ALCHEMY_DEBUG
    LOG(llevDebug,"attempt_recipe(): got %d nbatches\n",nbatches);
    LOG(llevDebug,"attempt_recipe(): using recipe %s\n",
	rp->title?rp->title:"unknown");
#endif

    if((item=make_item_from_recipe(cauldron, rp))!=NULL) {
	remove_contents(cauldron->inv, item);
        /* adj lvl, nrof on caster level */
	adjust_product(item, ability, rp->yield?(rp->yield*batches):batches);
	if(!item->env && (item=insert_ob_in_ob(item,cauldron)) == NULL) {
	    new_draw_info(NDI_UNIQUE, 0,caster,"Nothing happened.");
	    /* new_draw_info_format(NDI_UNIQUE, 0,caster,
	       "Your spell causes the %s to explode!",cauldron->name); */
	    /* kaboom_cauldron(); */
	} else {
	    new_draw_info_format(NDI_UNIQUE, 0,caster,
		"The %s %s.",cauldron->name,cauldron_sound());
	}
    }
    return item;
}



/* adjust_product() - we adjust the nrof, exp and level of the final product, based
 * on the item's default parameters, and the relevant caster skill level. */

void adjust_product(object *item, int lvl, int yield) {
    int nrof=1;

    if (!yield)
	yield = 1;
    if (lvl<=0)
	lvl = 1; /* lets avoid div by zero! */ 
    if (item->nrof) {
	nrof = (1.0 - 1.0/(lvl/10.0 + 1.0)) *
	    (rndm(0, yield-1) + rndm(0, yield-1) + rndm(0, yield-1)) + 1;
	if (nrof > yield)
	    nrof = yield;
	item->nrof=nrof;
    }
}


/* make_item_from_recipe()- using a list of items and a recipe to make an artifact. */
 
object * make_item_from_recipe(object *cauldron, recipe *rp) {
  artifact *art=NULL;
  object *item=NULL;
 
    if(rp==NULL) return (object *) NULL;

    /* Find the appropriate object to transform...*/
    if((item=find_transmution_ob(cauldron->inv,rp))==NULL) {
        LOG(llevDebug,"make_alchemy_item(): failed to create alchemical object.\n");
        return (object *) NULL;
    }
 
    /* Find the appropriate artifact template...*/
    if(strcmp(rp->title,"NONE")) { 
        if((art=locate_recipe_artifact(rp))==NULL) {
            LOG(llevError,"make_alchemy_item(): failed to locate recipe artifact.\n");
            LOG(llevDebug,"  --requested recipe: %s of %s.\n",rp->arch_name,rp->title);
            return (object *) NULL;
	}
	transmute_materialname(item, art->item);
        give_artifact_abilities(item, art->item);
    }
 
    if(QUERY_FLAG(cauldron,FLAG_CURSED)) SET_FLAG(item,FLAG_CURSED);
    if(QUERY_FLAG(cauldron,FLAG_DAMNED)) SET_FLAG(item,FLAG_DAMNED);
 
    return item;
}


/* find_transmution_ob() - looks through the ingredient list, if we find a
 * suitable object in it - we will use that to make the requested artifact.
 * Otherwise the code returns a 'generic' item. -b.t.
 */
 
object * find_transmution_ob ( object *first_ingred, recipe *rp) {
   object *item=NULL;
 
   if(rp->transmute) /* look for matching ingredient/prod archs */ 
        for(item=first_ingred;item;item=item->below)
            if(!strcmp(item->arch->name,rp->arch_name)) break; 
 
    /* failed, create a fresh object. Note no nrof>1 because that would
     * allow players to create massive amounts of artifacts easily */
   if(!item||item->nrof>1)
        item=get_archetype(rp->arch_name);

#ifdef ALCHEMY_DEBUG
   LOG(llevDebug,"recipe calls for%stransmution.\n",rp->transmute?" ":" no ");
   if(strcmp(item->arch->name,rp->arch_name))
       LOG(llevDebug,"WARNING: recipe calls for arch: %s\n",rp->arch_name);
   LOG(llevDebug," find_transmutable_ob(): returns arch %s(sp:%d)\n",
	    item->arch->name,item->stats.sp);
#endif
 
   return item;
}


/* alchemy_failure_effect - Ouch. We didnt get the formula we wanted.
 * This fctn simulates the backfire effects--worse effects as the level
 * increases. If SPELL_FAILURE_EFFECTS is defined some really evil things
 * can happen to the would be alchemist. This table probably needs some
 * adjustment for playbalance. -b.t.
 */
 
void alchemy_failure_effect(object *op,object *cauldron,recipe *rp,int danger) {
    int level=0;
 
    if(!op || !cauldron) return; 

    if(danger>1) level=random_roll(1, danger, op, PREFER_LOW);

#ifdef ALCHEMY_DEBUG
    LOG(llevDebug,"Alchemy_failure_effect(): using level=%d\n",level); 
#endif

    /* possible outcomes based on level */
    if(level<25) { 		      	/* INGREDIENTS USED/SLAGGED */
	object *item=NULL;
 
	if(rndm(0, 2)) {  /* slag created */
	    object *tmp=cauldron->inv;
	    int weight=0;
	    uint16 material=M_STONE;

	    while(tmp) { /* slag has coadded ingredient properties */
		weight+=tmp->weight; 
		if(!(material&tmp->material)) 
		    material |= tmp->material; 
		tmp=tmp->below;
	    }
	    tmp = get_archetype("rock");
	    tmp->weight=weight;
	    tmp->value=0;
	    tmp->material=material;
	    tmp->materialname = add_string("stone");
	    free_string(tmp->name);
	    tmp->name=add_string("slag");
	    if (tmp->name_pl) free_string(tmp->name_pl);
	    tmp->name_pl=add_string("slags");
	    item=insert_ob_in_ob(tmp,cauldron);
	    CLEAR_FLAG(tmp,FLAG_CAN_ROLL);
	    CLEAR_FLAG(tmp,FLAG_NO_PICK);
	    CLEAR_FLAG(tmp,FLAG_NO_PASS);
	}
	remove_contents(cauldron->inv,item);
	new_draw_info_format(NDI_UNIQUE,0,op, 
		     "The %s %s.",cauldron->name,cauldron_sound());
	return;
    } else if (level< 40) {                	/* MAKE TAINTED ITEM */
	object *tmp=NULL;

	if (!rp) 
	   if((rp=get_random_recipe((recipelist *) NULL))==NULL) 
	      	return;

	if((tmp=attempt_recipe(op,cauldron,1,rp,-1))) { 
	    if(!QUERY_FLAG(tmp,FLAG_CURSED)) /* curse it */
	   	SET_FLAG(tmp,FLAG_CURSED);

	    /* the apply code for potions already deals with cursed
	     * potions, so any code here is basically ignored.
	     */
	    if(tmp->type==FOOD) {
		tmp->stats.hp=random_roll(0, 149, op, PREFER_LOW);
	    }
	   tmp->value = 0; /* unsaleable item */
 
       	   /* change stats downward */
 	   do {
           	change_attr_value(&tmp->stats,rndm(0, 6),-1*(rndm(1, 3)));
           } while (rndm(0, 2));
	}
	return;
    } if(level==40) {                  		/* MAKE RANDOM RECIPE */
	recipelist *fl;
	int numb=numb_ob_inside(cauldron);

	fl=get_formulalist(numb-1); /* take a lower recipe list */ 
	if(fl &&(rp=get_random_recipe(fl)))
	    /* even though random, don't grant user any EXP for it */
	    (void) attempt_recipe(op,cauldron,1,rp,-1);
	else 
	    alchemy_failure_effect(op,cauldron,rp,level-1);
	return;

    } else if (level<45) {                	/* INFURIATE NPC's */
	/* this is kind of kludgy I know...*/
	cauldron->enemy=op;
	npc_call_help(cauldron);
	cauldron->enemy=NULL;

	alchemy_failure_effect(op,cauldron,rp,level-5);
	return;
    } else if (level<50) {               		/* MINOR EXPLOSION/FIREBALL */
	object *tmp;
	remove_contents(cauldron->inv,NULL);
	switch(rndm(0, 2)) {
	    case 0: 
		tmp=get_archetype("bomb");
		tmp->stats.dam=random_roll(1, level, op, PREFER_LOW);
		tmp->stats.hp=random_roll(1, level, op, PREFER_LOW);
		new_draw_info_format(NDI_UNIQUE,0,op,"The %s creates a bomb!",
				     cauldron->name);
		break; 

	    default:
		tmp=get_archetype("fireball");
		tmp->stats.dam=random_roll(1, level, op, PREFER_LOW)/5+1;
		tmp->stats.hp=random_roll(1, level, op, PREFER_LOW)/10+2;
		new_draw_info_format(NDI_UNIQUE,0,op,"The %s erupts in flame!",
				     cauldron->name);
		break;
	}
	tmp->x=cauldron->x,tmp->y=cauldron->y;
	insert_ob_in_map(tmp,op->map,NULL,0);
	return;

    } else if (level<60) {                	/* CREATE MONSTER */
	new_draw_info_format(NDI_UNIQUE,0,op, 
			     "The %s %s.",cauldron->name,cauldron_sound());
	remove_contents(cauldron->inv,NULL);
	return;
    } else if (level<80) {                	/* MAJOR FIRE */
	object *fb = get_archetype(SP_MED_FIREBALL);
	remove_contents(cauldron->inv,NULL);
	fire_arch_from_position(cauldron, cauldron,cauldron->x, cauldron->y,
	    0, fb);
	free_object(fb);
	new_draw_info_format(NDI_UNIQUE,0,op,"The %s erupts in flame!",
			     cauldron->name);
	return;

    } else if (level<100) {               	/* WHAMMY the CAULDRON */
	if(!QUERY_FLAG(cauldron,FLAG_CURSED))
	    SET_FLAG(cauldron,FLAG_CURSED);
	else cauldron->magic--;
	cauldron->magic -= random_roll(0, 4, op, PREFER_LOW);
	if(rndm(0, 1)) {
	    remove_contents(cauldron->inv,NULL);
	    new_draw_info_format(NDI_UNIQUE,0,op,
		 "Your %s turns darker then makes a gulping sound!",
		 cauldron->name);
	} else
	    new_draw_info_format(NDI_UNIQUE,0,op,
		"Your %s becomes darker.",cauldron->name);
	return;

    } else if (level<110) {               	/* SUMMON EVIL MONSTERS */
	object *tmp=get_random_mon(level/5);

	remove_contents(cauldron->inv,NULL);
	if(!tmp) 
	    alchemy_failure_effect(op,cauldron,rp,level);
	else if(summon_hostile_monsters(cauldron, random_roll(1, 10, op, PREFER_LOW), tmp->arch->name))
	    new_draw_info_format(NDI_UNIQUE, 0,op,
		 "The %s %s and then pours forth monsters!",
		 cauldron->name,cauldron_sound());
	return;

    } else if (level<150) {               	/* COMBO EFFECT */
	int roll = rndm(1, 3);
	while(roll) {
	    alchemy_failure_effect(op,cauldron,rp,level-39);
	    roll--;
	}
	return;
    } else if (level==151) {              	/* CREATE RANDOM ARTIFACT */
	object *tmp;
	/* this is meant to be better than prior possiblity, 
	 * in this one, we allow *any* valid alchemy artifact
  	 * to be made (rather than only those on the given
	 * formulalist) */
	if(!rp) rp=get_random_recipe((recipelist *) NULL);
	if(rp && (tmp=get_archetype(rp->arch_name))) { 
	    generate_artifact(tmp,random_roll(1, op->level/2+1, op, PREFER_HIGH)+1);
	    if((tmp=insert_ob_in_ob(tmp,cauldron))) { 
		remove_contents(cauldron->inv,tmp);
		new_draw_info_format(NDI_UNIQUE, 0,op,
				     "The %s %s.",cauldron->name,cauldron_sound());
	    }
	}
	return;
  } else {               	/* MANA STORM - watch out!! */
	object *tmp = get_archetype(LOOSE_MANA);
	new_draw_info(NDI_UNIQUE,0,op,"You unwisely release potent forces!");
	remove_contents (cauldron->inv,NULL);
	cast_magic_storm(op,tmp, level);
	return;
  }
}


/* remove_contents() - all but object "save_item" are elimentated from
 * the container list. Note we have to becareful to remove the inventories
 * of objects in the cauldron inventory (ex icecube has stuff in it).  
 */
 
void remove_contents (object *first_ob, object *save_item) {
  object *next,*tmp=first_ob;
 
    while(tmp) {
        next = tmp->below;
        if(tmp==save_item) {
          if(!(tmp=next)) break;
          else next=next->below;
	}
 	if(tmp->inv) remove_contents(tmp->inv,NULL);
        remove_ob(tmp);
        free_object(tmp);
        tmp=next;
    }
}

/* calc_alch_danger() - "Danger" level will determine how bad the backfire
 * could be if the user fails to concoct a recipe properly. Factors include
 * the number of ingredients, the length of the name of each ingredient,
 * the user's effective level, the user's Int and the enchantment on the
 * mixing device (aka "cauldron"). Higher values of 'danger' indicate more
 * danger. Note that we assume that we have had the caster ready the alchemy
 * skill *before* this routine is called. (no longer auto-readies that skill) 
 * -b.t. 
 */
 
int calc_alch_danger(object *caster,object *cauldron, recipe *rp) {
   object *item; 
   char name[MAX_BUF];
   int danger=0,nrofi=0; 
 
    /* Knowing alchemy skill reduces yer risk */
   danger -= caster->chosen_skill?caster->chosen_skill->level:caster->level;

   /* better cauldrons reduce risk */
   danger -= cauldron->magic;

   /* Higher Int, lower the risk */
   danger -= 3 * (caster->stats.Int - 15);
 
    /* Ingredients. Longer names usually mean rarer stuff.
     * Thus the backfire is worse. Also, more ingredients
     * means we are attempting a more powerfull potion,
     * and thus the backfire will be worse.  */
   for(item=cauldron->inv;item;item=item->below) {
        strcpy(name,item->name);
        if(item->title) sprintf(name,"%s %s",item->name,item->title);
        danger += (strtoint(name)/1000) + 3;
	nrofi++;
   }
   if (rp == NULL)
       danger += 110;
   else
       danger += rp->diff*3;
 
    /* Using a bad device is *majorly* stupid */
   if(QUERY_FLAG(cauldron,FLAG_CURSED)) danger +=80;
   if(QUERY_FLAG(cauldron,FLAG_DAMNED)) danger +=200;

#ifdef ALCHEMY_DEBUG
   LOG(llevDebug,"calc_alch_danger() returned danger=%d\n",danger);
#endif

   return danger;
}


