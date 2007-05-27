/*
 * static char *rcsid_button_c =
 *   "$Id$";
 */

/*
    CrossFire, A Multiplayer game for X-windows

    Copyright (C) 2002-2006 Mark Wedel & Crossfire Development Team
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

/**
 * @file common/button.c
 * This handles triggers, buttons, altars and associated objects.
 */

#include <global.h>


/**
 * Push the specified object.  This can affect other buttons/gates/handles
 * altars/pedestals/holes in the whole map.
 * Changed the routine to loop through _all_ linked objects.
 * Better hurry with that linked list...
 * @param op
 * object to push.
 */
void push_button(object *op) {
    object *tmp;
    objectlink *ol;

    /* LOG(llevDebug, "push_button: %s (%d)\n", op->name, op->count); */
    for (ol = get_button_links(op); ol; ol = ol->next) {
        if (!ol->ob || ol->ob->count != ol->id) {
            LOG(llevError, "Internal error in push_button (%s).\n", op->name);
            continue;
        }
        /* a button link object can become freed when the map is saving.  As
         * a map is saved, objects are removed and freed, and if an object is
         * on top of a button, this function is eventually called.  If a map
         * is getting moved out of memory, the status of buttons and levers
         * probably isn't important - it will get sorted out when the map is
         * re-loaded.  As such, just exit this function if that is the case.
         */

        if (QUERY_FLAG(ol->ob, FLAG_FREED)) return;
        tmp = ol->ob;

        /* if the criteria isn't appropriate, don't do anything */
        if (op->value && !QUERY_FLAG(tmp, FLAG_ACTIVATE_ON_PUSH)) continue;
        if (!op->value && !QUERY_FLAG(tmp, FLAG_ACTIVATE_ON_RELEASE)) continue;

        switch(tmp->type) {

            case GATE:
            case HOLE:
                tmp->value=tmp->stats.maxsp?!op->value:op->value;
                tmp->speed=0.5;
                update_ob_speed(tmp);
                break;

            case CF_HANDLE:
                SET_ANIMATION(tmp, (tmp->value=tmp->stats.maxsp?!op->value:op->value));
                update_object(tmp,UP_OBJ_FACE);
                break;

            case SIGN:
                if (!tmp->stats.food || tmp->last_eat < tmp->stats.food) {
                    ext_info_map(NDI_UNIQUE | NDI_NAVY,tmp->map,
                        MSG_TYPE_SIGN,MSG_SUBTYPE_NONE,
                        tmp->msg, tmp->msg);
                    if (tmp->stats.food) tmp->last_eat++;
                }
                break;

            case ALTAR:
                tmp->value = 1;
                SET_ANIMATION(tmp, tmp->value);
                update_object(tmp,UP_OBJ_FACE);
                break;

            case BUTTON:
            case PEDESTAL:
                tmp->value=op->value;
                SET_ANIMATION(tmp, tmp->value);
                update_object(tmp,UP_OBJ_FACE);
                break;

            case MOOD_FLOOR:
                do_mood_floor(tmp, op);
                break;

            case TIMED_GATE:
                tmp->speed = tmp->arch->clone.speed;
                update_ob_speed(tmp);  /* original values */
                tmp->value = tmp->arch->clone.value;
                tmp->stats.sp = 1;
                tmp->stats.hp = tmp->stats.maxhp;
                 /* Handle multipart gates.  We copy the value for the other parts
                 * from the head - this ensures that the data will consistent
                 */
                for (tmp=tmp->more; tmp!=NULL; tmp=tmp->more) {
                    tmp->speed = tmp->head->speed;
                    tmp->value = tmp->head->value;
                    tmp->stats.sp = tmp->head->stats.sp;
                    tmp->stats.hp = tmp->head->stats.hp;
                    update_ob_speed(tmp);
                }
                break;

            case DIRECTOR:
            case FIREWALL:
                if(!QUERY_FLAG(tmp,FLAG_ANIMATE)&&tmp->type==FIREWALL) move_firewall(tmp);
                else {
                    if ((tmp->stats.sp += tmp->stats.maxsp) > 8) /* next direction */
                        tmp->stats.sp = ((tmp->stats.sp-1)%8)+1;
                    animate_turning(tmp);
                }
                break;

            case TELEPORTER:
                move_teleporter(tmp);
                break;

            case CREATOR:
                move_creator(tmp);
                break;

            case TRIGGER_MARKER:
                move_marker(tmp);
                break;

            case DUPLICATOR:
                move_duplicator(tmp);
                break;
        }
    }
}

