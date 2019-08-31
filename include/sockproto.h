/* image.c */
int is_valid_faceset(int fsn);
void set_face_mode_cmd(char *buf, int len, socket_struct *ns);
void send_face_cmd(char *buff, int len, socket_struct *ns);
void esrv_send_face(socket_struct *ns, uint16_t face_num, int nocache);
void send_image_info(socket_struct *ns);
void send_image_sums(socket_struct *ns, char *params);
/* info.c */
void print_ext_msg(socket_struct *ns, int color, uint8_t type, uint8_t subtype, const char *message);
void draw_ext_info(int flags, int pri, const object *pl, uint8_t type, uint8_t subtype, const char *message);
void draw_ext_info_format(int flags, int pri, const object *pl, uint8_t type, uint8_t subtype, const char *format, ...);
void ext_info_map(int color, const mapstruct *map, uint8_t type, uint8_t subtype, const char *str1);
void ext_info_map_except(int color, const mapstruct *map, const object *op, uint8_t type, uint8_t subtype, const char *str1);
void ext_info_map_except2(int color, const mapstruct *map, const object *op1, const object *op2, int type, int subtype, const char *str1);
void rangetostring(const object *pl, char *obuf, size_t len);
void set_title(const object *pl, char *buf, size_t len);
void magic_mapping_mark(object *pl, char *map_mark, int strength);
void draw_magic_map(object *pl);
/* init.c */
void init_connection(socket_struct *ns, const char *from_ip);
void init_listening_socket(socket_struct *ns);
void init_server(void);
void free_all_newserver(void);
void free_newsocket(socket_struct *ns);
void final_free_player(player *pl);
/* item.c */
void esrv_draw_look(object *pl);
void esrv_send_inventory(object *pl, object *op);
void esrv_update_item(int flags, object *pl, object *op);
void esrv_send_item(object *pl, object *op);
void esrv_del_item(player *pl, object *ob);
void examine_cmd(char *buf, int len, player *pl);
void apply_cmd(char *buf, int len, player *pl);
void lock_item_cmd(uint8_t *data, int len, player *pl);
void mark_item_cmd(uint8_t *data, int len, player *pl);
void look_at(object *op, int dx, int dy);
void look_at_cmd(char *buf, int len, player *pl);
void esrv_move_object(object *pl, tag_t to, tag_t tag, long nrof);
void inscribe_scroll_cmd(char *buf, int len, player *pl);
/* loop.c */
void request_info_cmd(char *buf, int len, socket_struct *ns);
void handle_client(socket_struct *ns, player *pl);
void watchdog(void);
void do_server(void);
void update_players(void);
/* lowlevel.c */
void SockList_Init(SockList *sl);
void SockList_Term(SockList *sl);
void SockList_Reset(SockList *sl);
void SockList_ResetRead(SockList *sl);
void SockList_AddChar(SockList *sl, char c);
void SockList_AddShort(SockList *sl, uint16_t data);
void SockList_AddInt(SockList *sl, uint32_t data);
void SockList_AddInt64(SockList *sl, uint64_t data);
size_t SockList_Avail(const SockList *sl);
void SockList_AddString(SockList *sl, const char *data);
void SockList_AddData(SockList *sl, const void *data, size_t len);
void SockList_AddLen8Data(SockList *sl, const void *data, size_t len);
void SockList_AddLen16Data(SockList *sl, const void *data, size_t len);
void SockList_AddPrintf(SockList *sl, const char *format, ...);
void SockList_AddStringBuffer(SockList *sl, StringBuffer *sb);
void SockList_NullTerminate(SockList *sl);
int GetInt_String(const unsigned char *data);
short GetShort_String(const unsigned char *data);
int SockList_ReadPacket(int fd, SockList *sl, int len);
void Send_With_Handling(socket_struct *ns, SockList *sl);
void write_cs_stats(void);
/* metaserver.c */
void metaserver_init(void);
void metaserver_update(void);
int metaserver2_init(void);
void *metaserver2_thread(void *junk);
/* request.c */
void set_up_cmd(char *buf, int len, socket_struct *ns);
void add_me_cmd(char *buf, int len, socket_struct *ns);
void toggle_extended_infos_cmd(char *buf, int len, socket_struct *ns);
void toggle_extended_text_cmd(char *buf, int len, socket_struct *ns);
void ask_smooth_cmd(char *buf, int len, socket_struct *ns);
void new_player_cmd(uint8_t *buf, int len, player *pl);
void reply_cmd(char *buf, int len, player *pl);
void version_cmd(char *buf, int len, socket_struct *ns);
void set_sound_cmd(char *buf, int len, socket_struct *ns);
void map_newmap_cmd(socket_struct *ns);
void move_cmd(char *buf, int len, player *pl);
void send_query(socket_struct *ns, uint8_t flags, const char *text);
void esrv_update_stats(player *pl);
void esrv_new_player(player *pl, uint32_t weight);
void esrv_send_animation(socket_struct *ns, short anim_num);
void draw_client_map2(object *pl);
void draw_client_map(object *pl);
void esrv_map_scroll(socket_struct *ns, int dx, int dy);
void send_plugin_custom_message(object *pl, char *buf);
void send_exp_table(socket_struct *ns, char *params);
void send_skill_info(socket_struct *ns, char *params);
void send_spell_paths(socket_struct *ns, char *params);
void send_race_list(socket_struct *ns, char *params);
void send_race_info(socket_struct *ns, char *params);
void send_class_list(socket_struct *ns, char *params);
void send_class_info(socket_struct *ns, char *params);
void esrv_update_spells(player *pl);
void esrv_remove_spell(player *pl, object *spell);
void esrv_send_pickup(player *pl);
void esrv_add_spells(player *pl, object *spell);
void send_tick(player *pl);
void send_file(socket_struct *ns, const char *file);
void account_login_cmd(char *buf, int len, socket_struct *ns);
void account_new_cmd(char *buf, int len, socket_struct *ns);
void account_add_player_cmd(char *buf, int len, socket_struct *ns);
void account_play_cmd(char *buf, int len, socket_struct *ns);
void send_account_players(socket_struct *ns);
void create_player_cmd(char *buf, int len, socket_struct *ns);
void account_password(char *buf, int len, socket_struct *ns);
/* requestinfo.c */
void send_new_char_info(socket_struct *ns);
void send_map_info(socket_struct *ns);
/* sounds.c */
void play_sound_player_only(player *pl, int8_t sound_type, object *emitter, int dir, const char *action);
void play_sound_map(int8_t sound_type, object *emitter, int dir, const char *action);
void send_background_music(player *pl, const char *music);
void player_update_bg_music(object *player);
