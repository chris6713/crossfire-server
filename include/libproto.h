/* anim.c */
extern void free_all_anim(void);
extern void init_anim(void);
extern int find_animation(const char *name);
extern void animate_object(object *op, int dir);
/* arch.c */
extern archetype *find_archetype_by_object_name(const char *name);
extern archetype *find_archetype_by_object_type_name(int type, const char *name);
extern archetype *get_archetype_by_skill_name(const char *skill, int type);
extern archetype *get_archetype_by_type_subtype(int type, int subtype);
extern object *create_archetype_by_object_name(const char *name);
extern void init_archetypes(void);
extern void arch_info(object *op);
extern void clear_archetable(void);
extern void init_archetable(void);
extern void dump_arch(archetype *at);
extern void dump_all_archetypes(void);
extern void free_arch(archetype *at);
extern void free_all_archs(void);
extern archetype *get_archetype_struct(void);
extern void check_generators(void);
extern object *arch_to_object(archetype *at);
extern object *create_singularity(const char *name);
extern object *create_archetype(const char *name);
extern unsigned long hasharch(const char *str, int tablesize);
extern archetype *find_archetype(const char *name);
extern archetype *type_to_archetype(int type);
extern object *object_create_arch(archetype *at);
/* button.c */
extern void push_button(object *op);
extern void update_button(object *op);
extern void update_buttons(mapstruct *m);
extern void use_trigger(object *op);
extern void animate_turning(object *op);
extern int check_altar_sacrifice(const object *altar, const object *sacrifice, int remove_others, int *toremove);
extern int operate_altar(object *altar, object **sacrifice);
extern void trigger_move(object *op, int state);
extern int check_trigger(object *op, object *cause);
extern void add_button_link(object *button, mapstruct *map, int connected);
extern void remove_button_link(object *op);
extern objectlink *get_button_links(const object *button);
extern int get_button_value(const object *button);
extern void do_mood_floor(object *op, object *op2);
extern object *check_inv_recursive(object *op, const object *trig);
extern void check_inv(object *op, object *trig);
extern void verify_button_links(const mapstruct *map);
/* exp.c */
extern int new_exp(const object *ob);
extern int has_ability(const object *ob);
extern void init_experience(void);
extern void dump_experience(void);
extern void free_experience(void);
/* friend.c */
extern void add_friendly_object(object *op);
extern void remove_friendly_object(object *op);
extern void dump_friendly_objects(void);
extern void clean_friendly_list(void);
extern int is_friendly(const object *op);
/* glue.c */
extern void fatal(int err);
/* holy.c */
extern void init_gods(void);
extern godlink *get_rand_god(void);
extern object *pntr_to_god_obj(godlink *godlnk);
extern void free_all_god(void);
extern void dump_gods(void);
/* info.c */
extern void dump_abilities(void);
extern void print_monsters(void);
extern void bitstostring(long bits, int num, char *str);
/* image.c */
extern void read_bmap_names(void);
extern int find_face(const char *name, int error);
extern int read_smooth(void);
extern int find_smooth(uint16 face, uint16 *smoothed);
extern void free_all_images(void);
/* init.c */
extern void init_library(void);
extern void init_environ(void);
extern void init_globals(void);
extern void free_globals(void);
extern void init_objects(void);
extern void init_defaults(void);
extern void init_dynamic(void);
extern void write_todclock(void);
extern void init_clocks(void);
extern void init_attackmess(void);
/* item.c */
extern int get_power_from_ench(int ench);
extern int calc_item_power(const object *op, int flag);
extern const typedata *get_typedata(int itemtype);
extern const typedata *get_typedata_by_name(const char *name);
extern void describe_resistance(const object *op, int newline, char* buf, int size);
extern void query_weight(const object *op, char* buf, int size);
extern void get_levelnumber(int i, char* buf, int size);
extern void query_short_name(const object *op, char* buf, int size);
extern void query_name(const object *op, char* buf, int size);
extern void query_base_name(const object *op, int plural, char* buf, int size);
extern void describe_item(const object *op, const object *owner, char* retbuf, int size);
extern int is_magical(const object *op);
extern int need_identify(const object *op);
extern void identify(object *op);
/* links.c */
extern objectlink *get_objectlink(void);
extern oblinkpt *get_objectlinkpt(void);
extern void free_objectlink(objectlink *ol);
extern void free_objectlinkpt(oblinkpt *obp);
/* living.c */
extern void set_attr_value(living *stats, int attr, sint8 value);
extern void change_attr_value(living *stats, int attr, sint8 value);
extern sint8 get_attr_value(const living *stats, int attr);
extern void check_stat_bounds(living *stats);
extern int change_abil(object *op, object *tmp);
extern void drain_stat(object *op);
extern void drain_specific_stat(object *op, int deplete_stats);
extern void change_luck(object *op, int value);
extern void remove_statbonus(object *op);
extern void add_statbonus(object *op);
extern void fix_object(object *op);
extern int allowed_class(const object *op);
extern void set_dragon_name(object *pl, const object *abil, const object *skin);
extern void dragon_level_gain(object *who);
extern object *give_skill_by_name(object *op, const char *skill_name);
extern void player_lvl_adj(object *who, object *op);
extern sint64 level_exp(int level, double expmul);
extern void calc_perm_exp(object *op);
extern sint64 check_exp_loss(const object *op, sint64 exp);
extern sint64 check_exp_adjust(const object *op, sint64 exp);
extern void change_exp(object *op, sint64 exp, const char *skill_name, int flag);
extern void apply_death_exp_penalty(object *op);
extern int did_make_save(const object *op, int level, int bonus);
/* logger.c */
extern void LOG(LogLevel logLevel, const char *format, ...);
/* los.c */
extern void init_block(void);
extern void clear_los(object *op);
extern int has_carried_lights(const object *op);
extern void update_los(object *op);
extern void update_all_map_los(mapstruct *map);
extern void update_all_los(const mapstruct *map, int x, int y);
extern void print_los(object *op);
extern void make_sure_seen(const object *op);
extern void make_sure_not_seen(const object *op);
/* map.c */
extern mapstruct *has_been_loaded(const char *name);
extern void create_pathname(const char *name, char* buf, int size);
extern void create_overlay_pathname(const char *name, char* buf, int size);
extern void create_template_pathname(const char *name, char* buf, int size);
extern int check_path(const char *name, int prepend_dir);
extern void dump_map(const mapstruct *m);
extern void dump_all_maps(void);
extern int get_map_flags(mapstruct *oldmap, mapstruct **newmap, sint16 x, sint16 y, sint16 *nx, sint16 *ny);
extern int blocked_link(object *ob, mapstruct *m, int sx, int sy);
extern int ob_blocked(const object *ob, mapstruct *m, sint16 x, sint16 y);
extern void fix_container(object *container);
extern void load_objects(mapstruct *m, FILE *fp, int mapflags);
extern void save_objects(mapstruct *m, FILE *fp, FILE *fp2, int flag);
extern mapstruct *get_linked_map(void);
extern void allocate_map(mapstruct *m);
extern mapstruct *get_empty_map(int sizex, int sizey);
extern mapstruct *load_original_map(const char *filename, int flags);
extern mapstruct *load_overlay_map(const char *filename, mapstruct *m);
extern int save_map(mapstruct *m, int flag);
extern void clean_object(object *op);
extern void free_all_objects(mapstruct *m);
extern void free_map(mapstruct *m, int flag);
extern void delete_map(mapstruct *m);
extern mapstruct *ready_map_name(const char *name, int flags);
extern int calculate_difficulty(mapstruct *m);
extern void clean_tmp_map(mapstruct *m);
extern void free_all_maps(void);
extern int change_map_light(mapstruct *m, int change);
extern void update_position(mapstruct *m, int x, int y);
extern void set_map_reset_time(mapstruct *map);
extern int out_of_map(mapstruct *m, int x, int y);
extern mapstruct *get_map_from_coord(mapstruct *m, sint16 *x, sint16 *y);
extern void get_rangevector(object *op1, const object *op2, rv_vector *retval, int flags);
extern void get_rangevector_from_mapcoord(const mapstruct *m, int x, int y, const object *op2, rv_vector *retval, int flags);
extern int on_same_map(const object *op1, const object *op2);
/* object.c */
extern int can_merge(object *ob1, object *ob2);
extern signed long sum_weight(object *op);
extern object *object_get_env_recursive(object *op);
extern object *get_player_container(object *op);
extern void dump_object(object *op);
extern void dump_all_objects(void);
extern object *find_object(tag_t i);
extern object *find_object_name(const char *str);
extern void free_all_object_data(void);
extern object *get_owner(object *op);
extern void clear_owner(object *op);
extern void set_owner(object *op, object *owner);
extern void copy_owner(object *op, object *clone);
extern void reset_object(object *op);
extern void free_key_values(object *op);
extern void clear_object(object *op);
extern void copy_object(object *op2, object *op);
extern object *get_object(void);
extern void update_turn_face(object *op);
extern void update_ob_speed(object *op);
extern void remove_from_active_list(object *op);
extern void update_object(object *op, int action);
extern void free_object(object *ob);
extern int count_free(void);
extern int count_used(void);
extern int count_active(void);
extern void sub_weight(object *op, signed long weight);
extern void remove_ob(object *op);
extern object *merge_ob(object *op, object *top);
extern object *insert_ob_in_map_at(object *op, mapstruct *m, object *originator, int flag, int x, int y);
extern object *insert_ob_in_map(object *op, mapstruct *m, object *originator, int flag);
extern void replace_insert_ob_in_map(const char *arch_string, object *op);
extern object *get_split_ob(object *orig_ob, uint32 nr);
extern object *decrease_ob_nr(object *op, uint32 i);
extern void add_weight(object *op, signed long weight);
extern object *insert_ob_in_ob(object *op, object *where);
extern int check_move_on(object *op, object *originator);
extern object *present_arch(const archetype *at, mapstruct *m, int x, int y);
extern object *present(unsigned char type, mapstruct *m, int x, int y);
extern object *present_in_ob(unsigned char type, const object *op);
extern object *present_in_ob_by_name(int type, const char *str, const object *op);
extern object *present_arch_in_ob(const archetype *at, const object *op);
extern void flag_inv(object *op, int flag);
extern void unflag_inv(object *op, int flag);
extern void set_cheat(object *op);
extern int find_multi_free_spot_around(object *ob, object *gen, int *hx, int *hy);
extern int find_free_spot(const object *ob, mapstruct *m, int x, int y, int start, int stop);
extern int find_first_free_spot(const object *ob, mapstruct *m, int x, int y);
extern void get_search_arr(int *search_arr);
extern int find_dir(mapstruct *m, int x, int y, object *exclude);
extern int distance(const object *ob1, const object *ob2);
extern int find_dir_2(int x, int y);
extern int absdir(int d);
extern int dirdiff(int dir1, int dir2);
extern int can_see_monsterP(mapstruct *m, int x, int y, int dir);
extern int can_pick(const object *who, const object *item);
extern object *object_create_clone(object *asrc);
extern int was_destroyed(const object *op, tag_t old_tag);
extern object *find_obj_by_type_subtype(const object *who, int type, int subtype);
extern key_value *get_ob_key_link(const object *ob, const char *key);
extern const char *get_ob_key_value(const object *op, const char *const key);
extern int set_ob_key_value(object *op, const char *key, const char *value, int add_key);
extern object *find_best_weapon_used_match(object *pl, const char *params);
extern int item_matched_string(object *pl, object *op, const char *name);
extern void fix_multipart_object(object *tmp);
/* path.c */
extern char *path_combine(const char *src, const char *dst);
extern void path_normalize(char *path);
extern char *path_combine_and_normalize(const char *src, const char *dst);
/* porting.c */
extern char *tempnam_local(const char *dir, const char *pfx);
extern void remove_directory(const char *path);
extern char *strdup_local(const char *str);
extern long strtol_local(register char *str, char **ptr, register int base);
extern char *strcasestr_local(const char *s, const char *find);
extern char *strerror_local(int errnum);
extern int isqrt(int n);
extern char *ltostr10(signed long n);
extern char *doubletostr10(double v);
extern void save_long(char *buf, const char *name, long n);
extern void save_long_long(char *buf, char *name, sint64 n);
extern FILE *open_and_uncompress(const char *name, int flag, int *compressed);
extern void close_and_delete(FILE *fp, int compressed);
extern void make_path_to_file(char *filename);
/* player.c */
extern void free_player(player *pl);
extern int atnr_is_dragon_enabled(int attacknr);
extern int is_dragon_pl(const object *op);
extern client_spell *get_client_spell_state(player *pl, object *spell);
extern int is_wraith_pl(object *op);
extern int is_old_wraith_pl(object *op);
/* quest.c */
extern int quest_is_quest_marker(const object *marker, int task);
extern int quest_is_in_progress(const object *marker, int task);
extern int quest_is_completed(const object *marker, int task);
extern const char *quest_get_name(const object *marker);
extern object *quest_get_player_quest(const object *pl, const char *name, const char *name_pl);
extern object *quest_get_override(const object *ob, const object *pl);
extern const char *quest_get_override_slaying(const object *ob, const object *pl);
extern const char *quest_get_override_msg(const object *ob, const object *pl);
extern void quest_apply_items(object *wrapper, player *pl);
extern int quest_on_activate(object *ob, player *pl);
extern int quest_is_override_compatible(const object *marker, const object *pl);
/* re-cmp.c */
extern const char *re_cmp(const char *str, const char *regexp);
/* readable.c */
extern int nstrtok(const char *buf1, const char *buf2);
extern char *strtoktolin(const char *buf1, const char *buf2);
extern int book_overflow(const char *buf1, const char *buf2, int booksize);
extern void init_readable(void);
extern void change_book(object *book, int msgtype);
extern object *get_random_mon(int level);
extern char *mon_desc(const object *mon);
extern object *get_next_mon(object *tmp);
extern char *mon_info_msg(int level, int booksize);
extern char *spellpath_msg(int level, int booksize);
extern void make_formula_book(object *book, int level);
extern char *msgfile_msg(int level, int booksize);
extern const char *god_info_msg(int level, int booksize);
extern void tailor_readable_ob(object *book, int msg_type);
extern void free_all_readable(void);
extern void write_book_archive(void);
extern readable_message_type *get_readable_message_type(object *readable);
/* recipe.c */
extern recipelist *get_formulalist(int i);
extern void init_formulae(void);
extern void check_formulae(void);
extern void dump_alchemy(void);
extern archetype *find_treasure_by_name(const treasure *t, const char *name, int depth);
extern long find_ingred_cost(const char *name);
extern void dump_alchemy_costs(void);
extern const char *ingred_name(const char *name);
extern int strtoint(const char *buf);
extern artifact *locate_recipe_artifact(const recipe *rp, size_t idx);
extern int numb_ingred(const char *buf);
extern recipelist *get_random_recipelist(void);
extern recipe *get_random_recipe(recipelist *rpl);
extern void free_all_recipes(void);
/* region.c */
extern region *get_region_by_name(const char *region_name);
extern region *get_region_by_map(mapstruct *m);
extern const char *get_name_of_region_for_map(const mapstruct *m);
extern region *get_region_from_string(const char *name);
extern int region_is_child_of_region(const region *child, const region *r);
extern const char *get_region_longname(const region *r);
extern const char *get_region_msg(const region *r);
extern object *get_jail_exit(object *op);
extern void init_regions(void);
extern region *get_region_struct(void);
extern void parse_regions(FILE *fp);
extern void assign_region_parents(void);
/* shstr.c */
extern void init_hash_table(void);
extern const char *add_string(const char *str);
extern const char *add_refcount(const char *str);
extern int query_refcount(const char *str);
extern const char *find_string(const char *str);
extern void free_string(const char *str);
extern void ss_dump_statistics(void);
extern const char *ss_dump_table(int what);
extern int buf_overflow(const char *buf1, const char *buf2, int bufsize);
/* time.c */
extern void reset_sleep(void);
extern void log_time(long process_utime);
extern int enough_elapsed_time(void);
extern void sleep_delta(void);
extern void set_max_time(long t);
extern void get_tod(timeofday_t *tod);
extern void print_tod(object *op);
extern void time_info(object *op);
extern long seconds(void);
/* treasure.c */
extern void init_archetype_pointers(void);
extern void load_treasures(void);
extern treasurelist *find_treasurelist(const char *name);
extern void create_all_treasures(treasure *t, object *op, int flag, int difficulty, int tries);
extern void create_one_treasure(treasurelist *tl, object *op, int flag, int difficulty, int tries);
extern void create_treasure(treasurelist *t, object *op, int flag, int difficulty, int tries);
extern object *generate_treasure(treasurelist *t, int difficulty);
extern int level_for_item(const object *op, int difficulty, int retmult);
extern int magic_from_difficulty(int difficulty);
extern void set_abs_magic(object *op, int magic);
extern void set_ring_bonus(object *op, int bonus);
extern int get_magic(int diff);
extern void fix_generated_item(object *op, object *creator, int difficulty, int max_magic, int flags);
extern artifactlist *find_artifactlist(int type);
extern void dump_artifacts(void);
extern void dump_monster_treasure_rec(const char *name, treasure *t, int depth);
extern void dump_monster_treasure(const char *name);
extern void init_artifacts(void);
extern void add_abilities(object *op, object *change);
extern void give_artifact_abilities(object *op, object *artifact);
extern void generate_artifact(object *op, int difficulty);
extern void fix_flesh_item(object *item, object *donor);
extern int special_potion(object *op);
extern void free_treasurestruct(treasure *t);
extern void free_charlinks(linked_char *lc);
extern void free_artifact(artifact *at);
extern void free_artifactlist(artifactlist *al);
extern void free_all_treasures(void);
/* utils.c */
extern int random_roll(int min, int max, const object *op, int goodbad);
extern sint64 random_roll64(sint64 min, sint64 max, const object *op, int goodbad);
extern int die_roll(int num, int size, const object *op, int goodbad);
extern int rndm(int min, int max);
extern void decay_objects(mapstruct *m);
extern materialtype_t *name_to_material(const char *name);
extern void transmute_materialname(object *op, const object *change);
extern void set_materialname(object *op, int difficulty, materialtype_t *nmt);
extern void strip_media_tag(char *message);
extern const char *strrstr(const char *haystack, const char *needle);
extern void strip_endline(char *buf);
extern void replace(const char *src, const char *key, const char *replacement, char *result, size_t resultsize);
extern void make_list_like(char *input);
/* loader.c */
extern int lex_load(object *op, int map_flags);
extern void yyrestart(FILE *input_file);
extern void yypop_buffer_state(void);
extern int yyget_lineno(void);
extern FILE *yyget_in(void);
extern FILE *yyget_out(void);
extern int yyget_leng(void);
extern char *yyget_text(void);
extern void yyset_lineno(int line_number);
extern void yyset_in(FILE *in_str);
extern void yyset_out(FILE *out_str);
extern int yyget_debug(void);
extern void yyset_debug(int bdebug);
extern int yylex_destroy(void);
extern void yyfree(void *ptr);
extern int yyerror(char *s);
extern int load_object(FILE *fp, object *op, int bufstate, int map_flags);
extern int set_variable(object *op, char *buf);
extern void init_vars(void);
extern void free_loader(void);
extern void get_ob_diff(object *op, object *op2, char* buf, int size);
extern void save_object(FILE *fp, object *op, int flag);
