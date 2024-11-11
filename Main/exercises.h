
enum equipment { nothing, barbell, bench, pull_up_bar, pull_down_machine, resistance_bands };

typedef struct {
    char name[];
    enum equipment needed_equipment[];
} exercise;

exercise* create_all_exercises();

