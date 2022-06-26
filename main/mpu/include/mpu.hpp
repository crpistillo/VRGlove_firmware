#include "MPU.hpp"        // main file, provides the class itself
#include "mpu/math.hpp"   // math helper for dealing with MPU data
#include "mpu/types.hpp"  // MPU data types and definitions
#include "I2Cbus.hpp"

class MPU {
public:
    MPU();

    // Gpio number of the SDA
    static const gpio_num_t SDA;

    // Gpio number of the DCL
    static const gpio_num_t SCL;

    // Clock speed in kHz. Range: 100 KHz ~ 400Hz
    static const uint32_t CLOCK_SPEED; 

    void read();

    mpud::float_axes_t getAccelG();
    mpud::float_axes_t getGyroDPS();

private:
    MPU_t mpu_;
    mpud::raw_axes_t accelRaw_;   // x, y, z axes as int16
    mpud::raw_axes_t gyroRaw_;    // x, y, z axes as int16
    mpud::float_axes_t accelG_;   // accel axes in (g) gravity format
    mpud::float_axes_t gyroDPS_;  // gyro axes in (DPS) º/s format

    void initializeMPU();
    void testConnection();
    void setupConfigurations();
};