#ifndef TEST_H
#define TEST_H

#include "matrix.h"
#include <cassert>
#include <functional>
#include <vector>

extern const std::vector<std::function<void()>> tests;

// auxilary function
void
fill_matrix_with_some_numbers(Matrix &);

void
simple_create_test();
void
right_const_indexing_test();
void
right_assign_indexing_test();
void
wrong_const_indexing_test();
void
wrong_assign_indexing_test();
void
rows_test();
void
columns_test();
void
mairix_self_comparing_test();
void
comparing_equal_matrices_test();
void
comparing_matrices_with_different_sizes_test();
void
comparing_matrices_with_different_data_test();
void
copy_constructor_test();
void
assignment_operator_test();
void
multiple_assignment_test();
void 
self_assignment_test();
void
multiplication_by_number_test();
/*----- the following 4 tests must fail if run them -----*/
void
create_matrix_with_zero_rows_test();
void
create_matrix_with_zero_cols_test();
void
create_matrix_with_inf_rows_test();
void
create_matrix_with_inf_cols_test();
/*----------------------------------------------------------*/

// perform testing
void
testing();

#endif
