double base_weight_bench_press(double body_weight_pushups, double rep_max_pushup);
double base_weight_weighted_squats(double body_weight, double rep_max_pushup);
double base_weight_air_squats(double body_weight, double rep_max_squats);

//  Stages from problem analysis
enum stage { begynder, let_øvet, øvet, meget_øvet, ekspert };
//enum equipment { nothing, barbell, bench, pull_up_bar, pull_down_machine, resistance_bands, length_of_equipment_enum };
// nothing, barbell, bench, pull_up_bar, pull_down_machine, resistance_bands
typedef struct {
    int nothing;
    int barbell;
    int bench;
    int pull_up_bar;
    int pull_down_machine;
    int resistance_bands;
} check_equipment;

//  Exercise platform
typedef struct {
    char name[20];
    //  When calling necessary_equipment.x it searches in the check_equipment struct
    check_equipment necessary_equipment;
    //  We assume that weight only increases by 2.5, argue for this in implementation/design
    double addition;
    double base_weight;
} exercise;




exercise* create_all_exercises();
void print_exercise(exercise exercise);

