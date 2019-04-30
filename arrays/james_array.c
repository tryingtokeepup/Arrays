#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>

typedef struct Array
{
  int capacity;    // How many elements can this array hold? It will hold the amount passed in as the arg upon creation
  int count;       // How many states does the array currently hold? as many as **elements is not null
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
  for (int i = arr->count - 1; i >= 0; i--)
  {
    arr->elements[i] = NULL;
    free(arr->elements[i]);
  }
  arr->elements = NULL;
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
  // other solution
  // arr->capacity *= 2;
  // arr->elements = realloc(arr->elements, (arr->capacity *) * sizeof(char *)); // already doubled capacity, so we don't need *2

  // Create a new element storage with double capacity <- confusing wording
  // Increase the capacity to double size              <-p what I thin it means
  arr->capacity *= 2;
  char **storage = malloc(arr->capacity * sizeof(char *));

  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++)
  {
    storage[i] = arr->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);

  // Update the elements and capacity to new values
  arr->elements = storage;
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
  // Throw a NULL if the index is greater or equal to than the current count <- needs to be updated to test case
  if (index >= arr->count)
  {
    return '\0';
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
    printf("index out of bounds\n");
    return;
  }

  // Resize the array if the number of elements is over capacity
  int orig_capacity = arr->capacity;
  if (arr->count == arr->capacity)
  {
    resize_array(arr);
    if (orig_capacity == arr->capacity)
    {
      printf("array is full and cannot be resized\n");
      return;
    }
  }

  // Move every element after the insert index to the right one position
  for (int i = arr->count - 1; i >= index; i--)
  {
    arr->elements[i + 1] = arr->elements[i];
  }

  // Copy the element and add it to the array
  arr->elements[index] = strdup(element);

  // Increment count by 1
  arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  int orig_capacity = arr->capacity;
  if (arr->count == arr->capacity)
  {
    resize_array(arr);
    if (orig_capacity == arr->capacity)
    {
      printf("%d", orig_capacity);
      printf("%d", arr->capacity);
      printf("array is full and cannot be resized\n");
      return;
    }
  }

  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = strdup(element);

  // Increment count by 1
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element)
{
  // Search for the first occurence of the element and remove it.
  int i = 0;
  while (strcmp(arr->elements[i], element) != 0 && i < arr->count) // O(k)
  {
    i++;
  }

  // if element was not found, return error
  if (i == arr->count)
  {
    printf("element not found in array\n");
    return;
  }

  // Don't forget to free its memory!
  arr->elements[i] = NULL;
  free(arr->elements[i]);

  // Shift over every element after the removed element to the left one position
  for (; i < arr->count - 1; i++) // O(k)
  {
    arr->elements[i] = arr->elements[i + 1];
  }
  // remove duplicate at end, note: i is already at end from final i++ in for loop, or while loop at worst case
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