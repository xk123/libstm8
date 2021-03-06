/*
 * This file is part of the libstm8 project.
 *
 * Copyright (C) 2015 Nikolay Merinov <nikolay.merinov@member.fsf.org>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libstm8/l/clk.h>

void
clk_periph_clock_enable (enum clk_periph_clken clock)
{
  MMIO8(CLK_BASE + (clock >> 3)) |= 1 << (clock & 0x7);
}

void
clk_periph_clock_disable (enum clk_periph_clken clock)
{
  MMIO8(CLK_BASE + (clock >> 3)) &= ~(1 << (clock & 0x7));
}

void
clk_rtc_select_clock (uint8_t clock)
{
  uint8_t crtcr = CLK_CRTCR;
  do {} while (CLK_CRTCR & CLK_CRTC_SWBSY);

  crtcr &= ~(CLK_CRTC_SEL_MASK << CLK_CRTC_SEL_SHIFT);
  crtcr |= clock << CLK_CRTC_SEL_SHIFT;

  CLK_CRTCR = crtcr;
}

void
clk_rtc_set_prescaler (uint8_t prescaler)
{
  uint8_t crtcr = CLK_CRTCR;
  do {} while (CLK_CRTCR & CLK_CRTC_SWBSY);

  crtcr &= ~(CLK_CRTC_DIV_MASK << CLK_CRTC_DIV_SHIFT);
  crtcr |= prescaler << CLK_CRTC_DIV_SHIFT;

  CLK_CRTCR = crtcr;
}
