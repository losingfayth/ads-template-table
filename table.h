/**
 * Declaration File for Table<T>
 * 
 * Table<T> creates objects that store a generic type data T in a 2D vector
 * of user defined size and provides methods for the user to manipulate or
 * display said data.
 * 
 * @author fayth quinn
*/

#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

template <typename T>
class Table {

	public:
		Table(unsigned int ROWS, unsigned int COLS);
		Table(unsigned int SIZE);
		Table(const Table<T> &t);

		template <typename S>
		friend std::ostream& operator<<(std::ostream&, const Table<S>&);

		T& operator()(unsigned int i, unsigned int j);

		Table operator()(unsigned int i, unsigned int j, unsigned int m,
		 unsigned int n);

		Table<T>& operator+(T (*f)(T));

		void operator=(Table<T> t);

		unsigned int get_rows();
		unsigned int get_cols();
		Table<T> append_rows(Table<T> &t);
		Table<T> append_cols(Table<T> &t);

	private:
		std::vector<std::vector<T>> tbl;
		unsigned int ROWS;
		unsigned int COLS;

};

#endif