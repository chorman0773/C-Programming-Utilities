#ifndef UTIL_COLLECT_LIST_H_2019_12_01_12_35
#define UTIL_COLLECT_LIST_H_2019_12_01_12_35

#include <stddef.h>

#ifdef __cplusplus
extern"C"{
#endif

/**
 * Opaque type representing a LinkedList.
 * The LinkedList can be traversed forward or backward.
 */
typedef struct LinkedList LinkedList;
/**
 * Opaque type representing a handle to an element in a linked list.
 * Iterators are invalidated when the List is freed or cleared, or the element the iterator is bound to is removed/popped.
 */
typedef struct Iterator Iterator;
typedef struct ArrayList ArrayList;

/**
 * Constructs a new (type-erased) Linked List with a given value deallocator.
 * @param deallocFn The function to call when clearing or freeing the list. If no deallocation is necessary, NULL may be passed
 * @return A newly allocated LinkedList, with no elements
 *
 * Note: All LinkedList functions that take a LinkedList require a Non-null LinkedList* that was returned by a call to this function, and not freed.
 * All LinkedListFunctions that take an Iterator require a non-null Iterator* that is valid. .
 * A program which violates any of these preconditions has undefined behavior.
 */
LinkedList* LinkedList_new(void(*deallocFn)(void*));

/**
 * Frees a LinkedList created by a call to LinkedList_new.
 * If the values have non-trivial destruciton and deallocation, each element is destroyed as though by a call to the deallocFn.
 * The LinkedList itself is then deallocated.
 *
 * Complexity Guarantee: O(n).
 */
void LinkedList_free(LinkedList*);

/**
 * Destroys each element of a LinkedList, but does not free the List.
 *
 * Complexity Guarantee: O(n)
 */
void LinkedList_clear(LinkedList*);

/**
 * Obtains a handle to the beginning of the linked list, or NULL if the list is empty.
 *
 * Complexity Guarantee: O(1)
 */
Iterator* LinkedList_begin(LinkedList*);

/**
 * Obtains a handle to the element following the element represented by the given handle, or NULL if the handle represents the Last element
 *
 * Complexity Guarantee: O(1)
 */
Iterator* LinkedList_next(Iterator*);

/**
 * Obtains a handle to the element prior to the element represented by the given handle, or NULL if the handle represents the Last element
 *
 * Complexity Guarantee: O(1)
 */
Iterator* LinkedList_prev(Iterator* it);

/**
 * Inserts a new element after the element represented by the given handle, and returns a handle to that element.
 *
 * Complexity Guarantee: O(1)
 */
Iterator* LinkedList_insert(Iterator*,void*);
/**
 * Inserts a new element before the element represented by the given handle, and returns a handle to that element.
 *
 * Complexity Guarantee: O(1)
 */
Iterator* LinkedList_insertBefore(Iterator*,void*);
/**
 * Obtains the element represented by the given handle.
 *
 * Complexity Guarnatee: O(1)
 */
void* LinkedList_dereference(Iterator*);

/**
 * Removes (and does not return) the element represented by the given handle. The Iterator passed to this function is invalidated.
 *
 * Complexity Guarnatee: O(1)
 */
void LinkedList_remove(Iterator*);

/**
 * Inserts a new element at the position defined by the ascending order by cmpFn on list.
 * @param list A LinkedList which is ordered by cmpFn
 * @param cmpFn The function which is used to compare elements. Shall be a total order comparator of the elements in the list, such that cmpFn(a,b) is less than 0 if a is logically less than b, greater than 0 if a is logically greater than b, and 0 if a is logically equivalent to b
 * @param data The new element to insert
 * @return A handle to the new element
 *
 * Preconditions: In addition to the normal requirements, list shall be in ascending order as specified by cmpFn, or the behavior is undefined.
 * Postconditions: list is in ascending order by cmpFn.
 */
Iterator* LinkedList_insertOrdered(LinkedList* list,int(*cmpFn)(const void*,const void*),void* data);
/**
 * Inserts a new element to this list, at the back
 *
 * @return A handle to the new element
 */
Iterator* LinkedList_pushBack(LinkedList*,void*);
/**
 * Obtains a handle to the last element, or NULL if the List is empty
 */
Iterator* LinkedList_back(LinkedList*);
/**
 * Removes the last Element from the list, and returns the new back of the list, or NULL if the list is now empty.
 *
 * This function invalidates any iterators to the last element of the List.
 */
Iterator* LinkedList_popBack(LinkedList*);

ArrayList* ArrayList_new(void(*destructor)(void*),void(*copy)(void*,const void*),void(*relocate)(void*,void*),size_t valLen);
void ArrayList_add(ArrayList*,const void*);
void* ArrayList_data(ArrayList*);
void* ArrayList_get(ArrayList*,size_t pos);
void ArrayList_free(ArrayList*);
size_t ArrayList_length(ArrayList*);
void ArrayList_clear(ArrayList*);

#ifdef __cplusplus
};
#endif

#endif