/**
 * Updates everything connected with the button op.
 * After changing the state of a button, this function must be called
 * to make sure that all gates and other buttons connected to the
 * button reacts to the (eventual) change of state.
 * @param op
 * object to update.
 */
void update_button(object *op) {
    object *ab,*tmp,*head;
    int tot,any_down=0, old_value=op->value;
    objectlink *ol;

    /* LOG(llevDebug, "update_button: %s (%d)\n", op->name, op->count); */
    for (ol = get_button_links(op); ol; ol = ol->next) {
        if (!ol->ob || ol->ob->count != ol->id) {
            LOG(llevDebug, "Internal error in update_button (%s).\n", op->name);
            continue;
        }
        tmp = ol->ob;
        if (tmp->type==BUTTON) {
            for(ab=tmp->above,tot=0;ab!=NULL;ab=ab->above)
            /* Bug? The pedestal code below looks for the head of
             * the object, this bit doesn't.  I'd think we should check
             * for head here also.  Maybe it also makese sense to 
             * make the for ab=tmp->above loop common, and alter
             * behaviour based on object within that loop?
             */

            /* Basically, if the move_type matches that on what the
             * button wants, we count it.  The second check is so that
             * objects don't move (swords, etc) will count.  Note that
             * this means that more work is needed to make buttons
             * that are only triggered by flying objects.
             */
                if ((ab->move_type & tmp->move_on) || ab->move_type==0 ) 
                    tot+=ab->weight*(ab->nrof?ab->nrof:1)+ab->carrying;

            tmp->value=(tot>=tmp->weight)?1:0;
            if(tmp->value)
                any_down=1;
        } else if (tmp->type == PEDESTAL) {
            tmp->value = 0;
            for(ab=tmp->above; ab!=NULL; ab=ab->above) {
                head = ab->head ? ab->head : ab;
                /* Same note regarding move_type for buttons above apply here. */
                if  ( ((head->move_type & tmp->move_on) || ab->move_type==0) &&
                        (head->race==tmp->slaying ||
                        ((head->type==SPECIAL_KEY) && (head->slaying==tmp->slaying)) || 
                        (!strcmp (tmp->slaying, "player") && 
                        head->type == PLAYER)))
                    tmp->value = 1;
            }
            if(tmp->value)
                any_down=1;
        }
    }
    if(any_down) /* If any other buttons were down, force this to remain down */
        op->value=1;

    /* If this button hasn't changed, don't do anything */
    if (op->value != old_value) {
        SET_ANIMATION(op, op->value);
        update_object(op, UP_OBJ_FACE);
        push_button(op); /* Make all other buttons the same */
    }
}

/**
 * Updates every button on the map (by calling update_button() for them).
 */
void update_buttons(mapstruct *m) {
    objectlink *ol;
    oblinkpt *obp;
    for (obp = m->buttons; obp; obp = obp->next)
        for (ol = obp->link; ol; ol = ol->next) {
        if (!ol->ob || ol->ob->count != ol->id) {
            LOG(llevError, "Internal error in update_button (%s (%dx%d):%d, connected %ld).\n",
                ol->ob?ol->ob->name:"null",
                ol->ob?ol->ob->x:-1,
                ol->ob?ol->ob->y:-1,
                ol->id,
                obp->value);
            continue;
        }
        if (ol->ob->type==BUTTON || ol->ob->type==PEDESTAL)
        {
            update_button(ol->ob);
            break;
        }
        }
}

/**
 * Toggles the state of specified button.
 * @param op
 * object to toggle.
 */
void use_trigger(object *op) 
{
    /* Toggle value */
    op->value = !op->value;
    push_button(op);
}

/**
 * Animates one step of object.
 * @param op
 * object to animate.
 * @note
 * animate_object() should be used instead of this,
 * but it can't handle animations in the 8 directions
 * @todo
 * check if object is really animated?
 */
void animate_turning(object *op)
{
    if (++op->state >= NUM_ANIMATIONS(op)/8)
      op->state=0; 
    SET_ANIMATION(op, (op->stats.sp-1) * NUM_ANIMATIONS(op) / 8 + 
		  op->state);
    update_object(op,UP_OBJ_FACE);
}

