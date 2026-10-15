#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;

using u32 = unsigned int;
using f32 = float;
using u64 = unsigned long long;


class Matrix {
  public:
  u32 rows,cols;
  vector<f32> data;
  public:
  Matrix(u32 r,u32 c):rows(r),cols(c),data((size_t)r*c){}
  f32& operator()(u32 ro,u32 co) {return data[(size_t)cols*ro + co];}
  f32 operator()(u32 ro,u32 co){return data[(size_t)cols*ro + co];}

  Matrix operator*(f32 scalar) const {
    Matrix out(rows,cols);
    size_t n = data.size();
    for(size_t i = 0;i<n;i++)out.data[i]=scalar*data[i];
    return out;
  }

  friend Matrix operator*(f32 scalar,const Matrix& m){
    return m*scalar;
  }
  

  Matrix operator*(const Matrix& other)const{
    if(cols!=other.rows){throw invalid_argument("Dimensions do not match");}
    // a x b  .....  b x d
    Matrix out(rows,other.cols);
    for(size_t a = 0;a<rows;a++){
      for(size_t d = 0;d<other.cols;d++){
        for(size_t b = 0;b<cols;b++){
          out(a,d) = out(a,d) + other(b,d)*(*this)(a,b);
        }
      }
    }

    return out;
  }

};

bool mat_copy(Matrix &src,Matrix &dest){
  if(src.rows!=dest.rows || src.cols!=dest.cols)return false;
  memcpy(dest.data.data(),src.data.data(),sizeof(f32) * (u64)src.rows * src.cols);
  return 1;
}
void mat_clear(Matrix &src){
  memset(src.data.data(),0,sizeof(f32)*(u64)src.rows*src.cols);
}

void mat_fill(Matrix &src,f32 x){
  size_t n = src.data.size();
  for(size_t idx =0;idx<n;idx++)
    src.data[idx] = x;
}



// for the testing to be removed at the end
int main() {
    Matrix m(3, 3);
    f32 init[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < 9; i++)
        m.data[i] = init[i];

    Matrix r = m * 2.5f;

    for (size_t idx = 0; idx < r.data.size(); idx++)
        cout << r.data[idx] << '\n';
    Matrix cpy(3,3);

    if(mat_copy(r,cpy))cout << "copied" << '\n';

    for(size_t idx =0;idx <r.data.size();idx++){
      cout << cpy.data[idx] << '\n';
    }
    return 0;
}
