// Produit matrice-vecteur
#include <cassert>
#include <vector>
#include <iostream>
#include <mpi.h>


#pragma opm parallel
// ---------------------------------------------------------------------
class Matrix : public std::vector<double>
{
public:
    Matrix (int dim);
    Matrix( int nrows, int ncols );
    Matrix( const Matrix& A ) = delete;
    Matrix( Matrix&& A ) = default;
    ~Matrix() = default;

    Matrix& operator = ( const Matrix& A ) = delete;
    Matrix& operator = ( Matrix&& A ) = default;
    
    double& operator () ( int i, int j ) {
        return m_arr_coefs[i + j*m_nrows];
    }
    double  operator () ( int i, int j ) const {
        return m_arr_coefs[i + j*m_nrows];
    }
    
    std::vector<double> operator * ( const std::vector<double>& u ) const;
    
    std::ostream& print( std::ostream& out ) const
    {
        const Matrix& A = *this;
        out << "[\n";
        for ( int i = 0; i < m_nrows; ++i ) {
            out << " [ ";
            for ( int j = 0; j < m_ncols; ++j ) {
                out << A(i,j) << " ";
            }
            out << " ]\n";
        }
        out << "]";
        return out;
    }
private:
    int m_nrows, m_ncols;
    std::vector<double> m_arr_coefs;
};

// ---------------------------------------------------------------------
inline std::ostream& 
operator << ( std::ostream& out, const Matrix& A )
{
    return A.print(out);
}

// ---------------------------------------------------------------------
inline std::ostream&
operator << ( std::ostream& out, const std::vector<double>& u )
{
    out << "[ ";
    for ( const auto& x : u )
        out << x << " ";
    out << " ]";
    return out;
}

// ---------------------------------------------------------------------
std::vector<double> 
Matrix::operator * ( const std::vector<double>& u ) const
{
    const Matrix& A = *this;
    assert( u.size() == unsigned(m_ncols) );
    std::vector<double> v(m_nrows, 0.);
    for ( int i = 0; i < m_nrows; ++i ) {
        for ( int j = 0; j < m_ncols; ++j ) {
            v[i] += A(i,j)*u[j];
        }            
    }
    return v;
}

// =====================================================================
Matrix::Matrix (int dim) : m_nrows(dim), m_ncols(dim),
                           m_arr_coefs(dim*dim)
{
    for ( int i = 0; i < dim; ++ i ) {
        for ( int j = 0; j < dim; ++j ) {
            (*this)(i,j) = (i+j)%dim;
        }
    }
}
// ---------------------------------------------------------------------
Matrix::Matrix( int nrows, int ncols ) : m_nrows(nrows), m_ncols(ncols),
                                         m_arr_coefs(nrows*ncols)
{
    int dim = (nrows > ncols ? nrows : ncols );
    for ( int i = 0; i < nrows; ++ i ) {
        for ( int j = 0; j < ncols; ++j ) {
            (*this)(i,j) = (i+j)%dim;
        }
    }    
}
// =====================================================================

int main( int argc, char* argv[] )
{
    int number_proc;
    int rank;
    const int N = 16;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_proc);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    Matrix A(N);
    std::vector<double> u( N );
    for ( int i = 0; i < N; ++i ) u[i] = i+1;

    if (rank==0){
        std::cout  << "A : " << A << std::endl << std::endl;
        std::cout << " u : " << u << std::endl  << std::endl;
        std::vector<double> v = A*u;
        std::cout << "A.u = " << v << std::endl << std::endl;
    }
    int bigger_ligne=N%number_proc;
    int nb_ligne;
    int offset;
    nb_ligne=N/number_proc;
    offset=nb_ligne*rank;
    // if (rank==number_proc-1) nb_ligne+=bigger_ligne;
    
    Matrix sub_A(nb_ligne, N);
    for (int k=0;k<nb_ligne;k++){
        for (int j=0;j<N;j++){
            sub_A(k,j)=A(k+offset,j);
        }
    }
    std::vector<double> send=sub_A*u;
    std::vector<double> result(N,0);
    MPI_Gather(send.data(),nb_ligne,MPI_DOUBLE,result.data(),nb_ligne,MPI_DOUBLE,0,MPI_COMM_WORLD);
    if (rank==0) std::cout << "A.u = " << result;
    MPI_Finalize();
    return EXIT_SUCCESS;
}
