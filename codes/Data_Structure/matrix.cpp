template<typename T, size_t SIZE>
class Matrix{
private:
  T mtx[SIZE][SIZE];
  size_t size;
public:
  Matrix(){
    for(unsigned i=0;i<SIZE;i++) for(unsigned j=0;j<SIZE;j++)
      mtx[i][j]=0;
    size=SIZE;
  }
  Matrix(T arr[SIZE][SIZE]){
    for(unsigned i=0;i<SIZE;i++) for(unsigned j=0;j<SIZE;j++)
      mtx[i][j]=arr[i][j];
    size=SIZE;
  }
  inline void resize(size_t x){
    assert(x<=SIZE);
    size=x;
  }
  inline void toI(){
    for(unsigned i=0;i<size;i++) for(unsigned j=0;j<size;j++)
      mtx[i][j]=(i==j);
  }
  //Equal Operator
  Matrix operator=(T arr[SIZE][SIZE]){
    for(unsigned i=0;i<SIZE;i++) for(unsigned j=0;j<SIZE;j++)
      mtx[i][j]=arr[i][j];
    return *this;
  }
  Matrix operator=(const Matrix &a){
    assert(a.size==size);
    for(unsigned i=0;i<size;i++) for(unsigned j=0;j<size;j++)
      mtx[i][j]=a.mtx[i][j];
    return *this;
  }
  //Plus Operator
  Matrix operator+(const Matrix &a)const{
    assert(a.size == size);
    Matrix<T,SIZE> s;
    s.resize(size);
    for(unsigned i=0;i<size;i++) for(unsigned j=0;j<size;j++)
      s.mtx[i][j]=a.mtx[i][j]+mtx[i][j];
    return s;
  }
  Matrix operator+=(const Matrix &a){
    assert(a.size == size);
    for(unsigned i=0;i<size;i++) for(unsigned j=0;j<size;j++)
      mtx[i][j]+=a.mtx[i][j];
    return *this;
  }
  //Minus Operator
  Matrix operator-(const Matrix &a)const{
    assert(a.size == size);
    Matrix<T,SIZE> s;
    s.resize(size);
    for(unsigned i=0;i<size;i++) for(unsigned j=0;j<size;j++)
      s.mtx[i][j]=a.mtx[i][j]-mtx[i][j];
    return s;
  }
  Matrix operator-=(const Matrix &a){
    assert(a.size == size);
    for(unsigned i=0;i<size;i++) for(unsigned j=0;j<size;j++)
      mtx[i][j]-=a.mtx[i][j];
    return *this;
  }
  //Multiply Operator
  Matrix operator*(const Matrix &a)const{
    assert(a.size == size);
    Matrix<T, SIZE> s;
    s.resize(size);
    for(unsigned i=0;i<size;i++){
      for(unsigned j=0;j<size;j++){
        s.mtx[i][j] = 0;
        for(unsigned k=0;k<size;k++)
          s.mtx[i][j] += mtx[i][k]*a.mtx[k][j];
      }
    }
    return s;
  }
  Matrix operator*=(const Matrix &a){
    assert(a.size == size);
    *this = (*this)*a;
    return *this;
  }
  //Ostream Operator
  friend ostream& operator<<(ostream& os,const Matrix& x){
    for(unsigned i=0;i<x.size;i++){
      os<<x.mtx[i][0];
      for(unsigned j=1;j<x.size;j++){
        os<<' '<<x.mtx[i][j];
      }
      if(i!=x.size-1) os<<'\n';
    }
    return os;
  }
};
