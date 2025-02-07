#pragma once

namespace matrix {

void add_rows(matf& L, vecf& P, size_t to_add_to, size_t added, double scalar);
void subtract_rows(matf& L, vecf& P, size_t to_subtracted_from, size_t subtracted, double scalar);
void multiply_rows(matf& L, vecf& P, size_t row, double scalar);
void divide_rows(matf& L, vecf& P, size_t row, double scalar);
void swap_rows(matf& L, vecf& P, size_t row1, size_t row2);

}