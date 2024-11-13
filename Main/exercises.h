double base_weight(double body_weight, double rep_max_pushup);

//  Stages from problem analysis
enum stage { begynder, let_øvet, øvet, meget_øvet, ekspert };
enum equipment { nothing, barbell, bench, pull_up_bar, pull_down_machine, resistance_bands, length_of_equipment_enum };

//  Exercise platform
typedef struct {
    char name[20];
    //  Ændr til ny type
    enum equipment needed_equipment;
    //  We assume that weight only increases by 2.5, argue for this in implementation/design
    double addition;
    double base_weight;
} exercise;

typedef struct {
    int bench = 0;
    int barbell = 0;
    int pull_up_bar = 0;
} equipment_2;


exercise* create_all_exercises();
void print_exercise(exercise exercise);

