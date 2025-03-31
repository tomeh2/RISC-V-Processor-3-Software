#ifndef __CSR_H_
#define __CSR_H_

#define CSR_CYCLE	0xC00
#define CSR_CYCLEH	0xC80
#define CSR_INSTRET	0xC02
#define CSR_INSTRETH	0xC82
#define CSR_BREXEC	0xC03
#define CSR_BREXECH	0xC83
#define CSR_BRMISPRED	0xC04
#define CSR_BRMISPREDH	0xC84

#define CSR_READ(v, csr)				    \
{							                \
	__asm__ __volatile__("csrr %0, %1"		\
		: "=r" (v)				            \
		: "n" (csr)				            \
		:);					                \
}

#endif