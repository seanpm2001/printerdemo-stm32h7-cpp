
#include <cstdint>
#include <memory>
#include <slint-platform.h>
#include <type_traits>

// C++ Warning in the sdk headers
#pragma GCC diagnostic ignored "-Wvolatile"
#include "stm32h735g_discovery_lcd.h"
#include "stm32h735g_discovery_ts.h"
#include "stm32h7xx_hal.h"

extern "C" int32_t BSP_LED_On(int);
extern "C" int32_t BSP_LED_Off(int);

using Pixel = slint::platform::Rgb565Pixel;

struct StmWindowAdapter : public slint::platform::WindowAdapter {
  slint::platform::SoftwareRenderer m_renderer{
      slint::platform::SoftwareRenderer::RepaintBufferType::SwappedBuffers};
  bool needs_redraw = true;
  const slint::PhysicalSize m_size;

  explicit StmWindowAdapter(slint::PhysicalSize size) : m_size(size) {}

  slint::platform::AbstractRenderer &renderer() override { return m_renderer; }

  slint::PhysicalSize size() override { return m_size; }

  void request_redraw() override { needs_redraw = true; }
};

struct StmSlintPlatform : public slint::platform::Platform {

  StmWindowAdapter *m_window = nullptr;
  const slint::PhysicalSize size;
  std::span<Pixel> buffer1;
  std::span<Pixel> buffer2;

  StmSlintPlatform(slint::PhysicalSize size, std::span<Pixel> buffer1,
                   std::span<Pixel> buffer2)
      : size(size), buffer1(buffer1), buffer2(buffer2) {}

  std::unique_ptr<slint::platform::WindowAdapter>
  create_window_adapter() override {
    auto w = std::make_unique<StmWindowAdapter>(size);
    m_window = w.get();
    return w;
  }

  std::chrono::milliseconds duration_since_start() override {
    return std::chrono::milliseconds(HAL_GetTick());
  }

  void run_event_loop() override {

    int last_touch_x = 0;
    int last_touch_y = 0;
    bool touch_down = false;

    while (true) {
      slint::platform::update_timers_and_animations();

      if (m_window) {
        TS_State_t TS_State{};
        BSP_TS_GetState(0, &TS_State);
        if (TS_State.TouchDetected) {
          last_touch_x = TS_State.TouchX;
          last_touch_y = TS_State.TouchY;
          buffer2[last_touch_x + last_touch_y * size.width].b = 0x1f;
          buffer2[last_touch_x + last_touch_y * size.width].r = 0;

          m_window->window().dispatch_pointer_move_event(slint::LogicalPosition(
              {float(last_touch_x), float(last_touch_y)}));
          if (!touch_down) {
            BSP_LED_On(1);
            m_window->window().dispatch_pointer_press_event(
                slint::LogicalPosition(
                    {float(last_touch_x), float(last_touch_y)}),
                slint::PointerEventButton::Left);
          } else {
            BSP_LED_Off(1);
          }
          touch_down = true;
          BSP_LED_On(0);
        } else if (touch_down) {
          BSP_LED_Off(0);

          buffer2[last_touch_x + last_touch_y * size.width].b = 0x0f;
          buffer2[last_touch_x + last_touch_y * size.width].g = 0x1f;

          m_window->window().dispatch_pointer_release_event(
              slint::LogicalPosition(
                  {float(last_touch_x), float(last_touch_y)}),
              slint::PointerEventButton::Left);
          m_window->window().dispatch_pointer_exit_event();
          touch_down = false;
        }

        if (std::exchange(m_window->needs_redraw, false)) {
          m_window->m_renderer.render(buffer1, m_window->m_size.width);

          BSP_LCD_LayerConfig_t config;
          config.X0 = 0;
          config.X1 = LCD_DEFAULT_WIDTH;
          config.Y0 = 0;
          config.Y1 = LCD_DEFAULT_HEIGHT;
          config.PixelFormat = LCD_PIXEL_FORMAT_RGB565;
          config.Address = uintptr_t(buffer1.data());
          BSP_LCD_ConfigLayer(0, 0, &config);
          std::swap(buffer1, buffer2);
          // FIXME: flush caches and wait
        }
      }
    }
  }
};

void init_slint(unsigned int lcd_layer_0_address,
                           unsigned int lcd_layer_1_address, unsigned int width,
                           unsigned int height) {
  auto a = width * height;
  std::span<Pixel> buffer1(reinterpret_cast<Pixel *>(lcd_layer_0_address), a);
  std::span<Pixel> buffer2(reinterpret_cast<Pixel *>(lcd_layer_1_address), a);

  slint::platform::set_platform(std::make_unique<StmSlintPlatform>(
      slint::PhysicalSize({width, height}), buffer1, buffer2));
}