#define ARCH_SACRIFICE(xyz) ((xyz)->slaying)
#define NROF_SACRIFICE(xyz) ((uint32)(xyz)->stats.food)

/**
 * Helper function to check if the item matches altar's requested sacrifice.
 * The number of objects is not taken into account.
 *
 * @param altar
 * altar we're checking for. Can't be NULL.
 * @param sacrifice
 * what object to check for. Can't be NULL.
 * @return
 * 1 if object is suitable for the altar (number not taken into account), 0 else.
 */
static int matches_sacrifice(const object* altar, const object* sacrifice) {
    char name[MAX_BUF];
    if (QUERY_FLAG(sacrifice, FLAG_ALIVE) || QUERY_FLAG(sacrifice, FLAG_IS_LINKED) || sacrifice->type == PLAYER)
        return 0;

    query_base_name(sacrifice,0, name, MAX_BUF);
    if (ARCH_SACRIFICE(altar) == sacrifice->arch->name ||
      ARCH_SACRIFICE(altar) == sacrifice->name ||
      ARCH_SACRIFICE(altar) == sacrifice->slaying ||
      (!strcmp(ARCH_SACRIFICE(altar),name)))
            return 1;
    if (strcmp (ARCH_SACRIFICE(altar), "money") == 0 && sacrifice->type == MONEY)
        return 1;

    return 0;
}


/**
 * Checks whether the altar has enough to sacrifice.
 *
 * Function put in (0.92.1) so that identify altars won't grab money
 * unnecessarily - we can see if there is sufficient money, see if something
 * needs to be identified, and then remove money if needed.
 *
 * 0.93.4: Linked objects (ie, objects that are connected) can not be
 * sacrificed.  This fixes a bug of trying to put multiple altars/related
 * objects on the same space that take the same sacrifice.
 *
 * The function will now check for all items sitting on the altar, so that the player
 * can put various matching but non merging items on the altar.
 *
 * This function can potentially remove other items, if remove_others is set.
 *
 * @param altar
 * item to which there is a sacrifice
 * @param sacrifice
 * object that may be sacrifed
 * @param remove_others
 * if 1, will remove enough items apart sacrifice to compensate for not having enough in sacrifice itself.
 * @param[out] toremove
 * will contain the nrof of sacrifice to really remove to finish operating. Will be set if not NULL only
 * if the function returns 1.
 * @return
 * 1 if the sacrifice meets the needs of the altar, 0 else
 */
int check_altar_sacrifice (const object *altar, const object *sacrifice, int remove_others, int* toremove)
{
    int money;
    object* tmp;
    int wanted, rest;
    object* above;

    if (!matches_sacrifice(altar, sacrifice))
        /* New dropped object doesn't match the altar, other objects already on top are not enough to
         * activate altar, else they would have disappeared. */
        return 0;

    money = (strcmp (ARCH_SACRIFICE(altar), "money") == 0) ? 1 : 0;

    /* Easy checks: newly dropped object is enough for sacrifice. */
    if (money && sacrifice->nrof * sacrifice->value >= NROF_SACRIFICE(altar)) {
        if (toremove) {
            *toremove = NROF_SACRIFICE(altar) / sacrifice->value;
            /* Round up any sacrifices.  Altars don't make change either */
            if (NROF_SACRIFICE(altar) % sacrifice->value)
                (*toremove)++;
        }
        return 1;
    }

    if (!money && NROF_SACRIFICE(altar) <= (sacrifice->nrof?sacrifice->nrof:1)) {
        if (toremove)
            *toremove = NROF_SACRIFICE(altar);
        return 1;
    }

    if (money) {
        wanted = NROF_SACRIFICE(altar) - sacrifice->nrof * sacrifice->value;
    }
    else {
        wanted = NROF_SACRIFICE(altar) - (sacrifice->nrof?sacrifice->nrof:1);
    }
    rest = wanted;

    /* Ok, now we check if we got enough with other items.
     * We only check items above altar, and not checking again sacrifice.
     */
    for (tmp = altar->above; tmp != NULL && wanted > 0; tmp = tmp->above) {
        if (tmp == sacrifice || !matches_sacrifice(altar, tmp))
            continue;
        if (money)
            wanted -= tmp->nrof * tmp->value;
        else
            wanted -= (tmp->nrof?tmp->nrof:1);
    }

    if (wanted > 0)
        /* Not enough value, let's bail out. */
         return 0;

    /* From there on, we do have enough objects for the altar. */

    /* Last dropped object will be totally eaten in any case. */
    if (toremove)
        *toremove = sacrifice->nrof ? sacrifice->nrof : 1;

    if (!remove_others)
        return 1;

    /* We loop again, this time to remove what we need. */
    for (tmp = altar->above; tmp != NULL && rest > 0; tmp = above) {
        above = tmp->above;
        if (tmp == sacrifice || !matches_sacrifice(altar, tmp))
            continue;
        if (money) {
            wanted = tmp->nrof * tmp->value;
            if (rest > wanted) {
                remove_ob(tmp);
                rest -= wanted;
            } else {
                wanted = rest / tmp->value;
                if (rest % tmp->value)
                    wanted++;
                decrease_ob_nr(tmp, wanted);
                return 1;
            }
        }
        else
            if (rest > (tmp->nrof?tmp->nrof:1)) {
                rest -= (tmp->nrof?tmp->nrof:1);
                remove_ob(tmp);
            } else {
                decrease_ob_nr(tmp, rest);
                return 1;
            }
    }

    /* Something went wrong, we'll be nice and accept the sacrifice anyway. */
    LOG(llevError, "check_altar_sacrifice on %s: found objects to sacrifice, but couldn't remove them??\n", altar->map->path);
    return 1;
}


