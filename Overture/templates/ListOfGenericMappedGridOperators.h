#ifndef LISTOFGENERICMAPPEDGRIDOPERATORS_H
#define LISTOFGENERICMAPPEDGRIDOPERATORS_H "ListOfGenericMappedGridOperators.h"
class GenericMappedGridOperators;
//
//			ListOfGenericMappedGridOperators Class Template
//
//  This is the header file for a template class that stores pointers
//  of objects within an array.  The array is dynamic so that only 
//  memory and time limit the number of objects stored on the list.

//
//  Set this parameter to 1 if you find it necessary to track the lists
//  being created and destroyed.
//
#define DEBUGTEMPLATE 0


class ListOfGenericMappedGridOperators{
  private:

#if DEBUGTEMPLATE
    int theID;		// Unique id for each list object created.
#endif			// the counter static int theIDCount is used
			// to assign a value.

    int listLength;	// Number of elements in the list.
    int memAlloc;	// Current amount of memory allocated for the list.
    GenericMappedGridOperators **aList;		// Pointer to a list of pointers to object GenericMappedGridOperators.
    
    void checkRange(int) const;	// Internal range check function.
    
  public:

#if DEBUGTEMPLATE		// Should be initialized for debugging.
    static int theIDCount;	// example:
#endif				//   int ListOfGenericMappedGridOperators<stuff>::theIDCount = 0;

				// Constructors/Destructors
    ListOfGenericMappedGridOperators();			//   Default constructor.
    ListOfGenericMappedGridOperators(const ListOfGenericMappedGridOperators&);		//   Copy constructor.
   ~ListOfGenericMappedGridOperators();			//   Destructor.
    
    ListOfGenericMappedGridOperators& operator=(const ListOfGenericMappedGridOperators&);	// Equal operator (only pointers of
					// list objects copied).

//  void Iterator( void (GenericMappedGridOperators::*Function)());  // Function iterator.


			// ListOfGenericMappedGridOperators Management Functions

    void addElement(GenericMappedGridOperators &X);		// Add an object to the list.

    void addElement(GenericMappedGridOperators &X, int index);	// Add an object to the list at a
					//   given location.
    int getLength() const {return listLength;};// Get length of list.

    GenericMappedGridOperators* getElementPtr(int index) const;	// Get the pointer of the object
					//   at a given location.
    GenericMappedGridOperators& getElement(int index) const;		// Reference the object at a
    					//   a given location.
    GenericMappedGridOperators& operator[](int index) const;		// Reference the object at a
    					//   given location.
    void deleteElement(GenericMappedGridOperators &X);		// Find an element on the list
					//   and delete it.
    void deleteElement(int index);      // Delete the object at a given
					//   location in the list.
    void setElementPtr(GenericMappedGridOperators *X, int i);    // Set the list element at i
    					//   to point to X.
    void swapElements(int i, int j);    // Swap two elements for sorting
    					//   among other things.
    void clean();			// Deallocate pointer list but
					//   not objects in the list.
    void deepClean();			// Deallocate pointer list and
					//   the pointers on the list.
};

#endif
