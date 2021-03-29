#include "student.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * student.c contains functions that are used to modify
 * and manage different Students (a type of structure
 * with 2 char * fields). These functions can be used to
 * dynamically allocate space for Students and each of the
 * fields for each Student. They also modify the fields of
 * any given Student through new names or nicknames. Then,
 * there are other string focused applications like printing
 * or comparing names of Students.
 */

/*
 * init_student takes an existing student and assigns them a
 * first_name and last_name. It frees any space the fields of
 * the student was initially using and allocates only the bare
 * minimum space necessary to hold the string to each field.
 */
void init_student(Student *const student, const char first_name[],
                  const char last_name[]) {
  if (student == NULL || first_name == NULL || last_name == NULL) {
    return;
  }

  free(student->first_name);
  free(student->last_name);

  student->first_name = malloc((strlen(first_name) + 1) * sizeof(char));
  student->last_name = malloc((strlen(last_name) + 1) * sizeof(char));

  strcpy(student->first_name, first_name);
  strcpy(student->last_name, last_name);
}

/*
 * create_student creates a new student and returns a pointer to
 * that student. It also dynamically allocates space to and declares
 * the two name fields of the new student.
 */
Student *create_student(const char first_name[], const char last_name[]) {
  Student *student = malloc(sizeof(Student));
  if (first_name == NULL || last_name == NULL) {
    return NULL;
  }

  student->first_name = malloc((strlen(first_name) + 1) * sizeof(char));
  student->last_name = malloc((strlen(last_name) + 1) * sizeof(char));
  strcpy(student->first_name, first_name);
  strcpy(student->last_name, last_name);

  return student;
}

/*
 * print_student, after checking whether or not a student has a first
 * and last name, prints out the names it does have
 * in the format "<last_name>, <first_name>"
 */
void print_student(Student student) {
  if (student.last_name != NULL) {
    printf("%s, ", student.last_name);
  }
  if (student.first_name != NULL) {
    printf("%s", student.first_name);
  }
}

/*
 * change_first_name frees up the memory that the first name of the student
 * in question points to and then allocates the necessary new memory before
 * altering the name itself.
 */
unsigned int change_first_name(Student *const student, const char new_name[]) {
  if (student == NULL || new_name == NULL) {
    return 0;
  }

  free(student->first_name);
  student->first_name = malloc((strlen(new_name) + 1) * sizeof(char));
  strcpy(student->first_name, new_name);

  return 1;
}

/*
 * change_last_name frees up the memory that the last name of the student
 * in question points to and then allocates the necessary new memory before
 * altering the name itself.
 */
unsigned int change_last_name(Student *const student, const char new_name[]) {
  if (student == NULL || new_name == NULL) {
    return 0;
  }

  free(student->last_name);
  student->last_name = malloc((strlen(new_name) + 1) * sizeof(char));
  strcpy(student->last_name, new_name);

  return 1;
}

/*
 * add_nickname appends a nickname in the format " (<nickname>)" to
 * the first name field of the student in question. It also dynamically
 * allocates space to fit the nickname into the first_name field.
 */
unsigned int add_nickname(Student *const student, const char nickname[]) {
  if (student == NULL || nickname == NULL) {
    return 0;
  }
  if (strchr(student->first_name, '(') != NULL) {
    return 0;
  }

  student->first_name =
      realloc(student->first_name,
              (strlen(student->first_name) + strlen(nickname) + 4) * sizeof(char));

  strcat(student->first_name, " (");
  strcat(student->first_name, nickname);
  strcat(student->first_name, ")");

  return 1;
}

/*
 * compare first compares the last_name for each student
 * then compares based on first name if the last names are
 * the same.
 */
int compare(Student student1, Student student2) {
  int first = strcmp(student1.first_name, student2.first_name);
  int last = strcmp(student1.last_name, student2.last_name);

  if (last == 0) {
    return first;
  } else {
    return last;
  }
}

/*
 * reset_student frees up the memory used by the fields
 * of the student in question and then sets them to NULL.
 */
unsigned int reset_student(Student *const student) {
  if (student == NULL) {
    return 0;
  }

  free(student->first_name);
  free(student->last_name);

  student->first_name = NULL;
  student->last_name = NULL;

  return 1;
}

/*
 * free_student frees the fields of the student in question
 * and also the student struct itself. All space related to the
 * student is freed up in this process and the student cannot
 * be accessed again. The pointer to the now non-existent
 * student is also set to NULL.
 */
unsigned int free_student(Student **const student) {
  if (student == NULL || *student == NULL) {
    return 0;
  }

  free((**student).first_name);
  free((**student).last_name);
  free(*student);
  *student = NULL;

  return 1;
}