/**
 * Checks if sacrifice was accepted and removes sacrificed
 * objects.  Might be better to
 * call check_altar_sacrifice (above) than depend on the return value,
 * since operate_altar will remove the sacrifice also.
 *
 * If this function returns 1, '*sacrifice' is modified to point to the
 * remaining sacrifice, or is set to NULL if the sacrifice was used up.
 *
 * @param altar
 * item to which there is a sacrifice
 * @param sacrifice
 * object that may be sacrifed
 * @return
 * 1 if sacrifice was accepted, else 0
 */
int operate_altar (object *altar, object **sacrifice)
{
    int number;
    if ( ! altar->map) {
        LOG (llevError, "BUG: operate_altar(): altar has no map\n");
        return 0;
    }

    if (!altar->slaying || altar->value)
        return 0;

    if ( ! check_altar_sacrifice (altar, *sacrifice, 1, &number))
        return 0;

    /* check_altar_sacrifice fills in number for us. */
    *sacrifice = decrease_ob_nr (*sacrifice, number);

    if (altar->msg)
        ext_info_map(NDI_BLACK, altar->map, MSG_TYPE_DIALOG, MSG_TYPE_DIALOG_ALTAR,
            altar->msg, altar->msg);
    return 1;
}

/**
 * @todo document?
 */
void trigger_move (object *op, int state) /* 1 down and 0 up */
{
    op->stats.wc = state;
    if (state) {
        use_trigger(op);
        if (op->stats.exp > 0) /* check sanity  */
            op->speed = 1.0 / op->stats.exp;
        else
            op->speed = 1.0;
        update_ob_speed(op);
        op->speed_left = -1;
    } else {
        use_trigger(op);
        op->speed = 0;
        update_ob_speed(op);
    }
}


/**
 * @todo document properly
 * cause != NULL: something has moved on top of op
 *
 * cause == NULL: nothing has moved, we have been called from
 * animate_trigger().
 *
 * TRIGGER_ALTAR: Returns 1 if 'cause' was destroyed, 0 if not.
 *
 * TRIGGER: Returns 1 if handle could be moved, 0 if not.
 *
 * TRIGGER_BUTTON, TRIGGER_PEDESTAL: Returns 0.
 */
