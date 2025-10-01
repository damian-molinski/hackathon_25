#ifndef SDMCTL
#define SDMCTL	 0x022F		
#endif
#define DMACTL_ENABLE_MISSLE_DMA  4
#define DMACTL_ENABLE_PLAYER_DMA  8
#define DMACTL_NORMAL_PLAYFIELD   2
#define DMACTL_DMA_FETCH_INSTRUCTION   0x20
#ifndef PMBASE
#define PMBASE	 0xD407		
#endif
#ifndef GRACTL
#define GRACTL	 0xD01D		
#endif
#ifndef GPRIOR
#define GPRIOR	 0x026F		
#endif
#define PMG_MISSILES 1
#define PMG_PLAYERS  2
#ifndef PCOLR0
#define PCOLR0	 0x02C0		
#endif
#ifndef PCOLR1
#define PCOLR1	 0x02C1		
#endif
#ifndef PCOLR2
#define PCOLR2	 0x02C2		
#endif
#ifndef PCOLR3
#define PCOLR3	 0x02C3		
#endif

#ifndef SIZEP0
#define SIZEP0	 0xD008		
#endif
#ifndef SIZEP1
#define SIZEP1	 0xD009		
#endif
#ifndef SIZEP2
#define SIZEP2	 0xD00A		
#endif
#ifndef SIZEP3
#define SIZEP3	 0xD00B		
#endif

#ifndef SIZEM
#define SIZEM	 0xD00C		
#endif

#ifndef HPOSP0
#define HPOSP0	 0xD000		
#endif
#ifndef HPOSP1
#define HPOSP1	 0xD001		
#endif
#ifndef HPOSP2
#define HPOSP2	 0xD002		
#endif
#ifndef HPOSP3
#define HPOSP3	 0xD003		
#endif

#define SIZEP_SINGLE 0
#define SIZEP_DOUBLE 1
#define SIZEP_QUAD 3
