#include "calglibcalc.h"
#include <QDebug>

using namespace alglib_impl;

cAlglibCalc::cAlglibCalc(QObject *parent) : QObject(parent)
{

}

#define SPLINE1D_MUL    ( 100 )
// вызов функции
// alglib::spline1dbuildcubic(const real_1d_array &signal,  const ae_int_t n,
//                            const real_1d_array &pattern, const ae_int_t m,
//                                  real_1d_array &r,
//                                  ae_int_t bound, double, ae_int_t, double,
//                                  spline1dinterpolant &c,       ae_state &s);
void cAlglibCalc::calcSplineCube()  // используется _signal
{
    _result.clear();
    if (_signal.size()) {
        _result.reserve(_signal.size() * SPLINE1D_MUL);
        _max = 0.0;
        _index = 0;
        ae_state state;
        ae_state * _state = &state;
        ae_state_init(_state);
        alglib::real_1d_array x, y, res;
        spline1dinterpolant c;
        spline1dinterpolant * _c = &c;
        c.x = *x.c_ptr(); c.c = *y.c_ptr();
        y.setcontent(_signal.length(), _signal.data());
        x.setlength(y.length());
        res.setcontent(_signal.size() * SPLINE1D_MUL, _result.data());
        for(int i = 0; i < x.length(); i++) {
            x[i] = i;
        }// заполнить абсциссу
        spline1dbuildcubic(x.c_ptr(), y.c_ptr(), _signal.size(), 1, 0.0, 1, 1.0, &c, _state);
//      spline1dbuildlinear(x.c_ptr(), y.c_ptr(), _signal.size(), &c, _state);
        for(int i = 0; i < x.length(); i++) {
            for(double u = 0.0; u < 1.0; u += (1.0/SPLINE1D_MUL)) {
                _result.append(spline1dcalc(&c, i + u, _state));
            }
        }
    }
    emit calculated(QString("in_cube(f, %1)").arg(SPLINE1D_MUL), _result);
}

// вызов функции
// alglib::spline1dbuildmonotone(const real_1d_array &signal,  const ae_int_t n,
//                               const real_1d_array &pattern, const ae_int_t m,
//                                     real_1d_array &r,
//                                     spline1dinterpolant &c,       ae_state &s);
void cAlglibCalc::calcSplineMono()  // используется _signal
{
    _result.clear();
    if (_signal.size()) {
        _result.reserve(_signal.size() * SPLINE1D_MUL);
        _max = 0.0;
        _index = 0;
        ae_state state;
        ae_state * _state = &state;
        ae_state_init(_state);
        alglib::real_1d_array x, y, res;
        spline1dinterpolant c;
        spline1dinterpolant * _c = &c;
        c.x = *x.c_ptr(); c.c = *y.c_ptr();
        y.setcontent(_signal.length(), _signal.data());
        x.setlength(y.length());
        res.setcontent(_signal.size() * SPLINE1D_MUL, _result.data());
        for(int i = 0; i < x.length(); i++) {
            x[i] = i;
        }// заполнить абсциссу
      spline1dbuildmonotone(x.c_ptr(), y.c_ptr(), _signal.size(), &c, _state);
//      spline1dbuildlinear(x.c_ptr(), y.c_ptr(), _signal.size(), &c, _state);
        for(int i = 0; i < x.length(); i++) {
            for(double u = 0.0; u < 1.0; u += (1.0/SPLINE1D_MUL)) {
                _result.append(spline1dcalc(&c, i + u, _state));
            }
        }
    }
    emit calculated(QString("in_mono(f, %1)").arg(SPLINE1D_MUL), _result);
}

// вызов функции
// alglib::fftr1d ( ae_vector* a,
//                  ae_int_t n,
//                  ae_vector* f,
//                  ae_state *_s)
void cAlglibCalc::calcFFT()     // используется _signal
{
    _result.clear();
    if ((_signal.size())) {
        _result.reserve(_signal.size());
        _max = 0.0;
        _index = 0;
        ae_state state;
        ae_state * _state = &state;
        ae_state_init(_state);
        alglib::real_1d_array s;
        alglib::complex_1d_array res;
        s.setcontent(_signal.length(), _signal.data());
        res.setlength(_signal.size());
        fftr1d(s.c_ptr(), _signal.length(), res.c_ptr(), _state);
        for(int i = 0; i < res.length(); i++) {
            _result.append(alglib::abscomplex(res[i]));
//            _result.append(res[i].x);
//            _result.append(res[i].y);
//            _result.append(res[i].y);
/*
            double m = alglib::abscomplex(res[i]);
            _result.append(m);
            if (m > _max) {
                _max = m;
                _index = i;
            }
*/
        }
    }
    emit calculated("fft(f)", _result);
}

