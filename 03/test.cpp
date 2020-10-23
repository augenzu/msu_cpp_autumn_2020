#include "test.h"
#include <iostream>

// auxilary function
void
fill_matrix_with_some_numbers(Matrix &m)
{
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.columns(); ++j) {
            m[i][j] = 10 * i + j;
        }
    }
}

void
simple_create_test()
{
    Matrix m;
}

void
right_const_indexing_test()
{
    Matrix m(2, 3);
    int i = m[0][0];
    assert(i == m[0][0]);
}

void
right_assign_indexing_test()
{
    Matrix m(2, 3);
    m[1][2] = 1;
    assert(m[1][2] == 1);
}

void
wrong_const_indexing_test()
{
    Matrix m(2, 3);
    try {
        int i = m[2][0];
    } catch (const std::out_of_range &except) {
        assert(except.what() == std::string("Row index is out of range."));
    }
}

void
wrong_assign_indexing_test()
{
    Matrix m(2, 3);
    try {
        m[0][3] = 1;
    } catch (const std::out_of_range &except) {
        assert(except.what() == std::string("Column index is out of range."));
    }
}

void
rows_test()
{
    Matrix m(2, 3);
    assert(m.rows() == 2);
}

void
columns_test()
{
    Matrix m(2, 3);
    assert(m.columns() == 3);
}

void
mairix_self_comparing_test()
{
    Matrix m(3, 4);
    assert(m == m);
}

void
comparing_equal_matrices_test()
{
    Matrix m1(3, 4);
    Matrix m2(3, 4);
    fill_matrix_with_some_numbers(m1);
    fill_matrix_with_some_numbers(m2);

    assert(m1 == m2);
}

void
comparing_matrices_with_different_sizes_test()
{
    Matrix m1(2, 3);
    Matrix m2(2, 4);
    assert(m1 != m2);
}

void
comparing_matrices_with_different_data_test()
{
    Matrix m1(3, 4);
    Matrix m2(3, 4);
    fill_matrix_with_some_numbers(m1);
    fill_matrix_with_some_numbers(m2);

    m1[0][0] = -1;
    assert(m1 != m2);
}

void
copy_constructor_test()
{
    Matrix m(2, 3);
    m[0][0] = 1;
    Matrix copy_m{m};
    assert(copy_m == m);

    copy_m[0][0] = -1;
    // copy constructor should make full copy of original`s data, not just copy the pointer
    // then changes to the copy matrix and changes to the original 
    // do not affect each other
    assert(m[0][0] == 1);
}

void
assignment_operator_test()
{
    Matrix m1(2, 3);
    Matrix m2(11, 6);
    m2[0][0] = 1;

    m1 = m2;
    assert(m1 == m2);

    m2[0][0] = -1;
    // assignment operator should make full copy of original`s data, not just copy the pointer
    // then changes to the assigned matrix and changes to the original 
    // do not affect each other
    assert(m1[0][0] == 1);
}

void
multiple_assignment_test()
{
    Matrix m1, m2, m3(2, 3);
    m1 = m2 = m3;
    assert(m1 == m3);
}

void 
self_assignment_test()
{
    Matrix m(3, 4);
    fill_matrix_with_some_numbers(m);

    Matrix copy_m{m};
    m = m;
    assert(m == copy_m);
}

void
multiplication_by_number_test()
{
    Matrix m(3, 4);
    fill_matrix_with_some_numbers(m);

    Matrix multed_by_hand{m};
    for (size_t i = 0; i < multed_by_hand.rows(); ++i) {
        for (size_t j = 0; j < multed_by_hand.columns(); ++j) {
            multed_by_hand[i][j] *= 10;
        }
    }

    assert((m *= 10) == multed_by_hand);
}

/*----- the following 4 tests must fail if run them -----*/

void
create_matrix_with_zero_rows_test()
{
    Matrix m(0, 1);
}

void
create_matrix_with_zero_cols_test()
{
    Matrix m(1,0);
}

void
create_matrix_with_inf_rows_test()
{
    Matrix m(-1, 1);
}

void
create_matrix_with_inf_cols_test()
{
    Matrix m(1, -1);
}

/*----------------------------------------------------------*/

const std::vector<std::function<void()>> tests{
    simple_create_test,
    right_const_indexing_test,
    right_assign_indexing_test,
    wrong_const_indexing_test,
    wrong_assign_indexing_test,
    rows_test,
    columns_test,
    mairix_self_comparing_test,
    comparing_equal_matrices_test,
    comparing_matrices_with_different_sizes_test,
    comparing_matrices_with_different_data_test,
    copy_constructor_test,
    assignment_operator_test,
    multiple_assignment_test,
    self_assignment_test,
    multiplication_by_number_test    
};

void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}
