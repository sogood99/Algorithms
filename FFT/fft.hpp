#ifndef FFT_HPP
#define FFT_HPP

#include <iostream>

#define PI 3.141592653589793238462643
#define EPS 1e-9
#define MAX_DEPTH 5e6

double abs(double x){
    return x >= 0 ? x : -1*x;
}

double sqrt(double x){
    if (x == 0){
        return 0;
    }
    double x1, x0 = x/2;
    while(1){
        x1 = x0+1/(2*x0)*(x-x0*x0);
        if (abs(x1-x0)<EPS){
            return x1;
        }
        x0 = x1;
    }
    return 0;
}

double sin(double t){
    double ans = 0;
    double temp = t;
    for (int i = 1; i < MAX_DEPTH; i++){
        ans += temp;
        temp = (-1)*temp*t/(2*i)*t/(2*i+1);
        if (abs(temp) < 1e-15){
            return ans;
        }
    }
    return ans;
}

double cos(double t){
    double ans = 0;
    double temp = 1;
    for (int i = 1; i < MAX_DEPTH; i++){
        ans += temp;
        temp = (-1)*temp*t/(2*i-1)*t/(2*i);
        if (abs(temp) < 1e-15){
            return ans;
        }
    }
    return ans;
}

double atan(double t){
    double ans = 0;
    double temp = t;
    if (abs(t) < 1){
        for (int i = 0; i < MAX_DEPTH; i++){
            ans += temp/(2*i+1);
            temp = (-1)*temp*t*t;
            if (abs(temp/(2*i+3)) < 1e-15){
                return ans;
            }
        }
    }else{
        if (t > 0){
            ans = PI/2.;
        }else{
            ans = -PI/2.;
        }
        t = 1/t;
        temp = -t;
        for (int i = 0; i < MAX_DEPTH; i++){
            ans += temp/(2*i+1);
            temp = (-1)*temp*t*t;
            if (abs(temp/(2*i+3)) < 1e-15){
                return ans;
            }
        }
    }
    return ans;
}

class Complex{
public:
    Complex(double r = 0, double im = 0): m_Real(r), m_Imaginary(im){}
protected:
    double m_Real = 0;
    double m_Imaginary = 0;
public:
    bool zero() const;
    double abs() const;
    double ang() const;
    double Re() const;
    double Im() const;
    Complex operator +(const Complex & other);
    Complex operator -(const Complex & other);
    Complex operator *(const Complex & other);
    Complex operator /(const Complex & other);
};

bool Complex::zero() const{
    return !(m_Real || m_Imaginary);
}

double Complex::abs() const{
    return sqrt(m_Real*m_Real+m_Imaginary*m_Imaginary);
}

double Complex::ang() const{
    if (zero()){
        throw "Angle of zero undefined";
        return 0;
    }else if (m_Real == 0){
        return PI/2.;
    }
    return atan(m_Imaginary/m_Real);
}

double Complex::Re() const{
    return m_Real;
}

double Complex::Im() const{
    return m_Imaginary;
}

double Re(Complex z){
    return z.Re();
}

double Im(Complex z){
    return z.Im();
}

double ang(Complex z){
    return z.ang();
}

Complex Complex::operator+(const Complex &other){
    return Complex(m_Real+other.m_Real, m_Imaginary+other.m_Imaginary);
}

Complex Complex::operator-(const Complex &other){
    return Complex(m_Real-other.m_Real, m_Imaginary-other.m_Imaginary);
}

Complex Complex::operator*(const Complex &other){
    return Complex(m_Real*other.m_Real-m_Imaginary*other.m_Imaginary,
                   m_Real*other.m_Imaginary+m_Imaginary*other.m_Real);
}

Complex Complex::operator/(const Complex &other){
    if (other.m_Real == 0 && other.m_Imaginary == 0){
        throw "Math error: Attempted to divide by Zero\n";
        return 0;
    }
    double absValue = other.abs();
    return Complex((m_Real*other.m_Real+m_Imaginary*other.m_Imaginary)/absValue,
                   (m_Imaginary*other.m_Real-m_Real*other.m_Imaginary)/absValue);
}

std::ostream &operator << (std::ostream &os, const Complex &z){
    os << z.Re() << "+" << z.Im()<<"i";
    return os;
}

#endif // FFT_HPP
