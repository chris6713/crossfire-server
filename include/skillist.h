

/* This is the order of the skills structure:
 *  char *name;
 *  short category;  - the associated experience category
 *  short time;      - the base number of ticks it takes to execute skill
 *  long  bexp;      - base exp gain for use of this skill
 *  float lexp;      - level multiplier for experience gain
 *  short stat1;     - primary stat, for linking to exp cat.
 *  short stat2;     - secondary stat ...
 *  short stat3;     - tertiary stat ...
 *
 * About time - this  number is the base for the use of the skill. Level
 * and associated stats can modify the amound of time to use the skill.
 * Time to use the skill is only used when 1) op is a player and 
 * 2) the skill is called through do_skill(). 
 * It is strongly recogmended that many skills *not* have a time value.
 *
 * About 'stats' and skill.category - a primary use for stats is determining
 * the associated experience category (see link_skills_to_exp () ). 
 * Note that the ordering of the stats is important. Stat1 is the 'primary' 
 * stat, stat2 the 'secondary' stat, etc. In this scheme the primary stat 
 * is most important for determining the associated experience category. 
 * If a skill has the primary stat set to NO_STAT_VAL then it defaults to a 
 * 'miscellaneous skill'. 
 */
 
/* Don't change the order here w/o changing the skills.h file */

/* The default skills array, values can be overwritten by init_skills() 
 * in skill_util.c 
 */

skill skills[] = {
/* 0 */
    { "stealing",       EXP_NONE, 0, 0, 0.1,      DEX,     INT, NO_STAT_VAL },
    { "lockpicking",    EXP_NONE, 0, 50, 1.5,   DEX,     INT, NO_STAT_VAL },
    { "hiding",         EXP_NONE, 0, 10, 2.5,   DEX,     CHA, NO_STAT_VAL },
    { "smithery",       EXP_NONE, 10, 1, 1,     INT, 	 STR, NO_STAT_VAL },
    { "bowyer",         EXP_NONE, 10, 1, 1,     INT,     DEX, NO_STAT_VAL },
/* 5 */
    { "jeweler",        EXP_NONE, 10, 1, 1, 	INT, 	 DEX, 	  WIS },
    { "alchemy",        EXP_NONE, 10, 1, 1, 	INT, 	 WIS, 	  DEX },
    { "thaumaturgy",    EXP_NONE, 10, 1, 1, 	INT, 	 POW,     WIS },
    { "literacy",       EXP_NONE, 10, 1, 1, 	INT, 	 WIS, NO_STAT_VAL },
    { "bargaining",     EXP_NONE, 0, 0, 0,  NO_STAT_VAL, NO_STAT_VAL, NO_STAT_VAL },
/* 10 */
    { "jumping",        EXP_NONE, 0, 5, 2.5,      STR,     DEX, NO_STAT_VAL },
    { "sense magic",    EXP_NONE, 10, 10, 1, 	POW, 	 INT, NO_STAT_VAL },
    { "oratory",        EXP_NONE, 5, 1, 2,      CHA,     INT, NO_STAT_VAL },
    { "singing",        EXP_NONE, 5, 1, 2,      CHA,     INT, NO_STAT_VAL },
    { "sense curse",    EXP_NONE, 10, 10, 1, 	WIS,     POW, NO_STAT_VAL },
/* 15 */
    { "find traps",     EXP_NONE, 0, 0, 0,  NO_STAT_VAL, NO_STAT_VAL, NO_STAT_VAL },
    { "meditation",     EXP_NONE, 10, 0, 0, NO_STAT_VAL, NO_STAT_VAL, NO_STAT_VAL },
    { "punching",       EXP_NONE, 0, 0, 1,      STR,      DEX, NO_STAT_VAL },
    { "flame touch", 	EXP_NONE, 0, 0, 1,      STR,      DEX,     INT }, 
    { "karate",         EXP_NONE, 0, 0, 1,      STR,      DEX, NO_STAT_VAL },
/* 20 */
    { "mountaineer",    EXP_NONE, 0, 0, 0,  NO_STAT_VAL, NO_STAT_VAL, NO_STAT_VAL },
    { "woodsman",       EXP_NONE, 0, 1, 1,  	INT, 	  DEX, NO_STAT_VAL },
    { "inscription",    EXP_NONE, 0, 1, 5,      POW,      INT,  NO_STAT_VAL },
    { "melee weapons",  EXP_NONE, 0, 0, 1,      STR,      DEX, NO_STAT_VAL },
    { "missile weapons", EXP_NONE, 0, 0, 1,     STR,      DEX, NO_STAT_VAL },
/* 25 */
    { "throwing",       EXP_NONE, 0, 0, 1,      STR,      DEX, NO_STAT_VAL },
    { "wizardry",	EXP_NONE, 0, 0, 0,      POW,      INT, 	   WIS },
    { "disarm traps",   EXP_NONE, 0, 1, 0.5,    DEX,      INT, NO_STAT_VAL },
    { "set traps",      EXP_NONE, 0, 1, 0.5,    INT,      DEX, NO_STAT_VAL }, 
    { "use magic item", EXP_NONE, 0, 0, 0,   NO_STAT_VAL, NO_STAT_VAL, NO_STAT_VAL }, 
/* 30 */
    { "praying", 	EXP_NONE, 0, 0, 0,      WIS,      POW,     INT }, 
    { "clawing", 	EXP_NONE, 0, 0, 0,      STR,      DEX, NO_STAT_VAL },
    { "levitation",	EXP_NONE, 0, 0, 0, NO_STAT_VAL, NO_STAT_VAL, NO_STAT_VAL }
};



