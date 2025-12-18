
// ATmega328P @16MHz. Bare-metal I2C (TWI) reads MPU6050 gyro Z; PWM on PD6 controls fan.
// States: 0–30 OFF, 31–100 LOW, 101–200 MEDIUM, >200 HIGH.

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define F_CPU 16000000UL

// ----- TWI/I2C -----
#define TWI_FREQ     100000UL          // 100 kHz
#define MPU6050_ADDR 0x68              // 7-bit address

static void twi_init(void) {
    // SCL = F_CPU / (16 + 2*TWBR*prescaler); prescaler=1
    TWSR = 0x00; // prescaler = 1
    TWBR = (uint8_t)((F_CPU / TWI_FREQ - 16) / 2); // ~72 for 100kHz at 16MHz
}

static void twi_start(uint8_t addr_rw) {
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    TWDR = addr_rw;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}
static void twi_write(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}
static uint8_t twi_read_ack(void) {
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    return TWDR;
}
static uint8_t twi_read_nack(void) {
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    return TWDR;
}
static void twi_stop(void) {
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

// ----- MPU6050 minimal -----
static void mpu_write(uint8_t reg, uint8_t val) {
    twi_start((MPU6050_ADDR<<1) | 0); // write
    twi_write(reg);
    twi_write(val);
    twi_stop();
}
static void mpu_init(void) {
    // Wake-up: PWR_MGMT_1 (0x6B) = 0x00
    mpu_write(0x6B, 0x00);
    // Gyro ±250 dps: GYRO_CONFIG (0x1B) = 0x00
    mpu_write(0x1B, 0x00);
}
static int16_t mpu_read_gyroZ_raw(void) {
    // Set register address to GYRO_ZOUT_H (0x47)
    twi_start((MPU6050_ADDR<<1) | 0); // write
    twi_write(0x47);
    // Repeated start to read
    twi_start((MPU6050_ADDR<<1) | 1); // read
    uint8_t hi = twi_read_ack();
    uint8_t lo = twi_read_nack();
    twi_stop();
    return (int16_t)((hi<<8) | lo);
}
static float mpu_read_gyroZ_dps(void) {
    // FS = ±250 dps => 131 LSB/°/s
    int16_t raw = mpu_read_gyroZ_raw();
    return (float)raw / 131.0f;
}

// ----- PWM on PD6 (OC0A) -----
static void pwm_init(void) {
    DDRD |= (1<<DDD6); // PD6 output
    // Fast PWM, non-inverting on OC0A, prescaler 64 (~976 Hz)
    TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
    TCCR0B = (1<<CS01) | (1<<CS00); // clk/64
    OCR0A = 0; // start off
}
static void fan_set_duty(uint8_t duty) { OCR0A = duty; }

static void fan_state_from_dps(float dps_abs) {
    if (dps_abs <= 30.0f)       fan_set_duty(0);    // OFF
    else if (dps_abs <= 100.0f) fan_set_duty(64);   // LOW (~25%)
    else if (    else if (dps_abs <= 200.0f) fan_set_duty(160);  // MEDIUM (~63%)
    else                        fan_set_duty(255);  // HIGH (~100%)
}

int main(void) {
    twi_init();
    mpu_init();
    pwm_init();

    while (1) {
        float gz = mpu_read_gyroZ_dps();
        if (gz < 0) gz = -gz; // absolute value
        fan_state_from_dps(gz);
        _delay_ms(100);
    }