// вызов функции
// alglib::fftr1dinv (ae_vector* f, ae_int_t n,
//                    ae_vector* a,
//                    ae_state *_s)
void cAlglibCalc::calcIFFT()     // используется _signal
{
    _result.clear();
  // проверка обратного преобразования Фурье. Пока безуспешно
    if ((_signal.size())) {
        _result.reserve(_signal.size());
        _max = 0.0;
        _index = 0;
        ae_state state;
        ae_state * _state = &state;
        ae_state_init(_state);
//        alglib::complex_1d_array f;
//        f = "[10, -2+2i, -2]";

        alglib::complex_1d_array f;
        alglib::real_1d_array res;
        f.setlength(_signal.size());
        int i = 0;
        for(i=0; i < _signal.size();) {
            f[i].x = _signal[i++];
            f[i].y = _signal[i++];
        }
//        for(i; i < _signal.size()*2; i++) {
//            f[i].x = 0.0;
//            f[i].y = 0.0;
//        }
//        fftr1dinv(f.c_ptr(), f.length()-1, res.c_ptr(), _state); // выводит половину
        fftr1dinv(f.c_ptr(), f.length(), res.c_ptr(), _state);   // выводит половину и его отражение
        for(int i = 0; i < res.length(); i += 2) {
            double m = res[i];  //sqrt(res[i] * res[i] + res[i+1]*res[i+1]); //res[i*2];
            _result.append(m);
            if (m > _max) {
                _max = m;
                _index = i;
            }
        }
    }
    emit calculated("ifft(f)", _result);
}

// вызов функции
// alglib::corrr1d(const real_1d_array &signal,  const ae_int_t n,
//                 const real_1d_array &pattern, const ae_int_t m,
//                       real_1d_array &r,
//                       ae_state &s);
void cAlglibCalc::calcCorrr1D()     // используется _signal, _pattern
{
    _result.clear();
    if ((_signal.size()) && (_pattern.size())) {
        _result.reserve(_signal.size() + _pattern.size());
        _max = 0.0;
        _index = 0;
        ae_state state;
        ae_state * _state = &state;
        ae_state_init(_state);
        alglib::real_1d_array s, p, res;
        s.setcontent(_signal.length(), _signal.data());
        p.setcontent(_pattern.length(), _pattern.data());
        res.setcontent(_signal.size() + _pattern.size(), _result.data());
        corrr1d(s.c_ptr(), _signal.length(), p.c_ptr(), _pattern.length(), res.c_ptr(), _state);
        for(int i = 0; i < res.length(); i++) {
            _result.append(res[i]);
            if (res[i] > _max) {
                _max = res[i];
                _index = i;
            }
        }
    }
    emit calculated("corr(f, g)", _result);
}

// вызов функции
// alglib::corrr1dcircular(const real_1d_array &signal,  const ae_int_t n,
//                         const real_1d_array &pattern, const ae_int_t m,
//                               real_1d_array &r,
//                               ae_state &s);
void cAlglibCalc::calcCorrr1DCircular()   // используется _signal, _pattern
{
    _result.clear();
    if ((_signal.size()) && (_pattern.size())) {
        _result.reserve(_signal.size() + _pattern.size());
        _max = 0.0;
        _index = 0;
        ae_state state;
        ae_state * _state = &state;
        ae_state_init(_state);
        alglib::real_1d_array s, p, res;
        s.setcontent(_signal.length(), _signal.data());
        p.setcontent(_pattern.length(), _pattern.data());
        res.setcontent(_signal.size() + _pattern.size(), _result.data());
        corrr1dcircular(s.c_ptr(), _signal.length(), p.c_ptr(), _pattern.length(), res.c_ptr(), _state);
        for(int i = 0; i < res.length(); i++) {
            _result.append(res[i]);
            if (res[i] > _max) {
                _max = res[i];
                _index = i;
            }
        }
    }
    emit calculated("corrcirc(f, g)", _result);
}

