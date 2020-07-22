#include "office.h"
#include <assert.h>
#include <stdbool.h>

#define NAME_MAX (41)
#define QUEUE_CAPACITY (101)

struct storage {
    struct employee** queue;
    int first;
    int last;
};

struct storage s = { NULL, 0, 0 };

void enqueue(struct employee* emp) { s.queue[(s.last)++] = emp; }

struct employee* dequeue() { return s.queue[(s.first)++]; }

void deep_copy(struct employee* des, struct employee* src) {
    memcpy(des, src, sizeof(struct employee));
    des->name = malloc(sizeof(char) * NAME_MAX);
    strcpy(des->name, src->name);
}

int employee_exist(struct office* off, struct employee* emp) {
    if (off == NULL || off->department_head == NULL) { return false; } // invalid case

    s.queue = malloc(sizeof(struct employee*) * QUEUE_CAPACITY);

    struct employee* cursor = off->department_head;
    while (cursor != NULL) {
        if (cursor == emp) {
            free(s.queue);
            s.queue = NULL;
            s.first = 0;
            s.last = 0;
            return true;
        } else if (cursor->n_subordinates > 0) {
            for (int i = 0; i < (int)cursor->n_subordinates; i++) {
                enqueue(&cursor->subordinates[i]);
            }
        }
        cursor = dequeue();
    }
    free(s.queue);
    s.queue = NULL;
    s.first = 0;
    s.last = 0;
    return false;
}

struct employee* find_first_not_supervising(struct office* off) {
    if (off == NULL || off->department_head == NULL) { return NULL; } // invalid case

    s.queue = malloc(sizeof(struct employee*) * QUEUE_CAPACITY);

    struct employee* cursor = off->department_head;
    while (cursor != NULL) {
        if (cursor->n_subordinates == 0) {
            free(s.queue);
            s.queue = NULL;
            s.first = 0;
            s.last = 0;
            return cursor;
        } else {
            for (int i = 0; i < (int)cursor->n_subordinates; i++) {
                enqueue(&cursor->subordinates[i]);
            }
        }
        cursor = dequeue();
    }
    free(s.queue);
    s.queue = NULL;
    s.first = 0;
    s.last = 0;
    return NULL;
}

void add_emp_to_sup(struct employee* sup, struct employee* emp) {
    sup->n_subordinates++;
    emp->supervisor = sup;
    if (sup->n_subordinates == 0) { // initialize subordinate list
        sup->subordinates = malloc(sizeof(struct employee));
        deep_copy(sup->subordinates, emp);
    } else { // adding to the exist list
        sup->subordinates = realloc(sup->subordinates, sizeof(struct employee) * sup->n_subordinates);
        deep_copy(&sup->subordinates[sup->n_subordinates-1], emp);
    }
}

void office_employee_place(struct office* off, struct employee* sup, struct employee* emp) {
    if (off == NULL || emp == NULL) { return; } // invalid case

    if (sup == NULL) {
        if (off->department_head == NULL) {
            // put emp in office head
            off->department_head = malloc(sizeof(struct employee));
            deep_copy(off->department_head, emp);
        } else {
            // sup to be first employee's n_sub is 0
            sup = find_first_not_supervising(off);
            add_emp_to_sup(sup, emp);
        }
    } else { // sup is given
        if (employee_exist(off, sup) == false) { return; } // invalid case
        add_emp_to_sup(sup, emp);
    }
}

struct employee* list_deep_copy_without_emp(struct employee* emp) {
    struct employee* temp = malloc(sizeof(struct employee) * (emp->supervisor->n_subordinates));
    int index = 0;
    for (int i = 0; i < (int)emp->supervisor->n_subordinates+1; i++) {
        // if the employee is not the one we want to delete
        if (&emp->supervisor->subordinates[i] != emp) {
            // add to the list
            temp[index++] = emp->supervisor->subordinates[i];
        }
    }
    return temp;
}

void update(struct employee* list, struct employee* emp, int index) {
    if (index >= 0) {
        list[index].supervisor = emp->supervisor;
        list[index].subordinates = emp->subordinates;
        list[index].n_subordinates = emp->n_subordinates;
    }
    free(emp->name);
    emp->name = NULL;
    free(emp->supervisor->subordinates);
    emp->supervisor->subordinates = NULL;
    emp->supervisor->subordinates = list;
}

