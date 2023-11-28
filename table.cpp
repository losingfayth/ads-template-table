/**
 * Implementation File for Table<T>
 * 
 * Table<T> creates objects that store a generic type data T in a 2D vector
 * of user defined size and provides methods for the user to manipulate or
 * display said data.
 * 
 * Uses unsigned integers throughout to prevent attempts to access data beyond
 * the Table<T>'s scope and to allow the Table<T> object to store more data.
 * This can produce warnings and possibly cause issues when users provide signed
 * integers for comparison to the object's ROWS or COLS members, but should only
 * produce compiler warnings in the vast majority of cases.
 * 
 * @author fayth quinn
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include "table.h"

using namespace std;

/**
 * CONSTRUCTOR
 * Two-Variable Constructor
 * 
 * Creates a Table<T> object of size ROWS by COLS
 * 
 * @param ROWS Desired number of table rows
 * @param COLS Desired number of table columns
*/
template <typename T>
Table<T>::Table(unsigned int ROWS, unsigned int COLS) {

	this->ROWS = ROWS;
	this->COLS = COLS;

	vector<vector<T>> tmp(ROWS, vector<T>(COLS));
	this->tbl = tmp;

}

/**
 * CONSTRUCTOR
 * Single Variable Constructor
 * 
 * Creates a Table<T> object of size SIZE by SIZE
 * 
 * @param SIZE Desired number of table rows and columns
*/
template <typename T>
Table<T>::Table(unsigned int SIZE) {

	this->ROWS = SIZE;
	this->COLS = SIZE;

	vector<vector<T>> tmp(ROWS, vector<T>(COLS));
	this->tbl = tmp;

}

/**
 * CONSTRUCTOR
 * Copy Constructor
 * 
 * Creates a Table<T> object with the size and data of a given table
 * 
 * @param t Reference to a Table<T> object to be copied
*/
template <typename T>
Table<T>::Table(const Table<T> &t) {

	// Copy the structure of the given object
	ROWS = t.ROWS;
	COLS = t.COLS;
	
	vector<vector<T>> tmp(ROWS, vector<T>(COLS));
	this->tbl = tmp;

	// Copy the data of the given object
	for (unsigned int i = 0; i < ROWS; i++) {
		for (unsigned int j = 0; j < COLS; j++) {
			tbl[i][j] = t.tbl[i][j];
		}
	}
}

/**
 * Allows the user to access the value of ROWS,
 * representing this table's number of rows across.
 * 
 * @return This Table<T>'s ROWS attribute
*/
template <typename T>
unsigned int Table<T>::get_rows() { return ROWS; }

/**
 * Allows the user to access the value of COLS,
 * representing this table's number of columns down.
 * 
 * @return This Table<T>'s COLS attribute
*/
template <typename T>
unsigned int Table<T>::get_cols() { return COLS; }

/**
 * Allows the user to output this Table<T> objects data formatted correctly.
 * 
 * @param out A reference to an ostream object
 * @param t A reference to a Table<T> object
 * @return An ostream object containing the formatted Table<T> data
*/
template <typename T>
ostream& operator<<(ostream& out, Table<T>& t) {

	// Gets the width of the referenced ostream object and saves it
	streamsize w = out.width();

	out << endl;

	// Adds the values of t to out, formatted into a table
	// and giving each element a the width of the out object
	for (unsigned int i = 0; i < t.get_rows(); i++) {
		for (unsigned int j = 0; j < t.get_cols(); j++) {
			out << setw(w) << t(i,j) << " ";
		}
		out << endl;
	}

	return out;

}

/**
 * Allows the user to modify all the data in the table using a given function.
 * 
 * @param f A pointer to a function that modifies data of type T
 * and returns data of type T
 * @return A reference to a new Table<T> with the modified data
*/
template <typename T>
Table<T>& Table<T>::operator+(T (*f)(T)) {

	// Declare a static Table<T> object so that a reference may be returned
	// out of scope.
	static Table<T> t(ROWS, COLS);

	// Feeds the data of this Table<T> modified by f into the corresponding
	// location on the new table.
	for (unsigned int i = 0; i < ROWS; i++) {
		for (unsigned int j = 0; j < COLS; j++) {
			t(i,j) = f(tbl[i][j]);
		}
	}

	return t;

}

/**
 * Allows the user to view or modified the data of this Table<T>
 * at the given location.
 * 
 * @param i The row index of the requested data
 * @param j The column index of the requested data
 * @return A pointer to the data at the given location
*/
template <typename T>
T& Table<T>::operator()(unsigned int i, unsigned int j) { 
	
	// If row or column index is out of bounds, set to last row/column
	if (i >= ROWS) i = ROWS - 1;
	if (j >= COLS) j = COLS - 1;
	
	return tbl[i][j];

}

