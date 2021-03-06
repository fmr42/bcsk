#ifndef _BCQL_H_
#define _BCQL_H_

#include <cblas.h>
#include <lapacke/lapacke.h>
#include <math.h>


//TODO Only one order is currently supported...
enum BCSK_Q_ORDER { BcskWXYZ = 130 };
enum BCSK_V_ORDER { BcskXYZ  = 140 };
enum BCSK_M_ORDER { BcskColMajor = 102 }; //TODO Add Row Major


//copies first "len" entries of src to corresponding entries in dst
int dDub ( double *dst , double *src , unsigned int len ) ;

// Sets first "len" entries of array to 0;
int dZeros ( double *array , unsigned int len ) ;

// puts in dst the element-by-element sum of src1 and src2
int dSum2  ( double *dst , double alpha , double *src1 , double beta , double *src2 , unsigned int len ) ;

// sum up 3 arrays
int dSum3 ( double *dst ,
            double a1 , double *src1 ,
            double a2 , double *src2 ,
            double a3 , double *src3 ,
            unsigned int len ) ;

// sum up 4 arrays
int dSum4 ( double *dst ,
            double a1 , double *src1 ,
            double a2 , double *src2 ,
            double a3 , double *src3 ,
            double a4 , double *src4 ,
            unsigned int len ) ;

// sum up 5 arrays
int dSum5 ( double *dst ,
            double a1 , double *src1 ,
            double a2 , double *src2 ,
            double a3 , double *src3 ,
            double a4 , double *src4 ,
            double a5 , double *src5 ,
            unsigned int len ) ;

// Compute cross product between 2 3D vecs
// c = a cross b ;
int dCross ( double *c , double *a , double *b ) ;

// Set the square matrix mat to the identity matrix
int dEye ( unsigned int order , double scale , double *mat ) ;

// Transpose square matrix
int dSqTr ( int n , double *src , double *dst ) ;

// Stores in quaternion c the hamilton product between quaternions a and b
int dHamilton (const enum BCSK_Q_ORDER Order , double *c , double *a , double *b ) ;

// Store in b the inverse of quaternion a
int dQInv( const enum BCSK_Q_ORDER Order , double *b , double *a) ;

//TODO vec arma_quat_between_vecs(const vec& a,const vec& b);

/***********************************************
* Compute angular velocity given the orientation quaternion
* and its derivative.
***********************************************/
//int dQuatInv( const enum LIBQUAT_ORDER BOrder , double *v , const enum LIBQUAT_ORDER AOrder , double *a) ;
int dQD2Vel ( const enum BCSK_V_ORDER v_order    ,
              const enum BCSK_Q_ORDER q_order    ,
              double *v                          ,
              double *q                          ,
              double *dqdt                       );

/*TODO**********************************************
* Compute angular accelleration given the orientation quaternion
* and its derivatives.
***********************************************/
/*vec arma_quat_d_to_acc(const vec& q0,const vec& q1,const vec& q2){
	vec w1(4);
	w1 = 2 * arma_quat_hamilton( q2-arma_quat_hamilton(arma_quat_hamilton(q1,arma_quat_inv(q0)),q1) , arma_quat_inv(q0) );
	return(w1.subvec(1,3));
}
*/

/***********************************************
* Rotate vector v by rotation q.
* This formula should be faster than:
* v_new = q * v * q^-1
***********************************************/
//TODO vec arma_quat_rot ( const vec& q,const vec& v ) ;

/***********************************************
* Return matrix M from vector v s.t. for any x
* M*x = cross(v,x)
***********************************************/
int dCrossMat ( const enum BCSK_M_ORDER MOrder , double *M , const double *v ) ;

/***********************************************
* Applyes Rodriguez formula to convert quaternion q
* to rotation matrix R
***********************************************/
int dQ2R ( const enum BCSK_M_ORDER Order , const enum BCSK_Q_ORDER , double *R , double *q) ;


/***********************************************
* Conversion from rotation matrix R to quaternion q
***********************************************/
int dR2Q ( const enum BCSK_M_ORDER ROrder , const enum BCSK_Q_ORDER QOrder , double *R , double *q) ;


/* Saturate each elements of an array between -abs(sat_level) and +abs(sat_level)
 *
 *                _______  _  +abs(sat_level)
 *             | /
 *      _______|/_______y  _ 0
 *             /
 *      ______/|           _ -abs(sat_level)
 *             x
 *
 *     x: input value
 *     y: output value
 *
 * N.B. 
 */

int dSat( double *src , double *dst , double sat_level , int len ) ;



// normalize vector X
int dNormalise ( const int N , double *X  ); 

// compute rotation quaternion between v1 and v2
int dQbetVs ( double *Q , double *v1 , double *v2);

#endif

