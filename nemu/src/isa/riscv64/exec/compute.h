//U
static inline def_EHelper(lui)
{
  rtl_li(s, ddest, id_src1->imm);
  print_asm_template2(lui);
}
//U
static inline def_EHelper(auipc)
{
  rtl_li(s, ddest, id_src1->imm);
  print_asm_template2(auipc);
}
//I
static inline def_EHelper(addi)
{
  rtl_addi(s, ddest, dsrc1, id_src2->imm);
  print_asm_template2(addi);
}