int check_trigger (object *op, object *cause)
{
    object *tmp;
    int push = 0, tot = 0;
    int in_movement = op->stats.wc || op->speed;

    switch (op->type) {
        case TRIGGER_BUTTON:
            if (op->weight > 0) {
                if (cause) {
                    for (tmp = op->above; tmp; tmp = tmp->above)
                        /* Comment reproduced from update_buttons():
                         * Basically, if the move_type matches that on what the
                         * button wants, we count it.  The second check is so that
                         * objects that don't move (swords, etc) will count.  Note that
                         * this means that more work is needed to make buttons
                         * that are only triggered by flying objects.
                         */
                        if ((tmp->move_type & op->move_on) || tmp->move_type==0) {
                            tot += tmp->weight * (tmp->nrof ? tmp->nrof : 1)
                                 + tmp->carrying;
                        }
                        if (tot >= op->weight)
                            push = 1;
                        if (op->stats.ac == push)
                            return 0;
                        op->stats.ac = push;
                        if (NUM_ANIMATIONS(op)>1) {
                            SET_ANIMATION (op, push);
                            update_object (op, UP_OBJ_FACE);
                        }
                        if (in_movement || ! push)
                            return 0;
                }
                trigger_move (op, push);
            }
            return 0;

        case TRIGGER_PEDESTAL:
            if (cause) {
                for (tmp = op->above; tmp; tmp = tmp->above) {
                    object *head = tmp->head ? tmp->head : tmp;

                    /* See comment in TRIGGER_BUTTON about move_types */
                    if (((head->move_type & op->move_on) || head->move_type==0)
                        && (head->race==op->slaying ||
                        (!strcmp (op->slaying, "player") && head->type == PLAYER))) {
                        push = 1;
                        break;
                        }
                }
                if (op->stats.ac == push)
                    return 0;
                op->stats.ac = push;
                if (NUM_ANIMATIONS(op)>1) {
                    SET_ANIMATION (op, push);
                    update_object(op,UP_OBJ_FACE);
                }
                if (in_movement || ! push)
                    return 0;
            }
            trigger_move (op, push);
            return 0;

        case TRIGGER_ALTAR:
            if (cause) {
                if (in_movement)
                    return 0;
                if (operate_altar (op, &cause)) {
                    if (NUM_ANIMATIONS(op)>1) {
                        SET_ANIMATION (op, 1);
                        update_object(op,UP_OBJ_FACE);
                    }

                    if (op->last_sp >= 0) {
                        trigger_move (op, 1);
                        if (op->last_sp > 0)
                            op->last_sp = -op->last_sp;
                    }
                    else {
                        /* for trigger altar with last_sp, the ON/OFF
                         * status (-> +/- value) is "simulated": 
                         */
                        op->value = !op->value;
                        trigger_move (op, 1);
                        op->last_sp = -op->last_sp;
                        op->value = !op->value;
                    }
                    return cause == NULL;
                } else {
                    return 0;
                }
            } else {
                if (NUM_ANIMATIONS(op)>1) {
                    SET_ANIMATION (op, 0);
                    update_object(op,UP_OBJ_FACE);
                }

                /* If trigger_altar has "last_sp > 0" set on the map,
                 * it will push the connected value only once per sacrifice.
                 * Otherwise (default), the connected value will be
                 * pushed twice: First by sacrifice, second by reset! -AV 
                 */
                if (!op->last_sp)
                    trigger_move (op, 0);
                else {
                    op->stats.wc = 0;
                    op->value = !op->value;
                    op->speed = 0;
                    update_ob_speed(op);
                }
            }
            return 0;

        case TRIGGER:
            if (cause) {
                if (in_movement)
                    return 0;
                push = 1;
            }
            if (NUM_ANIMATIONS(op)>1) {
                SET_ANIMATION (op, push);
                update_object(op,UP_OBJ_FACE);
            }
            trigger_move (op, push);
            return 1;

        default:
            LOG(llevDebug, "Unknown trigger type: %s (%d)\n", op->name, op->type);
            return 0;
    }
}

/**
 * Links specified object in the map.
 * @param button
 * object to link. Must not be NULL.
 * @param map
 * map we are on. Should not be NULL.
 * @param connected
 * connection value for the item.
 */
void add_button_link(object *button, mapstruct *map, int connected) {
    oblinkpt *obp;
    objectlink *ol = get_objectlink();

    if (!map) {
        LOG(llevError, "Tried to add button-link without map.\n");
        free_objectlink(ol);
        return;
    }
    if (!editor) button->path_attuned = connected;  /* peterm:  I need this so I can rebuild 
        a connected map from a template map. */
/*  LOG(llevDebug,"adding button %s (%d)\n", button->name, connected);*/

    SET_FLAG(button,FLAG_IS_LINKED);

    ol->ob = button;
    ol->id = button->count;

    for (obp = map->buttons; obp && obp->value != connected; obp = obp->next);

    if (obp) {
        ol->next = obp->link;
        obp->link = ol;
    } else {
        obp = get_objectlinkpt();
        obp->value = connected;

        obp->next = map->buttons;
        map->buttons = obp;
        obp->link = ol;
    }
}

