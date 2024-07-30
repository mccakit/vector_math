#pragma once

#include <fstream>
#include <vector>
#include <ranges>

/*A naming alias for std::vector is used to avoid confusing an array with a vector*/
namespace my_std
{
    template<typename T>
    using dynamic_array = std::vector<T>;
}

/*This vector class can be of any size, +,* operators are overloaded to make vectors operations simpler to write.
() operator is overloaded so it can provide access to private elements of the vector.*/
class Vector
{
public:
    my_std::dynamic_array<double> elements{};

    Vector(const std::initializer_list<double>& data):
        elements{data}
    {
    }

    Vector(const my_std::dynamic_array<double>& data):
        elements{data}
    {
    }

    double& operator ()(const int index)
    {
        return elements[index];
    }

    double operator ()(const int index) const
    {
        return elements[index];
    }

    int element_count() const
    {
        return static_cast<int>(elements.size());
    }

    operator my_std::dynamic_array<double>() const
    {
        return elements;
    }
};

std::ostream& operator <<(std::ostream& out, const Vector& vector)
{
    for (int index{0}; index < vector.element_count(); ++index)
    {
        out << vector(index) << "\n";
    }
    return out;
}

Vector operator *(const Vector& ls_vector, const double& rs_factor)
{
    Vector result = ls_vector;
    for (int index{0}; index < ls_vector.element_count(); ++index)
    {
        result(index) *= rs_factor;
    }
    return result;
}

Vector operator *(const double& ls_factor, const Vector& rs_vector)
{
    Vector result = rs_vector;
    for (int index{0}; index < rs_vector.element_count(); ++index)
    {
        result(index) *= ls_factor;
    }
    return result;
}

void operator *=(Vector& ls_vector, const double& rs_factor)
{
    for (int index{0}; index < ls_vector.element_count(); ++index)
    {
        ls_vector(index) *= rs_factor;
    }
}

Vector operator +(const Vector& ls_vector, const Vector& rs_vector)
{
    Vector result = ls_vector;
    for (int index{0}; index < ls_vector.element_count(); ++index)
    {
        result(index) += rs_vector(index);
    }
    return result;
}

void operator +=(Vector& ls_vector, const Vector& rs_vector)
{
    for (int index{0}; index < ls_vector.element_count(); ++index)
    {
        ls_vector(index) += rs_vector(index);
    }
}

Vector operator -(const Vector& ls_vector, const Vector& rs_vector)
{
    Vector result = ls_vector;
    for (int index{0}; index < ls_vector.element_count(); ++index)
    {
        result(index) -= rs_vector(index);
    }
    return result;
}

void operator -=(Vector& ls_vector, const Vector& rs_vector)
{
    for (int index{0}; index < ls_vector.element_count(); ++index)
    {
        ls_vector(index) -= rs_vector(index);
    }
}

class Matrix
{
public:
    my_std::dynamic_array<Vector> vectors{};

    Matrix(const std::initializer_list<Vector>& data):
        vectors{data}
    {
    }

    Matrix(const int size):
        vectors{my_std::dynamic_array<Vector>(size, my_std::dynamic_array<double>(size))}
    {
    }

    double& operator ()(const int row, const int col)
    {
        return vectors[col](row);
    }

    double operator ()(const int row, const int col) const
    {
        return vectors[col](row);
    }

    Vector& operator ()(const int col)
    {
        return vectors[col];
    }

    Vector operator ()(const int col) const
    {
        return vectors[col];
    }

    int vector_count() const
    {
        return static_cast<int>(vectors.size());
    }

    int vector_length() const
    {
        return vectors[0].element_count();
    }
};

std::ostream& operator <<(std::ostream& out, const Matrix& matrix)
{
    for (int row{0}; row < matrix.vector_length(); ++row)
    {
        for (int col{0}; col < matrix.vector_count(); ++col)
        {
            out << matrix(row, col) << " ";
        }
        out << "\n";
    }
    return out;
}

Matrix operator *(Matrix ls_matrix, const double& rs_factor)
{
    for (auto& vector: ls_matrix.vectors)
    {
        vector *= rs_factor;
    }
    return ls_matrix;
}

Matrix operator *(const double& ls_factor, Matrix rs_matrix)
{
    for (auto& vector: rs_matrix.vectors)
    {
        vector *= ls_factor;
    }
    return rs_matrix;
}

void operator *=(Matrix& ls_matrix, const double& rs_factor)
{
    for (auto& vector: ls_matrix.vectors)
    {
        vector *= rs_factor;
    }
}

