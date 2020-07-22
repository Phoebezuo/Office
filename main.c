#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "office.h"

void example1() {
	struct office* off = malloc(sizeof(struct office));
	off->department_head = NULL;

	struct employee emp = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
	office_employee_place(off, NULL, &emp);
	printf("%s\n", off->department_head->name); // Employee1

	office_disband(off);
}

void example2() {
	struct office* off = malloc(sizeof(struct office));
	off->department_head = NULL;

	struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
	office_employee_place(off, NULL, &emp1);
	printf("%d\n", off->department_head == NULL); // 0 (False)

	struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

	office_employee_place(off, NULL, &emp2);
	printf("%s\n", off->department_head->subordinates[0].name); // Employee2

	office_disband(off);
}

void example3() {
    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;

    struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp1);
    puts(off->department_head->name); // Employee1

    struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp2);
    puts(off->department_head->subordinates[0].name); // Employee2
    printf("address expect %p\n", off->department_head);
    printf("n_sub expect %zu\n", off->department_head->n_subordinates);

    struct employee emp3 = { .name = "Employee3", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, off->department_head, &emp3);
    puts(off->department_head->subordinates[1].name); // Employee3

    office_disband(off);
}

void example4() {
    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;

    struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp1);
    puts(off->department_head->name); // Employee1

    struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp2);
    puts(off->department_head->subordinates[0].name); // Employee2

    struct employee emp3 = { .name = "Employee3", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp3);
    puts(off->department_head->subordinates->subordinates->name); // Employee3

    office_disband(off);
}

