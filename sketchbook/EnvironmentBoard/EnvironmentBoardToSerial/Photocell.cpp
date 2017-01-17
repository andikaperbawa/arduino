#include"Photocell.h"
#include<Arduino.h>

Photocell::Photocell(void) : m_U0(3.3f),m_R1(22000.0f),m_R2(10000.0f),m_Rmin(15.0f),m_Rmax(4500000.0f),m_Uadc(1.0),m_rho(4500000.0f) {
  pinMode(A0,INPUT);
}

Photocell::~Photocell(void) {
}

void Photocell::set_voltage(float U0) {
  m_U0 = U0;
}

void Photocell::set_resistors(float R1,float R2) {
  m_R1 = R1;
  m_R2 = R2;
}

void Photocell::set_range(float Rmin, float Rmax) {
  m_Rmin = Rmin;
  m_Rmax = Rmax;
}

// MATH:
// We are looking at a voltage divider between R1 and a variable resistor rho that depends on the resistance of the photocell R
//     rho(R) = 1.0/(1.0/R2 + 1.0/R)
// The maximum voltage at the ADC is
//     Umax = R2/(R1+R2)*U0, which should be at most 1V (at least in theory)
// The total resistance is
//     R_total = R1 + rho(R)
// The voltage divider is thus a series of resistors R1, rho(R).
// This results in the following voltage at the ADC
//     Uadc = rho(R) / (R1 + rho(R))*U0
// Now we want to compute R by measuring the voltage U(R) at the ADC.
// We have
//     rho(R) = R1*Uacd/[U0-Uadc]
// and
//     R = 1.0/ (1.0/rho - 1.0/R2)

// Now, let's see what happens at Rmin<Rmax:
//     rho(Rmax) = 1.0/(1.0/R2 + 1.0/Rmax) < rho(Rmin) = 1.0/(1.0/R2 + 1.0/Rmin) (!!)
// To see this, let's assume Rmax is close to infinity, hence
//     lim_Rmax->infinity  rho(Rmax) = 1.0/(1.0/R2 + 0.0) = R2
// For Rmin towards zero, on the other hand
//     lim_Rmin->0         rho(Rmin) = 1.0/(1.0/R2) + inf) = 0
// The implication is that the exprected voltage at the ADC, Uadc, is
//     Uadc(bright) = 0.0V
//     Uadc(dark)   = 1.0V (give or take)

void Photocell::measure(void) {
  m_Uadc = float(analogRead(A0))/1024.0f; // Ua in Volts. This is a bug in the IDE, the maximum value should be 1023!
  m_rho = m_R1*m_Uadc/(m_U0-m_Uadc);
}

float Photocell::adc_voltage(void) const {
  return m_Uadc;
}

float Photocell::cds_resistance(void) const {
  return 1.0/(1.0/m_rho - 1.0/m_R2);
}

float Photocell::total_resistance(void) const {
  return m_R1+m_rho;
}

float Photocell::total_current(void) const {
  return m_U0/total_resistance();
}

// We now assign a logarithmic lightness L, with L=100% for Rmin and L=0% at Rmax
//     g(R) = log(R) - log(Rmin) = log(R/Rmin) will be in the range [0..log(Rmax/Rmin)]
//     g'(R)= log(R/Rmin) / log(Rmax/Rmin) will be in the range [0..1]
//     L(R) = 100.0f*(1.0f-log(R/Rmin)/log(Rmax/Rmin)) will be percent "lightness"
//     L(R) should be clamped to 0,100 before display: L'(R) = min(100.0f,max(0.0f,L(R))

float Photocell::lightness(void) const {
  float R = cds_resistance();
  return 100.0f*min(1.0f,max(0.0f,(1.0f-log(R/m_Rmin)/log(m_Rmax/m_Rmin))));
}

