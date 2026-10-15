#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <stdexcept>

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
  f32 operator()(u32 ro,u32 co) const {return data[(size_t)cols*ro + co];}

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
    for(u32 a = 0;a<rows;a++){
      for(u32 d = 0;d<other.cols;d++){
        for(u32 b = 0;b<cols;b++){
          out(a,d) = out(a,d) + other(b,d)*(*this)(a,b);
        }
      }
    }

    return out;
  }

  void mat_transpose(){
    vector<f32> tmp((size_t)rows*cols);
    for(u32 i = 0;i<rows;i++){
      for(u32 j = 0;j<cols;j++){
        tmp[(size_t)rows*j + i] = data[(size_t)cols*i + j];
      }
    }
    data = tmp;
    swap(rows,cols); /// modifies the original Matrix
  }

  Matrix operator+(const Matrix& other)const {
    if(cols!=other.cols || rows!=other.rows){throw invalid_argument("Dimensions do not match");}

    Matrix out(rows,cols);
    for(u32 i = 0;i<rows;i++){
      for(u32 j = 0;j<cols;j++){
        out(i,j) = (*this)(i,j) + other(i,j);
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
void mat_print(Matrix &m){
  for(u32 i = 0;i<m.rows;i++){
    for(u32 j = 0;j<m.cols;j++)cout << m(i,j) << '\t';
    cout << '\n';
  }
  cout << '\n';
}