void remove_emp(struct employee* emp) {
    // decrease the size
    emp->supervisor->n_subordinates--;
    struct employee* temp = list_deep_copy_without_emp(emp);

    update(temp, emp, -1);
}

int find_index(struct employee* emp) {
    for (int i = 0; i < (int)emp->supervisor->n_subordinates; i++) {
        // if it is not the one need to fire, copy it into temp_sub_list
        if (&emp->supervisor->subordinates[i] == emp) {
            return i;
        }
    }
    return -1;
}

void office_fire_employee(struct employee* emp) {
    if (emp == NULL) { return; }

    if (emp->n_subordinates == 0) {
        remove_emp(emp);
    } else {
        // emp1's temporary subordinate list
        struct employee* temp_sub_list = malloc(sizeof(struct employee) * (emp->supervisor->n_subordinates));
        struct employee* promote_emp = &emp->subordinates[0]; // emp3

        for (int i = 0; i < (int)emp->supervisor->n_subordinates; i++) {
            // if it is not the one need to fire, copy it into temp_sub_list
            if (&emp->supervisor->subordinates[i] != emp) {
                temp_sub_list[i] = emp->supervisor->subordinates[i];
            }
        }

        int index = find_index(emp);
        deep_copy(&temp_sub_list[index], promote_emp);
        remove_emp(promote_emp);
        update(temp_sub_list, emp, index);
    }
}

struct employee* office_get_first_employee_with_name(struct office* off, const char* name) {
    if (off == NULL || name == NULL || off->department_head == NULL) { return NULL; }

    s.queue = malloc(sizeof(struct employee*) * QUEUE_CAPACITY);

    struct employee* cursor = off->department_head;
    while (cursor != NULL) {
        if (strcmp(cursor->name, name) == 0) {
            free(s.queue);
            s.queue = NULL;
            s.first = 0;
            s.last = 0;
            return cursor;
        }

        if (cursor->subordinates != NULL) {
            for (int i = 0; i < (int)cursor->n_subordinates; i++) {
                enqueue(&cursor->subordinates[i]);
            }
        }
        if (s.first == s.last) { break; }
        cursor = dequeue();
    }
    free(s.queue);
    s.queue = NULL;
    s.first = 0;
    s.last = 0;
    return NULL;
}

struct employee* office_get_last_employee_with_name(struct office* off, const char* name) {
    if (off == NULL || name == NULL || off->department_head == NULL) { return NULL; }

    s.queue = malloc(sizeof(struct employee*) * QUEUE_CAPACITY);

    size_t n_emps = 0;
    struct employee** emps = malloc(sizeof(struct employee*));

    struct employee* cursor = off->department_head;
    while (cursor != NULL) {
        if (strcmp(cursor->name, name) == 0) {
            n_emps++;
            emps = realloc(emps, n_emps * sizeof(struct employee*) * n_emps);
            emps[n_emps - 1] = cursor;
        }

        if (cursor->subordinates != NULL) {
            for (int i = 0; i < (int)cursor->n_subordinates; i++) {
                enqueue(&cursor->subordinates[i]);
            }
        }

        if (s.first == s.last) { break; }
        cursor = dequeue();
    }

    struct employee* ret;
    if (n_emps == 0) {
        ret = NULL;
    } else {
        ret = emps[n_emps-1];
    }
    free(emps);
    free(s.queue);
    s.queue = NULL;
    s.first = 0;
    s.last = 0;
	return ret;
}

void emps_init(struct employee** emps, size_t* n_emps) {
    *n_emps = 0;
    *emps = malloc(sizeof(struct employee));
}

void emps_restore(struct employee** emps, size_t* n_emps) {
    for (int i = 0; i < (int)*n_emps; i++) {
        free((*emps)[i].name);
    }
    *n_emps = 0;
    *emps = realloc(*emps, 0 * sizeof(struct employee));
}

void add_to_emps(struct employee** emps, size_t* n_emps, struct employee* emp) {
    (*n_emps)++;
    *emps = realloc(*emps, (*n_emps) * sizeof(struct employee));
    deep_copy(&(*emps)[*n_emps-1], emp);
}

