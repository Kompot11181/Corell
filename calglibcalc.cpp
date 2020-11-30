#include "calglibcalc.h"
#include <QDebug>

using namespace alglib_impl;

cAlglibCalc::cAlglibCalc(QObject *parent) : QObject(parent)
{

}

// вызов функции
// alglib::corrr1d(const real_1d_array &signal,  const ae_int_t n,
//                 const real_1d_array &pattern, const ae_int_t m,
//                       real_1d_array &r,
//                       const xparams _xparams = alglib::xdefault);
void cAlglibCalc::calcCorrr1D(const QVector<double> &signal, const QVector<double> &pattern)
{
    if ((signal.size()==0) || (pattern.size()==0)) return;
    _result.clear();
    _result.reserve(signal.size() + pattern.size());
    _max = 0.0;
    _index = 0;
    ae_state state;
    ae_state * _state = &state;
    ae_state_init(_state);
    alglib::real_1d_array s, p, res;
    s.setcontent(signal.length(), signal.data());
    p.setcontent(pattern.length(), pattern.data());
    res.setcontent(signal.size() + pattern.size(), _result.data());
    corrr1d(s.c_ptr(), signal.length(), p.c_ptr(), pattern.length(), res.c_ptr(), _state);
    for(int i = 0; i < res.length(); i++) {
        _result.push_back(res[i]);
        if (res[i] > _max) {
            _max = res[i];
            _index = i;
        }
    }
    emit calculated("corr(f, g)", _result);
}

