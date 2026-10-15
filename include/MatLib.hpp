#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

using u32 = unsigned int;
using f32 = float;



class Matrix {
  u32 rows,cols;
  vector<f32> data;
  public:
  Matrix(u32 r,u32 c):rows(r),cols(c),data((size_t)r*c){}
  f32& operator()(u32 ro,u32 co) {return data[(size_t)cols*i + j];}


  Matrix operator*(f32 scalar) const {
    Matrix out(rows,cols);
    size_t n = data.size();
    for(size_t i = 0;i<n;i++)out.data[i]*=scalar;
    return out;
  }

  friend Matrix operator*(f32 scalar,const Matrix& m){
    return m*scalar;
  }

};




int main() {
    Matrix m(3, 3);
    f32 init[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < 9; i++)
        m.data[i] = init[i];

    Matrix r = m * 2.5f;   // or 2.5f * m

    for (size_t idx = 0; idx < r.data.size(); idx++)
        cout << r.data[idx] << '\n';

    return 0;
}