/**
 * Creates a new Table<T>, a subtable of this Table<T>, with data taken from the
 * table between the given indexes.
 * 
 * @param i The beginning row index
 * @param j The beginning column index
 * @param m The ending row index
 * @param n The ending column index
 * @return A new Table<T> extracted from this Table<T> between the given indexes
*/
template <typename T>
Table<T> Table<T>::operator()(unsigned int i, unsigned int j, unsigned int m,
 unsigned int n) {

	// If an invalid row/column index range is given, modify the end of the
	// range to be the last row/column.
	if (i > m || m >= ROWS) m = ROWS - 1;
	if (j > n || n >= COLS) n = COLS - 1;

	// Declare a static Table<T> object so that a reference may be returned
	// out of scope.
	static Table<T> t((m - i) + 1, (n - j) + 1);

	// Copy the data from the given index range of this Table<T> to the
	// beginning of the new Table<T>.
	for (unsigned int ii = 0; ii < t.get_rows(); ii++, i++) {
		for (unsigned int jj = 0, jjj = j; jj < t.get_cols(); jj++, jjj++) {
			t(ii, jj) = tbl[i][jjj];
		}
	}

	return t;

}

/**
 * Sets this Table<T> to have the same data and structure as a given Table<T>
 * 
 * @param t The Table<T> to copy
*/
template <typename T>
void Table<T>::operator=(Table<T> t) {

	// Re-assign the variables of this object to be equal to
	// those of the given object
	ROWS = t.get_rows();
	COLS = t.get_cols();

	vector<vector<T>> tmp(ROWS, vector<T>(COLS));
	this->tbl = tmp;

	// Copy the data from the given object to this object
	for (unsigned int i = 0; i < ROWS; i++) {
		for (unsigned int j = 0; j < COLS; j++) {
			tbl[i][j] = t(i,j);
		}
	}
}

/**
 * Combines the data of a given Table<T> with the data of this Table<T>
 * to create a new Table<T>. The rows of the given Table<T> are appended to the
 * end of this Table<T>. If the given object has more columns that this object,
 * the additional columns are discarded.
 * 
 * @param t A reference to the Table<T> whose rows to append
 * @return A new Table<T> combining the two Table<T> objects
*/
template <typename T>
Table<T> Table<T>::append_rows(Table<T> &t) {

	// The new Table<T> to be returned
	Table<T> tt(ROWS + t.ROWS, COLS);

	for (unsigned int i = 0; i < tt.get_rows(); i++) {
		for (unsigned int j = 0; j < tt.get_cols(); j++) {
			// Assigns data from this Table<T> while in its scope
			if (i < ROWS) {
				tt(i,j) = tbl[i][j];
			}
			// Assigns data from the given Table<T> when it exceeds this
			// object's scope
			else {
				tt(i,j) = t(i - ROWS, j);
			}
		}
	}

	return tt;

}

/**
 * Combines the data of a given Table<T> with the data of this Table<T>
 * to create a new Table<T>. The columns of the given Table<T> are appended to
 * the end of this Table<T>. If the given object has more rows than this 
 * object, the additional rows are discarded.
 * 
 * @param t A reference to the Table<T> whose columns to append
 * @return A new Table<T> combining the two Table<T> objects
*/
template <typename T>
Table<T> Table<T>::append_cols(Table<T> &t) {

	// The new Table<T> to be returned
	Table<T> tt(ROWS, (COLS + t.COLS));

	for (unsigned int i = 0; i < tt.get_rows(); i++) {
		for (unsigned int j = 0; j < tt.get_cols(); j++) {
			// Assigns data from this Table<T> while in its scope
			if (j < COLS) {
				tt(i,j) = tbl[i][j];
			}
			// Assigns data from the given Table<T> when it exceeds this
			// object's scope
			else {
				tt(i,j) = t(i, j - COLS);
			}
		}
	}

	return tt;

}

/**
 * 
 * Author's Note:
 * 
 * 	I did not think that Java-style doc comments were standard for C++.
 * 	However, my IDE says they are valid and I've grown to like them, so I
 * 	have used them throughout this project. Let me know if you'd rather I not,
 * 	as I can see that you do not use them in your files.
 * 
 * 	I would likely have a concrete answer for this already if I had not
 * 	transferred in the previous C++ course, but alas I did do that, so I'm
 * 	missing much of the context of that course in regards to coding practices
 * 	preferred for C++.
 * 
 * 	Anyway, enjoy. There are some things I would go ahead and modify if I were
 * 	graced with more time, but nothing that would change the output of the code.
 * 	Mainly, I'd not initialize the class's vector<> object like I do. I'd
 *	likely make it a vector pointer instead. I tried an implementation, but I
 *	decided to stick to what was working.
 * 	
 * 	all the best,
 * 	fayth quinn :D
 * 
*/