void get_next_level(struct employee** emps, size_t* n_emps, struct employee* old_emps, int old_n_emps) {
    emps_restore(emps, n_emps);
    // loop though upper list, aka old
    for (int i = 0; i < old_n_emps; i++) {
        if (old_emps[i].n_subordinates != 0) {
            // put all subs of upper list into a list
            for (int j = 0; j < (int)old_emps[i].n_subordinates; j++) {
                add_to_emps(emps, n_emps, &old_emps[i].subordinates[j]);
            }
        }
    }
}

void office_get_employees_at_level(struct office* off, size_t level, struct employee** emps, size_t* n_emps) {
    if (off == NULL || off->department_head == NULL || n_emps == NULL || level < 0 || off->department_head->name == NULL) { return; } // invalid case

    emps_init(emps, n_emps);

    if (level == 0) {
        *emps = off->department_head;
        *n_emps = 1;
        return;
    }

    struct employee* old_emps = off->department_head;
    int old_n_emps = 1;
    for (int i = 0; i < (int)level; i++) {
        get_next_level(emps, n_emps, old_emps, old_n_emps);

        // update list
        old_emps = *emps;
        old_n_emps = *n_emps;
    }
    return;
}

void office_get_employees_by_name(struct office* off, const char* name, struct employee** emps, size_t* n_emps) {
    if (off == NULL || off->department_head == NULL || n_emps == NULL || name == NULL) { return; }

    s.queue = malloc(sizeof(struct employee*) * QUEUE_CAPACITY);

    emps_init(emps, n_emps);

    struct employee* cursor = off->department_head;
    while (cursor != NULL) {
        if (strcmp(cursor->name, name) == 0) {
            add_to_emps(emps, n_emps, cursor);
        }

        if (cursor->subordinates != NULL) {
            for (int i = 0; i < (int)cursor->n_subordinates; i++) {
                enqueue(&cursor->subordinates[i]);
            }
        }

        if (s.first == s.last) { break; }
        cursor = dequeue();
    }
    free(s.queue);
    s.queue = NULL;
    s.first = 0;
    s.last = 0;
    return;
}

void post_recursion(struct employee* root, struct employee** emps, size_t* n_emps) {
    if (*emps == false) { return; } // base case
    if (root->subordinates != NULL) {
        // recusive case
        for (int i = 0; i < (int)root->n_subordinates; i++) {
            post_recursion(&root->subordinates[i], emps, n_emps);
            add_to_emps(emps, n_emps, &root->subordinates[i]);
        }
    }
}

void office_get_employees_postorder(struct office* off, struct employee** emps, size_t* n_emps) {
    if (off == NULL || off->department_head == NULL) { return; }

    emps_init(emps, n_emps);
    post_recursion(off->department_head, emps, n_emps);
    add_to_emps(emps, n_emps, off->department_head);
}

void office_disband(struct office* off) {
    if (off == NULL) { return; }

    if (off->department_head == NULL) {
        free(off);
        off = NULL;
        return;
    }
    s.queue = malloc(sizeof(struct employee*) * QUEUE_CAPACITY);

    // add employee into queue
    struct employee* cursor = off->department_head;
    while (cursor != NULL) {
        if (cursor->subordinates != NULL) {
            for (int i = 0; i < (int)cursor->n_subordinates; i++) {
                enqueue(&cursor->subordinates[i]);
            }
        }
        if (s.first == s.last) { break; }
        cursor = dequeue();
    }
    free(cursor->name);
    cursor->name = NULL;
    free(cursor->subordinates);
    cursor->subordinates = NULL;

    // loop backwards queue
    for (int i = s.last - 1; i >= 0; i--) {
        free(s.queue[i]->name);
        s.queue[i]->name = NULL;
        if (s.queue[i]->subordinates != NULL) {
            free(s.queue[i]->subordinates);
            s.queue[i]->subordinates = NULL;
        }
    }

    if (off->department_head->n_subordinates != 0) {
        free(off->department_head->subordinates);
        off->department_head->subordinates = NULL;
    }

    free(off->department_head->name);
    off->department_head->name = NULL;
    free(off->department_head);
    off->department_head = NULL;
    free(off);
    off = NULL;
    free(s.queue);
    s.queue = NULL;
    s.first = 0;
    s.last = 0;
}

void office_promote_employee(struct employee* emp) { emp = NULL; }

void office_demote_employee(struct employee* supervisor, struct employee* emp) {
    supervisor = NULL;
    emp = NULL;
}
