#include "MPU.hpp"        // main file, provides the class itself
#include "mpu/math.hpp"   // math helper for dealing with MPU data
#include "mpu/types.hpp"  // MPU data types and definitions
#include "I2Cbus.hpp"
#include "MPUdmp.hpp"

class MPU {
public:
    MPU();

    // Gpio number of the SDA
    static const gpio_num_t SDA;

    // Gpio number of the DCL
    static const gpio_num_t SCL;

    // Clock speed in kHz. Range: 100 KHz ~ 400Hz
    static const uint32_t CLOCK_SPEED; 

    static const uint8_t kDMPOutputRate;
    static const mpud::dmp_feature_t kDMPFeatures;

    void read();
    mpud::float_axes_t getOrientation();
    void printOrientation();

private:
    MPUdmp_t mpu_;
    mpud::quat_t quat_;
    mpud::float_axes_t accelG_;   // accel axes in (g) gravity format
    mpud::float_axes_t gyroDPS_;  // gyro axes in (DPS) º/s format
    mpud::float_axes_t euler_;    // euler angles of the orientation in 0000000000000
    mpud::quat_q30_t quatRaw_;
    mpud::raw_axes_t accelRaw_, gyroRaw_;  

    void initializeMPU();
    void testConnection();
    void setupConfigurations();
};