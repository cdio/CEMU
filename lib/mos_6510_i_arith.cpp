/*
 * Copyright (C) 2020 Claudio Castiglia
 *
 * This file is part of CEMU.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see http://www.gnu.org/licenses/
 */
#include "mos_6510.hpp"


namespace cemu {

/********************************************************************************
 * AND
 ********************************************************************************/
void Mos6510::i_AND_imm(Mos6510 &self, addr_t value)
{
    /*
     * AND #$00
     */
    self._regs.A = self.logic_and(self._regs.A, static_cast<uint8_t>(value));
}

void Mos6510::i_AND(Mos6510 &self, addr_t addr)
{
    /*
     * AND $00
     * AND $00, X
     * AND $0000
     * AND $0000, Y
     * AND $0000, X
     * AND ($00, X)
     * AND ($00), Y
     */
    uint8_t value = self._mmap->read(addr);
    i_AND_imm(self, value);
}


/********************************************************************************
 * BIT (AND Accumulator without store. Modify flags only)
 ********************************************************************************/
void Mos6510::i_BIT(Mos6510 &self, addr_t addr)
{
    /*
     * BIT $00
     * BIT $0000
     *
     * Flags: N V Z
     *
     * 3 cycles
     */
    uint8_t value = self._mmap->read(addr);
    self.set_N(value);
    self.flag_V(value & 0x40);
    value &= self._regs.A;
    self.set_Z(value);
}


/********************************************************************************
 * ORA
 ********************************************************************************/
void Mos6510::i_ORA_imm(Mos6510 &self, addr_t value)
{
    /*
     * ORA #$00
     */
    self._regs.A = self.logic_or(self._regs.A, static_cast<uint8_t>(value));
}

void Mos6510::i_ORA(Mos6510 &self, addr_t addr)
{
    /*
     * ORA $00
     * ORA $00, X
     * ORA $0000
     * ORA $0000, X
     * ORA $0000, Y
     * ORA ($00, X)
     * ORA ($00), Y
     */
    uint8_t value = self._mmap->read(addr);
    i_ORA_imm(self, value);
}


/********************************************************************************
 * EOR
 ********************************************************************************/
void Mos6510::i_EOR_imm(Mos6510 &self, addr_t value)
{
    /*
     * EOR #$00
     */
    self._regs.A = self.logic_eor(self._regs.A, static_cast<uint8_t>(value));
}

void Mos6510::i_EOR(Mos6510 &self, addr_t addr)
{
    /*
     * EOR $00
     * EOR $00, X
     * EOR $0000
     * EOR $0000, Y
     * EOR $0000, X
     * EOR ($00, X)
     * EOR ($00, Y)
     */
    uint8_t value = self._mmap->read(addr);
    i_EOR_imm(self, value);
}


/********************************************************************************
 * ADC
 ********************************************************************************/
void Mos6510::i_ADC_imm(Mos6510 &self, addr_t value)
{
    /*
     * ADC #$00
     */
    self._regs.A = self.adc(self._regs.A, static_cast<uint8_t>(value));
}

void Mos6510::i_ADC(Mos6510 &self, addr_t addr)
{
    /*
     * ADC $00
     * ADC $00, X
     * ADC $0000
     * ADC $0000, X
     * ADC $0000, Y
     * ADC ($00, X)
     * ADC ($00), Y
     */
    uint8_t value = self._mmap->read(addr);
    i_ADC_imm(self, value);
}


/********************************************************************************
 * SBC
 ********************************************************************************/
void Mos6510::i_SBC_imm(Mos6510 &self, addr_t value)
{
    /*
     * SBC #$00
     */
    self._regs.A = self.sbc(self._regs.A, static_cast<uint8_t>(value));
}

void Mos6510::i_SBC(Mos6510 &self, addr_t addr)
{
    /*
     * SBC $00
     * SBC $00, X
     * SBC $0000
     * SBC $0000, X
     * SBC $0000, Y
     * SBC ($00, X)
     * SBC ($00), Y
     */
    uint8_t value = self._mmap->read(addr);
    i_SBC_imm(self, value);
}


/********************************************************************************
 * CMP
 ********************************************************************************/
void Mos6510::i_CMP_imm(Mos6510 &self, addr_t value)
{
    /*
     * CMP #$00
     */
    self.cmp(self._regs.A, static_cast<uint8_t>(value));
}

void Mos6510::i_CMP(Mos6510 &self, addr_t addr)
{
    /*
     * CMP $00
     * CMP $00, X
     * CMP $0000
     * CMP $0000, X
     * CMP $0000, Y
     * CPM ($00, X)
     * CPM ($00, Y)
     */
    uint8_t value = self._mmap->read(addr);
    i_CMP_imm(self, value);
}


/********************************************************************************
 * CPX
 ********************************************************************************/
void Mos6510::i_CPX_imm(Mos6510 &self, addr_t value)
{
    /*
     * CPX #$00
     */
    self.cmp(self._regs.X, static_cast<uint8_t>(value));
}

void Mos6510::i_CPX(Mos6510 &self, addr_t addr)
{
    /*
     * CPX $00
     * CPX $0000
     */
    uint8_t value = self._mmap->read(addr);
    i_CPX_imm(self, value);
}


/********************************************************************************
 * CPY
 ********************************************************************************/
void Mos6510::i_CPY_imm(Mos6510 &self, addr_t value)
{
    /*
     * CPY #$00
     */
    self.cmp(self._regs.Y, static_cast<uint8_t>(value));
}

void Mos6510::i_CPY(Mos6510 &self, addr_t addr)
{
    /*
     * CPY $00
     * CPY $0000
     */
    uint8_t value = self._mmap->read(addr);
    i_CPY_imm(self, value);
}


/********************************************************************************
 * DEC
 ********************************************************************************/
void Mos6510::i_DEC(Mos6510 &self, addr_t addr)
{
    /*
     * DEC $00
     * DEC $00, X
     * DEC $0000
     * DEC $0000, X
     *
     * Flags: N Z
     */
    uint8_t value = self._mmap->read(addr);
    self._mmap->write(addr, value); // Read-Write-Modify instruction.
    --value;
    self.set_N(value);
    self.set_Z(value);
    self._mmap->write(addr, value);
}


/********************************************************************************
 * DEX
 ********************************************************************************/
void Mos6510::i_DEX(Mos6510 &self, addr_t _)
{
    /*
     * DEX
     *
     * Flags: N Z
     */
    --self._regs.X;
    self.set_N(self._regs.X);
    self.set_Z(self._regs.X);
}


/********************************************************************************
 * DEY
 ********************************************************************************/
void Mos6510::i_DEY(Mos6510 &self, addr_t _)
{
    /*
     * DEY
     *
     * Flags: N Z
     */
    --self._regs.Y;
    self.set_N(self._regs.Y);
    self.set_Z(self._regs.Y);
}


/********************************************************************************
 * INC
 ********************************************************************************/
void Mos6510::i_INC(Mos6510 &self, addr_t addr)
{
    /*
     * INC $00
     * INC $00, X
     * INC $0000
     * INC $0000, X
     *
     * Flags: N Z
     */
    uint8_t value = self._mmap->read(addr);
    self._mmap->write(addr, value); // Read-Write-Modify instruction.
    ++value;
    self._mmap->write(addr, value);
    self.set_N(value);
    self.set_Z(value);
}


/********************************************************************************
 * INX
 ********************************************************************************/
void Mos6510::i_INX(Mos6510 &self, addr_t _)
{
    /*
     * INX
     *
     * Flags: N Z
     */
    ++self._regs.X;
    self.set_N(self._regs.X);
    self.set_Z(self._regs.X);
}


/********************************************************************************
 * INY
 ********************************************************************************/
void Mos6510::i_INY(Mos6510 &self, addr_t _)
{
    /*
     * INY
     *
     * Flags: N Z
     */
    ++self._regs.Y;
    self.set_N(self._regs.Y);
    self.set_Z(self._regs.Y);
}


/********************************************************************************
 * ASL (shift left 1 bit)
 ********************************************************************************/
void Mos6510::i_ASL_acc(Mos6510 &self, addr_t _)
{
    /*
     * ASL
     *
     * Flags: N Z C
     */
    self._regs.A = self.logic_shl(self._regs.A);
}

void Mos6510::i_ASL(Mos6510 &self, addr_t addr)
{
    /*
     * ASL $00
     * ASL $00, X
     * ASL $0000
     * ASL $0000, X
     *
     * Flags: N Z C
     */
    uint8_t value = self._mmap->read(addr);
    self._mmap->write(addr, value); // Read-Write-Modify instruction.
    value = self.logic_shl(value);
    self._mmap->write(addr, value);
}


/********************************************************************************
 * ROL (rotate left 1 bit)
 ********************************************************************************/
void Mos6510::i_ROL_acc(Mos6510 &self, addr_t _)
{
    /*
     * ROL $00
     *
     * Flags: N Z C
     */
    self._regs.A = self.logic_rol(self._regs.A);
}

void Mos6510::i_ROL(Mos6510 &self, addr_t addr)
{
    /*
     * ROL $00
     * ROL $00, X
     * ROL $0000
     * ROL $0000, X
     *
     * Flags: N Z C
     */
    uint8_t value = self._mmap->read(addr);
    self._mmap->write(addr, value); // Read-Write-Modify instruction.
    value = self.logic_rol(value);
    self._mmap->write(addr, value);
}


/********************************************************************************
 * LSR (shift right 1 bit)
 ********************************************************************************/
void Mos6510::i_LSR_acc(Mos6510 &self, addr_t _)
{
    /*
     * LSR
     *
     * Flags: N Z C
     */
    self._regs.A = self.logic_shr(self._regs.A);
}

void Mos6510::i_LSR(Mos6510 &self, addr_t addr)
{
    /*
     * LSR $00
     * LSR $00, X
     * LSR $0000
     * LSR $0000, X
     *
     * Flags: N Z C
     */
    uint8_t value = self._mmap->read(addr);
    self._mmap->write(addr, value); // Read-Write-Modify instruction.
    value = self.logic_shr(value);
    self._mmap->write(addr, value);
}


/********************************************************************************
 * ROR (rotate right 1 bit)
 ********************************************************************************/
void Mos6510::i_ROR_acc(Mos6510 &self, addr_t _)
{
    /*
     * ROR
     *
     * Flags: N Z C
     */
    self._regs.A = self.logic_ror(self._regs.A);
}

void Mos6510::i_ROR(Mos6510 &self, addr_t addr)
{
    /*
     * ROR $00
     * ROR $00, X
     * ROR $0000
     * ROR $0000, X
     *
     * Flags: N Z C
     */
    uint8_t value = self._mmap->read(addr);
    self._mmap->write(addr, value); // Read-Write-Modify instruction.
    value = self.logic_ror(value);
    self._mmap->write(addr, value);
}

}
