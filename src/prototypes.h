export void output_open(CONFIG *config);
export void output_close(CONFIG *config);
export void conv1(CONFIG *config, LING_LIST *ling_list, SENT *sent);
export int vowel(char *ph) ;
export void conv2(CONFIG *config, SENT *sent, SPROSOD_LIST *spl);
#ifdef FREEPHONE_OBSOLETE
export void durations(CONFIG *config, SPN *ps, ACOUSTIC *as);
#endif
export void durpros(CONFIG *config, SPROSOD_LIST *spl);
#ifdef FREEPHONE_OBSOLETE
export void go(CONFIG *config, BUFFER *buffer, LING_LIST *ling_list, SENT *sent, SPROSOD_LIST *spl, SPN *ps, ACOUSTIC *as) ;
#endif
export void go3(CONFIG *config, BUFFER *buffer, LING_LIST *ling_list, SENT *sent, SPROSOD_LIST *spl, SPN *ps) ;
#ifdef FREEPHONE_OBSOLETE
export void go2(CONFIG *config, SPN *ps, ACOUSTIC *as) ;
#endif
export void grammar(LING_LIST *ling_list);
export void outstring(char *string);
export int makeupper(int character);
export int Xgetc();
export int new_char();
export char *nrl_rules(char *in);
export void have_number();
export void have_letter();
export void have_dollars();
export void have_special();
export void xlate_string(char *is);
export void abbrev(char *buff);
#ifdef FREEPHONE_OBSOLETE
export void phonstoframes(SPN *ps, ACOUSTIC *as);
export void unload_diphs(CONFIG *config) /* for easier changes later  */;
export void load_speech(CONFIG *config);
#endif
export int main(int argc, char **argv);
export void nrl_edin_conv(char *str, char *str2);
export void load_context_rules(char * filename);
export void phon_rules_init();
export void phon_rules_free();
export void phon_rules(SENT *sent);
export void xlate_word(char *word);
#ifdef FREEPHONE_OBSOLETE
export void calc_pitch(CONFIG *config, SPN *ps, ACOUSTIC *as);
#endif
export void prosody(SPROSOD_LIST *spl, SPN *ps);
export int read_rule_file(char *filename, RULE *rules);
export void process_rule(char *input,RULE *rule);
export void replace_classes(int num_rules, RULE *rules, int num_classes, char **key, char **value);
export char *apply_class(int num_classes, char *string, char **key, char **value);
export void use_class(char *buffer, char *key, char *value);
export void replace_class(char *buffer, char *ptr, char *key, char *value);
export void rule_exec(int type,int nrules, RULE *rule, SENT *sent);
export void say_cardinal(long int value);
export void say_ordinal(long int value);
#ifdef FREEPHONE_OBSOLETE
export void init(CONFIG *config, BUFFER *buffer, LING_LIST *ling_list, SENT *sent, SPROSOD_LIST *spl, SPN *ps, ACOUSTIC *as) ;
export void terminate(CONFIG *config, BUFFER *buffer, LING_LIST *ling_list, SENT *sent, SPROSOD_LIST *spl, SPN *ps, ACOUSTIC *as);
#else
export void init(CONFIG *config, BUFFER *buffer, LING_LIST *ling_list, SENT *sent, SPROSOD_LIST *spl, SPN *ps) ;
export void terminate(CONFIG *config, BUFFER *buffer, LING_LIST *ling_list, SENT *sent, SPROSOD_LIST *spl, SPN *ps);
#endif

export void  buffer_init(BUFFER *buffer);
export char *buffer_text(BUFFER *buffer);
export void  buffer_add_char(BUFFER *buffer, int c);
export void  buffer_add_str(BUFFER *buffer, char *str);
export void  buffer_clear(BUFFER *buffer);
export char  buffer_last_char(BUFFER *buffer);
export void  buffer_free(BUFFER *buffer);

export void ling_list_malloc(int num, LING_LIST *ling_list);
export void ling_list_realloc(int num, LING_LIST *ling_list);
export void ling_list_free(LING_LIST *ling_list);
export void sent_init(SENT *sent);
export void sent_alloc_sil(SENT *sent, int n);
export void sent_list_clear(SENT *sent);
export void sent_list_concat(SENT *sent, char *str);
export void sent_free(SENT *sent);
export void spl_malloc(int num, SPROSOD_LIST *spl);
export void spl_realloc(int num, SPROSOD_LIST *spl);
export void spl_free(SPROSOD_LIST *spl);
export void ps_malloc(int nphons, int ntargs, SPN *ps);
export void ps_realloc(int nphons, int ntargs, SPN *ps);
export void ps_free(SPN *ps);
#ifdef FREEPHONE_OBSOLETE
export void as_malloc(int nframes, int npp, ACOUSTIC *as);
export void as_realloc(int nframes, int npp, ACOUSTIC *as);
export void as_free(ACOUSTIC *as);
#endif
export void say_ascii(int character);
export void spell_word(char *word);
export void put_mbrola_data(CONFIG *config, SPN *ps);
#ifdef FREEPHONE_OBSOLETE
export void put_spn_data(CONFIG *config, SPN *ps);
export void get_spn_data(CONFIG *config, SPN *ps);
#endif
export char *syllabify(char *string, CONFIG *config) 	/* replace string in situ  */;
export char *stress(char *param) /* no stress allowed initially  */;
#ifdef FREEPHONE_OBSOLETE
export void process_sentence(CONFIG *config, BUFFER *buffer, LING_LIST *ling_list, SENT *sent, SPROSOD_LIST *spl, SPN *ps, ACOUSTIC *as);
#endif
export void produce_spn_file(CONFIG *config, BUFFER *buffer, LING_LIST *ling_list, SENT *sent, SPROSOD_LIST *spl, SPN *ps);
#ifdef FREEPHONE_OBSOLETE
export void process_spn_file(CONFIG *config, SPN *ps, ACOUSTIC *as);
#endif
export void high_level(CONFIG *config, BUFFER *buffer, LING_LIST *ling_list, SENT *sent, SPROSOD_LIST *spl, SPN *ps);
#ifdef FREEPHONE_OBSOLETE
export void low_level(CONFIG *config, SPN *ps, ACOUSTIC *as);
#endif
export void tags(CONFIG *config,BUFFER *buffer, LING_LIST *ling_list);
export void transcribe(CONFIG *config, LING_LIST *ling_list);
export char **split(char *in) ;
export void tidy_split(char **root);
export KEY *binary(char *word, KEY tab[], int n);
export PKEY *pbinary(char *word, PKEY tab[], int n);
