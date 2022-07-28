#include <cpu/exec.h>
#include "../local-include/decode.h"
#include "all-instr.h"

static inline void set_width(DecodeExecState *s, int width)
{
  if (width != 0)
    s->width = width;
}

static inline def_EHelper(load)
{
  switch (s->isa.instr.i.funct3)
  {
    EXW(3, ld, 8)
  default:
    exec_inv(s);
  }
}

static inline def_EHelper(store)
{
  switch (s->isa.instr.s.funct3)
  {
    EXW(3, st, 8)
  default:
    exec_inv(s);
  }
}

static inline void fetch_decode_exec(DecodeExecState *s)
{
  s->isa.instr.val = instr_fetch(&s->seq_pc, 4);
  Log("0x%lx",s->isa.instr.val);
  Assert(s->isa.instr.i.opcode1_0 == 0x3, "Invalid instruction");
  // Log("%d", s->isa.instr.i.opcode6_2);
  switch (s->isa.instr.i.opcode6_2)
  {
    IDEX(0b00000, I, load)
    IDEXW(0b01000, S, store,4)
    IDEX(0b01101, U, lui)
    IDEX(0b00100, I, addi)
    IDEX(0b00101, U, auipc)
    IDEX(0b11011, U, jal)
    EX(0b11010, nemu_trap)
  default:
    exec_inv(s);
  }
  Log("seq:0x%lx  jmp:0x%lx  isJmp:%d",s->seq_pc,s->jmp_pc,s->is_jmp);
}

static inline void reset_zero()
{
  reg_d(0) = 0;
}

vaddr_t isa_exec_once()
{
  DecodeExecState s;
  s.is_jmp = 0;
  s.seq_pc = cpu.pc;

  fetch_decode_exec(&s);
  update_pc(&s);

  reset_zero();

  return s.seq_pc;
}
