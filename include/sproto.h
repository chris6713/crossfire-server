/*
 *   This file was automatically generated by version 1.7 of cextract.
 *   Manual editing not recommended.
 *
 *   Created: Tue Apr 25 23:45:32 2000
 */
#ifndef __CEXTRACT__
#ifdef __STDC__

extern char * cauldron_sound ( void );
extern void attempt_do_alchemy ( object *caster, object *cauldron );
extern int content_recipe_value ( object *op );
extern int numb_ob_inside ( object *op );
extern object * attempt_recipe ( object *caster, object *cauldron, int ability, recipe *rp, int nbatches );
extern void adjust_product ( object *item, int lvl, int yield );
extern object * make_item_from_recipe ( object *cauldron, recipe *rp );
extern object * find_transmution_ob ( object *first_ingred, recipe *rp );
extern void alchemy_failure_effect ( object *op, object *cauldron, recipe *rp, int danger );
extern void remove_contents ( object *first_ob, object *save_item );
extern int calc_alch_danger ( object *caster, object *cauldron );
extern void draw_find ( object *op, object *find );
extern int apply_potion ( object *op, object *tmp );
extern int check_item ( object *op, char *item );
extern void eat_item ( object *op, char *item );
extern int check_weapon_power ( object *who, int improvs );
extern int improve_weapon_stat ( object *op, object *improver, object *weapon, signed char *stat, int sacrifice_count, char *statname );
extern int prepare_weapon ( object *op, object *improver, object *weapon );
extern int improve_weapon ( object *op, object *improver, object *weapon );
extern int check_improve_weapon ( object *op, object *tmp );
extern int improve_armour ( object *op, object *improver, object *armour );
extern void money_change ( object *op, char *towhat );
extern int convert_item ( object *item, object *converter );
extern int apply_container ( object *op, object *sack );
extern int esrv_apply_container ( object *op, object *sack );
extern char *gravestone_text ( object *op );
extern int make_gravestone ( object *op, object *grave );
extern void move_apply ( object *trap, object *victim, object *originator );
extern int manual_apply ( object *op, object *tmp, int aflag );
extern int player_apply ( object *pl, object *op, int aflag, int quiet );
extern void player_apply_below ( object *pl );
extern int apply_special ( object *who, object *op, int aflags );
extern int monster_apply_special (object *who, object *op, int aflags);
extern int auto_apply ( object *op );
extern void fix_auto_apply ( mapstruct *m );
extern void eat_special_food ( object *who, object *food );
extern void apply_lighter ( object *who, object *lighter );
extern void scroll_failure ( object *op, int failure, int power );
extern int did_make_save_item ( object *op, int type );
extern void save_throw_object ( object *op, int type );
extern int hit_map ( object *op, int dir, int type );
extern int attack_ob ( object *op, object *hitter );
extern void tear_down_wall ( object *op );
extern int hit_player_attacktype ( object *op, object *hitter, int dam, uint32 attacktype, int magic );
extern int hit_player ( object *op, int dam, object *hitter, int type );
extern void poison_player ( object *op, object *hitter, int dam );
extern void slow_player ( object *op, object *hitter, int dam );
extern void confuse_player ( object *op, object *hitter, int dam );
extern void blind_player ( object *op, object *hitter, int dam );
extern void paralyze_player ( object *op, object *hitter, int dam );
extern void deathstrike_player ( object *op, object *hitter, int *dam );
extern object *thrown_item_effect ( object *hitter, object *victim );
extern int adj_attackroll ( object *hitter, object *target );
extern int is_aimed_missile ( object *op );
extern int checkbanned ( char *login, char *host );
extern int command_say ( object *op, char *params );
extern int command_last ( object *op, char *params );
extern void map_info ( object *op );
extern int command_spell_reset ( object *op, char *params );
extern int command_motd ( object *op, char *params );
extern int command_bug ( object *op, char *params );
extern void malloc_info ( object *op );
extern int count_pending ( mapstruct *map );
extern void current_map_info ( object *op );
extern int command_who ( object *op, char *params );
extern int command_malloc ( object *op, char *params );
extern int command_mapinfo ( object *op, char *params );
extern int command_maps ( object *op, char *params );
extern int command_strings ( object *op, char *params );
extern int command_sstable ( object *op, char *params );
extern int command_time ( object *op, char *params );
extern int command_archs ( object *op, char *params );
extern int command_hiscore ( object *op, char *params );
extern int command_debug ( object *op, char *params );
extern int command_dumpbelow ( object *op, char *params );
extern int command_wizpass ( object *op, char *params );
extern int command_dumpallobjects ( object *op, char *params );
extern int command_dumpfriendlyobjects ( object *op, char *params );
extern int command_dumplights ( object *op, char *params );
extern int command_dumpallarchetypes ( object *op, char *params );
extern int command_ssdumptable ( object *op, char *params );
extern int command_dumpmap ( object *op, char *params );
extern int command_dumpallmaps ( object *op, char *params );
extern int command_printlos ( object *op, char *params );
extern int command_version ( object *op, char *params );
extern void bug_report ( char * reportstring );
extern int command_output_sync ( object *op, char *params );
extern int command_output_count ( object *op, char *params );
extern int command_listen ( object *op, char *params );
extern int command_statistics ( object *pl, char *params );
extern int command_fix_me ( object *op, char *params );
extern int command_players ( object *op, char *paramss );
extern int command_logs ( object *op, char *params );
extern int command_usekeys ( object *op, char *params );
extern int command_east ( object *op, char *params );
extern int command_north ( object *op, char *params );
extern int command_northeast ( object *op, char *params );
extern int command_northwest ( object *op, char *params );
extern int command_south ( object *op, char *params );
extern int command_southeast ( object *op, char *params );
extern int command_southwest ( object *op, char *params );
extern int command_west ( object *op, char *params );
extern int command_stay ( object *op, char *params );
extern int command_search ( object *op, char *params );
extern int command_disarm ( object *op, char *params );
extern int execute_newserver_command ( object *pl, char *command );
extern int command_run ( object *op, char *params );
extern int command_run_stop ( object *op, char *params );
extern int command_fire ( object *op, char *params );
extern int command_fire_stop ( object *op, char *params );
extern int bad_command ( object *op, char *params );
extern int dump_object_from_tag ( object *pl, char *val );
extern int item_matched_string ( object *pl, object *op, char *name );
extern object *find_best_object_match ( object *pl, char *params );
extern int command_uskill ( object *pl, char *params );
extern int command_rskill ( object *pl, char *params );
extern int command_apply ( object *op, char *params );
extern int sack_can_hold ( object *pl, object *sack, object *op, int nrof );
extern void pick_up_object ( object *pl, object *op, object *tmp, int nrof );
extern void pick_up ( object *op, object *alt );
extern int command_take ( object *op, char *params );
extern void put_object_in_sack ( object *op, object *sack, object *tmp, long nrof );
extern void drop_object ( object *op, object *tmp, long nrof );
extern void drop ( object *op, object *tmp );
extern int command_dropall ( object *op, char *params );
extern int command_drop ( object *op, char *params );
extern int command_examine ( object *op, char *params );
extern object *find_marked_object ( object *op );
extern int command_mark ( object *op, char *params );
extern partylist * form_party ( object *op, char *params, partylist * firstparty, partylist * lastparty );
extern char * find_party ( int partynumber, partylist * party );
extern partylist *find_party_struct ( int partynumber );
extern int confirm_party_password ( object *op );
extern void receive_party_password ( object *op, char k );
extern void send_party_message ( object *op, char *msg );
extern int command_gsay ( object *op, char *params );
extern int command_party ( object *op, char *params );
extern int command_setgod ( object *op, char *params );
extern int command_kick ( object *op, char *params );
extern int command_shutdown ( object *op, char *params );
extern int command_goto ( object *op, char *params );
extern int command_generate ( object *op, char *params );
extern int command_summon ( object *op, char *params );
extern int command_create ( object *op, char *params );
extern int command_inventory ( object *op, char *params );
extern int command_skills ( object *op, char *params );
extern int command_dump ( object *op, char *params );
extern int command_patch ( object *op, char *params );
extern int command_remove ( object *op, char *params );
extern int command_free ( object *op, char *params );
extern int command_addexp ( object *op, char *params );
extern int command_speed ( object *op, char *params );
extern int command_stats ( object *op, char *params );
extern int command_abil ( object *op, char *params );
extern int command_reset ( object *op, char *params );
extern int command_nowiz ( object *op, char *params );
extern int command_dm ( object *op, char *params );
extern void init_commands ( void );
extern CommFunc find_oldsocket_command ( char *cmd );
extern CommFunc find_oldsocket_command2 ( char *cmd );
extern int parse_string ( object *op, char *str );
extern int parse_command ( object *op, char *str );
extern FILE *BecomeDaemon ( char *filename );
extern int move_disease ( object *disease );
extern int remove_symptoms ( object *disease );
extern object * find_symptom ( object *disease );
extern int check_infection ( object *disease );
extern int infect_object ( object *victim, object *disease );
extern int do_symptoms ( object *disease );
extern int grant_immunity ( object *disease );
extern int move_symptom ( object *symptom );
extern int check_physically_infect ( object *victim, object *hitter );
extern object *find_disease ( object *victim );
extern int cure_disease ( object *sufferer, object *caster );
extern int reduce_symptoms ( object *sufferer, int reduction );
extern int apply_power_crystal ( object *op, object *crystal );
extern char *spool ( char *bp, char *error );
extern void check_score ( object *op );
extern void display_high_score ( object *op, int max, char *match );
extern int lookup_god_by_name ( char *name );
extern object *find_god ( char *name );
extern void pray_at_altar ( object *pl, object *altar );
extern void become_follower ( object *op, object *new_god );
extern int worship_forbids_use ( object *op, object *exp_obj, uint32 flag, char *string );
extern void stop_using_item ( object *op, int type, int number );
extern void update_priest_flag ( object *god, object *exp_ob, uint32 flag );
extern char *determine_god ( object *op );
extern void god_intervention ( object *op, object *god );
extern int god_examines_priest ( object *op, object *god );
extern int god_examines_item ( object *god, object *item );
extern int get_god ( object *priest );
extern int tailor_god_spell ( object *spellop, object *caster );
extern void lose_priest_exp ( object *pl, int loss );
extern void set_logfile ( char *val );
extern void call_version ( void );
extern void showscores ( void );
extern void set_debug ( void );
extern void unset_debug ( void );
extern void set_mondebug ( void );
extern void set_dumpmon1 ( void );
extern void set_dumpmon2 ( void );
extern void set_dumpmon3 ( void );
extern void set_dumpmon4 ( void );
extern void set_dumpmon5 ( void );
extern void set_dumpmon6 ( void );
extern void set_dumpmon7 ( void );
extern void set_dumpmon8 ( void );
extern void set_dumpmon9 ( void );
extern void set_dumpmont ( char *name );
extern void set_daemon ( void );
extern void set_datadir ( char *path );
extern void set_localdir ( char *path );
extern void set_mapdir ( char *path );
extern void set_archetypes ( char *path );
extern void set_treasures ( char *path );
extern void set_uniquedir ( char *path );
extern void set_playerdir ( char *path );
extern void set_tmpdir ( char *path );
extern void showscoresparm ( char *data );
extern void set_csport ( char *val );
extern void init ( int argc, char **argv );
extern void usage ( void );
extern void help ( void );
extern void init_beforeplay ( void );
extern void init_startup ( void );
extern void compile_info ( void );
extern void rec_sigsegv ( int i );
extern void rec_sigint ( int i );
extern void rec_sighup ( int i );
extern void rec_sigquit ( int i );
extern void rec_sigpipe ( int i );
extern void rec_sigbus ( int i );
extern void rec_sigterm ( int i );
extern void fatal_signal ( int make_core, int close_sockets );
extern void init_signals ( void );
extern void setup_library ( void );
extern void init_races ( void );
extern void dump_races ( void );
extern void add_to_racelist ( char *race_name, object *op );
extern racelink * get_racelist ( void );
extern racelink * find_racelink ( char *name );
extern int onoff_value ( char *line );
extern object **find_objects ( object *op, char *line, int flags );
extern void drop_inventory ( object *op );
extern void examine_monster ( object *op, object *tmp );
extern char *long_desc ( object *tmp );
extern void examine ( object *op, object *tmp );
extern void inventory ( object *op, object *inv );
extern void receive_player_name ( object *op, char k );
extern void receive_player_password ( object *op, char k );
extern void set_pickup_mode ( object *op, int i );
extern int explore_mode ( void );
extern int command_help ( object *op, char *params );
extern int command_invoke ( object *op, char *params );
extern int command_cast ( object *op, char *params );
extern int command_prepare ( object *op, char *params );
extern int command_cast_spell ( object *op, char *params, char command );
extern int command_title ( object *op, char *params );
extern int command_save ( object *op, char *params );
extern int command_search_items ( object *op, char *params );
extern int command_peaceful ( object *op, char *params );
extern int command_strength ( object *op, char *params );
extern int command_pickup ( object *op, char *params );
extern int command_wimpy ( object *op, char *params );
extern int command_quit ( object *op, char *params );
extern int command_sound ( object *op, char *params );
extern int command_shout ( object *op, char *params );
extern int command_tell ( object *op, char *params );
extern int command_bell ( object *op, char *params );
extern int legal_range ( object *op, int r );
extern void change_spell ( object *op, char k );
extern int command_invisible ( object *op, char *params );
extern int command_rotateshoottype ( object *op, char *params );
extern int command_throw ( object *op, char *params );
extern int command_brace ( object *op, char *params );
extern int command_rotatespells ( object *op, char *params );
extern void emergency_save ( int flag );
extern void delete_character ( char *name, int new );
extern void unlock_player ( char *name );
extern int verify_player ( char *name, char *password );
extern int check_name ( player *me, char *name );
extern int create_savedir_if_needed ( char *savedir );
extern void destroy_object ( object *op );
extern int save_player ( object *op, int flag );
extern long calculate_checksum ( char *filename, int checkdouble );
extern void copy_file ( char *filename, FILE *fpout );
extern void check_login ( object *op );
extern void version ( object *op );
extern void info_keys ( object *op );
extern void start_info ( object *op );
extern char *crypt_string ( char *str, char *salt );
extern int check_password ( char *typed, char *crypted );
extern char *normalize_path ( char *src, char *dst );
extern void enter_exit ( object *op, object *exit_ob );
extern void enter_map ( object *op );
extern void process_active_maps ( void );
extern void process_players1 ( mapstruct *map );
extern void process_players2 ( mapstruct *map );
extern void process_events ( mapstruct *map );
extern void clean_tmp_files ( void );
extern void cleanup ( void );
extern void leave ( player *pl );
extern int forbid_play ( void );
extern void do_specials ( void );
extern int main ( int argc, char **argv );
extern object *get_enemy ( object *npc );
extern object *find_enemy ( object *npc );
extern int check_wakeup ( object *op, object *enemy );
extern int move_randomly ( object *op );
extern int move_monster ( object *op );
extern int can_hit ( object *ob1, object *ob2 );
extern int can_apply ( object *who, object *item );
extern object *monster_choose_random_spell ( object *monster );
extern int monster_cast_spell ( object *head, object *part, object *pl, int dir );
extern int monster_use_skill ( object *head, object *part, object *pl, int dir );
extern int monster_use_wand ( object *head, object *part, object *pl, int dir );
extern int monster_use_rod ( object *head, object *part, object *pl, int dir );
extern int monster_use_horn ( object *head, object *part, object *pl, int dir );
extern int monster_use_bow ( object *head, object *part, object *pl, int dir );
extern int check_good_weapon ( object *who, object *item );
extern int check_good_armour ( object *who, object *item );
extern void monster_check_pickup ( object *monster );
extern int monster_can_pick ( object *monster, object *item );
extern void monster_apply_below ( object *monster );
extern void monster_check_apply ( object *mon, object *item );
extern void npc_call_help ( object *op );
extern int dist_att ( int dir, object *ob, object *enemy, object *part );
extern int run_att ( int dir, object *ob, object *enemy, object *part );
extern int hitrun_att ( int dir, object *ob, object *enemy );
extern int wait_att ( int dir, object *ob, object *enemy, object *part );
extern int disthit_att ( int dir, object *ob, object *enemy, object *part );
extern int wait_att2 ( int dir, object *ob, object *enemy, object *part );
extern void circ1_move ( object *ob );
extern void circ2_move ( object *ob );
extern void pace_movev ( object *ob );
extern void pace_moveh ( object *ob );
extern void pace2_movev ( object *ob );
extern void pace2_moveh ( object *ob );
extern void rand_move ( object *ob );
extern void check_earthwalls ( object *op, int x, int y );
extern void check_doors ( object *op, int x, int y );
extern int move_object ( object *op, int dir );
extern void communicate ( object *op, char *txt );
extern int talk_to_npc ( object *npc, char *txt );
extern int talk_to_wall ( object *npc, char *txt );
extern object *find_mon_throw_ob ( object *op );
extern int can_detect_enemy ( object *op, object *enemy );
extern int stand_in_light ( object *op );
extern int can_see_enemy ( object *op, object *enemy );
extern int move_ob ( object *op, int dir, object *originator );
extern int transfer_ob ( object *op, int x, int y, int randomly, object *originator );
extern int teleport ( object *teleporter, unsigned char tele_type, object *originator );
extern void recursive_roll ( object *op, int dir, object *pusher );
extern int try_fit ( object *op, int x, int y );
extern int roll_ob ( object *op, int dir, object *pusher );
extern int push_ob ( object *who, int dir, object *pusher );
extern void add_pending_object ( object *ob, mapstruct *map );
extern void enter_pending_objects ( mapstruct *map );
extern object *get_pet_enemy ( object * pet );
extern void terminate_all_pets ( object *owner );
extern void remove_all_pets ( mapstruct *map );
extern void follow_owner ( object *ob, object *owner );
extern void pet_move ( object * ob );
extern void display_motd ( object *op );
extern int playername_ok ( char *cp );
extern int add_player ( NewSocket *ns );
extern archetype *get_player_archetype ( archetype* at );
extern object *get_player ( player *p, mapstruct *m );
extern object *get_nearest_player ( object *mon );
extern int path_to_player ( object *mon, object *pl, int mindiff );
extern void give_initial_items ( object *pl );
extern void get_name ( object *op );
extern void get_password ( object *op );
extern void play_again ( object *op );
extern int receive_play_again ( object *op, char key );
extern void confirm_password ( object *op );
extern void get_party_password ( object *op, int partyid );
extern int roll_stat ( void );
extern void roll_stats ( object *op );
extern void Roll_Again ( object *op );
extern void Swap_Stat ( object *op, int Swap_Second );
extern int key_roll_stat ( object *op, char key );
extern int key_change_class ( object *op, char key );
extern int key_confirm_quit ( object *op, char key );
extern void flee_player ( object *op );
extern int check_pick ( object *op );
extern object *find_arrow ( object *op, char *type );
extern void fire ( object *op, int dir );
extern object * find_key ( object *pl, object *container, object *door );
extern void move_player_attack ( object *op, int dir );
extern int move_player ( object *op, int dir );
extern int handle_newcs_player ( object *op );
extern int save_life ( object *op );
extern void remove_unpaid_objects ( object *op, object *env );
extern void do_some_living ( object *op );
extern void kill_player ( object *op );
extern void loot_object ( object *op );
extern void fix_weight ( void );
extern void fix_luck ( void );
extern void cast_dust ( object *op, object *throw_ob, int dir );
extern void make_visible ( object *op );
extern int is_true_undead ( object *op );
extern int hideability ( object *ob );
extern void do_hidden_move ( object *op );
extern int stand_near_hostile ( object *who );
extern int player_can_view ( object *pl, object *op );
extern int action_makes_visible ( object *op );
extern void dead_player ( object *op );
extern int cast_raise_dead_spell ( object *op, int dir, int spell_type, object * corpseobj );
extern int resurrection_fails ( int levelcaster, int leveldead );
extern int resurrect_player ( object *op, char *playername, int rspell );
extern void dead_character ( char *name );
extern int dead_player_exists ( char *name );
extern int write_rune ( object *op, int dir, int inspell, int level, char *runename );
extern void move_rune ( object *op );
extern void rune_attack ( object *op, object *victim );
extern void spring_trap ( object *trap, object *victim );
extern int dispel_rune ( object *op, int dir, int risk );
extern int trap_see ( object *op, object *trap );
extern int trap_show ( object *trap, object *where );
extern int trap_disarm ( object *disarmer, object *trap, int risk );
extern void trap_adjust ( object *trap, int difficulty );
extern int query_cost ( object *tmp, object *who, int flag );
extern char *cost_string_from_value ( int cost );
extern char *query_cost_string ( object *tmp, object *who, int flag );
extern int query_money ( object *op );
extern int pay_for_item ( object *op, object *pl );
extern int pay_from_container ( object *op, object *pouch, int to_pay );
extern int get_payment2 ( object *pl, object *op );
extern int get_payment ( object *pl );
extern void sell_item ( object *op, object *pl );
extern void shop_listing ( object *op );
extern int attempt_steal ( object* op, object* who );
extern int adj_stealchance ( object *op, object *victim, int roll );
extern int steal ( object* op, int dir );
extern int pick_lock ( object *pl, int dir );
extern int attempt_pick_lock ( object *door, object *pl );
extern int hide ( object *op );
extern int attempt_hide ( object *op );
extern int jump ( object *pl, int dir );
extern int skill_ident ( object *pl );
extern int do_skill_detect_curse ( object *pl );
extern int do_skill_detect_magic ( object *pl );
extern int do_skill_ident2 ( object *tmp, object *pl, int obj_class );
extern int do_skill_ident ( object *pl, int obj_class );
extern int use_oratory ( object *pl, int dir );
extern int singing ( object *pl, int dir );
extern int find_traps ( object *pl );
extern int pray ( object *pl );
extern void meditate ( object *pl );
extern int write_on_item ( object *pl, char *params );
extern int write_note ( object *pl, object *item, char *msg );
extern int write_scroll ( object *pl, object *scroll );
extern int remove_trap ( object *op, int dir );
extern int skill_throw ( object *op, int dir, char *params );
extern object *find_throw_ob ( object *op, char *request );
extern object *make_throw_ob ( object *orig );
extern void do_throw ( object *op, object *toss_item, int dir );
extern int do_skill ( object *op, int dir, char *string );
extern int calc_skill_exp ( object *who, object *op );
extern float calc_stat_mult ( object *who, int sk );
extern int get_weighted_skill_stat_sum ( object *who, int sk );
extern void init_new_exp_system ( void );
extern void dump_skills ( void );
extern void init_exp_obj ( void );
extern void link_skills_to_exp ( void );
extern int check_link ( int stat, object *exp );
extern void read_skill_params ( void );
extern int lookup_skill_by_name ( char *string );
extern int check_skill_to_fire ( object *who );
extern int check_skill_to_apply ( object *who, object *item );
extern int init_player_exp ( object *pl );
extern void unlink_skill ( object *skillop );
extern int remove_skill_from_list ( object *op, object *skillop );
extern int link_player_skills ( object *pl );
extern int link_player_skill ( object *pl, object *skillop );
extern int learn_skill ( object *pl, object *scroll );
extern void show_skills ( object *op );
extern int use_skill ( object *op, char *string );
extern int change_skill ( object *pl, int sk_index );
extern int attack_melee_weapon ( object *op, int dir, char *string );
extern int attack_hth ( object *pl, int dir, char *string );
extern int skill_attack ( object *tmp, object *pl, int dir, char *string );
extern int do_skill_attack ( object *tmp, object *op, char *string );
extern int hth_damage ( object *target, object *pl );
extern int SK_level ( object *op );
extern float get_skill_time ( object *op, int skillnr );
extern int get_skill_stat1 ( object *op );
extern int get_skill_stat2 ( object *op );
extern int get_skill_stat3 ( object *op );
extern int get_weighted_skill_stats ( object *op );
extern void prayer_failure ( object *op, int failure, int power );
extern void cast_mana_storm ( object *op, int lvl );
extern void cast_magic_storm ( object *op, object *tmp, int lvl );
extern void aggravate_monsters ( object *op );
extern int recharge ( object *op );
extern void polymorph_living ( object *op );
extern void polymorph_melt ( object *who, object *op );
extern void polymorph_item ( object *who, object *op );
extern void polymorph ( object *op, object *who );
extern int cast_polymorph ( object *op, int dir );
extern int cast_create_food ( object *op, object *caster, int dir, char *stringarg );
extern int cast_speedball ( object *op, int dir, int type );
extern int probe ( object *op, int dir );
extern int cast_invisible ( object *op, object *caster, int spell_type );
extern int cast_earth2dust ( object *op, object *caster );
extern int cast_wor ( object *op, object *caster );
extern int cast_wow ( object *op, int dir, int ability, SpellTypeFrom item );
extern int perceive_self ( object *op );
extern int cast_destruction ( object *op, object *caster, int dam, int attacktype );
extern int magic_wall ( object *op, object *caster, int dir, int spell_type );
extern int cast_light ( object *op, object *caster, int dir );
extern int dimension_door ( object *op, int dir );
extern int cast_heal ( object *op, int dir, int spell_type );
extern int cast_regenerate_spellpoints ( object *op );
extern int cast_change_attr ( object *op, object *caster, int dir, int spell_type );
extern int summon_pet ( object *op, int dir, SpellTypeFrom item );
extern int create_bomb ( object *op, object *caster, int dir, int spell_type, char *name );
extern void animate_bomb ( object *op );
extern int fire_cancellation ( object *op, int dir, archetype *at, int magic );
extern void move_cancellation ( object *op );
extern void cancellation ( object *op );
extern int cast_create_missile ( object *op, object *caster, int dir, char *stringarg );
extern int alchemy ( object *op );
extern int remove_curse ( object *op, int type, SpellTypeFrom src );
extern int cast_identify ( object *op );
extern int cast_detection ( object *op, int type );
extern int cast_pacify ( object *op, object *weap, archetype *arch, int spellnum );
extern int summon_fog ( object *op, object *caster, int dir, int spellnum );
extern int create_the_feature ( object *op, object *caster, int dir, int spell_effect );
extern int cast_transfer ( object *op, int dir );
extern int drain_magic ( object *op, int dir );
extern void counterspell ( object *op );
extern int summon_hostile_monsters ( object *op, int n, char *monstername );
extern int cast_charm ( object *op, object *caster, archetype *arch, int spellnum );
extern int cast_charm_undead ( object *op, object *caster, archetype *arch, int spellnum );
extern object *choose_cult_monster ( object *pl, object *god, int summon_level );
extern int summon_cult_monsters ( object *op, int old_dir );
extern int summon_avatar ( object *op, object *caster, int dir, archetype *at, int spellnum );
extern object *fix_summon_pet ( archetype *at, object *op, int dir, int type );
extern int cast_consecrate ( object *op );
extern int finger_of_death ( object *op, object *caster, int dir );
extern int animate_weapon ( object *op, object *caster, int dir, archetype *at, int spellnum );
extern int cast_daylight ( object *op );
extern int cast_nightfall ( object *op );
extern int cast_faery_fire ( object *op, object *caster );
extern int make_object_glow ( object *op, int radius, int time );
extern int cast_cause_disease ( object *op, object *caster, int dir, archetype *disease_arch, int type );
extern void init_spells ( void );
extern void dump_spells ( void );
extern void spell_effect ( int spell_type, int x, int y, mapstruct *map, object *originator );
extern spell *find_spell ( int spelltype );
extern int path_level_mod ( object *caster, int base_level, int spell_type );
extern int casting_level ( object *caster, int spell_type );
extern int check_spell_known ( object *op, int spell_type );
extern int cast_spell ( object *op, object *caster, int dir, int type, int ability, SpellTypeFrom item, char *stringarg );
extern int cast_create_obj ( object *op, object *caster, object *new_op, int dir );
extern int summon_monster ( object *op, object *caster, int dir, archetype *at, int spellnum );
extern int fire_bolt ( object *op, object *caster, int dir, int type, int magic );
extern int fire_arch ( object *op, object *caster, int dir, archetype *at, int type, int magic );
extern int fire_arch_from_position ( object *op, object *caster, sint16 x, sint16 y, int dir, archetype *at, int type, int magic );
extern int cast_cone ( object *op, object *caster, int dir, int strength, int spell_type, archetype *spell_arch, int magic );
extern void move_cone ( object *op );
extern void fire_a_ball ( object *op, int dir, int strength );
extern void explosion ( object *op );
extern int reflwall ( mapstruct *m, int x, int y );
extern void move_bolt ( object *op );
extern void move_golem ( object *op );
extern void control_golem ( object *op, int dir );
extern void move_missile ( object *op );
extern int explode_object ( object *op );
extern void check_fired_arch ( object *op );
extern void move_fired_arch ( object *op );
extern void drain_rod_charge ( object *rod );
extern void fix_rod_speed ( object *rod );
extern object *find_target_for_friendly_spell ( object *op, int dir );
extern void move_ball_lightning ( object *op );
extern int spell_find_dir ( mapstruct *m, int x, int y, object *exclude );
extern int SP_level_dam_adjust ( object *op, object *caster, int spell_type );
extern int SP_level_strength_adjust ( object *op, object *caster, int spell_type );
extern int SP_level_spellpoint_cost ( object *op, object *caster, int spell_type );
extern void move_swarm_spell ( object *op );
extern void fire_swarm ( object *op, object *caster, int dir, archetype *swarm_type, int spell_type, int n, int magic );
extern int look_up_spell_by_name ( object *op, char *spname );
extern void put_a_monster ( object *op, char *monstername );
extern void shuffle_attack ( object *op, int change_face );
extern void init_spell_param ( void );
extern object *get_pointed_target ( object *op, int dir );
extern int cast_smite_spell ( object *op, object *caster, int dir, int type );
extern void walk_on_deep_swamp ( object *op, object *victim );
extern void move_deep_swamp ( object *op );
extern void read_map_log ( void );
extern void swap_map ( mapstruct *map );
extern void check_active_maps ( void );
extern mapstruct *map_least_timeout ( char *except_level );
extern void swap_below_max ( char *except_level );
extern int players_on_map ( mapstruct *m );
extern void flush_old_maps ( void );
extern void remove_door ( object *op );
extern void remove_door2 ( object *op );
extern void generate_monster ( object *gen );
extern void regenerate_rod ( object *rod );
extern void remove_force ( object *op );
extern void remove_blindness ( object *op );
extern void remove_confusion ( object *op );
extern void execute_wor ( object *op );
extern void poison_more ( object *op );
extern void move_gate ( object *op );
extern void move_timed_gate ( object *op );
extern void move_detector ( object *op );
extern void animate_trigger ( object *op );
extern void move_hole ( object *op );
extern void stop_arrow ( object *op, object *tmp );
extern void move_arrow ( object *op );
extern void change_object ( object *op );
extern void move_teleporter ( object *op );
extern void move_firewall ( object *op );
extern void move_firechest ( object *op );
extern void move_player_mover ( object *op );
extern void move_creator ( object *op );
extern void move_marker ( object *op );
extern int process_object ( object *op );

#endif /* __STDC__ */
#endif /* __CEXTRACT__ */
