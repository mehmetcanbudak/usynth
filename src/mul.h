#ifndef MUL_H
#define MUL_H

/**
	\file Inline assmebly for integer multiplication

	Based on Norbert Pozar's https://github.com/rekka/avrmultiplication,
*/

#define MUL_U16_U8_L16(res, x, y) \
asm( \
"" \
: \
[res] "=r" (res) \
: \
[x] "a" (x), \
[y] "a" (y)  \
)


/*
	16 x 8 => low 16
*/
#define MUL_16_8_L16(intRes, int16In, int8In) \
asm volatile ( \
"mul %A1, %2 \n\t"\
"movw %A0, r0 \n\t"\
"mulsu %B1, %2 \n\t"\
"add %B0, r0 \n\t"\
"clr r1"\
: \
"=&r" (intRes) \
: \
"a" (int16In), \
"a" (int8In) \
)

/*
	16 x 8 => high 16
*/
#define MUL_16_8_H16(intRes, int16In, int8In) \
asm volatile ( \
"clr r26 \n\t"\
"mulsu %B1, %A2 \n\t"\
"movw %A0, r0 \n\t"\
"mul %A1, %A2 \n\t"\
"add %A0, r1 \n\t"\
"adc %B0, r26 \n\t"\
"clr r1 \n\t"\
: \
"=&r" (intRes) \
: \
"a" (int16In), \
"a" (int8In) \
:\
"r26"\
)

/*
	16 x 16 => 32
*/
#define MULU_16_S16_32(longRes, intIn1, intIn2) \
asm volatile ( \
"clr r26 \n\t" \
"mul %A1, %A2 \n\t" \
"movw %A0, r0 \n\t" \
"mul %B1, %B2 \n\t" \
"movw %C0, r0 \n\t" \
"mul %B2, %A1 \n\t" \
"add %B0, r0 \n\t" \
"adc %C0, r1 \n\t" \
"adc %D0, r26 \n\t" \
"mul %B1, %A2 \n\t" \
"add %B0, r0 \n\t" \
"adc %C0, r1 \n\t" \
"adc %D0, r26 \n\t" \
"clr r1 \n\t" \
: \
"=&r" (longRes) \
: \
"a" (intIn1), \
"a" (intIn2) \
: \
"r26" \
) 

/*
	16 x 16 => high 16
*/
#define MULU_16_16_H16(intRes, intIn1, intIn2) \
asm volatile ( \
"clr r26 \n\t" \
"mul %A1, %A2 \n\t" \
"mov r27, r1 \n\t" \
"mul %B1, %B2 \n\t" \
"movw %A0, r0 \n\t" \
"mul %B2, %A1 \n\t" \
"add r27, r0 \n\t" \
"adc %A0, r1 \n\t" \
"adc %B0, r26 \n\t" \
"mul %B1, %A2 \n\t" \
"add r27, r0 \n\t" \
"adc %A0, r1 \n\t" \
"adc %B0, r26 \n\t" \
"clr r1 \n\t" \
: \
"=&r" (intRes) \
: \
"a" (intIn1), \
"a" (intIn2) \
: \
"r26" , "r27" \
) 

#endif