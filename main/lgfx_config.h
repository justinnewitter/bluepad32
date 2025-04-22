#pragma once
#include <LovyanGFX.hpp>

// Screen SPI pins
static constexpr int PIN_SCLK = 18;
static constexpr int PIN_MISO = 16;
static constexpr int PIN_MOSI = 17;
static constexpr int PIN_DC   = 2;
static constexpr int PIN_CS   = 5;
static constexpr int PIN_RST  = 4;
static constexpr int PIN_BL   = 21;

// I2c Touch Pins
static constexpr int I2C_SDA = 8;
static constexpr int I2C_SCL = 9;
static constexpr int TOUCH_INT = 1;
static constexpr int TOUCH_RST = 48;

struct LGFX : public lgfx::LGFX_Device {

  lgfx::Panel_ST7796 _panel_instance;
  lgfx::Bus_SPI _bus_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Touch_FT5x06 _touch_instance;  // FT6336U compatible

  LGFX(void) {
    // Panel configuration
    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs           = PIN_CS;
      cfg.pin_rst          = PIN_RST;
      cfg.pin_busy         = -1;
      cfg.memory_width     = 320;
      cfg.memory_height    = 480;
      cfg.panel_width      = 320;
      cfg.panel_height     = 480;
      cfg.offset_x         = 0;
      cfg.offset_y         = 0;
      cfg.offset_rotation  = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits  = 1;
      cfg.readable         = true;
      cfg.invert           = false;
      cfg.rgb_order        = false;
      cfg.bus_shared       = true;
      cfg.dlen_16bit       = false;
      
      _panel_instance.config(cfg);
    }

    // SPI bus configuration
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host    = SPI3_HOST;      // SPI2_HOST or SPI3_HOST
      cfg.freq_write  = 20000000;       // 20MHz
      cfg.freq_read   = 10000000;       // 10MHz
      cfg.pin_sclk    = PIN_SCLK;
      cfg.pin_mosi    = PIN_MOSI;
      cfg.pin_miso    = PIN_MISO;
      cfg.pin_dc      = PIN_DC;
      cfg.dma_channel = -1; // 0, 1, or 2 depending on setup (enabling helps performance)

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

     // Backlight configuration
    {
        auto cfg = _light_instance.config();
    
        cfg.pin_bl = 21;     // LED backlight pin
        cfg.invert = false;
        cfg.freq = 44100;    // PWM frequency
        cfg.pwm_channel = 7; // PWM channel
    
        _light_instance.config(cfg);
        _panel_instance.setLight(&_light_instance);
    }

    // Touch config
    {
        auto cfg = _touch_instance.config();
        cfg.x_min = 0;
        cfg.x_max = 319;
        cfg.y_min = 0;
        cfg.y_max = 479;
        cfg.pin_int  = TOUCH_INT;
        cfg.pin_rst  = TOUCH_RST;
        cfg.i2c_port = 1;
        cfg.i2c_addr = 0x38;       // default FT6336U address
        cfg.pin_sda  = I2C_SDA;
        cfg.pin_scl  = I2C_SCL;
        cfg.freq     = 400000;

        _touch_instance.config(cfg);
        _panel_instance.setTouch(&_touch_instance);
    }
    

    setPanel(&_panel_instance);

  }

};