void example5() {
    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;

    struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp3 = { .name = "Employee3", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp4 = { .name = "Employee4", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp5 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp6 = { .name = "Employee6", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp1);
    office_employee_place(off, NULL, &emp2);
    office_employee_place(off, NULL, &emp3);
    office_employee_place(off, NULL, &emp4);
    office_employee_place(off, off->department_head, &emp5);
    office_employee_place(off, &off->department_head->subordinates[1], &emp6);

	printf("sup of 2 %s\n", off->department_head->subordinates[0].supervisor->name); // sup of 2 Employee1

	office_disband(off);
}

void example6() {
    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;

    struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp3 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp4 = { .name = "Employee4", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp5 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp6 = { .name = "Employee6", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp1);
    office_employee_place(off, NULL, &emp2);
    office_employee_place(off, NULL, &emp3);
    office_employee_place(off, NULL, &emp4);
    office_employee_place(off, off->department_head, &emp5);
    office_employee_place(off, &off->department_head->subordinates[1], &emp6);

    printf("function output address is %p\n", office_get_first_employee_with_name(off, "Employee5"));
    printf("expected address is %p\n", &off->department_head->subordinates[1]); // location of emp5
	puts("-------------------------");
    printf("emp1 %p\n", &off->department_head);
	printf("emp2 %p\n", &off->department_head->subordinates[0]);
	printf("emp3 %p\n", &off->department_head->subordinates[0].subordinates[0]);
	printf("emp4 %p\n", &off->department_head->subordinates[0].subordinates[0].subordinates[0]);
	printf("emp5 %p\n", &off->department_head->subordinates[1]);
	printf("emp6 %p\n", &off->department_head->subordinates[1].subordinates[0]);

	office_disband(off);
}

void example7() {
    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;

    struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp3 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp4 = { .name = "Employee4", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp5 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp6 = { .name = "Employee6", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp1);
    office_employee_place(off, NULL, &emp2);
    office_employee_place(off, NULL, &emp3);
    office_employee_place(off, NULL, &emp4);
    office_employee_place(off, off->department_head, &emp5);
    office_employee_place(off, &off->department_head->subordinates[1], &emp6);

    printf("function output address is %p\n", office_get_last_employee_with_name(off, "Employee5"));
    printf("expected address is %p\n", &off->department_head->subordinates[0].subordinates[0]); // location of emp3

	office_disband(off);
}

void example8() {
    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;

    struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp3 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp4 = { .name = "Employee4", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp5 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp6 = { .name = "Employee6", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp1);
    office_employee_place(off, NULL, &emp2);
    office_employee_place(off, NULL, &emp3);
    office_employee_place(off, NULL, &emp4);
    office_employee_place(off, off->department_head, &emp5);
    office_employee_place(off, &off->department_head->subordinates[1], &emp6);

    struct employee* emps = NULL;
    size_t n_emps = 0;
    office_get_employees_by_name(off, "Employee5", &emps, &n_emps);
    printf("%zu\n", n_emps); // 2

	office_disband(off);
}

void example9() {
    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;

    struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp3 = { .name = "Employee3", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp4 = { .name = "Employee4", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp5 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp6 = { .name = "Employee6", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp1);
    office_employee_place(off, NULL, &emp2);
    office_employee_place(off, NULL, &emp3);
    office_employee_place(off, NULL, &emp4);
    office_employee_place(off, off->department_head, &emp5);
    office_employee_place(off, &off->department_head->subordinates[1], &emp6);

    struct employee* emps = NULL;
    size_t n_emps = 0;
    office_get_employees_at_level(off, 1, &emps, &n_emps);
    printf("%s\n", emps[0].name);
	printf("%s\n", emps[1].name);

	office_disband(off);
}

void example10() {
    struct employee emp1 = {.name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp2 = {.name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp3 = {.name = "Employee3", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp4 = {.name = "Employee4", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp5 = {.name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp6 = {.name = "Employee6", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp7 = {.name = "Employee7", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp8 = {.name = "Employee8", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp9 = {.name = "Employee9", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp10 = {.name = "Employee10", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp11 = {.name = "Employee11", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp12 = {.name = "Employee12", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp13 = {.name = "Employee13", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};
    struct employee emp14 = {.name = "Employee14", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0};

    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;
    office_employee_place(off, NULL, &emp1);
    office_employee_place(off, off->department_head, &emp2);
    office_employee_place(off, off->department_head, &emp3);
    office_employee_place(off, off->department_head, &emp4);
    office_employee_place(off, off->department_head, &emp5);
    office_employee_place(off, &off->department_head->subordinates[0], &emp6);
    office_employee_place(off, &off->department_head->subordinates[0], &emp7);
    office_employee_place(off, &off->department_head->subordinates[0], &emp8);
    office_employee_place(off, &off->department_head->subordinates[1], &emp9);
    office_employee_place(off, &off->department_head->subordinates[1], &emp10);
    office_employee_place(off, &off->department_head->subordinates[2], &emp11);
    office_employee_place(off, &off->department_head->subordinates[2], &emp12);
    office_employee_place(off, &off->department_head->subordinates[1].subordinates[0], &emp13);
    office_employee_place(off, &off->department_head->subordinates[1].subordinates[1], &emp14);

	struct employee* emps = NULL;
    size_t n_emps = 0;
    office_get_employees_at_level(off, 3, &emps, &n_emps);

	office_disband(off);
}

void example11() {
    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;

    struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp3 = { .name = "Employee3", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp4 = { .name = "Employee4", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp5 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp6 = { .name = "Employee6", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp1);
    office_employee_place(off, NULL, &emp2);
    office_employee_place(off, NULL, &emp3);
    office_employee_place(off, NULL, &emp4);
    office_employee_place(off, off->department_head, &emp5);
    office_employee_place(off, &off->department_head->subordinates[1], &emp6);

    struct employee* emps = NULL;
    size_t n_emps = 0;
    office_get_employees_postorder(off, &emps, &n_emps);
	for (int i = 0; i < (int)n_emps; i++) {
		printf("%s\n", emps[i].name);
	}

	office_disband(off);
}

void example12() {
    struct office* off = malloc(sizeof(struct office));
    off->department_head = NULL;

    struct employee emp1 = { .name = "Employee1", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp2 = { .name = "Employee2", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp3 = { .name = "Employee3", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp4 = { .name = "Employee4", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
    struct employee emp5 = { .name = "Employee5", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };
	struct employee emp7 = { .name = "Employee7", .supervisor = NULL, .subordinates = NULL, .n_subordinates = 0 };

    office_employee_place(off, NULL, &emp1);
    office_employee_place(off, off->department_head, &emp2);
	office_employee_place(off, off->department_head, &emp7);
    office_employee_place(off, off->department_head, &emp5);
    office_employee_place(off, &off->department_head->subordinates[0], &emp3);
	office_employee_place(off, &off->department_head->subordinates[0], &emp4);

    office_fire_employee(&off->department_head->subordinates[0]); // emp2

	printf("%s\n", off->department_head->subordinates[0].name); // emp3
	printf("%s\n", off->department_head->subordinates[0].subordinates[0].name); // emp4
	office_disband(off);
}



int main() {
    puts("example1:");
	example1();

    puts("\nexample2:");
	example2();

    puts("\nexample3:");
	example3();

    puts("\nexample4:");
	example4();

    puts("\nexample5:");
    example5();

    puts("\nexample6:");
    example6();

    puts("\nexample7:");
    example7();

    puts("\nexample8:");
    example8();

    puts("\nexample9:");
    example9();

	puts("\nexample10:");
	example10();

	puts("\nexample11:");
	example11();

	puts("\nexample12:");
	example12();

	return 0;
}