/**
 * Remove the object from the linked lists of buttons in the map.
 * This is only needed by editors.
 * @param op
 * object to remove. Must be on a map, and linked.
 */
void remove_button_link(object *op) {
    oblinkpt *obp;
    objectlink **olp, *ol;

    if (op->map == NULL) {
        LOG(llevError, "remove_button_link() in object without map.\n");
        return;
    }
    if (!QUERY_FLAG(op,FLAG_IS_LINKED)) {
        LOG(llevError, "remove_button_linked() in unlinked object.\n");
        return;
    }
    for (obp = op->map->buttons; obp; obp = obp->next)
        for (olp = &obp->link; (ol = *olp); olp = &ol->next)
            if (ol->ob == op) {
/*        LOG(llevDebug, "Removed link %d in button %s and map %s.\n",
           obp->value, op->name, op->map->path);
*/
                *olp = ol->next;
                free(ol);
                return;
            }
    LOG(llevError, "remove_button_linked(): couldn't find object.\n");
    CLEAR_FLAG(op,FLAG_IS_LINKED);
}

/**
 * Return the first objectlink in the objects linked to this one
 * @param button
 * object to check. Must not be NULL.
 * @return
 * ::objectlink for this object, or NULL.
 */
objectlink *get_button_links(const object *button) {
    oblinkpt *obp;
    objectlink *ol;

    if (!button->map)
        return NULL;
    for (obp = button->map->buttons; obp; obp = obp->next)
        for (ol = obp->link; ol; ol = ol->next)
            if (ol->ob == button && ol->id == button->count)
                return obp->link;
    return NULL;
}

/**
 * Returns the first value linked to this button.
 * Made as a separate function to increase efficiency
 * @param button
 * object to check. Must not be NULL.
 * @return
 * connection value, or 0 if not connected.
 */
int get_button_value(const object *button) {
    oblinkpt *obp;
    objectlink *ol;

    if (!button->map)
        return 0;
    for (obp = button->map->buttons; obp; obp = obp->next)
        for (ol = obp->link; ol; ol = ol->next)
            if (ol->ob == button && ol->id == button->count)
                return obp->value;
    return 0;
}

/** This routine makes monsters who are  
 * standing on the 'mood floor' change their
 * disposition if it is different.  
 * If floor is to be triggered must have
 * a speed of zero (default is 1 for all
 * but the charm floor type).
 * by b.t. thomas@nomad.astro.psu.edu
 * @param op
 * floor that activates
 * @param op2
 * ??
 * @todo document op2
 */