Matrix operator +(Matrix ls_matrix, const Matrix& rs_matrix)
{
    for (int row{0}; row < ls_matrix.vector_length(); ++row)
    {
        for (int col{0}; col < ls_matrix.vector_count(); ++col)
        {
            ls_matrix(row, col) += rs_matrix(row, col);
        }
    }
    return ls_matrix;
}

void operator +=(Matrix& ls_matrix, const Matrix& rs_matrix)
{
    for (int row{0}; row < ls_matrix.vector_length(); ++row)
    {
        for (int col{0}; col < ls_matrix.vector_count(); ++col)
        {
            ls_matrix(row, col) += rs_matrix(row, col);
        }
    }
}

Matrix operator -(Matrix ls_matrix, const Matrix& rs_matrix)
{
    for (int row{0}; row < ls_matrix.vector_length(); ++row)
    {
        for (int col{0}; col < ls_matrix.vector_count(); ++col)
        {
            ls_matrix(row, col) -= rs_matrix(row, col);
        }
    }
    return ls_matrix;
}

void operator -=(Matrix& ls_matrix, const Matrix& rs_matrix)
{
    for (int row{0}; row < ls_matrix.vector_length(); ++row)
    {
        for (int col{0}; col < ls_matrix.vector_count(); ++col)
        {
            ls_matrix(row, col) -= rs_matrix(row, col);
        }
    }
}

Vector operator *(const Matrix& ls_matrix, const Vector& rs_vector)
{
    Vector transformed_vector{my_std::dynamic_array<double>(rs_vector.element_count())};
    for (int row{0}; row < rs_vector.element_count(); ++row)
    {
        transformed_vector += rs_vector(row) * ls_matrix(row);
    }
    return transformed_vector;
}

Matrix operator *(const Matrix& ls_matrix, Matrix rs_matrix)
{
    for (int col{0}; col < rs_matrix.vector_length(); ++col)
    {
        rs_matrix(col) = ls_matrix * rs_matrix(col);
    }
    return rs_matrix;
}

Matrix identity_matrix(const int size)
{
    Matrix identity_matrix{size};
    for (int index{0}; index < size; ++index)
    {
        identity_matrix(index, index) = 1;
    }
    return identity_matrix;
}

Matrix transpose(const Matrix& matrix)
{
    Matrix result {matrix.vector_count()};
    for (int row {0}; row < matrix.vector_length(); ++row)
    {
        for (int col {0}; col < matrix.vector_count(); ++col)
        {
            result(col, row) = matrix(row, col);
        }
    }

    return result;
}

Matrix submatrix(const Matrix& matrix, const int& ignored_row_index, const int& ignored_col_index)
{
    Matrix result{matrix.vector_count()-1};
    for (int col{0}; col < matrix.vector_count(); ++col)
    {
        for (int row{0}; row < matrix.vector_count(); ++row)
        {
            if(row > ignored_row_index and col > ignored_col_index)
            {
                result(row-1, col-1) = matrix(row, col);
            }
            else if(row > ignored_row_index and col < ignored_col_index)
            {
                result(row-1, col) = matrix(row, col);
            }
            else if(row < ignored_row_index and col > ignored_col_index)
            {
                result(row, col-1) = matrix(row, col);
            }
            else if(row < ignored_row_index and col < ignored_col_index)
            {
                result(row, col) = matrix(row, col);
            }
        }
    }
    return result;
}
double determinant(const Matrix& matrix);
double minor(const Matrix& matrix, const int& ignored_row_index, const int& ignored_col_index)
{
    return determinant(submatrix(matrix, ignored_row_index, ignored_col_index));
}
double cofactor(const Matrix& matrix, const int& ignored_row_index, const int& ignored_col_index)
{
    if ((ignored_row_index + ignored_col_index)%2 != 0)
    {
        return minor(matrix, ignored_row_index, ignored_col_index) * -1;
    }
    else
    {
        return minor(matrix,ignored_row_index,ignored_col_index);
    }
}
double determinant(const Matrix& matrix)
{
    if (matrix.vector_count() == 2)
    {
        return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1,0);
    }
    else
    {
        double result{0};
        for (int row {0}; row < matrix.vector_length(); ++row)
        {
            result += cofactor(matrix, row, 0) * matrix(row, 0);
        }
        return result;
    }
}
Matrix inverse(const Matrix& matrix)
{
    Matrix result = matrix;
    for (int col{}; col < matrix.vector_count(); ++col)
    {
        for (int row{}; row < matrix.vector_length(); ++row)
        {
            result(row, col) = cofactor(matrix, row, col);
        }
    }
    result = transpose(result);
    result *= 1/determinant(matrix);
    return result;
}
