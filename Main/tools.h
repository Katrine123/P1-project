enum datatype {integer, character, long_float, string};
typedef enum datatype datatype;
enum equipment {barbell, bench, pull_up_bar, pull_down_machine, resistance_bands };

int homemade_scan(datatype type, void* input);
char* naming_equipment(enum equipment eq) ;