void do_mood_floor(object *op, object *op2) {
    object *tmp;
    object *tmp2;

    for (tmp = GET_MAP_OB(op->map, op->x, op->y); tmp; tmp=tmp->above)
        if (QUERY_FLAG(tmp, FLAG_MONSTER)) break;

    /* doesn't effect players, and if there is a player on this space, won't also
     * be a monster here.
     */
    if (!tmp || tmp->type == PLAYER) return;

    switch(op->last_sp) { 
        case 0:			/* furious--make all monsters mad */ 
            if(QUERY_FLAG(tmp, FLAG_UNAGGRESSIVE))
                CLEAR_FLAG(tmp, FLAG_UNAGGRESSIVE);
            if(QUERY_FLAG(tmp, FLAG_FRIENDLY)) { 
                CLEAR_FLAG(tmp, FLAG_FRIENDLY);
                remove_friendly_object(tmp);
                tmp->attack_movement = 0;
                /* lots of checks here, but want to make sure we don't
                 * dereference a null value
                 */
                if (tmp->type == GOLEM && tmp->owner && tmp->owner->type==PLAYER &&
                    tmp->owner->contr->ranges[range_golem]==tmp) {
                    tmp->owner->contr->ranges[range_golem]=NULL;
                    tmp->owner->contr->golem_count = 0;
                    }
                    tmp->owner = 0;
            }
            break;

        case 1: 			/* angry -- get neutral monsters mad */	 
            if(QUERY_FLAG(tmp, FLAG_UNAGGRESSIVE)&& 
               !QUERY_FLAG(tmp, FLAG_FRIENDLY))	
                CLEAR_FLAG(tmp, FLAG_UNAGGRESSIVE);
            break;

        case 2:			/* calm -- pacify unfriendly monsters */ 
            if(!QUERY_FLAG(tmp, FLAG_UNAGGRESSIVE)) {
                SET_FLAG(tmp, FLAG_UNAGGRESSIVE);
                tmp->enemy = NULL;
            }
            break;

        case 3:			/* make all monsters fall asleep */ 
            if(!QUERY_FLAG(tmp, FLAG_SLEEP))
                SET_FLAG(tmp, FLAG_SLEEP);
            break;

        case 4:			/* charm all monsters */
            if(op == op2) break; 	     /* only if 'connected' */ 

            for(tmp2=get_map_ob(op2->map,op2->x,op2->y); /* finding an owner */ 
            tmp2->type!=PLAYER;tmp2=tmp2->above)	
            if(tmp2->above==NULL) break;

            if (tmp2->type != PLAYER)
                break;
            set_owner(tmp,tmp2);
            SET_FLAG(tmp,FLAG_MONSTER);
            tmp->stats.exp = 0;
            SET_FLAG(tmp, FLAG_FRIENDLY);
            add_friendly_object (tmp);
            tmp->attack_movement = PETMOVE;
            break;

        default:
            break;
    }
}

/**
 * Checks object and its inventory for specific item.
 *
 * It will descend through containers to find the object.
 *		slaying = match object slaying flag
 * 		race = match object archetype name flag
 *		hp = match object type (excpt type '0'== PLAYER)

 * @param op
 * object of which to search inventory
 * @param trig
 * what to search
 * @return
 * object that matches, or NULL if none matched.
 */
object * check_inv_recursive(object *op, const object *trig)
{
    object *tmp,*ret=NULL;

    /* First check the object itself. */
    if((trig->stats.hp && (op->type == trig->stats.hp)) 
        || (trig->slaying && (op->slaying == trig->slaying)) 
        || (trig->race && (op->arch->name == trig->race))) 
        return op;

    for(tmp=op->inv; tmp; tmp=tmp->below) {
        if (tmp->inv) {
            ret=check_inv_recursive(tmp, trig);
            if (ret) return ret;
        }
        else if((trig->stats.hp && (tmp->type == trig->stats.hp)) 
            || (trig->slaying && (tmp->slaying == trig->slaying)) 
            || (trig->race && (tmp->arch->name == trig->race))) 
            return tmp;
    }
    return NULL;
}

/**
 * Function to search the inventory,
 * of a player and then based on a set of conditions,
 * the square will activate connected items. 
 *
 * Monsters can't trigger this square (for now)
 * Values are:	last_sp = 1/0 obj/no obj triggers 
 * 		last_heal = 1/0  remove/dont remove obj if triggered
 * -b.t. (thomas@nomad.astro.psu.edu 
 *
 * @param op
 * object to check. Must be a player.
 * @param trig
 * trigger object that may be activated.
 */
void check_inv (object *op, object *trig) {
    object *match;

    if(op->type != PLAYER) return;
    match = check_inv_recursive(op,trig);
    if (match && trig->last_sp) {
        if(trig->last_heal) 
            decrease_ob(match);
        use_trigger(trig);
    }
    else if (!match && !trig->last_sp)
        use_trigger(trig);
}

/**
 * This does a minimal check of the button link consistency for object
 * map.  All it really does it much sure the object id link that is set
 * matches what the object has.
 *
 * Will log to error level.
 *
 * @param map
 * map to check.
 */
void verify_button_links(const mapstruct *map) {
    oblinkpt *obp;
    objectlink *ol;

    if (!map) return;

    for (obp = map->buttons; obp; obp = obp->next) {
        for (ol=obp->link; ol; ol=ol->next) {
            if (ol->id!=ol->ob->count)
                LOG(llevError,"verify_button_links: object %s on list is corrupt (%d!=%d)\n",ol->ob->name, ol->id, ol->ob->count);
        }
    }
}
