#include <iostream>
#include <sstream>


#include <simd.h>

using namespace ASC_HPC;
using std::cout, std::endl;

auto Func1 (SIMD<double> a, SIMD<double> b)
{
  return a+b;
}

auto Func2 (SIMD<double,4> a, SIMD<double,4> b)
{
  return a+3*b;
}

auto Func3 (SIMD<double,4> a, SIMD<double,4> b, SIMD<double,4> c)
{
  return FMA(a,b,c);
}


auto Load (double * p)
{
  return SIMD<double,2>(p);
}

auto LoadMask (double * p, SIMD<mask64,2> m)
{
  return SIMD<double,2>(p, m);
}

auto TestSelect (SIMD<mask64,2> m, SIMD<double,2> a, SIMD<double,2> b)
{
  return Select (m, a, b);
}

SIMD<double,2> TestHSum (SIMD<double,4> a, SIMD<double,4> b)
{
  return HSum(a,b);
}



int main()
{
  SIMD<double,4> a(1.,2.,3.,4.);
  SIMD<double,4> b(2.5);
  SIMD<double,4> c(1.0);
  
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "a+b = " << a+b << endl;

  cout << "HSum(a) = " << HSum(a) << endl;
  cout << "HSum(a,b) = " << HSum(a,b) << endl;

  
  auto sequ = IndexSequence<int64_t, 4>();
  cout << "sequ = " << sequ << endl;
  auto mask = (2 >= sequ);
  cout << "2 >= " << sequ << " = " << mask << endl;

  {
    double a[] = { 10, 10, 10, 10 };
    SIMD<double,4> sa(&a[0], mask);
    cout << "sa = " << sa << endl;
  }

  cout << "Select(mask, a, b) = " << Select(mask, a,c) << endl;

  auto d = a*b+c;
  cout << "d = " << d << endl;

  auto e = a/b-c;
  cout << "e = " << e << endl;

  auto matrix_row_1 = SIMD<double,4>(1,2,3,4);
  auto matrix_row_2 = SIMD<double,4>(5,6,7,8);
  auto matrix_row_3 = SIMD<double,4>(9,10,11,12);
  auto matrix_row_4 = SIMD<double,4>(13,14,15,16);

  auto copy_to_transpose_1 = SIMD<double,4>();
  auto copy_to_transpose_2 = SIMD<double,4>();
  auto copy_to_transpose_3 = SIMD<double,4>();
  auto copy_to_transpose_4 = SIMD<double,4>();
  
  Transpose(matrix_row_1, matrix_row_2, matrix_row_3, matrix_row_4, copy_to_transpose_1, copy_to_transpose_2, copy_to_transpose_3, copy_to_transpose_4);

  cout << "matrix_row_1 = " << matrix_row_1 << endl;
  cout << "matrix_row_2 = " << matrix_row_2 << endl;
  cout << "matrix_row_3 = " << matrix_row_3 << endl;
  cout << "matrix_row_4 = " << matrix_row_4 << endl;

  cout << "copy_to_transpose_1 = " << copy_to_transpose_1 << endl;
  cout << "copy_to_transpose_2 = " << copy_to_transpose_2 << endl;
  cout << "copy_to_transpose_3 = " << copy_to_transpose_3 << endl;
  cout << "copy_to_transpose_4 = " << copy_to_transpose_4 << endl;
}
