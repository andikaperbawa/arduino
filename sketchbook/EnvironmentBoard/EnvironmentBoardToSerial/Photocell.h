#ifndef __PHOTOCELL_H__
#define __PHOTOCELL_H__

// WIRING DIAGRAM:
// * Huzzah 3V3 Pin to 22k Resistor R1
// * 22k Resistor R1 to 10k Resistor R2
// * 10k Resistor R2 to GND
// * CdS parallel to 10k Resistor
// * Middle of R1/R2 to ADC
// (3V3)---[R1:22k]---+---[R2:10k]---+-(GND)
//                    |              |  
//                    +---[R: CdS]---+
//                    |
//                  (ADC)

class Photocell {
public:
  Photocell(void);
  ~Photocell(void);
  
  // calibration routines to generate more accurate readouts
  void set_voltage(float U0);
  void set_resistors(float R1,float R2);
  void set_range(float Rmin, float Rmax);
  
  // this performs the actual measurement
  void measure(void);

  // these functions return converted measured values
  float adc_voltage(void) const;      // the voltage at the ADC, in Volt
  float cds_resistance(void) const;   // the resistance of the photocell, in Ohm
  float total_resistance(void) const; // the total resistance of the network, in Ohm
  float total_current(void) const;    // the total current flowing through the network, in Ampere
  float total_voltage(void) const;    // the total voltage around the network. This is U0, in Volt.
  float lightness(void) const;        // the relative lightness, in %
protected:
  float m_U0;
  float m_R1,m_R2;  
  float m_Rmin,m_Rmax;
  float m_Uadc;
  float m_rho;
private:
  Photocell(const Photocell& other);
};

#endif

