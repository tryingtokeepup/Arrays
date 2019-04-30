#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
typedef struct Array
{
  int capacity;    // How many elements can this array hold?
  int count;       // How many states does the array currently hold?
  char **elements; // The string elements contained in the array
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array(int capacity)
{
  // Allocate memory for the Array struct
  Array *array = malloc(sizeof(struct Array));

  // Set initial values for capacity and count
  array->capacity = capacity;
  array->count = 0;

  // Allocate memory for elements
  array->elements = malloc(capacity * sizeof(char *));

  return array;
}

/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr)
{

  // Free all elements
  for (int i = 0; i < arr->capacity; i++)
  {
    //free(arr->elements[i]);
    printf("element: %s \n", arr->elements[i]);
    arr->elements[i] = NULL;
    free(arr->elements[i]);
    printf("maybe we were cool \n");
  }
  // // security freak James Page recommends nulling out all pointers and refs for security
  // arr->elements = NULL
  free(arr->elements);
  // Free array
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr)
{
  arr->capacity *= 2;
  // Create a new element storage with double capacity
  char **temp = malloc(arr->capacity * sizeof(char *));
  // Copy elements into the new storage

  int i = 0;
  while (i < arr->count) //i don't want to hit the null pointer
  {
    temp[i] = arr->elements[i];
    i++;
  }

  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = temp;
  // already ... umm... resized arr->capacity
}

/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index)
{

  // Throw an error if the index is greater or equal to than the current count
  // you can hit the null character, no biggie, because you disregard it anyway?
  if (index >= arr->count)
  {
    //printf("the index is out of range, check it real quick.\n");
    return NULL;
  }
  // Otherwise, return the element at the given index
  return arr->elements[index];
}

/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index)
{

  // Throw an error if the index is greater than the current count
  if (index > arr->count)
  {
    printf("out of bounds, check your index please!\n");
    return; // what do we return on a void?
  }
  // Resize the array if the number of elements is over capacity
  // when would we hit this? the count will always match the capacity.
  if (arr->count == arr->capacity)
  // if we have a count that is equal to the capacity, we need to allocate a lot more space for it
  {
    printf("ooh, we need to resize. \n");
    resize_array(arr);
  }
  // Move every element after the insert index to the right by one position
  // so disappointed, but i guess i have to iterate down
  for (int i = arr->count - 1; i >= index; i--)
  {
    printf("loop count %d", i);

    arr->elements[i + 1] = arr->elements[i];
  }
  // Copy the element and add it to the array
  arr->elements[index] = strdup(element);
  // Increment count by 1
  arr->count += 1;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->capacity == arr->count)
  {
    resize_array(arr);
  }
  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = element;
  // Increment count by 1
  arr->count += 1;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element)
{
  int i = 0;
  bool found = false;
  // Search for the first occurence of the element and remove it.
  for (; i < arr->count && !found; i++)
  {
    if (strcmp(arr->elements[i], element) == 0)
    // if strcmp returns a 0, that means we found a match!
    {
      found = true;
      arr->elements[i] = NULL;
      i--;
      //free(arr->elements[i]);
    }
  }
  // Don't forget to free its memory!
  // i did daddy
  // Shift over every element after the removed element to the left one position
  for (; i < arr->count - 1; i++)
  {
    arr->elements[i] = arr->elements[i + 1];
  }
  arr->elements[i] = NULL;
  free(arr->elements[i]);

  // Decrement count by 1
  arr->count--;
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("[");
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1)
    {
      printf(",");
    }
  }
  printf("]\n");
}

#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
